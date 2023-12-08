#include "../interface/interface.h"

#ifndef ADMIN_H
#define ADMIN_H

void print_record_user(users u[], int n);
void print_record_book(books b[], int n);
void sorting_user(users u[], int left, int right, int (*compare)(const char *, const char *));
int partition_user(users u[], int left, int right, int (*compare)(const char *, const char *));
void sorting_book(books b[], int left, int right, int (*compare)(const char *, const char *));
int partition_book(books b[], int left, int right, int (*compare)(const char *, const char *));
void sort_user(users u[], int user);
void view_user(int user);
int count_user(int *user_count);
void add_user(users u[]);
void edit_user();
void delete_user();
void search_user();
void delete_records();
void view_all_records(int user);
void search_all_records();
void sort_all_records(books b[], int user);

#endif