#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../include/pulsador.h"

#define T		10/portTICK_PERIOD_MS //defino el tiempo
#define PULSADOR    GPIO_NUM_18       //defino mi pin de entrada

void app_main() //nuestro bucle principal
{
    inicializarBoton(PULSADOR); //llamamos la funcion inicializar boton y le pasamos como argumento la variable Pulsador 
    while(true){
        actualizarBoton(PULSADOR);
        vTaskDelay(T);
    }
}
