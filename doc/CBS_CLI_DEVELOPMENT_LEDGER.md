# CBS CLI 开发台账

记录 ColliderBit Solo（CBS）的命令行、按 HepMC 文件续跑、给某个过程补事例，以及 JSON 输出。检查点驱动、按文件合并和补事例提示已经写进源码。`cmake --build --preset cbs-llvm --target CBS` 已通过。三文件结果尚未与 `0698e7a933` 的单次事例循环对比。

- 更新日期：2026-10-30，Australia/Adelaide。
- 目标分支：`Colliderbit-solo-development-preset`，工作树为 `cbs-presets`。
- 设计基线：`0698e7a933`（屏幕报告、合并 JSON、输出目录）。
- 关联说明：[SUSYRun2 HepMC 卡片](../ColliderBit/examples/SUSYRun2_HepMC.md)、[CMake preset 台账](CMAKE_PRESET_DEVELOPMENT_LEDGER.md)。

## 当前状态

`yaml_files/CBS_SUSYRun2_HepMC.yaml` 同时设置了 `settings.processes` 和 `settings.output`。这种卡片走 `run_with_checkpoints`：每个未完成的 HepMC 文件由一个子进程跑完并发布，父进程再合并。没有 `settings.output`，或仍使用 `event_file` 而没有 `processes` 的卡片，保持原来的一次性事例循环。多个对撞机但没有 `settings.output` 时仍走 `run_joint_colliders`。

`run_and_merge` 没有接到 `solo.cpp`。检查点子进程由 `build_checkpoint_child_yaml` 生成：一个 `event_file`、名义权重尺度 1、保留 Rivet、不跑 Contur。带 `cbs_collider_name` 的子进程不会再次进入检查点驱动。

用户看到的合并 JSON 继续使用 `cbs-solo-loglike-v2`。采样计算没有改。采样表用 `Process` 列点名需要补事例的过程。一行只分给一个过程时，该列只写过程名，事例数留在 `Outcome`。一行分给多个过程时，该列写出各自的份额。表后只留一句追加文件的说明，不再把分析、信号区和事例数重复列一遍。JSON 里的 `process_recommendations` 仍是精确整数。

## 目标

一次 CBS 调用按卡片顺序处理 HepMC 文件。每个文件完整结束后立刻留下一份 JSON。下次调用接着上次的进度：

- 已经完整结束、且指纹仍匹配的文件直接沿用，不再读事例。
- 没写完的文件整份重跑。不从上一个事例号接着读。
- 卡片或文件有改动时，只重跑指纹对不上的文件。
- 全部所需文件都齐了，才合并产额、重算 log L 和 Contur，并写出现在的那份合并 JSON 和屏幕摘要。
- 合并摘要若指出还要更多 MC，用户把新的 HepMC 文件追加到点名的那一个过程。下次调用只跑这些新文件，再与该过程已经保存的文件结果合并。

没有 `settings.output` 的运行保持现在的一次性内存流程，不建立检查点。续跑和补事例都需要一个稳定的输出路径。

## 已定设计

### 续跑单位

检查点的单位是卡片里的一个 HepMC 文件，不是单个事例，也不是整个卡片。

文件 JSON 只有在该文件的事例循环、分析收尾和 Rivet finalize 都成功之后才发布。发布方式是同一目录里先写临时文件，再 `rename` 成最终名字。进程在 rename 之前退出，目录里就没有这份完成记录，下次整份重跑。

不记录“这个文件已读到第 N 个事例”。HepMC 的 gzip 流和 Rivet handler 都没有一个便宜且可靠的中途恢复点。

新事例是追加到该过程 `files` 列表里的新 HepMC 文件。已经跑完的文件保持原样。把事例写进一个已有文件会改变该文件的指纹，那个文件整份重跑。

### 命令行

仍是一条命令，不新增第二个可执行文件，也不要求卡片增加 `resume: true`。不设 `--one-file`。一次调用跑完当前卡片里尚未完成的文件，包括后来追加的新文件。

```sh
./CBS ./yaml_files/CBS_SUSYRun2_HepMC.yaml
./CBS --fresh ./yaml_files/CBS_SUSYRun2_HepMC.yaml
```

| 用法 | 行为 |
| --- | --- |
| `./CBS card.yaml` | 按卡片顺序处理尚未完成或已失效的文件。每完成一个文件就发布该文件的 JSON，然后继续下一个。全部完成后写合并 JSON，并打印现在的屏幕摘要和补事例提示。 |
| `--fresh` | 先拿检查点锁，删掉该输出对应的检查点目录，再从第一个文件开始。已保存的文件结果不再参与合并。 |

