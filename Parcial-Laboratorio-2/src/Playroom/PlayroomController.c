/*
 * PlayroomController.c
 *
 *  Created on: 24 jun 2022
 *      Author: gonza
 */
#include "PlayroomController.h"

/** \brief Carga el contenido de *path a la LinkedList recibida
 *
 *	\param char *path
 * \param LinkedList *pArray
 * \return (0) si salio bien (-1) si el path o la linkedList es nula
 *
 */

int PlayroomController_LoadPlayroomsFromText(char *path,
		LinkedList *pArrayListPlayroom) {
	int r = -1;
	FILE *pFile;

	if (path != NULL && pArrayListPlayroom != NULL) {
		if (ll_len(pArrayListPlayroom) > 0) {
			if (confirmation(
					"\nSi carga los datos una vez más, se eliminaran los anteriores\n¿Esta seguro que desea realizar esta accion?(1:Si/Otro numero:No)\n",
					"Ha habido un error\n") == 1) {
				ll_clear(pArrayListPlayroom);
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
			if (parser_PlayroomFromText(pFile, pArrayListPlayroom) == 0) {
				r = 0;
			} else {
				r = -4;
			}
		}
		fclose(pFile);
	}

	return r;
}

int PlayroomController_registerAPlayroom(char *path,
		LinkedList *pArrayListPlayroom) {
	int r = -1;
	Playroom *playroom;
	Playroom auxPlayroom;

	if (path != NULL && pArrayListPlayroom != NULL) {
		if (Playroom_LoadPlayroom(&auxPlayroom) == 0) {
			auxPlayroom.id = Playroom_getUniqueId();
			playroom = Playroom_newParametros(&auxPlayroom.id, auxPlayroom.name,
					auxPlayroom.address, &auxPlayroom.type);
			if (playroom != NULL) {
				puts("Salon añadido: \n");
				Playroom_printOne(playroom);
				ll_add(pArrayListPlayroom, playroom);
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

int PlayroomController_printPlayrooms(LinkedList *pArrayPlayrooms, int size) {
	int r = -1;
	Playroom *playroom;
	char typeText[50];

	if (pArrayPlayrooms != NULL) {
		if (size > 0) {
			printf("%*s | %*s | %*s | %*s\n", -4, "ID", -MAX, "Nombre", -MAX,
					"Direccion", -MAX, "Tipo");
			printf("%*c | %*c | %*c | %*c\n", -4, '-', -MAX, '-', -MAX, '-',
					-MAX, '-');
			for (int i = 0; i < size; i++) {
				playroom = (Playroom*) ll_get(pArrayPlayrooms, i);
				Playroom_readTypePlayroom(&playroom->type, typeText);
				printf("%-4d | %-30s | %-30s | %-30s\n", playroom->id,
						playroom->name, playroom->address, typeText);
				r = 0;

			}
		}
	}

	return r;
}

int PlayroomController_PrintEspecificPlayroom(LinkedList *pArrayPlayrooms,
		int size) {
	int r = -1;
	Playroom *playroom;
	int playroomId;
	char typeText[50];
	int playroomIndex;

	if (pArrayPlayrooms != NULL) {
		if (size > 0) {
			if (Playroom_AskForPlayroomID(&playroomId) == 0) {
				playroomIndex = PlayroomController_SearchPlayroomIndexPerId(
						pArrayPlayrooms, &playroomId);
				if (playroomIndex != -1) {
					printf("%*s | %*s | %*s | %*s\n", -4, "ID", -MAX, "Nombre",
							-MAX, "Direccion", -MAX, "Tipo");
					printf("%*c | %*c | %*c | %*c\n", -4, '-', -MAX, '-', -MAX,
							'-', -MAX, '-');
					playroom = (Playroom*) ll_get(pArrayPlayrooms,
							playroomIndex);
					Playroom_readTypePlayroom(&playroom->type, typeText);
					printf("%-4d | %-30s | %-30s | %-30s\n", playroom->id,
							playroom->name, playroom->address, typeText);
					r = 0;
				} else {
					printf("El salon no existe.\n");
				}

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

int PlayroomController_SearchPlayroomIndexPerId(LinkedList *playroomList,
		int *id) {
	int r = -1;
	Playroom *playroom;
	int playroomListLength = ll_len(playroomList);

	if (playroomList != NULL && id > 0) {
		for (int i = 0; i < playroomListLength; i++) {
			playroom = (Playroom*) ll_get(playroomList, i);
			if (playroom->id == *id) {
				r = i;
				break;
			}
		}
	}
	return r;
}

/** \brief Busca en la LinkedList el nombre recibido y retorna su index
 *
 *	\param LinkedList *pArrayListArcade
 * \param  int *id
 * \return index si salio bien (-1) si la linkedList es nula o el size es menor a 0
 *
 */

int PlayroomController_SearchPlayroomIndexPerName(LinkedList *playroomList,
		char *name) {
	int r = -1;
	Playroom *playroom;
	int playroomListLength = ll_len(playroomList);

	if (playroomList != NULL && name != NULL && playroomListLength > 0) {
		for (int i = 0; i < playroomListLength; i++) {
			playroom = (Playroom*) ll_get(playroomList, i);
			if (strcmp(playroom->name, name) == 0) {
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

int PlayroomController_SavePlayroomAsText(char *path,
		LinkedList *pArrayListPlayroom) {
	int r = -1;
	FILE *pFile = NULL;
	Playroom *auxPlayroom;
	int playroomListLength = ll_len(pArrayListPlayroom);

	int id;
	char name[MAX_CHARS_NAME];
	char address[MAX_CHARS_ADDRESS];
	int type;
	char typeText[MAX_CHARS_NAME];

	if (path != NULL && pArrayListPlayroom != NULL) {
		pFile = fopen(path, "w");
		if (pFile != NULL) {
			r = 0;
			fprintf(pFile, "id, Nombre, Direccion, Tipo de sonido\n");
			for (int i = 0; i < playroomListLength; i++) {
				auxPlayroom = (Playroom*) ll_get(pArrayListPlayroom, i);
				if (auxPlayroom != NULL) {
					if (Playroom_getParametros(auxPlayroom, &id, name, address,
							&type) == 0) {
						Playroom_readTypePlayroom(&auxPlayroom->type, typeText);
						fprintf(pFile, "%d,%s,%s,%s\n", id, name, address,
								typeText);
					}
				}
			}
			fclose(pFile);

		}
	}

	return r;
}
