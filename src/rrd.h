/*
 * rdd.h
 *
 *  Created on: 25 déc. 2013
 *      Author: Bertrand
 */

#ifndef RDD_H_
#define RDD_H_



#endif /* RDD_H_ */


int rrd_add_temp(char * thermometer, float temp);
void rrd_create_temp(char* thermometer);
int rrd_create_rad_pgm(char* thermometer,float* pgm);

int rrd_test(void);
