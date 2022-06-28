/*
 * Arcade.c
 *
 *  Created on: 24 jun 2022
 *      Author: gonza
 */

#include "Arcade.h"
#include "../General.h"


/** \brief Verifica si el array de caracteres es valido para ser nacionalidad
 *
 * \param char newArray*
 * \param int size*
 * \return int Retorna (1) si el array es NULL o size es menor a 0 y (0) si se hizo la validacion
 *
 */
static int isNationalityArcade(char newArray[], int size) {
	int i = 0;
	int r = 1;

	if (newArray != NULL && size > 0) {
		for (i = 0; newArray[i] != '\0' && i < size; i++) {
			if ((newArray[i] > 'A' || newArray[i] < 'Z')
					&& (newArray[i] > 'a' || newArray[i] < 'z')
					&& newArray[i] != ' ') {
				r = 0;
				break;
			}
		}
	}
	return r;
}

/** \brief Retorna un espacio de memoria para un Arcade
 *
 * \return Arcade*
 *
 */

Arcade* Arcade_new() {
	return (Arcade*) malloc(sizeof(Arcade));
}

/** \brief Setea los datos de un nuevo arcade recibiendo chars como argumentos
 *
 * \param char *id
 * \param char *playroomId
 * \param char *gameId
 * \param char *nationality
 * \param char *soundType
 * \param char *players
 * \param char *maxCoins
 * \return Arcade*
 *
 */

Arcade* Arcade_newParametrosTxt(char *id, char *playroomId, char *gameId,
		char *nationality, char *soundType, char *players, char *maxCoins) {
	Arcade *aux = Arcade_new();
	int isValid = 0;
	if (aux != NULL) {
		//Validaciones
		if (Arcade_setIdTxt(aux, id) == 0) {
			if (Arcade_setPlayroomIdTxt(aux, playroomId) == 0) {
				if (Arcade_setGameIdTxt(aux, gameId) == 0) {
					if (Arcade_setNationality(aux, nationality) == 0) {
						if (Arcade_setSoundTypeTxt(aux, soundType) == 0) {
							if (Arcade_setPlayersTxt(aux, players) == 0) {
								if (Arcade_setMaxCoinsTxt(aux, maxCoins) == 0) {
									isValid = 1;
								}
							}
						}
					}
				}
			}
		}
		if (isValid == 0) {
			printf("no es valido");
			free(aux);
		}
	}
	return aux;
}

/** \brief Setea los datos de un nuevo arcade
 *
 * \param int *id
 * \param char *playroomId
 * \param char *gameId
 * \param float *nationality
 * \param char *soundType
 * \param int *players
 * \param int *maxCoins
 * \return Arcade*
 *
 */

Arcade* Arcade_newParametros(int *id, int *playroomId, int *gameId,
		char *nationality, int *soundType, int *players, int *maxCoins) {
	Arcade *aux = Arcade_new();
	int isValid = 0;
	if (aux != NULL) {
		//Validaciones
		if (Arcade_setId(aux, *id) == 0) {
			if (Arcade_setPlayroomId(aux, *playroomId) == 0) {
				if (Arcade_setGameId(aux, *gameId) == 0) {
					if (Arcade_setNationality(aux, nationality) == 0) {
						if (Arcade_setSoundType(aux, *soundType) == 0) {
							if (Arcade_setPlayers(aux, *players) == 0) {
								if (Arcade_setMaxCoins(aux, *maxCoins) == 0) {
									isValid = 1;
								}
							}
						}
					}
				}
			}
		}
		if (isValid == 0) {
			printf("no es valido");
			free(aux);
		}
	}
	return aux;
}

/** \brief Recibe los datos de un nuevo arcade
 *
 *\param Arcade *arcade
 * \param int *id
 * \param char *playroomId
 * \param char *gameId
 * \param float *nationality
 * \param char *soundType
 * \param int *players
 * \param int *maxCoins
 * \return Arcade*
 *
 */

int Arcade_getParametros(Arcade *arcade, int *id, int *playroomId,
		int *gameId, char *nationality, int *soundType, int *players,
		int *maxCoins) {
	int r = -1;
	if (arcade != NULL && id > 0 && playroomId > 0 && gameId > 0 && nationality != NULL
			&& soundType > 0 && players > 0 && maxCoins > 0) {
		if (Arcade_getId(arcade, id) == 0) {
			if (Arcade_getPlayroomId(arcade, playroomId) == 0) {
				if (Arcade_getGameId(arcade, gameId) == 0) {
					if (Arcade_getNationality(arcade, nationality) == 0) {
						if (Arcade_getSoundType(arcade, soundType) == 0) {
							if (Arcade_getPlayers(arcade, players) == 0) {
								if (Arcade_getMaxCoins(arcade, maxCoins)
										== 0) {
									r = 0;
								}
							}
						}
					}
				}
			}
		}
	}
	return r;
}

