/*
 * utils.c
 *
 *  Created on: 25 déc. 2013
 *      Author: Bertrand
 */
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#include "utils.h"
#include "Components.h"
#include "radiateur.h"

#define NBR_MSG_MAX	10000
message_t msg_log[NBR_MSG_MAX];

int last_msg=0;

void log_msg(const char* level,char* tag,char *format,va_list args)
{

	strncpy(msg_log[last_msg].level,level,sizeof(msg_log[0].level));
	strncpy(msg_log[last_msg].tag,tag,sizeof(msg_log[0].tag));
	vsprintf(msg_log[last_msg].message,format,args);
	msg_log[last_msg].date=time(NULL);

	last_msg++;
	if(last_msg>=NBR_MSG_MAX)
		last_msg=0;


}

int get_http_msg(char* bufhttp,int buflen)
{
	int len=0;
	int ii;
 	char buf[512];
	ii=(last_msg-1);

	while(ii!=last_msg)
	{
		if(ii<0)
			ii=NBR_MSG_MAX-1;

		if(msg_log[ii].date>0)
		{
			sprintf(buf,"[%s] [%s] %s\n",msg_log[ii].level,msg_log[ii].tag,msg_log[ii].message);
			strcpy(&bufhttp[len],buf);
			len+=strlen(buf);
			printf("%i\n",len);
		}
		if(len>buflen-512)
		{
			return len;
		}
		ii--;
	}
	return len;
}

int get_http_sts(char* bufhttp,int buflen)
{
	int len=0;
	int ii;
 	char buf[512];
	struct tm * timeinfo;




	// Radiator
	sprintf(buf,"<p>[Radiator]\n");
	strcpy(&bufhttp[len],buf);
	len+=strlen(buf);

	for(ii=0;ii<RD_LAST;ii++)
	{
		sprintf(buf,"<p>{%s}\n<p>  target_temp=%i\n<p>  state=%i\n",radiateur[ii].name,radiateur[ii].calculated_target_temp,radiateur[ii].expected_state);
		strcpy(&bufhttp[len],buf);
		len+=strlen(buf);
		if(len>buflen-512)
		{
			return len;
		}
	}

	// Thermometer
	sprintf(buf,"[Thermometer]\n<p>");
	strcpy(&bufhttp[len],buf);
	len+=strlen(buf);

	for(ii=0;ii<TH_LAST;ii++)
	{

		sprintf(buf,"{%s}\n  temp=%f\n<p>  date=%s",thermometer[ii].name,thermometer[ii].temperature, ctime(&thermometer[ii].mesure_date));
		strcpy(&bufhttp[len],buf);
		len+=strlen(buf);
		if(len>buflen-512)
		{
			return len;
		}
	}

	return len;
}

int parse_http_cmd(char* cmd)
{
	char* pch;
	pch = strtok(cmd,"?");
	pch = strtok(NULL,"?");
	while (pch != NULL)
	{
		printf("Command %s\n",pch);
		parse_http_cmd_token(pch);
		pch = strtok (NULL, "?");
	}
}

int parse_http_cmd_token(char* cmd)
{
	if(strcmp("PGM=off",cmd)==0)
	{
		info("HTTP","Commqnd receive: PGM Off");
		radiateur_init_pgm_piece(RD_CUISINE);
		radiateur_init_pgm_piece(RD_DAPHNEE);
		radiateur_init_pgm_piece(RD_VICTOR);
		radiateur_init_pgm_piece(RD_HOMECINEMA);
		radiateur_init_pgm_piece(RD_SALON);
	}

	if(strcmp("PGM=normal",cmd)==0)
	{
		info("HTTP","Commqnd receive: PGM normal");
		radiateur_init_pgm_piece(RD_CUISINE);
		radiateur_init_pgm_chambre(RD_DAPHNEE);
		radiateur_init_pgm_chambre(RD_VICTOR);
		radiateur_init_pgm_piece(RD_HOMECINEMA);
		radiateur_init_pgm_salon(RD_SALON);

	}
}

