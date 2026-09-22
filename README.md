# PMSM 电机控制项目

本仓库整理了两个基于 **STM32G431CBU6** 的永磁同步电机（PMSM）控制项目，包含 MATLAB/Simulink 模型、控制算法源码、STM32 工程和 VOFA+ 上位机配置。

## 项目内容

| 目录 | 内容 |
| --- | --- |
| [`HFI_SMOPLL`](HFI_SMOPLL) | PMSM 无位置传感器控制相关模型与工程，包含高频注入（HFI）、滑模观测器（SMO）和锁相环（PLL）相关实现。 |
| [`PosLoop`](PosLoop) | PMSM 位置环 FOC 项目，包含电流环、速度环、位置环、编码器反馈及 STM32 实机工程。 |

## 效果展示

### HFI / SMO-PLL

![HFI 与 SMO-PLL 仿真模型](docs/images/hfi-smo-model.png)

速度指令、实际转速与估算转速跟踪结果：

![速度跟踪结果](docs/images/hfi-smo-speed-tracking.png)

### 位置环控制

![位置环仿真模型](docs/images/posloop-model.png)

实物测试平台：

![位置环实物平台](docs/images/posloop-hardware.jpg)

## 目录结构

```text
PMSM/
├─ HFI_SMOPLL/
│  ├─ HFI_AVi.sldd
│  ├─ HFI_UB_counter_latch.slx
│  ├─ STM32G4_FOC_Speedloop_SMO/
│  └─ VOFA GUI/
├─ PosLoop/
│  ├─ posloop.sldd
│  ├─ posloop.slx
│  ├─ STM32G4_FOC_Posloop/
│  └─ VOFA GUI/
└─ docs/images/
```

STM32 工程中主要保留了以下内容：

- `app/`：电机控制任务、编码器和通信相关代码
- `Core/`：STM32 启动和外设初始化代码
- `MATLAB/`、`MATLAB2/`：模型对应的控制算法 C 源码
- `Drivers/`：工程使用的 STM32 HAL、CMSIS 和 DSP 依赖
- `MDK-ARM/`：Keil MDK 工程文件
- `*.ioc`：STM32CubeMX 配置

## 开发环境

- MATLAB / Simulink R2021b
- STM32CubeMX
- Keil MDK-ARM
- STM32G431CBU6
- VOFA+

## 使用方法

### Simulink 模型

1. 使用 MATLAB/Simulink 打开对应目录下的 `.slx` 文件。
2. 保持同目录的 `.sldd` 数据字典可访问。
3. 检查电机参数、母线电压、采样周期和控制器参数后再运行仿真。

### STM32 工程

1. 使用 Keil 打开项目目录下的 `MDK-ARM/STM32G4_FOC Base.uvprojx`。
2. 如需修改外设配置，使用 STM32CubeMX 打开同目录下的 `STM32G4_FOC Base.ioc`。
3. 根据实际电机、功率板和编码器修改参数，编译后下载到 STM32G431CBU6。
4. 可使用相应 `VOFA GUI/` 目录中的配置观察电流、转速、角度等变量。

## 说明

- 仓库未提交 Simulink 缓存、Keil 编译产物和调试缓存，可在本地重新生成。
- 上电测试前请核对相序、电流采样极性、编码器方向、母线电压和过流保护参数。
- `Drivers/` 中的 STM32 HAL、CMSIS 等第三方文件保留其原始版权与许可声明。

