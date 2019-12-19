/*
 * Components.h
 *
 *  Created on: 16 déc. 2013
 *      Author: Bertrand
 */

#ifndef COMPONENTS_H_
#define COMPONENTS_H_

#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
///////////////////////////////////////////////////////////////////////////////////
//
//	Radiateur
//

enum radiateur_type { FIL_PILOTE,RF_CONTROLED,SONOFF_HTTP };
enum radiateur_name { RD_HOMECINEMA=0,RD_SALON,RD_BARNABE,RD_DAPHNEE,RD_CUISINE,RD_VICTOR,RD_PARENT,RD_LAST};

typedef struct {
	enum 	radiateur_type type;
	char 	name[32];
	char 	mqtt_topic[256];
	int 	index;
	float 	program[7*24*4];
	int 	thermometer;
	int 	interupteur;
	int 	calculated_target_temp;
	int 	expected_state;
	time_t	http_req_time;
	int		http_req_temp;
	int 	mirror_state;
	time_t	mirror_time;
} radiateur_t;


///////////////////////////////////////////////////////////////////////////////////
//
//	Thermometer
//



enum thermometer_name { TH_BROKEN=0,TH_GARAGE,TH_SALON,TH_BARNABE,TH_VICTOR,TH_CUISINE,TH_DAPHNE,TH_LAST};

typedef struct {
	char name[32];
	char mqtt_topic[256];
	float temperature;
	float hygrometrie;
	time_t mesure_date;
	char id[32];
	char type;
	int smsSent;
} thermometer_t;


///////////////////////////////////////////////////////////////////////////////////
//
//	Interrupter
//
enum Interrupter_name { IT_HOMECINEMA=0,IT_BARNABE,IT_GARAGE,IT_OLD_1,IT_SOFIA,IT_LAST};

typedef struct {
	time_t action_date;
	int action;
	char id[18];
} interrupter_t;


enum Light_name { LI_GARAGE=0,LI_ETABLI,LI_ATELIER,LI_PRISE_1,LI_AMPOULE_DISCO,LI_VMC,LI_RAD_BARNABE,LI_RAD_VICTOR,LI_LAST};//
typedef struct {
	char name[32];
	time_t action_date;
	int blyss_id;
	int presence;
	int interupteur[20];
} light_t;

enum Presence_name { PR_GARAGE=0,PR_ATELIER,PR_LAST};
typedef struct {
	char name[32];
	time_t action_date;
	char id[32];
	char mqtt_topic[256];
} presence_t;

typedef struct {
	unsigned int last_rain;
	unsigned int current_rain;
	unsigned int falled;
} rain_t;

typedef struct {
	float current;
	float power;
} power_t;

#ifdef MAIN_CODE
	#define EXT
#else
	#define EXT extern
#endif

EXT radiateur_t 	radiateur[RD_LAST];
EXT interrupter_t 	interrupter[IT_LAST];
EXT thermometer_t	thermometer[TH_LAST];
EXT presence_t		presence[PR_LAST];
EXT light_t			light[LI_LAST];
EXT rain_t			rain;
EXT power_t			power;

EXT sem_t 			sem_capteur_data_available;
EXT sem_t 			sem_blyss;


#endif /* COMPONENTS_H_ */