`--report` 只改变屏幕详略，不进入文件指纹，也不改变检查点能否复用。

续跑是默认行为，不再设 `--resume`。`--help` 要说明这些进度规则：完成的文件跳过，未完成的文件整份重跑，某个过程新追加的 HepMC 文件只跑新文件并与已保存结果合并，合并结果只在所需文件都齐了之后出现。`--fresh` 删掉该输出的检查点后从头开始。

`keep_batch_tmp` 继续只表示是否保留多对撞机子进程的临时文件。它不表示续跑。

相对输出路径仍相对当前工作目录，和现在的 `settings.output: ./runs/CBS_SUSYRun2_HepMC.json` 一样。

### 给某个过程补事例

这是运行结束后的既定流程，不是新的 YAML 键，也不是新的命令行旗标。采样公式保持现在的 `build_sampling_advice`：追加事例仍是 `ceil(n_events * max(1, (frac/target)^2))` 再减去已有事例，再按该对撞机各过程的截面分配（没有正截面时按已有事例数）。屏幕格式化不改变 JSON 里的整数。

全部所需文件都有效、合并摘要已经打印之后，MC sampling advice 仍按分析、信号区和 Goal 给出总追加事例。`Process` 列点名 `recommended_additional_events > 0` 的过程。该行只有一个这样的过程时，列里只写过程名。多个过程分享一行时，列里写出各自向上取整后的份额，不同分析的建议不相加。表后一行说明把新的 HepMC 文件追加到该过程的 `settings.processes[].files`，然后用同一条命令再跑；已完成文件留在检查点里并与新文件合并。事例数沿用现有屏幕缩写，图例规则不变。JSON 仍写精确整数。

SUSYRun2 这张卡片只有 EWino 一个过程，所以该过程分到对应行 Outcome 的全部事例。多个过程时按现有份额拆开。份额在屏幕上各自向上取整，显示值加起来可以和该行 Outcome 的显示值不同；JSON 里的整数仍然加总等于该行的 `recommended_additional_events`。

用户可以在追加新 run 时改这个过程的截面，使它仍是事例数加权平均。截面和截面不确定度只让父进程重算合并 JSON，不重读已经完成的 HepMC。

下次调用的开跑短表把指纹未变的旧文件标成 `kept` / `complete`，把新文件标成 `run` / `missing`。只执行新文件。父进程用已保存的文件产额和新文件产额重算过程权重、log L、Contur 和采样建议，并覆盖 `settings.output`。中途没有合并摘要，因此也不打印补事例提示。

### 目录

检查点目录由 `settings.output` 推导，不新增必填 YAML 键。输出 `./runs/CBS_SUSYRun2_HepMC.json` 时，进度放在：

```text
runs/CBS_SUSYRun2_HepMC.json
runs/CBS_SUSYRun2_HepMC.cbs/manifest.json
runs/CBS_SUSYRun2_HepMC.cbs/checkpoint.lock
runs/CBS_SUSYRun2_HepMC.cbs/files/<key>.json
runs/CBS_SUSYRun2_HepMC.cbs/files/<key>.yoda
runs/CBS_SUSYRun2_HepMC.cbs/files/<key>.stamp.json
runs/CBS_SUSYRun2_HepMC.cbs/work/
```

`<key>` 是对撞机名、过程名和 HepMC 路径的 FNV-1a 64 位十六进制，不含卡片顺序。顺序只用于屏幕上的 `File 2/3`。身份比较使用 `SoloInput` 已经认定的那条路径，不另做一套 realpath 规则。

完成记录是 `files/<key>.stamp.json`。`manifest.json` 是索引。文件大小和 mtime 以字符串存放，避免超过 JSON 安全整数。`manifest.json` 的格式版本是 `cbs-solo-checkpoint-v1`，和结果 JSON 的 `cbs-solo-loglike-v2` 分开。合并 JSON 的字段和精度保持不变，下游仍读 `settings.output`。

文件 YODA 是 Rivet/Contur 的检查点，即使 `write_YODA_file: false` 也要留下，否则下次无法在不重跑的情况下合并测量。用户可见的 `GAMBIT_collider_measurements_<collider>.yoda` 仍只在该开关为 true 时写到输出目录。`contur.log` 仍是合并后那一次 Contur 的日志。

