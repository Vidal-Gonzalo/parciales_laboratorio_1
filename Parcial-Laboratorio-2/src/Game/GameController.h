/*
 * GameController.h
 *
 *  Created on: 25 jun 2022
 *      Author: gonza
 */

#ifndef GAME_GAMECONTROLLER_H_
#define GAME_GAMECONTROLLER_H_
#include "../LinkedList.h"
#include "../Parser.h"
#include "../General.h"
#include "Game.h"
#include "InputGame.h"

int GameController_LoadGamesFromText(char *path, LinkedList *pArrayListGame);
int GameController_RegisterGame(char *path, LinkedList *pArrayListGame);
int GameController_PrintGames(LinkedList *pArrayListGame, int size);
int GameController_SearchGameIndexPerId(LinkedList *gamesList, int *id);
int GameController_SaveGameAsText(char *path, LinkedList *pArrayListGame);
#endif /* GAME_GAMECONTROLLER_H_ */
