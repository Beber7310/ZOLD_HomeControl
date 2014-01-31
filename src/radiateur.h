/*
 * radiateur.h
 *
 *  Created on: 16 déc. 2013
 *      Author: Bertrand
 */

#ifndef RADIATEUR_H_
#define RADIATEUR_H_

void radiateur_init(void);
void radiateur_init_pgm_chambre(int rad);
void radiateur_init_pgm_cuisine(int rad);
void radiateur_init_pgm_homecinema(int rad);
void radiateur_init_pgm_salon(int rad);
void radiateur_init_pgm_piece(int rad);
void * radiateur_loop(void * arg);

#endif /* RADIATEUR_H_ */
