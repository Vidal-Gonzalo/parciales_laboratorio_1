/*
 * User.c
 *
 *  Created on: 14 may 2022
 *      Author: gonza
 */

#include "User.h"
#include "General.h"

static int idAI = 1000;
static int User_getUniqueId() {
	return idAI++;
}

/** \brief print the content of one element of User
 *
 * \param list User
 * \return int
 *
 */

void User_printOne(User s) {
	printf("ID %d\nEmail: %s\nDireccion: %s\nCodigo postal: %d\n", s.idUsuario,
			s.email, s.address, s.postalCode);
}

/** \brief To indicate that all position in the array are empty,
 * this function put the flag (isEmpty) in TRUE in all
 * position of the array
 * \param list User* Pointer to array of User
 * \param len int Array length
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */

int User_initializeUsers(User *userList, int size) {
	int r = -1;
	int i;

	if (userList != NULL && size > 0) {
		for (i = 0; i < size; i++) {
			userList[i].isEmpty = FREE;
		}
	}
	return r;
}

/** \brief Search free space in array list, load the no-generic data of the User, gives him an ID and
 *  add User's data.
 * \param list User* Pointer to array of User
 * \param len int Array length
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */

int User_Membership(User userList[], int size) {
	int r = -1;
	User auxUser;

	if (userList != NULL && size > 0) {
		int index = User_SearchSpace(userList, size, FREE);
		if (index != -1) {
			if (User_LoadUser(&auxUser) == 0) {
				auxUser.idUsuario = User_getUniqueId();
				auxUser.isEmpty = OCCUPIED;
				userList[index] = auxUser;
				r = 0;
			}
		}
	}

	return r;
}

int User_HardcodeUser(char email[], char password[], char address[],
		int postalCode, int userType, User userList[], int size) {
	int r = -1;
	User aux;
	int index = User_SearchSpace(userList, size, FREE);
	if (index != -1) {
		strncpy(aux.email, email, MAX_EMAIL);
		strncpy(aux.password, password, MAX_PASSWORD);
		strncpy(aux.address, address, MAX_ADDRESS);
		aux.postalCode = postalCode;
		aux.type = userType;
		aux.isEmpty = OCCUPIED;
		aux.idUsuario = User_getUniqueId();
		userList[index] = aux;
		r = 0;
	}

	return r;
}

int User_Login(User userList[], int size, int *userIndex) {
	int r = -1;
	char auxEmail[MAX_EMAIL];
	char auxPassword[MAX_PASSWORD];

	if (userList != NULL && size >= 0) {
		general_getEmail(auxEmail, MAX_EMAIL, "Correo electronico:\n",
				"Por favor, asegurese de que ingresa letras\n", 3);
		general_getAlphanumericWithMin(auxPassword, MAX_PASSWORD, 4,
				"Contrase?a:\n", "La contrase?a debe tener letras y numeros.\n",
				3);
		if (auxEmail != NULL && auxPassword != NULL) {
			for (int i = 0; i < size; i++) {
				if (strcmp(userList[i].email, auxEmail) == 0) {
					if (strcmp(userList[i].password, auxPassword) == 0) {
						if (userList[i].isEmpty != -2) {
							if (userList[i].type == 1) {
								r = 1;
							} else {
								if (userList[i].type == 2) {
									r = 2;
								}
							}
							userList[i].loggedIn = 1;
							*userIndex = i;
							break;
						}
					}
				} else {
					r = -2;
				}
			}
		}
	}

	return r;
}

/** \brief print the content of Products array
 *
 * \param list Product*
 * \param length int
 * \return int (1 OK -1 if products list is null or size less than 0)
 *
 */

int User_PrintAllUsers(User userList[], int userSize) {
	int r = -1;

	if (userList != NULL && userSize > 0) {
		for (int i = 0; i < userSize; i++) {
			if (userList[i].isEmpty == 1 || userList[i].isEmpty == -2) {
				printf("ID Usuario: %d\nCorreo electronico: %s\n",
						userList[i].idUsuario, userList[i].email);
				if (userList[i].isEmpty == -2) {
					printf("Estado: BAJA\n");
				} else {
					if (userList[i].isEmpty == 1) {
						printf("Estado: ACTIVO\n");
					}
				}
			}
		}
		r = 0;
	}
	return r;
}

