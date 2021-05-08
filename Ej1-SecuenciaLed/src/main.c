/* Río Darío Ingenieria Electronica 5to*/ 
/*Ej1-SecuenciaLed: Prender secuencialmente 3 leds. En todo momento habrá encendido solamente 1 led.
Utilizar 2 pulsadores para controlar el sentido de encendido. Por ejemplo:
Pulsador A: led1 > led2 > led3 > led1 > …
Pulsador B: led1 > led3 > led2 > led1 > …
Algunas preguntas para pensar:
• ¿Es fácil agregar más leds a cada secuencia?
• ¿Se puede cambiar el sentido de la secuencia en cualquier momento de la ejecución?
• ¿Responde adecuadamente el programa a la pulsación de la tecla?*/

#include "../driver/include/driver/gpio.h"  // para todas las funciones de entrada y salidas de proposito general
#include "freertos/FreeRTOS.h" // estas dos son bibliotecas sitemas operativos de tiempo real para los delay
#include "freertos/task.h"     //

#define N_LED 		3
#define N_PULSADOR 	2
#define T_ON		500/portTICK_PERIOD_MS

int led [N_LED] = {GPIO_NUM_27, GPIO_NUM_26, GPIO_NUM_25}; //defino arreglo, el tamaño del arreglo esta dado por N_LED que es 3
int pulsador [N_PULSADOR] = {GPIO_NUM_32, GPIO_NUM_35}; //defino arreglo 

void app_main()
{
	//Configuración
	for(int i = 0; i < N_LED; i++){
		gpio_pad_select_gpio(led[i]); //selecciono el pin de la placa a usar con un arreglo
		gpio_set_direction(led[i], GPIO_MODE_OUTPUT);// los declaro como salida
	}
	
	for(int i = 0; i < N_PULSADOR; i++){
		gpio_pad_select_gpio(pulsador[i]); //selecciono el pin de la placa a usar con un arreglo
		gpio_set_direction(pulsador[i], GPIO_MODE_INPUT); // los declaro como entrada
		gpio_set_pull_mode(pulsador[i], GPIO_PULLDOWN_ONLY); //recistencia de pull down 
	}

   int i = 0, sentido = 0;
   //Bucle infinito
   while( true )
    {
		if (gpio_get_level(pulsador[0]) == 1) //leer el pin 
		{
			sentido = 1;
		}
	   	else if (gpio_get_level(pulsador[1]) == 1)
		{
			sentido = 0;   
		}	

	   	if (sentido == 0)
		{
			gpio_set_level(led[i], 0);
			i++;
			if ( i >= N_LED ){
				i = 0;
			}
			gpio_set_level(led[i], 1);
		}
	   	else 
		{
			gpio_set_level(led[i], 0);
			i--;
			if ( i < 0 ){
				i = N_LED;
			}
			gpio_set_level(led[i], 1);
		}
		vTaskDelay(T_ON);	
		
	}
   return 0;
}
/*
#define LED1 GPIO_NUM_32 //ver de crear un tipo de datos
#define LED2 GPIO_NUM_33
#define LED3 GPIO_NUM_25
#define PULSADOR1 GPIO_NUM_26
#define PULSADOR2 GPIO_NUM_27
#define T_ON		500/portTICK_PERIOD_MS
void app_main()
{
	//Configuración
	gpio_pad_select_gpio(LED1);
	gpio_set_direction(LED1, GPIO_MODE_OUTPUT);
	gpio_pad_select_gpio(LED2);
	gpio_set_direction(LED2, GPIO_MODE_OUTPUT);
	gpio_pad_select_gpio(LED3);
	gpio_set_direction(LED3, GPIO_MODE_OUTPUT);
	gpio_pad_select_gpio(PULSADOR1);
	gpio_set_direction(PULSADOR1, GPIO_MODE_INPUT);
	gpio_pad_select_gpio(PULSADOR2);
	gpio_set_direction(PULSADOR2, GPIO_MODE_INPUT);
   int i = 0;
   unsigned int sentido = 0;
   // ----- Repeat for ever -------------------------
   while( true )
    {
	   	if (gpio_get_level(PULSADOR1) == 0)
		{
			sentido = 1;
		}
	   	else if (gpio_get_level(PULSADOR2) == 0)
		{
			sentido = 0;
		}
		if ( i == 0 ){
			gpio_set_level(LED1, 1);
			gpio_set_level(LED2, 0);
			gpio_set_level(LED3, 0);
		}
		if ( i == 1 ){
			gpio_set_level(LED1, 0);
			gpio_set_level(LED2, 1);
			gpio_set_level(LED3, 0);
		}
		if ( i == 2 ){
			gpio_set_level(LED1, 0);
			gpio_set_level(LED2, 0);
			gpio_set_level(LED3, 1);
		}
		if(sentido == 0){
			i++;
		}
		else{
			i--;
		}
		if ( i < 0 ){
		i = 2;
		}
		if ( i > 2 ){
		i = 0;
		}
		vTaskDelay(T_ON);
	}
   return 0;
}
*/