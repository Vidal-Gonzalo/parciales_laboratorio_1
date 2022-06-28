/*
 * Relationships_ArcadePlayroomAndGames.c
 *
 *  Created on: 25 jun 2022
 *      Author: gonza
 */

#include "Relationships_ArcadePlayroomAndGames.h"

int Relationship_ArcadeInput(LinkedList *pArrayListPlayroom,
		LinkedList *pArrayListArcade, LinkedList *pArrayListGame,
		Arcade *arcadeAux) {
	int r = -1;
	int pArrayListPlayroomLength = ll_len(pArrayListPlayroom);
	int pArrayListGameLength = ll_len(pArrayListGame);

	if (pArrayListPlayroom != NULL && pArrayListArcade != NULL
			&& pArrayListGame != NULL) {
		if (utn_getString(arcadeAux->nationality, MAX_CHARS_NATIONALITY,
				"Nacionalidad del arcade:\n",
				"Ha habido un error, vuelva a intentar.\n", 3) == 0) {
			if (utn_getNumeroWithMax("Tipo de sonido:(1-Mono/2-Estereo)\n",
					"Ha habido un error, vuelva a intentar.\n", 1, 2, 3,
					&arcadeAux->soundType) == 0) {
				if (utn_getNumeroWithMax("Cantidad de jugadores:(1-4)\n",
						"Ha habido un error, vuelva a intentar.\n", 1, 2, 3,
						&arcadeAux->players) == 0) {
					if (utn_getNumero("Cantidad maxima de fichas:\n",
							"Ha habido un error, vuelva a intentar.\n", 1, 3,
							&arcadeAux->maxCoins) == 0) {
						PlayroomController_printPlayrooms(pArrayListPlayroom,
								pArrayListPlayroomLength);
						if (utn_getNumero(
								"¿En que salon desea colocar el arcade?\n",
								"Ha habido un error, vuelva a intentar.\n", 1,
								3, &arcadeAux->playroomId) == 0) {
							if (PlayroomController_SearchPlayroomIndexPerId(
									pArrayListPlayroom, &arcadeAux->playroomId)
									!= -1) {
								GameController_PrintGames(pArrayListGame,
										pArrayListGameLength);
								if (utn_getNumero(
										"¿Que juego desea colocarle al arcade?\n",
										"Ha habido un error, vuelva a intentar.\n",
										1, 3, &arcadeAux->gameId) == 0) {
									if (GameController_SearchGameIndexPerId(
											pArrayListGame, &arcadeAux->gameId)
											!= -1) {
										r = 0;
									} else {
										puts(
												"Ese juego no existe. Vuelva a ingresar los datos por favor\n");
									}
								}
							} else {
								puts(
										"Ese salon no existe. Vuelva a ingresar los datos por favor\n ");
							}
						}
					}
				}
			}
		}
	}
	if (r == -1) {
		free(arcadeAux);
	}
	return r;
}

int Relationship_RegisterAnArcadeInPlayroom(LinkedList *pArrayListPlayroom,
		LinkedList *pArrayListArcade, LinkedList *pArrayListGame) {
	int r = -1;
	Arcade *arcade;
	Arcade auxArcade;
	if (pArrayListArcade != NULL) {
		if (Relationship_ArcadeInput(pArrayListPlayroom, pArrayListArcade,
				pArrayListGame, &auxArcade) == 0) {
			auxArcade.id = Arcade_getUniqueId();
			arcade = Arcade_newParametros(&auxArcade.id, &auxArcade.playroomId,
					&auxArcade.gameId, auxArcade.nationality,
					&auxArcade.soundType, &auxArcade.players,
					&auxArcade.maxCoins);
			if (arcade != NULL) {
				ll_add(pArrayListArcade, arcade);
				puts("Arcade añadido:\n");
				Arcade_printOne(arcade);
				r = 0;
			}
		}
	}
	return r;
}

