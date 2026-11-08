# 修复记录：conan CI 构建失败（2026-11-08）

## 失败信息
- 仓库：wiseism/cpptestlibpqxx
- Workflows：conan2 ubuntu / conan2 win 2022 / conan2 macos latest
- 失败 run：
  - [41938327691](https://github.com/wiseism/cpptestlibpqxx/actions/runs/41938327691)（ubuntu）
  - [41938327686](https://github.com/wiseism/cpptestlibpqxx/actions/runs/41938327686)（win）
  - [41938327683](https://github.com/wiseism/cpptestlibpqxx/actions/runs/41938327683)（macos）

## 错误日志摘录
```
# ubuntu
ERROR: Invalid setting '15' is not a valid 'settings.compiler.version' value.
Possible values are [... '13.2']
# win
conanvcvars.bat: Activating environment ... vcvars_ver=14.3
[ERROR:vcvars.bat] Toolset directory for version '14.3' was not found.
ERROR: libpq/14.5: Error in build() method, line 173
	self.run("perl build.pl libpq")
CMake Error: Could not read presets from D:/a/cpptestlibpqxx/cpptestlibpqxx:
File not found: ... CMakePresets.json
# macos
CMake Error at cmake/config.cmake:45 (cmake_determine_compile_features):
  Unknown CMake command "cmake_determine_compile_features".
```

## 原因分析
1. ubuntu：pip 安装的 conan==2.0.16 settings 列表止步 GCC13，runner 默认 GCC15。
2. win：windows-latest 迁移到 VS2026 镜像（仅安装 MSVC 14.44 / v143 17.14 工具集），
   conan 由 settings 定到 14.3 → vcvars 报错 → libpq 用 perl 构建失败，
   后续 CMakePresets 未生成。
3. macos：系统 CMake 已是 4.x，`cmake_determine_compile_features`
   这一内部命令被移除；libpqxx 7.7.4（旧版 recipe/源码）构建配置阶段失败。

## 修复内容
1. `conandata.yml`：`libpqxx/7.3.2 → libpqxx/7.9.2`（新版修复了该 CMake 命令用法）。
2. `conan2_ubuntu.yml`：`pip3 install -U conan`。
3. `conan2_win.yml`：`pip3 install -U conan` + profile 追加
   `[conf] tools.microsoft:msvc_toolset_version=14.44`。

## 验证
| run id | 结果 |
| --- | --- |
| 本次推送触发 | 待填 |
