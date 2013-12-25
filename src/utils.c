/*
 * utils.c
 *
 *  Created on: 25 déc. 2013
 *      Author: Bertrand
 */
#include<stdio.h>
#include<stdarg.h>
#include<stdlib.h>

void info(char* tag,char *format,...)
{
	va_list args;
	va_start(args,format);

	printf("\e[32m[INFO] \e[0m");
	printf("%s ",tag);
	vprintf(format,args);
	printf("\n");
	va_end(args);

}
void warning(char* tag,char *format,...)
{
	va_list args;
	va_start(args,format);

	printf("\e[33m[WARNING] \e[0m");
	printf("%s ",tag);
	vprintf(format,args);
	printf("\n");
	va_end(args);

}