int Relationship_ModifyArcade(LinkedList *pArrayListArcade,
		LinkedList *pArrayListGame) {
	int r = -1;
	Arcade *arcade = NULL;
	Game *game = NULL;
	int pArrayListArcadeLength = ll_len(pArrayListArcade);
	int pArrayListGameLength = ll_len(pArrayListGame);
	int idArcadeToModify;
	int indexToModify;
	int optionToModify;
	int gameIndex;

	if (pArrayListArcade != NULL && pArrayListGame != NULL) {
		if (ArcadeController_PrintArcades(pArrayListArcade,
				pArrayListArcadeLength) == 0) {
			if (utn_getNumero("ID del arcade a modificar:\n",
					"Ha habido un error, vuelva a intentar.\n", 1, 3,
					&idArcadeToModify) == 0) {
				indexToModify = ArcadeController_SearchArcadeIndexPerId(
						pArrayListArcade, &idArcadeToModify);
				if (indexToModify != -1) {
					arcade = ll_get(pArrayListArcade, indexToModify);
					puts("\nEl arcade que elegiste modificar es:\n");
					Arcade_printOne(arcade);
					if (utn_getNumeroWithMax(
							"\n1-Modificar cantidad de jugadores\n2-Juego que contiene\n3-Salir\n",
							"Ha habido un error, vuelva a intentar\n", 1, 3, 3,
							&optionToModify) == 0) {
						switch (optionToModify) {
						case 1:
							if (utn_getNumeroWithMax(
									"Cantidad de jugadores:(1-4)\n",
									"Ha habido un error, vuelva a intentar.\n",
									1, 4, 3, &arcade->players) == 0) {
								printf(
										"La nueva cantidad de jugadores es: %d\n",
										arcade->players);
								if (confirmation(
										"Esta seguro que desea modificarlo?(1-Si/Otro numero-No)\n",
										"Ha habido un error\n") == 1) {
									ll_set(pArrayListArcade, indexToModify,
											arcade);
									puts(
											"Cantidad de jugadores modificados!\n");
								} else {
									puts(
											"No se han modificado la cantidad de jugadores.\n");
								}
							}
							break;
						case 2:
							GameController_PrintGames(pArrayListGame,
									pArrayListGameLength);
							if (utn_getNumero(
									"Ingrese el ID del nuevo juego para su arcade:\n",
									"Ha habido un error, vuelva a intentar\n",
									1, 3, &arcade->gameId) == 0) {
								gameIndex = GameController_SearchGameIndexPerId(
										pArrayListGame, &arcade->gameId);
								if (gameIndex != -1) {
									game = (Game*) ll_get(pArrayListGame,
											gameIndex);
									puts(
											"El nuevo juego que quiere colocar en su arcade es:\n");
									Game_printOne(game);
									if (confirmation(
											"Esta seguro que desea modificarlo?(1-Si/Otro numero-No)\n",
											"Ha habido un error\n") == 1) {
										ll_set(pArrayListArcade, indexToModify,
												arcade);
										puts("Juego modificado!\n");
									} else {
										puts("El juego no ha sido modificado");
									}
								}
							}
							break;
						case 3:
							puts("No se han realizado modificaciones.\n");
							break;

						}
					}
					r = 0;
				}
			}
		}
	}
	return r;
}

int Relationship_PrintCompletePlayroom(LinkedList *pArrayListPlayroom,
		LinkedList *pArrayListGame, LinkedList *pArrayListArcade,
		int arcadeListSize, int playroomListSize) {
	int r = -1;
	Arcade *arcade = NULL;
	Playroom *playroom = NULL;
	char playroomTypeTxt[50];
	Game *game = NULL;
	int gameIndex;
	int platformGames = 0;
	int labyrinthGames = 0;
	int adventureGames = 0;
	int listPrinted = 0;

	if (pArrayListGame != NULL && pArrayListPlayroom != NULL
			&& arcadeListSize > 0) {
		printf("%*s | %*s | %*s | %*s\n", -4, "ID", -MAX, "Nombre", -MAX,
				"Direccion", -MAX, "Tipo");
		printf("%*c | %*c | %*c | %*c\n", -4, '-', -MAX, '-', -MAX, '-', -MAX,
				'-');
		for (int i = 0; i < playroomListSize; i++) {
			playroom = (Playroom*) ll_get(pArrayListPlayroom, i);
			platformGames = 0;
			labyrinthGames = 0;
			adventureGames = 0;
			for (int j = 0; j < arcadeListSize; j++) {
				arcade = (Arcade*) ll_get(pArrayListArcade, j);
				if (arcade->playroomId == playroom->id) {
					gameIndex = GameController_SearchGameIndexPerId(
							pArrayListGame, &arcade->gameId);
					if (gameIndex != -1) {
						game = (Game*) ll_get(pArrayListGame, gameIndex);
						if (game != NULL) {
							if (game->genre == 1) {
								platformGames++;
							} else {
								if (game->genre == 2) {
									adventureGames++;
								} else {
									if (game->genre == 3) {
										labyrinthGames++;
									}
								}
							}
						}
					}
				}
			}
			if (platformGames >= 4 && labyrinthGames >= 3
					&& adventureGames >= 5) {
				playroom = (Playroom*) ll_get(pArrayListPlayroom, i);
				Playroom_readTypePlayroom(&playroom->type, playroomTypeTxt);
				printf("%-4d | %-30s | %-30s | %-30s\n", playroom->id,
						playroom->name, playroom->address, playroomTypeTxt);
				r = 0;
				listPrinted = 1;
			}
		}
		if (listPrinted != 1) {
			printf("\nNo hay salones que cumplan los requisitos.\n");
		}
	}
	return r;
}

