/*
 * Playroom.c
 *
 *  Created on: 24 jun 2022
 *      Author: gonza
 */

#include "Playroom.h"
#include "../General.h"

static int isNamePlayroom(char newArray[], int size) {
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

/** \brief Retorna un espacio de memoria para un Playroom
 *
 * \return Playroom*
 *
 */

Playroom* Playroom_new() {
	return (Playroom*) malloc(sizeof(Playroom));
}

/** \brief Setea los datos de un nuevo playroom recibiendo chars como argumentos
 *
 * \param char *id
 * \param char *name
 * \param char *address
 * \param char *type
 * \return Playroom*
 *
 */

Playroom* Playroom_newParametrosTxt(char *id, char *name, char *address,
		char *type) {
	Playroom *aux = Playroom_new();
	int isValid = 0;
	if (aux != NULL) {
		//Validaciones
		if (Playroom_setIdTxt(aux, id) == 0) {
			if (Playroom_setName(aux, name) == 0) {
				if (Playroom_setAddress(aux, address) == 0) {
					if (Playroom_setTypeTxt(aux, type) == 0) {
						isValid = 1;
					} else {
						printf("Error precio: %s", type);
					}
				} else {
					printf("Error address: %s", address);
				}
			} else {
				printf("Error name: %s", name);
			}
		} else {
			printf("Error id: %s", id);
		}
		if (isValid == 0) {
			printf("no es valido");
			free(aux);
		}
	}
	return aux;
}

/** \brief Setea los datos de un nuevo playroom
 *
 * \param int *id
 * \param char *name
 * \param char *address
 * \param float *precio
 * \param char *codigoVuelo
 * \param int *tipoplayroom
 * \param int *statusFlight
 * \return Playroom*
 *
 */

Playroom* Playroom_newParametros(int *id, char *name, char *address, int *type) {
	Playroom *aux = Playroom_new();
	int isValid = 0;
	if (aux != NULL) {
		//Validaciones
		if (Playroom_setId(aux, *id) == 0) {
			if (Playroom_setName(aux, name) == 0) {
				if (Playroom_setAddress(aux, address) == 0) {
					if (Playroom_setType(aux, *type) == 0) {
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

int Playroom_getParametros(Playroom *playroom, int *id, char *name,
		char *address, int *type) {
	int r = -1;
	if (playroom != NULL && id > 0 && name != NULL && address != NULL
			&& type > 0) {
		if (Playroom_getId(playroom, id) == 0) {
			if (Playroom_getName(playroom, name) == 0) {
				if (Playroom_getAddress(playroom, address) == 0) {
					if (Playroom_getType(playroom, type) == 0) {
						r = 0;
					}
				}
			}
		}
	}
	return r;
}

/** \brief Libera el espacio de memoria dedicado a un playroom en particular
 *
 * \param Playroom* this
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

void Playroom_delete(Playroom *this) {
	if (this != NULL) {
		free(this);
	}
}

int Playroom_setId(Playroom *this, int id) {
	int r = -1;
	if (this != NULL && id >= 0) {
		r = 0;
		this->id = id;
	}
	return r;
}

int Playroom_setIdTxt(Playroom *this, char *id) {
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

int Playroom_getId(Playroom *this, int *id) {
	int r = -1;
	if (this != NULL && id != NULL) {
		r = 0;
		*id = this->id;
	}
	return r;
}

int Playroom_getIdTxt(Playroom *this, char *id) {
	int r = -1;
	if (this != NULL && id != NULL) {
		r = 0;
		sprintf(id, "%d", this->id);
	}
	return r;
}

int Playroom_setName(Playroom *this, char *name) {
	int r = -1;
	if (this != NULL && name != NULL) {
		if (isNamePlayroom(name, MAX_CHARS_NAME) == 0) {
			r = 0;
			strncpy(this->name, name, MAX_CHARS_NAME);
		}
	}
	return r;
}

int Playroom_getName(Playroom *this, char *name) {
	int r = -1;
	if (this != NULL && name != NULL) {
		r = 0;
		strncpy(name, this->name, MAX_CHARS_NAME);
	}
	return r;
}

int Playroom_setAddress(Playroom *this, char *address) {
	int r = -1;
	if (this != NULL && address != NULL) {
		if (isNamePlayroom(address, MAX_CHARS_ADDRESS) == 0) {
			r = 0;
			strncpy(this->address, address, MAX_CHARS_ADDRESS);
		}
	}
	return r;
}
int Playroom_getAddress(Playroom *this, char *address) {
	int r = -1;
	if (this != NULL && address != NULL) {
		r = 0;
		strncpy(address, this->address, MAX_CHARS_ADDRESS);
	}
	return r;
}

int Playroom_setType(Playroom *this, int type) {
	int r = -1;
	if (this != NULL && type > 0) {
		r = 0;
		this->type = type;
	}
	return r;
}

int Playroom_setTypeTxt(Playroom *this, char *type) {
	int r = -1;
	if (this != NULL && type != NULL) {
		if (Playroom_verifyTypeTxt(type, &this->type) == 0) {
			r = 0;
		}
	}
	return r;
}

int Playroom_getType(Playroom *this, int *type) {
	int r = -1;
	if (this != NULL && type != NULL) {
		r = 0;
		*type = this->type;
	}
	return r;
}

int Playroom_getTypeTxt(Playroom *this, char *type) {
	int r = -1;
	if (this != NULL && type != NULL) {
		r = 0;
		sprintf(type, "%d", this->type);
	}
	return r;
}

int Playroom_readTypePlayroom(int *type, char *typeTxt) {
	int r = -1;
	if (type > 0 && typeTxt != NULL) {
		if (*type == 2) {
			strncpy(typeTxt, "Local", 50);
		} else {
			strncpy(typeTxt, "Shopping", 50);
		}
		r = 0;
	}
	return r;
}

int Playroom_verifyTypeTxt(char *typeTxt, int *typeVerified) {
	int r = -1;
	if (typeTxt != NULL) {
		if (strcmp(typeTxt, "Shopping") == 0) {
			*typeVerified = 2;
		} else {
			if (strcmp(typeTxt, "Local") == 0) {
				*typeVerified = 1;
			}
		}
		r = 0;
	}
	return r;
}

void Playroom_printOne(Playroom *p) {
	char typePlayroomTxt[50];

	Playroom_readTypePlayroom(&p->type, typePlayroomTxt);
	printf("ID %d\nNombre: %s\nDireccion: %s\nTipo: %s\n", p->id, p->name,
			p->address, typePlayroomTxt);

}

int Playroom_getUniqueId() {
	FILE *pFile;
	int id = 1;

	pFile = fopen("maxIdPlayroom", "r");
	if (pFile != NULL) {
		if (fscanf(pFile, "%d", &id) == 1) {
			id++;
		}
		fclose(pFile);
		pFile = fopen("maxIdPlayroom", "w");
		if (pFile != NULL) {
			fprintf(pFile, "%d", id);
			fclose(pFile);
		}
	} else {
		pFile = fopen("maxIdPlayroom", "w");
		if (pFile != NULL) {
			fprintf(pFile, "%d", id);
			fclose(pFile);
		}
	}

	return id;
}

/** \brief print the content of Playrooms array
 *
 * \param LinkedList Playroom*
 * \param length int
 * \return int
 *
 */

