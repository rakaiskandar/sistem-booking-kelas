#include <stdio.h>
#include <string.h>
#include "utils.h"

void swap_book(books *a, books *b){	
	books temp = *a;
    *a = *b;
    *b = temp;
}

void swap_user(users *a, users *b){	
	users temp = *a;
	*a = *b;
	*b = temp;
}

int compare_nama_asc(const char *nama1, const char *nama2){
	return strcmp(nama1, nama2);
}

int compare_nama_desc(const char *nama1, const char *nama2){
	return strcmp(nama2, nama1);
}

int compare_tanggal_asc(const char *tgl1, const char *tgl2){
	int day1, month1, year1;
    int day2, month2, year2;

    sscanf(tgl1, "%d-%d-%d", &day1, &month1, &year1);
    sscanf(tgl2, "%d-%d-%d", &day2, &month2, &year2);

    // Compare years
    if (year1 < year2) return -1;
    if (year1 > year2) return 1;

    // Compare months
    if (month1 < month2) return -1;
    if (month1 > month2) return 1;

    // Compare days
    if (day1 < day2) return -1;
    if (day1 > day2) return 1;

    return 0;
}

int compare_tanggal_desc(const char *tgl1, const char *tgl2){
	return -compare_tanggal_asc(tgl1, tgl2);
}