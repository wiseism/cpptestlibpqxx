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
