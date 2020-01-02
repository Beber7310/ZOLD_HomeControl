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
	radiateur[RD_CUISINE].type = FIL_PILOTE;
	radiateur[RD_CUISINE].index = 0;
	radiateur[RD_CUISINE].thermometer = TH_CUISINE;
	radiateur[RD_CUISINE].interupteur = IT_OLD_1;
	radiateur[RD_CUISINE].calculated_target_temp = 0;
	radiateur[RD_CUISINE].expected_state = 0;
	radiateur[RD_CUISINE].http_req_time = 0;
	radiateur[RD_CUISINE].http_req_temp = 0;
	radiateur[RD_CUISINE].mirror_state = -1;
	radiateur[RD_CUISINE].mirror_time = 0;
	strcpy(radiateur[RD_CUISINE].name, "Cuisine");
	strcpy(radiateur[RD_CUISINE].mqtt_topic, "");

	radiateur_init_pgm_cuisine(RD_CUISINE);

	radiateur[RD_DAPHNEE].type = FIL_PILOTE;
	radiateur[RD_DAPHNEE].index = 1;
	radiateur[RD_DAPHNEE].thermometer = TH_DAPHNE;
	radiateur[RD_DAPHNEE].interupteur = IT_HOMECINEMA;
	radiateur[RD_DAPHNEE].calculated_target_temp = 0;
	radiateur[RD_DAPHNEE].expected_state = 0;
	radiateur[RD_DAPHNEE].http_req_time = 0;
	radiateur[RD_DAPHNEE].http_req_temp = 0;
	radiateur[RD_DAPHNEE].mirror_state = -1;
	radiateur[RD_DAPHNEE].mirror_time = 0;
	strcpy(radiateur[RD_DAPHNEE].name, "Daphnee");
	strcpy(radiateur[RD_DAPHNEE].mqtt_topic, "");
	radiateur_init_pgm_chambre(RD_DAPHNEE);

	radiateur[RD_BARNABE].type = SONOFF_HTTP;
	radiateur[RD_BARNABE].index = 6;
	radiateur[RD_BARNABE].thermometer = TH_BARNABE;
	radiateur[RD_BARNABE].interupteur = IT_BARNABE;
	radiateur[RD_BARNABE].calculated_target_temp = 0;
	radiateur[RD_BARNABE].expected_state = 0;
	radiateur[RD_BARNABE].http_req_time = 0;
	radiateur[RD_BARNABE].http_req_temp = 0;
	radiateur[RD_BARNABE].mirror_state = -1;
	radiateur[RD_BARNABE].mirror_time = 0;
	strcpy(radiateur[RD_BARNABE].name, "Barnabe");
	strcpy(radiateur[RD_BARNABE].mqtt_topic, "lamotte/barnabe/sonoff_heater/cmnd/POWER");
	radiateur_init_pgm_chambre(RD_BARNABE);

	radiateur[RD_HOMECINEMA].type = FIL_PILOTE;
	radiateur[RD_HOMECINEMA].index = 3;
	radiateur[RD_HOMECINEMA].thermometer = -1;
	radiateur[RD_HOMECINEMA].interupteur = -1;
	radiateur[RD_HOMECINEMA].calculated_target_temp = 0;
	radiateur[RD_HOMECINEMA].expected_state = 0;
	radiateur[RD_HOMECINEMA].http_req_time = 0;
	radiateur[RD_HOMECINEMA].http_req_temp = 0;
	radiateur[RD_HOMECINEMA].mirror_state = -1;
	radiateur[RD_HOMECINEMA].mirror_time = 0;
	strcpy(radiateur[RD_HOMECINEMA].name, "Homecinema");
	strcpy(radiateur[RD_HOMECINEMA].mqtt_topic, "");
	radiateur_init_pgm_homecinema(RD_HOMECINEMA);

	radiateur[RD_SALON].type = FIL_PILOTE;
	radiateur[RD_SALON].index = 4;
	radiateur[RD_SALON].thermometer = TH_SALON;
	radiateur[RD_SALON].interupteur = IT_OLD_1;
	radiateur[RD_SALON].calculated_target_temp = 0;
	radiateur[RD_SALON].expected_state = 0;
	radiateur[RD_SALON].http_req_time = 0;
	radiateur[RD_SALON].http_req_temp = 0;
	radiateur[RD_SALON].mirror_state = -1;
	radiateur[RD_SALON].mirror_time = 0;
	strcpy(radiateur[RD_SALON].name, "Salon");
	strcpy(radiateur[RD_SALON].mqtt_topic, "");
	radiateur_init_pgm_salon(RD_SALON);

	radiateur[RD_VICTOR].type = RF_CONTROLED;
	radiateur[RD_VICTOR].index = 7;
	radiateur[RD_VICTOR].thermometer = TH_VICTOR;
	radiateur[RD_VICTOR].interupteur = -1;
	radiateur[RD_VICTOR].calculated_target_temp = 0;
	radiateur[RD_VICTOR].expected_state = 0;
	radiateur[RD_VICTOR].http_req_time = 0;
	radiateur[RD_VICTOR].http_req_temp = 0;
	radiateur[RD_VICTOR].mirror_state = -1;
	radiateur[RD_VICTOR].mirror_time = 0;
	strcpy(radiateur[RD_VICTOR].name, "Victor");
	strcpy(radiateur[RD_VICTOR].mqtt_topic, "");
	radiateur_init_pgm_chambre(RD_VICTOR);

	radiateur[RD_PARENT].type = FIL_PILOTE;
	radiateur[RD_PARENT].index = 2;
	radiateur[RD_PARENT].thermometer = -1;
	radiateur[RD_PARENT].interupteur = IT_SOFIA;
	radiateur[RD_PARENT].calculated_target_temp = 0;
	radiateur[RD_PARENT].expected_state = 0;
	radiateur[RD_PARENT].http_req_time = 0;
	radiateur[RD_PARENT].http_req_temp = 0;
	strcpy(radiateur[RD_PARENT].name, "Parent");
	strcpy(radiateur[RD_PARENT].mqtt_topic, "");
	radiateur_init_pgm_chambre(RD_PARENT);

}

