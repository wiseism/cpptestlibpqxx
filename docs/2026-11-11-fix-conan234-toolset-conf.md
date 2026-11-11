# 修复 conan2 win：msvc_toolset_version conf 已被 conan 2.34 移除

## 失败信息
- Run 42444053256（conan2 win 2022）：
  `ERROR: [conf] 'tools.microsoft:msvc_toolset_version' does not exist in configuration list`

## 原因分析
- conan 2.34 移除了该 conf；`compiler.version=194` 已自动映射 toolset 14.4X。

## 修复内容
- 删除 win workflow 中向 profile 追加该 conf 的行。

## 验证记录
| Run | 结果 |
|---|---|
| 42444053256 (修复前) | failure — 未知 conf |
| 待 re-run | 待填 |
