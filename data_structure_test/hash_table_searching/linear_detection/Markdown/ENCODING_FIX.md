# 乱码问题解决方案

## 问题描述
在Windows系统中运行批处理文件时，可能出现中文字符显示为乱码的情况。

## 解决方案

### 方法1：使用中文版本脚本
- `demo_conflicts_cn.bat` - 中文版交互式程序演示
- `demo_improved_cn.bat` - 中文版改进测试演示

这些文件已经添加了UTF-8编码设置：
```batch
chcp 65001 >nul
```

### 方法2：使用英文版本脚本
如果中文仍然显示异常，请使用英文版本：
- `demo_conflicts.bat` - 英文版交互式程序演示  
- `demo_improved.bat` - 英文版改进测试演示

### 方法3：手动设置编码
在命令行中执行：
```cmd
chcp 65001
```
然后运行相应的批处理文件。

### 方法4：直接编译运行
如果批处理文件仍有问题，直接使用命令行：

```cmd
# 编译交互式版本
gcc -o interactive_hash_table.exe interactive_hash_table.c
interactive_hash_table.exe

# 编译基础版本
gcc -o hash_linear_detection.exe hash_linear_detection.c
hash_linear_detection.exe
```

## 推荐使用顺序

1. **首选**：`demo_improved_cn.bat` (中文版改进演示)
2. **备选1**：`demo_improved.bat` (英文版改进演示)
3. **备选2**：直接命令行编译运行
4. **最后**：在VS Code集成终端中运行

## 程序功能说明

### 基础版本 (hash_linear_detection.c)
- 固定测试数据，展示改进的冲突分布
- 详细的性能统计信息
- 环形探测演示

### 交互式版本 (interactive_hash_table.c)  
- 完整的交互式菜单
- 多种冲突模式测试
- 实时ASL计算
- 用户自定义测试

## 注意事项
- 确保已安装GCC编译器
- 在Windows PowerShell中可能需要使用 `.\` 前缀运行exe文件
- 如果仍有编码问题，建议在命令提示符(cmd)中运行，而非PowerShell
