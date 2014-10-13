/*
 * radiateur.c
 *
 *  Created on: 16 déc. 2013
 *      Author: Bertrand
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


#include "Components.h"
#include "radiateur.h"
#include "utils.h"
#include "SerialManagement.h"
#include "rrd.h"

/*
extern radiateur_t 		radiateur[RD_LAST];
extern interrupter_t 	interrupter[IT_LAST];
extern thermometer_t	thermometer[TH_LAST];
extern presence_t 	    presence[PR_LAST];
extern thermometer_t	thermometer[TH_LAST];
*/


void radiateur_init(void)
{
	radiateur[RD_CUISINE].type= FIL_PILOTE;
	radiateur[RD_CUISINE].index = 0;
	radiateur[RD_CUISINE].thermometer=-1;
	radiateur[RD_CUISINE].interupteur=IT_CUISINE;
	radiateur[RD_CUISINE].calculated_target_temp = 0;
	radiateur[RD_CUISINE].expected_state = 0;
	radiateur[RD_CUISINE].http_req_time=0;
	radiateur[RD_CUISINE].http_req_temp=0;
	strcpy(radiateur[RD_CUISINE].name,"Cuisine");
	radiateur_init_pgm_cuisine(RD_CUISINE);

	radiateur[RD_DAPHNEE].type= FIL_PILOTE;
	radiateur[RD_DAPHNEE].index = 1;
	radiateur[RD_DAPHNEE].thermometer=TH_DAPHNEE;
	radiateur[RD_DAPHNEE].interupteur=-1;
	radiateur[RD_DAPHNEE].calculated_target_temp = 0;
	radiateur[RD_DAPHNEE].expected_state = 0;
	radiateur[RD_DAPHNEE].http_req_time=0;
	radiateur[RD_DAPHNEE].http_req_temp=0;
	strcpy(radiateur[RD_DAPHNEE].name,"Daphnee");
	radiateur_init_pgm_chambre(RD_DAPHNEE);

	radiateur[RD_VICTOR].type= FIL_PILOTE;
	radiateur[RD_VICTOR].index = 2;
	radiateur[RD_VICTOR].thermometer=TH_VICTOR;
	radiateur[RD_VICTOR].interupteur=-1;
	radiateur[RD_VICTOR].calculated_target_temp = 0;
	radiateur[RD_VICTOR].expected_state = 0;
	radiateur[RD_VICTOR].http_req_time=0;
	radiateur[RD_VICTOR].http_req_temp=0;
	strcpy(radiateur[RD_VICTOR].name,"Victor");
	radiateur_init_pgm_chambre(RD_VICTOR);

	radiateur[RD_HOMECINEMA].type= FIL_PILOTE;
	radiateur[RD_HOMECINEMA].index = 3;
	radiateur[RD_HOMECINEMA].thermometer=-1;
	radiateur[RD_HOMECINEMA].interupteur=IT_HOMECINEMA;
	radiateur[RD_HOMECINEMA].calculated_target_temp = 0;
	radiateur[RD_HOMECINEMA].expected_state = 0;
	radiateur[RD_HOMECINEMA].http_req_time=0;
	radiateur[RD_HOMECINEMA].http_req_temp=0;
	strcpy(radiateur[RD_HOMECINEMA].name,"Homecinema");
	radiateur_init_pgm_homecinema(RD_HOMECINEMA);

	radiateur[RD_SALON].type= FIL_PILOTE;
	radiateur[RD_SALON].index = 4;
	radiateur[RD_SALON].thermometer=TH_SALON;
	radiateur[RD_SALON].interupteur=-1;
	radiateur[RD_SALON].calculated_target_temp = 0;
	radiateur[RD_SALON].expected_state = 0;
	radiateur[RD_SALON].http_req_time=0;
	radiateur[RD_SALON].http_req_temp=0;
	strcpy(radiateur[RD_SALON].name,"Salon");
	radiateur_init_pgm_salon(RD_SALON);

}