int Relationship_PrintArcadesWithPlayroomAndGame(LinkedList *pArrayListArcade,
		LinkedList *pArrayListPlayroom, LinkedList *pArrayListGame,
		int sizeArcadeList, int sizePlayroomList, int sizeGameList) {
	int r = -1;
	Arcade *arcade;
	Game *game;
	Playroom *playroom;
	int playroomIndex;
	int gameIndex;

	char arcadeSoundTypeTxt[50];
	char gameGenreTxt[50];
	char playroomTypeTxt[50];

	if (pArrayListArcade != NULL && sizeArcadeList > 0 && sizePlayroomList > 0
			&& sizeGameList > 0) {
		printf(
				"%*s | %*s | %*s | %*s | %*s | %*s | %*s | %*s | %*s | %*s | %*s \n",
				-4, "ID", -30, "Nacionalidad", -30, "Tipo de sonido", -10,
				"Jugadores", -10, "Fichas", -30, "Nombre salon", -30,
				"Direccion", -10, "Tipo", -30, "Nombre juego", -30, "Compañia",
				-30, "Genero");
		printf(
				"%*c | %*c | %*c | %*c | %*c | %*c | %*c | %*c | %*c | %*c | %*c\n",
				-4, '-', -30, '-', -30, '-', -10, '-', -10, '-', -30, '-', -30,
				'-', -10, '-', -30, '-', -30, '-', -30, '-');

		for (int i = 0; i < sizeArcadeList; i++) {
			arcade = (Arcade*) ll_get(pArrayListArcade, i);
			playroomIndex = PlayroomController_SearchPlayroomIndexPerId(
					pArrayListPlayroom, &arcade->playroomId);
			if (playroomIndex != -1) {
				playroom = (Playroom*) ll_get(pArrayListPlayroom,
						playroomIndex);
				if (playroom != NULL) {
					gameIndex = GameController_SearchGameIndexPerId(
							pArrayListGame, &arcade->gameId);
					if (gameIndex != -1) {
						game = (Game*) ll_get(pArrayListGame, gameIndex);
						if (game != NULL) {
							Arcade_readSoundTypeArcade(&arcade->soundType,
									arcadeSoundTypeTxt);
							Playroom_readTypePlayroom(&playroom->type,
									playroomTypeTxt);
							Game_readGenreGame(&game->genre, gameGenreTxt);
							printf(
									"%-4d | %-30s | %-30s | %-10d | %-10d | %-30s | %-30s | %-10s | %-30s | %-30s | %-30s\n",
									arcade->id, arcade->nationality,
									arcadeSoundTypeTxt, arcade->players,
									arcade->maxCoins, playroom->name,
									playroom->address, playroomTypeTxt,
									game->name, game->company, gameGenreTxt);
							r = 0;
						}
					}
				}
			}

		}
	}
	return r;
}

