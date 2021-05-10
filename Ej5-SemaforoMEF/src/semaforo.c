#include "../include/led.h"
#include "../include/semaforo.h"

//definiciones para los pines donde se conectan los leds
#define LED_VERDE GPIO_NUM_25
#define LED_AMARILLO GPIO_NUM_26
#define LED_ROJO GPIO_NUM_27

#define T_VERDE		300
#define T_AMARILLO	100
#define T_ROJO		500

// Tipo de datos para la variable de estados
typedef enum{
    ROJO,
    ROJO_AMARILLO,
    VERDE,
    AMARILLO
} estadoMEF_t;

estadoMEF_t estadoActual, estadoAnterior; // Variable de estado (global)

int contador; //variable para contar la cantidad de veces que ingresa a la funcipon actualizar MEF

// Función Inicializar MEF
void iniciarSemaforo(void){
	configurarLed(LED_ROJO, LED_AMARILLO, LED_VERDE);
	estadoActual = ROJO;
	estadoAnterior = AMARILLO;
	contador = 0;
}

// Función Actualizar MEF
void actualizarSemaforo(void)
{
	switch (estadoActual) {
		case ROJO:
        {
            // Actualizar salida del estado
			if(estadoAnterior != estadoActual)
			{
				prenderLed('R');
				apagarLed('A');
				apagarLed('V');
				estadoAnterior = estadoActual;
			}
    		// Chequear condiciones de transición de estado
			if(contador == T_ROJO ){
				// Cambiar a otro estado
				 estadoActual = ROJO_AMARILLO;
				 contador = 0;
			}
			contador++;
		}
		break;
		case ROJO_AMARILLO:{
			// Actualizar salida del estado
			if(estadoAnterior != estadoActual)
			{
				prenderLed('R');
				prenderLed('A');
				apagarLed('V');
				estadoAnterior = estadoActual;
			}
    		// Chequear condiciones de transición de estado
			if(contador == T_AMARILLO ){
				// Cambiar a otro estado
				 estadoActual = VERDE;
				 contador = 0;
			}
			contador++;
		}
		break;
		case VERDE:{
			// Actualizar salida del estado
			if(estadoAnterior != estadoActual)
			{
				apagarLed('R');
				apagarLed('A');
				prenderLed('V');
				estadoAnterior = estadoActual;
			}
    		// Chequear condiciones de transición de estado
			if(contador == T_VERDE ){
				// Cambiar a otro estado
				 estadoActual = AMARILLO;
				 contador = 0;
			}
			contador++;
		}
		break;
		case AMARILLO:{
			// Actualizar salida del estado
			if(estadoAnterior != estadoActual)
			{
				apagarLed('R');
				prenderLed('A');
				apagarLed('V');
				estadoAnterior = estadoActual;
			}
    		// Chequear condiciones de transición de estado
			if(contador == T_AMARILLO ){
				// Cambiar a otro estado
				 estadoActual = ROJO;
				 contador = 0;
			}
			contador++;
		}
		break;
		default:{
			//Si cae en un estado no valido, reinicio
			iniciarSemaforo();
		}
		break;
	}	
}