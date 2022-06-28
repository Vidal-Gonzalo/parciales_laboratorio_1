/*
 * Relationships_ArcadePlayroomAndGames.h
 *
 *  Created on: 25 jun 2022
 *      Author: gonza
 */

#ifndef RELATIONSHIPS_RELATIONSHIPS_ARCADEPLAYROOMANDGAMES_H_
#define RELATIONSHIPS_RELATIONSHIPS_ARCADEPLAYROOMANDGAMES_H_

#include <stdio.h>
#include <stdlib.h>

#include "../LinkedList.h"
#include "../Arcade/Arcade.h"
#include "../Arcade/ArcadeController.h"

#include "../Playroom/Playroom.h"
#include "../Playroom/PlayroomController.h"

#include "../Game/Game.h"
#include "../Game/GameController.h"

int Relationship_ArcadeInput(LinkedList *playroomList, LinkedList *arcadeList,
		LinkedList *gameList, Arcade *arcadeToAdd);

int Relationship_RegisterAnArcadeInPlayroom(LinkedList *playroomList,
		LinkedList *arcadeList, LinkedList *gameList);

int Relationship_ModifyArcade(LinkedList *arcadeList, LinkedList *gameList);

int Relationship_PrintCompletePlayroom(LinkedList *pArrayListPlayroom,
		LinkedList *pArrayListGame, LinkedList *pArrayListArcade,
		int arcadeListSize, int playroomListSize);

int Relationship_PrintArcadesWithGame(LinkedList *pArrayListArcade,
		LinkedList *pArrayListGame, int sizeArcadeList);

int Relationship_PrintArcadesWithPlayroomAndGame(LinkedList *pArrayListArcade,
		LinkedList *pArrayListPlayroom, LinkedList *pArrayListGame,
		int sizeArcadeList, int sizePlayroomList, int sizeGameList);

int Relationship_PrintArcadesOfPlayroom(LinkedList *pArrayListArcade,
		LinkedList *pArrayListPlayroom, LinkedList *pArrayListGame,
		int sizeArcadeList, int sizePlayroomList);

int Relationship_RemoveArcade(LinkedList *pArrayListArcade,
		LinkedList *pArrayListPlayroom, LinkedList *pArrayListGame);

int Relationship_RemovePlayroomAndArcade(LinkedList *pArrayListPlayroom,
		LinkedList *pArrayListArcade);

int Relationship_PrintPlayroomWithMaxArcade(LinkedList *pArrayListArcade,
		LinkedList *pArrayListPlayroom, int playroomListSize,
		int arcadeListSize);

int Relationship_PrintPlayroomWithArcade(LinkedList *pArrayListPlayroom,
		LinkedList *pArrayListArcade, int playroomSize, int arcadeSize);

int Relationship_PrintArcadeForTwoPlayers(LinkedList *pArrayListArcade,
		LinkedList *pArrayListPlayroom, LinkedList *pArrayListGame,
		int sizeArcadeList);

int Relationship_PrintSpecificKindOfArcade(LinkedList *pArrayListArcade,
		LinkedList *pArrayListGame, int arcadeListSize, int soundTypeArcade,
		int gameGenre);

int Relationship_CreateSpecificGameList(LinkedList *newGameList,
		LinkedList *pArrayListGame, LinkedList *pArrayListArcade,
		int arcadeListSize, int soundTypeArcade, int gameGenre);

int Relationship_PrintNewGameListSortedByGameName(LinkedList *newList,
		LinkedList *pArrayListArcade, int arcadeListSize);

int Relationship_PrintArcadeListOfAPlayroom(LinkedList *pArrayListArcade,
		int arcadeListLength, int playroomId);

#endif /* RELATIONSHIPS_RELATIONSHIPS_ARCADEPLAYROOMANDGAMES_H_ */
