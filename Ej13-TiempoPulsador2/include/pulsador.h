#ifndef PULSADOR_H_
#define PULSADOR_H_
/*==================[ Inclusiones ]============================================*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
/*==================[ Definiciones ]===================================*/
#define TIEMPO_NO_VALIDO   0

typedef enum // Darío: Maquina de estado para el anti-rebote
{
    ALTO,
    BAJO,
    DESCENDENTE,
    ASCENDENTE
} estadoPulsador;

typedef struct  //Dario:en esta estructura guardo varios datos
{
    gpio_int_type_t tecla; //Dario: Guardo el pin del pulsador que voy a conectaar a la placa
    estadoPulsador estado;   //variables
    TickType_t tiempoBajo;		//tiempo de la última transición del estado alto a bajo
    TickType_t tiempoAlto;		    //tiempo de la última transición del estado bajo a alto
    TickType_t diferenciaTiempo;	    //variables /Dario: Diferencia de tiempo desde que yo lo tengo pulsado hasta que lo solte
} pulsadorInfo;

/*==================[Prototipos de funciones]======================*/
void inicializarPulsador( void );
TickType_t obtenerDiferencia( void);
void borrarDiferencia( void );

#endif