同一输出路径同时只允许一个 CBS 驱动进程。驱动开始时对 `checkpoint.lock` 加独占锁；锁失败就退出并说明已有运行占用该检查点，不等待、不交互。

### 父进程和子进程

父进程是驱动：列文件、比对指纹、决定跳过或重跑、在文件 JSON 发布后更新 manifest、全部齐了再合并。

每个实际开跑的文件仍是一个新的 CBS 子进程，沿用现在的 fork/exec。子进程只看到这一个 `event_file`，并带上 `cbs_collider_name`，因此不会把临时 JSON 宣称为用户的合并结果，也不会把检查点目录当成另一套运行目录。Rivet handler 和分析静态状态留在子进程里，父进程不尝试在同一个进程里清空它们。

子进程把 `cbs_file_weight_scale` 设为 1，只保留名义权重，并把当时的过程截面写进文件 JSON 的 `sigma_stored`。子进程产额因此是 `L * sigma_stored / N_file * sum(nominal)`。父进程乘以 `f = (sigma_new / sigma_stored) * N_file / S_p`，得到 `L * sigma_new / S_p * sum(nominal)`。对外 JSON 的 `weight_scale` 是混合物尺度 `c_p = N * sigma_p / (sigma * S_p)`，不是子进程的 1。Cutflow 计数是原始事例数，相加，不乘 `f`。然后调用现有的 `calc_LHC_LogLikes_common`。log L 不能把各文件的 log L 相加。过程下新增文件后，过程总权重变了，父进程用各文件已经保存的产额重算份额；已完成文件的 JSON 保存的是可合并的产额，不是最终 log L。

检查点里的 YODA 保持名义权重。子进程先写到 `work/<key>.tmp.yoda`：YODA 按最后一个扩展名选择格式，`.yoda.tmp` 会被拒绝。父进程确认后再改名为 `files/<key>.yoda`。父进程按 `c_p` 缩放 `/RAW/` 里的 Fillable（含 `_EVTCOUNT`，不含 `_XSEC` 和 `_BEAMPZ`）。`/RAW/` 里的 Estimate 是 finalize 之前的空位，不是权重和，不乘 `c_p`；合并后由分析的 finalize 重算。然后对每个对撞机做一次等价 merge、写回对撞机截面，再跑一次 Contur。`contur_evaluations` 按对撞机计，不按文件计。

因此下面这些改动只让父进程重算合并 JSON，不重读 HepMC：

- 过程或对撞机截面及其不确定度
- 似然开关、nuisance 设置、FullLikes 选择
- 采样建议的目标比例
- `report` 和 `screen_output`

下面这些改动使受影响对撞机的全部文件失效：

- `analyses` 列表
- `rivet-settings.analyses`、`exclude_analyses` 和 `contur-settings`
- jet collection、`jet_collection_taus`、`jet_pt_min`、`nominal_weight_name`、seed
- 对撞机束流和能量
- 构建期 Cutflow 开关、`check_cutflow`、`check_histogram`
- `trace_input_events` 和 `drop_accepted_events_file`

`write_YODA_file`、`drop_YODA_file`、`YODA_filename` 和 `YODA_output_directory` 不进入指纹。翻转是否写出用户可见的 YODA 不会重跑 HepMC。`--report` 只影响屏幕，也不进入指纹。

HepMC 检查写在 `files/<key>.stamp.json` 里：束流、能量、名义权重名和序号、事例数、权重和。父进程看到大小、mtime 和名义权重名都未变时，不再打开这个已经分析过的文件，验证表的状态写 `checkpoint`。分析指纹变化仍重跑该文件，但不再为了检查而重读 HepMC。大小或 mtime 变化时重新检查，并只重跑该文件。某个过程的 `files` 里新增文件时，该过程和其他过程里已完成且指纹未变的文件继续沿用，只跑新文件。调换卡片里的文件顺序不使内容失效；manifest 按路径识别文件，顺序只影响屏幕上的 `File 2/3`。

分析代码本身的变化不自动进入指纹。需要因分析实现变化而重跑时使用 `--fresh`。

### 屏幕

父进程在开跑前打印一张短表：文件、状态（`kept`、`run`、`rerun`）、原因（`complete`、`missing`、`incomplete`、`file changed`、`settings changed`）。

