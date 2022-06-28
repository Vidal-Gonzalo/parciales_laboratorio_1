/*
 * ArcadeController.h
 *
 *  Created on: 26 jun 2022
 *      Author: gonza
 */

#ifndef ARCADE_ARCADECONTROLLER_H_
#define ARCADE_ARCADECONTROLLER_H_

#include "../LinkedList.h"
#include "../Parser.h"
#include "../General.h"
#include "Arcade.h"
#define MAX_COL 20

int ArcadeController_LoadArcadesFromText(char *path, LinkedList *pArrayListArcade);
int ArcadeController_PrintArcades(LinkedList *pArrayListGame, int size);
int ArcadeController_SearchArcadeIndexPerId(LinkedList *pArrayListArcade, int *id);
int ArcadeController_SaveArcadeAsText(char *path, LinkedList *pArrayListGame);

#endif /* ARCADE_ARCADECONTROLLER_H_ */

