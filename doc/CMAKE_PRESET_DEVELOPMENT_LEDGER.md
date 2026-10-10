# CMake Preset 开发台账

记录 GAMBIT 和 ColliderBit Solo 的 preset、CMake 构建与开发体验改进。C++ 标准统一和 BUILD-01 已提交，维护者反馈 BUILD-01 重新编译及 touch 后构建都很快。BUILD-02 已完成脚本检查，并由维护者日志确认独立对象构建、完整链接及主工程无变化构建通过；实际并行重叠与运行场景仍待验证。BUILD-03 已接入可选 ccache，维护者日志确认真实 launcher 与完整 CBS 链接成功；精确命中增量和开关场景仍待补齐。BUILD-04 已移除三处停用即删除逻辑，并保留停用包的显式清理入口；5 组夹具检查通过，维护者日志确认 RestFrames OFF/ON 后安装保留、外部目标复用及完整 CBS 构建成功；HepMC/YODA 停用场景仍待验证。BUILD-05 已增加 FastJet/Contrib 文件与构建身份检查，11 组脚本夹具通过；维护者日志确认首次迁移重建、成功记录、相同配置复用及完整 CBS 构建通过。BUILD-07 已为日志中的三包接入输入状态检查和成功安装后记录，11 组脚本夹具通过；维护者日志确认首次建立记录、直接重复构建和相同配置后复用均成功，三包重复步骤已跳过。其余事项按台账继续推进。

- 更新日期：2026-10-11，Australia/Adelaide。
- 目标分支：`Colliderbit-solo-development-preset`，工作树为 `cbs-presets`。
- C++ 标准、BUILD-01 和台账已提交为 `a3b3cc87c7`，实施基线为 `28600078fc`。
- BUILD-02 已提交为 `957c81ecd9`，父提交为 `a3b3cc87c7`；包含独立程序对象目标、脚本回归及维护者日志验收记录。
- BUILD-03 已提交为 `0965735828`，父提交为 `957c81ecd9`；包含可选 ccache、摘要、策略测试和维护者构建记录。
- BUILD-04 已提交为 `1d46bf0439`，父提交为 `0965735828`；包含三包停用保留、显式清理入口及维护者验收记录。
- BUILD-05 已提交为 `09929f07fb`，父提交为 `1d46bf0439`；当前 macOS LLVM 首次迁移及相同配置复用已验收。
- BUILD-07 基于 `09929f07fb` 实施；当前 macOS LLVM 首次记录、直接重复构建及相同配置复用已验收，随本轮提交；BUILD-06 为 P3 后续评估。
- 关联文档：[Preset 使用说明](../cmake/presets/README.md)、[CMake Preset 工程标准](CMAKE_PRESET_STANDARD.md)、[仓库开发规则](../AGENTS.md)。

## 状态与验收规则

