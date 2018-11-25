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

	sprintf(filename,"db/%s_%s.db",dbtype,dbname);

	FILE * pFile;
	pFile = fopen(filename,"ab");

	if (pFile!=NULL)
	{

		fwrite (&date , sizeof(date), 1, pFile);
		fwrite (&data , sizeof(data), 1, pFile);

		fclose (pFile);
	}

	emon_log_data(filename, data);
}


int log_get_http_temp(char* bufhttp,int buflen)
{
	FILE * pFile;


	time_t start_time;
	struct tm * timeinfo;
	time_t date;
	int ii;
	float data;
	int read_len;
	int http_len=0;

	float* pResult;


	if (pFile!=NULL)
	{
		http_q_data(&http_len,bufhttp,"<html>\n");
		http_q_data(&http_len,bufhttp,"<head>\n");
		http_q_data(&http_len,bufhttp,"<script type='text/javascript' src='http://www.google.com/jsapi'></script>\n");
		http_q_data(&http_len,bufhttp,"<script type='text/javascript'>\n");
		http_q_data(&http_len,bufhttp,"google.load('visualization', '1', {'packages':['annotatedtimeline']});\n");
		http_q_data(&http_len,bufhttp,"google.setOnLoadCallback(drawChart);\n");
		http_q_data(&http_len,bufhttp,"function drawChart() {\n");
		http_q_data(&http_len,bufhttp,"var data = new google.visualization.DataTable();\n");
		http_q_data(&http_len,bufhttp,"data.addColumn('datetime', 'datetime');\n");
		http_q_data(&http_len,bufhttp,"data.addColumn('number', 'Salon');\n");
		http_q_data(&http_len,bufhttp,"data.addColumn('number', 'Exterieur');\n");
		http_q_data(&http_len,bufhttp,"data.addColumn('number', 'Garage');\n");
		http_q_data(&http_len,bufhttp,"data.addColumn('number', 'Chambre B');\n");
		http_q_data(&http_len,bufhttp,"data.addColumn('number', 'Chambre V');\n");
		http_q_data(&http_len,bufhttp,"data.addColumn('number', 'Chambre D');\n");
		http_q_data(&http_len,bufhttp,"data.addRows([\n");

		pFile = fopen("db/th_Salon.db","rb");
		do
		{
			fread (&date, sizeof(time_t), 1,pFile);
			timeinfo = localtime (&date);
			read_len=fread (&data, sizeof(float), 1,pFile);


			http_q_data(&http_len,bufhttp,"[new Date(%i,%i,%i,%i,%i,%i), %.2f,%s,%s,%s,%s,%s],\n",1900+timeinfo->tm_year,timeinfo->tm_mon,timeinfo->tm_mday,\
					timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec,data,"null","null","null","null","null");
		}while(read_len);
		fclose(pFile);

		pFile = fopen("db/th_Exterior.db","rb");
		do
		{
			fread (&date, sizeof(time_t), 1,pFile);
			timeinfo = localtime (&date);
			read_len=fread (&data, sizeof(float), 1,pFile);


			http_q_data(&http_len,bufhttp,"[new Date(%i,%i,%i,%i,%i,%i), %s,%.2f,%s,%s,%s,%s],\n",1900+timeinfo->tm_year,timeinfo->tm_mon,timeinfo->tm_mday,\
					timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec,"null",data,"null","null","null","null");
		}while(read_len);
		fclose(pFile);

		pFile = fopen("db/th_Garage.db","rb");
		do
		{
			fread (&date, sizeof(time_t), 1,pFile);
			timeinfo = localtime (&date);
			read_len=fread (&data, sizeof(float), 1,pFile);


			http_q_data(&http_len,bufhttp,"[new Date(%i,%i,%i,%i,%i,%i), %s,%s,%.2f,%s,%s,%s],\n",1900+timeinfo->tm_year,timeinfo->tm_mon,timeinfo->tm_mday,\
					timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec,"null","null",data,"null","null","null");
		}while(read_len);
		fclose(pFile);

		http_q_data(&http_len,bufhttp,"       ]);\n");
		http_q_data(&http_len,bufhttp,"        var chart = new google.visualization.AnnotatedTimeLine(document.getElementById('chart_div'));\n");
		http_q_data(&http_len,bufhttp,"        chart.draw(data, {displayAnnotations: true});\n");
		http_q_data(&http_len,bufhttp,"      }\n");
		http_q_data(&http_len,bufhttp,"    </script>\n");
		http_q_data(&http_len,bufhttp,"    <meta http-equiv=\"Refresh\" content=\"%i\">\n",600);
		http_q_data(&http_len,bufhttp,"  </head>\n");
		http_q_data(&http_len,bufhttp,"  <body>\n");
		http_q_data(&http_len,bufhttp,"    <div id='chart_div' style='width: 1027px; height: 550px;'></div>\n");
		http_q_data(&http_len,bufhttp,"  </body>\n");
		http_q_data(&http_len,bufhttp,"</html>\n");


	}



	return http_len;
}
