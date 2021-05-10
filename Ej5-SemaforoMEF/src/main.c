#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../include/semaforo.h"

#define T 10/portTICK_PERIOD_MS //tiempo en ms de espera para volver a ingresar a la función de actualizar semaforo

void app_main()
{    
    iniciarSemaforo();

    while(1)
    {
        actualizarSemaforo();
        vTaskDelay(T);
    }
}