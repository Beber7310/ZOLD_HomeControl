/*
 * utils.h
 *
 *  Created on: 25 déc. 2013
 *      Author: Bertrand
 */

#ifndef UTILS_H_
#define UTILS_H_

void info(char* tag,char *format,...);
void warning(char* tag,char *format,...);

void send_http_msg(FILE* stream);

typedef struct {
	char 	level[16];
	char 	tag[32];
	char 	message[128];
	time_t 	date;

} message_t;

#endif /* UTILS_H_ */
