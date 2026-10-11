# CMake Preset 开发台账

记录 GAMBIT 和 ColliderBit Solo 的 preset、CMake 构建与开发体验改进。C++ 标准统一和 BUILD-01 已提交，维护者反馈 BUILD-01 重新编译及 touch 后构建都很快。BUILD-02 已完成脚本检查，并由维护者日志确认独立对象构建、完整链接及主工程无变化构建通过；实际并行重叠与运行场景仍待验证。BUILD-03 已接入可选 ccache，维护者日志确认真实 launcher 与完整 CBS 链接成功；精确命中增量和开关场景仍待补齐。BUILD-04 已移除三处停用即删除逻辑，并保留停用包的显式清理入口；5 组夹具检查通过，维护者日志确认 RestFrames OFF/ON 后安装保留、外部目标复用及完整 CBS 构建成功；HepMC/YODA 停用场景仍待验证。BUILD-05 已增加 FastJet/Contrib 文件与构建身份检查，11 组脚本夹具通过；维护者日志确认首次迁移重建、成功记录、相同配置复用及完整 CBS 构建通过。BUILD-07 已为日志中的三包接入输入状态检查和成功安装后记录，11 组脚本夹具通过；维护者日志确认首次建立记录、直接重复构建和相同配置后复用均成功，三包重复步骤已跳过。BUILD-08 的 RestFrames 阶段已完成首次迁移、恢复 ON 六个对象与最后无变化构建验收；ONNX/两包 RPATH 阶段完成首次迁移、四次开关、CBS 启动、真实文件快照及最后无变化构建验收。当前 macOS cbs-llvm 构建基线进入交付收尾，物理运行、新环境、其他依赖和平台分别记录。

- 更新日期：2026-10-12，Australia/Adelaide。
- 目标分支：`Colliderbit-solo-development-preset`，工作树为 `cbs-presets`。
- C++ 标准、BUILD-01 和台账已提交为 `a3b3cc87c7`，实施基线为 `28600078fc`。
- BUILD-02 已提交为 `957c81ecd9`，父提交为 `a3b3cc87c7`；包含独立程序对象目标、脚本回归及维护者日志验收记录。
- BUILD-03 已提交为 `0965735828`，父提交为 `957c81ecd9`；包含可选 ccache、摘要、策略测试和维护者构建记录。
- BUILD-04 已提交为 `1d46bf0439`，父提交为 `0965735828`；包含三包停用保留、显式清理入口及维护者验收记录。
- BUILD-05 已提交为 `09929f07fb`，父提交为 `1d46bf0439`；当前 macOS LLVM 首次迁移及相同配置复用已验收。
- BUILD-07 已提交为 `0c3ea3e566`；当前 macOS LLVM 首次记录、直接重复构建及相同配置复用已验收；BUILD-06 按维护者选择暂缓。
- BUILD-08 RestFrames 阶段已提交为 `eb03406a7c`，父提交为 `0c3ea3e566`；当前环境迁移、恢复 ON 和无变化构建已通过。ONNX/两包 RPATH 阶段提交为 `52aaf8434f`；首次迁移、四次开关、启动、快照及最后 no-op 通过，其他依赖与平台仍按范围验收。
- DOC-01/DOC-02 文档政策与原 HPC 示例已提交为 `eeaf63d5ef`，包含当前 cbs-llvm 两轮无变化验收记录；BUILD-08 四次开关及最终 no-op 现已通过，验收入口随本轮提交。
- 关联文档：[Preset 使用说明](../cmake/presets/README.md)、[CMake Preset 工程标准](CMAKE_PRESET_STANDARD.md)、[仓库开发规则](../AGENTS.md)。

## PR 前兼容性修复（2026-10-12）

比较基线为本地 `gambit/ColliderBit_solo_development`（`b356b08b04`），修复在 preset 分支实施，基于 `b4a0a6120b`。四项均已实现并完成脚本检查，随本轮授权提交；真实 CBS 构建仍待维护者执行，先前验收记录不替代本轮验证。

| 问题 | 修复 | 检查 |
| --- | --- | --- |
| P1：YODA 的 `file(CHMOD)` 需要 CMake 3.19，破坏普通 GAMBIT 的 3.16.3 入口 | UNIX 下使用 `chmod 755`，失败清楚报错；preset 最低版本和主工程最低版本保持原约定 | 临时 h5cc 包装脚本可执行、仅规范化 `-showconfig`、原参数完整传递，权限失败退出；未使用 CMake 3.16.3 二进制做真实配置 |
| P2：首次显式设置 backend 裁剪被自动默认值覆盖 | 没有自动记录的值按显式选择保留；覆盖自动默认值后移除自动记录，后续模块切换继续保留 | 首次显式 OFF/ON、全模块与子集自动切换、覆盖后反复切换 |
| P2：链接库整体去重破坏重复静态库及 `optimized`/`debug`/`general` 配对 | 只过滤原有无效 `-L` 项，保留其他条目的顺序和次数 | 配置关键字、多次库引用、link group 及有效目录项均完整保留 |
| P2：RestFrames 停用保留后可能复用旧工具链或 flags 的对象 | 接入 contrib 构建身份；包含编译器、flags、ROOT、平台和补丁输入；仅身份匹配且必要安装文件存在时复用 | 同配置 OFF/ON 与缺失 EP 标记保留文件；配置变化拒绝旧对象；临时 Git tag 重建干净源码；补丁变化、缺文件、失败保留原安装和路径边界 |

检查入口为 [merge_compatibility.py](../cmake/tests/merge_compatibility.py) 和 [restframes_build_identity.py](../cmake/tests/restframes_build_identity.py)。联动复查 contrib 保留、FastJet 身份、RestFrames/ONNX 范围、standalone 对象，共 54 组 Python 脚本检查通过；C++ 政策 30 项通过。全部使用临时文件、临时 Git 仓库、捕获的 target/ExternalProject 注册及 `cmake -P`，没有工程配置、编译器探测、make、网络访问或真实安装清理。

RestFrames 旧安装尚无身份记录，首次启用构建会重建一次并在成功安装后记录。配置阶段只写入 build/ 请求和失效步骤标记；真实源码准备在 build 阶段进行。优先从本地 Git tag 克隆干净源码，只有无 `.git` 的 source drop 或缺少 tag 才需要从上游重新下载；准备失败保留原安装。相同身份重新配置及 OFF/ON 不删除源码或安装。

维护者先在当前工作树执行以下命令，不需要清空 build/：

```sh
cmake --preset cbs-llvm
cmake --build build --target CBS -j8
cmake --build build --target CBS -j8
cmake --preset cbs-llvm
cmake --build build --target CBS -j8
```

预期首轮 RestFrames 显示 `no recorded build identity` 并重新构建；成功后存在 `contrib/RestFrames-1.0.2/.gambit-restframes-build-identity`。后两轮构建应无重复编译/链接，最后配置显示身份匹配。随后可运行已有 `python3 cmake/scripts/cbs_feature_acceptance.py --run --jobs 8`，检查两项 OFF/ON 和最后无变化构建。若测试工具链切换，仍按既有共享 build/ 政策使用 `--fresh`；需要看到 RestFrames 拒绝旧身份并重建，匹配 ROOT/C++ 标准后再恢复原 preset。

## 状态与验收规则

| 状态 | 含义 |
| --- | --- |
| 已合入 | 已有 Git 提交；构建验证情况单独记录 |
| 已实现待构建 | 代码已写入工作树，完成所列静态或脚本检查，尚未完成真实构建验收 |
| 已实现已构建 | 实现完成，维护者已执行所记录的实际构建场景；提交状态、测量证据及未测场景单独记录 |
| 部分完成 | 所列子项中已有实现，其余子项仍待开发或验收 |
| 待开发 | 问题或改进方向已确认，尚未实现 |
| 待评估 | 需要进一步设计或测量后决定是否实施 |
| 待提交 | 所列修改和相应检查已完成，等待维护者授权提交；实际构建记录另记 |
| 暂缓 | 维护者选择暂不推进，重新启动需有明确需求 |

P1 优先处理配置正确性、重复构建和主要编译等待；P2 改善可复用性、诊断与使用体验；P3 为后续能力。合入、测试通过和性能收益分别记录，不能相互替代。

## 已有基础与历史记录

| 编号 | 日期 | 事项 | 状态与证据 |
| --- | --- | --- | --- |
| BASE-01 | 2026-10-09 | 合入 `ColliderBit_solo_development` 的新增功能与兼容性更新，保留 preset 集成 | 已合入，提交 `1521dee5ba`；包括 CBS 功能、CMake 冲突处理及依赖解压和补丁流程整合 |
| BASE-02 | 2026-10-09 | 原生工具链发现、preset 摘要及只读 bootstrap | 已合入，相关提交 `805929b308`、`166db2dae0`、`28600078fc` |
| BASE-03 | 2026-10-09 | 模块选择改变后更新自动后端接口裁剪 | 已合入，提交 `ec454fe7df`；后续优化继续保留 `Bits=ColliderBit` 与后端裁剪 |

此前维护者报告两个工作树的 CBS 构建约为 48 分钟和 14 分钟，命令均为 `cmake --build build --target CBS -j8`。当时两边的模块选择、后端接口范围和外部依赖复用情况不同，因此这组数字是排查背景，不能作为本轮 C++ 修改的前后性能基准。

## C++ 标准修复记录

以下项目均在 2026-10-10 实现并提交为 `a3b3cc87c7`。当前 macOS LLVM、AUTO、ROOT 17 的配置和 CBS 构建已有日志；其他标准选择、冲突拒绝、跨平台及运行场景仍按下方矩阵验收。

| 编号 | 问题与改动 | 代码位置 | 构建验收要点 |
| --- | --- | --- | --- |
| CXX-01 | 统一标准选择；使用 `CMAKE_CXX_STANDARD`，开启 REQUIRED、关闭扩展；显式值优先，未指定时自动选择 23、20、17 | [CXXStandard.cmake](../cmake/CXXStandard.cmake)，[主配置](../CMakeLists.txt) | 主工程实际编译命令与选定标准一致；自动选择不会变成下一次配置的显式缓存请求 |
| CXX-02 | ROOT 必须与主工程使用同一标准；自动模式跟随 ROOT，显式冲突清楚报错 | [optional.cmake](../cmake/optional.cmake)，`gambit_match_root_cxx_standard` | ROOT 17 配显式 20 时配置失败；自动模式配 ROOT 17 时生效标准为 17 |
| CXX-03 | 修复 ROOT 自动发现覆盖 `WITH_ROOT=OFF`；统一旧别名和 `gnu++` 解析；拒绝未知或不支持的标准 | [CBSRootDiscovery.cmake](../cmake/presets/CBSRootDiscovery.cmake)，[CBS.cmake](../cmake/CBS.cmake) | 显式 OFF 保持关闭；无效元信息能够按规则回退到 flags，未知标准不被误报为可用 |
| CXX-04 | 同步普通、无优化和 MPI 三类 backend flags；保留包级标准例外并规范化私有参数 | [CXXStandard.cmake](../cmake/CXXStandard.cmake)，[contrib.cmake](../cmake/contrib.cmake)，[backends.cmake](../cmake/backends.cmake) | ROOT 调整标准后，三类参数全部同步；例外包保持各自要求 |
| CXX-05 | 外部依赖最低标准判断改为数值比较，避免将 C++20/23 误判为不满足 C++14/17 | [externals.cmake](../cmake/externals.cmake) | 更高标准满足较低要求；高于当前标准的要求被排除并说明原因 |
| CXX-06 | C++ 编译链接检查使用实际标准，按输入签名失效缓存；摘要显示请求、最终标准与原因 | [CBSValidation.cmake](../cmake/presets/CBSValidation.cmake)，[CBS 摘要](../cmake/presets/CBSCompilerSummary.cmake)，[GAMBIT 摘要](../cmake/presets/GAMBITBuildSummary.cmake) | 切换标准或相关 flags 后重新验证；未变化时复用结果；摘要与实际命令一致 |

### 当前标准约定

| 范围 | 约定 |
| --- | --- |
| 主工程 | C++17、C++20、C++23；最低为 C++17，当前不启用 C++26 |
| 自动选择 | 在 CMake 和编译器已知的模式中按 23 → 20 → 17 选择；ROOT 启用后精确对齐其标准 |
| 显式选择 | `-DCMAKE_CXX_STANDARD=17`、`20` 或 `23`；与 ROOT 或 legacy flags 冲突时报错 |
| CMake 版本 | 原生 C++23 属性要求 CMake ≥ 3.20；较旧的受支持 CMake 自动选择最高到 C++20 |
| 旧 flags | 识别 `c++`、`gnu++` 及 `1z`、`2a`、`2b`；以最后一个标准参数为准，跨配置冲突仍报错 |
| 外部包例外 | macOS Pythia 最高 C++17；GM2Calc 1.2/1.3 使用 C++14；Rivet 使用 C++17；HepMC 随 ROOT，未启用 ROOT 时为 C++17 |

