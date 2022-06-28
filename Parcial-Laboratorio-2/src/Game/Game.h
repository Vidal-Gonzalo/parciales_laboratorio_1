/*
 * Game.h
 *
 *  Created on: 24 jun 2022
 *      Author: gonza
 */

#ifndef GAME_H_
#define GAME_H_
#include "../General.h"
#define MAX_CHARS_NAME 50
#define MAX_CHARS_COMPANY 50
#define MAX_CHARS_GENRE 50
#define PLATFORM 1
#define ADVENTURE 2
#define LABYRINTH 3
#define OTHER 4

typedef struct {
	int id;
	char name[MAX_CHARS_NAME];
	char company[MAX_CHARS_COMPANY];
	int genre;
} Game;

Game* Game_new();

Game* Game_newParametrosTxt(char *id, char *name, char *company, char *genre);
Game* Game_newParametros(int *id, char *name, char *company, int *genre);

int Game_getParametros(Game *game, int *id, char *name, char *company,
		int *genre);

void Game_delete(Game *this);

int Game_setId(Game *this, int id);
int Game_setIdTxt(Game *this, char *id);

int Game_getId(Game *this, int *id);
int Game_getIdTxt(Game *this, char *id);

int Game_setName(Game *this, char *name);
int Game_getName(Game *this, char *name);

int Game_setCompany(Game *this, char *company);
int Game_getCompany(Game *this, char *company);

int Game_setGenre(Game *this, int genre);
int Game_setGenreTxt(Game *this, char *genre);

int Game_getGenre(Game *this, int *genre);
int Game_getGenreTxt(Game *this, char *genre);

void Game_printOne(Game *p);

int Game_getUniqueId();

int Game_readGenreGame(int *genre, char *genreTxt);
int Game_verifyGenreTxt(char *genreTxt, int *genreVerified);

int Game_CheckForBiggerName(void *pGame1, void *pGame2);
int Game_CheckForSameGenre(void *pGame, int id);

#endif /* GAME_H_ */