| 状态 | 含义 |
| --- | --- |
| 已合入 | 已有 Git 提交；构建验证情况单独记录 |
| 已实现待构建 | 代码已写入工作树，完成所列静态或脚本检查，尚未完成真实构建验收 |
| 已实现已构建 | 实现完成，维护者已执行所记录的实际构建场景；提交状态、测量证据及未测场景单独记录 |
| 部分完成 | 所列子项中已有实现，其余子项仍待开发或验收 |
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
| BUILD-03 | P2 | 已合入 | 使用 `GAMBIT_COMPILER_CACHE=AUTO/CCACHE/OFF` 接入原生 C/CXX launcher；preset 首次默认 AUTO，普通首次配置默认 OFF；逐语言保留显式 launcher（含空值），自动值不写入持久缓存；摘要显示策略、版本和实际 launcher | [CompilerCache.cmake](../cmake/CompilerCache.cmake)、[主配置](../CMakeLists.txt)、[CBS 摘要](../cmake/presets/CBSCompilerSummary.cmake)、[GAMBIT 摘要](../cmake/presets/GAMBITBuildSummary.cmake)。7 组策略脚本通过；真实 launcher 与完整 CBS 链接已有维护者日志，全局缓存已有命中；同文件命中增量与开关场景尚未记录。Fortran 与外部项目分别处理，首次全量编译不承诺提速 |
| BUILD-04 | P1 | 已合入 | 移除 RestFrames/HepMC/YODA 停用分支中的自动删除及未使用的 `nuke_ditched_contrib_content`；保留源码、安装、外部构建目录和步骤标记；三包的显式 clean/nuke 在停用时也可用 | [contrib.cmake](../cmake/contrib.cmake)、[contrib_retention.py](../cmake/tests/contrib_retention.py)。5 组夹具检查通过；当前 macOS LLVM 环境 RestFrames OFF/ON 保留复用和完整 CBS 构建已通过；HepMC/YODA 停用及清理入口的真实验收待补齐 |
| BUILD-05 | P1 | 已合入 | FastJet/Contrib 每次重新搜索并检查实际文件；复用须匹配成功安装后的构建身份；缺失或不匹配时使所属步骤失效，构建阶段从校验过的归档恢复干净源码；FastJet 重建级联至 Contrib | [contrib.cmake](../cmake/contrib.cmake)、[ContribBuildIdentity.cmake](../cmake/ContribBuildIdentity.cmake)、[contrib_build_identity.py](../cmake/tests/contrib_build_identity.py)。11 组脚本夹具通过；当前 macOS LLVM 首次迁移、安装身份、相同配置复用及完整 CBS 构建已通过；直接无配置重复构建、时间戳对照和其他平台待补齐 |
| BUILD-06 | P3 | 待评估 | 支持 Ninja 前需分离主 generator 与外部 make 工具，并完善生成物声明 | [utilities.cmake](../cmake/utilities.cmake) 的 `MAKE_PARALLEL`。FastJet 等 Autotools 包必须仍用 make；不能只替换 preset 的 generator |
| BUILD-07 | P2 | 已合入 | 为 nulike 1.0.9、Rivet 4.1.0、Contur 3.0.0 声明输入和关键产物；成功安装后记录状态，无变化保留 build 标记；编辑/touch/增删源码或缺产物时使所属步骤失效；其他包保留原策略 | [ExternalAutoRebuild.cmake](../cmake/ExternalAutoRebuild.cmake)、[external_rebuild.py](../cmake/scripts/external_rebuild.py)、[externals.cmake](../cmake/externals.cmake)、[backends.cmake](../cmake/backends.cmake)。11 组临时检查通过；当前环境首次记录、直接重复构建及重新配置后跳过已通过，时间戳对照及源码 touch 待补齐 |
| BUILD-08 | P2 | 待评估 | 可选依赖通过目录级 include_directories 传播到无关原生目标；OFF/ON 改写 flags.make，即使恢复原配置也会触发对象构建。评估目标级依赖及配置头文件范围 | [contrib.cmake](../cmake/contrib.cmake)、[preprocessor.cmake](../cmake/preprocessor.cmake)。本次 RestFrames 切换后，Models、FastJet Contrib、mkpath、Fortran 等目标均带 RestFrames include。收窄影响范围时必须保留实际使用该依赖的目标及生成头文件顺序；不能强行恢复旧时间戳隐藏配置变更 |

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

2026-10-11 基于 `09929f07fb` 实现；当前 macOS LLVM 的首次记录、直接重复构建及相同配置后复用已由维护者验收，随本轮提交，状态为 **已合入**。台账将 Ninja 适配（BUILD-06）列为 P3 后续评估，本轮先处理已有实际日志证据的 P2 重复步骤。

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

## 配置正确性与使用体验待办

| 编号 | 优先级 | 状态 | 实施内容 | 验收标准与位置 |
| --- | --- | --- | --- | --- |
| CFG-01 | P1 | 待开发 | LLVM 发现先尊重显式编译器和 CC/CXX，再自动搜索 | [NativeCompilerDiscovery.cmake](../cmake/presets/NativeCompilerDiscovery.cmake)、[NativePresetToolchain.cmake](../cmake/toolchains/NativePresetToolchain.cmake)。多版本 LLVM 环境可选择指定版本；真正切换编译器仍遵守共享缓存规则 |
| CFG-02 | P2 | 待开发 | macOS SDK 判断改为尊重 `CMAKE_OSX_SYSROOT` | [MacOSX.cmake](../cmake/MacOSX.cmake)。用户指定 SDK 不被后续 xcrun 探测覆盖 |
| CFG-03 | P2 | 待开发 | 为 Python、Boost、HDF5、SQLite 等检查增加针对输入变化的缓存失效机制 | [CBSValidation.cmake](../cmake/presets/CBSValidation.cmake)。修复或更换依赖后不沿用陈旧 PASS/FAIL；当前只完成了 C++ 模式检查的失效机制 |
| CFG-04 | P2 | 待开发 | 同一次 bootstrap/configure 内复用重复工具链探测，并合并 Python 模块检查 | [detect-presets.cmake](../cmake/presets/detect-presets.cmake)、[PresetEnvironmentDiscovery.cmake](../cmake/presets/PresetEnvironmentDiscovery.cmake)、[CBSPythonDiscovery.cmake](../cmake/presets/CBSPythonDiscovery.cmake)。减少重复进程，环境改变后仍能重新探测 |
| CFG-05 | P2 | 待开发 | 统一 OpenMP、SDK 和 deployment flags 的来源，避免缓存与实际命令显示不一致；补齐 GNU Fortran 编译阶段的公共 macOS minimum target | [主配置](../CMakeLists.txt)、[MacOSX.cmake](../cmake/MacOSX.cmake)。摘要及生成命令一致，保留各外部包必要参数；当前日志发现 Fortran 新编对象 minimum 为 28.0、链接为 27.0，生成 Fortran_FLAGS 缺少 minimum 参数，链接命令已有公共 27.0 参数 |
| UX-01 | P2 | 待开发 | 构建示例采用明确并发数，例如 `--parallel 8` | [BootstrapReport.cmake](../cmake/presets/BootstrapReport.cmake)、[Preset README](../cmake/presets/README.md)。默认提示不依赖无上限并发，允许用户按资源调整 |
| UX-02 | P2 | 部分完成 | 摘要已补充缓存策略、ccache 版本和 C/C++ launcher；依赖复用或重建原因及 compile_commands 导出待开发 | 摘要已有标准选择信息；后续实际构建命令可追溯，IDE 能读取 `compile_commands.json` |
| DOC-01 | P2 | 待开发 | 修正文档中独立构建目录与共享 build 政策的冲突 | [工程标准](CMAKE_PRESET_STANDARD.md) 第 5 节与第 12 节。以 [AGENTS.md](../AGENTS.md) 的共享 `build/` 为准；本轮只更新了 C++ 约定 |
| DOC-02 | P2 | 待开发 | 将文档引用的 HPC preset 示例纳入版本控制 | [CMakeUserPresets.json.example](../CMakeUserPresets.json.example) 当前未跟踪。新 clone 可直接执行文档中的复制步骤；其他本地报告不顺带提交 |