void radiateur_init_pgm_salon(int rad)
{
	int ii,jj;
	for(ii=0;ii<7*24*4;ii+=24*4)
	{
		for(jj=0;jj<24*4;jj++)
		{
			if((jj<7*4)||(jj>21*4))
			{
				radiateur[rad].program[ii+jj]=15.0f ;
			}
			else
			{
				radiateur[rad].program[ii+jj]=20.0f ;
			}
		}
	}
	//rrd_create_rad_pgm(radiateur[rad].name,radiateur[rad].program);
}

void radiateur_init_pgm_chambre(int rad)
{
	int ii,jj;
	for(ii=0;ii<7*24*4;ii+=24*4)
	{
		for(jj=0;jj<24*4;jj++)
		{
			if(((jj>19*4)&&(jj<21*4)) || ((jj>7*4)&&(jj<8*4)))
			{
				radiateur[rad].program[ii+jj]=20.0f ;
			}
			else
			{
				radiateur[rad].program[ii+jj]=15.0f ;
			}
		}
	}
	//rrd_create_rad_pgm(radiateur[rad].name,radiateur[rad].program);
}

void radiateur_init_pgm_cuisine(int rad)
{
	int ii,jj;
	for(ii=0;ii<7*24*4;ii+=24*4)
	{
		for(jj=0;jj<24*4;jj++)
		{
			if((jj>6*4)&&(jj<9*4))
			{
				radiateur[rad].program[ii+jj]=20.0f ;
			}
			else
			{
				radiateur[rad].program[ii+jj]=15.0f ;
			}
		}
	}
	//rrd_create_rad_pgm(radiateur[rad].name,radiateur[rad].program);
}

void radiateur_init_pgm_homecinema(int rad)
{
	int ii,jj;
	for(ii=0;ii<7*24*4;ii+=24*4)
	{
		for(jj=0;jj<24*4;jj++)
				{
		if((jj>=20*4)&&(jj<21*4))
		{
			radiateur[rad].program[ii+jj]=20.0f ;
		}
		else
		{
			radiateur[rad].program[ii+jj]=15.0f ;
		}
				}
	}
	//rrd_create_rad_pgm(radiateur[rad].name,radiateur[rad].program);
}

void radiateur_init_pgm_piece(int rad)
{
	int ii;
	for(ii=0;ii<7*24*4;ii++)
	{
		radiateur[rad].program[ii]=15.0f ;
	}
	//rrd_create_rad_pgm(radiateur[rad].name,radiateur[rad].program);
}