int get_http_cmd(char* bufhttp,int buflen)
{
	int len=0;
	int ii;
 	char buf[512];
	struct tm * timeinfo;

	sprintf(buf,"<html><head><title>Sample \"Hello, World\" Application</title></head>\n");
	strcpy(&bufhttp[len],buf);
	len+=strlen(buf);

	sprintf(buf,"<body bgcolor=white>\n");
	strcpy(&bufhttp[len],buf);
	len+=strlen(buf);



	// Radiator
	sprintf(buf,"[Radiator]\n");
	strcpy(&bufhttp[len],buf);
	len+=strlen(buf);

	for(ii=0;ii<RD_LAST;ii++)
	{

		sprintf(buf,"<p> %s\n",radiateur[ii].name);
		strcpy(&bufhttp[len],buf);
		len+=strlen(buf);

		sprintf(buf,"<a href=\"hc_cmd?RAD_%s=15\">15°C</a> \n",radiateur[ii].name,radiateur[ii].name);
		strcpy(&bufhttp[len],buf);
		len+=strlen(buf);

		sprintf(buf,"<a href=\"hc_cmd?RAD_%s=20\">20°C</a> \n",radiateur[ii].name,radiateur[ii].name);
		strcpy(&bufhttp[len],buf);
		len+=strlen(buf);

		sprintf(buf,"<a href=\"hc_cmd?RAD_%s=22\">22°C</a> \n",radiateur[ii].name,radiateur[ii].name);
		strcpy(&bufhttp[len],buf);
		len+=strlen(buf);
	}

	sprintf(buf,"<p>All radiators\n");
	strcpy(&bufhttp[len],buf);
	len+=strlen(buf);


	// 15°C
	sprintf(buf,"<a href=\"hc_cmd");
	strcpy(&bufhttp[len],buf);
	len+=strlen(buf);
	for(ii=0;ii<RD_LAST;ii++)
	{
		sprintf(buf,"?RAD_%s=15",radiateur[ii].name);
		strcpy(&bufhttp[len],buf);
		len+=strlen(buf);
	}
	sprintf(buf,"\">15°C</a> \n");
	strcpy(&bufhttp[len],buf);
	len+=strlen(buf);

	// 20°C
	sprintf(buf,"<a href=\"hc_cmd");
	strcpy(&bufhttp[len],buf);
	len+=strlen(buf);
	for(ii=0;ii<RD_LAST;ii++)
	{
		sprintf(buf,"?RAD_%s=20",radiateur[ii].name);
		strcpy(&bufhttp[len],buf);
		len+=strlen(buf);
	}
	sprintf(buf,"\">20°C</a> \n");
	strcpy(&bufhttp[len],buf);
	len+=strlen(buf);

	// 20°C
	sprintf(buf,"<a href=\"hc_cmd");
	strcpy(&bufhttp[len],buf);
	len+=strlen(buf);
	for(ii=0;ii<RD_LAST;ii++)
	{
		sprintf(buf,"?RAD_%s=22",radiateur[ii].name);
		strcpy(&bufhttp[len],buf);
		len+=strlen(buf);
	}
	sprintf(buf,"\">22°C</a> \n");
	strcpy(&bufhttp[len],buf);
	len+=strlen(buf);

	// Radiator program
	sprintf(buf,"<p>[Radiator program]\n");
	strcpy(&bufhttp[len],buf);
	len+=strlen(buf);


	sprintf(buf,"<p>All radiators\n");
	strcpy(&bufhttp[len],buf);
	len+=strlen(buf);


	// Off
	sprintf(buf,"<a href=\"hc_cmd?PGM=off\">Off </a>");
	strcpy(&bufhttp[len],buf);
	len+=strlen(buf);

	// Normal
	sprintf(buf,"<a href=\"hc_cmd?PGM=normal\">Normal</a>");
	strcpy(&bufhttp[len],buf);
	len+=strlen(buf);

	// Thermometer
	sprintf(buf,"<p><p><p>[Thermometer]\n");
	strcpy(&bufhttp[len],buf);
	len+=strlen(buf);

	for(ii=0;ii<TH_LAST;ii++)
	{

		sprintf(buf,"<%s>\n  temp=%f\n  date=%s",thermometer[ii].name,thermometer[ii].temperature, ctime(&thermometer[ii].mesure_date));
		strcpy(&bufhttp[len],buf);
		len+=strlen(buf);
		if(len>buflen-512)
		{
			return len;
		}
	}

	sprintf(buf,"</body></html>\n");
	strcpy(&bufhttp[len],buf);
	len+=strlen(buf);

	return len;
}

void info(char* tag,char *format,...)
{
	va_list args;
	va_start(args,format);

	printf("\e[32m[INFO] \e[0m");
	printf("[%s] ",tag);
	vprintf(format,args);
	printf("\n");
	va_end(args);

	va_start(args,format);
	log_msg("INFO",tag,format,args);
	va_end(args);

}

void warning(char* tag,char *format,...)
{
	va_list args;
	va_start(args,format);

	printf("\e[33m[WARNING] \e[0m");
	printf("[%s] ",tag);
	vprintf(format,args);
	printf("\n");
	va_end(args);

	va_start(args,format);
	log_msg("WARNING",tag,format,args);
	va_end(args);
}

void init_msg(void)
{
 int ii;

	for(ii=0;ii<NBR_MSG_MAX;ii++)
	{
		msg_log[ii].date=0;
		msg_log[ii].level[0]=0;
		msg_log[ii].message[0]=0;
		msg_log[ii].tag[0]=0;
	}

}
