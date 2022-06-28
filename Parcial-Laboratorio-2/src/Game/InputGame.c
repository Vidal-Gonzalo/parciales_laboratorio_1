/*
 * InputGame.c
 *
 *  Created on: 25 jun 2022
 *      Author: gonza
 */

#ifndef GAME_INPUTGAME_C_
#define GAME_INPUTGAME_C_

#include "InputGame.h"

/** \brief Toma los datos de un juego. (Retorna 0 si salio bien -1 si salio mal)
 *
 * \param path Game aux*
 * \return int
 *
 */

int Game_LoadGame(Game *auxiliar) {
	int r = -1;

	if (utn_getString(auxiliar->name, MAX_CHARS_NAME, "Nombre del juego:\n",
			"Error, vuelva a intentar.\n", 3) == 0) {
		if (utn_getString(auxiliar->company, MAX_CHARS_COMPANY,
				"Compañia del juego:\n", "Error, vuelva a intentar.\n", 3)
				== 0) {
			if (utn_getNumero(
					"Genero:(1-Plataforma/2-Aventura/3-Laberinto/4-Otro)\n",
					"Error, vuelva a intentar.\n", 0, 3, &auxiliar->genre)
					== 0) {
				r = 0;
			}
		}
	}

	return r;
}

int Game_AskForGameGenre(int *genre) {
	int r = -1;
	if (utn_getNumero(
			"Filtrar por genero: (1-Plataforma/2-Aventura/3-Laberinto/4-Otro)\n",
			"Ha habido un error, vuelva a intentar\n", 1, 3, genre) == 0) {
		r = 0;
	}
	return r;
}

#endif /* GAME_INPUTGAME_C_ */
