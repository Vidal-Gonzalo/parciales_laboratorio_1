/*
 * PlayroomController.h
 *
 *  Created on: 24 jun 2022
 *      Author: gonza
 */

#ifndef PLAYROOMCONTROLLER_H_
#define PLAYROOMCONTROLLER_H_
#include "../LinkedList.h"
#include "../Parser.h"
#include "../General.h"
#include "Playroom.h"
#include "InputPlayroom.h"

int PlayroomController_LoadPlayroomsFromText(char *path,
		LinkedList *pArrayListPlayroom);
int PlayroomController_registerAPlayroom(char *path,
		LinkedList *pArrayListPlayroom);
int PlayroomController_printPlayrooms(LinkedList *pArrayPlayrooms, int size);
int PlayroomController_PrintEspecificPlayroom(LinkedList *pArrayPlayrooms,
		int size);
int PlayroomController_SearchPlayroomIndexPerId(LinkedList *playroomList,
		int *id);
int PlayroomController_SearchPlayroomIndexPerName(LinkedList *playroomList,
		char *name);
int PlayroomController_SavePlayroomAsText(char *path,
		LinkedList *pArrayListPlayroom);
#endif /* PLAYROOMCONTROLLER_H_ */
