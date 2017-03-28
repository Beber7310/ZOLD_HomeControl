/*
 * http.h
 *
 *  Created on: 3 janv. 2014
 *      Author: Astro
 */

#ifndef HTTP_H_
#define HTTP_H_

void * http_loop(void * arg);
int http_q_data(int * current_len,char * bufhttp,char *format,...);


#endif /* HTTP_H_ */
