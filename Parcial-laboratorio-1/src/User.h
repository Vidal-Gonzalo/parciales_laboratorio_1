/*
 * User.h
 *
 *  Created on: 14 may 2022
 *      Author: gonza
 */

#ifndef USER_H_
#define USER_H_

#define MAX 10
#define LOW -2
#define FREE 0
#define OCCUPIED 1
#define MAX_USERS 13
#define MAX_EMAIL 25
#define MAX_PASSWORD 10
#define MAX_ADDRESS 50

typedef struct {
	int idUsuario;
	short int isEmpty;

	short int type;
	char email[MAX_EMAIL];
	char password[MAX_PASSWORD];
	char address[MAX_ADDRESS];
	int postalCode;
	int loggedIn;
} User;

int addUser(User *list, int len, int id, char name[], char lastname[],
		float price, int typeUser, char flycode[]);
int User_initializeUsers(User userList[], int size);
int User_printUsers(User UsersList[], int size);
int User_Login(User userList[], int size, int *userId);
int User_SearchSpace(User userList[], int size, int status);
int User_SearchFlightStatus(User userList[], int size,
		int statusFlight);
int User_Membership(User userList[], int size);
int User_Baja(User userList[], int size);
int User_Edit(User userList[], int size);
int User_PrintAllUsers(User userList[], int userSize);
int User_LowMembership(User userList[], int userSize, User user);
int User_SearchIndexPerId(User userList[], int size, int ID);
int User_AveragePrice(User userList[], int size);
int User_Sort(User UsersList[], int size, int order);
int User_SortByFlightcode(User UsersList[], int size, int order);
int User_HardcodeUser(char email[], char password[], char address[],
		int postalCode, int userType, User userList[], int size);
User User_ModificarUno(User s);
int User_LoadUser(User *user);

#endif /* USER_H_ */