void radiateur_init_pgm_froid(int rad)
{
	int ii, jj;
	for (ii = 0; ii < 7 * 24 * 4; ii += 24 * 4)
	{
		for (jj = 0; jj < 24 * 4; jj++)
		{
			if ((jj < 7 * 4) || (jj > 21 * 4))
			{
				radiateur[rad].program[ii + jj] = 15.0f;
			}
			else
			{
				radiateur[rad].program[ii + jj] = 20.0f;
			}
		}
	}

}

void radiateur_init_pgm_salon(int rad)
{
	int ii, jj;
	for (ii = 0; ii < 7 * 24 * 4; ii += 24 * 4)
	{
		for (jj = 0; jj < 24 * 4; jj++)
		{
			//if((jj<7*4)||(jj>21*4))
			if (((jj >= 7 * 4) && (jj < 9 * 4)))
			{
				radiateur[rad].program[ii + jj] = 21.0f;
			}
			else if ((jj > 15.5 * 4) && (jj < 21 * 4))
			{
				radiateur[rad].program[ii + jj] = 20.0f;
			}
			else
			{
				radiateur[rad].program[ii + jj] = 15.0f;
			}
		}
	}
	ii = 3 * 24 * 4;
	for (jj = 0; jj < 24 * 4; jj++)
	{
		//if((jj<7*4)||(jj>21*4))
		if ((jj >= 7 * 4) && (jj < 9 * 4))
		{
			radiateur[rad].program[ii + jj] = 21.0f;
		}
		else if ((jj >= 12 * 4) && (jj < 21 * 4))
		{
			radiateur[rad].program[ii + jj] = 20.0f;
		}
		else
		{
			radiateur[rad].program[ii + jj] = 15.0f;
		}
	}
	ii = 0 * 24 * 4;
	for (jj = 0; jj < 24 * 4; jj++)
	{
		if ((jj >= 9 * 4) && (jj < 21 * 4))
		{
			radiateur[rad].program[ii + jj] = 20.0f;
		}
		else
		{
			radiateur[rad].program[ii + jj] = 15.0f;
		}
	}
	ii = 6 * 24 * 4;
	for (jj = 0; jj < 24 * 4; jj++)
	{
		if ((jj >= 9 * 4) && (jj < 21 * 4))
		{
			radiateur[rad].program[ii + jj] = 20.0f;
		}
		else
		{
			radiateur[rad].program[ii + jj] = 15.0f;
		}
	}
}

