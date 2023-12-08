#include "../interface/interface.h"

#ifndef UTILS_H
#define UTILS_H

void swap_user(users *a, users *b);
void swap_book(books *a, books *b);
int compare_nama_asc(const char *nama1, const char *nama2);
int compare_nama_desc(const char *nama1, const char *nama2);
int compare_tanggal_asc(const char *tgl1, const char *tgl2);
int compare_tanggal_desc(const char *tgl1, const char *tgl2);

#endif