/*
 * Game.c
 *
 *  Created on: 24 jun 2022
 *      Author: gonza
 */
#include "Game.h"

static int isNameGame(char newArray[], int size) {
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


/** \brief Retorna un espacio de memoria para un Game
 *
 * \return Game*
 *
 */

Game* Game_new() {
	return (Game*) malloc(sizeof(Game));
}

/** \brief Setea los datos de un nuevo Game recibiendo chars como argumentos
 *
 * \param char *id
 * \param char *name
 * \param char *address
 * \param char *type
 * \return Game*
 *
 */

Game* Game_newParametrosTxt(char *id, char *name, char *company, char *genre) {
	Game *aux = Game_new();
	int isValid = 0;
	if (aux != NULL) {
		//Validaciones
		if (Game_setIdTxt(aux, id) == 0) {
			if (Game_setName(aux, name) == 0) {
				if (Game_setCompany(aux, company) == 0) {
					if (Game_setGenreTxt(aux, genre) == 0) {
						isValid = 1;
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

/** \brief Setea los datos de un nuevo Game
 *
 * \param int *id
 * \param char *name
 * \param char *address
 * \param float *precio
 * \param char *codigoVuelo
 * \param int *tipoGame
 * \param int *statusFlight
 * \return Game*
 *
 */

Game* Game_newParametros(int *id, char *name, char *company, int *genre) {
	Game *aux = Game_new();
	int isValid = 0;
	if (aux != NULL) {
		//Validaciones
		if (Game_setId(aux, *id) == 0) {
			if (Game_setName(aux, name) == 0) {
				if (Game_setCompany(aux, company) == 0) {
					if (Game_setGenre(aux, *genre) == 0) {
						isValid = 1;
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

int Game_getParametros(Game *game, int *id, char *name, char *company,
		int *genre) {
	int r = -1;
	if (game != NULL && id > 0 && name != NULL && company != NULL
			&& genre > 0) {
		if (Game_getId(game, id) == 0) {
			if (Game_getName(game, name) == 0) {
				if (Game_getCompany(game, company) == 0) {
					if (Game_getGenre(game, genre) == 0) {
						r = 0;
					}
				}
			}
		}
	}
	return r;
}

/** \brief Libera el espacio de memoria dedicado a un Game en particular
 *
 * \param Game* this
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

void Game_delete(Game *this) {
	if (this != NULL) {
		free(this);
	}
}

int Game_setId(Game *this, int id) {
	int r = -1;
	if (this != NULL && id >= 0) {
		r = 0;
		this->id = id;
	}
	return r;
}

int Game_setIdTxt(Game *this, char *id) {
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

int Game_getId(Game *this, int *id) {
	int r = -1;
	if (this != NULL && id != NULL) {
		r = 0;
		*id = this->id;
	}
	return r;
}

int Game_getIdTxt(Game *this, char *id) {
	int r = -1;
	if (this != NULL && id != NULL) {
		r = 0;
		sprintf(id, "%d", this->id);
	}
	return r;
}

int Game_setName(Game *this, char *name) {
	int r = -1;
	if (this != NULL && name != NULL) {
		if (isNameGame(name, MAX_CHARS_NAME) == 0) {
			r = 0;
			strncpy(this->name, name, MAX_CHARS_NAME);
		}
	}
	return r;
}

int Game_getName(Game *this, char *name) {
	int r = -1;
	if (this != NULL && name != NULL) {
		r = 0;
		strncpy(name, this->name, MAX_CHARS_NAME);
	}
	return r;
}

int Game_setCompany(Game *this, char *company) {
	int r = -1;
	if (this != NULL && company != NULL) {
		if (isNameGame(company, MAX_CHARS_COMPANY) == 0) {
			r = 0;
			strncpy(this->company, company, MAX_CHARS_COMPANY);
		}
	}
	return r;
}

int Game_getCompany(Game *this, char *company) {
	int r = -1;
	if (this != NULL && company != NULL) {
		r = 0;
		strncpy(company, this->company, MAX_CHARS_COMPANY);
	}
	return r;
}

int Game_setGenre(Game *this, int genre) {
	int r = -1;
	if (this != NULL && genre > 0) {
		r = 0;
		this->genre = genre;
	}
	return r;
}

int Game_setGenreTxt(Game *this, char *genre) {
	int r = -1;
	if (this != NULL && genre != NULL) {
		if (Game_verifyGenreTxt(genre, &this->genre) == 0) {
			r = 0;
		}
	}
	return r;
}

int Game_getGenre(Game *this, int *genre) {
	int r = -1;
	if (this != NULL && genre > 0) {
		r = 0;
		*genre = this->genre;
	}
	return r;
}

int Game_getGenreTxt(Game *this, char *genre) {
	int r = -1;
	if (this != NULL && genre != NULL) {
		r = 0;
		sprintf(genre, "%d", this->genre);
	}
	return r;
}

void Game_printOne(Game *p) {
	char genreGameTxt[MAX_CHARS_GENRE];
	Game_readGenreGame(&p->genre, genreGameTxt);
	printf("ID %d\nNombre: %s\nCompañia: %s\nGenero: %s\n", p->id, p->name,
			p->company, genreGameTxt);
}

int Game_getUniqueId() {
	FILE *pFile;
	int id = 1;

	pFile = fopen("maxIdGame", "r");
	if (pFile != NULL) {
		if (fscanf(pFile, "%d", &id) == 1) {
			id++;
		}
		fclose(pFile);
		pFile = fopen("maxIdGame", "w");
		if (pFile != NULL) {
			fprintf(pFile, "%d", id);
			fclose(pFile);
		}
	} else {
		pFile = fopen("maxIdGame", "w");
		if (pFile != NULL) {
			fprintf(pFile, "%d", id);
			fclose(pFile);
		}
	}

	return id;
}

/** \brief print the content of Games array
 *
 * \param LinkedList Game*
 * \param length int
 * \return int
 *
 */

int Game_readGenreGame(int *genre, char *genreTxt) {
	int r = -1;
	if (genre > 0 && genreTxt != NULL) {
		switch (*genre) {
		case PLATFORM:
			strncpy(genreTxt, "Plataforma", 50);
			break;
		case ADVENTURE:
			strncpy(genreTxt, "Aventura", 50);
			break;
		case LABYRINTH:
			strncpy(genreTxt, "Laberinto", 50);
			break;
		case OTHER:
			strncpy(genreTxt, "Otro", 50);
			break;
		default:
			strncpy(genreTxt, "Otro", 50);
			break;
		}
		r = 0;
	}
	return r;
}

int Game_verifyGenreTxt(char *genreTxt, int *genreVerified) {
	int r = -1;
	if (genreTxt != NULL) {
		if (strcmp(genreTxt, "Plataforma") == 0) {
			*genreVerified = PLATFORM;
		} else {
			if (strcmp(genreTxt, "Aventura") == 0) {
				*genreVerified = ADVENTURE;
			} else {
				if (strcmp(genreTxt, "Laberinto") == 0) {
					*genreVerified = LABYRINTH;
				} else {
					if (strcmp(genreTxt, "Otro") == 0) {
						*genreVerified = OTHER;
					}
				}
			}
		}
		r = 0;
	}
	return r;
}


int Game_CheckForBiggerName(void *pGame1, void *pGame2) {
	if (strcmp(((Game*) pGame1)->name, ((Game*) pGame2)->name) > 0) {
		return 1;
	}
	if (strcmp(((Game*) pGame1)->name, ((Game*) pGame2)->name) < 0) {
		return -1;
	}
	return 0;
}
