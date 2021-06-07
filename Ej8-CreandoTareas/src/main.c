/*
Ejercicio: N° 8
Alumono Darío Río
Carrera:Ing. Electronica
Curso: 5to
Año: 2021
*/
#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"      //intrucciones para trabajar con OS
#include "freertos/task.h"          //intrucciones para trabajar con OS
#include "freertos/FreeRTOSConfig.h"//intrucciones para trabajar con OS
#include "driver/gpio.h"

#define PULSADOR    GPIO_NUM_25
#define SALIDA1     GPIO_NUM_26
#define SALIDA2     GPIO_NUM_27
#define RETARDO_US  1

void tareaSecundaria( void * pvParameters ); //Prototipo de la tarea (funcion void void)

void app_main() 
{
    TaskHandle_t xHandle1 = NULL;           //Puntero a la tarea, lo apuntamos a nulo

    xTaskCreate( tareaSecundaria,           //Función que implementa la tarea. La misma no debe retornar.
                 "Tarea secundaria",        //Nombre que reprenta la tarea, para facilitar la depuración.
                 configMINIMAL_STACK_SIZE,  //Tamaño del stack en bytes (minimo en este caso 768 bytes), si necesito mas le pongo *2,*3... 
                 NULL,                      //Puntero que se utilizará como parámetro para la tarea que se está creando. Como no lo usamos ponemos NULL (le paso datos a esa tarea)
                 tskIDLE_PRIORITY,          //Prioridad de la tarea (si quiero darle mas prioridad le pongo antes del ; +1,+2...)
                 &xHandle1                  //Puntero a la tarea, me va permitir suspenderla o eliminarla
                );
    configASSERT( xHandle1 );                //entra si no se pudieron crear las tareas, para debug

    gpio_pad_select_gpio(PULSADOR);
	gpio_set_direction(PULSADOR, GPIO_MODE_INPUT);
	gpio_set_pull_mode(PULSADOR, GPIO_PULLDOWN_ONLY);
    gpio_pad_select_gpio(SALIDA1);
    gpio_set_direction(SALIDA1, GPIO_MODE_OUTPUT);

    while(true)
    {
        if (gpio_get_level(PULSADOR))
        {
             
            }
        }
        gpio_set_level(SALIDA1, 1);
        ets_delay_us(RETARDO_US);    //delay en microsegundos que bloquea al procesador
        gpio_set_level(SALIDA1, 0);
        ets_delay_us(RETARDO_US);
    }
}

//Definición de la tarea
void tareaSecundaria( void * pvParameters )
{
    gpio_pad_select_gpio(SALIDA2); //configuro el pin
    gpio_set_direction(SALIDA2, GPIO_MODE_OUTPUT);
    while (true)
    {
        gpio_set_level(SALIDA2, 1);
        ets_delay_us(RETARDO_US);    //delay en microsegundos que bloquea al procesador
        gpio_set_level(SALIDA2,0);
        ets_delay_us(RETARDO_US);
    }
}