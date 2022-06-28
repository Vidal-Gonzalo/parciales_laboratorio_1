/*
 * Parser.h
 *
 *  Created on: 24 jun 2022
 *      Author: gonza
 */

#ifndef PARSER_H_
#define PARSER_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Playroom/Playroom.h"
#include "./Arcade/Arcade.h"
#include "./Game/Game.h"
#include "LinkedList.h"


int parser_PlayroomFromText(FILE* pFile , LinkedList* pArrayListPlayroom);
int parser_ReadPlayroomFromText(FILE *pFile, Playroom* pArrayListPlayroom);

int parser_ArcadeFromText(FILE* pFile , LinkedList* pArrayListArcade);
int parser_ReadArcadeFromText(FILE *pFile, Arcade* pArrayListArcade);

int parser_GameFromText(FILE* pFile , LinkedList* pArrayListGame);
int parser_ReadGameFromText(FILE *pFile, Game* pArrayListGame);

#endif /* PARSER_H_ */