int Relationship_PrintArcadesOfPlayroom(LinkedList *pArrayListArcade,
		LinkedList *pArrayListPlayroom, LinkedList *pArrayListGame,
		int sizeArcadeList, int sizePlayroomList) {
	int r = -1;
	Arcade *arcade = NULL;
	Playroom *playroom = NULL;
	Game *game = NULL;
	int playroomId;
	int playroomIndex;
	int gameIndex;
	char arcadeSoundTypeTxt[50];
	char playroomTypeTxt[50];
	int printedList = 0;

	if (pArrayListArcade != NULL && pArrayListPlayroom != NULL
			&& sizeArcadeList > 0) {
		if (PlayroomController_printPlayrooms(pArrayListPlayroom,
				sizePlayroomList) == 0) {
			if (Playroom_AskForPlayroomID(&playroomId) == 0) {
				printf("%*s | %*s | %*s | %*s | %*s | %*s | %*s | %*s \n", -4,
						"ID", -30, "Nacionalidad", -30, "Tipo de sonido", -10,
						"Jugadores", -10, "Fichas", -30, "Nombre salon", -10,
						"Tipo", -30, "Nombre juego");
				printf("%*c | %*c | %*c | %*c | %*c | %*c | %*c | %*c\n", -4,
						'-', -30, '-', -30, '-', -10, '-', -10, '-', -30, '-',
						-10, '-', -30, '-');
			}
			for (int i = 0; i < sizeArcadeList; i++) {
				arcade = (Arcade*) ll_get(pArrayListArcade, i);
				if (arcade != NULL) {
					if (arcade->playroomId == playroomId) {
						playroomIndex =
								PlayroomController_SearchPlayroomIndexPerId(
										pArrayListPlayroom, &playroomId);
						playroom = (Playroom*) ll_get(pArrayListPlayroom,
								playroomIndex);
						if (playroom != NULL) {
							gameIndex = GameController_SearchGameIndexPerId(
									pArrayListGame, &arcade->gameId);
							game = (Game*) ll_get(pArrayListGame, gameIndex);
							if (game != NULL) {
								Arcade_readSoundTypeArcade(&arcade->soundType,
										arcadeSoundTypeTxt);
								Playroom_readTypePlayroom(&playroom->type,
										playroomTypeTxt);
								printf(
										"%-4d | %-30s | %-30s | %-10d | %-10d | %-30s | %-10s | %-30s\n",
										arcade->id, arcade->nationality,
										arcadeSoundTypeTxt, arcade->players,
										arcade->maxCoins, playroom->name,
										playroomTypeTxt, game->name);
								printedList = 1;
								r = 0;
							}
						}
					}
				}
			}
			if (printedList != 1) {
				printf("No hay ningun arcade en ese salon.\n");
			}
		}
	}
	return r;
}

int Relationship_PrintArcadesWithGame(LinkedList *pArrayListArcade,
		LinkedList *pArrayListGame, int sizeArcadeList) {
	int r = -1;
	Arcade *arcade;
	Game *game;
	int gameIndex;

	char arcadeSoundTypeTxt[50];
	char gameGenreTxt[50];

	if (pArrayListArcade != NULL && sizeArcadeList > 0) {
		printf("%*s | %*s | %*s | %*s | %*s | %*s | %*s | %*s \n", -4, "ID",
				-30, "Nacionalidad", -30, "Tipo de sonido", -10, "Jugadores",
				-10, "Fichas", -30, "Nombre juego", -30, "Compañia", -30,
				"Genero");
		printf("%*c | %*c | %*c | %*c | %*c | %*c | %*c | %*c\n", -4, '-', -30,
				'-', -30, '-', -10, '-', -10, '-', -30, '-', -30, '-', -30,
				'-');

		for (int i = 0; i < sizeArcadeList; i++) {
			arcade = (Arcade*) ll_get(pArrayListArcade, i);
			gameIndex = GameController_SearchGameIndexPerId(pArrayListGame,
					&arcade->gameId);
			if (gameIndex != -1) {
				game = (Game*) ll_get(pArrayListGame, gameIndex);
				if (game != NULL) {
					Arcade_readSoundTypeArcade(&arcade->soundType,
							arcadeSoundTypeTxt);
					Game_readGenreGame(&game->genre, gameGenreTxt);
					printf(
							"%-4d | %-30s | %-30s | %-10d | %-10d | %-30s | %-30s | %-30s\n",
							arcade->id, arcade->nationality, arcadeSoundTypeTxt,
							arcade->players, arcade->maxCoins, game->name,
							game->company, gameGenreTxt);
					r = 0;
				}
			}
		}

	}
	return r;
}