void radiateur_init_pgm_chambre(int rad)
{
	int ii, jj;
	for (ii = 0; ii < 7 * 24 * 4; ii += 24 * 4)
	{
		for (jj = 0; jj < 24 * 4; jj++)
		{
			if (((jj > 19 * 4) && (jj < 21 * 4)) || ((jj > 7 * 4) && (jj < 8 * 4 + 2)))
			{
				radiateur[rad].program[ii + jj] = 20.0f;
			}
			else
			{
				radiateur[rad].program[ii + jj] = 15.0f;
			}
		}
	}

	ii = 0;
	for (jj = 0; jj < 24 * 4; jj++)
	{
		if ((jj >= 8 * 4) && (jj <= 19 * 4))
		{
			radiateur[rad].program[ii + jj] = 18.0f;
		}

	}
	ii = 6 * 24 * 4;
	for (jj = 0; jj < 24 * 4; jj++)
	{
		if ((jj >= 8 * 4) && (jj <= 19 * 4))
		{
			radiateur[rad].program[ii + jj] = 18.0f;
		}

	}
	ii = 3 * 24 * 4;
	for (jj = 0; jj < 24 * 4; jj++)
	{
		if ((jj >= 13 * 4) && (jj <= 19 * 4))
		{
			radiateur[rad].program[ii + jj] = 18.0f;
		}

	}

//rrd_create_rad_pgm(radiateur[rad].name,radiateur[rad].program);
}

void radiateur_init_pgm_cuisine(int rad)
{
	int ii, jj;
	for (ii = 0; ii < 7 * 24 * 4; ii += 24 * 4)
	{
		for (jj = 0; jj < 24 * 4; jj++)
		{
			if ((jj > 6 * 4) && (jj < 9 * 4))
			{
				radiateur[rad].program[ii + jj] = 22.0f;
			}
			else if ((jj > 8 * 4) && (jj < 16 * 4))
			{
				radiateur[rad].program[ii + jj] = 16.0f;
			}
			else if ((jj >= 16 * 4) && (jj < 21 * 4))
			{
				radiateur[rad].program[ii + jj] = 20.0f;
			}
			else
			{
				radiateur[rad].program[ii + jj] = 15.0f;
			}
		}
	}

	ii = 3 * 24 * 4;
	{
		for (jj = 0; jj < 24 * 4; jj++)
		{
			if ((jj > 6 * 4) && (jj < 9 * 4))
			{
				radiateur[rad].program[ii + jj] = 22.0f;
			}
			else if ((jj > 8 * 4) && (jj < 12 * 4))
			{
				radiateur[rad].program[ii + jj] = 16.0f;
			}
			else if ((jj >= 12 * 4) && (jj < 21 * 4))
			{
				radiateur[rad].program[ii + jj] = 20.0f;
			}
			else
			{
				radiateur[rad].program[ii + jj] = 15.0f;
			}
		}
	}

//rrd_create_rad_pgm(radiateur[rad].name,radiateur[rad].program);
}

void radiateur_init_pgm_homecinema(int rad)
{
	int ii, jj;
	for (ii = 0; ii < 7 * 24 * 4; ii += 24 * 4)
	{
		for (jj = 0; jj < 24 * 4; jj++)
		{
			if ((jj >= 20 * 4) && (jj < 21 * 4))
			{
				radiateur[rad].program[ii + jj] = 20.0f;
			}
			else
			{
				radiateur[rad].program[ii + jj] = 15.0f;
			}
		}
	}
//rrd_create_rad_pgm(radiateur[rad].name,radiateur[rad].program);
}

void radiateur_init_pgm_piece(int rad)
{
	int ii;
	for (ii = 0; ii < 7 * 24 * 4; ii++)
	{
		radiateur[rad].program[ii] = 15.0f;
	}
//rrd_create_rad_pgm(radiateur[rad].name,radiateur[rad].program);
}

void radiateur_init_pgm_hors_gele(int rad)
{
	int ii;
	for (ii = 0; ii < 7 * 24 * 4; ii++)
	{
		radiateur[rad].program[ii] = 12.0f;
	}
//rrd_create_rad_pgm(radiateur[rad].name,radiateur[rad].program);
}

void radiateur_init_pgm_temp(int rad, float temp)
{
	int ii;
	for (ii = 0; ii < 7 * 24 * 4; ii++)
	{
		radiateur[rad].program[ii] = temp;
	}
//rrd_create_rad_pgm(radiateur[rad].name,radiateur[rad].program);
}

