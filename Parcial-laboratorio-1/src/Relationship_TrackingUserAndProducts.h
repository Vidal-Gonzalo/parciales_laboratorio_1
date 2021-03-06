/*
 * Relationship_TrackingUserAndProducts.h
 *
 *  Created on: 14 may 2022
 *      Author: gonza
 */

#ifndef RELATIONSHIP_TRACKINGUSERANDPRODUCTS_H_
#define RELATIONSHIP_TRACKINGUSERANDPRODUCTS_H_
#include "General.h"
#include "User.h"
#include "Product.h"
#include "Tracking.h"

int Relationship_newTracking(Tracking trackingList[], int trackingSize,
		int idBuyer, int postalCode, int idSeller, int productId,
		int stockToBuy);

int Relationship_BuyProductAndNewTracking(Product productList[], int size,
		Tracking trackingList[], int trackingSize, User buyer);

int Relationship_checkBoughtTrackings(Tracking trackingList[], int trackingSize,
		Product productList[], int productSize, User buyer);

int Relationship_CheckAndRestockMyProducts(Product productList[],
		int productSize, User seller);

int Relationship_checkSoldTrackings(Tracking trackingList[], int trackingSize,
		Product productList[], int productSize, User seller);

int Relationship_SellProduct(Product productList[], int size, User seller);

int Relationship_FilterProductByName(Product productList[], int productSize) ;

#endif /* RELATIONSHIP_TRACKINGUSERANDPRODUCTS_H_ */
