/*
 * GameController.c
 *
 *  Created on: 25 jun 2022
 *      Author: gonza
 */

#include "GameController.h"

/** \brief Carga el contenido de *path a la LinkedList recibida
 *
 *	\param char *path
 * \param LinkedList *pArray
 * \return (0) si salio bien (-1) si el path o la linkedList es nula
 *
 */

int GameController_LoadGamesFromText(char *path, LinkedList *pArrayListGame) {
	int r = -1;
	FILE *pFile;

	if (path != NULL && pArrayListGame != NULL) {
		if (ll_len(pArrayListGame) > 0) {
			if (confirmation(
					"\nSi carga los datos una vez más, se eliminaran los anteriores\n¿Esta seguro que desea realizar esta accion?(1:Si/Otro numero:No)\n",
					"Ha habido un error\n") == 1) {
				ll_clear(pArrayListGame);
			} else {
				return r = -2; //Carga de datos denegada
			}
		}
		pFile = fopen(path, "r");
		if (pFile == NULL) {
			pFile = fopen(path, "w");
			fclose(pFile);
			r = 1;
		} else {
			if (parser_GameFromText(pFile, pArrayListGame) == 0) {
				r = 0;
			} else {
				r = -4;
			}
		}
		fclose(pFile);
	}
	return r;
}

int GameController_RegisterGame(char *path, LinkedList *pArrayListGame) {
	int r = -1;
	Game *game;
	Game auxGame;

	if (path != NULL && pArrayListGame != NULL) {
		if (Game_LoadGame(&auxGame) == 0) {
			auxGame.id = Game_getUniqueId();
			game = Game_newParametros(&auxGame.id, auxGame.name,
					auxGame.company, &auxGame.genre);
			if (game != NULL) {
				puts("Juego añadido: \n");
				Game_printOne(game);
				ll_add(pArrayListGame, game);
				r = 0;
			}
		}
	}
	return r;
}

/** \brief Imprime el contenido de la LinkedList recibida
 *
 *	\param LinkedList *pArrayListArcade
 * \param  int size
 * \return (0) si salio bien (-1) si la linkedList es nula o el size es menor a 0
 *
 */

int GameController_PrintGames(LinkedList *pArrayGames, int size) {
	int r = -1;
	Game *game;
	char gameGenreTxt[50];

	if (pArrayGames != NULL) {
		if (size > 0) {
			printf("%*s | %*s | %*s | %*s\n", -4, "ID", -MAX, "Nombre", -MAX,
					"Compañia", -MAX, "Genero");
			printf("%*c | %*c | %*c | %*c\n", -4, '-', -MAX, '-', -MAX, '-',
					-MAX, '-');
			for (int i = 0; i < size; i++) {
				game = (Game*) ll_get(pArrayGames, i);
				Game_readGenreGame(&game->genre, gameGenreTxt);
				printf("%-4d | %-30s | %-30s | %-30s\n", game->id, game->name,
						game->company, gameGenreTxt);
				r = 0;

			}
		}
	}

	return r;
}

/** \brief Busca en la LinkedList el ID recibido y retorna su index
 *
 *	\param LinkedList *pArrayListArcade
 * \param  int *id
 * \return index si salio bien (-1) si la linkedList es nula o el size es menor a 0
 *
 */

int GameController_SearchGameIndexPerId(LinkedList *gamesList, int *id) {
	int r = -1;
	Game *game;
	int gameListLength = ll_len(gamesList);

	if (gamesList != NULL && id > 0) {
		for (int i = 0; i < gameListLength; i++) {
			game = (Game*) ll_get(gamesList, i);
			if (game->id == *id) {
				r = i;
				break;
			}
		}
	}
	return r;
}

int GameController_FilterListPerGenre(LinkedList *gamesList) {
	int r = -1;
	int genre;
	LinkedList *auxList = ll_newLinkedList();

	if (gamesList != NULL && genre > 0) {
		if (Game_AskForGameGenre(&genre) == 0) {
			auxList = ll_filter(gamesList, Game_CheckForSameGenre, genre);
			if (auxList != NULL) {
				int auxListLength = ll_len(auxList);
				GameController_PrintGames(auxList, auxListLength);
				r = 0;
			}
		}

	}

	return r;
}

/** \brief Guarda en el path recibido la linkedList recibida.
 *
 * \param char *path,
 * \param LinkedList *pArrayListArcade
 * \return 0 si salio bien (-1) si la linkedList es nula o el path es nulo
 *
 */

int GameController_SaveGameAsText(char *path, LinkedList *pArrayListGame) {
	int r = -1;
	FILE *pFile = NULL;
	Game *auxGame;

	int id;
	char name[MAX_CHARS_NAME];
	char company[MAX_CHARS_ADDRESS];
	int genre;
	char genreText[MAX_CHARS_NAME];
	int listGameLength = ll_len(pArrayListGame);

	if (path != NULL && pArrayListGame != NULL) {
		pFile = fopen(path, "w");
		if (pFile != NULL) {
			r = 0;
			fprintf(pFile, "id, Nombre, Compañia, Genero\n");
			for (int i = 0; i < listGameLength; i++) {
				auxGame = (Game*) ll_get(pArrayListGame, i);
				if (auxGame != NULL) {
					if (Game_getParametros(auxGame, &id, name, company, &genre)
							== 0) {
						Game_readGenreGame(&auxGame->genre, genreText);
						fprintf(pFile, "%d,%s,%s,%s\n", id, name, company,
								genreText);
						r = 0;
					}

				}
			}
			fclose(pFile);
		}
	}

	return r;
}

