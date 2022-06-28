/*
 * InputPlayroom.c
 *
 *  Created on: 11 jun 2022
 *      Author: gonza
 */

#include "InputPlayroom.h"

/** \brief Toma los datos de un salon. (Retorna 0 si salio bien -1 si salio mal)
 *
 * \param path Playroom aux*
 * \return int
 *
 */

int Playroom_LoadPlayroom(Playroom *auxiliar) {
	int r = -1;

	if (utn_getString(auxiliar->name, MAX_CHARS_NAME, "Nombre de salon:\n",
			"Error, vuelva a intentar.\n", 3) == 0) {
		if (general_getAlphanumeric(auxiliar->address, MAX_CHARS_ADDRESS,
				"Direccion y altura del salon:\n",
				"Error, vuelva a intentar.\n", 3) == 0) {
			if (utn_getNumero("Tipo de salon: (1-Shopping/2-Local)\n",
					"Error, vuelva a intentar.\n", 0, 3, &auxiliar->type)
					== 0) {
				r = 0;
			}
		}

	}

	return r;
}

/** \brief Toma el nombre de un salon. (Retorna 0 si salio bien -1 si salio mal)
 *
 * \param char playroomName*
 * \return int (0 si salio bien -1 si salio mal)
 *
 */

int Playroom_AskForPlayroomName(char *playroomName) {
	int r = -1;
	if (utn_getString(playroomName, 50, "Nombre del salon:\n",
			"Ha habido un error, vuelva a intentar\n", 3) == 0) {
		r = 0;
	}
	return r;
}

/** \brief Toma el ID de un salon. (Retorna 0 si salio bien -1 si salio mal)
 *
 * \param char playroomName*
 * \return int (0 si salio bien -1 si salio mal)
 *
 */

int Playroom_AskForPlayroomID(int *id) {
	int r = -1;
	if (utn_getNumero("ID del salon:\n",
			"Ha habido un error, vuelva a intentar\n", 1, 3, id) == 0) {
		r = 0;
	}
	return r;
}

