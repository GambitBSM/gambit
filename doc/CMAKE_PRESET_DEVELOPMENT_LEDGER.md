# CMake Preset 开发台账

记录 GAMBIT 和 ColliderBit Solo 的 preset、CMake 构建与开发体验改进。C++ 标准统一和 BUILD-01 已提交，维护者反馈 BUILD-01 重新编译及 touch 后构建都很快。BUILD-02 已完成脚本检查，并由维护者日志确认独立对象构建、完整链接及主工程无变化构建通过；实际并行重叠与运行场景仍待验证。其余事项按台账继续推进。

- 更新日期：2026-10-10，Australia/Adelaide。
- 目标分支：`Colliderbit-solo-development-preset`，工作树为 `cbs-presets`。
- C++ 标准、BUILD-01 和台账已提交为 `a3b3cc87c7`，实施基线为 `28600078fc`。
- BUILD-02 基于 `a3b3cc87c7` 实施，随本轮提交合入；提交包含独立程序对象目标、脚本回归及维护者日志验收记录。
- 关联文档：[Preset 使用说明](../cmake/presets/README.md)、[CMake Preset 工程标准](CMAKE_PRESET_STANDARD.md)、[仓库开发规则](../AGENTS.md)。

## 状态与验收规则

| 状态 | 含义 |
| --- | --- |
| 已合入 | 已有 Git 提交；构建验证情况单独记录 |
| 已实现待构建 | 代码已写入工作树，完成所列静态或脚本检查，尚未完成真实构建验收 |
| 已实现已构建 | 实现完成，维护者已执行所记录的实际构建场景；提交状态、测量证据及未测场景单独记录 |
| 待开发 | 问题或改进方向已确认，尚未实现 |
| 待评估 | 需要进一步设计或测量后决定是否实施 |

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
| BUILD-03 | P2 | 待开发 | 当前主工程未接入 ccache；增加可选 C/CXX launcher、保留用户选择并在摘要显示 | [Preset 入口](../cmake/CBS.cmake)、[工具链目录](../cmake/toolchains)。重复构建有可核实的命中记录；Fortran 与外部项目分别处理；首次全量编译不承诺提速 |
| BUILD-04 | P1 | 待开发 | 关闭部分功能会在配置期间删除对应安装树；停用 target 时保留依赖，由显式 nuke 负责删除 | [contrib.cmake](../cmake/contrib.cmake) 的 `nuke_ditched_contrib_content`。同工具链下关闭再开启功能，不应无故重建未变化的依赖 |
| BUILD-05 | P1 | 待开发 | FastJet 的缓存路径可能指向已删除的库；依赖复用缺少编译配置身份检查 | [contrib.cmake](../cmake/contrib.cmake) 的 FastJet/fjcontrib 复用逻辑。检查实际文件及编译器、架构、关键 flags、deployment target 等签名；缺失或不匹配时重新准备 |
| BUILD-06 | P3 | 待评估 | 支持 Ninja 前需分离主 generator 与外部 make 工具，并完善生成物声明 | [utilities.cmake](../cmake/utilities.cmake) 的 `MAKE_PARALLEL`。FastJet 等 Autotools 包必须仍用 make；不能只替换 preset 的 generator |
| BUILD-07 | P2 | 待评估 | 无变化 CBS 构建仍进入外部包装步骤：公共 `enable_auto_rebuild` 每次删除 build 标记，nulike/Rivet/Contur 的 build 重跑；Rivet 完成标记更新还使 Contur configure 重跑 | [externals.cmake](../cmake/externals.cmake) 的 `enable_auto_rebuild`、[backends.cmake](../cmake/backends.cmake) 的 Rivet/Contur。保留外部源码修改后的自动增量构建能力，减少无变化安装、配置及级联失效；不能直接删除自动重建机制 |

BUILD-02 的问题由原生成 Makefile 的依赖顺序确认；实现后独立对象目标及无变化构建已通过，实际并行重叠和节省时间尚未测量。BUILD-03 改善缓存命中的重复编译，不能解决所有首次编译等待。BUILD-07 由维护者无变化日志及当前生成规则确认，尚未修改代码。

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

## 配置正确性与使用体验待办

