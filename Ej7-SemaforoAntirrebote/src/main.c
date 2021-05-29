#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../include/semaforo.h"
#include "../include/pulsador.h"
#include "driver/gpio.h"

#define PULSADOR GPIO_NUM_18
#define T 10/portTICK_PERIOD_MS //tiempo en ms de espera para volver a ingresar a la función de actualizar semaforo

extern int cambioModo;

void app_main()
{    
    iniciarSemaforo();

    inicializarBoton( GPIO_NUM_18);

    while(1)
    {
        actualizarBoton(PULSADOR);

        if(cambioModo == 0)
        {
            actualizarSemaforoNormal();
        }
        else
        {
            actualizarSemaforoIntermitente();
        }
        
        vTaskDelay(T);
    }
}