/*
Ejercicio N°: 16
Alumono: Darío Río
Carrera: Ing. Electrónica
Curso: 5to
Año: 2021
Clase N°: 9b 
*/
#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/FreeRTOSConfig.h"
#include "driver/gpio.h"
#include <math.h>

#define N_LED       3
#define TON_LED     pdMS_TO_TICKS(500) // ( 500 / portTICK_RATE_MS );
#define PERIODO     pdMS_TO_TICKS(1000)
#define PROCESADORA 0
#define PROCESADORB 1

typedef struct
{
    gpio_int_type_t pin;
    TickType_t tiempoOn;		//tiempo Duty o ciclo de trabajo
    TickType_t periodo;
} led_t;

gpio_int_type_t pines[N_LED]  = {GPIO_NUM_25, GPIO_NUM_26, GPIO_NUM_27}; /// Arreglo para los distintos pines
led_t leds [N_LED];             ///Un arreglode la estructura de arriba 
uint32_t tiempoLeds [N_LED];    /// Un arreglo  de tiempos de led

void tareaDestello( void* taskParmPtr ); //Prototipo de la función de la tarea

void app_main()
{
    // Crear tarea en freeRTOS
    // Devuelve pdPASS si la tarea fue creada y agregada a la lista ready
    // En caso contrario devuelve pdFAIL.
    for(int i=0; i<N_LED; i++) /// Mediante este for creo varias tareas destello
    {
        leds[i].pin = pines[i];
        leds[i].tiempoOn = TON_LED * pow(2,i); //i=0 -> 1; i=1 -> 2; i=4;  
        leds[i].periodo = PERIODO * pow(2,i);  /// Como arriba lo multiplico por la potencia 2^i 

        BaseType_t res = xTaskCreate(
            tareaDestello,                     	// Funcion de la tarea a ejecutar
            "tareaDestello",   	                // Nombre de la tarea como String amigable para el usuario
            configMINIMAL_STACK_SIZE, 		// Cantidad de stack de la tarea
            &leds[i],                          	// Parametros de tarea /// Le estoy pasando una referencia de la direccion de esa variable y en base a eso trabajo con puntero 
            tskIDLE_PRIORITY+i,         	// Prioridad de la tarea -> Queremos que este un nivel encima de IDLE
            NULL                          		// Puntero a la tarea creada en el sistema
        );
        // Gestion de errores
        if(res == pdFAIL)
        {
            printf( "Error al crear la tarea.\r\n" );
            while(true);					// si no pudo crear la tarea queda en un bucle infinito
        }
    }
}

// Implementacion de funcion de la tarea
void tareaDestello( void* taskParmPtr )
{
    // ---------- Configuraciones ------------------------------
    led_t* led = (led_t*) taskParmPtr; /// Recibe el parametro y lo combierte en un puntero
    gpio_pad_select_gpio(led->pin);    /// Como traqbajamos con un puntero para acceder a los datos de la estructura, usamos la flecha 
    gpio_set_direction(led->pin, GPIO_MODE_OUTPUT); ///accedo al pin

    TickType_t xLastWakeTime = xTaskGetTickCount(); /// Verificavamos el tiempo

    // ---------- Bucle infinito --------------------------
    while( true )
    {
        gpio_set_level(led->pin, 1); /// Le paso el pin para reder el led
        vTaskDelay( led->tiempoOn);  /// Le paso el tiempo que tengo en la estructura
        gpio_set_level(led->pin, 0); /// Le paso el in para apagarlo 
        // Envia la tarea al estado bloqueado durante xPeriodicity (delay periodico)
        vTaskDelayUntil( &xLastWakeTime , led->periodo ); /// Le paso el periodo para hacer el  vTaskDelayUntil y tener el periodo asociado a cada led
    }
}