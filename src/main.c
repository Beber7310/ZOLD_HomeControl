#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#define MAIN_CODE
#include "radiateur.h"
#include "SerialManagement.h"
#include "Components.h"

sem_t sem_capteur_data_available;

int main()
{
	pthread_t th_radiateur;
	pthread_t th_uart;
/*
	SerialSeup();
	sleep(5);
	while(1)
	{
		SerialSendChar(ii++);
		printf ("%i\n",ii);
		sleep(1);
	}
	return 0;
*/

	sem_init(&sem_capteur_data_available, 0,0);


	if (pthread_create (&th_radiateur, NULL, radiateur_loop, 0) < 0)
	{
		printf ("pthread_create error for thread radiateur_loop\n");
		exit (1);
	}

	if (pthread_create (&th_uart, NULL, uart_rf_loop, 0) < 0)
	{
		printf ("pthread_create error for thread uart_rf_loop\n");
		exit (1);
	}

	while(1)
	{
		sleep(1);
	}
	return 0;
}
