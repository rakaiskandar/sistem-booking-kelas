#include "../interface/interface.h"

#ifndef AUTH_H
#define AUTH_H

int login(char *username, char *password);
char get_roles(char *username, char *password);
void display_password(char *password);

#endif