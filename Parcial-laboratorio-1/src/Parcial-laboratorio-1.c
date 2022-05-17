/*
 ============================================================================
 Name        : Parcial-laboratorio-1.c
 Author      : Gonzalo Vidal
 Version     :
 Copyright   : Parcial laboratorio
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "General.h"
#include "User.h"
#include "Product.h"
#include "Tracking.h"
#include "Relationship_TrackingUserAndProducts.h"


int main(void) {
	setbuf(stdout, NULL);
	User userList[MAX_USERS];
	Product productList[MAX_PRODUCTS];
	Tracking trackingList[MAX_TRACKINGS];
	int r;
	int startOption;
	int userOption;
	int adminOption;
	int userId = 0;

	User_initializeUsers(userList, MAX_USERS);
	Product_initializeProducts(productList, MAX_PRODUCTS);
	Tracking_initializeTrackings(trackingList, MAX_TRACKINGS);

	printExamMenu(0);

	do {
		utn_getNumero("1)Ingresar\n2)Registrarse\n\n9)Salir\n",
				"Ha habido un error\n", 0, 3, &startOption);
		switch (startOption) {
		case 1:
			r = User_Login(userList, MAX_USERS, &userId);
			if (r == 2 && userList[userId].loggedIn == 1) {

				printExamMenu(userList[userId].type);

				do {
					if (userList[userId].loggedIn == 1) {
						utn_getNumero(
								"1)Listar estado de todos los usuarios\n2)Listar todos los productos por categoria\n3)Baja de un producto\n4)Baja de un usuario\n5)Ver tracking global\n9)Salir\n",
								"Ha habido un error\n", 0, 3, &adminOption);
						switch (adminOption) {
						case 1:
							if (User_PrintAllUsers(userList, MAX_USERS) == 0) {
								printf("Usuarios listados\n\n");
							} else {
								printf("Ha habido un error\n\n");
							}
							break;
						case 2:
							if (Product_PrintProducts(productList, MAX_PRODUCTS,
							ACTIVE) == 0) {
								printf("Productos listados\n\n");
							}
							break;
						case 3:
							if (Product_RemoveProduct(productList, MAX_PRODUCTS)
									== 0) {
								printf("Producto dado de baja\n\n");
							} else {
								printf(
										"El producto no ha podido darse de baja\n\n");
							}
							break;
						case 4:
							if (User_LowMembership(userList, MAX_USERS,
									userList[userId]) == 0) {
								printf("Usuario dado de baja\n\n");
							} else {
								printf(
										"El usuario no ha podido darse de baja\n\n");
							}
							break;
						case 5:
							if (Tracking_PrintAndRefreshTrackings(trackingList,
							MAX_TRACKINGS) == 0) {
								printf("Trackings listados\n\n");
							} else {
								printf("Ha habido un error\n\n");
							}
							break;
						case 0:
							userList[userId].loggedIn = 0;
							break;
						default:
							break;
						}
					}
				} while (adminOption != 9 && userList[userId].loggedIn == 1);
				//MENU ADMIN
			} else {
				if (r == 1 && userList[userId].loggedIn) {
					printExamMenu(userList[userId].type);
					do {
						utn_getNumero(
								"1)Comprar\n2)Vender\n3)Estado de compras\n4)Estado de ventas\n9)Salir\n",
								"Ha habido un error\n", 0, 3, &userOption);
						switch (userOption) {
						case 1:
							r = Relationship_BuyProductAndNewTracking(
									productList, MAX_PRODUCTS, trackingList,
									MAX_TRACKINGS, userList[userId]);
							if (r == 0) {
								printf("\n\nCompra realizada con exito!\n\n");
							} else {
								printf("\n\nCompra no realizada.\n\n");

							}
							break;
						case 2:
							if (Relationship_SellProduct(productList,
							MAX_PRODUCTS, userList[userId]) == 0) {
								printf(
										"\n\n�Tu producto se ha puesto en venta!\n\n");
							} else {
								printf(
										"\n\nTu producto no se pudo poner en venta :(\n\n");
							}
							break;
						case 3:
							if (Relationship_checkBoughtTrackings(trackingList,
							MAX_TRACKINGS, productList, MAX_PRODUCTS,
									userList[userId]) == 0) {
								printf("\n\n------------\n\n");
							} else {
								printf("\n\nHa habido un error :/\n\n");
							}
							break;
						case 4:
							if (Relationship_checkSoldTrackings(trackingList,
							MAX_TRACKINGS, productList, MAX_PRODUCTS,
									userList[userId]) == 0) {
								printf("\n\n------------\n\n");
							} else {
								printf("\n\nHa habido un error :/\n\n");
							}
							break;
						case 0:
							userList[userId].loggedIn = 0;
							break;
						default:
							break;
						}
					} while (userOption != 9);
				} else {
					if(r == -2){
						printf("\n\nEmail y/o contrase�a incorrectos\n\n");
					}
				}
			}
			break;
		case 2:
			if (User_Membership(userList, MAX_USERS) == 0) {
				printf("�Usuario creado con exito!\n\n");
			} else {
				printf("�Ha habido un error en el registro!\n\n");
			}
			break;
		case 9:
			printf("�Gracias por usar nuestro programa!\n\n");
			break;
		default:
			printf("Por favor, ingrese un numero de los mencionados.\n\n");
			break;
		}
	} while (startOption != 9);
	return EXIT_SUCCESS;
}