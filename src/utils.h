/*
 * utils.h
 *
 *  Created on: 25 déc. 2013
 *      Author: Bertrand
 */

#ifndef UTILS_H_
#define UTILS_H_

void init_msg(void);
void info(char* tag,char *format,...);
void warning(char* tag,char *format,...);

int get_http_msg(char* buf,int buflen);
int get_http_sts(char* bufhttp,int buflen);
int get_http_sts_short(char* bufhttp,int buflen);
int get_http_cmd(char* bufhttp,int buflen);
int parse_http_thermostat(char* cmd);
int parse_http_thermostat_status(char* cmd);
float parse_http_thermostat_target(char* cmd);
int parse_http_cmd(char* cmd);
int parse_http_cmd_token(char* cmd);
int parse_http_cmd_RAD_token(char* cmd);
int parse_http_cmd_LIGHT_token(char* cmd);
float parse_http_temp(char* cmd);
int get_pgm_index(void);
char hextochar(char hex);
typedef struct {
	char 	level[16];
	char 	tag[32];
	char 	message[128];
	time_t 	date;

} message_t;

#endif /* UTILS_H_ */
