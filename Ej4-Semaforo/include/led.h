#ifndef LED_H //chequea que otro archivo no haya llamado a led.h
#define LED_H

#include "driver/gpio.h" // porque voy a confgurar las salidas para los leds

void configurarLed(gpio_int_type_t ledR, gpio_int_type_t ledA, gpio_int_type_t ledV); //especifica en que pines conectar cada led: ROJO, AMARILLO, VERDE, // pongo void porque esta funcion no devuelve nada// este es el prototipo de la funcion

void prenderLed(char led);

void apagarLed(char led);

#endif   