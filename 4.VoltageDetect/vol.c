#include "vol.h"

/**
 * @brief Get the voltage value of the battery
 * @param ch: the channel of the battery 
 * @retval the voltage value of the battery
 */
uint16_t Get_BAT(uint32_t ch){
    ADC_ChannelConfTypeDef sConfig = {0};  // ADC channel initialization 
    // ADC channel configuration
    sConfig.Channel = ch;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;

    // ADC error handler
    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK){
        Error_Handler();
    }

    HAL_ADCEx_Calibration_Start(&hadc3); // ADC calibration

    HAL_ADC_Start(&hadc3);
    HAL_ADC_PollForConversion(&hadc3, 100);
	return HAL_ADC_GetValue(&hadc3);
}

/**
 * @brief Get the average ADC value of the battery
 * @param ch: the channel of the battery 
 * @param times: the number of times to get the average value
 * @retval the multiple ADC measurements in average 
 */
uint16_t Adc_Get_Average(uint32_t ch, uint8_t times){
    uint32_t temp_val = 0; // temporary value for the ADC measurement
    for (uint8_t t = 0; t < times; t++){
        temp_val += Get_BAT(ch);
    }
    if (times == 4)
        temp_val = temp_val >> 2;  // temp_val = temp_val/4 (for better performance)
    else 
        temp_val = temp_val / times;

    return temp_val;
}

/**
 * @brief turn the ADC value into the voltage value 
 * @param none
 * @retval the voltage value of the battery
 */
float Adc_Get_Measure_Volotage(void){
    uint16_t adcx = Adc_Get_Average(BAT_CH, 4);
    float temp = (float)adcx * (3.3f / 4096);
    return temp;
}

/**
 * @brief the actual voltage before battery partial voltage
 */
float Adc_Get_Battery_Volotage(void){
	float temp;
	temp = Adc_Get_Measure_Volotage();
	temp *= 4.03f; // temp*(10+3.3)/3.3;
	return temp;
}
