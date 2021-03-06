/*
 * Relationship_TrackingUserAndProducts.c
 *
 *  Created on: 14 may 2022
 *      Author: gonza
 */

#include "Relationship_TrackingUserAndProducts.h"
#include "General.h"
#include "User.h"
#include "Product.h"
#include "Tracking.h"
#include "Product.h"
#include "TimeFunctions.h"

static int idTrackingAI = 2000;
static int Tracking_GetUniqueId() {
	return idTrackingAI++;
}

static int idProductAI = 4000;
static int Product_getUniqueId() {
	return idProductAI++;
}

int Relationship_BuyProductAndNewTracking(Product productList[], int size,
		Tracking trackingList[], int trackingSize, User buyer) {
	int r = -1;
	int indexBuy;
	int stockToBuy;
	float totalPrice;
	int availableToBuy = 0;
	int ID = 0;

	if (productList != NULL) {
		if (size > 0) {
			for (int i = 0; i < size; i++) {
				if (productList[i].isEmpty == 1) {
					availableToBuy = 1;
				}
			}
			if (availableToBuy == 1) {
				Product_PrintProducts(productList, size, INPROCESS);
				if (confirmation(
						"\n\n?Desea proseguir con la compra?\n(1-Si / Otro numero-No)\n\n",
						"Ha habido un error, intentelo nuevamente por favor.\n")
						== 1) {
					if (utn_getNumero("Ingrese el ID del producto a comprar:\n",
							"Hubo un error\n", 0, 3, &ID) == 0) {
						indexBuy = Product_SearchIndexPerId(productList, size,
								ID,
								INPROCESS);
						if (indexBuy == -1) {
							printf("No se encontro el ID en la lista.\n");
						} else {
							printf(
									"El producto que desea comprar es el siguiente:\n");
							Product_printOne(productList[indexBuy]);
							utn_getNumeroWithMax(
									"Ingrese la cantidad de elementos que desea comprar.\n",
									"Ha habido un error, vuelva a intentarlo.\n",
									0, productList[indexBuy].stock, 3,
									&stockToBuy);
							totalPrice = stockToBuy
									* productList[indexBuy].price;
							printf("Precio final: %.2f\n", totalPrice);
							if (confirmation(
									"?Esta seguro que quiere comprar?(1-Si/Otro numero-No)\n",
									"Ha habido un error en relacion al numero ingresado. Intentelo nuevamente.\n")
									== 1) {
								productList[indexBuy].stock =
										productList[indexBuy].stock
												- stockToBuy;
								productList[indexBuy].isEmpty = INPROCESS;
								if (productList[indexBuy].stock == 0) {
									productList[indexBuy].isEmpty = NOSTOCK;
								}

								Relationship_newTracking(trackingList,
										trackingSize, buyer.idUsuario,
										buyer.postalCode,
										productList[indexBuy].idSeller,
										productList[indexBuy].idProduct,
										stockToBuy);
								r = 0;
							} else {
								r = -2;
							}
						}
					}
				}
			} else {
				printf("No hay productos a la venta.\n");
			}

		}
	}
	return r;
}

int Relationship_SellProduct(Product productList[], int size, User seller) {
	int r = -1;
	Product auxProduct;

	if (productList != NULL && size > 0) {
		int indexProduct = Product_SearchSpace(productList, size, FREE);

		if (indexProduct != -1) {
			printf(
					"Categorias:\nModa: 1\nTecnologia: 2\nConstruccion: 3\nElectrodomesticos: 4\n\n");
			if (Product_LoadProduct(&auxProduct) == 0) {
				auxProduct.idProduct = Product_getUniqueId();
				auxProduct.isEmpty = INPROCESS;
				auxProduct.idSeller = seller.idUsuario;
				productList[indexProduct] = auxProduct;
				r = 0;
			} else {
				printf("Hubo un error en la carga del producto.\n\n");
			}
		}
	}
	return r;
}

