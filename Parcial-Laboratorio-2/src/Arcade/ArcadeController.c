/*
 * ArcadeController.c
 *
 *  Created on: 26 jun 2022
 *      Author: gonza
 */

#include "ArcadeController.h"

/** \brief Carga el contenido de *path a la LinkedList recibida
 *
 *	\param char *path
 * \param LinkedList *pArray
 * \return (0) si salio bien (-1) si el path o la linkedList es nula
 *
 */

int ArcadeController_LoadArcadesFromText(char *path,
		LinkedList *pArrayListArcades) {
	int r = -1;
	FILE *pFile;

	if (path != NULL && pArrayListArcades != NULL) {
		if (ll_len(pArrayListArcades) > 0) {
			if (confirmation(
					"\nSi carga los datos una vez más, se eliminaran los anteriores\n¿Esta seguro que desea realizar esta accion?(1:Si/Otro numero:No)\n",
					"Ha habido un error\n") == 1) {
				ll_clear(pArrayListArcades);
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
			if (parser_ArcadeFromText(pFile, pArrayListArcades) == 0) {
				r = 0;
			} else {
				r = -4;
			}
		}
		fclose(pFile);
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

int ArcadeController_PrintArcades(LinkedList *pArrayListArcade, int size) {
	int r = -1;
	Arcade *arcade;
	char arcadeSoundTypeTxt[50];

	if (pArrayListArcade != NULL && size > 0) {
		printf("%*s | %*s | %*s | %*s | %*s | %*s | %*s\n", -4, "ID", -8,
				"Salon ID", -8, "Juego ID", -MAX_COL, "Nacionalidad", -MAX_COL,
				"Tipo de sonido", -10, "Jugadores", -2, "Fichas");
		printf("%*c | %*c | %*c | %*c | %*c | %*c | %*c\n", -4, '-', -8, '-',
				-8, '-', -MAX_COL, '-', -MAX_COL, '-', -10, '-', -2, '-');
		for (int i = 0; i < size; i++) {
			arcade = (Arcade*) ll_get(pArrayListArcade, i);
			Arcade_readSoundTypeArcade(&arcade->soundType, arcadeSoundTypeTxt);
			printf("%-4d | %-8d | %-8d | %-20s | %-20s | %-10d | %d\n",
					arcade->id, arcade->playroomId, arcade->gameId,
					arcade->nationality, arcadeSoundTypeTxt, arcade->players,
					arcade->maxCoins);
			r = 0;
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

int ArcadeController_SearchArcadeIndexPerId(LinkedList *arcadeList, int *id) {
	int r = -1;
	Arcade *arcade;
	int arcadeListLength = ll_len(arcadeList);

	if (arcadeList != NULL && id > 0) {
		for (int i = 0; i < arcadeListLength; i++) {
			arcade = (Arcade*) ll_get(arcadeList, i);
			if (arcade->id == *id) {
				r = i;
				break;
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

int ArcadeController_SaveArcadeAsText(char *path, LinkedList *pArrayListArcade) {
	int r = -1;
	FILE *pFile = NULL;
	Arcade *auxArcade;
	int listArcadeLength = ll_len(pArrayListArcade);

	int id;
	int playroomId;
	int gameId;
	char nationality[MAX_CHARS_NAME];
	int soundType;
	char soundTypeText[MAX_CHARS_NAME];
	int players;
	int maxCoins;

	if (path != NULL && pArrayListArcade != NULL) {
		pFile = fopen(path, "w");
		if (pFile != NULL) {

			fprintf(pFile,
					"id, SalonID, JuegoID, Nacionalidad, Tipo de sonido, Jugadores, Fichas\n");
			for (int i = 0; i < listArcadeLength; i++) {
				auxArcade = (Arcade*) ll_get(pArrayListArcade, i);

				if (auxArcade != NULL) {
					if (Arcade_getParametros(auxArcade, &id, &playroomId,
							&gameId, nationality, &soundType, &players,
							&maxCoins) == 0) {
						Arcade_readSoundTypeArcade(&auxArcade->soundType,
								soundTypeText);
						fprintf(pFile, "%d,%d,%d,%s,%s,%d,%d\n", id, playroomId,
								gameId, nationality, soundTypeText, players,
								maxCoins);
						r = 0;
					} else {
						r = -3;
						puts("No se han podido guardar los datos.\n");
					}
				} else {
					r = -2;
					puts("No se han podido guardar los datos.\n");
				}
			}
			fclose(pFile);

		}
	}

	return r;
}