## 下一轮实施与构建验收

1. C++ 修改及 BUILD-01 已提交；当前 LLVM/ROOT 17 配置和 CBS 构建已有日志，继续按需补齐其他标准、冲突拒绝及运行场景。
2. BUILD-01 已有当前环境的维护者构建反馈；后续按需补充文件增删或缺失恢复场景，继续完成 CFG-01/CFG-02 的显式配置优先级修复。
3. BUILD-03 已提交为 `0965735828`；按需补齐命中增量和 OFF/AUTO 实测。BUILD-04 已提交为 `1d46bf0439`，HepMC/YODA 场景按需补齐；BUILD-05 首次迁移及相同配置复用已通过并提交为 `09929f07fb`；BUILD-07 首次记录、直接重复构建及相同配置后复用已通过并随本轮提交；时间戳对照、源码 touch 和其他平台按需补齐。BUILD-06 Ninja 适配仍作为 P3 后续评估。
4. BUILD-02 独立对象构建、完整链接及无变化主工程构建已通过；继续补齐并行重叠与单点运行，以同环境基准量化收益，结合 BUILD-07 的验收日志测量外部步骤重复开销。
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
| 2026-10-10 | BUILD-02 提交为 `957c81ecd9`；实现 BUILD-03 可选 ccache 与两类摘要，记录七组策略检查和命中/关闭验收步骤；BUILD-03 尚未提交 |
| 2026-10-10 | 审阅维护者 195 行日志：ccache 编译 solo_cli.cpp 和完整 CBS 链接成功；登记全局 64 次命中及单快照限制，提交 BUILD-03 后继续 BUILD-04 |
| 2026-10-10 | BUILD-03 提交为 `0965735828`；实现 BUILD-04 RestFrames/HepMC/YODA 停用保留及显式清理入口，记录五组夹具检查和实际开关/复用验收流程；BUILD-04 尚未提交 |
| 2026-10-10 | 审阅 BUILD-04 的 1125 行日志：RestFrames OFF 后库保留、恢复复用及完整 CBS 构建通过；区分 301 条 C++ 对象构建与外部依赖重建，新增 BUILD-08 评估项，并补充 CFG-05 的 Fortran minimum target 不一致证据；尚未提交 |
| 2026-10-10 | 维护者补充恢复配置后的 CBS -j8 无变化日志：无原生对象编译、链接及代码生成，主工程增量验收通过；nulike/Rivet/Contur 包装步骤仍重复进入，继续跟踪 BUILD-07；BUILD-04 尚未提交 |
| 2026-10-11 | BUILD-04 提交为 `1d46bf0439`；实现 BUILD-05 FastJet/Contrib 实际文件与构建身份校验、构建阶段干净准备及成功安装后记录；11 组新夹具和五组保留检查通过，真实构建待维护者验收；BUILD-05 尚未提交 |
| 2026-10-11 | 维护者日志确认 BUILD-05 首次迁移、成功安装记录、相同配置复用及完整 CBS 构建通过；安装记录只读比对通过；开始处理 BUILD-07，直接重复构建/时间戳与其他平台待补齐 |
| 2026-10-11 | BUILD-05 提交为 `09929f07fb`；实现 BUILD-07 三包输入/产物检查和成功安装后记录，11 组脚本夹具通过，当前安装只读扫描稳定；真实构建待维护者验收，BUILD-07 尚未提交 |
| 2026-10-11 | 审阅 BUILD-07 的 889 行日志：三包首次成功记录、直接重复构建及相同配置后跳过重复步骤均通过；三次 CBS 成功，无原生编译/链接；成功记录及生成命令只读比对通过，随本轮提交；touch/时间戳及其他平台待补齐 |
