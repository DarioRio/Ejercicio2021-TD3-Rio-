/*
Ejercicio N°: 12
Alumono: Darío Río
Carrera: Ing. Electrónica
Curso: 5to
Año: 2021
*/
#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/FreeRTOSConfig.h"
#include "driver/gpio.h"

#define SALIDA1     GPIO_NUM_25
#define PERIODO_MS  1000 //Dario: 1seg 
#define PERIODO     pdMS_TO_TICKS(PERIODO_MS)//Dario: los 1000 ms los tranfromo en TIKCS
#define PROCESADORA 0
#define PROCESADORB 1
#define INCREMENTO 100
#define MAX_INC  (PERIODO_MS - INCREMENTO)

void tareaDestello( void* taskParmPtr ); //Prototipo de la función de la tarea

void app_main()
{
    // Crear tarea en freeRTOS
    // Devuelve pdPASS si la tarea fue creada y agregada a la lista ready
    // En caso contrario devuelve pdFAIL.
    BaseType_t res = xTaskCreatePinnedToCore(
    	tareaDestello,                     	// Funcion de la tarea a ejecutar
        "tareaDestello",   	                // Nombre de la tarea como String amigable para el usuario
        configMINIMAL_STACK_SIZE, 		// Cantidad de stack de la tarea
        NULL,                          	// Parametros de tarea
        tskIDLE_PRIORITY+1,         	// Prioridad de la tarea -> Queremos que este un nivel encima de IDLE
        NULL,                          		// Puntero a la tarea creada en el sistema
        PROCESADORA
    );

    // Gestion de errores
	if(res == pdFAIL)
	{
		printf( "Error al crear la tarea.\r\n" );
		while(true);					// si no pudo crear la tarea queda en un bucle infinito
	}
}

// Implementacion de funcion de la tarea
void tareaDestello( void* taskParmPtr )
{
    // ---------- Congiguraciones ------------------------------
    gpio_pad_select_gpio(SALIDA1);
    gpio_set_direction(SALIDA1, GPIO_MODE_OUTPUT);

    TickType_t xPeriodicity =  PERIODO;			// Tarea periodica cada 1000 ms

    TickType_t xLastWakeTime = xTaskGetTickCount(); //Dario: genero una bandera de tiempo

    uint16_t duty = 0;

    // ---------- Bucle infinito --------------------------
    while( true )
    {
        duty += INCREMENTO;

        gpio_set_level(SALIDA1, 1);
        vTaskDelay ( pdMS_TO_TICKS(duty) );
        gpio_set_level(SALIDA1, 0);

        if ( duty == MAX_INC )
        {
            duty = 0;
        }

        ets_delay_us(100000); //delay que representa cualquier otra instrucción que podría hacer esta tarea

        // Envia la tarea al estado bloqueado durante xPeriodicity (delay periodico)
        vTaskDelayUntil( &xLastWakeTime , xPeriodicity );//esto me corrige le tiempo que me falta pero si me paso ya no
    }
}