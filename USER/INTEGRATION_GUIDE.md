# stm32f407lm5175电源控制系统

本文档介绍了GUI、PID自动整定、FLASH存储模块的集成。

## 体系结构概述

该系统由几个综合模块组成：

1. **GUI Handler** (`H_GUI_HANDLER.c/h`) - 管理GUI事件和数据显示
2. **PID Auto-tuning** (`M_PID_AUTOTUNE.c/h`) - I实现Ziegler-Nichols中继反馈自动调整
3. **FLASH Storage** (`H_FLASH_STORAGE.c/h`) - 从内部FLASH保存/加载PID参数
4. **System Manager** (`M_SYSTEM_MANAGER.c/h`) - 将所有模块集成到一个内聚的系统中
5. **TYPE3 Controller** (`M_TYPE3_Controller.c/h`) - PID控制器实现

## 快速入门集成示例

### 1. 在main.c中包含所需的头文件

```c
#include "M_SYSTEM_MANAGER.h"
#include "ui.h"
```

### 2. 声明系统管理器实例

```c
/* Private variables ---------------------------------------------------------*/
static SystemManager_t g_system_manager;
```

### 3. 在GUI初始化之后，在main（）中初始化

```c
int main(void)
{
    /* ... HAL initialization ... */
    
    /* Initialize GUI */
    ui_init();
    
    /* Initialize System Manager with GUI */
    SystemManager_Init(&g_system_manager, &guider_ui);
    
    /* Main loop */
    while (1)
    {
        /* ... existing code ... */
    }
}
```

### 4. 增加控制循环更新

在主循环或定时器回调中，添加周期性系统更新：

```c
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    /* ... existing LVGL updates ... */
    
    // Update control system at control frequency (e.g., 100Hz)
    if(htim == &htim_control) // Define your control timer
    {
        // Get sensor readings (example - replace with actual sensor reading)
        float vout = INA226_ReadVoltage();  // Output voltage
        float iout = INA226_ReadCurrent();  // Output current
        float vbus = INA226_ReadBusVoltage(); // Input voltage
        float ibus = INA226_ReadBusCurrent(); // Input current
        float temp = TEMP_Read();  // Temperature
        
        // Update system manager
        uint32_t current_time = HAL_GetTick();
        SystemManager_Update(&g_system_manager,
                           vout, iout,
                           vbus, ibus,
                           temp,
                           current_time);
    }
}
```

## 功能的使用

### 自整定PID参数

启动自动调优（可以通过按键或命令触发）：

```c
// 在12V目标时开始自动调节
if(auto_tune_button_pressed)
{
    float target_voltage = 12.0f;
    uint32_t current_time = HAL_GetTick();
    
    if(SystemManager_StartAutoTune(&g_system_manager, target_voltage, current_time))
    {
        // 自动调优成功启动
        // 完成后，系统将自动应用新的参数
    }
}

// 检查是否正在进行自动调优
if(SystemManager_IsAutoTuning(&g_system_manager))
{
    // 在GUI上显示“正在进行的自动调优…
}
```

### 将参数保存到FLASH中

```c
// 保存当前PID参数和设置到FLASH
if(save_button_pressed)
{
    if(SystemManager_SaveParams(&g_system_manager))
    {
        // 参数保存成功
    }
    else
    {
        // Save failed
    }
}
```

### 从FLASH中加载参数

参数在`SystemManager_Init()`期间自动加载。
手动重新加载：

```c
if(SystemManager_LoadParams(&g_system_manager))
{
    // 参数加载成功
}
```

### 重置为默认参数

```c
SystemManager_ResetParams(&g_system_manager);
```

## 图形用户界面集成

The GUI handler automatically:
- Updates all display labels (VBUS, IBUS, VOUT, IOUT, POUT, temperature, efficiency)
- Reads voltage/current setpoints from spinboxes
- Reads output enable switch state
- Reads control mode (CC/CV) from dropdown

No additional code needed in main loop - just call `SystemManager_Update()`.

## 自动理论

中继反馈方法的工作原理如下：

1. **继电器控制**: 在设定值周围应用开/关控制
2. **振动检测**: 测量振荡的周期和振幅
3. **最终增益计算**: Ku = 4*d/(π*a), 其中d=继电器振幅，a=振荡 amplitude
4. **PID Tuning**: 采用保守的齐格勒-尼科尔斯规则：
   - Kp = 0.45 * Ku
   - Ki = 0.54 * Ku / Pu
   - Kd = 0.09 * Ku * Pu

其中Pu为最终周期（振荡周期）。

##闪存布局

- **Sector 11** (0x080E0000 - 0x080FFFFF, 128KB) 用于参数存储
- 结构包括:
  - 神奇的数字 (0x50494441)
  - 版本号
  - PID参数 (Kp, Ki, Kd)
  - 默认的定位点 (Vset, Iset)
  - 用于验证的校验和

## 安全注意事项

1. **Auto-tuning**: 只有在适当负载的受控条件下才能运行自动调优
2. **Parameter Validation**: FLASH参数在使用前经过crc验证
3. **Fallback**: 如果FLASH参数无效，系统将使用安全的默认值
4. **Limits**: 所有的电压/电流设定值都固定在GLOBAL_CONFIG.h中定义的安全范围内

## 配置选项

In `GLOBAL_CONFIG.h`:
```c
#define MAX_VOLTAGE 27.0F      // Maximum output voltage
#define MIN_VOLTAGE 1.0F       // Minimum output voltage
#define MAX_CURRENT 7.0F       // Maximum output current
#define MIN_CURRENT 0.05F      // Minimum output current
#define START_KP 100.0F        // Default Kp
#define START_KI 10.0F         // Default Ki
#define START_KD 1.0F          // Default Kd
#define FREQ_OF_CONTROL 100    // Control loop frequency (Hz)
```

In `M_PID_AUTOTUNE.h`:
```c
#define AUTOTUNE_DEFAULT_RELAY_AMPLITUDE 2.0f   // ±2V relay output
#define AUTOTUNE_DEFAULT_NOISE_BAND      0.05f  // 50mV hysteresis
#define AUTOTUNE_DEFAULT_MAX_CYCLES      5      // Measure 5 cycles
#define AUTOTUNE_DEFAULT_TIMEOUT_MS      30000  // 30 second timeout
```

## 故障排除

### 自动失败
-确保有足够的负载连接
- 检查继电器的振幅是否与系统相适应
- 如果系统响应慢，增加超时时间
- 验证传感器读数是否准确

### 参数不保存到FLASH
- 检查FLASH是否没有写保护
- 在写操作时，验证电量是否充足
- 确保没有其他代码同时访问FLASH

### GUI not updating
- Verify `GUI_Handler_Init()` was called with valid `lv_ui` pointer
- Ensure `SystemManager_Update()` is called periodically
- Check LVGL timer is running correctly

## API Reference

See header files for complete API documentation:
- `M_SYSTEM_MANAGER.h` - 主要系统集成API
- `H_GUI_HANDLER.h` - GUI界面功能
- `M_PID_AUTOTUNE.h` - 自动功能
- `H_FLASH_STORAGE.h` - FLASH参数存储功能
- `M_TYPE3_Controller.h` - PID控制器功能