/** \brief Libera el espacio de memoria dedicado a un arcade en particular
 *
 * \param Arcade* this
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

void Arcade_delete(Arcade *this) {
	if (this != NULL) {
		free(this);
	}
}

/** \brief Setea el ID(int) al puntero de arcade recibido
 *
 * \param Arcade* this
 * \param int id
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

int Arcade_setId(Arcade *this, int id) {
	int r = -1;
	if (this != NULL && id >= 0) {
		r = 0;
		this->id = id;
	}
	return r;
}

/** \brief Setea el ID(char) al puntero de arcade recibido
 *
 * \param Arcade* this
 * \param char id
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

int Arcade_setIdTxt(Arcade *this, char *id) {
	int r = -1;
	if (this != NULL && id != NULL) {
		if (isNumber(id) == 0) {
			r = 0;
			this->id = atoi(id);
		} else {
			printf("Setid TXT: %s", id);
		}
	}
	return r;
}

/** \brief Recibe el ID(int) del puntero de arcade recibido
 *
 * \param Arcade* this
 * \param int id
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

int Arcade_getId(Arcade *this, int *id) {
	int r = -1;
	if (this != NULL && id != NULL) {
		r = 0;
		*id = this->id;
	}
	return r;
}

/** \brief Recibe el ID(char) del puntero de arcade recibido
 *
 * \param Arcade* this
 * \param char id
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

int Arcade_getIdTxt(Arcade *this, char *id) {
	int r = -1;
	if (this != NULL && id != NULL) {
		r = 0;
		sprintf(id, "%d", this->id);
	}
	return r;
}

/** \brief Recibe el ID(char) del puntero de arcade recibido
 *
 * \param Arcade* this
 * \param char id
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

int Arcade_setPlayroomId(Arcade *this, int playroomId) {
	int r = -1;
	if (this != NULL && playroomId >= 0) {
		r = 0;
		this->playroomId = playroomId;
	}
	return r;
}

/** \brief Setea el ID(int) al puntero de arcade recibido
 *
 * \param Arcade* this
 * \param int id
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

int Arcade_setPlayroomIdTxt(Arcade *this, char *playroomId) {
	int r = -1;
	if (this != NULL && playroomId != NULL) {
		if (isNumber(playroomId) == 0) {
			r = 0;
			this->playroomId = atoi(playroomId);
		} else {
			printf("Setid TXT: %s", playroomId);
		}
	}
	return r;
}

/** \brief Recibe el ID(char) del puntero de arcade recibido
 *
 * \param Arcade* this
 * \param char id
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

int Arcade_getPlayroomId(Arcade *this, int *playroomId) {
	int r = -1;
	if (this != NULL && playroomId != NULL) {
		r = 0;
		*playroomId = this->playroomId;
	}
	return r;
}

/** \brief Recibe el ID(char) del puntero de arcade recibido
 *
 * \param Arcade* this
 * \param char id
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

int Arcade_getPlayroomIdTxt(Arcade *this, char *playroomId) {
	int r = -1;
	if (this != NULL && playroomId != NULL) {
		r = 0;
		sprintf(playroomId, "%d", this->playroomId);
	}
	return r;
}

/** \brief Recibe el ID(char) del puntero de arcade recibido
 *
 * \param Arcade* this
 * \param char id
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

int Arcade_setGameId(Arcade *this, int gameId) {
	int r = -1;
	if (this != NULL && gameId >= 0) {
		r = 0;
		this->gameId = gameId;
	}
	return r;
}

/** \brief Recibe el ID(char) del puntero de arcade recibido
 *
 * \param Arcade* this
 * \param char id
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

int Arcade_setGameIdTxt(Arcade *this, char *gameId) {
	int r = -1;
	if (this != NULL && gameId != NULL) {
		if (isNumber(gameId) == 0) {
			r = 0;
			this->gameId = atoi(gameId);
		} else {
			printf("Setid TXT: %s", gameId);
		}
	}
	return r;
}

/** \brief Recibe el ID(char) del puntero de arcade recibido
 *
 * \param Arcade* this
 * \param char id
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

int Arcade_getGameId(Arcade *this, int *gameId) {
	int r = -1;
	if (this != NULL && gameId != NULL) {
		r = 0;
		*gameId = this->gameId;
	}
	return r;
}


/** \brief Recibe el ID(char) del puntero de arcade recibido
 *
 * \param Arcade* this
 * \param char id
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

int Arcade_getGameIdTxt(Arcade *this, char *gameId) {
	int r = -1;
	if (this != NULL && gameId != NULL) {
		r = 0;
		sprintf(gameId, "%d", this->gameId);
	}
	return r;
}

/** \brief Recibe el ID(char) del puntero de arcade recibido
 *
 * \param Arcade* this
 * \param char id
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

int Arcade_setNationality(Arcade *this, char *nationality) {
	int r = -1;
	if (this != NULL && nationality != NULL) {
		if (isNationalityArcade(nationality, MAX_CHARS_NATIONALITY) == 0) {
			r = 0;
			strncpy(this->nationality, nationality, MAX_CHARS_NATIONALITY);
		}
	}
	return r;
}

/** \brief Recibe el ID(char) del puntero de arcade recibido
 *
 * \param Arcade* this
 * \param char id
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

int Arcade_getNationality(Arcade *this, char *nationality) {
	int r = -1;
	if (this != NULL && nationality != NULL) {
		r = 0;
		strncpy(nationality, this->nationality, MAX_CHARS_NATIONALITY);
	}
	return r;
}

/** \brief Recibe el ID(char) del puntero de arcade recibido
 *
 * \param Arcade* this
 * \param char id
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

//Sound type
int Arcade_setSoundType(Arcade *this, int soundType) {
	int r = -1;
	if (this != NULL && soundType >= 0) {
		r = 0;
		this->soundType = soundType;
	}
	return r;
}

/** \brief Recibe el ID(char) del puntero de arcade recibido
 *
 * \param Arcade* this
 * \param char id
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

int Arcade_setSoundTypeTxt(Arcade *this, char *soundType) {
	int r = -1;
	if (this != NULL && soundType != NULL) {
		if (Arcade_verifySoundTypeTxt(soundType, &this->soundType) == 0) {
			r = 0;
		}
	}
	return r;
}

/** \brief Recibe el ID(char) del puntero de arcade recibido
 *
 * \param Arcade* this
 * \param char id
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

int Arcade_getSoundType(Arcade *this, int *soundType) {
	int r = -1;
	if (this != NULL && soundType != NULL) {
		r = 0;
		*soundType = this->soundType;
	}
	return r;
}

/** \brief Recibe el ID(char) del puntero de arcade recibido
 *
 * \param Arcade* this
 * \param char id
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

int Arcade_getSoundTypeTxt(Arcade *this, char *soundType) {
	int r = -1;
	if (this != NULL && soundType != NULL) {
		r = 0;
		sprintf(soundType, "%d", this->soundType);
	}
	return r;
}

/** \brief Recibe el ID(char) del puntero de arcade recibido
 *
 * \param Arcade* this
 * \param char id
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

//Players
int Arcade_setPlayers(Arcade *this, int players) {
	int r = -1;
	if (this != NULL && players > 0) {
		r = 0;
		this->players = players;
	}
	return r;
}

/** \brief Recibe el ID(char) del puntero de arcade recibido
 *
 * \param Arcade* this
 * \param char id
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

int Arcade_setPlayersTxt(Arcade *this, char *players) {
	int r = -1;
	if (this != NULL && players != NULL) {
		if (isNumber(players) == 0) {
			r = 0;
			this->players = atoi(players);
		} else {
			printf("Setid TXT: %s", players);
		}
	}
	return r;
}

/** \brief Recibe el ID(char) del puntero de arcade recibido
 *
 * \param Arcade* this
 * \param char id
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

int Arcade_getPlayers(Arcade *this, int *players) {
	int r = -1;
	if (this != NULL && players != NULL) {
		r = 0;
		*players = this->players;
	}
	return r;
}

/** \brief Recibe el ID(char) del puntero de arcade recibido
 *
 * \param Arcade* this
 * \param char id
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

int Arcade_getPlayersTxt(Arcade *this, char *players) {
	int r = -1;
	if (this != NULL && players != NULL) {
		r = 0;
		sprintf(players, "%d", this->players);
	}
	return r;
}

/** \brief Recibe el ID(char) del puntero de arcade recibido
 *
 * \param Arcade* this
 * \param char id
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

//Max coins
int Arcade_setMaxCoins(Arcade *this, int maxCoins) {
	int r = -1;
	if (this != NULL && maxCoins >= 0) {
		r = 0;
		this->maxCoins = maxCoins;
	}
	return r;
}

/** \brief Recibe el ID(char) del puntero de arcade recibido
 *
 * \param Arcade* this
 * \param char id
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

int Arcade_setMaxCoinsTxt(Arcade *this, char *maxCoins) {
	int r = -1;
	if (this != NULL && maxCoins != NULL) {
		if (isNumber(maxCoins) == 0) {
			r = 0;
			this->maxCoins = atoi(maxCoins);
		} else {
			printf("Setid TXT: %s", maxCoins);
		}
	}
	return r;
}

/** \brief Recibe el ID(char) del puntero de arcade recibido
 *
 * \param Arcade* this
 * \param char id
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

int Arcade_getMaxCoins(Arcade *this, int *maxCoins) {
	int r = -1;
	if (this != NULL && maxCoins != NULL) {
		r = 0;
		*maxCoins = this->maxCoins;
	}
	return r;
}

/** \brief Recibe el ID(char) del puntero de arcade recibido
 *
 * \param Arcade* this
 * \param char id
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

int Arcade_getMaxCoinsTxt(Arcade *this, char *soundType) {
	int r = -1;
	if (this != NULL && soundType != NULL) {
		r = 0;
		sprintf(soundType, "%d", this->soundType);
	}
	return r;
}

/** \brief Recibe el ID(char) del puntero de arcade recibido
 *
 * \param Arcade* this
 * \param char id
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

int Arcade_readSoundTypeArcade(int *soundType, char *soundTypeTxt) {
	int r = -1;
	if (soundType > 0 && soundTypeTxt != NULL) {
		if (*soundType == STEREO) {
			strncpy(soundTypeTxt, "Estereo", 50);
		} else {
			strncpy(soundTypeTxt, "Mono", 50);
		}
		r = 0;
	}
	return r;
}

/** \brief Recibe el ID(char) del puntero de arcade recibido
 *
 * \param Arcade* this
 * \param char id
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

int Arcade_verifySoundTypeTxt(char *soundTypeTxt, int *soundTypeVerified) {
	int r = -1;
	if (soundTypeTxt != NULL) {
		if (strcmp(soundTypeTxt, "Estereo") == 0) {
			*soundTypeVerified = STEREO;
		} else {
			if (strcmp(soundTypeTxt, "Mono") == 0) {
				*soundTypeVerified = MONO;
			}
		}
		r = 0;
	}
	return r;
}

/** \brief print the content of *p
 *
 * \param Arcade *p
 * \return void
 *
 */

