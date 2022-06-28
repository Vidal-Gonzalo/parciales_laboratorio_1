/*
 * Parser.c
 *
 *  Created on: 24 jun 2022
 *      Author: gonza
 */

#include "Parser.h"

int parser_PlayroomFromText(FILE *pFile, LinkedList *pArrayListPlayroom) {
	//fOpen lo realizó la función q llama a este parser
	int r = -1;
	FILE *idFile;
	Playroom *playroom = NULL;
	char id[5];
	int auxId = 0;
	char name[MAX_CHARS_NAME];
	char address[MAX_CHARS_ADDRESS];
	char type[50];

	if (pFile != NULL && pArrayListPlayroom != NULL) {
		do {
			if (fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", id, name, address,
					type) == 4) {
				if (strcmp("id", id) != 0) {
					playroom = Playroom_newParametrosTxt(id, name, address,
							type);
					if (playroom != NULL) {
						if (playroom->id > auxId) {
							auxId = playroom->id;
							idFile = fopen("maxIdPlayroom", "w");
							fprintf(idFile, "%d", auxId);
							fclose(idFile);
						}

						ll_add(pArrayListPlayroom, playroom);
					}
				}
			}
		} while (!feof(pFile));
		r = 0;
	}
	return r;
}

int parser_ReadPlayroomFromText(FILE *pFile, Playroom *pArrayListPlayroom) {
	//fOpen lo realizó la función q llama a este parser
	int r = -1;
	Playroom *playroom = NULL;
	int i = 0;
	char id[5];
	char name[MAX_CHARS_NAME];
	char address[MAX_CHARS_ADDRESS];
	char type[5];

	if (pFile != NULL && pArrayListPlayroom != NULL) {
		do {
			if (fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", id, name, address,
					type) == 4) {
				if (strcmp("ID", id) != 0) {
					playroom = Playroom_newParametrosTxt(id, name, address,
							type);
					if (playroom != NULL) {
						pArrayListPlayroom[i] = *playroom;
						i++;
					}
				}
			}
		} while (!feof(pFile));
		r = 0;
	}
	return r;
}

int parser_ArcadeFromText(FILE *pFile, LinkedList *pArrayListArcade) {
	int r = -1;
	FILE *idFile;
	Arcade *arcade = NULL;
	char id[15];
	char playroomId[15];
	char gameId[15];
	int auxId = 0;
	char nationality[MAX_CHARS_NATIONALITY];
	char soundType[15];
	char players[5];
	char maxCoins[5];

	if (pFile != NULL && pArrayListArcade != NULL) {
		do {
			if (fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
					id, playroomId, gameId, nationality, soundType, players,
					maxCoins) == 7) {
				if (strcmp("id", id) != 0) {
					arcade = Arcade_newParametrosTxt(id, playroomId, gameId,
							nationality, soundType, players, maxCoins);
					if (arcade != NULL) {
						if (arcade->id > auxId) {
							auxId = arcade->id;
							idFile = fopen("maxIdArcade", "w");
							fprintf(idFile, "%d", auxId);
							fclose(idFile);
						}
						ll_add(pArrayListArcade, arcade);
					}
				}
			}
		} while (!feof(pFile));
		r = 0;
	}
	return r;
}
int parser_ReadArcadeFromText(FILE *pFile, Arcade *pArrayListArcade) {
	int r = -1;
	Arcade *arcade = NULL;
	char id[5];
	int i = 0;
	char playroomId[5];
	char gameId[5];
	char nationality[MAX_CHARS_NATIONALITY];
	char soundType[5];
	char players[5];
	char maxCoins[5];

	if (pFile != NULL && pArrayListArcade != NULL) {
		do {
			if (fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
					id, playroomId, gameId, nationality, soundType, players,
					maxCoins) == 7) {
				if (strcmp("id", id) != 0) {
					arcade = Arcade_newParametrosTxt(id, playroomId, gameId,
							nationality, soundType, players, maxCoins);
					if (arcade != NULL) {
						pArrayListArcade[i] = *arcade;
						i++;
					}
				}
			}
		} while (!feof(pFile));
		r = 0;
	}
	return r;
}

int parser_GameFromText(FILE *pFile, LinkedList *pArrayListGame) {
	int r = -1;
	FILE *idFile;
	Game *game = NULL;
	char id[5];
	int auxId = 0;
	char name[MAX_CHARS_NAME];
	char company[MAX_CHARS_COMPANY];
	char genre[MAX_CHARS_GENRE];

	if (pFile != NULL && pArrayListGame != NULL) {
		do {
			if (fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", id, name, company,
					genre) == 4) {
				if (strcmp("id", id) != 0) {
					game = Game_newParametrosTxt(id, name, company, genre);
					if (game != NULL) {
						if (game->id > auxId) {
							auxId = game->id;
							idFile = fopen("maxIdGame", "w");
							fprintf(idFile, "%d", auxId);
							fclose(idFile);
						}
						ll_add(pArrayListGame, game);
					}
				}
			}
		} while (!feof(pFile));
		r = 0;
	}
	return r;
}
int parser_ReadGameFromText(FILE *pFile, Game *pArrayListGame) {
	int r = -1;
	Game *game = NULL;
	char id[5];
	int i = 0;
	char name[MAX_CHARS_NAME];
	char company[MAX_CHARS_COMPANY];
	char genre[MAX_CHARS_GENRE];

	if (pFile != NULL && pArrayListGame != NULL) {
		do {
			if (fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", id, name, company,
					genre) == 4) {
				if (strcmp("id", id) != 0) {
					game = Game_newParametrosTxt(id, name, company, genre);
					if (game != NULL) {
						pArrayListGame[i] = *game;
						i++;
					}
				}
			}
		} while (!feof(pFile));
		r = 0;
	}
	return r;
}
