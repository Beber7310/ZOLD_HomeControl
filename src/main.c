#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#define MAIN_CODE
#include "radiateur.h"
#include "SerialManagement.h"
#include "Components.h"

#include "utils.h"

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
	info("START UP","\n\n    ---- Home control ---- \n");

	sem_init(&sem_capteur_data_available, 0,0);

	if (pthread_create (&th_radiateur, NULL, radiateur_loop, 0) < 0)
	{
		info("START UP","pthread_create error for thread radiateur_loop");
		exit (1);
	}
	info("START UP","Thread radiateur created");

	if (pthread_create (&th_uart, NULL, uart_rf_loop, 0) < 0)
	{
		info("START UP","pthread_create error for thread uart_rf_loop");
		exit (1);
	}
	info("START UP","Thread rf created\n");

	while(1)
	{
		sleep(1);
	}
	return 0;
}