void thermometer_init(void)
{

	thermometer[TH_BROKEN].smsSent = 0;
	thermometer[TH_BROKEN].mesure_date = time(NULL);
	thermometer[TH_BROKEN].temperature = 19.0f;
	thermometer[TH_BROKEN].hygrometrie = -1.0f;
	thermometer[TH_BROKEN].type = 'C';
	strcpy(thermometer[TH_BROKEN].id, ">C:6509631");
	strcpy(thermometer[TH_BROKEN].name, "Broken");
	strcpy(thermometer[TH_BROKEN].mqtt_topic, "lamotte/broken");

	thermometer[TH_GARAGE].smsSent = 0;
	thermometer[TH_GARAGE].mesure_date = time(NULL);
	thermometer[TH_GARAGE].temperature = 19.0f;
	thermometer[TH_GARAGE].hygrometrie = -1.0f;
	thermometer[TH_GARAGE].type = 'V';
	strcpy(thermometer[TH_GARAGE].id, ">V:28E01DC803000066");
	strcpy(thermometer[TH_GARAGE].name, "Garage");
	strcpy(thermometer[TH_GARAGE].mqtt_topic, "lamotte/garage");

	thermometer[TH_DAPHNE].smsSent = 0;
	thermometer[TH_DAPHNE].mesure_date = time(NULL);
	thermometer[TH_DAPHNE].temperature = 19.0f;
	thermometer[TH_DAPHNE].hygrometrie = -1.0f;
	thermometer[TH_DAPHNE].type = 'C';
	strcpy(thermometer[TH_DAPHNE].id, ">C:650B033");
	strcpy(thermometer[TH_DAPHNE].name, "Daphnee");
	strcpy(thermometer[TH_DAPHNE].mqtt_topic, "lamotte/daphnee");

	thermometer[TH_SALON].smsSent = 0;
	thermometer[TH_SALON].mesure_date = time(NULL);
	thermometer[TH_SALON].temperature = 19.0f;
	thermometer[TH_SALON].hygrometrie = -1.0f;
	thermometer[TH_SALON].type = 'C';
	strcpy(thermometer[TH_SALON].id, ">C:6505101");
	strcpy(thermometer[TH_SALON].name, "Salon");
	strcpy(thermometer[TH_SALON].mqtt_topic, "lamotte/salon");

	thermometer[TH_BARNABE].smsSent = 0;
	thermometer[TH_BARNABE].mesure_date = time(NULL);
	thermometer[TH_BARNABE].temperature = 19.0f;
	thermometer[TH_BARNABE].hygrometrie = -1.0f;
	thermometer[TH_BARNABE].type = 'C';
	strcpy(thermometer[TH_BARNABE].id, ">C:6508503");
	strcpy(thermometer[TH_BARNABE].name, "Barnabe");
	strcpy(thermometer[TH_BARNABE].mqtt_topic, "lamotte/barnabe");

	thermometer[TH_VICTOR].smsSent = 0;
	thermometer[TH_VICTOR].mesure_date = time(NULL);
	thermometer[TH_VICTOR].temperature = 19.0f;
	thermometer[TH_VICTOR].hygrometrie = -1.0f;
	thermometer[TH_VICTOR].type = 'C';
	strcpy(thermometer[TH_VICTOR].id, ">C:6503804");
	strcpy(thermometer[TH_VICTOR].name, "Victor");
	strcpy(thermometer[TH_VICTOR].mqtt_topic, "lamotte/victor");

	thermometer[TH_CUISINE].smsSent = 0;
	thermometer[TH_CUISINE].mesure_date = time(NULL);
	thermometer[TH_CUISINE].temperature = 19.0f;
	thermometer[TH_CUISINE].hygrometrie = -1.0f;
	thermometer[TH_CUISINE].type = 'C';
	strcpy(thermometer[TH_CUISINE].id, ">C:6501504");
	strcpy(thermometer[TH_CUISINE].name, "Cuisine");
	strcpy(thermometer[TH_CUISINE].mqtt_topic, "lamotte/cuisine");

	thermometer[TH_EXTERIEUR].smsSent = 0;
	thermometer[TH_EXTERIEUR].mesure_date = time(NULL);
	thermometer[TH_EXTERIEUR].temperature = 19.0f;
	thermometer[TH_EXTERIEUR].hygrometrie = -1.0f;
	thermometer[TH_EXTERIEUR].type = 'S';
	strcpy(thermometer[TH_EXTERIEUR].id, "0316A2790DBF");
	strcpy(thermometer[TH_EXTERIEUR].name, "Exterieur");
	strcpy(thermometer[TH_EXTERIEUR].mqtt_topic, "lamotte/exterieur");

}

