/*
 * Product.c
 *
 *  Created on: 14 may 2022
 *      Author: gonza
 */

#include "Product.h"
#include "General.h"
static int idHardcodedProductAI = 3000;
static int HardcodedProduct_getUniqueId() {
	return idHardcodedProductAI++;
}
/** \brief To indicate that all position in the array are empty,
 * this function put the flag (isEmpty) in TRUE in all
 * position of the array
 * \param list Product* Pointer to array of Product
 * \param len int Array length
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */

int Product_initializeProducts(Product *productList, int size) {
	int r = -1;
	int i;

	if (productList != NULL && size > 0) {
		for (i = 0; i < size; i++) {
			productList[i].isEmpty = FREE;
		}
	}
	return r;
}

/** \brief print the content of one element of Product
 *
 * \param Struct p
 * \return int
 *
 */
void Product_printOne(Product p) {
	printf("ID %d\nNombre: %s\nPrecio: %.2f\nCategoria: %d\nStock: %d\n",
			p.idProduct, p.productName, p.price, p.category, p.stock);

}

/** \brief print the content of Products array after sorting them by category
 *
 * \param list Product*
 * \param length int
 * \return int (1 OK -1 if products list is null or size less than 0
 *
 */

int Product_PrintProducts(Product ProductsList[], int size, int status) {
	int r = -1;

	if (ProductsList != NULL) {
		if (size > 0) {
			if (Product_Sort(ProductsList, size) == 0) {
				printf("%*s | %*s | %*s | %*s | %*s\n", -4, "ID", -MAX,
						"PRODUCTO", -MAX, "CATEGORIA", -MAX, "PRECIO", -MAX,
						"STOCK");
				printf("%*c | %*c | %*c | %*c | %*c\n", -4, '-', -MAX, '-',
						-MAX, '-', -MAX, '-', -MAX, '-');
				for (int i = 0; i < size; i++) {
					if (ProductsList[i].isEmpty == status) {
						printf("%-4d | %-10s | %-10d | %-10.2f | %-10d\n",
								ProductsList[i].idProduct,
								ProductsList[i].productName,
								ProductsList[i].category, ProductsList[i].price,
								ProductsList[i].stock);
						r = 0;
					}
				}
			}
		}
	}

	return r;
}

/** \brief sort the content of the array by category.
 *
 * \param list Product*
 * \param length int
 * \return int (1 OK -1 if products list is null or size less than 0
 *
 */

int Product_Sort(Product productList[], int size) {
	int r = -1;
	int i;
	int j;
	Product aux;

	if (productList != NULL && size > 0) {

		for (i = 0; i < size - 1; i++) {
			for (j = i + 1; j < size; j++) {
				if (productList[i].isEmpty == ACTIVE
						&& productList[j].isEmpty == ACTIVE) {
					if (productList[i].category > productList[j].category) {
						aux = productList[i];
						productList[i] = productList[j];
						productList[j] = aux;
					}
				}
			}
		}
		r = 0;

	}
	return r;
}

/** \brief Remove a Product by Id (put isEmpty Flag in 1)
 *
 * \param list Product*
 * \param len int
 * \param id int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
 find a Product] - (0) if Ok
 *
 */
int Product_RemoveProduct(Product productList[], int size) {
	int r = -1;
	int indexToRemove;
	int ID = 0;

	if (productList != NULL) {
		if (size > 0) {
			if (Product_PrintProducts(productList, size, ACTIVE) == 0) {
				if (utn_getNumero(
						"Ingrese el ID del producto que desea dar de baja:\n",
						"Hubo un error\n", 0, 3, &ID) == 0) {
					indexToRemove = Product_SearchIndexPerId(productList, size,
							ID,
							ACTIVE);
					if (indexToRemove == -1) {
						printf("No se encontro el ID en la lista.\n");
						return r;
					} else {
						printf(
								"El producto que desea dar de baja es el siguiente:\n");
						Product_printOne(productList[indexToRemove]);

						if (confirmation(
								"?Esta seguro que quiere darlo de baja?(1-Si/Otro numero-No)\n",
								"Ha habido un error en relacion al numero ingresado. Intentelo nuevamente.\n")
								== 1) {
							productList[indexToRemove].isEmpty = LOW;
							r = 0;
						} else {
							r = -2;
						}
					}
				}
			}
		}
	}
	return r;
}

/** \brief Search an especific space in the array
 *
 * \param list Product*
 * \param len int
 * \param id status (to search)
 * \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
 find a Product] - (0) if Ok
 *
 */

int Product_SearchSpace(Product productList[], int size, int status) {
	int r = -1;
	int i;

	if (productList != NULL && size > 0) {
		for (i = 0; i <= size; i++) {
			if (productList[i].isEmpty == status) {
				r = i;
				break;
			}
		}
	}
	return r;
}

/** \brief Search an especific index in the array who matches with the ID given in the param
 *
 * \param list Product*
 * \param len int
 * \param id (to search)
 * \param status (to search)
 * \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
 find a Product] - (0) if Ok
 *
 */

int Product_SearchIndexPerId(Product productList[], int size, int ID,
		int status) {
	int r = -1;
	int i;

	if (productList != NULL && size > 0) {
		for (i = 0; i < size; i++) {
			if (productList[i].idProduct == ID
					&& productList[i].isEmpty == status) {
				r = i;
				break;
			}
		}
	}

	return r;
}

/** \brief Loads non-generic data to an Product auxiliar
 *\param Struct auxiliar
 * \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
 find a Product] - (0) if Ok
 *
 */

int Product_LoadProduct(Product *auxiliar) {
	int r = -1;

	if (utn_getString(auxiliar->productName, 25, "Nombre de producto:\n",
			"Error, vuelva a intentar.\n", 3) == 0) {
		if (utn_getNumeroFlotante("Precio de producto:\n",
				"Hubo un error. Vuelva a intentar\n", 1, 3, &auxiliar->price)
				== 0) {
			if (utn_getShortInt("Categoria:\n", "Error, vuelva a intentar.\n",
					1, 5, 3, &auxiliar->category) == 0) {
				if (utn_getNumero("Cantidad de stock:\n",
						"Error, vuelva a intentar.\n", 0, 3, &auxiliar->stock)
						== 0) {
					r = 0;
				}
			}
		}
	}

	return r;

}

//Repet? el ID

int Product_HardcodeProduct(char productName[], float price, short int category,
		int stock, Product productList[], int size) {
	int r = -1;
	Product aux;

	int index = Product_SearchSpace(productList, size, FREE);
	if (index != -1) {
		strncpy(aux.productName, productName, MAX_PRODUCTNAME);
		aux.price = price;
		aux.category = category;
		aux.stock = stock;
		aux.isEmpty = ACTIVE;
		aux.idProduct = HardcodedProduct_getUniqueId();
		productList[index] = aux;
	}

	return r;
}

/** \brief find a Product by Id en returns the index position in ProductsList.
 *
 * \param list Product*
 * \param len int
 * \param id int
 * \return Return Product index position or (-1) if [Invalid length or
 NULL pointer received or Product not found]
 *
 */