int Relationship_CheckAndRestockMyProducts(Product productList[],
		int productSize, User seller) {
	int r = -1;
	int productsInSystem = 0;
	int idToModify;
	int stockToAdd;

	if (productList != NULL && productSize > 0) {
		for (int i = 0; i < productSize; i++) {
			if (productList[i].idSeller == seller.idUsuario) {
				productsInSystem = 1;
				Product_printOne(productList[i]);
			}
		}
		if (productsInSystem == 1) {
			if (confirmation(
					"\n\n?Desea reponer stock de alguno de sus productos? 1)Si / Otro numero) No\n\n",
					"Ha habido un error\n") == 1) {
				if (utn_getNumero(
						"Ingrese el ID del producto al que quiera sumarle stock\n",
						"Ha habido un error, intentelo nuevamente\n", 1, 3,
						&idToModify) == 0) {
					int indexToModify = Product_SearchIndexPerId(productList,
							productSize, idToModify, ACTIVE);
					if (indexToModify != -1) {
						printf(
								"El producto que desea restockear es el siguiente:\n");
						Product_printOne(productList[indexToModify]);
						if (confirmation(
								"\n\n?Esta seguro que desea restockearlo? 1)Si / Otro numero) No\n\n",
								"Ha habido un error\n") == 1) {
							if (utn_getNumero(
									"?Cuantos elementos desea a?adir?\n",
									"Ha habido un error\n", 1, 3, &stockToAdd)
									== 0) {
								productList[indexToModify].stock =
										productList[indexToModify].stock
												+ stockToAdd;
								printf("\n?Restock realizado!\n");
								r = 0;
							}
						}
					}
				}
			} else {
				printf("No se ha realizado ningun restock.\n");
			}
		} else {
			printf("\nNo tenes productos a la venta\n");
		}

	}
	return r;
}

int Relationship_newTracking(Tracking trackingList[], int trackingSize,
		int idBuyer, int postalCode, int idSeller, int productId,
		int stockToBuy) {
	int r = -1;
	Tracking auxTracking;
	int distanceKM;
	long int timeArrival;
	char sTimeArrival[4096];

	int indexFree = Tracking_SearchSpace(trackingList, trackingSize, FREE);

	if (indexFree != -1) {
		if (trackingList != NULL && trackingSize > 0 && idBuyer >= 0
				&& postalCode >= 0 && idSeller >= 0 && productId >= 0
				&& stockToBuy >= 0) {
			auxTracking.idTracking = Tracking_GetUniqueId();
			auxTracking.idProduct = productId;
			auxTracking.quantity = stockToBuy;
			auxTracking.idBuyer = idBuyer;
			auxTracking.idSeller = idSeller;
			CalculateDistance(postalCode, &distanceKM);
			CalculateArrivalTime(distanceKM, &timeArrival);
			auxTracking.arrivingTime = timeArrival;
			strncpy(sTimeArrival, ctime(&timeArrival), 4096);
			auxTracking.isEmpty = OCCUPIED;
			trackingList[indexFree] = auxTracking;
			printf(
					"ID tracking: %d\nID Product:%d\nID de comprador:%d\nID de vendedor:%d\nStock:%d\nCodigo postal del comprador:%d\nTiempo estimado de llegada: %s\n",
					trackingList[indexFree].idTracking,
					trackingList[indexFree].idProduct,
					trackingList[indexFree].idBuyer,
					trackingList[indexFree].idSeller,
					trackingList[indexFree].quantity, postalCode, sTimeArrival);
			r = 0;
		}

	}

	return r;
}

int Relationship_checkBoughtTrackings(Tracking trackingList[], int trackingSize,
		Product productList[], int productSize, User buyer) {
	int r = -1;
	int option;
	int activeBuyer = 0;

	if (trackingList != NULL && trackingSize > 0 && buyer.idUsuario > 0
			&& productList != NULL && productSize > 0) {

		for (int i = 0; i < trackingSize; i++) {
			if (trackingList[i].idBuyer == buyer.idUsuario) {
				activeBuyer = 1;
				for (int j = 0; j < productSize; j++) {
					if (trackingList[i].idProduct == productList[j].idProduct) {
						if (trackingList[i].arrivingTime < time_Current()) {
							trackingList[i].isEmpty = DELIVERED;
							printf("?Su producto %s ya ha sido entregado!\n",
									productList[j].productName);
						}
						printf(
								"\nID Producto: %d\nNombre de producto: %s\nTiempo estimado de llegada:%s\n",
								productList[j].idProduct,
								productList[j].productName,
								ctime(&trackingList[i].arrivingTime));
						if (trackingList[i].isEmpty == 1) {
							printf("Estado: EN PROCESO\n\n");
						} else {
							if (trackingList[i].isEmpty == 2) {
								printf("Estado: ENTREGADO\n\n");
							} else {
								if (trackingList[i].isEmpty == -2) {
									printf("Estado: CANCELADO\n\n");
								}
							}
						}
					}
				}
			}
		}
		if (activeBuyer == 1) {
			if (utn_getNumeroWithMax("1)Cancelar una compra\n0)Salir\n",
					"Ha habido un error, intentelo nuevamente\n", 0, 2, 3,
					&option) == 0) {
				int idToCancel;
				switch (option) {
				case 0:
					break;
				case 1:
					if (utn_getNumero(
							"Ingrese el ID del producto que desea cancelar\n",
							"Ha habido un error, intentelo nuevamente\n", 0, 3,
							&idToCancel) == 0) {
						int productToCancel = Product_SearchIndexPerId(
								productList, productSize, idToCancel,
								ACTIVE);
						printf(
								"El producto que desea cancelar es el siguiente:\n");
						Product_printOne(productList[productToCancel]);
						if (confirmation(
								"?Esta seguro que desea cancelarlo? 1-Si / Otro numero-No\n",
								"Ha habido un error.\n") == 1) {

							for (int i = 0; i < trackingSize; i++) {
								if (trackingList[i].idProduct == idToCancel) {
									if (trackingList[i].isEmpty == 2) {
										printf(
												"?El producto que desea cancelar ya fue entregado!\n");
									} else {
										trackingList[i].isEmpty = CANCELLED;
										printf("?Compra cancelada!\n");
									}
								}
							}

						}
					}
				}
			}
		} else {
			printf("?Todavia no compraste ningun elemento!\n");
		}
	}
	r = 0;

	return r;
}

