#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "auth.h"

int login(char *username, char *password)
{
	FILE *fp;
	users u;
	int is_login = 0;

	fp = fopen("../data/user.txt", "r");

	if (fp == NULL)
	{
		fprintf(stderr, "Tidak dapat membuka file\n");
		exit(EXIT_FAILURE);
	}

	while (fscanf(fp, "%s %s %s", &u.username, &u.password, &u.role) == 3)
	{
		if ((strcmp(u.username, username) == 0) && (strcmp(u.password, password) == 0))
		{
			is_login = 1;
			break;
		}
	}

	fclose(fp);

	return is_login;
}

char get_roles(char *username, char *password)
{
	FILE *fp;
	users u;
	int is_admin = 0;

	fp = fopen("../data/user.txt", "r");
	if (fp == NULL)
	{
		fprintf(stderr, "Tidak dapat membuka file\n");
		exit(EXIT_FAILURE);
	}

	while (fscanf(fp, "%s %s %s", &u.username, &u.password, &u.role) == 3)
	{
		if ((strcmp(u.username, username) == 0) && (strcmp(u.password, password) == 0) && (strcmp(u.role, "admin") == 0))
		{
			is_admin = 1;
			break;
		}
		else if ((strcmp(u.username, username) == 0) && (strcmp(u.password, password) == 0) && (strcmp(u.role, "user") == 0))
		{
			return is_admin;
			break;
		}
	}

	fclose(fp);

	return is_admin;
}

void display_password(char *password)
{
	int i = 0, length = sizeof(password) / sizeof(password[0]);
	char ch;

	while (1)
	{
		ch = _getch();

		if (ch == '\r')
		{
			break;
		}
		else if (ch == '\b' && i > 0)
		{
			i--;
			printf("\b \b");
		}
		else if (i < length)
		{
			password[i] = ch;
			i++;
			printf("*");
		}
	}

	password[i] = '\0';
	printf("\n");
}