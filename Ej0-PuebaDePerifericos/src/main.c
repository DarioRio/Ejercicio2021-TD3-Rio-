#include "../driver/include/driver/gpio.h"
//#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#define led1 GPIO_NUM_25
#define led2 GPIO_NUM_26
#define led3 GPIO_NUM_27
#define pulsador1 GPIO_NUM_14
#define pulsador2 GPIO_NUM_32
#define pulsador3 GPIO_NUM_35


#define T_ON		500/portTICK_PERIOD_MS

//int led1 = GPIO_NUM_25;
//int led2 = GPIO_NUM_26;
//nt led3 = GPIO_NUM_27;

//int pulsador1 = GPIO_NUM_14;
//int pulsador2 = GPIO_NUM_32;
//int pulsador3 = GPIO_NUM_35;
void app_main() 
{
gpio_pad_select_gpio(led1); 
gpio_set_direction(led1, GPIO_MODE_OUTPUT); 
gpio_pad_select_gpio(pulsador1);
gpio_set_direction(pulsador1, GPIO_MODE_INPUT); 
gpio_set_pull_mode(pulsador1, GPIO_PULLDOWN_ONLY);

gpio_pad_select_gpio(led2); 
gpio_set_direction(led2, GPIO_MODE_OUTPUT); 
gpio_pad_select_gpio(pulsador2);
gpio_set_direction(pulsador2, GPIO_MODE_INPUT); 
gpio_set_pull_mode(pulsador2, GPIO_PULLDOWN_ONLY);

gpio_pad_select_gpio(led3); 
gpio_set_direction(led3, GPIO_MODE_OUTPUT); 
gpio_pad_select_gpio(pulsador3);
gpio_set_direction(pulsador3, GPIO_MODE_INPUT); 
gpio_set_pull_mode(pulsador3, GPIO_PULLDOWN_ONLY);
while (true)
{
    if (gpio_get_level(pulsador1) == 1)
		{
			vTaskDelay(T_ON);
            gpio_set_level(led1, 1);
        }
    else
        {
            gpio_set_level(led1, 0);
        }

    if (gpio_get_level(pulsador2) == 1)
		{
			vTaskDelay(T_ON);
            gpio_set_level(led2, 1);
        }
    else
        {
            vTaskDelay(T_ON);
            gpio_set_level(led2, 0);
        }

    if (gpio_get_level(pulsador3) == 1)
		{
			vTaskDelay(T_ON);
            gpio_set_level(led3, 1);
        }
    else
        {
            gpio_set_level(led3, 0);
        }  
}
}