void interupter_init(void)
{

//>C:FE6142281E6A10

	interrupter[IT_HOMECINEMA].action_date = 0;
	interrupter[IT_HOMECINEMA].action = 0;
	strcpy(interrupter[IT_HOMECINEMA].id, ">C:FE61422");

	interrupter[IT_BARNABE].action_date = 0;
	interrupter[IT_BARNABE].action = 0;
	strcpy(interrupter[IT_BARNABE].id, ">C:FE6103A");

	interrupter[IT_GARAGE].action_date = 0;
	interrupter[IT_GARAGE].action = 0;
	strcpy(interrupter[IT_GARAGE].id, ">C:FE68722");

	interrupter[IT_SOFIA].action_date = 0;
	interrupter[IT_SOFIA].action = 0;
	strcpy(interrupter[IT_SOFIA].id, ">C:FE68792");

	interrupter[IT_OLD_1].action_date = 0;
	interrupter[IT_OLD_1].action = 0;
	strcpy(interrupter[IT_OLD_1].id, ">C:FE685FA");

}

void Light_init(void)
{

	light[LI_ATELIER].action_date = 0;
	light[LI_ATELIER].blyss_id = 2;
	light[LI_ATELIER].presence = PR_ATELIER;
	strcpy(light[LI_ATELIER].name, "Atelier");
	memset(light[LI_ATELIER].interupteur, -1, sizeof(light[LI_ATELIER].interupteur));

	light[LI_ETABLI].action_date = 0;
	light[LI_ETABLI].blyss_id = 1;
	light[LI_ETABLI].presence = PR_GARAGE;
	strcpy(light[LI_ETABLI].name, "Etabli");
	memset(light[LI_ETABLI].interupteur, -1, sizeof(light[LI_ETABLI].interupteur));
	light[LI_ETABLI].interupteur[0] = IT_GARAGE;

	light[LI_GARAGE].action_date = 0;
	light[LI_GARAGE].blyss_id = 0;
	light[LI_GARAGE].presence = PR_GARAGE;
	strcpy(light[LI_GARAGE].name, "Garage");
	memset(light[LI_GARAGE].interupteur, -1, sizeof(light[LI_GARAGE].interupteur));

	light[LI_PRISE_1].action_date = 0;
	light[LI_PRISE_1].blyss_id = 3;
	light[LI_PRISE_1].presence = -1;
	strcpy(light[LI_PRISE_1].name, "Prise_1");
	memset(light[LI_PRISE_1].interupteur, -1, sizeof(light[LI_PRISE_1].interupteur));

	light[LI_AMPOULE_DISCO].action_date = 0;
	light[LI_AMPOULE_DISCO].blyss_id = 4;
	light[LI_AMPOULE_DISCO].presence = -1;
	strcpy(light[LI_AMPOULE_DISCO].name, "Ampoule_Disco");
	memset(light[LI_AMPOULE_DISCO].interupteur, -1, sizeof(light[LI_PRISE_1].interupteur));

	light[LI_VMC].action_date = 0;
	light[LI_VMC].blyss_id = 5;
	light[LI_VMC].presence = -1;
	strcpy(light[LI_VMC].name, "VMC");
	memset(light[LI_VMC].interupteur, -1, sizeof(light[LI_PRISE_1].interupteur));

	light[LI_RAD_BARNABE].action_date = 0;
	light[LI_RAD_BARNABE].blyss_id = 6;
	light[LI_RAD_BARNABE].presence = -1;
	strcpy(light[LI_RAD_BARNABE].name, "RAD_BARNABE");
	memset(light[LI_RAD_BARNABE].interupteur, -1, sizeof(light[LI_PRISE_1].interupteur));

	light[LI_RAD_VICTOR].action_date = 0;
	light[LI_RAD_VICTOR].blyss_id = 7;
	light[LI_RAD_VICTOR].presence = -1;
	strcpy(light[LI_RAD_VICTOR].name, "RAD_VICTOR");
	memset(light[LI_RAD_VICTOR].interupteur, -1, sizeof(light[LI_PRISE_1].interupteur));
}

void Rain_Init(void)
{
	rain.last_rain = 0;
}