每个待跑文件启动前，父进程打印 `Running File i/n` 和该 HepMC 路径并刷新。子进程进度行接着写 `CBS HepMC File i/n`。每发布一个文件 JSON，打印该 JSON 的绝对路径。`screen_output: false` 时不打印这张表、`Running File` 行和检查点路径。全部文件有效后，才打印现在的 Summary、分析表、Contur、采样建议、补事例提示、归一化表，以及合并 JSON 的 `Wrote` 行。文件还没齐时，不给出部分样本的总 log L，也不提示补事例。

### 和现有路径的关系

单对撞机、带 `settings.processes` 的卡片改由新的驱动处理，包括现在这张带 Rivet/Contur 的 SUSYRun2 卡片。切换默认路径之前，三个文件的合并 log L、Contur 和采样建议必须与 `0698e7a933` 的单次事例循环一致。这一对比由维护者重编译后运行，本设计不记录尚未产生的数值。

多个对撞机时，驱动先按对撞机分开，再按文件做检查点。每个对撞机在自己的文件齐了之后做一次 Rivet merge 和一次 Contur。不同对撞机的同名 Contur pool 仍按现在的规则报错。补事例只跑用户追加了新文件的那个过程；其他过程的已完成文件保持 `kept`。

GAMBIT 的 ScannerBit 扫描不读这个检查点目录，也不写 `cbs-solo-checkpoint-v1`。

## 明确不做

- 从 HepMC 文件中途的某个事例恢复。
- 增加 `--one-file`，或让一次调用在还有未完成文件时停下来。
- 为补事例增加必填 YAML 键或单独旗标。
- 并行跑同一个输出目录下的多个文件。
- 把各文件的 log L 加起来当作总 log L。
- 把不同分析的追加事例建议加总成一个过程配额。
- 从一份旧的合并 JSON 反推出每文件检查点。没有检查点目录时，下次把所有文件视为未跑。
- 为检查点另设 `GAMBIT_RUN_DIR` 或 preset 专用构建目录。

## 工作包

| 编号 | 状态 | 内容 | 验收 |
| --- | --- | --- | --- |
| CLI-01 | 已确认 | 2026-10-30 定稿：一次调用跑完剩余文件和新增文件，每个文件后落盘，齐了再合并。不设 `--one-file`。保留 `--fresh`。合并摘要点名需要补事例的过程；下次只跑该过程新追加的 HepMC 文件并与已存结果合并 | 本节与下表一致 |
| CLI-02 | 代码已落地 | 父进程驱动、文件锁、原子发布、manifest 和 stamp。搜索产额在父进程合并 | 运行验收仍由维护者完成。杀掉正在跑的第二个文件后，第一个文件的 JSON 仍在；下次只重跑第二个文件 |
| CLI-03 | 代码已落地 | 指纹和失效规则。截面、似然开关只重算合并 JSON；分析列表和文件大小变化按规则重跑。指纹包含 `trace_input_events` 和 `drop_accepted_events_file` | 运行验收仍由维护者完成。用三文件卡片的小型替身验证 kept、rerun 和 settings changed |
| CLI-04 | 代码已落地 | 每文件 YODA 与父进程 merge，然后每个对撞机一次 Contur。`write_YODA_file: false` 时检查点保留文件 YODA，输出目录仍不写合并 YODA | 运行验收仍由维护者完成。与单次事例循环的 ColliderBit log L 和 Contur log L 一致之后，才把 SUSYRun2 的数值当作已核对 |
| CLI-05 | 代码已落地 | `--fresh`、进度表、补事例提示和 `--help`。采样计算不变 | 运行验收仍由维护者完成。`--help` 与真实进度规则一致，且不出现 `--one-file`。提示含过程名，事例数用现有向上取整缩写；JSON 仍是精确整数 |
| CLI-06 | 代码已落地 | 三文件卡片的中断、续跑，以及给一个过程追加新文件 | 运行验收仍由维护者完成。中断第二个文件，续跑后的合并 JSON 与一次跑完的结果一致。再在该过程 `files` 末尾追加一个新 HepMC 文件时，只跑这个新文件，并用旧文件已存产额与新文件产额重算合并 JSON，不重读旧文件 |

代码在 `solo.cpp`、`solo_batch.cpp`、`ColliderBit_measurements.cpp` 和 `cbs_multifile_acceptance.py`。验收测试删除输出 JSON 时也会删除旁边的 `.cbs` 目录。`cmake --build --preset cbs-llvm --target CBS` 已通过。没有运行 CBS。数值是否与 `0698e7a933` 一致，仍要等维护者跑过三文件卡片后再比。
