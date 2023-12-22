#include "../interface/interface.h"

#ifndef USER_H
#define USER_H

void booking(books b[], char *username);
void retrieve_class(char *username);
void cancel(char *username);
void view_class();
void delete_class(char *kode_kelas);
void view_record(char *username, int user);
void sort_record(books b[], char *username, int user);
void sorting(books b[], int left, int right, int (*compare)(const char *, const char *));
void print_record(books b[], int n);
int partition(books b[], int left, int right, int (*compare)(const char *, const char *));
void search_record(char *username);
void generate_report(char *username, int user);

#endif