void Arcade_printOne(Arcade *p) {
	char soundTypeTxt[50];

	Arcade_readSoundTypeArcade(&p->soundType, soundTypeTxt);
	printf(
			"ID: %d\nID del salon: %d\nNacionalidad: %s\nTipo de sonido: %s\nCantidad de jugadores: %d\nCapacidad maxima de monedas: %d\nID de juego: %d\n",
			p->id, p->playroomId, p->nationality, soundTypeTxt, p->players,
			p->maxCoins, p->gameId);
}

/** \brief Retorna un ID unico
 *

 * \return id
 *
 */

int Arcade_getUniqueId() {
	FILE *pFile;
	int id = 1;

	pFile = fopen("maxIdArcade", "r");
	if (pFile != NULL) {
		if (fscanf(pFile, "%d", &id) == 1) {
			id++;
		}
		fclose(pFile);
		pFile = fopen("maxIdArcade", "w");
		if (pFile != NULL) {
			fprintf(pFile, "%d", id);
			fclose(pFile);
		}
	} else {
		pFile = fopen("maxIdArcade", "w");
		if (pFile != NULL) {
			fprintf(pFile, "%d", id);
			fclose(pFile);
		}
	}

	return id;
}



int Arcade_CheckForBiggerId(void *pArcade1, void *pArcade2) {
	if (((Arcade*) pArcade1)->id > ((Arcade*)pArcade2)->id) {
		return 1;
	}
	if (((Arcade*) pArcade1)->id < ((Arcade*)pArcade2)->id) {
		return -1;
	}
	return 0;
}

