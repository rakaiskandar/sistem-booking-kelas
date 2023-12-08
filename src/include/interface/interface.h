#include <stdbool.h>

#ifndef INTERFACE_H
#define INTERFACE_H

typedef struct Users{
    char username[12];
    char password[12];
    char role[10];
} users;

typedef struct Book{
	char kode_kelas[20];
    char prodi[20];
    char nama[20];
	char fakultas[20];
    char tanggal[20];
    bool status_pemesanan;
} books;

typedef struct Class{
   char kode_kelas[20];
   char gedung[20];
} classes;

#endif