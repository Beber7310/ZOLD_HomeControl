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
	sprintf(buf,"rrdtool create %s.rrd --no-overwrite --step 60 DS:%s:GAUGE:60:U:U RRA:AVERAGE:0.5:1:14400 RRA:AVERAGE:0.5:6:14400",thermometer,thermometer);
	system(buf);
	return 0;

}

int rrd_create_rad_pgm(char* thermometer,float* pgm)
{
	int ii;
	char buf[512];
	sprintf(buf,"rrdtool create pgm_%s.rrd --start 920804400 --step 900 DS:%s:GAUGE:900:U:U RRA:AVERAGE:0.5:1:672",thermometer,thermometer);
	system(buf);

	printf("populate rrd\n");
	for(ii=1;ii<7*24*4;ii+=8)
	{
		sprintf(buf,"rrdtool update pgm_%s.rrd %i:%f %i:%f %i:%f %i:%f %i:%f %i:%f %i:%f %i:%f",thermometer,\
				920851200 + (15*60 * ii),pgm[ii],\
			    920851200 + (15*60 * (ii+1)),pgm[ii+1],\
			    920851200 + (15*60 * (ii+2)),pgm[ii+2],\
			    920851200 + (15*60 * (ii+3)),pgm[ii+3],\
			    920851200 + (15*60 * (ii+4)),pgm[ii+4],\
			    920851200 + (15*60 * (ii+5)),pgm[ii+5],\
			    920851200 + (15*60 * (ii+6)),pgm[ii+6],\
			    920851200 + (15*60 * (ii+7)),pgm[ii+7]);
		system(buf);
	}
	printf("start rrd graph \n");

	sprintf(buf,"rrdtool graph pgm_%s.jpeg -t %s -w 800 -h 400 --start 920851200 --end 921456000 DEF:%s=pgm_%s.rrd:%s:AVERAGE LINE2:%s#FF0000",thermometer,thermometer,thermometer,thermometer,thermometer,thermometer);
	system(buf);
	printf("done rrd graph \n");
	return 0;

}

int rrd_test(void)
{
	int ii,start_time;

	char buf[512];
	sprintf(buf,"rrdtool create %s.rrd --start 920804400 --step 60 DS:%s:GAUGE:60:U:U RRA:AVERAGE:0.5:1:14400 RRA:AVERAGE:0.5:6:14400","pipo","pipo");
	system(buf);


	for(ii=0;ii<50;ii++)
	{
		sprintf(buf,"rrdtool update %s.rrd %i:%f","pipo",920804400 + (60 * ii),ii/1.2f);

		system(buf);
	}

return 0;
}
