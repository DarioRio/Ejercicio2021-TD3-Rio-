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
    AMARILLO,
	INTERMITENTE_A,
	INTERMITENTE_B
} estadoMEF_t;

estadoMEF_t estadoActual, estadoAnterior, estadoActualIntermitente, estadoAnteriorIntermitente; // Variable de estado (global)

int contadorNormal, contadorIntermitente; //variable para contar la cantidad de veces que ingresa a la funcipon actualizar MEF

// Función Inicializar MEF
void iniciarSemaforo(void){
	configurarLed(LED_ROJO, LED_AMARILLO, LED_VERDE);
	estadoActual = ROJO;
	estadoActualIntermitente = INTERMITENTE_A;
	estadoAnterior = AMARILLO;
	estadoAnteriorIntermitente = INTERMITENTE_B;
	contadorNormal = 0;
	contadorIntermitente = 0;
}

// Función Actualizar MEF
void actualizarSemaforoNormal(void)
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
			if(contadorNormal == T_ROJO ){
				// Cambiar a otro estado
				 estadoActual = ROJO_AMARILLO;
				 contadorNormal = 0;
			}
			contadorNormal++;
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
			if(contadorNormal == T_AMARILLO ){
				// Cambiar a otro estado
				 estadoActual = VERDE;
				 contadorNormal = 0;
			}
			contadorNormal++;
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
			if(contadorNormal == T_VERDE ){
				// Cambiar a otro estado
				 estadoActual = AMARILLO;
				 contadorNormal = 0;
			}
			contadorNormal++;
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
			if(contadorNormal == T_AMARILLO ){
				// Cambiar a otro estado
				 estadoActual = ROJO;
				 contadorNormal = 0;
			}
			contadorNormal++;
		}
		break;
		default:{
			//Si cae en un estado no valido, reinicio
			iniciarSemaforo();
		}
		break;
	}	
}

// Función Actualizar MEF
void actualizarSemaforoIntermitente(void)
{
	switch (estadoActualIntermitente) {
		case INTERMITENTE_A:{
			// Actualizar salida del estado
			if(estadoAnteriorIntermitente != estadoActualIntermitente)
			{
				apagarLed('R');
				prenderLed('A');
				apagarLed('V');
				estadoAnteriorIntermitente = estadoActualIntermitente;
			}
    		// Chequear condiciones de transición de estado
			if(contadorIntermitente == T_AMARILLO ){
				// Cambiar a otro estado
				 estadoActualIntermitente = INTERMITENTE_B;
				 contadorIntermitente = 0;
			}
			contadorIntermitente++;
		}
		break;
		case INTERMITENTE_B:{
			// Actualizar salida del estado
			if(estadoAnteriorIntermitente != estadoActualIntermitente)
			{
				apagarLed('R');
				apagarLed('A');
				apagarLed('V');
				estadoAnteriorIntermitente = estadoActualIntermitente;
			}
    		// Chequear condiciones de transición de estado
			if(contadorIntermitente == T_AMARILLO ){
				// Cambiar a otro estado
				 estadoActualIntermitente = INTERMITENTE_A;
				 contadorIntermitente = 0;
			}
			contadorIntermitente++;
		}
		break;
		default:{
			//Si cae en un estado no valido, reinicio
		}
		break;
	}	
}