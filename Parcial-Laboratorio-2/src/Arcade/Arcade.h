/*
 * Arcade.h
 *
 *  Created on: 24 jun 2022
 *      Author: gonza
 */

#ifndef ARCADE_H_
#define ARCADE_H_

#define MAX_CHARS_NATIONALITY 50
#define MONO 1
#define STEREO 2

typedef struct {
	int id;
	int playroomId;
	int gameId; //Poner solo el ID o una struct completa de juego?
	char nationality[MAX_CHARS_NATIONALITY];
	int soundType;
	int players;
	int maxCoins;
} Arcade;

/** \brief Retorna un espacio de memoria para un Arcade
 *
 * \return Arcade*
 *
 */

Arcade* Arcade_new();

/** \brief Setea los datos de un nuevo pasajero recibiendo chars como argumentos
 *
 * \param char *id
 * \param char *name
 * \param char *address
 * \param char *type
 * \return Arcade*
 *
 */

Arcade* Arcade_newParametrosTxt(char *id, char *playroomId, char *gameId,
		char *nationality, char *soundType, char *players, char *maxCoins);

/** \brief Setea los datos de un nuevo pasajero
 *
 * \param int *id
 * \param char *name
 * \param char *address
 * \param float *precio
 * \param char *codigoVuelo
 * \param int *tipoPasajero
 * \param int *statusFlight
 * \return Arcade*
 *
 */

Arcade* Arcade_newParametros(int *id, int *playroomId, int *gameId,
		char *nationality, int *soundType, int *players, int *maxCoins);

int Arcade_getParametros(Arcade *arcade, int *id, int *playroomId, int *gameId,
		char *nationality, int *soundType, int *players, int *maxCoins);

/** \brief Libera el espacio de memoria dedicado a un pasajero en particular
 *
 * \param Arcade* this
 * \return int (-1 si salio mal 0 si salio bien)
 *
 */

void Arcade_delete(Arcade *this);

//Arcade ID
int Arcade_setId(Arcade *this, int id);
int Arcade_setIdTxt(Arcade *this, char *id);

int Arcade_getId(Arcade *this, int *id);
int Arcade_getIdTxt(Arcade *this, char *id);

//Playroom ID
int Arcade_setPlayroomId(Arcade *this, int playroomId);
int Arcade_setPlayroomIdTxt(Arcade *this, char *playroomId);

int Arcade_getPlayroomId(Arcade *this, int *playroomId);
int Arcade_getPlayroomIdTxt(Arcade *this, char *playroomId);

//Game ID
int Arcade_setGameId(Arcade *this, int gameId);
int Arcade_setGameIdTxt(Arcade *this, char *gameId);

int Arcade_getGameId(Arcade *this, int *gameId);
int Arcade_getGameIdTxt(Arcade *this, char *gameId);

//Nationality
int Arcade_setNationality(Arcade *this, char *nationality);
int Arcade_getNationality(Arcade *this, char *nationality);

//Players
int Arcade_setPlayers(Arcade *this, int players);
int Arcade_setPlayersTxt(Arcade *this, char *players);

int Arcade_getPlayers(Arcade *this, int *players);
int Arcade_getPlayersTxt(Arcade *this, char *players);

//Max coins
int Arcade_setMaxCoins(Arcade *this, int maxCoins);
int Arcade_setMaxCoinsTxt(Arcade *this, char *maxCoins);

int Arcade_getMaxCoins(Arcade *this, int *maxCoins);
int Arcade_getMaxCoinsTxt(Arcade *this, char *maxCoins);

//Sound type
int Arcade_setSoundType(Arcade *this, int soundType);
int Arcade_setSoundTypeTxt(Arcade *this, char *soundType);

int Arcade_getSoundType(Arcade *this, int *soundType);
int Arcade_getSoundTypeTxt(Arcade *this, char *soundType);

int Arcade_readSoundTypeArcade(int *soundType, char *soundTypeTxt);
int Arcade_verifySoundTypeTxt(char *soundTypeTxt, int *soundTypeVerified);

//Unique arcade ID
int Arcade_getUniqueId();

//Print Arcade's data
void Arcade_printOne(Arcade *p);

int Arcade_CheckForBiggerId(void *pArcade1, void *pArcade2);

#endif /* ARCADE_H_ */
