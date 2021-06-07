/*
Ejercicio N°: 15
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
#include "pulsador.h"

#define SALIDA1     GPIO_NUM_25
#define T_ESPERA_MS  40
#define T_ESPERA     pdMS_TO_TICKS(T_ESPERA_MS)
#define PROCESADORA 0
#define PROCESADORB 1

void tareaDestello( void* taskParmPtr ); //Prototipo de la función de la tarea
TaskHandle_t xHandle1 = NULL;           ///Puntero a la tarea, lo apuntamos a nulo
void app_main()
{
    // Crear tarea en freeRTOS
    // Devuelve pdPASS si la tarea fue creada y agregada a la lista ready
    // En caso contrario devuelve pdFAIL.
    inicializarPulsador();

    
    if (CrearTareaDestello == 1)
    {
          BaseType_t res = xTaskCreatePinnedToCore(
    	tareaDestello,                     	// Funcion de la tarea a ejecutar
        "tareaDestello",   	                // Nombre de la tarea como String amigable para el usuario
        configMINIMAL_STACK_SIZE, 		// Cantidad de stack de la tarea
        NULL,                          	// Parametros de tarea
        tskIDLE_PRIORITY+1,         	// Prioridad de la tarea -> Queremos que este un nivel encima de IDLE
        &xHandle1,                  //Puntero a la tarea, me va permitir suspenderla o eliminarla
        PROCESADORA
    );
    CrearTareaDestello = 0;
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
    // ---------- Congiguraciones ------------------------------
    gpio_pad_select_gpio(SALIDA1);
    gpio_set_direction(SALIDA1, GPIO_MODE_OUTPUT);

    TickType_t dif;

    // ---------- Bucle infinito --------------------------
   // while( true )
    {
        dif = obtenerDiferencia();

        if( dif > TIEMPO_NO_VALIDO )
        {
            gpio_set_level( SALIDA1, 1 );
            vTaskDelay( dif );
            gpio_set_level( SALIDA1, 0 );
            borrarDiferencia();
        }
        else
        {
            vTaskDelay( T_ESPERA );
        }
             //Borra la tarea usando el handle
            if( xHandle1 != NULL )      //Nos aseguramos de que no sea NULL para que no elimine la tarea actual
            {
            vTaskDelete( xHandle1 );    //Elimina la tarea /con el supend la suspendo en vez de eliminarla
            xHandle1 = NULL;
            }
    }
}