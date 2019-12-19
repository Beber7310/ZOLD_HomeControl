/*
 * rdd.c
 *
 *  Created on: 25 déc. 2013
 *      Author: Bertrand
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */
#include "http.h"
#include "emon.h"

int logData(char* dbtype,char* dbname,time_t date,float data)
{
	char filename[256];

	sprintf(filename,"%s_%s",dbname,dbtype);

	emon_log_data(filename, data);
}
