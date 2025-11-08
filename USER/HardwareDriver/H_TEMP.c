/**
 ******************************************************************************
 * @file           : H_TEMP.c
 * @brief          :
 * @author         : UF4OVER
 * @date           : 2025/10/29
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 UF4.
 * All rights reserved.
 *
 ******************************************************************************
 */
//
// Created by 33974 on 2025/10/29.
//

/* Includes ------------------------------------------------------------------*/
#include "H_TEMP.h"
/* USER CODE BEGIN Includes */

#include "math.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/**
 * @brief 将ADC值转换为温度值(°C)，精度0.1°C
 * 使用公式: Rt = R * EXP(B * (1/T1 - 1/T2))
 * 其中T1和T2是开尔文温度(K)，K = 273.15 + 摄氏度
 * @param adc_value ADC读数 (0-4095 对应 0-3.3V)
 * @return 温度值(°C)
 */
float adcToTemperature(uint32_t adc_value) {
    // 防止除零错误
    if (adc_value >= 4095) {
        return -40.0; // 返回最低温度
    }

    // 计算NTC电阻值
    // 电路为: 3.3V - NTC - ADC - 10K - GND
    float voltage = (float)(4095-adc_value) * NTC_VREF / 4095.0;
    float ntc_resistance = NTC_R * voltage / (NTC_VREF - voltage);

    // 使用热敏电阻公式计算温度
    // Rt = R * EXP(B * (1/T1 - 1/T2))
    // => T1 = 1 / (1/T2 + ln(Rt/R)/B)
    // T2是25°C时的温度，即298.15K
    // T1是当前温度(开尔文)

    float T2 = ABSOLUTE_ZERO + 25.0; // 25°C对应的开尔文温度
    float ln_rt_over_r = logf(ntc_resistance / NTC_R25);
    float T1 = 1.0 / (1.0/T2 + ln_rt_over_r/NTC_BETA);

    // 转换为摄氏度
    float temperature = T1 - ABSOLUTE_ZERO;

    // 限制温度范围在-40°C到120°C之间
    if (temperature < -40.0) {
        temperature = -40.0;
    } else if (temperature > 120.0) {
        temperature = 120.0;
    }
    return temperature;
}
float GetTemperature(void){
    uint32_t adc_value;
//    HAL_ADC_Start_DMA(&hadc1, &adc_value, 1);
    return adcToTemperature(adc_value);
}

/* USER CODE END 0 */

/* External functions --------------------------------------------------------*/
/* USER CODE BEGIN EF */

/* USER CODE END EF */

/* Exported functions --------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