int Relationship_checkSoldTrackings(Tracking trackingList[], int trackingSize,
		Product productList[], int productSize, User seller) {
	int r = -1;
	int option;
	int activeSeller = 0;
	int productDeliveredOrCancelled = 0;
	int productsActive = 0;

	if (trackingList != NULL && trackingSize > 0 && seller.idUsuario > 0
			&& productList != NULL && productSize > 0) {

		for (int i = 0; i < productSize; i++) {
			if (productList[i].idSeller == seller.idUsuario) {
				activeSeller = 1;
			}
		}

		if (activeSeller == 1) {
			do {
				if (utn_getNumeroWithMax(
						"1)Listado de ventas finalizadas\n2)Ver mis productos\n0)Salir\n",
						"Ha habido un error, vuelva a intentarlo.\n", 0, 4, 3,
						&option) == 0) {
					switch (option) {
					case 1:
						for (int i = 0; i < trackingSize; i++) {
							if (trackingList[i].idSeller == seller.idUsuario) {
								for (int j = 0; j < productSize; j++) { //Refactorizar
									if (trackingList[i].idProduct
											== productList[j].idProduct) {
										if (trackingList[i].arrivingTime
												< time_Current()) {
											trackingList[i].isEmpty = DELIVERED;
										}
										if (trackingList[i].isEmpty == CANCELLED
												|| trackingList[i].isEmpty
														== DELIVERED) {
											productDeliveredOrCancelled = 1;
											printf(
													"ID Producto: %d\nNombre de producto: %s\nCategoria: %d\nPrecio: %.2f\nEstado:%d\n",
													productList[j].idProduct,
													productList[j].productName,
													productList[j].category,
													productList[j].price,
													trackingList[i].isEmpty);
										}
									}
								}
							}
						}
						if (productDeliveredOrCancelled == 0) {
							printf(
									"No hay productos entregados o cancelados\n");
						}
						break;
					case 2:
						for (int j = 0; j < productSize; j++) { //Refactorizar
							if (productList[j].idSeller == seller.idUsuario) {
								if (productList[j].isEmpty == ACTIVE) {
									printf(
											"ID Producto: %d\nNombre de producto: %s\n",
											productList[j].idProduct,
											productList[j].productName);
								}
								productsActive = 1;
							}
						}
						if (productsActive == 0) {
							printf("No hay productos a la venta\n");
						}
						break;
					case 0:
						break;
					}
				}

			} while (option != 0);

		} else {
			printf("?Todavia no hay ventas!\n");
		}
	}
	r = 0;
	return r;
}

int Relationship_FilterProductByName(Product productList[], int productSize) {
	int r = -1;
	char productNameToSearch[MAX_PRODUCTNAME];
	Product aux;
	Product newArray[50];
	int newArrayIndexFree;
	int newArrayIndexActive;
	Product_initializeProducts(newArray, 50);

	if (productList != NULL && productSize > 0) {

		if (utn_getString(productNameToSearch, MAX_PRODUCTNAME,
				"Ingrese el nombre de producto a buscar\n",
				"Ha habido un error, vuelva a intentar.\n", 3) == 0) {
			for (int i = 0; i < productSize; i++) {
				if (strcmp(productList[i].productName, productNameToSearch)
						== 0) {
					newArrayIndexFree = Product_SearchSpace(newArray, 50, FREE);
					newArray[newArrayIndexFree] = productList[i];
				}
			}
			newArrayIndexActive = Product_SearchSpace(newArray, 50, ACTIVE);
			if (newArrayIndexActive != -1) {
				for (int i = 0; i < 50; i++) {
					for (int j = i + 1; j < 50; j++) {
						if (newArray[i].stock < newArray[j].stock) {
							aux = newArray[i];
							newArray[i] = newArray[j];
							newArray[j] = aux;
						}
					}
				}

				Product_PrintProducts(newArray, 50, ACTIVE);
				r = 0;
			}

		}
	}
	return r;
}

