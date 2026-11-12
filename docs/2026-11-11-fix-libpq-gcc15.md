# 修复 conan2(ubuntu)：libpq 15.4 源码编译在 GCC 15 下失败

## 失败信息
- Run 42444053205（conan2(ubuntu)）`conan install --build=missing`：
  `error: 'bool' cannot be defined via 'typedef'`（libpq/15.4 src/include/c.h:419）
  → libpq/15.4 build() 失败。

## 原因分析
- ubuntu-latest 已迁 Ubuntu 26.04（GCC 15.2 默认 -std=gnu23，bool 为关键字），
  老版本 libpq 15.4 源码 `typedef bool` 不兼容 C23。
- conancenter 已下架 libpq/15.4，最新 libpqxx 8.0.2 依赖 `libpq/[>=15.4 <18]`
  解析到 libpq/17.11（meson 构建，GCC 15 兼容）。

## 修复内容
- `conandata.yml`：`libpqxx/7.9.2` → `libpqxx/8.0.2`。

## 验证记录
| Run | 结果 |
|---|---|
| 42444053205 (修复前) | failure — libpq 15.4 GCC15 编译失败 |
| 待 re-run | 待填 |

## 补记: libpqxx 8.0.2 需 C++20
- profile cppstd gnu17→gnu20 (ubuntu/win/mac 三个 workflow)，CMakeLists CXX_STANDARD 20。

## 补记: 直接链接 libpq::pq 目标缺失
- libpq 17.11 (meson recipe) 的 CMakeDeps 未生成 libpq::pgport/pgcommon/pq 目标；
  libpqxx::pqxx 已传递依赖 libpq，改为仅链接 libpqxx::pqxx。

## 补记: conan 2.34 preset 命名
- 三个 workflow 的 conan-debug→conan-default。

## 补记: conan 2.34 布局变化
- 构建目录 build/Debug→build，三个 workflow 修正。

## 补记: preset 命名不稳定
- 改用 conan_toolchain.cmake 直接 configure。

## 补记: 改用 conan build
- conanfile 增加 build()，workflow 统一 conan install + conan build。

## 补记: libpqxx 8 API 变更
- txn.exec() 不再隐式转换到 pqxx::row，pg_brief.cpp 改用 exec1()。

## 补记: mysql_query 参数错误
- mysql_main.cpp 误把 mysql_query 当预处理用（5 参数）；改为 snprintf 格式化后 2 参数调用。
