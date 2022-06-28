/*
 ============================================================================
 Name        : Parcial-Laboratorio-2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "General.h"
#include "Playroom/PlayroomController.h"
#include "Game/GameController.h"
#include "Arcade/ArcadeController.h"
#include "Relationships/Relationships_ArcadePlayroomAndGames.h"

int main(void) {
	setbuf(stdout, NULL);
	LinkedList *listOfPlayrooms = ll_newLinkedList();
	LinkedList *listOfArcades = ll_newLinkedList();
	LinkedList *listOfGames = ll_newLinkedList();

	//ARREGLAR:
	/*
	 * 2-Documentacion
	 */

	int option;
	int subOption;

	//Carga de datos//
	PlayroomController_LoadPlayroomsFromText("playroomData", listOfPlayrooms);
	GameController_LoadGamesFromText("gamesData", listOfGames);
	ArcadeController_LoadArcadesFromText("arcadeData", listOfArcades);

	do {
		printf("*************************\n");
		printf("**2do EXAMEN LAB I - 1H **\n");
		printf("*************************\n\n");

		if (utn_getNumero(
				"Menu:\n1-Alta de salon\n2-Eliminar salon\n3-Listar salones\n4-Incorporar arcade\n5-Modificar arcade\n6-Remover arcade\n7-Listar arcades\n8-Agregar juego\n9-Listar juegos\n10-Informes\n11-Salir\n",
				"Ha habido un error\n", 0, 3, &option) == 0) {
			switch (option) {
			case 1:
				if (PlayroomController_registerAPlayroom("playroomData",
						listOfPlayrooms) == 0) {
					puts("Salon registrado con exito\n");
				} else {
					puts("Hubo una falla en el registro del salon\n");
				}
				break;
			case 2:
				if (Relationship_RemovePlayroomAndArcade(listOfPlayrooms,
						listOfArcades) == 0) {
					puts("Salon removido correctamente!\n");
				} else {
					puts("No se ha podido remover el salon\n");
				}
				break;
			case 3:
				if (PlayroomController_printPlayrooms(listOfPlayrooms,
						ll_len(listOfPlayrooms)) == 0) {
					puts("\nLista impresa\n");
				} else {
					puts("Hubo un error\n");
				}
				break;
			case 4:
				if (Relationship_RegisterAnArcadeInPlayroom(listOfPlayrooms,
						listOfArcades, listOfGames) == 0) {
					puts("Se ha registrado el arcade con exito\n");
				} else {
					puts("Hubo un error\n");
				}
				break;
			case 5:
				if (Relationship_ModifyArcade(listOfArcades, listOfGames)
						== -1) {
					puts("Hubo un error\n");
				}
				break;
			case 6:
				if (Relationship_RemoveArcade(listOfArcades, listOfPlayrooms,
						listOfGames) == 0) {
					puts("Arcade removido!\n");
				} else {
					puts("Ningun arcade fue removido\n");
				}
				break;
			case 7:
				if (Relationship_PrintArcadesWithGame(listOfArcades,
						listOfGames, ll_len(listOfArcades)) == 0) {
					puts("\nLista impresa\n");
				} else {
					puts("Ha habido un error\n");
				}
				break;
			case 8:
				if (GameController_RegisterGame("gamesData", listOfGames)
						== 0) {
					puts("Juego añadido con exito\n");
				} else {
					puts("Hubo un error\n");
				}
				break;
			case 9:
				if (GameController_PrintGames(listOfGames, ll_len(listOfGames))
						== 0) {
					puts("\nLista impresa\n");
				} else {
					puts("Hubo un error\n");
				}
				break;
			case 10:
				do {
					if (utn_getNumero(
							"\nSubmenu:\n--------\n\n1-Listar salones con mas de 4 arcades\n2-Listar arcades para mas de 2 jugadores\n3-Listar informacion de salon especifico\n4-Listar salones completos\n5-Listar arcades de un salon\n6-Listar salon con mas cantidad de arcade\n7-Listar arcades son sonido MONO y genero PLATAFORMA\n8-Salir\n",
							"Ha habido un error, vuelva a intentar\n", 1, 3,
							&subOption) == 0) {
						switch (subOption) {
						case 1:
							if (Relationship_PrintPlayroomWithArcade(
									listOfPlayrooms, listOfArcades,
									ll_len(listOfPlayrooms),
									ll_len(listOfArcades)) == 0) {
								puts("\nLista impresa\n");
							} else {
								puts("Hubo un error\n");
							}
							break;
						case 2:
							if (Relationship_PrintArcadeForTwoPlayers(
									listOfArcades, listOfPlayrooms, listOfGames,
									ll_len(listOfArcades)) == 0) {
								puts("\nLista impresa\n");
							} else {
								puts("Hubo un error\n");
							}
							break;
						case 3:
							if (PlayroomController_PrintEspecificPlayroom(
									listOfPlayrooms, ll_len(listOfPlayrooms))
									== 0) {
								puts("\nSalon impreso\n");
							} else {
								puts("Hubo un error\n");
							}
							break;
						case 4:
							if (Relationship_PrintCompletePlayroom(
									listOfPlayrooms, listOfGames, listOfArcades,
									ll_len(listOfArcades),
									ll_len(listOfPlayrooms)) == 0) {
								printf("\nLista impresa\n");
							} else {
								printf("Hubo un error.\n");
							}
							break;
						case 5:
							if (Relationship_PrintArcadesOfPlayroom(
									listOfArcades, listOfPlayrooms, listOfGames,
									ll_len(listOfArcades),
									ll_len(listOfPlayrooms)) == 0) {
								puts("\nLista impresa\n");
							} else {
								puts("Hubo un error\n");
							}
							break;
						case 6:
							if (Relationship_PrintPlayroomWithMaxArcade(
									listOfArcades, listOfPlayrooms,
									ll_len(listOfPlayrooms),
									ll_len(listOfArcades)) == 0) {
								puts("\nLista impresa\n");
							} else {
								puts("Hubo un error\n");
							}
							break;
						case 7:
							if (Relationship_PrintSpecificKindOfArcade(
									listOfArcades, listOfGames,
									ll_len(listOfArcades), STEREO, PLATFORM)
									== 0) {
								puts("\nLista impresa\n");
							} else {
								puts("Hubo un error\n");
							}
							break;
						case 8:
							puts("Saliendo...\n");
							break;
						default:
							printf("Por favor, elija un numero del 1 al 8\n");
							break;
						}
					}
				} while (subOption != 8);
				break;
			case 11:
				printf("Saliendo...\n");
				break;
			}
		}
	} while (option != 11);

	//Guardado de datos
	PlayroomController_SavePlayroomAsText("playroomData", listOfPlayrooms);
	ArcadeController_SaveArcadeAsText("arcadeData", listOfArcades);
	GameController_SaveGameAsText("gamesData", listOfGames);

	return EXIT_SUCCESS;
}
