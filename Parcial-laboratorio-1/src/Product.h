/*
 * Product.h
 *
 *  Created on: 14 may 2022
 *      Author: gonza
 */

#ifndef PRODUCT_H_
#define PRODUCT_H_
#define MAX 10
#define LOW -2
#define NOSTOCK -1
#define FREE 0
#define ACTIVE 1
#define MAX_PRODUCTS 5

typedef struct{
	int idProduct;
	int idSeller;
	short int isEmpty;
	//AGREGAR RELACION
	char productName[25];
	float price;
	short int category;
	int stock;
} Product;

int Product_initializeProducts(Product productList[], int size);
void Product_printOne(Product p);
int Product_PrintProducts(Product ProductsList[], int size, int status);
int Product_SearchSpace(Product productList[], int size, int status);
int Product_BuyProduct(Product productList[], int size);
int Product_SellProduct(Product productList[], int size, int userId);
int Product_Membership(Product productList[], int size);
int Product_RemoveProduct(Product productList[], int size);
int Product_Edit(Product productList[], int size);
int Product_SearchIndexPerId(Product productList[], int size, int ID, int status);
int Product_Sort(Product productList[], int size);
Product Product_ModificarUno(Product s);
int Product_LoadProduct(Product *product);

#endif /* PRODUCT_H_ */
