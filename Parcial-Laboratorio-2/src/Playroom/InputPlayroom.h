/*
 * InputPlayroom.h
 *
 *  Created on: 24 jun 2022
 *      Author: gonza
 */

#ifndef INPUTPLAYROOM_H_
#define INPUTPLAYROOM_H_

#include "../General.h"
#include "Playroom.h"

#define MAX 30
#define MAX_CHARS_NAME 50
#define MAX_CHARS_ADDRESS 50

int Playroom_LoadPlayroom(Playroom *auxiliar);

int Playroom_AskForPlayroomName(char *playroomName);

int Playroom_AskForPlayroomID(int *id);

int Playroom_ModifyOne(Playroom *p);

#endif /* INPUTPLAYROOM_H_ */