void thermometer_init(void)
{
	// TH_EXTERIEUR,TH_GARAGE,TH_SALON,TH_DAPHNEE,TH_VICTOR,TH_BARNABE

	thermometer[TH_EXTERIEUR].mesure_date=0;
	thermometer[TH_EXTERIEUR].temperature=19.0f;
	thermometer[TH_EXTERIEUR].type='V';
	strcpy(thermometer[TH_EXTERIEUR].id,">V:281C0CC8030000D8");
	strcpy(thermometer[TH_EXTERIEUR].name,"Exterior");
	//rrd_create_temp(thermometer[TH_EXTERIEUR].name);

	thermometer[TH_GARAGE].mesure_date=0;
	thermometer[TH_GARAGE].temperature=19.0f;
	thermometer[TH_GARAGE].type='V';
	strcpy(thermometer[TH_GARAGE].id,">V:28E01DC803000066");
	strcpy(thermometer[TH_GARAGE].name,"Garage");
	//rrd_create_temp(thermometer[TH_GARAGE].name);

	thermometer[TH_SALON].mesure_date=0;
	thermometer[TH_SALON].temperature=19.0f;
	thermometer[TH_SALON].type='V';
	strcpy(thermometer[TH_SALON].id,">V:28980CC8030000EE");
	strcpy(thermometer[TH_SALON].name,"Salon");
	//rrd_create_temp(thermometer[TH_SALON].name);

	thermometer[TH_DAPHNEE].mesure_date=0;
	thermometer[TH_DAPHNEE].temperature=19.0f;
	thermometer[TH_DAPHNEE].type='V';
	strcpy(thermometer[TH_DAPHNEE].id,">V:28ADE14A0400007A");
	strcpy(thermometer[TH_DAPHNEE].name,"Daphnee");
	//rrd_create_temp(thermometer[TH_DAPHNEE].name);

	thermometer[TH_VICTOR].mesure_date=0;
	thermometer[TH_VICTOR].temperature=19.0f;
	thermometer[TH_VICTOR].type='C';
	strcpy(thermometer[TH_VICTOR].id,">C:6508503");
	strcpy(thermometer[TH_VICTOR].name,"Victor");
	//rrd_create_temp(thermometer[TH_VICTOR].name);

	thermometer[TH_BARNABE].mesure_date=0;
	thermometer[TH_BARNABE].temperature=19.0f;
	thermometer[TH_BARNABE].type='V';
	strcpy(thermometer[TH_BARNABE].id,">V:2816B14A04000010");
	strcpy(thermometer[TH_BARNABE].name,"Barnabe");
	//rrd_create_temp(thermometer[TH_BARNABE].name);

	thermometer[TH_PARENT].mesure_date=0;
	thermometer[TH_PARENT].temperature=19.0f;
	thermometer[TH_PARENT].type='V';
	strcpy(thermometer[TH_PARENT].id,">V:2877EB4A040000CC");
	strcpy(thermometer[TH_PARENT].name,"Parent");
	//rrd_create_temp(thermometer[TH_BARNABE].name);

	thermometer[TH_DAPHNEE].mesure_date=0;
	thermometer[TH_DAPHNEE].temperature=19.0f;
	thermometer[TH_DAPHNEE].type='V';
	strcpy(thermometer[TH_DAPHNEE].id,">V:28ADE14A0400007A");
	strcpy(thermometer[TH_DAPHNEE].name,"Daphnee");

	thermometer[TH_CUISINE].mesure_date=0;
	thermometer[TH_CUISINE].temperature=19.0f;
	thermometer[TH_CUISINE].type='C';
	strcpy(thermometer[TH_CUISINE].id,">C:6501504");
	strcpy(thermometer[TH_CUISINE].name,"Cuisine");


}

void interupter_init(void)
{

	//>C:FE6142281E6A10


	interrupter[IT_HOMECINEMA].action_date=0;
	interrupter[IT_HOMECINEMA].action=0;
	strcpy(interrupter[IT_HOMECINEMA].id,">C:FE61422");

	interrupter[IT_CUISINE].action_date=0;
	interrupter[IT_CUISINE].action=0;
	strcpy(interrupter[IT_CUISINE].id,">C:FE6103A");

	interrupter[IT_GARAGE].action_date=0;
	interrupter[IT_GARAGE].action=0;
	strcpy(interrupter[IT_GARAGE].id,">C:FE68722");


}



void Light_init(void)
{

	light[LI_ATELIER].action_date=0;
	light[LI_ATELIER].blyss_id=3;
	light[LI_ATELIER].presence=PR_ATELIER;
	strcpy(light[LI_ATELIER].name,"Atelier");
	memset(light[LI_ATELIER].interupteur,-1,sizeof(light[LI_ATELIER].interupteur));

	light[LI_ETABLI].action_date=0;
	light[LI_ETABLI].blyss_id=4;
	light[LI_ETABLI].presence=PR_GARAGE;
	strcpy(light[LI_ETABLI].name,"Etabli");
	memset(light[LI_ETABLI].interupteur,-1,sizeof(light[LI_ETABLI].interupteur));
	light[LI_ETABLI].interupteur[0]=IT_GARAGE;

	light[LI_GARAGE].action_date=0;
	light[LI_GARAGE].blyss_id=2;
	light[LI_GARAGE].presence=PR_GARAGE;
	strcpy(light[LI_GARAGE].name,"Garage");
	memset(light[LI_GARAGE].interupteur,-1,sizeof(light[LI_GARAGE].interupteur));

	light[LI_PRISE_1].action_date=0;
	light[LI_PRISE_1].blyss_id=5;
	light[LI_PRISE_1].presence=PR_GARAGE;
	strcpy(light[LI_PRISE_1].name,"Prise 1");
	memset(light[LI_PRISE_1].interupteur,-1,sizeof(light[LI_PRISE_1].interupteur));
	light[LI_PRISE_1].interupteur[0]=IT_HOMECINEMA;


}

