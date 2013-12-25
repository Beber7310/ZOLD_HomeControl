/*
 * radiateur.c
 *
 *  Created on: 16 déc. 2013
 *      Author: Bertrand
 */
#include <stdio.h>
#include <string.h>

#include "Components.h"
#include "radiateur.h"
#include "utils.h"
#include "SerialManagement.h"

extern radiateur_t 		radiateur[RD_LAST];
extern interrupter_t 	interrupter[IT_LAST];
extern thermometer_t	thermometer[TH_LAST];

void radiateur_init(void)
{
	radiateur[RD_CUISINE].type= FIL_PILOTE;
	radiateur[RD_CUISINE].index = 0;
	radiateur[RD_CUISINE].thermometer=-1;
	radiateur[RD_CUISINE].interupteur=IT_CUISINE;
	radiateur[RD_CUISINE].calculated_target_temp = 0;
	radiateur[RD_CUISINE].expected_state = 0;

	radiateur[RD_SALON].type= FIL_PILOTE;
	radiateur[RD_SALON].index = 1;
	radiateur[RD_SALON].thermometer=TH_SALON;
	radiateur[RD_SALON].interupteur=-1;
	radiateur[RD_SALON].calculated_target_temp = 0;
	radiateur[RD_SALON].expected_state = 0;

	radiateur[RD_VICTOR].type= FIL_PILOTE;
	radiateur[RD_VICTOR].index = 2;
	radiateur[RD_VICTOR].thermometer=TH_VICTOR;
	radiateur[RD_VICTOR].interupteur=-1;
	radiateur[RD_VICTOR].calculated_target_temp = 0;
	radiateur[RD_VICTOR].expected_state = 0;

	radiateur[RD_DAPHNEE].type= FIL_PILOTE;
	radiateur[RD_DAPHNEE].index = 3;
	radiateur[RD_DAPHNEE].thermometer=TH_DAPHNEE;
	radiateur[RD_DAPHNEE].interupteur=-1;
	radiateur[RD_DAPHNEE].calculated_target_temp = 0;
	radiateur[RD_DAPHNEE].expected_state = 0;



	radiateur[RD_HOMECINEMA].type= FIL_PILOTE;
	radiateur[RD_HOMECINEMA].index = 4;
	radiateur[RD_HOMECINEMA].thermometer=-1;
	radiateur[RD_HOMECINEMA].interupteur=IT_HOMECINEMA;
	radiateur[RD_HOMECINEMA].calculated_target_temp = 0;
	radiateur[RD_HOMECINEMA].expected_state = 0;

}

void thermometer_init(void)
{
	// TH_EXTERIEUR,TH_GARAGE,TH_SALON,TH_DAPHNEE,TH_VICTOR,TH_BARNABE
	thermometer[TH_EXTERIEUR].mesure_date=0;
	thermometer[TH_EXTERIEUR].temperature=19.0f;
	strcpy(thermometer[TH_EXTERIEUR].id,">281C0CC8030000D8");

	thermometer[TH_GARAGE].mesure_date=0;
	thermometer[TH_GARAGE].temperature=19.0f;
	strcpy(thermometer[TH_GARAGE].id,">28E01DC803000066");

	thermometer[TH_SALON].mesure_date=0;
	thermometer[TH_SALON].temperature=19.0f;
	strcpy(thermometer[TH_SALON].id,">28980CC8030000EE");

	thermometer[TH_DAPHNEE].mesure_date=0;
	thermometer[TH_DAPHNEE].temperature=19.0f;
	strcpy(thermometer[TH_DAPHNEE].id,">28ADE14A0400007A");

	thermometer[TH_VICTOR].mesure_date=0;
	thermometer[TH_VICTOR].temperature=19.0f;
	strcpy(thermometer[TH_VICTOR].id,">2877EB4A040000CC");

	thermometer[TH_BARNABE].mesure_date=0;
	thermometer[TH_BARNABE].temperature=19.0f;
	strcpy(thermometer[TH_BARNABE].id,">2816B14A04000010");

}

void interupter_init(void)
{
	enum Interrupter_name { IT_HOMECINEMA=0,IT_CUISINE,IT_GARAGE,IT_LAST};

	typedef struct {
		time_t action_date;
		int action;
		char id[18];
	} interrupter_t;

	interrupter[IT_HOMECINEMA].action_date=0;
	interrupter[IT_HOMECINEMA].action=0;
	strcpy(interrupter[IT_HOMECINEMA].id,">0000000000081422");

	interrupter[IT_CUISINE].action_date=0;
	interrupter[IT_CUISINE].action=0;
	strcpy(interrupter[IT_CUISINE].id,">000000000008103A");

	interrupter[IT_GARAGE].action_date=0;
	interrupter[IT_GARAGE].action=0;
	strcpy(interrupter[IT_GARAGE].id,">0000000000088722");



}

void radiateur_evaluate_next_state(int rad)
{
	float targ_temp,measured_temp;

	time_t rawtime;
	struct tm * timeinfo;
	int index_prog;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	index_prog=((timeinfo->tm_wday*24*60)+(timeinfo->tm_hour*60)+timeinfo->tm_min)/15;

	targ_temp=radiateur[rad].program[index_prog];

	if(radiateur[rad].interupteur>=0)
	{
		if(((time(NULL)-interrupter[radiateur[rad].interupteur].action_date)<3600) &&(interrupter[radiateur[rad].interupteur].action==1))
		{
			targ_temp=21.0f;
		}
	}

	radiateur[rad].calculated_target_temp=targ_temp;

	if(radiateur[rad].thermometer>=0)
	{
		measured_temp=thermometer[radiateur[rad].thermometer].temperature;
	}
	else
	{
		measured_temp=19.0f;
	}

	if(measured_temp<targ_temp)
	{
		if(radiateur[rad].expected_state==0)
			info("RADIATEUR","Switch on radiator %i",rad);
		radiateur[rad].expected_state=1;
	}
	else
	{
		if(radiateur[rad].expected_state==1)
			info("RADIATEUR","Switch off radiator %i",rad);
		radiateur[rad].expected_state=0;
	}
}

void * radiateur_loop(void * arg)
{
	int ii;

	radiateur_init();
	thermometer_init();
	interupter_init();

	while(1)
	{
		for(ii=0;ii<RD_LAST;ii++)
		{
			radiateur_evaluate_next_state(ii);
		}


		SerialFilPiloteSendCommande();
		sem_wait(&sem_capteur_data_available);

	}
}
