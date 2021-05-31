/*
Ejercicio: N° 10
Alumono Darío Río
Carrera:Ing. Electronica
Curso: 5to
Año: 2021
*/
#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/FreeRTOSConfig.h"
#include "driver/gpio.h"

#define PULSADOR    GPIO_NUM_18
#define SALIDA1     GPIO_NUM_25
#define SALIDA2     GPIO_NUM_26
#define PROCESADORA 0
#define PROCESADORB 1
#define RETARDO_MS  100/portTICK_PERIOD_MS

void tareaUno( void * pvParameters );
void tareaDos( void * pvParameters ); //Prototipo de la tarea

TaskHandle_t xHandle2 = NULL;            //Puntero a la tarea
TaskHandle_t xHandle1 = NULL;            //Puntero a la tarea

void app_main() 
{
    xTaskCreatePinnedToCore( tareaDos,      //Función que implementa la tarea. La misma no debe retornar.
                 "Tarea dos",               //Nombre que reprenta la tarea, para facilitar la depuración.
                 configMINIMAL_STACK_SIZE,  //Tamaño del stack en bytes, puedo borrar "configMINIMAL_STACK_SIZE" y poner directamente los bytes ejemplo "300"
                 NULL,                      //Puntero que se utilizará como parámetro para la tarea que se está creando. Como no lo usamos ponemos NULL
                 tskIDLE_PRIORITY+1,        //Prioridad de la tarea
                 &xHandle2,                 //Puntero a la tarea
                 PROCESADORB                //Procesador donde se ejecuta la tarea
                );
    configASSERT( xHandle2 );                //entra si no se pudieron crear las tareas, para debug

    xTaskCreatePinnedToCore( tareaUno,                  //Función que implementa la tarea. La misma no debe retornar.
                 "Tarea uno",               //Nombre que reprenta la tarea, para facilitar la depuración.
                 configMINIMAL_STACK_SIZE,  //Tamaño del stack en bytes
                 NULL,                      //Puntero que se utilizará como parámetro para la tarea que se está creando. Como no lo usamos ponemos NULL
                 tskIDLE_PRIORITY+2,          //Prioridad de la tarea
                 &xHandle1,                 //Puntero a la tarea
                 PROCESADORB                //Procesador donde se ejecuta la tarea
                );
    configASSERT( xHandle1 );                //entra si no se pudieron crear las tareas, para debug

    gpio_pad_select_gpio(PULSADOR);
	gpio_set_direction(PULSADOR, GPIO_MODE_INPUT);
	gpio_set_pull_mode(PULSADOR, GPIO_PULLDOWN_ONLY);
    
    while(true)
    {
        if (gpio_get_level(PULSADOR))   //no es necesario quedo del programa anterior
        {
            //Borra la tarea usando el handle
            if( xHandle2 != NULL )
            {
            vTaskDelete( xHandle2 );
            }
        }
        vTaskDelay(RETARDO_MS);
        //Muestra el espacio mínimo libre de stack que ha habido desde que comenzó la tarea.(mientras mas cerca de 0 este mas peligroso es de quedarse sin memoria)
        //Cuanto menor sea el número devuelto, más cerca está la tarea de desbordar su stack.
        printf( "Task %u min %u bytes\r\n", 2,  uxTaskGetStackHighWaterMark( xHandle2));
        printf( "Task %u min %u bytes\r\n", 1,  uxTaskGetStackHighWaterMark( xHandle1));
    }
}

void tareaUno( void * pvParameters )
{
    gpio_pad_select_gpio(SALIDA1);
    gpio_set_direction(SALIDA1, GPIO_MODE_OUTPUT);
    while (true)
    {
        gpio_set_level(SALIDA1, 1);
        vTaskDelay(RETARDO_MS);
        gpio_set_level(SALIDA1,0);
        vTaskDelay(RETARDO_MS);
    }
}
//Definición de la tarea
void tareaDos( void * pvParameters )
{
    gpio_pad_select_gpio(SALIDA2);
    gpio_set_direction(SALIDA2, GPIO_MODE_OUTPUT);

    while (true)
    {
        gpio_set_level(SALIDA2, 1);
        vTaskDelay(RETARDO_MS);
        gpio_set_level(SALIDA2,0);
        vTaskDelay(RETARDO_MS);
    }
}