/** \brief print the content of user array sorted by category and asks for the user an ID to search it
 * and remove it from the same array.
 *
 * \param list User*
 * \param length int
 * \param Struct user
 * \return int (1 OK -1 if products list is null or size less than 0)
 *
 */

int User_LowMembership(User userList[], int userSize, User user) {
	int r = -1;
	int indexToRemove;
	int ID = 0;

	if (userList != NULL) {
		if (userSize > 0) {
			User_PrintAllUsers(userList, userSize);
			if (utn_getNumero(
					"Ingrese el ID del usuario que desea dar de baja:\n",
					"Hubo un error\n", 0, 3, &ID) == 0) {
				indexToRemove = User_SearchIndexPerId(userList, userSize, ID);
				if (indexToRemove == -1) {
					printf("No se encontro el ID en la lista.\n");
					return r;
				} else {
					printf(
							"El usuario que desea dar de baja es el siguiente:\n");
					User_printOne(userList[indexToRemove]);

					if (confirmation(
							"?Esta seguro que quiere darlo de baja?(1-Si/Otro numero-No)\n",
							"Ha habido un error en relacion al numero ingresado. Intentelo nuevamente.\n")
							== 1) {
						userList[indexToRemove].isEmpty = LOW;
						r = 0;
					} else {
						r = -2;
					}
				}
			}

		}
	}
	return r;
}

/** \brief Search an especific space in the array
 *
 * \param list User*
 * \param len int
 * \param id status (to search)
 * \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
 find a User] - (0) if Ok
 *
 */

int User_SearchSpace(User userList[], int size, int status) {
	int r = -1;
	int i;

	if (userList != NULL && size > 0) {
		for (i = 0; i <= size; i++) {
			if (userList[i].isEmpty == status) {
				r = i;
				break;
			}
		}
	}
	return r;
}

/** \brief Loads non-generic data to an User auxiliar and returns it
 *
 * \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
 find a User] - (0) if Ok
 *
 */

int User_LoadUser(User *auxiliar) {
	int r = -1;

	if (general_getEmail(auxiliar->email, MAX_EMAIL, "Correo electronico:\n",
			"Ingrese un mail valido\n", 3) == 0) {
		if (general_getAlphanumericWithMin(auxiliar->password, MAX_PASSWORD, 4,
				"Contrase?a:\n", "La contrase?a debe tener letras y numeros.\n",
				3) == 0) {
			if (utn_getString(auxiliar->address, 50, "Direccion:\n",
					"Error, vuelva a intentar.\n", 3) == 0) {
				if (utn_getNumero("Codigo postal:\n",
						"Error, vuelva a intentar.\n", 1, 3,
						&auxiliar->postalCode) == 0) {
					if (utn_getShortInt("Tipo de usuario:\n",
							"Error, vuelva a intentar.\n", 1, 2, 3,
							&auxiliar->type) == 0) {
						r = 0;
						printf("Datos cargados correctamente\n");
					} else {
						printf("No se ha podido cargar el tipo de usuario\n");
					}
				} else {
					printf("No se ha podido cargar el codigo postal.\n");
				}
			} else {
				printf("No se ha podido cargar la direccion.\n");
			}
		} else {
			printf("No se ha podido cargar la contrase?a.\n");
		}
	} else {
		printf("No se ha podido cargar el email.\n");
	}

	return r;

}

/** \brief find a User by Id en returns the index position in UsersList.
 *
 * \param list User*
 * \param len int
 * \param id int
 * \return Return User index position or (-1) if [Invalid length or
 NULL pointer received or User not found]
 *
 */
int User_SearchIndexPerId(User userList[], int size, int ID) {
	int r = -1;
	int i;

	if (userList != NULL && size > 0) {
		for (i = 0; i < size; i++) {
			if (userList[i].idUsuario == ID && userList[i].isEmpty == OCCUPIED) {
				r = i;
				break;
			}
		}
	}

	return r;
}

