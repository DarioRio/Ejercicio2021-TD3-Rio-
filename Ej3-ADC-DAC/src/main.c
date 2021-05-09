/* Rio Dario, Ingenieria Electrínica, 5to año,2021*/
/* Ej3-ADC-DAC: Realizar un programa que lea una señal del ADC y la procese y active/desactive una salida digital según un valor de umbral previamente definido. Por ejemplo: Encender/apagar un led al alcanzar determinado valor.
Opcional: modificar el programa para que se produzca una salida en un pin DAC proporcional a la señal leída en el ADC, lo que podría servir para diversas aplicaciones como: control de velocidad de motor de CC, control de brillo de un led, control de un led RGB, etc…*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include <driver/adc.h> // libreria del adc
#include <driver/dac.h>

void app_main()
{
    adc1_config_width(ADC_WIDTH_12Bit); //configuran la resoluncion a 12 Bit (se puede 10 9 y 11 bit tambien )
    adc1_config_channel_atten (ADC1_CHANNEL_0 ,ADC_ATTEN_11db); (canal 0 es el pin 36 ,con una atenuacion de 11 dB, para que me permita la escala de 0 a 3.3  )
   
    adc2_config_channel_atten (ADC2_CHANNEL_0, ADC_ATTEN_11db);
    
    dac_output_enable(DAC_CHANNEL_1); // para habilitar el DAC

    while(true)
    {
        int lectura = adc1_get_raw(ADC1_CHANNEL_0); //hago la lectura
        printf("El valor del ADC1 es %d\n",lectura); //Muestro el valor

        dac_output_voltage(DAC_CHANNEL_1,(lectura*255/4095)); //hacemos  la lectura y convertimos mis valores de 12bit a 8bit
                                                            // 0 y 255 DAC -- 8 bit -- va de 0 V a VDA (pin de alimentacion analogico) 
                                                              //0 y 4095 ADC

        int lectura2 = 0;
        adc2_get_raw(ADC2_CHANNEL_0, ADC_WIDTH_12Bit, &lectura2);
        printf("El valor del ADC2 es %d\n", lectura2);

        vTaskDelay(500/portTICK_PERIOD_MS);  //para que la medicion no sea tan rapida y vea muchos datos a la vez
    }

}