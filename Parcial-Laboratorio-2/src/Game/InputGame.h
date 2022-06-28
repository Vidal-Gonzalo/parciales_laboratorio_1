/*
 * InputGame.h
 *
 *  Created on: 25 jun 2022
 *      Author: gonza
 */

#ifndef GAME_INPUTGAME_H_
#define GAME_INPUTGAME_H_

#include "../General.h"
#include "Game.h"

#define MAX 30
#define MAX_CHARS_NAME 50
#define MAX_CHARS_COMPANY 50
#define MAX_CHARS_GENRE 50

int Game_LoadGame(Game *auxiliar);

int Game_AskForGameGenre(int *genre);

#endif /* GAME_INPUTGAME_H_ */