这些是语言模式约定，不表示所有编译器都完整实现该标准的每项语言与标准库特性。ROOT 的精确匹配要求见 [ROOT 官方构建说明](https://root.cern/install/build_from_source/#caveats)；原生属性版本见 [CMake CXX_STANDARD 文档](https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html)。

### 已完成验证

| 验证 | 结果 | 范围 |
| --- | --- | --- |
| 仓库内策略脚本 | 30 项通过 | 15 个选择案例、4 个解析案例、11 个应拒绝的配置；入口为 [cxx_standard.cmake](../cmake/tests/cxx_standard.cmake) |
| 临时 ROOT 测试 | 7 项通过 | 6 个元信息或 flags 回退案例，以及 1 个显式 OFF 案例；临时夹具未纳入仓库 |
| CMake 结构检查 | 通过 | 本轮 12 个 CMake 文件的命令及块结构 |
| 差异与格式检查 | 通过 | 本轮修改和新增文件的空白检查及代码复核 |
| 实际配置与 CBS 构建 | 当前环境通过 | 2026-10-10 维护者日志：`cbs-llvm`、LLVM 22.1.8、ROOT 6.40.00，AUTO 生效为 C++17；CBS 程序对象编译及完整链接成功；其他矩阵场景及单点运行仍待执行 |

脚本检查不调用项目配置或编译器，可在仓库根目录运行：

```sh
cmake -P cmake/tests/cxx_standard.cmake
```

## 构建性能与增量正确性待办

| 编号 | 优先级 | 状态 | 问题与实施方向 | 主要位置与验收标准 |
| --- | --- | --- | --- | --- |
| BUILD-01 | P1 | 已实现已构建 | 保留 harvest 标记；登记实际 Python、完整参数及输入/输出清单；补全 header 与 harvest 顺序依赖；functor 使用独立完成标记和稳定排序，源码仅内容变化时更新 | [主配置](../CMakeLists.txt)、[utilities.cmake](../cmake/utilities.cmake)、[CodeGeneration.cmake](../cmake/CodeGeneration.cmake)、[standalone_facilitator.py](../Elements/scripts/standalone_facilitator.py)。相同配置再次生成后构建，不应重编译未变化的 functor 源码 |
| BUILD-02 | P1 | 已合入 | standalone 自身源码移入独立 `<name>_objects` OBJECT target；等待 contrib 和生成头文件后，可与模块对象及后端库构建并行；最终可执行文件保留完整依赖 | [utilities.cmake](../cmake/utilities.cmake) 的 `add_standalone`、`gambit_configure_standalone_objects`。CBS 使用 `CBS_objects`；保留 BOSS → harvest 顺序和编译上下文；用实际构建日志确认并行重叠 |
| BUILD-03 | P2 | 已合入 | 使用 `GAMBIT_COMPILER_CACHE=AUTO/CCACHE/OFF` 接入原生 C/CXX launcher；preset 首次默认 AUTO，普通首次配置默认 OFF；逐语言保留显式 launcher（含空值），自动值不写入持久缓存；摘要显示策略、版本和实际 launcher | [CompilerCache.cmake](../cmake/CompilerCache.cmake)、[主配置](../CMakeLists.txt)、[CBS 摘要](../cmake/presets/CBSCompilerSummary.cmake)、[GAMBIT 摘要](../cmake/presets/GAMBITBuildSummary.cmake)。7 组策略脚本通过；真实 launcher 与完整 CBS 链接已有维护者日志，全局缓存已有命中；同文件命中增量与开关场景尚未记录。Fortran 与外部项目分别处理，首次全量编译不承诺提速 |
| BUILD-04 | P1 | 已合入 | 移除 RestFrames/HepMC/YODA 停用分支中的自动删除及未使用的 `nuke_ditched_contrib_content`；保留源码、安装、外部构建目录和步骤标记；三包的显式 clean/nuke 在停用时也可用 | [contrib.cmake](../cmake/contrib.cmake)、[contrib_retention.py](../cmake/tests/contrib_retention.py)。5 组夹具检查通过；当前 macOS LLVM 环境 RestFrames OFF/ON 保留复用和完整 CBS 构建已通过；HepMC/YODA 停用及清理入口的真实验收待补齐 |
| BUILD-05 | P1 | 已合入 | FastJet/Contrib 每次重新搜索并检查实际文件；复用须匹配成功安装后的构建身份；缺失或不匹配时使所属步骤失效，构建阶段从校验过的归档恢复干净源码；FastJet 重建级联至 Contrib | [contrib.cmake](../cmake/contrib.cmake)、[ContribBuildIdentity.cmake](../cmake/ContribBuildIdentity.cmake)、[contrib_build_identity.py](../cmake/tests/contrib_build_identity.py)。11 组脚本夹具通过；当前 macOS LLVM 首次迁移、安装身份、相同配置复用及完整 CBS 构建已通过；直接无配置重复构建、时间戳对照和其他平台待补齐 |
| BUILD-06 | P3 | 暂缓 | 维护者此前使用 Ninja 未成功，选择继续 Unix Makefiles；Ninja 适配暂不推进 | [utilities.cmake](../cmake/utilities.cmake) 的 `MAKE_PARALLEL`。若后续明确重启，仍需分离主 generator 与外部 make 工具，并完善生成物声明；不能只替换 preset 的 generator |
| BUILD-07 | P2 | 已合入 | 为 nulike 1.0.9、Rivet 4.1.0、Contur 3.0.0 声明输入和关键产物；成功安装后记录状态，无变化保留 build 标记；编辑/touch/增删源码或缺产物时使所属步骤失效；其他包保留原策略 | [ExternalAutoRebuild.cmake](../cmake/ExternalAutoRebuild.cmake)、[external_rebuild.py](../cmake/scripts/external_rebuild.py)、[externals.cmake](../cmake/externals.cmake)、[backends.cmake](../cmake/backends.cmake)。11 组临时检查通过；当前环境首次记录、直接重复构建及重新配置后跳过已通过，时间戳对照及源码 touch 待补齐 |
| BUILD-08 | P2 | 部分完成 | RestFrames PRIVATE include/专用头阶段已合入并验收；本轮实现 ONNX 专用头/PUBLIC include 范围与 RestFrames/ONNX 按实际链接消费添加 RPATH；其他可选依赖按需继续审计 | [contrib.cmake](../cmake/contrib.cmake)、[utilities.cmake](../cmake/utilities.cmake)、[preprocessor.cmake](../cmake/preprocessor.cmake)、[onnxruntime_scope.py](../cmake/tests/onnxruntime_scope.py)。本轮 27 组脚本检查、首次迁移/CBS 启动和实际 include/RPATH 范围通过；已提交为 `52aaf8434f`。ONNX 三对象、RestFrames 六对象、95 个文件的开关快照和最后无变化构建均已通过；验收入口随本轮提交，其他依赖及平台按需验收 |

BUILD-02 的问题由原生成 Makefile 的依赖顺序确认；实现后独立对象目标及无变化构建已通过，实际并行重叠和节省时间尚未测量。BUILD-03 改善缓存命中的重复编译，不能解决所有首次编译等待。BUILD-07 由维护者无变化日志及当前生成规则确认；当前三包已接入状态检查；维护者日志确认直接重复构建及相同配置后跳过重复步骤，具体耗时未测量。

### BUILD-01 实施与验证

2026-10-10 完成以下修改。维护者随后反馈已完成测试：重新编译，以及 `touch` 之后的重新编译都很快。当前实际构建证据为维护者反馈，未记录具体耗时、构建日志或时间戳对比；不据此填写量化提速或其他平台结论。

- 相同配置保留五个 harvest 完成标记，不再在配置阶段统一删除。
- options 标记记录 `Python3_EXECUTABLE`、ditch 参数、`*_EXTRA_ARGS`、输入及输出清单。相同清单保持时间戳；新增或删除文件在重新配置后使对应生成步骤失效。
- module 输入覆盖递归解析的工程头文件、默认 BOSS 命名空间及类型等价配置；backend 输入覆盖 Bit 头文件、frontend shared includes 和 BOSS 类型。剔除生成器自己的输出，避免自身反复失效。
- module harvest 显式等待 model、backend 和启用的 collider harvest；原有 BOSS → backend harvest 顺序保持。
- 各 standalone 的 `functors_for_<name>.stamp` 记录完成时间，C++ 文件作为 `BYPRODUCTS` 登记；去除源码上的强制 `touch`。两类模板类型都按名称排序。
- 重新配置时检查生成物是否缺失，只删除所属生成器的完成标记。Unix Makefiles 下，手工移走生成物后先重新配置再构建；正常 `clean` 会同时清理完成标记和生成物。

脚本回归入口为 [code_generation.py](../cmake/tests/code_generation.py)，可在仓库根目录执行：

```sh
python3 cmake/tests/code_generation.py
```

已通过 6 组测试：相同 options 保持时间戳；解释器、额外参数、输入增删与参数边界改变使 options 失效；缺失输出仅影响所属生成器；实际 CMake 注册函数使用正确解释器、完成标记和依赖顺序；输入发现覆盖 shared/BOSS/type 头文件且排除自身输出；真实 facilitator 在不同 `PYTHONHASHSEED` 下保持输出 hash/时间戳，新增类型时更新输出。另已检查 CMake/Python 结构、输入清单不含生成器自身输出。测试仅运行脚本和临时夹具，不执行项目配置、编译器探测或构建，不能代替 Make 构建图的实际验收。

#### 维护者验收步骤

以下命令适用于当前 `cbs-presets` 工作树的 `cbs-llvm` 配置。若使用其他 preset，所有步骤保持同一个 preset 及相同参数。测试期间不要 `--fresh`、`clean` 或切换标准、依赖开关；这些操作会改变对比条件。

1. 更新构建图并构建一次，建立基线。首次可能因为此前 C++ 修改、类型排序及新完成标记而重新编译，这是正常的一次性更新。

   ```sh
   cd /Users/p.zhu/Gambit-Workshop/worktree/cbs-presets
   set -o pipefail
   cmake --preset cbs-llvm
   cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-build01-baseline.log
   ```

2. 在 macOS 保存生成源码、对应对象和完成标记的时间戳：

   ```sh
   stat -f '%m %N' ColliderBit/examples/functors_for_CBS.cpp \
     build/CMakeFiles/CBS.dir/ColliderBit/examples/functors_for_CBS.cpp.o \
     build/modules_harvested build/functors_for_CBS.stamp > /tmp/cbs-build01-before.txt
   ```

3. 不改源码，先重复构建，再执行相同配置并构建。配置命令必须与第一步保持相同参数。

   ```sh
   cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-build01-noop.log
   cmake --preset cbs-llvm
   cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-build01-reconfigure.log
   stat -f '%m %N' ColliderBit/examples/functors_for_CBS.cpp \
     build/CMakeFiles/CBS.dir/ColliderBit/examples/functors_for_CBS.cpp.o \
     build/modules_harvested build/functors_for_CBS.stamp > /tmp/cbs-build01-after.txt
   diff -u /tmp/cbs-build01-before.txt /tmp/cbs-build01-after.txt
   ```

   预期 `diff` 没有输出。日志可以有 `Built target ...`；不应重新生成 harvest/functor 完成标记，不应编译未变化的 CBS 对象或再次链接 CBS。如仍有其他对象重编译，记录具体对象和触发依赖，继续排查。

4. 验证生成器需要重跑但内容不变时的行为。以下 `touch` 仅改变脚本修改时间，不修改源码内容：

   ```sh
   touch Elements/scripts/standalone_facilitator.py
   cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-build01-generator.log
   cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-build01-generator-noop.log
   ```

   第一次应执行 facilitator、更新 `functors_for_CBS.stamp`，但保持生成 C++ 文件及其对象时间戳，也不应重新链接 CBS；第二次应恢复无变化构建。真实新增类型会更新输出，已由脚本测试覆盖。

| 验收项 | 状态 | 维护者实测记录 |
| --- | --- | --- |
| 六组脚本回归与结构检查 | 已通过 | 2026-10-10；无项目配置或编译 |
| 相同配置重复构建 | 维护者反馈通过 | 2026-10-10：测试已完成，重新编译很快；未记录具体耗时或日志 |
| 无变化重新配置后构建 | 维护者反馈通过 | 2026-10-10：维护者在上述验收流程后反馈重新编译很快；未记录时间戳对比或日志 |
| 修改生成器时间但输出内容不变 | 维护者反馈通过 | 2026-10-10：touch 后重新编译也很快；未记录完成标记、源码和对象的时间戳对比 |
| 文件增删或生成物缺失后重新配置 | 待执行 | 对应生成器正确失效、恢复输出 |

### BUILD-02 实施与验证

2026-10-10 基于 `a3b3cc87c7` 完成修改。维护者随后提供配置、独立对象构建、完整构建及无变化构建日志，独立对象构建、完整链接和无变化主工程构建通过，随本轮提交合入；并行重叠和单点运行尚未验收。

- 所有 `add_standalone` 创建的程序源码使用 `<name>_objects` OBJECT target；CBS 的 `solo.cpp`、`solo_cli.cpp`、`solo_input.cpp`、`solo_batch.cpp`、`solo_output.cpp` 移入 `CBS_objects`，每份源码只编译一次。
- 新对象目标等待 contrib、model/backend/module/printer harvest，使生成头文件和依赖包头文件先就绪；原有 BOSS → backend harvest → module harvest 顺序保持。对象目标不接入 ColliderBit 等模块对象库或 nulike/Rivet/Contur 的完整构建依赖。
- 对象目标复制最终 executable 创建时的编译属性和 `LINK_LIBRARIES` 使用要求，涵盖 include、宏、options、标准、可见性、架构、IPO 等；`CBS_EXPORTS` 等导出宏单独保留。依赖库提供的编译要求及其必要准备仍生效。
- 最终 executable 继续包含全部模块和公共对象，并保持完整后端依赖、链接库顺序与导出行为。生成的 `functors_for_<name>.cpp` 保留为 executable 的实际源码，其 BUILD-01 完成标记机制保持。
- 新对象目标设置 `EXCLUDE_FROM_ALL`，避免默认构建额外编译未选中的 standalone。上述变化统一作用于 standalones，普通 GAMBIT executable 的源码与构建方式保持。
- 工程仍使用共享 `build/`。CBS 程序对象的新路径为 `build/CMakeFiles/CBS_objects.dir/ColliderBit/examples/*.cpp.o`；functor 对象仍位于 `CBS.dir`，因此 BUILD-01 的时间戳验证命令继续适用。

设计参考 CMake 官方的 [OBJECT 库使用要求](https://cmake.org/cmake/help/v3.16/command/target_link_libraries.html#linking-object-libraries)及 [LINK_LIBRARIES 属性](https://cmake.org/cmake/help/v3.16/prop_tgt/LINK_LIBRARIES.html)；复制链接属性用于保持程序对象的依赖库编译要求，后端完整构建依赖仍留在 executable 上。

新增 [standalone_objects.py](../cmake/tests/standalone_objects.py) 的 5 组脚本回归已通过：程序源码和最终链接输入分离；头文件准备依赖与后端完整依赖分离；编译属性及 OpenMP/MPI/Python/yaml-cpp 使用要求保留；数字开头名称和自定义/空导出宏、配置级 IPO；被排除或没有程序源码时不创建多余对象目标。测试在 `cmake -P` 模式捕获实际注册函数的调用，不创建真实 CMake 工程，也不执行编译器。BUILD-01 的 6 组回归再次通过。维护者当前 Unix Makefiles 构建日志及生成文件已确认对象目标分离、编译参数保留及完整链接；其他 generator 和平台尚未验证。

```sh
python3 cmake/tests/standalone_objects.py
python3 cmake/tests/code_generation.py
```

#### 维护者验收步骤

继续使用当前 `cbs-llvm` 配置和原来的 `build/`，无需清空目录或 `--fresh`。

1. 重新配置后只构建新对象目标，检查它能独立完成。程序对象迁移路径后，首次需要编译这 5 份源码；已有 ColliderBit/公共对象和外部安装树可继续复用。

   ```sh
   cd /Users/p.zhu/Gambit-Workshop/worktree/cbs-presets
   set -o pipefail
   cmake --preset cbs-llvm
   cmake --build build --target CBS_objects -j8 --verbose 2>&1 | tee /tmp/cbs-build02-objects.log
   ```

   预期只编译 `CBS_objects` 自身源码，以及必要的头文件/依赖准备；不编译 ColliderBit 分析对象、公共对象或等待 nulike/Rivet/Contur 的完整构建。查看 verbose 命令中的 C++ 标准、include、OpenMP、`CHECK_CUTFLOW` 和 `CBS_EXPORTS`，应与原 CBS 编译配置一致。

2. 构建完整 CBS，并确认随后无变化构建仍很快。

   ```sh
   cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-build02-full.log
   cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-build02-noop.log
   ```

   第一次应复用已完成的 `CBS_objects`，完成必要依赖并链接 CBS；第二次不应重新编译未变化的程序源码或 functor。再运行维护者已有的 CBS 单点配置，确认后端加载和运行结果保持。

3. 要观察真实并行重叠，在上述构建成功后只改时间戳，使一个程序文件和一个较慢的 ColliderBit 实现文件同时过期；不清理外部依赖。

   ```sh
   touch ColliderBit/examples/solo.cpp ColliderBit/src/ColliderBit_eventloop.cpp
   cmake --build build --target CBS -j8 --verbose 2>&1 | tee /tmp/cbs-build02-overlap.log
   ```

   预期 `solo.cpp` 的编译可以在 `Built target ColliderBit` 之前开始，最后链接仍等待两个目标完成。`touch` 只改变修改时间；实际收益以同配置、同并发的日志和耗时为准，不根据依赖图填写提速百分比。日志中的任务启动顺序受可用并发槽位影响。

4. 可直接检查 Unix Makefiles 的依赖图：

   ```sh
   rg 'CMakeFiles/CBS(_objects)?\.dir/all:' build/CMakeFiles/Makefile2
   ```

   `CBS_objects.dir/all` 应包含头文件准备和所需库使用依赖，不应包含 ColliderBit/公共对象库、nulike、rivet、contur 的完整目标；`CBS.dir/all` 则仍应包含 `CBS_objects`、模块/公共对象及启用的后端完整目标。某些 BOSS 头文件准备会依赖后端的下载/patch 步骤，这是必要依赖。

| 验收项 | 状态 | 维护者实测记录 |
| --- | --- | --- |
| 5 组 standalone 注册回归、6 组 BUILD-01 回归及结构检查 | 已通过 | 脚本/静态检查，未执行项目配置或编译 |
| 独立构建 CBS_objects | 已通过 | 2026-10-10 日志第 371–397 行：只编译 5 份 CBS 程序源码；未构建 ColliderBit/公共对象或 nulike/Rivet/Contur 完整目标 |
| 编译上下文与真实生成依赖图 | 已通过 | 当前 `CBS.dir` 与 `CBS_objects.dir/flags.make` 的 `CXX_DEFINES`、`CXX_INCLUDES`、`CXX_FLAGS` 完全相同；包含 `CBS_EXPORTS`、`CHECK_CUTFLOW`、C++17 和 OpenMP。`Makefile2` 中对象目标只等待 contrib、harvest、cbs_preload、yaml-cpp，最终 CBS 保留模块/公共对象和全部启用后端依赖 |
| 完整 CBS 链接 | 已通过 | 日志第 398–453 行：复用 5 份程序对象，无 C++ 编译，链接 CBS 一次并成功；当前 `CBS.dir/link.txt` 中每份新程序对象各出现一次 |
| 无变化主工程构建 | 已通过 | 日志第 454–508 行：无 C++ 编译、无 CBS 链接、无 harvest/functor 生成；外部包装步骤仍重跑，另记 BUILD-07 |
| CBS 单点运行 | 待执行 | 日志未包含运行输入和结果 |
| solo.cpp 与 ColliderBit 编译重叠及构建耗时 | 待执行 | 本次先独立构建 CBS_objects，再构建完整 CBS；日志未含双文件 touch、并行重叠或构建计时 |

#### 2026-10-10 构建日志记录

维护者提供的原始日志位于 `/Users/p.zhu/.codex/attachments/46897018-a28b-451e-bb96-3d8592c7c7e8/Pasted text.txt`，共 508 行；命令依次为 `cmake --preset cbs-llvm`、`cmake --build build --target CBS_objects -j8`、两次 `cmake --build build --target CBS -j8`。环境为 macOS arm64、Release、Unix Makefiles、LLVM 22.1.8、GNU Fortran 15.2.0、Python 3.13.13、ROOT 6.40.00、C++17、OpenMP 开启，backend 接口保留 12/52。配置阶段记录 7.0 秒，生成阶段 0.5 秒；未记录三个构建阶段的耗时。维护者反馈构建很快，不能据此量化并行收益。

本次没有 CMake/编译/链接错误。pybind11 的最低 CMake 兼容版本和 CMP0148 OLD 行为有弃用警告；Mathematica/libuuid、可选 scanner Python 包与 scanner 库缺失导致相应功能禁用，不影响本次 CBS 成功构建，不能把这些提示记为 CBS 构建失败。

无变化日志第 470–471 行仍执行 nulike/Rivet build，第 496–497 行显示 Rivet 安装分析数据，第 502–503 行执行 Contur configure/build。已只读核对当前生成规则：三个 `check-rebuild-*` 目标每次删除各自 build 标记，来自 `externals.cmake` 的 `enable_auto_rebuild`；Rivet 的完成标记是 Contur configure 的输入。外部 make 仍可自行判断对象是否需要重编译，因此该日志能确认步骤重复进入，不能确认这些库每次完整重编译。该问题登记为 BUILD-07，后续需要测量耗时并保留外部源码增量构建能力。

### BUILD-03 实施与验证

2026-10-10 基于 `957c81ecd9` 完成实现。维护者日志确认 ccache launcher 调用及完整 CBS 链接成功，随本轮提交合入。当前环境 ccache 版本为 4.13.6；Codex 仅执行脚本及只读检查，真实构建由维护者执行。

- 新增公共 `CompilerCache.cmake`，在 `project()` 导入标准 launcher 环境设置之后、任何原生 C/C++ target 创建之前初始化 launcher；适用于 GAMBIT、CBS 和其他 standalone。
- `GAMBIT_COMPILER_CACHE` 支持 AUTO（存在则使用）、CCACHE（缺失或版本命令失败时报错）、OFF（不自动注入），不接受未知值。首次 preset 配置默认 AUTO，首次普通配置默认 OFF；之后保留已缓存的策略。
- 逐语言尊重 `CMAKE_C_COMPILER_LAUNCHER` 和 `CMAKE_CXX_COMPILER_LAUNCHER`，包括空值和带参数的分号列表，不再叠加自动 ccache。OFF 同样保留用户显式 launcher；需用 `-U` 移除显式设置才能返回自动管理。
- 自动值只在当前配置过程的普通变量中设置；重新配置 OFF 无需清理缓存，AUTO 每次重新探测 PATH 上的工具，避免保留已删除的自动工具路径。真实编译器路径、标准和输出目录保持原有政策。
- 两类 preset 摘要都显示缓存策略、检测版本和 C/C++ launcher。Makefiles/Ninja 提供 launcher 机制，其他 generator 在 AUTO 下跳过、CCACHE 下报错；本项不代表工程已支持 Ninja。
- 原生 C/C++ target（含通过 add_subdirectory 加入的库）受益；不自动设置 Fortran launcher，不传播到独立配置的 ExternalProject 或 Make/Autotools 后端，不修改 ccache 全局设置。

[compiler_cache.py](../cmake/tests/compiler_cache.py) 的 7 组检查已通过：preset/普通配置默认值；显式及空 launcher 保留；缺失和损坏 ccache 的回退/拒绝；OFF 及重新配置不残留自动值；工具消失后的重探测与用户缓存保留；generator 和无效策略诊断；初始化与摘要接入位置。测试使用 `cmake -P`、隔离 PATH 和只支持 `--version` 的临时工具，不配置工程、不调用编译器。临时工具路径包含空格。CMake 初始化规则见 [官方 launcher 文档](https://cmake.org/cmake/help/v3.16/variable/CMAKE_LANG_COMPILER_LAUNCHER.html)。

#### 维护者验收步骤

继续使用当前 `cbs-llvm` 和 `build/`，无需清空、clean 或 `--fresh`。本项测试使用未改变内容的 `solo_cli.cpp`，不需要重编译整个工程。

```sh
cd /Users/p.zhu/Gambit-Workshop/worktree/cbs-presets
set -o pipefail
cmake --preset cbs-llvm -DGAMBIT_COMPILER_CACHE=CCACHE
ccache -s
touch ColliderBit/examples/solo_cli.cpp
cmake --build build --target CBS_objects -j8 --verbose 2>&1 | tee /tmp/cbs-build03-prime.log
ccache -s
touch ColliderBit/examples/solo_cli.cpp
cmake --build build --target CBS_objects -j8 --verbose 2>&1 | tee /tmp/cbs-build03-hit.log
ccache -s
cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-build03-full.log
cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-build03-noop.log
```

预期摘要显示 ccache 版本与两个 launcher 路径，verbose 编译命令先调用 ccache 再调用原编译器。第一次 touch 使源码通过 ccache 编译，已有缓存可能直接命中；第二次相同内容编译应增加 hit 数。记录三次统计快照，保持相同 flags、头文件和 CCACHE 环境；无变化构建不执行编译，因此不能单靠它证明 ccache 命中。统计来自 ccache 的现有缓存，其他并发编译可能影响计数；需要隔离测量时，可先在当前终端 `export CCACHE_DIR="$(mktemp -d /tmp/cbs-build03-cache.XXXXXX)"`，保持两次构建使用该目录，测试后 `unset CCACHE_DIR`。不用清空全局缓存或重置全局计数。

再验证自动值的关闭与恢复：

```sh
cmake --preset cbs-llvm -DGAMBIT_COMPILER_CACHE=OFF
touch ColliderBit/examples/solo_cli.cpp
cmake --build build --target CBS_objects -j8 --verbose 2>&1 | tee /tmp/cbs-build03-off.log
cmake --build build --target CBS -j8
cmake --preset cbs-llvm -DGAMBIT_COMPILER_CACHE=AUTO
```

没有显式 launcher 时，OFF 的编译命令应直接使用原编译器，摘要 launcher 为 none，随后 AUTO 恢复探测。若当前缓存或环境已有显式 launcher，OFF 会保留它；该行为是设计约定，移除对应设置后再测自动关闭。Rivet/nulike/Contur 仍可能重复进入包装步骤（BUILD-07），本项未修改其重建机制。

| 验收项 | 状态 | 记录 |
| --- | --- | --- |
| 7 组策略脚本及静态检查 | 已通过 | 无项目配置或编译；包含路径空格、缓存切换与缺失工具 |
| 当前环境 ccache 发现 | 只读检查通过 | `/opt/homebrew/bin/ccache --version`：4.13.6；不是实际构建命中证据 |
| 真实 C++ launcher 命令与完整 CBS 链接 | 已通过 | 维护者 195 行日志第 124–126 行：仅重编译 solo_cli.cpp，通过 `/opt/homebrew/bin/ccache /opt/homebrew/opt/llvm/bin/clang++`；第 194–195 行链接 CBS 成功。生成规则另确认 C、C++ 及 functor 均接入 launcher |
| 同文件内容相同编译的精确命中增量 | 待补齐记录 | 日志只含一个全局快照：509 次可缓存调用，64 次命中（58 direct、6 preprocessed），445 次 miss；不能从单快照判断本次调用是否命中或量化提速 |
| OFF → AUTO 切换及无变化构建 | 待执行 | 无需清空 build；关闭命令、摘要与增量日志 |
| 其他 preset/平台及显式自定义 launcher | 待执行 | 已有策略测试，真实目标生成及编译需对应环境验收 |

#### 2026-10-10 BUILD-03 构建日志

原始附件：`/Users/p.zhu/.codex/attachments/a4de0004-d198-4177-a868-b02c2059d464/Pasted text.txt`，共 195 行。维护者提供最后一次 touch、CBS_objects verbose 构建、ccache 统计及完整 CBS 构建。CBS_objects 只执行 solo_cli.cpp 的一条编译命令，C++17、OpenMP 和 CBS_EXPORTS 保留；完整构建无额外 C++ 编译，重新链接 libfirst.so 和 CBS 后成功。touch 后程序对象更新时间，因此随后 CBS 链接符合预期，本次不是无变化构建测试。

统计为全局历史快照（命中率 12.57%），包含此前其他调用，不能把该比例记为本轮源文件命中率。当前生成的 mkpath C、CBS_objects C++、CBS functor 编译规则均前缀 ccache；缓存策略为 CCACHE。未提供配置摘要、OFF/AUTO 切换、第二次无变化构建或单点运行日志。这些未测场景单独保留，不阻碍已通过真实构建的接入实现提交。

### BUILD-04 实施与验证

2026-10-10 基于 `0965735828` 完成实现，已提交为 `1d46bf0439`，状态为 **已合入**。维护者已验证当前 macOS LLVM 环境的 RestFrames OFF/ON 保留、恢复复用和完整 CBS 构建；其他场景按下方矩阵单独记录。

- 关闭 RestFrames（显式 OFF、缺少 ROOT 或未选择 ColliderBit）时，仅停用该包；未选择 ColliderBit 时，HepMC/YODA 按原条件停用。三个分支均不再删除源码/安装目录、ExternalProject 构建目录或步骤标记。
- 移除已无调用方的 `nuke_ditched_contrib_content`。三个包的 `add_contrib_clean_and_nuke` 移到启用条件外，保持 `clean-*`、`nuke-*`、`distclean`、`nuke-contrib` 和 `nuke-all` 的显式清理关联；这些目标不参与默认构建。
- 包启用条件、编译参数、正常构建依赖和 HepMC 的 pristine prepare_source/patch 流程保持；未启用的包不向当前模块添加 include/link 需求。更改编译器、参数、依赖或补丁时仍可能需要真正重建，BUILD-04 不承诺跨配置二进制复用。

新增 [contrib_retention.py](../cmake/tests/contrib_retention.py) 的 5 组检查已通过：RestFrames 显式 OFF；缺少 ROOT；无 ColliderBit（DarkBit、SpecBit、空 Bits）；重新启用；显式 nuke 仅删除指定临时包。测试运行实际包选择块及清理注册函数，用 `cmake -P` 捕获 target/ExternalProject 注册，禁止配置阶段执行外部命令。临时源码、库、对象和 8 类步骤标记的内容 hash/纳秒时间戳在停用与重新注册后相同；显式 nuke 测试只执行登记的 cmake -E 删除命令，范围限定于临时夹具，不执行 shell/make、工程配置、编译器或真实安装树清理。

```sh
python3 cmake/tests/contrib_retention.py
```

#### 维护者验收步骤

继续使用当前 `cbs-llvm`、相同编译器及 `build/`，不清空、clean 或 `--fresh`。下面 macOS 快照对应当前工作树实际存在的三份库和三个 install 标记。

1. 建立当前配置基线并保存外部安装状态：

   ```sh
   cd /Users/p.zhu/Gambit-Workshop/worktree/cbs-presets
   set -o pipefail
   cmake --preset cbs-llvm
   build04_files=(
     contrib/RestFrames-1.0.2/lib/libRestFrames.dylib
     contrib/HepMC3-3.2.5/local/lib/libHepMC3.dylib
     contrib/YODA-2.1.0/local/lib/libYODA.dylib
     build/restframes-prefix/src/restframes-stamp/restframes-install
     build/hepmc-prefix/src/hepmc-stamp/hepmc-install
     build/yoda-prefix/src/yoda-stamp/yoda-install
   )
   stat -f '%m %N' "${build04_files[@]}" > /tmp/cbs-build04-before.txt
   ```

2. 关闭 RestFrames，确认现有库和安装标记仍在、时间戳不变，再恢复 preset 默认 ON：

   ```sh
   cmake --preset cbs-llvm -DWITH_RESTFRAMES=OFF
   stat -f '%m %N' "${build04_files[@]}" > /tmp/cbs-build04-restframes-off.txt
   diff -u /tmp/cbs-build04-before.txt /tmp/cbs-build04-restframes-off.txt
   cmake --build build --target help | rg '(clean|nuke)-(restframes|hepmc|yoda)'
   cmake --preset cbs-llvm
   stat -f '%m %N' "${build04_files[@]}" > /tmp/cbs-build04-restframes-on.txt
   diff -u /tmp/cbs-build04-before.txt /tmp/cbs-build04-restframes-on.txt
   ```

   预期两个 diff 都无输出；关闭状态仍能列出三包的显式 clean/nuke target。仅停用或启用功能不应删除已有依赖。

3. 需要覆盖 HepMC/YODA 的自动停用分支时，临时只选 DarkBit 并关闭 CBS 配置入口，完成快照后立即恢复。同一工具链、同一个 preset 和 build/，只作配置验证：

   ```sh
   cmake --preset cbs-llvm -DBits=DarkBit -DCBS_BUILD_PRESET:STRING= -DWITH_ONNXRUNTIME=OFF
   stat -f '%m %N' "${build04_files[@]}" > /tmp/cbs-build04-no-colliderbit.txt
   diff -u /tmp/cbs-build04-before.txt /tmp/cbs-build04-no-colliderbit.txt
   cmake --build build --target help | rg '(clean|nuke)-(restframes|hepmc|yoda)'
   cmake --preset cbs-llvm
   stat -f '%m %N' "${build04_files[@]}" > /tmp/cbs-build04-restored.txt
   diff -u /tmp/cbs-build04-before.txt /tmp/cbs-build04-restored.txt
   ```

   Bits 不含 ColliderBit 时，HepMC/YODA 会按工程规则关闭。显式清空 CBS_BUILD_PRESET 是为了让临时配置不要求创建 CBS target；恢复 `cbs-llvm` 会恢复 ColliderBit/CBS 和默认能力开关。预期所有 diff 无输出。若仅做最小验收，可先执行第 1、2、4 步。

4. 在恢复当前配置后构建三份外部依赖，再构建完整 CBS：

   ```sh
   cmake --build build --target restframes hepmc yoda -j8 2>&1 | tee /tmp/cbs-build04-reuse.log
   cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-build04-full.log
   ```

   保持包输入不变时，外部日志应复用原安装，不因本次 OFF/ON 而重新下载、prepare_source、patch、configure 或编译这些包。主工程可能因能力配置/生成头文件变化而重编译，需与外部库的无效重建分开记录。Rivet/nulike/Contur 的重复包装步骤仍属 BUILD-07。

`nuke-restframes`、`nuke-hepmc`、`nuke-yoda` 是主动删除对应源码/安装树及外部构建目录的命令，会导致之后重新准备依赖；本项复用验收无需对真实安装树执行 nuke，删除语义已在临时夹具检查。

| 验收项 | 状态 | 记录 |
| --- | --- | --- |
| 5 组保留/清理夹具检查 | 已通过 | 内容、时间戳、启用/排除状态、cleanup target 关联及限定清理范围；不配置或编译工程 |
| 当前工作树验收路径 | 只读检查通过 | 三份 macOS 动态库和三个 install 标记均存在 |
| RestFrames OFF → ON 安装保留、外部复用与 CBS 构建 | 已通过 | 1125 行维护者日志：OFF 后 ls 成功；恢复后 restframes 目标没有 ExternalProject 下载/配置/编译步骤，完整 CBS 构建成功。只读核对当前库及 install 标记仍为此前安装时间 |
| 恢复配置后的无变化主工程构建 | 已通过 | 维护者随后在聊天提供 CBS -j8 日志：无 C/C++/Fortran 对象编译、无链接及 harvest/functor 生成命令，最终 Built target CBS；nulike/Rivet/Contur 包装步骤仍进入，属 BUILD-07 |
| 三包内容/时间戳对照及停用时 cleanup target help | 待补齐记录 | 本次日志没有保存切换前后快照，也没有 target help；不能据此确认完整目录逐文件不变 |
| 移除 ColliderBit → 恢复后的 HepMC/YODA 保留 | 待执行 | 临时配置快照、target help 和恢复日志 |
| 其他平台 | 待执行 | 用平台对应库名/时间戳工具验证相同约定 |


#### 2026-10-10 BUILD-04 构建日志

原始附件：`/Users/p.zhu/.codex/attachments/7cbd744c-fad5-4d67-ae78-e213c8a938f7/Pasted text.txt`，共 1125 行。命令顺序为 RestFrames OFF 配置、检查安装库、恢复 `cbs-llvm` 配置、构建 restframes、构建 CBS，均使用同一 build 和 `-j8`。两次配置分别用时 8.6/6.0 秒，生成分别 0.6/0.5 秒；没有构建总耗时或 ccache 增量统计。

- 第 139–140 行确认关闭 RestFrames，第 377 行 ls 输出已安装动态库路径；第 509 行确认恢复启用。第 747–750 行只重编译/链接 GAMBIT preload，然后完成 restframes；没有 RestFrames 下载、prepare_source、patch、configure、build 或 install 步骤。配置摘要中的“will be downloaded and installed”是通用提示，不能作为实际重新下载证据。
- 当前工作树只读检查中，RestFrames 动态库及 install 标记时间仍为 20:43:10，早于本次恢复配置头文件的 23:27:04 和目标 flags.make 的 23:27:08。该证据支持原安装复用，不能代替未提供的完整目录前后 hash/时间戳快照。
- 第 1124–1125 行完整 CBS 链接成功，无构建错误。两个构建合计出现 301 条 C++ 对象构建、1 条 C 对象构建和 2 条 Fortran 对象构建；这次存在大范围主工程重编译，不能记成无变化构建。已启用 ccache，但日志没有命中差值，构建条数不等于实际编译器工作量。
- 触发路径包括 `cmake_variables.hpp` 的 EXCLUDE_RESTFRAMES/RESTFRAMES_INCLUDE 内容改变，以及目录级 RestFrames include 移除后恢复。生成规则确认 Models 和 FastJet Contrib 等对象依赖各自 flags.make；恢复后的 flags.make 含 RestFrames include，mtime 与本次配置一致，随后对象更新。即使最终配置回到原值，Make 仍会因中间变化留下的新时间戳重新调度对象。这与外部 RestFrames 的复用是不同问题，收窄无关目标的配置影响记为 BUILD-08。
- 第 785、787 行出现 Fortran deployment target 警告：本次新编对象标记为 macOS 28.0，链接目标为 27.0。生成 Fortran_FLAGS 没有 minimum 参数，link.txt 则包含公共 `-mmacosx-version-min=27.0`；不是单纯旧对象遗留。补齐编译/链接的一致性归入 CFG-05；本次链接成功，但日志不证明产物在最低目标系统上的兼容性。
- pybind11 的旧 CMake 策略弃用、FastJet Contrib 的未使用参数/变量警告未阻止构建；若干可选 Python scanner 模块和 Mathematica WSTP 依赖缺失，仅影响相应可选功能。nulike/Rivet/Contur 包装步骤再次进入，仍按 BUILD-07 跟踪。

维护者随后在本聊天补充执行 `cmake --build build --target CBS -j8` 的日志：没有 C/C++/Fortran 对象编译或任何链接命令，也没有 harvest/functor 生成命令，最终 `Built target CBS`。因此恢复配置后的主工程无变化构建已通过；RestFrames/HepMC/YODA 仅显示目标完成，没有外部重建步骤。nulike/Rivet 仍执行 build，Rivet 仍安装分析数据，Contur 仍执行 configure/build，这些包装步骤的重复开销继续归入 BUILD-07。该日志未提供耗时或 ccache 增量，不能量化提速，也不补足其他未执行的开关/平台场景。

### BUILD-05 实施与验证

2026-10-11 基于 `1d46bf0439` 实现。当前 macOS LLVM 的首次迁移和相同配置后复用已由维护者验收，已提交为 `09929f07fb`，状态为 **已合入**。

- 两包的库搜索不再信任旧 cache/normal 路径，只搜索当前安装 prefix，并检查实际存在、非目录。FastJet 检查 fastjet-config 和所需插件头文件；Contrib 检查公共头文件及主工程所编译的六份 Nsubjettiness 源码。
- 构建身份记录包版本/归档校验值、C/C++/Fortran 编译器路径、版本、realpath 和文件时间戳、标准、系统/处理器/架构、SDK/deployment、实际包编译 flags、configure 选项。Contrib 额外关联 FastJet 身份和 OpenMP 库路径。自动 ccache launcher 不用于这些外部 Make 包，也不计入其身份。
- 配置只写内容稳定的期望输入和步骤请求，清除被拒绝包的 prepare/patch/configure/build/install/complete/身份完成标记；安装树和源码保留到实际构建。缺少或无效的缓存归档还使 download 标记失效。FastJet 重建要求 Contrib 重建；Contrib 单独失效时可复用匹配的 FastJet。
- prepare_source 位于 update 之后、patch 之前；先校验并在临时目录解包，然后替换包树，确保编译器/flags 改变后没有旧 Autotools 对象残留。FastJet 的 local prefix 包含 Contrib 安装，FastJet 重建会替换这个 prefix，所以两包同时登记重建。校验或解包失败时不替换原包树。
- record_identity 位于 install 之后，再次验证文件/库，成功后才写安装身份。FastJet build 自身执行 make install，其 INSTALL_COMMAND 为空，record 仍位于该成功步骤之后。普通后续构建无需重新配置也应跳过这些步骤；相同配置后续转为直接复用目标。复用状态同样保留显式 clean/nuke 入口。
- 当前旧 FastJet Makefile 记录 macOS 26.5 SDK/minimum，而此前主工程配置使用 27.0；旧逻辑仍直接复用。这是增加身份检查的实际例子。旧安装没有成功构建记录，无法仅凭文件名确认一致，因此首次需要重建两包；复用原缓存归档不等于重新下载。该首次迁移不能作为无变化性能基准。

[contrib_build_identity.py](../cmake/tests/contrib_build_identity.py) 的 11 组检查通过：旧安装迁移且配置不删源码/安装；匹配记录复用且输入/安装/标记时间戳稳定；缓存外部路径和已删除 FastJet 库；缺失 Contrib 库/头文件/六份 native 源码及 fastjet-config；标准、编译器、flags、架构、SDK/minimum 和处理器变化；Contrib OpenMP/链接参数单独失效；真实临时归档恢复干净源码并清除旧对象；坏归档/不完整安装拒绝写成功记录；目录范围与 macOS 非存在子路径 realpath；归档缺失/损坏使下载步骤失效；停用 ColliderBit 保留安装与标记。执行的是实际包选择块、捕获的 ExternalProject 注册与临时 cmake -P 解包/记录，不执行项目 configure、编译器、make 或下载。另复查 BUILD-04 的五组保留检查，均通过。

#### 维护者最小验收

继续当前 `cbs-llvm` 和共享 build，不清空、不 clean、不 --fresh。先构建外部两包，再构建 CBS：

```sh
cd /Users/p.zhu/Gambit-Workshop/worktree/cbs-presets
set -o pipefail
cmake --preset cbs-llvm
cmake --build build --target fjcontrib -j8 2>&1 | tee /tmp/cbs-build05-deps.log
cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-build05-first.log
```

第一次配置应提示 `no recorded build identity`；fjcontrib 依赖 fastjet，会按顺序构建、安装并记录。日志应有各自 prepare_source/record_identity，最后两个记录存在：

```sh
build05_files=(
  contrib/fastjet-3.5.1/local/.gambit-fastjet-build-identity
  contrib/fastjet-3.5.1/local/.gambit-fjcontrib-build-identity
  contrib/fastjet-3.5.1/local/lib/libfastjet.dylib
  contrib/fastjet-3.5.1/local/lib/libfastjetcontribfragile.dylib
)
stat -f '%m %N' "${build05_files[@]}" > /tmp/cbs-build05-before.txt
cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-build05-noop.log
cmake --preset cbs-llvm
cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-build05-reconfigured.log
stat -f '%m %N' "${build05_files[@]}" > /tmp/cbs-build05-after.txt
diff -u /tmp/cbs-build05-before.txt /tmp/cbs-build05-after.txt
```

预期后续配置均显示两包 `build identity matches`；两个后续 CBS 构建不进入 FastJet/Contrib 的准备、配置、编译、安装或身份重写，也不重编主工程对象/链接 CBS；diff 无输出。Rivet/nulike/Contur 的包装步骤仍属 BUILD-07，首次依赖重建导致的下游更新需单独记录。保存日志即可，无需删除真实库或切换 C++ 标准；缺失文件和配置失效已在临时夹具覆盖。

| 验收项 | 状态 | 记录 |
| --- | --- | --- |
| 11 组身份/复用/恢复夹具及 BUILD-04 五组保留检查 | 已通过 | cmake -P 临时文件与真实注册块；未配置或编译工程 |
| 当前旧安装和缓存归档 | 只读检查通过 | 旧 Makefile 的 SDK 为 26.5；当前两份归档都存在，未修改安装 |
| 真实首次迁移重建、安装身份及完整 CBS | 当前环境通过 | 日志确认 pristine 准备、顺序构建及成功安装后记录；完整 CBS 链接成功；只读检查两包安装记录均与当前期望输入一致 |
| 相同配置后复用 | 当前环境通过 | 第二次配置两包均显示 build identity matches；其后 CBS 无 FastJet/Contrib 外部步骤、原生对象编译或链接 |
| 直接无配置重复构建及安装时间戳对照 | 待补齐 | 本次日志未包含该独立场景或 before/after 时间戳，不据此填写通过 |
| 其他平台、工具链切换及单点运行 | 待执行 | 签名失效检查不代替对应平台实际构建/运行与二进制兼容性验收 |

#### 维护者构建记录（2026-10-11）

日志为 `/Users/p.zhu/.codex/attachments/0b2e7abd-f01a-44ef-9c0b-88bb1b12f757/Pasted text.txt`（2067 行）。环境为 `cbs-llvm`、LLVM 22.1.8、ROOT 6.40.00、C++17、SDK/minimum 27.0、ccache 4.13.6，并发为 `-j8`。

- 初次配置第 151–152 行拒绝没有记录的 FastJet，并登记 Contrib 随之重建。第 376 行和 1118 行准备干净源码；第 1115 行在 FastJet 安装之后记录，第 1191 行在 Contrib 安装之后记录，两包目标成功。
- 首次完整 CBS 构建包含 167 条原生对象编译记录和一次 CBS 链接，第 1643 行成功。替换 FastJet 源码及安装头文件后的首次主工程重编属于本轮迁移成本，不作为无变化性能基准。
- 第二次配置第 1788–1789 行两包身份匹配，配置/生成耗时为 6.5/0.5 秒。第 2013–2067 行 CBS 构建没有对象编译、链接或两包外部步骤，最终成功。
- 构建后只读检查两份安装记录与 `build/{package}-prefix/tmp/{package}-identity.txt` 字节一致，均记录当前 SDK/minimum 27.0。时间戳前后对照、未经配置的直接重复构建、总构建耗时及 ccache 命中增量未提供。
- pybind11 的 CMake 弃用提示、FastJet/Contrib 未使用变量/参数及旧链接选项警告未阻止构建。最后一次仍进入 nulike/Rivet build、Rivet 数据安装及 Contur configure/build，继续按 BUILD-07 处理。

### BUILD-07 实施与验证

2026-10-11 基于 `09929f07fb` 实现；当前 macOS LLVM 的首次记录、直接重复构建及相同配置后复用已由维护者验收，已提交为 `0c3ea3e566`，状态为 **已合入**。台账将 Ninja 适配（BUILD-06）列为 P3 后续评估，本轮先处理已有实际日志证据的 P2 重复步骤。

- 公共 `enable_auto_rebuild` 支持可选的输入、上游文件、构建产物和配置产物声明。当前只为 nulike 1.0.9、Rivet 4.1.0、Contur 3.0.0 接入；其余版本/后端/scanner 仍执行原来的自动 make 检查，逐包审计后再扩展。
- 每次请求包目标时，以项目已有的 Python 3 扫描声明的输入：记录路径/realpath、纳秒 mtime、大小和 SHA256；清单增删、touch 和内容变化均可使 build 标记失效。输入身份还包含真实 ExternalProject configure/build/install 参数、编译器版本/路径/文件时间戳及检查脚本版本。生成的对象、libtool 文件、`.libs/.deps`、内部 build 和 Python cache 不进入源码状态。
- 无成功记录或状态不同，只清除该包 build 标记；缺少声明的配置产物时额外清除 configure。成功 install 之后的 `record_source_state` 再检查关键产物，原子记录状态；失败或不完整安装不覆盖旧成功记录。相同状态不改写 JSON。内部 make 决定具体对象重编译范围，本轮不改变 backend 的编译器/ABI 迁移及 flags 变更后对象清理政策。
- nulike 跟踪 Makefile、src/include/contrib，检查真实 `lib/libnulike.so`。Rivet 跟踪源码、公共头、Python 和分析数据、必要共享头及 FastJet/YODA/HepMC 的安装头/库；检查实际主库、三个分析插件及启用时的 Python 产品，支持 site-packages/dist-packages。Contur 跟踪 DB 的 Makefile/SQL，检查 analyses.db 和 `init_by_GAMBIT.py`。该声明覆盖当前构建入口，并非任意 C/C++ 外部头文件的完整依赖扫描。
- Rivet/Contur 的检查 target 等待 ExternalProject 已声明的上游依赖后再扫描，保留并行构建的顺序。已有下载、补丁、BOSS、pristine Rivet 准备、显式 clean/nuke 及 CBS 对象依赖不变。无变化时不再由删除 build 标记引发 Rivet 数据安装/库复制，也不再因此更新完成标记并级联到 Contur configure。

[external_auto_rebuild.py](../cmake/tests/external_auto_rebuild.py) 的 11 组检查通过：首次建立记录且只删自身 build；无变化输入/产物/标记和 JSON 时间戳稳定；保持 mtime/大小的内容编辑及纳秒 touch；源码增删且无需重新配置；生成对象/cache 排除；库或配置产物缺失的分阶段失效；失败重试及不完整安装不覆盖成功记录；编译命令及已安装依赖改变；损坏记录/空输入拒绝；Python 安装目录通配；实际三包声明、其他 nulike 版本原策略、上游顺序、原 pristine/BOSS 注册和 pyext OFF。执行的是临时文件、Python 检查和捕获注册的 `cmake -P`；没有配置或编译工程。

另对当前真实安装做了只读扫描：nulike 114、Rivet 8772、Contur 3 个输入，两次连续读取状态相同，当前所声明的构建/配置产物均存在。一次输入扫描约为 0.025/1.593/0.003 秒；这些是局部检查脚本的读取时间，不是实际 CBS 构建耗时或已验收的提速结果。

#### 维护者验收

继续当前 preset 和共享 build，不清空、不 clean、不 --fresh。第一次预计三包各进入一次包装 build 并出现 `Recording successful ... source state`；Rivet 此次完成标记更新可导致 Contur 一次 configure，这属于建立记录的成本。

```sh
cd /Users/p.zhu/Gambit-Workshop/worktree/cbs-presets
set -o pipefail
cmake --preset cbs-llvm
cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-build07-first.log

build07_files=(
  build/nulike_1.0.9-prefix/src/nulike_1.0.9-stamp/nulike_1.0.9-build
  build/rivet_4.1.0-prefix/src/rivet_4.1.0-stamp/rivet_4.1.0-build
  build/rivet_4.1.0-prefix/src/rivet_4.1.0-stamp/rivet_4.1.0-done
  build/contur_3.0.0-prefix/src/contur_3.0.0-stamp/contur_3.0.0-configure
  build/contur_3.0.0-prefix/src/contur_3.0.0-stamp/contur_3.0.0-build
  build/nulike_1.0.9-prefix/tmp/nulike_1.0.9-source-state.json
  build/rivet_4.1.0-prefix/tmp/rivet_4.1.0-source-state.json
  build/contur_3.0.0-prefix/tmp/contur_3.0.0-source-state.json
  Backends/installed/nulike/1.0.9/lib/libnulike.so
  Backends/installed/rivet/4.1.0/local/lib/libRivet.so
  Backends/installed/contur/3.0.0/data/DB/analyses.db
)
stat -f '%m %N' "${build07_files[@]}" > /tmp/cbs-build07-before.txt
cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-build07-noop.log
cmake --preset cbs-llvm
cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-build07-reconfigured.log
stat -f '%m %N' "${build07_files[@]}" > /tmp/cbs-build07-after.txt
diff -u /tmp/cbs-build07-before.txt /tmp/cbs-build07-after.txt
```

后两次 CBS 都应成功，三个 `check-rebuild-*` 仍显示目标完成，但不应有这三包 configure/build/install/record_source_state 命令、Rivet `Installing analysis data files...`，或无变化主工程的对象编译/链接；diff 无输出。每次仍有输入扫描成本，需结合实际日志计时判断收益。

再检查外部源码 touch 的自动增量入口（不重新配置）：

```sh
touch Backends/installed/nulike/1.0.9/src/utils.f
cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-build07-touch.log
cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-build07-touch-noop.log
```

第一次应提示 nulike source inputs changed，进入其增量 build 和成功记录；第二次不再进入。无需删除真实库、修改源码内容或重建全部依赖。

| 验收项 | 状态 | 范围 |
| --- | --- | --- |
| 11 组临时检查与实际声明捕获 | 已通过 | 源码变化/缺产物/失败/目录与并行顺序；不运行 make、编译器或项目 configure |
| 当前安装产物和只读输入扫描 | 当前环境通过 | 所声明文件存在、连续扫描稳定；不代替工程验收 |
| 首次建立成功记录及完整 CBS | 当前环境通过 | 三包成功 build/install 后记录；三次 CBS 都成功；首次没有主工程对象编译或链接 |
| 直接重复构建及相同配置后复用 | 当前环境通过 | 两次后续日志均无三包 configure/build/install/record、Rivet 数据安装、主工程对象编译或链接 |
| 标记、JSON、库/DB 时间戳前后对照 | 待补齐 | 日志未包含 before/after stat 与 diff，不据此填写时间戳稳定或量化提速 |
| 外部源码 touch 后构建及其后无变化构建 | 待执行 | 不重新配置也能进入对应包，成功后下一次再次跳过 |
| 其他平台、pyext OFF 和真实失败/缺产物恢复 | 待执行 | 临时夹具不代替平台构建；不要求破坏现有安装来验证 |

#### 维护者构建记录（2026-10-11）

日志为 `/Users/p.zhu/.codex/attachments/9d5b19bb-ae94-454e-acc6-5e9f7cb6a434/Pasted text.txt`（889 行）。环境为当前 `cbs-llvm`、LLVM 22.1.8、Python 3.13.13、C++17、SDK/minimum 27.0、ccache 4.13.6，三次构建均为 CBS `-j8`。

- 第一次配置继续复用身份匹配的 FastJet/Contrib；nulike/Rivet/Contur 各因没有成功源码记录进入一次 build，并在第 403、423、432 行成功记录。Rivet 本次完成标记变化导致 Contur 一次 configure，与建立记录阶段的预期一致。第 436 行 CBS 成功，没有主工程对象编译或链接。
- 第 437–478 行直接重复构建，第 848–889 行相同配置后的构建，都没有三包 configure/build/install/record 命令、Rivet 数据安装、对象编译或链接；两次最终均 `Built target CBS`。轻量 check-rebuild 目标仍正常运行。
- 构建后只读重新扫描，三份成功记录与当前输入状态一致，也与生成的 check-rebuild 命令身份一致，声明的构建/配置产物均存在。当前输入数为 nulike 114、Rivet 9142、Contur 3；该数字与此前安装在首次记录前的读取不同，当前记录及连续后续构建均匹配。
- 第二次配置/生成为 5.9/0.4 秒。日志没有总构建耗时、前后时间戳对照或源码 touch 场景，不能量化提速，也不补足这些未执行的验收项。配置中的可选依赖提示及 pybind11 旧 CMake 策略弃用未阻止构建。

### BUILD-08 RestFrames 实施与验证

2026-10-11 基于 `0c3ea3e566` 实现第一阶段。补齐 preload 使用者后，维护者已验证当前 macOS LLVM 的首次迁移、恢复 ON 六个必要对象及最终无变化构建，RestFrames 阶段已提交为 `eb03406a7c`；BUILD-08 总体状态为 **部分完成**，其他可选依赖和 RPATH 范围仍待处理。

- 去掉 RestFrames 的目录级 `include_directories`，改由公共 `add_gambit_library` 仅向 ColliderBit 对象库添加 PRIVATE 路径。该路径在 ON/OFF、缺少 ROOT 或未启用 ColliderBit 时均保持同一值；安装尚不存在时也允许登记普通 include 路径。功能是否可用由开关和依赖条件决定，不由路径存在与否决定。
- 从通用 `cmake_variables.hpp.in` 移出 `EXCLUDE_RESTFRAMES` 和 `RESTFRAMES_INCLUDE`，由 `preprocessor.cmake` 生成专用 `restframes_variables.hpp`。四个分析（2017_03_RJR、2018_05_RJR、2018_12_RJR、2018_16）、`AnalysisContainer.cpp` 和 `gambit_preload.cpp` 显式包含专用头，放在原有 ROOT/RestFrames 判断之前；分析算法和注册条件保持原样。Preload 使用同一专用头控制原有的 `CPLUS_INCLUDE_PATH` 设置，不需要 RestFrames 编译 include 路径。
- 专用头不经通用头或公共 Bit 头间接包含。以后新增或本地维护的 RestFrames 分析，需要显式包含 `gambit/cmake/restframes_variables.hpp` 再判断 `EXCLUDE_RESTFRAMES`；判断 ROOT 仍使用通用头。公共接口若将来暴露 RestFrames 类型，需要重新评估 PRIVATE 范围。
- 现有 RestFrames 下载、补丁、安装、contrib 构建顺序、链接参数及显式清理入口保留。BUILD-04 的安装保留机制继续适用；本轮没有改变其他可选依赖的配置宏，也没有收窄全局 RPATH。

[restframes_scope.py](../cmake/tests/restframes_scope.py) 的 7 组脚本检查通过：真实包选择及 library helper 的 private/目标范围；OFF 和依赖不满足时路径稳定且不注册外部包；未提供包元数据时 helper 不添加路径；ON/OFF/ON 只改变专用头；相同内容保留两头的纳秒时间戳且其他配置仍正常更新；缺少 ROOT 时两个 feature 正确关闭；全仓库已跟踪 C/C++ 源码及本地新增 ColliderBit 实现的使用者在宏使用前包含专用头，且公共头不传播它。扩大后的检查已在未修复源码上准确失败于 preload 的缺失 include；ON/OFF 临时生成头同时检查 include 路径宏。测试捕获目标和依赖探测，使用实际 `configure_file` 写临时头文件，不执行工程配置、编译器或 make。实际 Make 对象构建范围仍由维护者验证。 原有五组 contrib 保留检查和五组 standalone 对象检查也通过，本轮共 17 组；`git diff --check` 通过。

#### 维护者验收

继续 `cbs-llvm` 和现有 `build`，不要清空、clean 或 --fresh；保持 ROOT、编译器、标准和其他开关不变。**首次迁移可能重编译很多对象**：通用配置头删除旧字段，同时无关目标移除旧 RestFrames include，这是一次性更新，不作为 OFF/ON 性能验收。

```sh
cd /Users/p.zhu/Gambit-Workshop/worktree/cbs-presets
set -o pipefail
cmake --preset cbs-llvm -DWITH_RESTFRAMES=ON
cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-build08-first.log
```

首次成功后，可用下列函数记录通用头与九个代表目标的编译 flags 的内容和纳秒 mtime；其中包括 ColliderBit 自身，确认其 private 路径在切换时也保持稳定：

```sh
cbs_build08_snapshot() {
  python3 - <<'PY'
from pathlib import Path
import hashlib
names = {'ColliderBit.dir', 'Models.dir', 'Utils.dir', 'Backends.dir',
         'CBS_objects.dir', 'fjcontrib_nsubjettiness.dir', 'mkpath.dir', 'fortran.dir', 'gambit_preload.dir'}
paths = [Path('cmake/include/gambit/cmake/cmake_variables.hpp')]
paths += sorted(p for p in Path('build').rglob('flags.make') if p.parent.name in names)
assert len(paths) == 10, '当前 Unix Makefiles 构建应包含上述九个目标'
for p in paths:
    print(hashlib.sha256(p.read_bytes()).hexdigest(), p.stat().st_mtime_ns, p)
PY
}
cbs_build08_snapshot > /tmp/cbs-build08-before.txt
```

关闭 RestFrames 并实际构建，再恢复并实际构建；不要只切换配置后才构建，否则无法分别验证关闭和恢复的注册/链接：

```sh
cmake --preset cbs-llvm -DWITH_RESTFRAMES=OFF
cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-build08-off.log
cbs_build08_snapshot > /tmp/cbs-build08-off.txt
diff -u /tmp/cbs-build08-before.txt /tmp/cbs-build08-off.txt

cmake --preset cbs-llvm -DWITH_RESTFRAMES=ON
cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-build08-on.log
cbs_build08_snapshot > /tmp/cbs-build08-on.txt
diff -u /tmp/cbs-build08-before.txt /tmp/cbs-build08-on.txt

cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-build08-noop.log
```

两次 diff 应无输出。OFF 和 ON 日志中的对象编译应仅涉及上述四个 RestFrames 分析、注册容器和 gambit_preload；Models、Utils、Backends、CBS_objects、FastJet Contrib、mkpath 和 Fortran 应跳过对象编译。CBS 需要重新链接，部分共享库可能因全局 runtime library path 改变而重新链接，需与对象重编译区分。恢复 ON 应继续复用未改变输入的 RestFrames 安装；三包 backend 检查保持 BUILD-07 的无变化跳过行为。最后重复构建应没有对象编译、链接、harvest/functor 生成或这些外部包的 configure/build/install 步骤。`Built target ...` 或轻量 `check-rebuild-*` 出现正常。

若实际范围仍较大，保留日志和两次 diff，按具体对象依赖继续调查；不同开关/编译器/ROOT 条件变化不作为这一项的验收。无需删除现有安装验证缺失场景。

| 验收项 | 状态 | 记录 |
| --- | --- | --- |
| 七组范围、生成头及注册检查 | 已通过 | 2026-10-11；临时 `cmake -P`，没有工程配置或编译 |
| 首次迁移及完整 CBS 构建 | 当前环境通过 | 补齐 preload 后，OFF 构建完成 288 个 C++ 对象的一次性迁移，CBS 成功；恢复 ON 和直接重复构建也成功 |
| 恢复 ON 的对象范围及安装复用 | 当前环境通过 | 仅四个分析、注册容器、preload 共六个对象，六次必要链接；没有 RestFrames 或三包 backend 的外部步骤 |
| 迁移后独立 OFF 的对象范围 | 待补齐 | 本次 OFF 包含首次迁移，不能当作纯开关范围验证；不阻止提交已验收的 RestFrames 阶段 |
| 公共头/flags 的真实前后快照 | 待补齐 | 日志没有 stat/hash/diff；脚本夹具稳定及当前生成依赖的只读确认分别记录 |
| 恢复后的无变化构建 | 当前环境通过 | 日志第 1141–1182 行，零对象编译、零链接、零外部步骤或代码生成 |
| 其他平台和其他可选依赖 | 待执行 | 不由临时脚本检查推定通过 |

#### 2026-10-11 首次 OFF/ON 日志与修复

附件 `/Users/p.zhu/.codex/attachments/097aa5f9-fb63-4761-962b-22d5984f35bd/Pasted text.txt` 包含 OFF、ON 和直接重复构建。第 406、805、833 行均报 `contrib/preload/gambit_preload.cpp:157` 使用未声明的 `RESTFRAMES_INCLUDE`，三次构建均失败，没有完整 CBS 成功记录。此前附件 `d9aff82b-f67f-41c4-b976-3b899b2b3a77` 与 BUILD-07 附件字节一致，不能用于本项验收。

原因是首次源码搜索排除了整个 contrib，原七组检查又只检查 ColliderBit 使用者，漏掉 preload 中由 `EXCLUDE_RESTFRAMES` 控制的环境变量设置。已给 preload 显式加入专用头，保留其原功能；检查改为扫描全仓库已跟踪 C/C++ 源码（包含 contrib），并覆盖本地新增 ColliderBit 实现。更新预期为四个分析、注册容器与 preload 共六个对象；preload 在 ON/OFF 时确有功能变化，属于必要重编译。公共配置头和无关目标的 compile flags 仍应稳定。

日志中的共享库重新链接符合 RPATH 切换预期；Fortran 对象 macOS minimum 28.0、链接 27.0 的警告沿用 CFG-05 跟踪，不是此次阻断构建的错误。因构建提前失败，不能验证其余对象范围、安装复用或最终无变化行为。该次修复当时仅完成脚本/源码检查；后续复测结果见下一节，历史失败不计为通过。

#### 2026-10-11 修复后复测

附件 `/Users/p.zhu/.codex/attachments/95fc74b3-ed5d-4c3e-a4f2-1f67983ab8e8/Pasted text.txt` 共 1182 行，命令为同一 `cbs-llvm`、共享 build、CBS `-j8` 的 OFF 构建、ON 构建及直接重复构建。三次均成功，未见错误；配置环境仍为 LLVM 22.1.8、Python 3.13.13、ROOT 6.40.00、C++17 和 SDK/minimum 27.0。

- OFF 阶段第 375–714 行完成首次迁移：288 个 C++ 对象和 6 次链接，最终 CBS 成功。此前 preload 失败阻止了这些下游对象完成迁移；本次包含公共头删除旧字段及旧目录级 include 移除的成本，不能把这 288 个对象计为正常开关的重编译范围。无外部 configure/build/install/record，也没有 harvest/functor 生成命令。
- 恢复 ON 后，第 1094、1127–1131 行恰好编译六个对象：gambit_preload、四个 RestFrames 分析和 AnalysisContainer。Models、Utils、Backends、CBS_objects、其他 ColliderBit 分析等均跳过对象编译。执行五个共享库及 CBS 的六次必要链接；RestFrames 显示目标完成，没有外部步骤，三包 backend 检查也不进入包装步骤。第 1140 行 CBS 成功。
- 第 1141–1182 行直接重复构建零对象编译、零链接、零外部步骤和代码生成，最终 CBS 成功。`Built target` 与轻量 check-rebuild 输出正常。
- 只读检查当前生成文件：仅 ColliderBit 的原生 flags.make 含 RestFrames include；专用头已启用 RestFrames，公共头没有这两个宏；真实 `.o.d` 中引用专用头的恰为上述六个对象。现有 RestFrames 动态库和 install 标记仍在。此检查确认当前依赖范围，不替代未提供的前后时间戳快照。
- OFF/ON 配置分别为 6.1/6.4 秒，生成均为 0.5 秒；日志没有总构建耗时或 ccache 增量，不填写量化提速。pybind11 弃用与 Fortran 28.0 对象链接到 27.0 的既有警告未阻止构建；后者仍跟踪于 CFG-05。迁移后独立 OFF 场景、前后快照与其他平台待补齐。

17 组脚本检查再次通过（RestFrames scope 7、contrib retention 5、standalone objects 5），`git diff --check` 通过；此次没有由代理运行工程配置、编译器或构建。仅提交本阶段源码、配置模板、测试、README 及台账，不纳入其他本地未跟踪文件。

### BUILD-08 ONNX 与可选 RPATH 实施与验证

2026-10-12 基于 UX-01 提交 `88346e66ba` 实现第二阶段，状态为 **已实现已构建**；当前 macOS 首次迁移和 CBS 启动通过，已提交为 `52aaf8434f`。当前 macOS ONNX/RestFrames 的真实开关范围、快照和无变化构建已通过，详见本轮开关验收记录；BUILD-08 总体保持部分完成，其他依赖及平台继续按范围验收。工程 configure/build 和运行验收由维护者执行。

实施前只读证据：ONNX 与 RestFrames 均 ON。ONNX 的 EXCLUDE 宏仍在公共配置头中，其 include 出现在 ColliderBit、Models、Utils、Backends 和 CBS_objects 的实际 flags.make。first、fortran、FarrayTest、cbs_preload 的实际 link.txt 都带两包 RPATH，却没有链接这两种库。gambit_preload 在包选择前创建，本就没有这两个 RPATH，不能计入本轮移除收益。wrapper 的当前 `.o.d` 使用者只有自身实现与 ATLAS_SUSY_2018_30；注册容器另外直接使用 ONNX 开关。

- 从通用配置头移出 EXCLUDE_ONNXRUNTIME，生成 `onnxruntime_variables.hpp`。两个实现、注册容器和 public wrapper 在 feature guard 前显式包含专用头；不改变分析算法、注册表内容或 ONNX 类结构。
- ONNX include 不再目录级传播。wrapper 含 Ort/ONNX 类型，因此 ColliderBit 的路径是 PUBLIC；ON/OFF 保持稳定，未安装时也可登记。以 ColliderBit 对象组装的 GAMBIT/CBS executable，以及直接链接 ONNX 的 executable，显式获得该路径；standalone program objects 按既有 helper 复制。启用时 contrib 的下载依赖顺序保留。
- 两包不再自动追加全局 CMAKE_INSTALL_RPATH。公共 executable helper 检查实际 link list 中的 package library，按需追加该 target 的 INSTALL_RPATH；继承和用户路径保留，包路径不重复追加。GAMBIT 和相关 standalones 共用此政策。ROOT/HepMC/YODA/FastJet/FlexibleSUSY 及 preload 基础路径保持本轮现有政策。
- ONNX 外部下载/注册/清理入口不变；OFF 不删除安装文件或标记。新增使用者需要包含专用头再判断其宏，wrapper 本身已包含它。

[INSTALL_RPATH](https://cmake.org/cmake/help/latest/prop_tgt/INSTALL_RPATH.html) 在创建 target 时从全局变量初始化；本工程已启用 BUILD_WITH_INSTALL_RPATH，因此按 target 设置可隔离两个可选包的链接变化。PUBLIC include 根据公开类型及 [target_include_directories 的作用范围](https://cmake.org/cmake/help/latest/command/target_include_directories.html) 选择。

无构建验证：新 [onnxruntime_scope.py](../cmake/tests/onnxruntime_scope.py) **9 组**通过；RestFrames scope 7、standalone objects 6、contrib retention 5，共 **27 组**。新夹具执行真实包选择、library/executable/standalone helper 和头生成，捕获 target/ExternalProject/codegen 注册，禁止 execute_process/try_compile/try_run，模拟只读探测。覆盖 PUBLIC 传播、无关模块隔离、ON/OFF/ON 的 common header/include 稳定、Linux/Darwin RPATH、独立开关、用户路径顺序/去重、partial project、安装/标记保留及全仓库 guard 使用者。原实现用同一夹具复现缺少专用头、未提供目标 PUBLIC include 和全局 optional RPATH 三类问题。夹具不替代实际构建图或动态加载验收。

#### 本阶段维护者验收

继续当前 cbs-llvm、C++17、ROOT、SDK 和其余依赖。**保留 build，不 clean，不 --fresh**。第一次配置会移除公共头旧 ONNX 宏与无关目标旧 include/RPATH，可能较多重编译/链接；这是一次性迁移，不能作为纯开关结果。

```sh
cd /Users/p.zhu/Gambit-Workshop/worktree/cbs-presets
set -o pipefail
cmake --preset cbs-llvm -DWITH_ONNXRUNTIME=ON -DWITH_RESTFRAMES=ON 2>&1 | tee /tmp/cbs-build08-scope-configure-first.log
cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-build08-scope-first.log
./CBS --help 2>&1 | tee /tmp/cbs-build08-scope-loader-first.log
```

首次 CBS 成功后记录公共头、九个目标 flags 和五个共享库 link 命令的 hash/mtime；这些文件在两个开关测试中应稳定，不包括必然改变的 CBS 链接命令与两个专用配置头。

```sh
cbs_build08_scope_snapshot() {
  python3 - <<'PY'
from pathlib import Path
import hashlib
names = {'ColliderBit.dir', 'Models.dir', 'Utils.dir', 'Backends.dir',
         'CBS_objects.dir', 'fjcontrib_nsubjettiness.dir', 'mkpath.dir', 'fortran.dir', 'gambit_preload.dir'}
flags = sorted(p for p in Path('build').rglob('flags.make') if p.parent.name in names)
assert len(flags) == 9, '当前 Unix Makefiles 应有上述九个目标'
paths = [Path('cmake/include/gambit/cmake/cmake_variables.hpp')] + flags
paths += [Path('build/Backends/CMakeFiles') / (name + '.dir/link.txt')
          for name in ('first', 'fortran', 'FarrayTest')]
paths += [Path('build/CMakeFiles') / (name + '.dir/link.txt')
          for name in ('cbs_preload', 'gambit_preload')]
for p in paths:
    print(hashlib.sha256(p.read_bytes()).hexdigest(), p.stat().st_mtime_ns, p)
PY
}
cbs_build08_scope_snapshot > /tmp/cbs-build08-scope-before.txt

cmake --preset cbs-llvm -DWITH_ONNXRUNTIME=OFF 2>&1 | tee /tmp/cbs-build08-scope-onnx-off-configure.log
cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-build08-scope-onnx-off.log
cbs_build08_scope_snapshot > /tmp/cbs-build08-scope-onnx-off.txt
diff -u /tmp/cbs-build08-scope-before.txt /tmp/cbs-build08-scope-onnx-off.txt
./CBS --help 2>&1 | tee /tmp/cbs-build08-scope-onnx-off-loader.log

cmake --preset cbs-llvm -DWITH_ONNXRUNTIME=ON 2>&1 | tee /tmp/cbs-build08-scope-onnx-on-configure.log
cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-build08-scope-onnx-on.log
cbs_build08_scope_snapshot > /tmp/cbs-build08-scope-onnx-on.txt
diff -u /tmp/cbs-build08-scope-before.txt /tmp/cbs-build08-scope-onnx-on.txt
./CBS --help 2>&1 | tee /tmp/cbs-build08-scope-onnx-on-loader.log

cmake --preset cbs-llvm -DWITH_RESTFRAMES=OFF 2>&1 | tee /tmp/cbs-build08-scope-restframes-off-configure.log
cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-build08-scope-restframes-off.log
cbs_build08_scope_snapshot > /tmp/cbs-build08-scope-restframes-off.txt
diff -u /tmp/cbs-build08-scope-before.txt /tmp/cbs-build08-scope-restframes-off.txt
./CBS --help 2>&1 | tee /tmp/cbs-build08-scope-restframes-off-loader.log

cmake --preset cbs-llvm -DWITH_RESTFRAMES=ON 2>&1 | tee /tmp/cbs-build08-scope-restframes-on-configure.log
cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-build08-scope-restframes-on.log
cbs_build08_scope_snapshot > /tmp/cbs-build08-scope-restframes-on.txt
diff -u /tmp/cbs-build08-scope-before.txt /tmp/cbs-build08-scope-restframes-on.txt
./CBS --help 2>&1 | tee /tmp/cbs-build08-scope-restframes-on-loader.log

cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-build08-scope-noop.log
```

所有 diff 应无输出。ONNX 每次切换只编译 wrapper、ATLAS_SUSY_2018_30 与 AnalysisContainer 共三个对象，CBS 重新链接；RestFrames 每次切换仍只编译六个必要对象，gambit_preload 与 CBS 重新链接。first/fortran/FarrayTest/cbs_preload 不应因这两个开关重新链接，其他模块/CBS_objects 和其他分析不应重编译。恢复 ON 复用原安装，最后重复构建零编译/链接/外部步骤。显式用户 runtime paths 保留，不计为本项目额外添加的路径。

CBS 的 link.txt 在 ON 保留所属 -lRestFrames/-lonnxruntime 和 runtime 路径，OFF 移除该包自动路径/链接项；三个后端例库和 cbs_preload 不带本项目自动加入的两项路径。`./CBS --help` 检查直接动态依赖可解析，不计为 ONNX 推理/RestFrames 分析运行通过；`--list-analyses` 基于 metadata/validation，不能据此判定 ONNX 是否编译启用。其他可选依赖、平台和物理运行按需补齐。

| 验收项 | 状态 | 说明 |
| --- | --- | --- |
| 新 ONNX/RPATH 9 组与相关 18 组 | 已通过 | 共 27 组，无工程配置或编译器执行 |
| 首次迁移与公共头/flags/link 快照 | 当前环境通过 | 首次 CBS 成功；本轮四次开关与最终 no-op 的 95 个文件快照均稳定 |
| ONNX OFF/ON 三对象、RestFrames OFF/ON 六对象 | 当前环境通过 | 四次对象/链接范围准确，公共文件稳定，CBS 专属 runtime paths 与开关一致 |
| CBS 启动与最后无变化构建 | 当前环境通过 | 四次 --help 正常，恢复 ON 后零编译/链接/生成/外部步骤；物理运行单独验收 |

#### 2026-10-12 当前 macOS 首次迁移验收

附件 `/Users/p.zhu/.codex/attachments/2d793729-47b7-40f5-b5d9-a7d2145238e0/Pasted text.txt` 共 765 逻辑行，仅包含两个功能均 ON 的首次配置、CBS 构建和 `--help`。同时只读核对 `/tmp/cbs-build08-scope-configure-first.log`、`/tmp/cbs-build08-scope-first.log` 与 `/tmp/cbs-build08-scope-loader-first.log`，内容一致。

- 第 380–382 行配置/生成成功，耗时分别为 6.4/0.6 秒；工具链 LLVM 22.1.8、GNU Fortran 15.2.0、C++17、ROOT 6.40.00、Python 3.13.13、ccache 4.13.6、SDK/minimum 27.0 保持一致，摘要检查 PASS/READY。
- 第 383–755 行完成 304 个原生对象编译、五个共享库与 CBS 共六次链接，CBS 成功。公共配置头移出旧宏、无关目标去掉 include/RPATH 导致首次迁移重编译，属于预期；此次没有外部 configure/build/install/record 步骤，原安装继续复用。不能将首次迁移记录为开关增量结果或量化提速。
- 第 757–765 行 `--help` 正常输出，没有 dyld 错误。只读检查 CBS 的 Mach-O 依赖与 LC_RPATH，RestFrames/ONNX 库及其 runtime paths 均存在；first/fortran/FarrayTest/cbs_preload/gambit_preload 的实际 LC_RPATH 均没有本项目自动加入的这两包路径。
- 实际九个 flags.make 中，只有 ColliderBit 和 CBS_objects 带 ONNX include；Models/Utils/Backends/Fortran/FastJet Contrib/mkpath/preload 没有该路径。公共头不再带 ONNX 宏，两个专用头保持 ON；实际 `.o.d` 恰好三个 ONNX 专用头消费者，与设计范围一致。五个共享库 link.txt 均不带两包路径或链接项，CBS 保留正确的链接项和路径。
- 日志无配置或构建错误。pybind11 两项 CMake 弃用提示及 fjcontrib 三项未使用参数/变量警告来自现有外部代码；缺少可选 Python scanner 模块、旧 h5py/HDF5 版本差异等提示沿用。27 组已通过的脚本检查所用源码与当前 14 个待提交文件逐一比对一致；此次仅做日志、生成文件和二进制只读核对，没有由代理执行工程配置、编译或 CBS。

当前首轮通过，可以提交本阶段实现。此次没有 ONNX/RestFrames OFF/ON、跨开关快照或最后 no-op 日志，仍保留这些待验收项；其他依赖与平台继续按需审计。

## 配置正确性与使用体验待办

| 编号 | 优先级 | 状态 | 实施内容 | 验收标准与位置 |
| --- | --- | --- | --- | --- |
| CFG-01 | P1 | 已实现已构建 | LLVM 先尊重每种语言的 CMAKE 编译器变量，再读取 CC/CXX；未指定时保留自动搜索。单选时在所属安装补齐匹配版本，非法显式选择不回退 | [CBSCompilerDiscovery.cmake](../cmake/presets/CBSCompilerDiscovery.cmake)、[NativeCompilerDiscovery.cmake](../cmake/presets/NativeCompilerDiscovery.cmake)、[NativePresetToolchain.cmake](../cmake/toolchains/NativePresetToolchain.cmake)、[native_compiler_selection.py](../cmake/tests/native_compiler_selection.py)。11 组脚本夹具与当前 macOS LLVM 显式/缓存配置、两次无变化 CBS 构建通过；真实 bootstrap 环境选择与失败诊断、多版本及其他平台待补齐 |
| CFG-02 | P2 | 已实现已构建 | 在 project 前按 CMAKE_OSX_SYSROOT、SDKROOT、自动发现选择 SDK；缓存实际目录，显式无效选择不回退；原生/外部参数共用该 SDK | [MacOSX.cmake](../cmake/MacOSX.cmake)、[macos_sdk.py](../cmake/tests/macos_sdk.py)。26 组脚本检查与当前 SDK 的显式/缓存/自动发现配置、三次 CBS 构建通过；首次外部迁移后零重复步骤，其他 SDK/平台待补齐 |
| CFG-03 | P2 | 已实现已构建 | 原生语言、macOS linker 与 Python/Boost/HDF5/SQLite 检查随输入变化失效；共享 HDF5 gate 同步修复，输入稳定时复用 PASS/FAIL | [ValidationCache.cmake](../cmake/ValidationCache.cmake)、[CBSValidation.cmake](../cmake/presets/CBSValidation.cmake)、[validation_cache.py](../cmake/tests/validation_cache.py)。16 组无编译夹具、当前配置的九项首次重检/后续复用及两次 CBS 无变化构建通过；只重跑检查、真实依赖恢复及其他平台按需补齐 |
| CFG-04 | P2 | 已实现已构建 | 同轮只读工具链/Python 元数据查询复用，Python 必需/可选模块按组导入，并共享原始结果 | [ProcessProbe.cmake](../cmake/ProcessProbe.cmake)、[PythonModules.cmake](../cmake/PythonModules.cmake)、[process_probes.py](../cmake/tests/process_probes.py)。22 组无构建夹具、当前 macOS 双系统 bootstrap、两次配置及 CBS 无变化构建通过；其他过滤/平台按需补齐 |
| CFG-05 | P2 | 已实现已构建 | 统一 OpenMP 发现及自动缓存 hints；原生 C/C++ SDK/minimum 使用 CMake，GNU Fortran 补齐未探测的选项；外部 shell/CMake flags 分别由公共政策派生 | [OpenMP.cmake](../cmake/OpenMP.cmake)、[MacOSX.cmake](../cmake/MacOSX.cmake)、[platform_flags.py](../cmake/tests/platform_flags.py)。78 组脚本夹具与 C++ 政策 30 项通过；当前 macOS LLVM 首次迁移及第二轮无变化 CBS 构建通过，实际两种 Fortran 对象/库与 CBS minimum 均为 27.0；其他 SDK/profile/平台按需补齐 |
| UX-01 | P2 | 已实现已构建 | bootstrap 与 README 构建示例明确使用 `--parallel 8`，说明简写、资源调整及环境变量优先级 | [BootstrapReport.cmake](../cmake/presets/BootstrapReport.cmake)、[Preset README](../cmake/presets/README.md)。15 个注册 preset 的纯报告渲染与文档命令检查通过；当前 macOS 双系统 bootstrap 四项构建提示及 CBS 零工作增量构建通过 |
| UX-02 | P2 | 部分完成 | 摘要已补充缓存策略、ccache 版本和 C/C++ launcher；依赖复用或重建原因及 compile_commands 导出待开发 | 摘要已有标准选择信息；后续实际构建命令可追溯，IDE 能读取 `compile_commands.json` |
| DOC-01 | P2 | 已合入 | 工程标准统一共享 build/、切换时 --fresh 与既有输出布局；同步示例、验收清单、15 个公开 preset 注册表及并发数 | [工程标准](CMAKE_PRESET_STANDARD.md)、[使用说明](../cmake/presets/README.md)。15 个定义与构建入口静态核对、六种注册/筛选检查及文档片段验证通过；维护者两轮 no-op 均通过，提交为 `eeaf63d5ef` |
| DOC-02 | P2 | 已合入 | 文档引用的 HPC preset 示例已纳入版本控制，保留原内容 | [CMakeUserPresets.json.example](../CMakeUserPresets.json.example)。临时复制为 CMakeUserPresets.json 后，原生 --list-presets=all 正常列出 configure/build，继承共享 build/；提交为 `eeaf63d5ef`，真实 HPC 构建待维护者执行 |

### CFG-01 实施与验证

2026-10-11 基于 `eb03406a7c` 实现，状态为 **已实现已构建**；维护者当前 macOS LLVM 配置及重复 CBS 构建通过，本阶段随验收提交。本阶段修复公共 LLVM 发现入口，适用于所有注册系统的 LLVM profile 及只读 bootstrap；没有更改 preset 的共享 build、编译参数、输出目录或主工程构建目标。

- `cbs_find_llvm_toolchain` 每种语言按 `CMAKE_C_COMPILER` / `CMAKE_CXX_COMPILER`、环境 `CC` / `CXX` 的顺序解析。已有缓存编译器视为显式选择；没有任何显式选择时，保留原 Homebrew、标准安装目录、版本化 PATH 及普通 PATH 搜索。
- 两个显式编译器必须满足原 GAMBIT 最低版本策略，均为 upstream Clang 且版本一致。缺失路径、AppleClang/GNU、过旧版本或版本不匹配直接返回诊断，不搜索另一套 LLVM 来替代。只提供一个语言时，匹配其同目录或实际安装中的 companion，包含版本化名称；不能补齐时提示指定另一语言。
- 通用命令解析先识别实际路径，修复未加 shell 引号的带空格路径；普通命令名称仍从 PATH 搜索，不优先拾取工作目录同名文件。LLVM selector 只接受一个可执行文件，额外参数不再悄悄丢失：编译 flags 放 `CMAKE_C_FLAGS/CMAKE_CXX_FLAGS`，包装工具用 compiler launcher。该限制只作用于 LLVM 显式选择，本轮不扩展其他 profile 的参数处理。
- LLVM root 从实际 C++ 可执行文件的目录推导，正确处理符号链接。NativeCompilerDiscovery 与 NativePresetToolchain 通过原共享调用接入；Fortran 选择、AppleClang/GNU profile 及已有跨 profile 的缓存拒绝保持原策略。CMake 变量优先于环境，bootstrap 不读 build 缓存，因此二者面对不同输入时可能报告不同选择。

[native_compiler_selection.py](../cmake/tests/native_compiler_selection.py) 的 11 组脚本夹具通过：缓存优先；环境优先于默认安装；单语言补齐；版本化名称；符号链接及真实 root；带空格/引号/PATH 名称与工作目录同名文件；无效路径/身份/最低版本/混合版本不回退；缺失 companion 和额外参数诊断；重复加载工具链；Darwin/Linux 自动搜索；其他 profile 与共享缓存契约。原实现已用同一夹具复现：发现和工具链均忽略 CC/CXX、选择默认 LLVM。测试运行真实 CMake 函数，临时假程序只响应版本查询；执行 guard 按真实路径禁止任何真实程序探测。没有工程配置、启用语言、真实编译器调用或编译。

#### 维护者验收

保持当前 `/opt/homebrew/opt/llvm` 编译器和现有 build，不清空、不 clean、不 --fresh，也不切换依赖或 C++ 标准。以下是当前机器已有的缓存路径；在其他机器替换为其现有编译器。

1. 只读发现验证环境选择：

   ```sh
   cd /Users/p.zhu/Gambit-Workshop/worktree/cbs-presets
   CC=/opt/homebrew/opt/llvm/bin/clang CXX=/opt/homebrew/opt/llvm/bin/clang++ \
     ./cmake/bootstrap --preset cbs-llvm --verbose
   ```

   报告应使用指定的编译器与版本。LLVM root 可以显示 Homebrew Cellar 的实际版本目录，这来自符号链接解析，不能据此判断换了编译器。

2. 用原编译器路径明确配置，再验证相同配置后的增量构建：

   ```sh
   set -o pipefail
   cmake --preset cbs-llvm \
     -DCMAKE_C_COMPILER=/opt/homebrew/opt/llvm/bin/clang \
     -DCMAKE_CXX_COMPILER=/opt/homebrew/opt/llvm/bin/clang++
   cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-cfg01-first.log
   cmake --preset cbs-llvm
   cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-cfg01-noop.log
   ```

   当前编译器仍为 LLVM 22.1.8；相同路径不应因搜索其他 LLVM 而报冲突或触发无关对象重编译。两次 CBS 应成功，无变化构建应保持零对象编译、零链接、零重复外部步骤。不会为了本项验收实际切换编译器或清理已安装依赖。

3. 只读失败场景，不修改缓存：

   ```sh
   CC=/__gambit_missing_compiler__/clang CXX=/opt/homebrew/opt/llvm/bin/clang++ \
     ./cmake/bootstrap --preset cbs-llvm --verbose
   ```

   应报告 unavailable，并明确指出 CC 请求的路径不存在；不能转选已安装的默认 LLVM。有效 discovery 请求即使 unavailable 仍退出 0，这是 bootstrap 既有约定。后续正常配置继续使用缓存的原编译器。

真实更换编译器或版本需 `--fresh`，并承担必要的工具链/外部包迁移成本；ENV 不能覆盖已有 CMake 编译器变量。此项不修复升级后保持同一路径的编译器身份缓存、探测复用（CFG-04）或 Fortran minimum flags（CFG-05）。

| 验收项 | 状态 | 记录 |
| --- | --- | --- |
| 十一组脚本夹具与原问题复现 | 已通过 | 假版本查询程序和临时 `cmake -P`，没有真实编译器或工程配置 |
| 当前显式 LLVM 配置、缓存重配置及无变化 CBS | 已通过 | 835 行日志；两次配置均 LLVM 22.1.8，两次构建零对象编译、零链接、零重复外部步骤 |
| 环境指定 LLVM 的真实只读 bootstrap | 待执行 | 未包含在此次维护者日志，脚本夹具已通过 |
| 显式无效路径的真实只读诊断 | 待执行 | unavailable，不回退，不改 build 缓存 |
| 多版本实机、单语言、Linux 和其他平台 | 待执行 | 临时夹具不替代平台配置与构建 |

#### 2026-10-11 维护者日志验收

附件 `/Users/p.zhu/.codex/attachments/36d28b02-1458-4464-b2d4-87618915cce7/Pasted text.txt` 共 835 行。维护者先通过 `-DCMAKE_C_COMPILER` / `-DCMAKE_CXX_COMPILER` 明确指定原 Homebrew LLVM 路径并构建，再仅用同一 preset 重配置后构建；两次均使用共享 build、CBS `-j8` 和 `pipefail`。

- 两次摘要第 297–301、709–713 行均为 upstream LLVM 22.1.8，C/C++ 路径保持 `/opt/homebrew/opt/llvm/bin/clang` / `clang++`。LLVM root 为 `/opt/homebrew/Cellar/llvm/22.1.8`，符合真实路径解析策略，不代表切换编译器。所有配置检查 PASS，环境 READY；ROOT 6.40.00、C++17、Python 3.13.13、ccache 4.13.6 和 SDK/minimum 27.0 保持一致。
- 第一轮第 382–423 行、第二轮第 794–835 行均只有 42 条目标完成消息；零对象编译、零链接、零外部 configure/build/install/record 及构建阶段代码生成，两次均以 CBS 成功结束。`check-rebuild-*` 目标完成属于轻量输入检查，不表示包重新构建；FastJet/Contrib 配置身份均匹配并复用。
- 配置分别 7.0/5.4 秒，生成分别 0.5/0.4 秒；日志没有总构建时间或 ccache 命中增量，不填写提速比例。pybind11 的最低 CMake/CMP0148 弃用警告、缺少可选 scanner 模块/库及 h5py/HDF5 版本提示未阻止本次 CBS，未发现新增配置或构建错误。
- 只读核对当前缓存及 CBS_objects 生成 flags：C/C++ 与 LLVM 摘要一致，原 Fortran 路径保持；C++17、SDK/minimum 27.0 保持。脚本夹具 11 组再次通过，`git diff --check` 通过。代理没有执行工程配置、真实编译器或构建。

此次日志覆盖当前显式选择、缓存重配置与增量构建；未执行真实 bootstrap、无效路径、多版本切换、单语言或其他平台，保留对应待补验收项。提交仅包含公共编译器发现、回归脚本、README 和本台账；其他本地文件不纳入。

### CFG-02 实施与验证

2026-10-11 基于 CFG-01 提交 `cf10364f98` 实现，状态为 **已实现已构建**；维护者当前 SDK 的显式、缓存重配置和自动发现验收通过，已提交为 `4dad77208a`。本阶段修复共享 macOS 配置，不增加 preset 专用 build 目录或输出布局。

- 原 `MacOSX.cmake` 在 project 后检查 `CMAKE_CXX_SYSROOT`，随后却把自动 SDK 写入 `CMAKE_OSX_SYSROOT` 的普通变量。脚本夹具已复现：显式缓存保留所选 SDK，普通变量和实际 flags 被默认 SDK 覆盖，导致缓存与命令不一致。
- 新 SDK 初始化在 project/启用语言之前运行：非空 `CMAKE_OSX_SYSROOT`（含缓存）优先，其次 `SDKROOT`，再自动查询 macosx。SDK 名称按该名称查询并解析为实际目录；缺失路径、名称失败、空结果或不存在的查询目录明确报错，不选择另一个 SDK。结果保存在公共 CMake cache 并传回调用作用域；非 macOS 主机保持原行为。
- 当前普通 SDK 路径下，C/C++、共享链接、Rivet 和 YODA 的 flags 字符串已与旧实现夹具逐项比对，一致。带空格的 SDK 在 legacy flags 中加引号；Rivet CPP 和 YODA lib 搜索共用这个路径。重复初始化读取缓存，不重新探测或被改变后的环境覆盖。
- 主工程及 CMake 外部 recipe 显式传递同一 SDK。新增 `GAMBIT_MACOS_CMAKE_SYSROOT_ARG`，覆盖 HepMC、HEPLike、libphysica、obscura、VevaciousPlusPlus、GreAT 和 Minuit2 的 CMake 参数。已有外部配置命令发生一次迁移是预期；首次可能执行 HepMC configure/build/install，后续相同命令应稳定。该项不保证真实 SDK 切换时免重建。
- 单一 minimum 政策不变：已有 `MACOS_DEPLOYMENT_TARGET` 优先，初次显式 `CMAKE_OSX_DEPLOYMENT_TARGET` 仍被接受；只有未指定时才查询选定 SDK 的版本，不再查询另一套默认 SDK。Fortran minimum flags、重复 OpenMP/SDK flags 等仍由 CFG-05 跟踪。

[macos_sdk.py](../cmake/tests/macos_sdk.py) 的 10 组检查通过：显式路径与带空格路径优先；显式名称；SDKROOT 路径/名称；自动发现及缓存重入；非法路径/名称/查询结果不回退；选定 SDK 的默认 minimum、显式最低版本及版本查询失败；原生/Rivet/YODA flags 与 CMake SDK 参数；project 后不再覆盖；非 macOS 及 pre-project 调用顺序；CMake 外部 recipe 参数覆盖。测试仅运行临时 `cmake -P`，xcrun 查询全部由 CMake 函数模拟，其他进程探测立即拒绝，不执行真实工具、工程配置或编译。

相关脚本回归再次通过：contrib retention 5 组、FastJet/Contrib build identity 11 组，加上本项 SDK 10 组，共 26 组；`git diff --check` 通过。真实工作树与临时夹具中的检查一致，没有执行工程配置、真实工具探测或构建。

#### 维护者验收

当前生成 flags 使用 `/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX27.0.sdk`，公共 minimum 为 27.0，但旧缓存 `CMAKE_OSX_SYSROOT` 仍为空。以下保持同一 SDK、LLVM 和共享 build；不需要清空、clean 或 --fresh。

1. 明确指定当前实际使用的 SDK，再做相同配置后的无变化构建：

   ```sh
   cd /Users/p.zhu/Gambit-Workshop/worktree/cbs-presets
   set -o pipefail
   cmake --preset cbs-llvm \
     -DCMAKE_OSX_SYSROOT=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX27.0.sdk
   cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-cfg02-first.log
   cmake --preset cbs-llvm
   cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-cfg02-noop.log
   ```

   两次 SDK 日志应保留指定路径，minimum 仍 27.0，C/C++ 仍 LLVM 22.1.8；两次 CBS 均成功。首轮外部 CMake 参数迁移可能执行 HepMC 的配置/构建/安装，不把该成本计为正常 no-op；第二次应没有对象编译、链接或重复外部步骤。对比真实 flags/cache 与外部 CMake 命令中的 `CMAKE_OSX_SYSROOT`，确认一致。

2. 重新自动发现同一默认 SDK，只清除该 SDK 缓存项，保留其他设置：

   ```sh
   env -u SDKROOT cmake --preset cbs-llvm -U CMAKE_OSX_SYSROOT
   cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-cfg02-auto.log
   ```

   若当前 Xcode 默认仍为同一 SDK，应回到相同实际路径并继续增量稳定。默认结果现在也会缓存；更换 Xcode/默认 SDK 后，可用上述命令主动重新发现，或用显式路径选择。`cmake --preset cbs-llvm` 本身会保留缓存选择。

3. 可选非法路径验收：配置时指定不存在的 SDK，应在 project 前报错；随后必须用第 1 步的正常 SDK 路径恢复该缓存项，再进行正常构建。不要执行 fresh 或清空依赖来处理这个诊断。对应失败条件已由脚本夹具覆盖，此场景不计入当前实际构建通过项。

| 验收项 | 状态 | 记录 |
| --- | --- | --- |
| 十组 SDK 脚本夹具、旧问题复现及同 SDK flags 对比 | 已通过 | 模拟 xcrun，真实 CMake 函数，无真实工具或工程构建 |
| 当前显式 SDK 与缓存重配置、CBS 构建 | 已通过 | 三次 CBS 成功；首轮外部迁移完成，缓存重配置后零重复步骤 |
| 同一 SDK 的默认重新发现与增量构建 | 已通过 | 清除单个 SDK 项并去掉 SDKROOT，仍 SDK 27.0；零对象编译、链接及外部步骤 |
| 非法 SDK 实机诊断、其他 SDK/路径/平台 | 待执行 | 失败后恢复正常 SDK；夹具不替代平台构建 |

#### 2026-10-11 维护者日志验收

附件 `/Users/p.zhu/.codex/attachments/c21edbd0-2361-428e-bf50-8122745fb015/Pasted text.txt` 共 2433 行，依次为指定当前 SDK、读取 SDK 缓存、去掉 SDKROOT 并清除单个 SDK 项重新自动发现；每次配置后构建共享 build 的 CBS `-j8`，三次均成功。

- 三次 SDK 日志（第 56、1653、2065 行）均保持 MacOSX27.0.sdk；minimum 27.0、LLVM 22.1.8、C++17、ROOT 6.40.00、Python 3.13.13、ccache 4.13.6 一致，所有环境检查 PASS/READY。主配置分别 7.1/6.1/5.5 秒，生成 0.6/0.5/0.4 秒；未提供总构建耗时或 ccache 增量，不填提速比例。
- 第 383–1609 行完成首次迁移：HepMC configure/build/install、28 个外部对象编译（主库 20、search 2、rootIO 6）、三个 HepMC 动态库链接以及 ROOT dictionary 生成。主工程没有对象编译或链接。HepMC 变化触发 Rivet/Contur 的输入检查、配置/包装构建和成功记录；Rivet Python 扩展有实际构建命令，属于首次迁移的后续依赖成本，不能计作正常无变化开销。
- 缓存重配置后的第 1980–2021 行及自动发现后的第 2392–2433 行，各只有 42 条目标完成消息；零对象编译、零链接、零外部步骤和构建阶段代码生成。三次均以 CBS 成功结束。FastJet/Contrib 三次构建身份一致、安装复用。
- 只读比对主缓存、HepMC 外部缓存与 `hepmc-cfgcmd.txt`：SDK 路径和 minimum 一致，外部命令显式包含所选 SDK；CBS_objects 与 HepMC3 的真实 flags 都使用该 SDK。SDK cache 已由原空值变为实际 PATH，符合初始化策略。
- 未发现新增配置/构建错误。pybind11/HepMC 的最低 CMake 弃用、HepMC 源码 sprintf 弃用和 ROOT unused class rule、Rivet 重复 -ldl 警告未阻断构建。HepMC 的 extra path 警告来自原有 `CMAKE_COMMAND ... ..` 配方，本轮没有更改该行；冗余 source 参数可后续单独清理。

26 组脚本检查再次通过（SDK 10、contrib retention 5、build identity 11），`git diff --check` 通过。代理未执行工程配置、编译器或构建；非法路径、其他真实 SDK/名称/带空格路径以及平台构建仍按表保留待补项。提交仅包含本阶段八个源码、测试和文档文件。

### CFG-03 实施与验证

2026-10-11 基于 CFG-02 提交 `4dad77208a` 实现，状态为 **已实现已构建**；维护者当前环境首次重检、相同配置复用及两次 CBS 增量验收通过，已提交为 `35e6a4e73e`。共享 build、输出布局与外部项目配方保持既有政策；实际工程配置和构建由维护者执行。

- 原 CBS 检查只有 C++ 模式会比较输入，C、Fortran、dynamic_lookup、Python、Boost、HDF5、SQLite 则只要结果变量存在就跳过，旧 PASS/FAIL 都可能沿用。共享 `optional.cmake` 中的 `GAMBIT_HDF5_USABLE` 更早决定 HDF5 功能，旧失败会阻止后续 CBS 再验证，不能只修 CBS 末尾的检查。
- 新增 [ValidationCache.cmake](../cmake/ValidationCache.cmake)，用带长度的字段和 SHA256 保存每项检查的输入签名。输入变化时，在探测的调用作用域同时删除 cache 和普通结果变量；否则 CMake 原生模块的 `DEFINED` 判断仍可能被旧普通变量挡住。相同签名保留原生检查的缓存语义；旧 C++ 单项签名迁移至统一命名 `GAMBIT_CHECK_CACHE_<result>_SIGNATURE`。
- 输入覆盖探测源码、语言编译器/版本/目标/flags/标准、各配置 flags（含自定义配置）、链接 flags、try_compile 平台变量及其值、SDK/sysroot/minimum/architecture、required 定义/includes/libs/link 设置，以及相关包版本、FOUND 状态和 Python executable。PATH、CPATH、语言 include path、LIBRARY_PATH、SDKROOT、DEVELOPER_DIR 也计入，以跟随环境改变。
- 选定 include 下的少量直接探测头和 toolchain 文件计算内容 hash；绝对编译器、linker、解释器、库及 sysroot 路径记录真实路径、存在状态、大小和时间戳。可发现同路径文件升级、删除/修复及软链接指向变化；不对大二进制做全量 hash，也不递归扫描 SDK 或所有传递依赖。
- Python、Boost、HDF5、SQLite 在可用性分支之前更新签名，防止“找到 → 未找到 → 再找到”复活旧结果；每项使用独立 include/lib 列表。共享 HDF5 gate 在功能选择之前遵循同一策略，修复后可恢复打印器和读取器。Boost 兼容 finder 的 singular/plural include 变量。SQLite/Contur 仍为可选；OpenMP 状态、sqlite CLI 及已有 Python 模块检查继续使用每次配置的当前结果。
- `Validation: ... check inputs are new or changed` 提示仅在新签名或变化时出现。CBS 失败提示先建议修复依赖并正常重新配置，也给出只重跑这些检查的 `-U 'GAMBIT_CHECK_CACHE_*'`；切换编译器家族才按共享 build 政策使用 `--fresh`。

[validation_cache.py](../cmake/tests/validation_cache.py) 的 16 组脚本检查通过：无变化复用 PASS/FAIL；四类依赖版本变化局部重检与失败恢复；消失/重现；头文件修改/删除/修复；头和 toolchain 同大小同时间戳内容修改；库及 Python executable 元数据；软链接切换；语言 flags/标准与普通变量遮蔽；公共链接/required/SDK/config/platform 输入；编译器文件变化；toolchain 与手动签名 reset；旧结果迁移；非 macOS 不探测 dynamic_lookup；跨脚本进程缓存复用；调用者 required 状态保留；共享 HDF5 gate 先恢复再选择功能。脚本以 CMake 函数模拟原生 `DEFINED`/CACHE 行为并计数，运行真实 validator/gate，禁止 execute_process/try_compile/try_run；不执行编译器或工程配置。

C++ 标准政策的 30 项脚本检查（15 selections、4 parsers、11 rejected configurations）与静态 diff 检查通过。夹具验证缓存控制逻辑，不替代真实编译/link 检查或多平台构建。

#### 维护者验收

当前工具链、SDK 和依赖路径保持不变，不清空 build、不 clean、不 --fresh。

1. 完成一次签名迁移，再重复同样的配置和构建：

   ```sh
   cd /Users/p.zhu/Gambit-Workshop/worktree/cbs-presets
   set -o pipefail
   cmake --preset cbs-llvm 2>&1 | tee /tmp/cbs-cfg03-first-configure.log
   cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-cfg03-first-build.log
   cmake --preset cbs-llvm 2>&1 | tee /tmp/cbs-cfg03-noop-configure.log
   cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-cfg03-noop-build.log
   ```

   现有 macOS CBS 配置首次应显示九项签名刷新（共享 HDF5 gate、C/C++/Fortran、dynamic_lookup、四类依赖）；所有 required 检查 PASS、环境 READY。首次增加小探测开销，不把其耗时当正常 no-op。第二次应无签名刷新；两次 CBS 成功，原生对象/链接和外部步骤应保持无变化。如实际依赖文件或环境有变化，应按日志记录对应的合理重检。

2. 主动只重跑验证，再确认缓存恢复复用：

   ```sh
   cmake --preset cbs-llvm -U 'GAMBIT_CHECK_CACHE_*' 2>&1 | tee /tmp/cbs-cfg03-reset-configure.log
   cmake --preset cbs-llvm 2>&1 | tee /tmp/cbs-cfg03-reset-noop-configure.log
   cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-cfg03-reset-build.log
   ```

   reset 轮显示同样的九项签名刷新及 PASS；下一轮无刷新，CBS 成功且无重复编译/链接/外部步骤。reset 只移除本阶段签名；编译器、依赖 finder 缓存、对象和安装继续保留。

3. 依赖失败恢复已用模拟 fixture 覆盖，无需为初次验收破坏真实依赖。以后实际升级或修复包时，确认 finder 报告的 include/library 路径，再检查该项刷新、结果恢复与下一轮复用。

| 验收项 | 状态 | 记录 |
| --- | --- | --- |
| 16 组缓存夹具、C++ 政策 30 项与静态检查 | 已通过 | 无真实编译器、工程配置或构建 |
| 当前环境首次签名迁移与相同配置复用 | 已通过 | 首轮九项刷新，第二轮无刷新，均 PASS/READY；两次 CBS 零编译、链接及外部步骤 |
| 只清签名后的重检与复用 | 待执行 | reset 重检一次；后续配置及 CBS 稳定 |
| 真实依赖升级/失败修复及其他平台 | 待执行 | finder 输入确实改变后记录；夹具不计作实际编译验收 |

本机制验证 finder 已选中的输入，不自动清除 find_package 缓存或改选依赖。它不穷举传递头/库、未解析的库名或 imported target 对应文件；大二进制若内容变化但保持大小和时间戳，也可能不触发自动失效。这些情况可用第 2 步强制重检；真实编译器家族切换继续按 `AGENTS.md` 使用 --fresh。

#### 2026-10-11 维护者日志验收

附件 `/Users/p.zhu/.codex/attachments/1ee072a4-e237-4600-8c1b-8b765db46d39/Pasted text.txt` 包含同一 `cbs-llvm`、共享 build、CBS `-j8` 的首次签名迁移和重复配置/构建，两个 CBS 均成功，无新增错误。

- 首轮第 63、288–295 行恰好出现九项输入刷新：共享 HDF5 gate、C/C++/Fortran、macOS dynamic_lookup、Python、Boost、HDF5 和 SQLite。第 315–326 行所有检查 PASS，环境 READY。第二轮没有任何 `Validation:` 刷新，第 727–738 行继续 PASS/READY，符合输入稳定时复用结果的预期。
- 第 385–426 行与第 797–838 行各仅有 42 条目标完成输出，均零对象编译、零链接、零外部 configure/build/install/record 及构建阶段代码生成。`check-rebuild-*` 的目标完成输出属于轻量输入检查；Rivet/Contur 没有再次进入外部步骤。两次 FastJet/Contrib 均匹配安装身份并复用。
- 工具链仍 LLVM 22.1.8、GNU Fortran 15.2.0、Python 3.13.13、C++17、ROOT 6.40.00、ccache 4.13.6，SDK/minimum 27.0 一致；HDF5 1.10.11 与 SQLite 继续启用。配置分别 10.0/5.6 秒，生成 0.6/0.4 秒；首次重检后回到缓存复用符合预期，日志没有独立探测耗时、总构建耗时或 ccache 增量，不填写提速比例。
- 只读检查真实 `build/CMakeCache.txt`：九项原生结果均为 1，各自签名为完整 SHA256，旧 `CBS_VALIDATION_CXX_SIGNATURE` 已移除。`CMakeConfigureLog.yaml` 中存在九项对应的最新原生 probe 事件，与首次刷新相符。
- 告警仅为已有 pybind11 最低 CMake/CMP0148 弃用；可选 scanner Python 模块、scanner 库和 WSTP libuuid 缺失提示沿用原配置，不阻断 CBS。本次没有新的 HDF5 失败、链接问题或重复外部工作。

16 组缓存夹具、C++ 标准政策 30 项和 `git diff --check` 再次通过。代理没有执行工程配置、编译器或构建。手动 `-U 'GAMBIT_CHECK_CACHE_*'`、真实依赖失败后恢复与其他平台仍保留待补项；对应模拟夹具不能计作真实编译验收。提交只包含本阶段六个源码、测试和文档文件，其他本地未跟踪文件保持原状。

### CFG-04 实施与验证

2026-10-11 基于 CFG-03 提交 `35e6a4e73e` 实现，状态为 **已实现已构建**；维护者当前 macOS 双系统 bootstrap、两次配置及 CBS 无变化构建通过，已提交为 `f981c115cf`。目标是减少同一 CMake 进程的重复查询和解释器启动；下一次配置仍从当前环境重新读取。工程配置与构建继续由维护者执行。

- 新增共享 `ProcessProbe.cmake`，只用于编译器版本/GNU dumpversion、LLVM Homebrew prefix、xcrun 编译器位置及 Python 元数据等只读查询。GLOBAL 属性复用成功和失败的结果，不写 CMakeCache，不跨 bootstrap/configure 或 toolchain 子进程。命令及参数边界、cwd、timeout、相关 PATH/编译器/SDK/locale/Python 环境、可执行文件真实路径/大小/时间戳和显式探测脚本内容 hash 参与键；编译器优先级、家族检查与 `--fresh` 政策保持原状。
- bootstrap 的 GAMBIT/CBS 使用同一 Python 元数据查询，分别判断开发库要求；只选 GAMBIT 不导入 CBS 的四个可选模块。provider 可用 `preset_probe_python_modules_<system>` 声明本轮模块组。`--list`、非法过滤与跨主机条目维持零环境探测。
- 新增 `PythonModules.cmake` 和批量导入脚本：主工程八项必需模块与选中的 CBS 四项可选模块合并，扫描器十三种不同模块合并，backend 模块组只补查尚未请求的模块。CBS/原生 GAMBIT 共用原始结果，PyYAML 必需、Rivet/Contur 可选和扫描器 pip 包别名规则不变；h5py/HDF5 版本政策在消费结果时单独判断，版本不匹配仍禁用相关功能。
- Python 导入保持旧 `-c` 的 cwd 搜索路径；`-B` 不生成探测字节码。总批次超时按每个请求模块十秒计，逐条刷新结果；异常/SystemExit 记为缺失，崩溃或超时保留已完成记录，只对未报告模块单独补查。新脚本变更纳入自动 CMake 重配置依赖。不同配置进程不缓存模块结果，因此安装或移除模块后直接重新配置即可；同一次配置过程中修改包安装不属于复用契约。
- 本轮不修改语言/链接 flags、构建目录、并发数、目标图或 ExternalProject 配方，不应要求清空 build 或主动刷新外部依赖。

无构建验证：`process_probes.py` 的 22 组夹具、原有编译器选择 11 组、contrib 保留 5 组及外部自动重建 11 组通过。夹具仅运行 `cmake -P`、临时版本报告器和临时 Python 包；所有实际编译器及 compile/run 探测均被阻止。完整 dispatcher 使用实际 provider/registry，CMake `-E echo` 只负责输出报告；测试不创建工程 build 或 CMakeCache，不计为真实配置/编译验收。

| 夹具场景 | 本轮观察 |
| --- | --- |
| 同时选择 GAMBIT/CBS，Darwin 的 LLVM/AppleClang profile | Python 元数据查询一次；yaml 与 CBS 四项可选模块一次导入；每个 C/C++ 可执行文件 `--version` 一次；GNU Fortran 两种版本命令各一次；xcrun 两种位置命令各一次；Homebrew LLVM prefix 一次 |
| 只选 GAMBIT / `--list` / 非法 system | GAMBIT 仅导入 yaml；后两者零环境命令 |
| 主工程八项必需 + CBS 四项可选模块 / 关闭 CBS 后端 | 分别一次导入十二项 / 一次导入八项；后续原生/CBS 查询无额外进程 |
| 十五个 Python scanner 的十三种模块及 h5py 版本检查 | 一次导入，保留缺失包别名和 HDF5 不匹配策略 |
| 失败、输出干扰、SystemExit、批次崩溃、工具超时 | 保留独立结果；崩溃后只补查未报告项；同轮失败/超时可复用 |
| 环境、解释器、软链接、同大小同时间戳脚本内容、下一轮安装模块 | 按输入变化重查；新 CMake 进程重新发现安装后的模块 |

以上为模拟查询次数，不据此填写真实提速比例。当前机器 bootstrap、两次配置及 CBS 构建已收到维护者日志，验收记录见下；日志没有命令调用 trace，真实查询次数及独立探测耗时未量化。

手动验收（保持当前 `cbs-llvm` 与相同依赖选项，不清空 build，不加 `--fresh`）：

```sh
cd /Users/p.zhu/Gambit-Workshop/worktree/cbs-presets
set -o pipefail
./cmake/bootstrap --system gambit --system cbs --verbose 2>&1 | tee /tmp/cbs-cfg04-bootstrap.log
./cmake/bootstrap --system gambit --verbose 2>&1 | tee /tmp/cbs-cfg04-gambit.log
./cmake/bootstrap --list 2>&1 | tee /tmp/cbs-cfg04-list.log
cmake --preset cbs-llvm 2>&1 | tee /tmp/cbs-cfg04-configure-1.log
cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-cfg04-build-1.log
cmake --preset cbs-llvm 2>&1 | tee /tmp/cbs-cfg04-configure-2.log
cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-cfg04-build-2.log
```

检查 preset、Python/工具链身份、必需与可选依赖理由是否保持正确；两次配置环境应 READY，原有输入签名稳定时不应重新触发九项原生校验；CBS 应成功，第二次构建不应出现对象编译、链接或外部 configure/build/install/record。若此前有未构建变更或另行切换功能，先完成该迁移再记录无变化轮。仅因读取新的 CMake 辅助文件不应重新编译对象。记录配置/生成耗时，避免混入 backend 或主工程构建时间；已有 pybind11、可选 Python 包缺失或 h5py/HDF5 不匹配提示按原政策判断。

| 验收项 | 状态 | 记录 |
| --- | --- | --- |
| 同轮复用、批量查询、故障隔离与输入变化夹具 | 通过 | 22 组新检查及 27 组相关已有回归；无真实编译 |
| 当前机器 bootstrap 同时选择两个系统 | 通过 | 四项 AVAILABLE、两项 OTHER HOST，必需与可选依赖身份正确 |
| 当前机器仅 GAMBIT 过滤 / 只列注册项 | 按需补齐 | 新夹具已通过；本次未提供对应真实日志 |
| 当前环境两次配置与 CBS 增量构建 | 通过 | 配置 5.3/4.3 秒、生成 0.6/0.4 秒；每轮只有 42 条目标完成输出，无编译/链接/外部步骤 |
| 真实安装/移除 Python 模块后恢复及其他平台 | 按需补齐 | 新进程恢复已有模拟检查；不改变当前包安装 |

#### CFG-04 当前 macOS LLVM 验收（2026-10-11）

附件 `/Users/p.zhu/.codex/attachments/b49c4c41-5ec0-4704-869d-be2e6d400cdb/Pasted text.txt` 共 924 行逻辑记录（最后一行没有换行，`wc -l` 为 923）。同时选择 GAMBIT/CBS 的只读 bootstrap、两次 `cbs-llvm` 配置与 CBS `-j8` 构建均完成，无新增错误。

- 第 12–100 行 bootstrap：GAMBIT/CBS 的 LLVM 和 AppleClang 四项 AVAILABLE，两个 GNU 条目为 OTHER HOST；Python 3.13.13/PyYAML、OpenMP、Boost、Eigen、GSL、HDF5、Python 开发库及 Rivet/Contur 必需条件被找到。两系统使用相同 Clang 22.1.8 / GNU Fortran 15.2.0；AppleClang 21.0.0 仅为独立的 macOS profile。ROOT 6.40.00、SQLite CLI 3.54.0 等与实际配置一致。
- 第 401–412 与 813–824 行所有原生验证保持 PASS，CBS 环境 READY；两轮都没有 `Validation:` 输入刷新。只读真实 cache 显示九项结果均为 1、签名均为完整 SHA256，未发现 `GAMBIT_PROCESS_PROBE_*`、`GAMBIT_PYTHON_MODULE_*` 或元数据探测的持久缓存键，符合仅在本进程复用的设计。
- 第 468–470 与 880–882 行：配置 5.3/4.3 秒，生成 0.6/0.4 秒；编译器、Python、C++17、ROOT、ccache、共享 build 和可选功能身份稳定。日志没有 bootstrap/独立探测或 CBS 总耗时，不填写查询次数或提速比例。
- 第 471–512 与 883–924 行每轮各 42 条 Built target 输出，均零对象编译、零链接、零外部 configure/build/install/record 和构建阶段代码生成。`check-rebuild-*` 仅完成轻量输入检查；Rivet/Contur 和 FastJet/Contrib 均复用已有产物。
- h5py 所用 HDF5 2.0.0 与工程 HDF5 1.10.11 不匹配，保留原生相关功能禁用策略；这里的 2.0.0 是 HDF5 库版本。PyYAML/Cython/configobj/pandas/matplotlib 被找到，Rivet/Contur 保持 enabled。可选 scanner Python 模块/库与 WSTP libuuid 缺失、两处 pybind11 弃用提示，以及配置阶段的 `Updated ScannerBit/CMakeLists.txt`，均在上一份 CFG-03 日志中已存在；此次没有因此增加编译工作。

核对已部署的十六个文件与通过脚本测试的版本完全一致，`git diff --check` 通过；没有执行工程配置、编译器或构建。当前环境验收通过，已提交为 `f981c115cf`。仅 GAMBIT/--list 的真实运行、真实包安装变动和其他平台按需补齐，不将夹具结果计为这些真实场景的验收。

### CFG-05 实施与验证

2026-10-11 基于 CFG-04 提交 `f981c115cf` 实现，状态为 **已实现已构建**；维护者当前 macOS LLVM 首次迁移及第二轮无变化 CBS 构建通过，已提交为 `2b258bb609`。实际工程配置、编译器探测及构建由维护者执行。

- 只读核对当前生成文件：CBS_objects 的 SDK/minimum 由全局 flags 和 CMake 各加入一次，OpenMP 由全局 flags 和 imported target 各加入一次。缓存显示 `-fopenmp=libomp`，实际普通变量却使用 `-Xclang -fopenmp`。GNU Fortran 的 `CMAKE_Fortran_SYSROOT_FLAG` 和 `CMAKE_Fortran_OSX_DEPLOYMENT_TARGET_FLAG` 均为空，fortran/FarrayTest 对象编译没有公共 minimum，解释了此前对象 28.0 与链接 27.0 的警告。静态阅读本机 CMake 4.4.2 的 Apple-GNU-Fortran/Apple-GNU 模块确认：这两个选项由 GNU help 文本匹配决定，本轮没有执行该查询或编译器。
- `OpenMP.cmake` 合并两个 Homebrew 检测入口，要求三种启用语言分别被 FindOpenMP 找到，移除盲目追加 Fortran `-fopenmp` 的回退。自动 C/C++ cache hints 与实际加入 native flags 的结果一致；精确匹配旧自动 bundle 时迁移一次，记录自有 hints，用户更改或其他手动 hints 保留。Fortran 仍使用其独立发现的 flags/runtime；原 Homebrew LLVM runtime 检查保留，并从选中的库派生 YODA 搜索/rpath。
- 原生 C/C++ SDK/minimum 由 `CMAKE_OSX_*` 提供，不再手动加入全局 flags。GNU Fortran 仅对 CMake 未提供的两项分别补齐。公共最低版本仍只有 `MACOS_DEPLOYMENT_TARGET`；显式 compiler/linker flags 中的冲突 SDK/minimum 明确报错，允许相同版本写法及 SDK 软链接。保留 dynamic_lookup 与 SDK lib 搜索路径。
- shell/Autotools 的 backend flags 和四种 C dialect flags 导出公共 SDK/minimum；手写共享链接命令改用派生 linker flags。七处外部 CMake recipe 使用公共 CMake 参数，去除额外的公共 flags，保留 package 标准、include、警告及其他链接选项；补齐 GreAT/Minuit2 的公共 deployment 参数。CalcHEP 沿用无 build-type 优化的 Fortran flags，避免顺带改变优化级别。
- GAMBIT/CBS executable 使用 FindOpenMP 的显式 library list，避免再次继承 imported target 的编译选项；有旧 target/manual hint 的兼容分支仍保留。原生校验签名加入语言平台标志，CBS 摘要列出语言 OpenMP flags/libs 与公共 SDK/minimum。

无构建验证：平台/OpenMP 18 组、SDK 10 组、validation cache 17 组、standalone objects 6 组、contrib retention 5 组、FastJet/Contrib identity 11 组、外部自动重建 11 组，共 **78 组**；C++ 政策另外 **30 项**通过。新增检查使用真实 CMake policy/helper 及 recipe 参数、模拟 FindOpenMP/只读 Homebrew 查询；验证旧缓存迁移、跨脚本进程自有 hint 更新、用户修改保留、两种 Clang profile、缺少语言失败、GNU Fortran fallback/平台已支持时不重复、空格路径、冲突 minimum/SDK 与七处外部参数。新增 Fortran 平台标志局部失效和 executable/object runtime 继承检查。夹具没有实际工具查询、工程配置或编译，不替代真实平台验收。

手动验收保持当前 `cbs-llvm`、SDK 和依赖选项，**保留 build，不 clean，不 --fresh**。本阶段改变命令 flags，第一次可能较多重编译并迁移 FastJet/HepMC/Rivet 等外部包；validation 签名更新也可能使九项检查重跑一次。完成迁移后再判断增量稳定性。

```sh
cd /Users/p.zhu/Gambit-Workshop/worktree/cbs-presets
set -o pipefail
cmake --preset cbs-llvm 2>&1 | tee /tmp/cbs-cfg05-configure-1.log
rg -n '^(MACOS_DEPLOYMENT_TARGET|CMAKE_OSX_SYSROOT|CMAKE_OSX_DEPLOYMENT_TARGET|OpenMP_(C|CXX|Fortran)_FLAGS):' build/CMakeCache.txt
rg -n -- '-isysroot|-mmacosx-version-min|-fopenmp|libomp' build/CMakeFiles/CBS_objects.dir/flags.make build/Backends/CMakeFiles/fortran.dir/flags.make build/Backends/CMakeFiles/FarrayTest.dir/flags.make build/CMakeFiles/CBS.dir/link.txt
cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-cfg05-build-1.log
cmake --preset cbs-llvm 2>&1 | tee /tmp/cbs-cfg05-configure-2.log
cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-cfg05-build-2.log
```

当前环境期望 SDK/minimum 保持 27.0，工具链保持 LLVM 22.1.8/GNU Fortran 15.2.0，环境 READY。OpenMP cache 与摘要均为 `-Xclang -fopenmp` 加 libomp include；CBS_objects 的 OpenMP、SDK/minimum 各出现一次，CBS 链接仍有选中的 libomp。Fortran/FarrayTest 对象编译出现公共 `-mmacosx-version-min=27.0`，补齐 SDK 选项；首次重编后的本项目 Fortran 对象不应再报告以 28.0 构建。依赖库自身的 minimum 必须另行核对，不把该修复理解为重写已有第三方二进制。

两轮 CBS 都应成功。第二轮签名稳定时不再重检原生校验，构建不应出现对象编译、链接或重复外部 configure/build/install/record。若首次迁移未完成，先处理具体错误再重复构建，不通过清空 build 隐藏原因。记录两轮日志及 flags/cache 输出；单次迁移耗时不计作正常 no-op。

| 验收项 | 状态 | 说明 |
| --- | --- | --- |
| 78 组脚本夹具、C++ 30 项 | 已通过 | 模拟 package/tool 结果，无工程构建 |
| 当前 macOS LLVM 的 flags/cache/摘要与 Fortran 对象 minimum | 已通过 | 缓存与摘要一致，native 参数各一份；两个 Fortran 对象、相应库及 CBS 的 Mach-O minimum 均为 27.0 |
| 首次 CBS 迁移与第二轮无变化 configure/build | 已通过 | 两轮 CBS 成功，首次九项重检与外部迁移完成；第二轮零编译/链接/外部步骤 |
| 真实 AppleClang/GNU 其他平台、手动 OpenMP 配置与其他 SDK | 按需补齐 | 夹具通过不计作真实构建通过 |

#### CFG-05 当前 macOS LLVM 验收（2026-10-11）

附件 `/Users/p.zhu/.codex/attachments/6dd59e0d-e531-48ab-ad60-5335f8153b97/Pasted text.txt` 共 3690 逻辑行（最后一行没有换行，wc 为 3689），依次为两次相同 `cbs-llvm` 配置和 CBS `-j8` 构建；第 3272 与 3690 行均成功完成 CBS。

- 第 55 行只出现一次旧 Homebrew OpenMP hints 迁移；首轮第 65、290–297 行共九项 validation 输入刷新，全部 PASS/READY，第二轮没有 hints 迁移或 validation 刷新。C/C++ flags 为 `-Xclang -fopenmp` 加 libomp include，library 指向 Homebrew libomp；Fortran 保持 GNU `-fopenmp` / libgomp。SDK/minimum 仍 27.0、LLVM 22.1.8/GNU Fortran 15.2.0、C++17/ROOT 6.40.00、Python 3.13.13、ccache 4.13.6 与既有配置一致。
- 首轮配置 9.2 秒、生成 0.6 秒；第二轮配置 6.1 秒、生成 0.6 秒。日志未给出总构建时间或 ccache 命中增量，不据此填写构建提速比例。
- 第 395–3272 行完成命令迁移：362 条 CMake 对象构建输出，其中主工程/内嵌 contrib 342 条（C++ 339、Fortran 2、C 1），HepMC 外部 CMake 20 条；另有 Autotools 的编译输出，不包括在此计数内。共 19 条 ExternalProject configure/build/install 步骤，FastJet/Contrib 按新身份准备、重建并记录成功状态，HepMC/YODA/RestFrames、nulike/Rivet/Contur 的相关迁移完成。此轮为 flags 改变后的必要迁移。
- 第 3649–3690 行恰好 42 条 Built target 输出，零对象编译、零链接、零外部 configure/build/install/record 或构建阶段代码生成；第二轮 FastJet/Contrib 与三项 source-state 检查稳定复用。
- 只读核对当前 cache、native flags、CBS 链接及 HepMC 外部命令：OpenMP cache 与摘要/实际 flags 一致；CBS_objects、CBS link 和 HepMC 的 SDK/minimum/OpenMP 各为一份。HepMC recipe 的 flags 无手工 SDK/minimum，仍通过公共 CMAKE_OSX 参数取得相同 27.0 SDK/minimum。GNU Fortran 两个 CMake 平台标志仍为空，但对象与链接 flags 已各补齐公共选项。
- 直接用 Python 标准库读取 Mach-O load commands，未调用编译器或系统工具：`libfortran.f90.o`、`libFarrayTest.f90.o`、对应的两份 `.so` 及 CBS 的 LC_BUILD_VERSION minimum 均为 27.0.0；链接产物 SDK 均为 27.0.0。日志已无对象 28.0 / 链接 27.0 警告，确认修复体现在真实产物中。
- 仍有非阻断警告：pybind11/HepMC 的 CMake 弃用、HepMC 的 sprintf 弃用、已有 macOS 链接选项及重复 -ldl 提示；HepMC 两条 Ignoring extra path 在 CFG-02 的验收日志中已存在。第 1873–1876 行 Fortran 提示 FastJet include 暂不存在，发生在 FastJet 首次清理/安装期间；这两份示例源码不使用 FastJet 头，编译成功，迁移结束后两个 include 目录均已恢复。外部 Rivet Python 构建器合并多组 flags 时仍重复相同的 SDK/minimum，未出现冲突，未计作本阶段已消除的 native/CMake recipe 重复项。全局 include 范围和外部构建器参数清理可按后续优化项处理。

十六个已部署文件与通过 78 组脚本夹具及 C++ 30 项的版本逐一一致；本轮仅更新验收台账，`git diff --check` 通过，没有代维护者运行 configure/build 或真实编译器探测。当前环境验收通过，已提交为 `2b258bb609`；其他编译器 profile、平台、SDK 及真实手动 OpenMP 配置仍按需补齐。

### UX-01 实施与验证

2026-10-11 基于 CFG-05 提交 `2b258bb609` 实现，状态为 **已实现已构建**；当前 macOS bootstrap 提示及 CBS 无变化构建通过，已提交为 `88346e66ba`。本阶段统一 bootstrap 和 README 的构建示例，不改变 preset 的构建参数或依赖策略。

- 所有 AVAILABLE preset 的构建提示使用 `cmake --build --preset <name> --parallel 8`，提示按 CPU 和内存调整数字；README 的 GAMBIT/CBS 示例一致。
- `--parallel 8` 与 `-j8` 是同一选项的完整与简写形式，性能与构建行为相同；维护者此前使用的 `-j8` 已满足明确并发要求。无数字的 `--parallel` 由原生构建工具决定任务数，Make 下可能无上限。
- README 补充 `CMAKE_BUILD_PARALLEL_LEVEL=4 cmake --build --preset cbs-llvm` 示例：省略命令行并发选项时使用该环境默认值，显式选项优先。数字只限制构建任务并发，不是所有程序内部线程的全局上限；改变数字无需清空 build 或重新配置。

无构建验证：使用真实报告 helper 纯渲染全部 **15 个**注册的公开 preset，逐条确认 build 提示为 `--parallel 8`、配置提示保持原值、资源调整说明存在；README 所有 `--parallel` 构建命令均带明确数字。临时脚本禁止进程查询，没有调用真实发现流程、编译器或工程 configure/build。当前 Makefile 的配置依赖未引用这三个文件，修改不改变现有编译命令；真实增量结果由维护者验收。

在现有 `cbs-llvm` 配置上运行以下命令，保留 build，不 clean，不 --fresh；本阶段无需重新配置：

```sh
cd /Users/p.zhu/Gambit-Workshop/worktree/cbs-presets
set -o pipefail
./cmake/bootstrap --system gambit --system cbs --verbose 2>&1 | tee /tmp/cbs-ux01-bootstrap.log
cmake --build --preset cbs-llvm --parallel 8 2>&1 | tee /tmp/cbs-ux01-build.log
```

bootstrap 的 AVAILABLE 构建提示应明确包含 `--parallel 8` 和资源调整说明。CBS 应成功；若源码、配置和依赖输入没有其他变化，继续零对象编译、零链接和零外部 configure/build/install/record。可继续使用原来的 `cmake --build build --target CBS -j8`；它与上述 preset 命令构建相同 CBS 目标，验证长写法不需要重置目录。记录真实日志后更新验收状态。

#### UX-01 当前 macOS 验收（2026-10-11）

附件 `/Users/p.zhu/.codex/attachments/4a613fd7-9801-445f-a6f9-7335a9134af9/Pasted text.txt` 共 137 逻辑行（最后一行没有换行）。GAMBIT/CBS 的 LLVM 与 AppleClang 四项 AVAILABLE，GNU 两项 OTHER HOST，环境发现正常；第 75 行资源调整说明和四项 `--parallel 8` 提示均正确。第 96–137 行恰好 42 条 Built target 输出，最终 CBS 成功，零对象编译、零链接及零外部 configure/build/install/record，没有新增错误或警告。本项只是修正提示中未明确的并发数，原来的 `-j8` 已正确，不记录提速比例。当前环境验收通过，已提交为 `88346e66ba`。

## 下一轮实施与构建验收

1. C++ 修改及 BUILD-01 已提交；当前 LLVM/ROOT 17 配置和 CBS 构建已有日志，继续按需补齐其他标准、冲突拒绝及运行场景。
2. CFG-01 提交为 `cf10364f98`，11 组脚本夹具、当前 LLVM 显式/缓存配置及两次无变化 CBS 构建通过；真实 bootstrap、多版本及其他平台按需补齐。CFG-02 的 26 组脚本检查、当前 SDK 配置、外部迁移及两次无变化构建通过，已提交为 `4dad77208a`；其他 SDK/平台按需补齐。CFG-03 的 16 组缓存夹具、C++ 政策 30 项和当前环境首次/重复配置及两次 CBS 无变化构建通过，已提交为 `35e6a4e73e`；只清签名、真实依赖失败恢复和其他平台按需补齐。CFG-04 的 22 组无构建夹具、相关已有回归、当前 macOS 双系统 bootstrap、两次配置和 CBS 无变化构建通过，已提交为 `f981c115cf`；CFG-05 的 78 组脚本夹具与 C++ 30 项、当前 macOS LLVM flags/cache/实际 Mach-O minimum、首次迁移及第二轮 CBS 无变化构建通过，已提交为 `2b258bb609`；其他 SDK/profile/平台按需补齐。BUILD-01 的额外恢复场景按需补充。
3. BUILD-03 已提交为 `0965735828`；按需补齐命中增量和 OFF/AUTO 实测。BUILD-04 已提交为 `1d46bf0439`，HepMC/YODA 场景按需补齐；BUILD-05 首次迁移及相同配置复用已通过并提交为 `09929f07fb`；BUILD-07 首次记录、直接重复构建及相同配置后复用已通过并提交为 `0c3ea3e566`；时间戳对照、源码 touch 和其他平台按需补齐。BUILD-06 Ninja 适配按维护者选择暂缓。
4. BUILD-02 独立对象构建、完整链接及无变化主工程构建已通过；继续补齐并行重叠与单点运行，以同环境基准量化收益，结合 BUILD-07 的验收日志测量外部步骤重复开销。
5. BUILD-08 RestFrames 阶段已完成 include/配置头范围收敛；preload 漏查已修复，维护者首次迁移、恢复 ON 六个对象及最后无变化构建通过，已提交为 `eb03406a7c`。后续按需补齐迁移后独立 OFF、时间戳及其他平台，再处理其他依赖与配置发现项；Ninja 适配暂缓。
6. UX-01 已提交为 `88346e66ba`。BUILD-08 的 ONNX 专用头/include 与两包 RPATH 范围已实现，27 组脚本检查、首次迁移和 CBS 启动通过，已提交为 `52aaf8434f`；补齐真实 OFF/ON、快照与无变化 CBS 验收，然后按下方整体验收矩阵推进。UX-02 按维护者选择后续推进，Ninja（BUILD-06）与 lld 迁移暂缓。

维护者于 2026-10-12 明确选择继续 Unix Makefiles 和当前平台链接器，Ninja 与 lld 迁移暂缓；只有明确要求重启或出现相关实际问题时再评估。只读核对确认当前 build 使用 `Unix Makefiles`，缓存链接器为 `/usr/bin/ld`；仓库 preset 未强制 Ninja 或 lld。保留 ccache 的通用 generator 能力判断，不增加 generator 或链接器切换。本轮 BUILD-08 验收继续使用现有 `cbs-llvm` 和 `-j8`。

本台账不改变仓库构建政策：继续使用 `${sourceDir}/build`；切换编译器家族按 `AGENTS.md` 使用 `--fresh`；实际构建由维护者执行。变更 profile、关闭依赖与重置缓存的影响应单独记录，避免把额外重建误认为编译回退。

### Preset 系统整体验收阶段

当前 macOS `cbs-llvm` 的构建、无变化及 ONNX/RestFrames 四次开关验收已通过，可以冻结本轮构建改动并进入交付收尾。交付范围为现有 Unix Makefiles、LLVM 与依赖环境；CBS 物理运行、新环境完整构建及其他 preset/工具链分别保留验收记录。

| 验收范围 | 当前证据 | 下一步与通过标准 |
| --- | --- | --- |
| 当前 macOS cbs-llvm 配置、并行完整构建与启动 | 本轮首次迁移成功，--help 正常，实际 ONNX include/依赖及两包 RPATH 正确 | 固定工具链、ROOT、SDK 和并发，保存配置摘要与日志 |
| ONNX/RestFrames 开关与编译范围 | 27 组范围检查和 14 组入口夹具通过；真实四次开关和最终 no-op 均 PASS | 当前环境已通过：三个/六个必要对象、正确链接/RPATH、95 个文件快照稳定及 CBS 启动；复验可使用下方入口 |
| 无变化配置/构建和单文件增量 | 当前直接 no-op 与相同配置后 no-op 均通过；之前阶段已有源码 touch 日志 | 直接重复构建、相同配置后构建均零编译/链接/外部步骤；touch 单个分析和 CBS 源码仅重编译必要对象并链接 |
| 依赖复用与缺失诊断 | 当前外部安装复用；发现/缓存/缺失输入有脚本夹具 | 按需补齐真实缺失依赖诊断、缺产物恢复及外部源码 touch，只让所属依赖及必要下游重建 |
| CBS 功能运行 | --help 只覆盖启动与直接动态依赖加载 | 用已有有效 YAML 完成小规模单点运行，检查后端接口、输出及所选分析；物理结果验收单独记录 |
| 新环境完整构建 | 当前验证使用已有外部安装，不能算全冷构建 | 在独立工作树或测试机器从标准依赖环境完成配置、下载、生成和 -j8 构建；保留当前工作树 build，每个工作树仍使用其共享 build/ |
| 其他工具链与 profile | 本轮 macOS LLVM CBS 不覆盖其他矩阵 | AppleClang CBS、Linux LLVM/GNU、完整 GAMBIT 与 DarkBit 按各自支持范围分别验收，切换编译器家族使用 --fresh |
| 文档与开发体验 | DOC-01 政策与 DOC-02 示例已提交为 `eeaf63d5ef`；UX-02 有后续增强 | 文档、验收与交付按 AGENTS.md 的共享 build/ 政策；compile_commands 等增强按需推进 |

Ninja 和 lld 继续按维护者选择暂缓。验收状态按上述范围分别记录，只有完成对应场景才将其标为通过。

### 当前 cbs-llvm 的下一轮验收命令

DOC-01/DOC-02 提交 `eeaf63d5ef` 只涉及文档和示例，构建 preset、工具链和源代码保持 `52aaf8434f` 基线；不需要清空 build。以下首次迁移后直接 no-op 和相同配置后的 no-op 已通过，保留命令供复验：

```sh
cd /Users/p.zhu/Gambit-Workshop/worktree/cbs-presets
set -o pipefail
cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-acceptance-direct-noop.log
cmake --preset cbs-llvm 2>&1 | tee /tmp/cbs-acceptance-reconfigure.log
cmake --build build --target CBS -j8 2>&1 | tee /tmp/cbs-acceptance-reconfigure-noop.log
```

两次 CBS 均应成功，零对象编译、零链接、零外部 configure/build/install/record；相同配置的公共头与编译命令应稳定。然后执行上方 BUILD-08 的四次 OFF/ON 与 hash/mtime 快照验证，已有命令无需重复首次迁移。实际编译与运行由维护者执行，代理核对日志和生成文件。

#### 2026-10-12 当前 cbs-llvm 无变化验收

维护者反馈两次构建都很快完成。进一步只读检查其保存日志：`/tmp/cbs-acceptance-direct-noop.log` 和 `/tmp/cbs-acceptance-reconfigure-noop.log` 均为 42 行，全部为目标完成输出，CBS 均成功，零对象编译、零链接、零外部步骤和构建阶段生成。`/tmp/cbs-acceptance-reconfigure.log` 为 377 行，配置/生成分别 6.0/0.6 秒，摘要 PASS/READY，没有重检提示或配置错误。未记录总构建耗时与 ccache 命中增量，不填写提速比例。

当前 ON 状态的直接重复构建与相同配置后重复构建已验收。随后维护者执行下方入口，另外补齐四次 OFF/ON、跨开关 hash/mtime 快照与恢复 ON 后最后 no-op；两类证据分别记录。

#### BUILD-08 开关验收入口

基于 `eeaf63d5ef` 新增 [cbs_feature_acceptance.py](../cmake/scripts/cbs_feature_acceptance.py)，把前述手动四次开关与快照检查整理为维护者运行的一条命令。当前状态为 **已实现已构建**，维护者已完成真实四次开关及最终无变化验收，入口与记录随本轮提交。

```sh
cd /Users/p.zhu/Gambit-Workshop/worktree/cbs-presets
python3 cmake/scripts/cbs_feature_acceptance.py --run --jobs 8
```

前置条件是当前 macOS `cbs-llvm`、Unix Makefiles、两项开关 ON、首次迁移已完成，RestFrames 1.0.2 和 ONNX Runtime 1.14.1 的安装仍在。保留共享 `build/`，不 clean 或 --fresh；期间不编辑源码，也不并行执行另一次配置或构建。

入口按 ONNX OFF、ONNX ON、RestFrames OFF、RestFrames ON 顺序显式设置两项开关，核对缓存、专用头、CBS 链接项及所属 RPATH；要求原有工具链、ROOT、Python、SDK/minimum 和 profile 身份保持一致。ONNX 每次恰好编译三个对象并链接 CBS；RestFrames 每次恰好编译六个对象并链接 gambit_preload 和 CBS。每轮 `CBS --help` 应正常输出 Usage；最后重复构建要求零对象、零链接、零生成或外部步骤。

公共配置头、九个目标 flags、五个共享库 link 命令及两包安装头/库记录内容 SHA-256、纳秒 mtime、大小和解析后的路径。开关后的四份快照和最终无变化快照均与初始快照比较。默认在系统临时目录创建唯一的新日志目录，开始和结束均打印路径；可用 `--log-dir /tmp/cbs-feature-check` 指定尚不存在的目录。目录包含每步 configure/build/loader 日志、快照和 `summary.json`，摘要记录通过场景、命令耗时及失败原因；现有日志目录不会覆盖。

只有 `--run` 才执行真实命令，默认调用只打印帮助。失败立即停止并返回非零，保留日志和已完成场景，不自动继续或恢复；此时可能留下某项 OFF，终端会打印恢复两项 ON 的配置及构建命令。全部通过后两项恢复 ON，摘要为 PASS。`--help` 仅验收启动和直接动态依赖，ONNX 推理、RestFrames 分析及物理运行仍单独验收。

无构建检查：新增 [cbs_feature_acceptance.py 夹具](../cmake/tests/cbs_feature_acceptance.py) 的 **14 组**通过，使用临时树和捕获命令，未执行任何真实 CMake、构建或 CBS。覆盖完整顺序/恢复及报告、前置条件拒绝、意外对象/重复链接/外部步骤/生成、安装内容/mtime/删除、显式用户 RPATH、错误或损坏专用头、失败退出和停止、工具链改变、日志保护、无关 link 变化、启动输出缺失及最终 no-op 仍有工作。进程退出检查仅运行打印后退出的 Python 夹具，默认帮助检查也仅运行 Python。

对当前真实文件只读核对：两项 ON、95 个快照文件连续读取一致、实际专用头消费者分别三个和六个；两份已验收的 no-op 日志由新解析器确认零编译/链接/外部步骤。该只读核对与维护者真实开关结果分别记录，后者见下节。

#### 2026-10-12 四次开关与最终无变化验收

维护者执行 `python3 cmake/scripts/cbs_feature_acceptance.py --run --jobs 8`，附件为 `/Users/p.zhu/.codex/attachments/8049895f-e0fe-49fe-9655-52dea35216de/Pasted text.txt`（1814 行），日志目录为 `/var/folders/rz/jq3y3vy92s1b_6fsw7wvs6k40000gn/T/cbs-feature-acceptance-85qv5gos`。只读重新检查实际五份 build 日志、四份 loader 日志、summary 和五份快照，全部符合入口的预期。

| 场景 | 对象编译 | 链接 | build 命令墙钟秒 | 结果 |
| --- | --- | --- | --- | --- |
| ONNX OFF | 3 | CBS | 3.508 | PASS |
| ONNX ON | 3 | CBS | 2.071 | PASS |
| RestFrames OFF | 6 | gambit_preload、CBS | 3.359 | PASS |
| RestFrames ON | 6 | gambit_preload、CBS | 1.975 | PASS |
| 最后无变化构建 | 0 | 0 | 1.529 | PASS |

四次开关及最后一次构建均没有额外生成或外部 configure/build/install/record 步骤；公共配置头、九个目标 flags、五个共享库 link 命令及两包安装头/库合计 95 个文件，与初始快照的 SHA-256、mtime_ns、大小和解析路径均一致。四次 CBS `--help` 正常，缓存/专用头/链接项/RPATH 与每轮开关一致；最终两项均 ON，工具链、ROOT、SDK/minimum、Python 与 profile 身份保持一致。

耗时来自入口的 `time.monotonic()`，包含命令启动和日志输出，测量环境使用已有安装与 ccache；不用于推定冷构建性能或 ccache 命中增量。当前 macOS 构建基线可进入交付收尾。有效 YAML 的小规模实际运行、新环境与其他平台保持单独待验收；Ninja/lld 继续暂缓。代理此次只读取维护者结果及做静态检查，没有执行工程配置、构建或 CBS。

#### DOC-01/DOC-02 验收准备记录（2026-10-12）

- 工程标准升至 1.1：删除每个 preset 独立 binaryDir 及无需 --fresh 切换的旧约定；第 1/4/5/11/12/13/14/15/16/17 节均按共享 build/ 政策同步。独立工作树用于隔离真实构建，未来 manifest 记录当前配置，源码树中现有外部包状态继续按迁移项处理。
- 静态解析当前 15 个公开 preset（GAMBIT 3、CBS 3、DarkBit 9），检查 inheritance、共享 binaryDir、输出设置、profile/toolchain identity、工具链文件、主机条件和最终构建目标，均通过。
- 实际 bootstrap 注册列表及 GAMBIT/CBS/DarkBit 三种筛选均通过；未知 preset 和不相交筛选按预期退出 1。使用 --list，仅读取注册与主机条件，没有执行环境探测、配置或编译。
- 在临时目录复制 HPC 示例为 CMakeUserPresets.json，原生 cmake --list-presets=all 同时列出 gambit-hpc 的 configure/build；临时 CMakeLists 放置失败哨兵未触发，没有创建 build/。示例继承 GAMBIT 共享目录和构建目标，保持原有内容；随本轮提交纳入版本控制，真实模块环境与 HPC 构建未测试。
- 文档引用、JSON/shell 片段及差异检查通过；本轮仅文档准备，未由代理执行工程配置、编译或 CBS。其他本地分析验证文档、模板及 report.txt 不纳入本轮。

### C++ 构建验收矩阵

| 场景 | 预期 | 实测记录 |
| --- | --- | --- |
| 当前 macOS LLVM，AUTO，ROOT 17 | 主工程、ROOT 及通用 backend 参数为 C++17 | 当前配置/CBS 构建通过：摘要跟随 ROOT 为 17，CBS 与 CBS_objects 的生成 flags 均为 `-std=c++17`；外部包实际命令未逐项核对 |
| 显式 C++17，ROOT 17 | 配置和编译成功，摘要显示显式请求 | 待执行 |
| 显式 C++20，ROOT 17 | 配置阶段报告冲突及可用修复方式 | 待执行 |
| 显式 C++20/23，ROOT OFF | ROOT 保持关闭；编译器支持相应模式时主工程使用请求标准 | 待执行 |
| 从 17 切换到 20 或改变相关 flags | C++ 检查结果重新计算，摘要更新 | 待执行 |
| AppleClang 与 Linux GNU/LLVM | 按各环境实际具备的工具链和 ROOT 重复验证 | 待执行 |

以下命令供维护者在目标仓库根目录执行；同一工具链下可先验证现有 C++17 配置：

```sh
cmake --preset cbs-llvm -DCMAKE_CXX_STANDARD=17
cmake --build --preset cbs-llvm --parallel 8
```

恢复自动标准选择使用 `-U CMAKE_CXX_STANDARD`，同时移除 legacy flags 中的显式标准。切换编译器家族仍需 `--fresh`。

### 性能记录要求

每次对比记录 Git 提交或工作树版本、preset、CMake/generator、编译器版本、标准、ROOT 版本、并发数、后端裁剪范围、外部依赖状态和 ccache 冷热状态。至少分别比较以下场景：

| 场景 | 重点观察 |
| --- | --- |
| 相同配置重复构建 | 是否有无变化文件重新生成、编译或链接 |
| 无变化重新配置后构建 | BUILD-01 是否消除了无效重编译 |
| 只修改单个分析文件 | 重编译范围是否收敛到必要目标 |
| 修改 CBS 自身源码 | 缓存和 CBS 编译依赖关系是否符合预期 |
| 受控的完整构建 | 总耗时、`solo.cpp` 起止时间、峰值内存和外部包耗时 |

验收时将实际命令、日志位置、结果、耗时和提交号补回对应条目。未经同条件测量，不填写预计提速百分比。

## 更新记录

| 日期 | 更新 |
| --- | --- |
| 2026-10-10 | 建立台账；登记已合入基础、C++ 标准修复与 37 项脚本检查，整理构建、配置、文档待办及后续验收矩阵 |
| 2026-10-10 | 实现 BUILD-01；记录六组脚本回归、增量构建验收命令和时间戳检查，真实构建及性能收益待维护者验证 |
| 2026-10-10 | 维护者反馈 BUILD-01 测试已完成，重新编译及 touch 后重新编译都很快；状态更新为已实现已构建，定性反馈已登记，尚未记录具体耗时或日志 |
| 2026-10-10 | 将 C++ 标准、BUILD-01 和台账提交为 `a3b3cc87c7`；实现 BUILD-02，登记五组 standalone 注册回归及维护者构建验证步骤，尚未提交 BUILD-02 |
| 2026-10-10 | 审阅维护者 508 行构建日志及当前生成文件；确认 BUILD-02 独立对象构建、编译上下文、完整链接和无变化主工程构建通过；登记 BUILD-07 外部步骤重复进入，实际并行重叠、计时及单点运行仍待验收 |
| 2026-10-10 | 提交 BUILD-02 程序对象拆分、五组脚本回归及维护者日志验收记录；父提交为 `a3b3cc87c7`，后续按 BUILD-03 接入可选编译缓存 |
| 2026-10-10 | BUILD-02 提交为 `957c81ecd9`；实现 BUILD-03 可选 ccache 与两类摘要，记录七组策略检查和命中/关闭验收步骤；BUILD-03 尚未提交 |
| 2026-10-10 | 审阅维护者 195 行日志：ccache 编译 solo_cli.cpp 和完整 CBS 链接成功；登记全局 64 次命中及单快照限制，提交 BUILD-03 后继续 BUILD-04 |
| 2026-10-10 | BUILD-03 提交为 `0965735828`；实现 BUILD-04 RestFrames/HepMC/YODA 停用保留及显式清理入口，记录五组夹具检查和实际开关/复用验收流程；BUILD-04 尚未提交 |
| 2026-10-10 | 审阅 BUILD-04 的 1125 行日志：RestFrames OFF 后库保留、恢复复用及完整 CBS 构建通过；区分 301 条 C++ 对象构建与外部依赖重建，新增 BUILD-08 评估项，并补充 CFG-05 的 Fortran minimum target 不一致证据；尚未提交 |
| 2026-10-10 | 维护者补充恢复配置后的 CBS -j8 无变化日志：无原生对象编译、链接及代码生成，主工程增量验收通过；nulike/Rivet/Contur 包装步骤仍重复进入，继续跟踪 BUILD-07；BUILD-04 尚未提交 |
| 2026-10-11 | BUILD-04 提交为 `1d46bf0439`；实现 BUILD-05 FastJet/Contrib 实际文件与构建身份校验、构建阶段干净准备及成功安装后记录；11 组新夹具和五组保留检查通过，真实构建待维护者验收；BUILD-05 尚未提交 |
| 2026-10-11 | 维护者日志确认 BUILD-05 首次迁移、成功安装记录、相同配置复用及完整 CBS 构建通过；安装记录只读比对通过；开始处理 BUILD-07，直接重复构建/时间戳与其他平台待补齐 |
| 2026-10-11 | BUILD-05 提交为 `09929f07fb`；实现 BUILD-07 三包输入/产物检查和成功安装后记录，11 组脚本夹具通过，当前安装只读扫描稳定；真实构建待维护者验收，BUILD-07 尚未提交 |
| 2026-10-11 | 审阅 BUILD-07 的 889 行日志：三包首次成功记录、直接重复构建及相同配置后跳过重复步骤均通过；三次 CBS 成功，无原生编译/链接；成功记录及生成命令只读比对通过，随本轮提交；touch/时间戳及其他平台待补齐 |
| 2026-10-11 | BUILD-07 提交为 `0c3ea3e566`；实现 BUILD-08 第一阶段 RestFrames PRIVATE include 与专用配置头，七组脚本检查通过；首次迁移、真实 OFF/ON 及无变化构建待维护者验收，尚未提交 |
| 2026-10-11 | BUILD-08 首次 OFF/ON 及重复构建均在 preload 缺失 RESTFRAMES_INCLUDE 处失败；补齐专用头，将使用者审计扩展到全仓库，确认回归检查能抓到遗漏；更新为六个必要对象，真实构建待复测，尚未提交 |
| 2026-10-11 | 审阅 BUILD-08 修复后的 1182 行日志：OFF 完成 288 个对象的首次迁移，恢复 ON 仅六个必要对象，最后零编译/链接/外部步骤，三次 CBS 成功；真实 flags/依赖范围及 17 组脚本检查通过，RestFrames 阶段随本轮提交；迁移后独立 OFF 与时间戳对照仍待补齐 |
| 2026-10-11 | BUILD-08 RestFrames 阶段提交为 `eb03406a7c`；实现 CFG-01 LLVM 显式选择优先级、匹配 companion 与无回退诊断，11 组脚本夹具通过；真实配置及构建待维护者验收，尚未提交 |
| 2026-10-11 | 审阅 CFG-01 的 835 行日志：原 LLVM 显式配置、缓存重配置及两次 CBS 构建通过，均零编译/链接/外部重复步骤；11 组脚本检查与当前缓存/flags 只读核对通过，本阶段随验收提交；真实 bootstrap、多版本及其他平台待补齐 |
| 2026-10-11 | CFG-01 提交为 `cf10364f98`；实现 CFG-02 SDK 优先级、pre-project 初始化、所选 SDK 的初始 minimum 与外部 CMake SDK 参数；26 组脚本检查（SDK 10、retention 5、identity 11）、旧覆盖问题复现及同 SDK flags 对比通过，真实构建待维护者验收，尚未提交 |
| 2026-10-11 | 审阅 CFG-02 的 2433 行日志：显式 SDK、缓存重配置及自动重新发现均成功，首轮 HepMC/Rivet/Contur 迁移后两轮零编译/链接/外部步骤；26 组脚本与真实 SDK/cache/flags 比对通过，本阶段随验收提交；其他 SDK 与平台待补齐 |
| 2026-10-11 | CFG-02 已提交为 `4dad77208a`；实现 CFG-03 统一输入签名、依赖文件指纹、共享 HDF5 gate 恢复及只重检提示；16 组无编译缓存夹具和 C++ 政策 30 项通过，真实配置/增量构建待维护者验收，尚未提交 |
| 2026-10-11 | 审阅 CFG-03 首次/重复配置及两次 CBS 构建日志：首轮恰好九项重检，第二轮复用，均 PASS/READY；两次构建零编译/链接/外部步骤；16 组缓存夹具、C++ 政策 30 项及真实 cache/probe 只读核对通过，本阶段随验收提交，其他场景按需补齐 |
| 2026-10-11 | CFG-03 已提交为 `35e6a4e73e`；实现 CFG-04 同轮只读查询复用和 Python 模块批量导入；22 组新夹具、11 组编译器选择、5 组 contrib 保留及 11 组外部自动重建检查通过；真实 bootstrap/配置/CBS 增量验收待维护者执行，尚未提交 |
| 2026-10-11 | 审阅 CFG-04 的 924 行日志：双系统 bootstrap 四项 AVAILABLE、两项 OTHER HOST；两次配置 5.3/4.3 秒、生成 0.6/0.4 秒，原生检查 PASS/READY 且未刷新；两次 CBS 各 42 条目标完成输出，零编译/链接/外部步骤；旧 h5py/HDF5 不匹配及可选模块/弃用提示沿用；状态改为已实现已构建，尚未提交 |
| 2026-10-11 | 维护者授权提交已验收的 CFG-04，提交为 `f981c115cf`；仅包含本阶段十六个源码、夹具与文档文件，其他未跟踪文件保留；随后开始 CFG-05 |
| 2026-10-11 | CFG-05 统一 OpenMP 自动 hints 与 native flags，原生 C/C++ 去除重复 SDK/minimum，GNU Fortran 补齐未探测选项，外部 shell/CMake flags 由公共政策派生；78 组夹具与 C++ 30 项通过，实际首次迁移及无变化 CBS 构建待维护者验收，尚未提交 |
| 2026-10-11 | 审阅 CFG-05 的 3690 行日志：两轮 CBS 成功，首次九项重检及 native/外部 flags 迁移完成；第二轮 42 条目标输出、零编译/链接/外部步骤；cache 与生成 flags 一致，两个 Fortran 对象/库及 CBS 的 Mach-O minimum 均为 27.0；状态改为已实现已构建，本阶段随本轮验收提交 |
| 2026-10-11 | CFG-05 已提交为 `2b258bb609`；实现 UX-01，bootstrap/README 示例统一明确并发 8，补充 -j8 等价、环境默认值及资源调整说明；15 个 preset 的无探测纯报告渲染与文档命令检查通过，真实提示/CBS 增量验收待维护者执行，尚未提交 |
| 2026-10-11 | 审阅 UX-01 的 137 行日志：bootstrap 四项 AVAILABLE 构建提示均明确 `--parallel 8`，两个 GNU profile 为 OTHER HOST；CBS 42 条目标完成输出，零编译/链接/外部步骤，无新增错误或警告；状态改为已实现已构建，尚未提交 |
| 2026-10-11 | 维护者授权提交已验收的 UX-01；本阶段仅提交 bootstrap 报告、preset README 和开发台账三份文件；下一项为 UX-02，先完善 compile_commands 导出，再补充依赖复用或重建原因的摘要 |
| 2026-10-12 | UX-01 已提交为 `88346e66ba`；按维护者选择继续 BUILD-08，实现 ONNX 专用头/PUBLIC include 与两包按真实链接消费添加 RPATH；原实现三类问题用夹具复现，27 组脚本检查通过；首次迁移、开关范围/快照、CBS 加载和重复构建待维护者执行，尚未提交 |
| 2026-10-12 | 按维护者选择将 BUILD-06 Ninja 适配及 lld 迁移列为暂缓；只读核对 preset、构建缓存和相关 CMake 设置，当前使用 Unix Makefiles 与 `/usr/bin/ld`，没有强制 Ninja/lld；继续当前 BUILD-08 验收，未修改 generator 或链接器设置 |
| 2026-10-12 | 审阅 BUILD-08 的 765 行首次迁移日志及保存日志：304 个原生对象、六次链接、CBS/--help 成功，零外部构建步骤；真实 include、三个专用头消费者、CBS 与五个共享库的 link/LC_RPATH 核对通过，本阶段随本轮提交；OFF/ON 快照和最后 no-op 待补齐，登记当前 cbs-llvm 分阶段整体验收矩阵 |
| 2026-10-12 | BUILD-08 ONNX/RPATH 阶段已提交为 `52aaf8434f`；继续整体验收准备，DOC-01 同步共享 build/、--fresh、并发数与公开 preset 清单，DOC-02 示例完成无配置列表验证并待纳入提交；保留原示例及其他本地文件，补充两轮 no-op 验收命令，尚未提交本轮文档 |
| 2026-10-12 | 维护者反馈两轮快速完成；只读核对保存日志，两次 CBS 均 42 条目标完成输出，零编译/链接/外部步骤；重配置 6.0 秒、生成 0.6 秒，PASS/READY；DOC-01 文档与 DOC-02 原 HPC 示例随本轮提交，随后补齐 BUILD-08 开关验收 |
| 2026-10-12 | DOC-01/DOC-02 提交为 `eeaf63d5ef`；新增维护者 BUILD-08 四次开关验收入口和 14 组捕获命令夹具，记录范围、快照、启动、最终 no-op 与失败停止；当前 95 个文件快照和三个/六个实际依赖只读核对通过，真实开关待维护者执行，新入口尚未提交 |
| 2026-10-12 | 审阅 1814 行维护者开关日志、summary 与五份快照：ONNX 3/3 个对象和各一次链接，RestFrames 6/6 个对象和各两次链接，最终零工作；95 个文件 hash/mtime 稳定，四次 CBS 启动通过且两项恢复 ON；入口及验收记录随本轮提交，三个本地未追踪文件按明确路径加入 gitignore |