| 编号 | 优先级 | 状态 | 实施内容 | 验收标准与位置 |
| --- | --- | --- | --- | --- |
| CFG-01 | P1 | 待开发 | LLVM 发现先尊重显式编译器和 CC/CXX，再自动搜索 | [NativeCompilerDiscovery.cmake](../cmake/presets/NativeCompilerDiscovery.cmake)、[NativePresetToolchain.cmake](../cmake/toolchains/NativePresetToolchain.cmake)。多版本 LLVM 环境可选择指定版本；真正切换编译器仍遵守共享缓存规则 |
| CFG-02 | P2 | 待开发 | macOS SDK 判断改为尊重 `CMAKE_OSX_SYSROOT` | [MacOSX.cmake](../cmake/MacOSX.cmake)。用户指定 SDK 不被后续 xcrun 探测覆盖 |
| CFG-03 | P2 | 待开发 | 为 Python、Boost、HDF5、SQLite 等检查增加针对输入变化的缓存失效机制 | [CBSValidation.cmake](../cmake/presets/CBSValidation.cmake)。修复或更换依赖后不沿用陈旧 PASS/FAIL；当前只完成了 C++ 模式检查的失效机制 |
| CFG-04 | P2 | 待开发 | 同一次 bootstrap/configure 内复用重复工具链探测，并合并 Python 模块检查 | [detect-presets.cmake](../cmake/presets/detect-presets.cmake)、[PresetEnvironmentDiscovery.cmake](../cmake/presets/PresetEnvironmentDiscovery.cmake)、[CBSPythonDiscovery.cmake](../cmake/presets/CBSPythonDiscovery.cmake)。减少重复进程，环境改变后仍能重新探测 |
| CFG-05 | P2 | 待开发 | 统一 OpenMP、SDK 和 deployment flags 的来源，避免缓存与实际命令显示不一致 | [主配置](../CMakeLists.txt)、[MacOSX.cmake](../cmake/MacOSX.cmake)。摘要及生成命令一致，保留各外部包必要参数 |
| UX-01 | P2 | 待开发 | 构建示例采用明确并发数，例如 `--parallel 8` | [BootstrapReport.cmake](../cmake/presets/BootstrapReport.cmake)、[Preset README](../cmake/presets/README.md)。默认提示不依赖无上限并发，允许用户按资源调整 |
| UX-02 | P2 | 待开发 | 摘要补充缓存工具、依赖复用或重建原因；启用 compile_commands 导出 | 摘要已有标准选择信息；后续实际构建命令可追溯，IDE 能读取 `compile_commands.json` |
| DOC-01 | P2 | 待开发 | 修正文档中独立构建目录与共享 build 政策的冲突 | [工程标准](CMAKE_PRESET_STANDARD.md) 第 5 节与第 12 节。以 [AGENTS.md](../AGENTS.md) 的共享 `build/` 为准；本轮只更新了 C++ 约定 |
| DOC-02 | P2 | 待开发 | 将文档引用的 HPC preset 示例纳入版本控制 | [CMakeUserPresets.json.example](../CMakeUserPresets.json.example) 当前未跟踪。新 clone 可直接执行文档中的复制步骤；其他本地报告不顺带提交 |

## 下一轮实施与构建验收

1. C++ 修改及 BUILD-01 已提交；当前 LLVM/ROOT 17 配置和 CBS 构建已有日志，继续按需补齐其他标准、冲突拒绝及运行场景。
2. BUILD-01 已有当前环境的维护者构建反馈；后续按需补充文件增删或缺失恢复场景，继续完成 CFG-01/CFG-02 的显式配置优先级修复。
3. 接入 BUILD-03，完善 BUILD-04/BUILD-05 的依赖保留与复用；补齐对应摘要。
4. BUILD-02 独立对象构建、完整链接及无变化主工程构建已通过；继续补齐并行重叠与单点运行，以同环境基准量化收益，再评估 BUILD-07 的外部步骤重复开销。
5. 清理文档与探测重复项，再评估 Ninja 适配。

本台账不改变仓库构建政策：继续使用 `${sourceDir}/build`；切换编译器家族按 `AGENTS.md` 使用 `--fresh`；实际构建由维护者执行。变更 profile、关闭依赖与重置缓存的影响应单独记录，避免把额外重建误认为编译回退。

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