void Presence_init(void)
{
	presence[PR_ATELIER].action_date = 0;
	strcpy(presence[PR_ATELIER].id, ">C:FE802F3");
	strcpy(presence[PR_ATELIER].name, "sdb_haut");
	strcpy(presence[PR_ATELIER].mqtt_topic, "lamotte/sdb_haut");

	presence[PR_GARAGE].action_date = 0;
	strcpy(presence[PR_GARAGE].id, ">C:FE80769");
	strcpy(presence[PR_GARAGE].name, "Garage");
	strcpy(presence[PR_GARAGE].mqtt_topic, "lamotte/garage");
}

void radiateur_evaluate_next_state(int rad)
{
	float targ_temp, measured_temp;

//	time_t rawtime;
//	struct tm * timeinfo;
	int index_prog;

	index_prog = get_pgm_index();
	targ_temp = radiateur[rad].program[index_prog];

	if (radiateur[rad].interupteur >= 0)
	{
		if (((time(NULL) - interrupter[radiateur[rad].interupteur].action_date) < 3600) && (interrupter[radiateur[rad].interupteur].action == 1))
		{
			targ_temp = 21.0f;
		}
	}

	if ((time(NULL) - radiateur[rad].http_req_time) < 3600)
	{
		targ_temp = radiateur[rad].http_req_temp;
	}

	radiateur[rad].calculated_target_temp = targ_temp;

	if (radiateur[rad].thermometer >= 0)
	{
		measured_temp = thermometer[radiateur[rad].thermometer].temperature;
	}
	else
	{
		measured_temp = 19.0f;
	}
// info("RADIATEUR","Radiator %s target temp: %f measured temp: %f",radiateur[rad].name,targ_temp,measured_temp);

	if (measured_temp < (targ_temp - 0.5))
	{
		if (radiateur[rad].expected_state == 0)
			info("RADIATEUR", "Switch on radiator %s", radiateur[rad].name);
		radiateur[rad].expected_state = 1;
	}
	else if (measured_temp > (targ_temp + 0.5))
	{
		if (radiateur[rad].expected_state == 1)
			info("RADIATEUR", "Switch off radiator %s", radiateur[rad].name);
		radiateur[rad].expected_state = 0;
	}
}

void light_evaluate_next_state(int li)
{
//int ii;

	if (light[li].presence >= 0)
	{
		if (((time(NULL) - presence[light[li].presence].action_date) > 600) && (light[li].action_date < presence[light[li].presence].action_date))
		{
			info("LIGHT", "SendBlyssCmd %i interrupter %i", light[li].blyss_id, 0);

			SendBlyssCmd(light[li].blyss_id, 0);
			SendBlyssCmd(light[li].blyss_id, 0);
			SendBlyssCmd(light[li].blyss_id, 0);

			light[li].action_date = time(NULL);
		}
	}
}

void rain_calcul(void)
{
	if ((rain.current_rain >= rain.last_rain) && (rain.last_rain > 0))
	{
		rain.falled = rain.current_rain - rain.last_rain;
	}
	else
	{
		rain.falled = 0;
	}

	rain.last_rain = rain.current_rain;
}

void * radiateur_loop(void * arg)
{
	int ii;

	radiateur_init();
	thermometer_init();
	interupter_init();
	Light_init();
	Presence_init();
	Rain_Init();

	while (1)
	{
		// info("RADIATEUR","Evaluate radiateur status");
		for (ii = 0; ii < RD_LAST; ii++)
		{
			radiateur_evaluate_next_state(ii);
		}

		for (ii = 0; ii < LI_LAST; ii++)
		{
			light_evaluate_next_state(ii);
		}

		SerialFilPiloteSendCommande();
		manageAlarm();
		sem_wait(&sem_capteur_data_available);

	}
}

void manageAlarm(void)
{
	int ii;
	char szBuf[1024];

	for (ii = 0; ii < TH_LAST; ii++)
	{

		if (thermometer[ii].smsSent == 0)
		{
			if ((time(NULL) - thermometer[ii].mesure_date) > 60 * 30)
			{
				thermometer[ii].smsSent = 1;
				sprintf(szBuf, "        --- HomeControl ---\n%s thermometer looks to be off", thermometer[ii].name);
				sendSMS(szBuf);
			}
		}
		else
		{
			if ((time(NULL) - thermometer[ii].mesure_date) < 60 * 2)
			{
				thermometer[ii].smsSent = 0;
				sprintf(szBuf, "        --- HomeControl ---\n%s thermometer is back to normal", thermometer[ii].name);
				sendSMS(szBuf);
			}
		}

	}

}