int Relationship_RemoveArcade(LinkedList *pArrayListArcade,
		LinkedList *pArrayListPlayroom, LinkedList *pArrayListGame) {
	int r = -1;
	int listArcadeLength = ll_len(pArrayListArcade);
	int listPlayroomLength = ll_len(pArrayListPlayroom);
	int listGameLength = ll_len(pArrayListGame);
	Arcade *arcade = NULL;
	int indexToRemove;
	int idToRemove;

	if (pArrayListArcade != NULL && pArrayListGame != NULL
			&& pArrayListPlayroom != NULL) {
		if (Relationship_PrintArcadesWithPlayroomAndGame(pArrayListArcade,
				pArrayListPlayroom, pArrayListGame, listArcadeLength,
				listPlayroomLength, listGameLength) == 0) {
			if (utn_getNumero("Ingrese el ID del arcade a remover:\n",
					"Ha habido un error, vuelva a intentar\n", 1, 3,
					&idToRemove) == 0) {
				indexToRemove = ArcadeController_SearchArcadeIndexPerId(
										pArrayListArcade, &idToRemove);
				if (indexToRemove != -1) {
					arcade = ll_get(pArrayListArcade, indexToRemove);
					puts("El arcade que elegiste remover es: \n");
					Arcade_printOne(arcade);
					if (confirmation(
							"Estas seguro que deseas removerlo?(1-Si/Otro numero-No)\n",
							"Ha habido un error.\n") == 1) {
						ll_remove(pArrayListArcade, indexToRemove);
						r = 0;
					}
				}
			}
		}
	}

	return r;
}

int Relationship_RemovePlayroomAndArcade(LinkedList *pArrayListPlayroom,
		LinkedList *pArrayListArcade) {
	int r = -1;
	Playroom *playroom = NULL;
	Arcade *arcade = NULL;
	int idToRemove;
	int indexToRemove = -1;

	if (pArrayListArcade != NULL && pArrayListPlayroom != NULL) {

		int playroomListLength = ll_len(pArrayListPlayroom);
		int arcadeListLength = ll_len(pArrayListArcade);

		if (PlayroomController_printPlayrooms(pArrayListPlayroom,
				playroomListLength) == 0) {
			if (utn_getNumero("Ingrese el ID del salon a dar de baja:\n",
					"Error, vuelva a intentar.\n", 1, 3, &idToRemove) == 0) {
				indexToRemove = PlayroomController_SearchPlayroomIndexPerId(
						pArrayListPlayroom, &idToRemove);
				if (indexToRemove != -1) {
					playroom = (Playroom*) ll_get(pArrayListPlayroom,
							indexToRemove);
					puts("El salon que deseas remover es:\n");
					Playroom_printOne(playroom);
					if (confirmation(
							"¿Esta seguro que desea removerlo? Aclaracion: se removeran todos los arcades de este salon\n(1:Si/Otro numero:No)\n",
							"Ha habido un error.\n") == 1) {
						for (int i = 0; i < arcadeListLength; i++) {
							arcade = ll_get(pArrayListArcade, i);
							if (arcade->playroomId == idToRemove) {
								ll_remove(pArrayListArcade, i);
							}
						}
						ll_remove(pArrayListPlayroom, indexToRemove);
						r = 0;
					}
				}
			}
		}
	}
	return r;
}

int Relationship_PrintPlayroomWithArcade(LinkedList *pArrayListPlayroom,
		LinkedList *pArrayListArcade, int playroomSize, int arcadeSize) {
	int r = -1;
	Arcade *arcade = NULL;
	Playroom *playroom = NULL;
	int amountOfArcades = 0;
	int listPrinted = 0;
	char playroomTypeText[50];

	if (pArrayListArcade != NULL && pArrayListPlayroom != NULL
			&& playroomSize > 0 && arcadeSize > 0) {
		printf("%*s | %*s | %*s | %*s\n", -4, "ID", -MAX, "Nombre", -MAX,
				"Direccion", -MAX, "Tipo");
		printf("%*c | %*c | %*c | %*c\n", -4, '-', -MAX, '-', -MAX, '-', -MAX,
				'-');
		for (int i = 0; i < playroomSize; i++) {
			amountOfArcades = 0;
			for (int j = 0; j < arcadeSize; j++) {
				playroom = (Playroom*) ll_get(pArrayListPlayroom, i);
				arcade = (Arcade*) ll_get(pArrayListArcade, j);

				if (arcade->playroomId == playroom->id) {
					amountOfArcades++;
				}
				if (amountOfArcades > 4) {
					Playroom_readTypePlayroom(&playroom->type,
							playroomTypeText);
					printf("%-4d | %-30s | %-30s | %-30s\n", playroom->id,
							playroom->name, playroom->address,
							playroomTypeText);
					listPrinted = 1;
					break;
				}
			}
		}
		if (listPrinted != 1) {
			printf("\tNo hay salones con mas de 4 arcades.\n");
		}
		r = 0;
	}
	return r;
}

