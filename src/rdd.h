/*
 * rdd.h
 *
 *  Created on: 25 déc. 2013
 *      Author: Bertrand
 */

#ifndef RDD_H_
#define RDD_H_



#endif /* RDD_H_ */


void rrd_create()
{
	system("rrdtool create temp.rrd --start 1297810800 DS:exterieur:GAUGE:600:U:U DS:salon:GAUGE:600:U:U RRA:AVERAGE:0.5:1:24 RRA:AVERAGE:0.5:6:12");
}
