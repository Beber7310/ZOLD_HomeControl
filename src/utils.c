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

#define NBR_MSG_MAX	10000
message_t msg_log[NBR_MSG_MAX];

int last_msg=0;

void log_msg(const char* level,char* tag,char *format,...)
{
	va_list args;
	va_start(args,format);

	strncpy(msg_log[last_msg].level,level,sizeof(msg_log[0].level));
	strncpy(msg_log[last_msg].tag,tag,sizeof(msg_log[0].tag));
	sprintf(msg_log[last_msg].message,format,args);


	last_msg++;
	if(last_msg>=NBR_MSG_MAX)
		last_msg=0;

	va_end(args);

}

void send_http_msg(FILE* stream)
{
	int ii;
	int w;
	char buf[512];
	ii=(last_msg-1);

	while(ii!=last_msg)
	{
		if(ii<0)
			ii=NBR_MSG_MAX-1;

		sprintf(buf,"[%s] [%s] %s\n",msg_log[ii].level,msg_log[ii].tag,msg_log[ii].message);

		for (w=0; w<strlen(buf); )
		{
			int a = fwrite(buf+w, 1, strlen(buf)-w, stream);
			if (a<=0)
			{
				if (errno==EINTR) continue;
				break;
			}
			w += a;
		}
		ii--;
	}
}

void info(char* tag,char *format,...)
{
	va_list args;
	va_start(args,format);

	printf("\e[32m[INFO] \e[0m");
	printf("[%s] ",tag);
	vprintf(format,args);
	log_msg("INFO",tag,format,args);
	printf("\n");
	va_end(args);

}
void warning(char* tag,char *format,...)
{
	va_list args;
	va_start(args,format);

	printf("\e[33m[WARNING] \e[0m");
	printf("[%s] ",tag);
	vprintf(format,args);
	log_msg("WARNING",tag,format,args);
	printf("\n");
	va_end(args);

}