int Relationship_PrintPlayroomWithMaxArcade(LinkedList *pArrayListArcade,
		LinkedList *pArrayListPlayroom, int playroomListSize,
		int arcadeListSize) {
	int r = -1;
	Arcade *arcade = NULL;
	int arcadeAux = 0;
	int arcadeMax = 0;
	Playroom *playroom = NULL;
	int playroomId;
	int playroomIndex;

	if (pArrayListArcade != NULL && pArrayListPlayroom != NULL
			&& playroomListSize > 0) {
		for (int i = 0; i < playroomListSize; i++) {
			playroom = (Playroom*) ll_get(pArrayListPlayroom, i);
			arcadeAux = 0;
			if (playroom != NULL) {
				for (int j = 0; j < arcadeListSize; j++) {
					if (arcadeMax <= arcadeAux) {
						arcadeMax = arcadeAux;
						playroomId = playroom->id;
					}
					arcade = (Arcade*) ll_get(pArrayListArcade, j);
					if (arcade != NULL) {
						if (arcade->playroomId == playroom->id) {
							arcadeAux++;
						}
						r = 0;
					}
				}
			}
		}
		playroomIndex = PlayroomController_SearchPlayroomIndexPerId(
				pArrayListPlayroom, &playroomId);
		if (playroomIndex != -1) {
			playroom = (Playroom*) ll_get(pArrayListPlayroom, playroomIndex);
			puts("\nEl salon con mas cantidad de arcades es:\n");
			Playroom_printOne(playroom);
			if (ll_sort(pArrayListArcade, Arcade_CheckForBiggerId, 1) == 0) {
				puts("\nSus arcades son:\n----------\n");
				Relationship_PrintArcadeListOfAPlayroom(pArrayListArcade,
						arcadeListSize, playroomId);
			}
		}
	}
	return r;
}

int Relationship_PrintArcadeForTwoPlayers(LinkedList *pArrayListArcade,
		LinkedList *pArrayListPlayroom, LinkedList *pArrayListGame,
		int sizeArcadeList) {
	int r = -1;
	Arcade *arcade;
	Game *game;
	Playroom *playroom;
	char gameGenreTxt[50];
	int playroomIndex;
	int gameIndex;
	int listPrinted = 0;

	if (pArrayListArcade != NULL && sizeArcadeList > 0) {
		printf("%*s | %*s | %*s | %*s | %*s \n", -4, "ID", -10, "Jugadores",
				-30, "Nombre salon", -30, "Nombre juego", -30, "Genero");
		printf("%*c | %*c | %*c | %*c | %*c\n", -4, '-', -10, '-', -30, '-',
				-30, '-', -30, '-');
		for (int i = 0; i < sizeArcadeList; i++) {
			arcade = (Arcade*) ll_get(pArrayListArcade, i);
			if (arcade->players > 2) {
				playroomIndex = PlayroomController_SearchPlayroomIndexPerId(
						pArrayListPlayroom, &arcade->playroomId);
				playroom = ll_get(pArrayListPlayroom, playroomIndex);
				if (playroom != NULL) {
					gameIndex = GameController_SearchGameIndexPerId(
							pArrayListGame, &arcade->gameId);
					game = ll_get(pArrayListGame, gameIndex);
					if (game != NULL) {
						Game_readGenreGame(&game->genre, gameGenreTxt);
						printf("%-4d | %-10d | %-30s | %-30s | %-30s\n",
								arcade->id, arcade->players, playroom->name,
								game->name, gameGenreTxt);
						listPrinted = 1;
					}
				}
			}
		}
		if (listPrinted != 1) {
			printf("/t No hay arcades de mas de dos jugadores.\n");
		}
		r = 0;
	}
	return r;
}

