#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>


#define MAIN_CODE
#include "radiateur.h"
#include "SerialManagement.h"
#include "Components.h"
#include "rrd.h"
#include "http.h"
#include "utils.h"

int main()
{
	pthread_t th_radiateur;
	pthread_t th_uart;
	pthread_t th_uart_fp;
	pthread_t th_http;

	init_msg();

	info("START UP","\n\n    ---- Home control ---- \n");
    setpriority(PRIO_PROCESS, 0, -10);

    if (pthread_create (&th_uart, NULL, uart_rf_loop, 0) < 0)
	{
		info("START UP","pthread_create error for thread uart_rf_loop");
		exit (1);
	}

    if (pthread_create (&th_uart_fp, NULL, uart_filPilote_loop, 0) < 0)
    	{
    		info("START UP","pthread_create error for thread uart_filPilote_loop");
    		exit (1);
    	}


/*
    while(1)
    {
    		sleep(1);
        	SendBlyssCmd(5,1);
        	sleep(1);
        	SendBlyssCmd(5,0);
    }*/

	sem_init(&sem_capteur_data_available, 0,0);

	if (pthread_create (&th_radiateur, NULL, radiateur_loop, 0) < 0)
	{
		info("START UP","pthread_create error for thread radiateur_loop");
		exit (1);
	}
	info("START UP","Thread radiateur created");

	if (pthread_create (&th_http, NULL, http_loop, 0) < 0)
	{
		info("START UP","pthread_create error for thread http_loop");
		exit (1);
	}
	info("START UP","Thread http created");




	info("START UP","Thread rf created");

	while(1)
	{
		sleep(1);
	}
	return 0;
}
