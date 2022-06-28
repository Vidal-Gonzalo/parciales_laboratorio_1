/*
 * Playroom.h
 *
 *  Created on: 24 jun 2022
 *      Author: gonza
 */

#ifndef PLAYROOM_H_
#define PLAYROOM_H_
#define MAX 30
#define MAX_CHARS_NAME 50
#define MAX_CHARS_ADDRESS 50
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int id;
	char name[MAX_CHARS_NAME];
	char address[MAX_CHARS_ADDRESS];
	int type;
} Playroom;

/** \brief Retorna un espacio de memoria para un Playroom
 *
 * \return Playroom*
 *
 */

Playroom* Playroom_new();

/** \brief Setea los datos de un nuevo pasajero recibiendo chars como argumentos
 *
 * \param char *id
 * \param char *name
 * \param char *address
 * \param char *type
 * \return Playroom*
 *
 */

Playroom* Playroom_newParametrosTxt(char *id, char *name, char *address,
		char *type);

/** \brief Setea los datos de un nuevo pasajero
 *
 * \param int *id
 * \param char *name
 * \param char *address
 * \param float *precio
 * \param char *codigoVuelo
 * \param int *tipoPasajero
 * \param int *statusFlight
 * \return Playroom*
 *
 */

Playroom* Playroom_newParametros(int *id, char *name, char *address, int *type);

/** \brief Libera el espacio de memoria dedicado a un pasajero en particular
 *
 * \param Playroom* this
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

int Playroom_getParametros(Playroom *playroom, int *id, char *name,
		char *address, int *type);

void Playroom_delete(Playroom *this);

int Playroom_setId(Playroom *this, int id);

int Playroom_setIdTxt(Playroom *this, char *id);

int Playroom_getId(Playroom *this, int *id);

int Playroom_getIdTxt(Playroom *this, char *id);

int Playroom_setName(Playroom *this, char *name);

int Playroom_getName(Playroom *this, char *name);

int Playroom_setAddress(Playroom *this, char *address);
int Playroom_getAddress(Playroom *this, char *address);

int Playroom_setType(Playroom *this, int type);
int Playroom_setTypeTxt(Playroom *this, char *type);

int Playroom_getType(Playroom *this, int *type);

int Playroom_getTypeTxt(Playroom *this, char *type);

int Playroom_readTypePlayroom(int *type, char *typeTxt);
int Playroom_getUniqueId();
void Playroom_printOne(Playroom *p);
int Playroom_verifyTypeTxt(char *typeTxt, int *typeVerified);

#endif /* PLAYROOM_H_ */
