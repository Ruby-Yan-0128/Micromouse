/*
 * irs.c
 */

#include "main.h"
#include "irs.h"
#include "delay.h"

// The ADC handle that CubeMX created for us in main.c
extern ADC_HandleTypeDef hadc1;

// This is the buffer that will get filled up with all the measurements
uint16_t adc_buf[NUM_SAMPLES];
// "boolean" variable to say when the ADC has finished filling up the buffer
// volatile tells the compiler this can change at any time (it is set inside an interrupt)
volatile uint8_t complete = 0;

/*
 This function should handle everything for reading a specific IR
 First turn on the correct IR emitter
 Wait for a small amount of time (at least 20 us) so the receiver can react
 Then read the correct receiver
 Lastly turn off the emitter

 Emitter user labels (from CubeMX): Emitter1, Emitter2, Emitter3, Emitter4
 Setting an emitter pin HIGH (GPIO_PIN_SET) turns it ON
 */
uint16_t readIR(IR ir)
{
    if (ir == IR_1) {
        HAL_GPIO_WritePin(Emitter1_GPIO_Port, Emitter1_Pin, GPIO_PIN_SET);
        Delay_us(20);
        uint16_t value = readIR1();
        HAL_GPIO_WritePin(Emitter1_GPIO_Port, Emitter1_Pin, GPIO_PIN_RESET);
        return value;
    } else if (ir == IR_2) {
        HAL_GPIO_WritePin(Emitter2_GPIO_Port, Emitter2_Pin, GPIO_PIN_SET);
        Delay_us(20);
        uint16_t value = readIR2();
        HAL_GPIO_WritePin(Emitter2_GPIO_Port, Emitter2_Pin, GPIO_PIN_RESET);
        return value;
    } else if (ir == IR_3) {
        HAL_GPIO_WritePin(Emitter3_GPIO_Port, Emitter3_Pin, GPIO_PIN_SET);
        Delay_us(20);
        uint16_t value = readIR3();
        HAL_GPIO_WritePin(Emitter3_GPIO_Port, Emitter3_Pin, GPIO_PIN_RESET);
        return value;
    } else if (ir == IR_4) {
        HAL_GPIO_WritePin(Emitter4_GPIO_Port, Emitter4_Pin, GPIO_PIN_SET);
        Delay_us(20);
        uint16_t value = readIR4();
        HAL_GPIO_WritePin(Emitter4_GPIO_Port, Emitter4_Pin, GPIO_PIN_RESET);
        return value;
    }
    return 0;
}

/*
 Implement the following 4 functions to read each IR
 Hint: Each function may just be one line
 */
uint16_t readIR1(void)
{
    return analogRead(IR_1);
}

uint16_t readIR2(void)
{
    return analogRead(IR_2);
}

uint16_t readIR3(void)
{
    return analogRead(IR_3);
}

uint16_t readIR4(void)
{
    return analogRead(IR_4);
}


/*
 This function reads the specific channel of the ADC corresponding to the correct IR
 You should not have to edit this function
 */
uint16_t analogRead(IR ir)
{
    ADC_ChannelConfTypeDef sConfig = {0}; //this initializes the IR ADC [Analog to Digital Converter]

    //this picks the IR direction to choose the right ADC channel
    switch(ir)
    {
        case IR_1:
            sConfig.Channel = ADC_CHANNEL_8;  // Receiver 1 (left side), PB0
            break;
        case IR_2:
            sConfig.Channel = ADC_CHANNEL_6;  // Receiver 2 (front-left), PA6
            break;
        case IR_3:
            sConfig.Channel = ADC_CHANNEL_4;  // Receiver 3 (front-right), PA4
            break;
        case IR_4:
            sConfig.Channel = ADC_CHANNEL_2;  // Receiver 4 (right side), PA2
            break;
        default:
            return 0;
    }

    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_84CYCLES;

    // make sure everything was set up correctly
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        return 0;
    }

    complete = 0;

    // start filling up the ADC buffer
    HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_buf, NUM_SAMPLES);

    // wait for the buffer to become full (this takes about half a millisecond)
    uint32_t start = HAL_GetTick();
    while (complete == 0)
    {
        // if the buffer never fills up, something is set up wrong (see the Questions section)
        if (HAL_GetTick() - start > 10)
        {
            HAL_ADC_Stop_DMA(&hadc1);
            return 0;
        }
    }

    uint32_t sum = 0;
    // calculate the sum of the measurements in order to calculate the average
    uint16_t measurement = 0;
    while(measurement < NUM_SAMPLES) //this takes multiple measurements
    {
        sum += adc_buf[measurement];
        ++measurement;
    }

    return sum/NUM_SAMPLES;
}

/*
 This function is called when the ADC buffer is filled
 It stops the ADC and changes our "complete" variable to be "true"
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    // stop the ADC
    HAL_ADC_Stop_DMA(hadc);
    complete = 1;
}
