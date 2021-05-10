/* Aalumno: Darío Río, 5tp año, Ingenieria Eletrónica 2020´*/

/*Ej4-Semaforo: Realizar un semáforo con 3 leds y un pulsador. El pulsador debe cambiar entre el modo normal de funcionamiento y el modo intermitente. Utilizar los siguientes módulos:
• main.c y main.h
• semaforo.c y semaforo.h
• led.c y led.h
• tecla.c y tecla.hEj4-Semaforo: Realizar un semáforo con 3 leds y un pulsador. El pulsador debe cambiar entre el modo normal de funcionamiento y el modo intermitente. Utilizar los siguientes módulos:
• main.c y main.h
• semaforo.c y semaforo.h
• led.c y led.h
• tecla.c y tecla.h*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../include/semaforo.h" // los caracteres ../ significa que vaya una carpeta arriba entre a la carpeta include y me agregue el semaforo.h

void app_main()
{
    iniciarSemaforo();

    while(1)
    {
        actualizarSemaforo();
    }
}