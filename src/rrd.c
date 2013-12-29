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


	// rrdtool create test.rrd --start 1051480800 DS:vitesse:COUNTER:600:U:U RRA:AVERAGE:0.5:1:24 RRA:AVERAGE:0.5:6:10

int rrd_add_temp(char* thermometer, float temp)
{
	char buf[512];
	sprintf(buf,"rrdtool update %s.rrd %i:%f",thermometer,(int)time(NULL),temp);
	system(buf);
	printf(buf);
	return 0;
}


int rrd_create_temp(char* thermometer)
{
	char buf[512];
	sprintf(buf,"rrdtool create %s.rrd DS:%s:GAUGE:60:U:U RRA:AVERAGE:0.5:1:14400 RRA:AVERAGE:0.5:6:14400",thermometer,thermometer);
	system(buf);
	return 0;

}