void Presence_init(void)
{

	presence[PR_ATELIER].action_date=0;
	strcpy(presence[PR_ATELIER].id,">00000000000802F3");
	strcpy(presence[PR_ATELIER].name,"Atelier");


	presence[PR_GARAGE].action_date=0;
	strcpy(presence[PR_GARAGE].id,">0000000000080769");
	strcpy(presence[PR_GARAGE].name,"Garage");

}

void radiateur_evaluate_next_state(int rad)
{
	float targ_temp,measured_temp;

	time_t rawtime;
	struct tm * timeinfo;
	int index_prog;


	index_prog=get_pgm_index();
	targ_temp=radiateur[rad].program[index_prog];

	if(radiateur[rad].interupteur>=0)
	{
		if(((time(NULL)-interrupter[radiateur[rad].interupteur].action_date)<3600) &&(interrupter[radiateur[rad].interupteur].action==1))
		{
			targ_temp=21.0f;
		}
	}

	if((time(NULL)-radiateur[RD_SALON].http_req_time)<3600)
	{
		targ_temp=radiateur[RD_SALON].http_req_temp;
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
	// info("RADIATEUR","Radiator %s target temp: %f measured temp: %f",radiateur[rad].name,targ_temp,measured_temp);

	if(measured_temp<(targ_temp-0.5))
	{
		if(radiateur[rad].expected_state==0)
			info("RADIATEUR","Switch on radiator %s",radiateur[rad].name);
		radiateur[rad].expected_state=1;
	}
	else if(measured_temp>(targ_temp+0.5))
	{
		if(radiateur[rad].expected_state==1)
			info("RADIATEUR","Switch off radiator %s",radiateur[rad].name);
		radiateur[rad].expected_state=0;
	}
}


void light_evaluate_next_state(int li)
{
	int ii;

	for(ii=0;ii<sizeof(light[0].interupteur)/sizeof(light[0].interupteur[0]);ii++)
	{
		if(light[li].interupteur[ii]>=0)
		{
		  //info("LIGHT","light %i interupteur %i",li,light[li].interupteur[ii]);
		  if((time(NULL)- interrupter[light[li].interupteur[ii]].action_date)<5)
		  {
			 // info("LIGHT","SendBlyssCmd %i interupteur %i",light[li].blyss_id, interrupter[light[li].interupteur[ii]].action);
			 // sleep(1);
			 // SendBlyssCmd(light[li].blyss_id,interrupter[light[li].interupteur[ii]].action);
		  }
		}
	}




	interrupter[ii].action_date=time(NULL);
}

void * radiateur_loop(void * arg)
{
	int ii;

	radiateur_init();
	thermometer_init();
	interupter_init();
	Light_init();
	Presence_init();
	while(1)
	{
		// info("RADIATEUR","Evaluate radiateur status");
		for(ii=0;ii<RD_LAST;ii++)
		{
			radiateur_evaluate_next_state(ii);
		}


		for(ii=0;ii<LI_LAST;ii++)
		{
			light_evaluate_next_state(ii);
		}
		SerialFilPiloteSendCommande();
		sem_wait(&sem_capteur_data_available);

	}
}