int Relationship_PrintSpecificKindOfArcade(LinkedList *pArrayListArcade,
		LinkedList *pArrayListGame, int arcadeListSize, int soundTypeArcade,
		int gameGenre) {
	int r = -1;
	LinkedList *auxGameList = ll_newLinkedList();

	if (pArrayListArcade != NULL && pArrayListGame != NULL
			&& arcadeListSize > 0) {
		printf("%*s | %*s | %*s | %*s\n", -10, "Arcade ID", -30,
				"Nombre de juego", -30, "Genero", -10, "Jugadores");
		printf("%*c | %*c | %*c | %*c\n", -10, '-', -30, '-', -30, '-', -10,
				'-');
		if (Relationship_CreateSpecificGameList(auxGameList, pArrayListGame,
				pArrayListArcade, arcadeListSize, soundTypeArcade, gameGenre)
				== 0) {
			if (Relationship_PrintNewGameListSortedByGameName(auxGameList,
					pArrayListArcade, arcadeListSize) == 0) {
				r = 0;
			}
		}

	}
	/*


	 */
	return r;
}

int Relationship_CreateSpecificGameList(LinkedList *newGameList,
		LinkedList *pArrayListGame, LinkedList *pArrayListArcade,
		int arcadeListSize, int soundTypeArcade, int gameGenre) {
	int r = -1;
	Arcade *arcade = NULL;
	Game *game = NULL;
	int gameIndex;

	if (newGameList != NULL) {
		for (int i = 0; i < arcadeListSize; i++) {
			arcade = (Arcade*) ll_get(pArrayListArcade, i);
			if (arcade != NULL) {
				gameIndex = GameController_SearchGameIndexPerId(pArrayListGame,
						&arcade->gameId);
				if (gameIndex != -1) {
					game = (Game*) ll_get(pArrayListGame, gameIndex);
					if (game != NULL) {
						if (arcade->soundType == soundTypeArcade
								&& game->genre == gameGenre) {
							ll_add(newGameList, game);
							r = 0;
						}
					}
				}
			}
		}
	}
	return r;
}

int Relationship_PrintNewGameListSortedByGameName(LinkedList *newList,
		LinkedList *pArrayListArcade, int arcadeListSize) {
	int r = -1;
	Arcade *arcade = NULL;
	Game *game = NULL;
	char gameGenreTxt[50];
	int printedList = 0;

	if (newList->pFirstNode != NULL) {
		int auxGameListLength = ll_len(newList);
		if (ll_sort(newList, Game_CheckForBiggerName, 1) == 0) {
			for (int i = 0; i < auxGameListLength; i++) {
				game = (Game*) ll_get(newList, i);
				if (game != NULL) {
					for (int j = 0; j < arcadeListSize; j++) {
						arcade = (Arcade*) ll_get(pArrayListArcade, j);
						if (arcade->gameId == game->id) {
							Game_readGenreGame(&game->genre, gameGenreTxt);
							printf("%-10d | %-30s | %-30s | %-10d\n",
									arcade->id, game->name, gameGenreTxt,
									arcade->players);
							r = 0;
							printedList = 1;
						}
					}
				}
			}
			if (printedList != 1) {
				printf("No hay arcades con esas caracteristicas.\n");
			}
		}
	}
	return r;
}

int Relationship_PrintArcadeListOfAPlayroom(LinkedList *pArrayListArcade,
		int arcadeListLength, int playroomId) {
	int r = -1;
	Arcade *arcade = NULL;
	char arcadeSoundTypeTxt[50];

	if (pArrayListArcade != NULL && arcadeListLength > 0 && playroomId > 0) {
		printf("%*s | %*s | %*s | %*s | %*s | %*s | %*s\n", -4, "ID", -8,
				"Salon ID", -8, "Juego ID", -MAX_COL, "Nacionalidad", -MAX_COL,
				"Tipo de sonido", -10, "Jugadores", -2, "Fichas");
		printf("%*c | %*c | %*c | %*c | %*c | %*c | %*c\n", -4, '-', -8, '-',
				-8, '-', -MAX_COL, '-', -MAX_COL, '-', -10, '-', -2, '-');
		for (int i = 0; i < arcadeListLength; i++) {
			arcade = (Arcade*) ll_get(pArrayListArcade, i);
			if (arcade->playroomId == playroomId) {
				Arcade_readSoundTypeArcade(&arcade->soundType,
						arcadeSoundTypeTxt);
				printf("%-4d | %-8d | %-8d | %-20s | %-20s | %-10d | %d\n",
						arcade->id, arcade->playroomId, arcade->gameId,
						arcade->nationality, arcadeSoundTypeTxt,
						arcade->players, arcade->maxCoins);
				r = 0;
			}

		}
	}
	return r;
}
