#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "user.h"
#include "../utils/utils.h"

void booking(books b[], char *username){
	FILE *file, *file_class;
	classes c;

	int jumlah_booking;

	printf("Berapa kelas yang akan dibooking: ");
	scanf("%d", &jumlah_booking);

	for (int i = 0; i < jumlah_booking; i++){
		printf("Masukkan kode kelas: ");
		scanf("%s", &b[i].kode_kelas);
		printf("Masukkan prodi: ");
		scanf("%s", &b[i].prodi);
		printf("Masukkan fakultas: ");
		scanf("%s", &b[i].fakultas);

		strcpy(b[i].nama, username);
		strcpy(c.kode_kelas, b[i].kode_kelas);
		strcpy(c.gedung, b[i].fakultas);

		b[i].status_pemesanan = false;
	}

	file = fopen("data/data.txt", "a");
	file_class = fopen("data/kelas.txt", "a");

	if ((file == NULL) && (file_class == NULL)){
		fprintf(stderr, "Tidak dapat membuka file\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < jumlah_booking; i++){
		bool is_booked = false;

		rewind(file);

		while (fscanf(file_class, "%s %s", c.kode_kelas, c.gedung) == 2){
			if ((strcmp(b[i].kode_kelas, c.kode_kelas) == 0)){
				is_booked = true;
				printf("Kelas sudah dipesan, Coba cari kelas lain!\n");
				break;
			}
		}

		if (!is_booked){
			// Get current date
			time_t t;
			struct tm *tminfo;
			time(&t);
			tminfo = localtime(&t);
			
			// Modify the data as needed
			b[i].status_pemesanan = 1;
			strftime(b[i].tanggal, sizeof(b[i].tanggal), "%d-%m-%Y", tminfo);
			fprintf(file, "%s %s %s %s %d %s\n", b[i].kode_kelas, b[i].nama, b[i].prodi, b[i].fakultas, b[i].status_pemesanan, b[i].tanggal);
			fprintf(file_class, "%s %s\n", b[i].kode_kelas, b[i].fakultas);

			printf("Selamat, Booking Kelas Berhasil");
			printf("\n");
		}
	}

	fclose(file);
}

void cancel(char *username, int user){
	FILE *file = fopen("data/data.txt", "r+");
	books b;

	if (file == NULL){
		fprintf(stderr, "Tidak dapat membuka file\n");
		exit(EXIT_FAILURE);
	}

	int data_edited = 0;

	// Create a temporary filename
    char temp_filename[] = "data/book_tmp.txt";
    FILE *temp_file = fopen(temp_filename, "w");

    if (temp_file == NULL) {
        fclose(file);
        fprintf(stderr, "Tidak dapat membuka file temporary\n");
        exit(EXIT_FAILURE);
    }

	char ch[20];
	printf("Masukkan kode kelas: ");
	scanf("%s", &ch);

	while (fscanf(file, "%s %s %s %s %d %s", b.kode_kelas, b.nama, b.prodi, b.fakultas, &b.status_pemesanan, b.tanggal) == 6){
		if ((strcmp(b.nama, username) == 0) && (strcmp(b.kode_kelas, ch) == 0)){
			// Modify the data as needed
			b.status_pemesanan = 0;

			fprintf(temp_file, "%s %s %s %s %d %s\n", b.kode_kelas, b.nama, b.prodi, b.fakultas, b.status_pemesanan, b.tanggal);

			data_edited = 1; 
		}else{
			fprintf(temp_file, "%s %s %s %s %d %s\n", b.kode_kelas, b.nama, b.prodi, b.fakultas, b.status_pemesanan, b.tanggal);
		}
	}

	fclose(file);
	fclose(temp_file);

    // Remove the original file
    if (remove("data/data.txt") != 0) {
        perror("Error removing the original file");
        exit(EXIT_FAILURE);
    }

    // Rename the temporary file to the original filename
    if (rename(temp_filename, "data/data.txt") != 0) {
        perror("Error renaming the temporary file");
        exit(EXIT_FAILURE);
    }

	if (data_edited){
		printf("Data for kode kelas '%s' cancel successfully.\n", ch);
	}else{
		printf("Kode kelas '%s' not found in the file.\n", ch);
	}
}

void sort_record(books b[], char *username, int user)
{
	FILE *file = fopen("data/data.txt", "r");

    if (file == NULL) {
        fprintf(stderr, "Tidak dapat membuka file..\n");
        exit(EXIT_FAILURE);
    }

	int num_records = 0, pilihan;
	printf("[1] Ascending\n");
	printf("[2] Descending\n");
	printf("Pilih filter data: ");
	scanf("%d", &pilihan);

	while (num_records < user && fscanf(file, "%s %s %s %s %d %s", b[num_records].kode_kelas, b[num_records].nama, b[num_records].prodi, b[num_records].fakultas, &b[num_records].status_pemesanan, b[num_records].tanggal) == 6) {
        if ((strcmp(b[num_records].nama, username) == 0) && b[num_records].status_pemesanan != 0) {
            num_records++;
        }
    }

	fclose(file);

	if (num_records > 0){
		switch (pilihan){
			case 1:
				sorting(b, 0, num_records - 1, compare_tanggal_asc);
				break;
			case 2:
				sorting(b, 0, num_records - 1, compare_tanggal_desc);
				break;
		}

		printf("Data tersortir:\n");
        print_record(b, num_records);
	}else {
		printf("No records found in the file.\n");
	}
}

int partition(books b[], int left, int right, int (*compare)(const char *, const char *)) {
    char pivot_tanggal[50];
    strcpy(pivot_tanggal, b[right].tanggal);

    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (compare(b[j].tanggal, pivot_tanggal) <= 0) {
            i++;
            swap_book(&b[i], &b[j]);
        }
    }

    swap_book(&b[i + 1], &b[right]);

    return i + 1;
}

void sorting(books b[], int left, int right, int (*compare)(const char *, const char *)) {
    if (left < right) {
        int pivot_index = partition(b, left, right, compare);
        sorting(b, left, pivot_index - 1, compare);
        sorting(b, pivot_index + 1, right, compare);
    }
}

void print_record(books b[], int n){
	for (int i = 0; i < n; i++){
		printf("%s %s %s %s %d %s\n", b[i].kode_kelas, b[i].nama, b[i].prodi, b[i].fakultas, b[i].status_pemesanan, b[i].tanggal);
	}
	printf("\n");
}

void search_record(char *username)
{
	FILE *file;
	books b;

	char ch[8];
	printf("Masukkan kode kelas: ");
	scanf("%s", &ch);

	file = fopen("data/data.txt", "r");
	if (file == NULL){
		fprintf(stderr, "Tidak dapat membuka file\n");
		exit(EXIT_FAILURE);
	}

	while (fscanf(file, "%s %s %s %s %d %s", &b.kode_kelas, &b.nama, &b.prodi, &b.fakultas, &b.status_pemesanan, &b.tanggal) == 6){
		if ((strcmp(b.kode_kelas, ch) == 0) && (strcmp(b.nama, username) == 0)){
			printf("Data ditemukan!");
			printf("\nKode Kelas: %s", b.kode_kelas);
			printf("\nNama Pemesan: %s", b.nama);
			printf("\nProdi: %s", b.prodi);
			printf("\nFakultas: %s", b.fakultas);
			printf("\nStatus: %d", b.status_pemesanan);
			printf("\nTanggal: %s\n", b.tanggal);
			break;
		}
	}

	fclose(file);
}

void view_class(){
	FILE *file;
	classes c;

	file = fopen("data/kelas.txt", "r");
	if (file == NULL)
	{
		fprintf(stderr, "Tidak dapat membuka file\n");
        exit(EXIT_FAILURE);
	}

	while (fscanf(file, "%s %s", &c.kode_kelas, &c.gedung) == 2){
		printf("%s %s\n", c.kode_kelas, c.gedung);
	}

	fclose(file);
}

void view_record(char *username, int user)
{
	FILE *file;
	books b;

	file = fopen("data/data.txt", "r");
	if (file == NULL)
	{
		fprintf(stderr, "Tidak dapat membuka file\n");
        exit(EXIT_FAILURE);
	}

	int data_found = 0;

	while (fscanf(file, "%s %s %s %s %d %s", &b.kode_kelas, &b.nama, &b.prodi, &b.fakultas, &b.status_pemesanan, &b.tanggal) == 6){
		if ((strcmp(b.nama, username) == 0) && b.status_pemesanan != 0){
			printf("%s %s %s %s %d %s\n", b.kode_kelas, b.nama, b.prodi, b.fakultas, b.status_pemesanan, b.tanggal);
			data_found++;
		}
		
		if (data_found >= user){
			break;
		}
		
	}
	
	if (data_found == 0){
		printf("Kamu belum memesan kelas\n");
	}

	fclose(file);
}

void generate_report(char *username)
{
	FILE *file;
	books b;

	file = fopen("data/data.txt", "r");
	if (file == NULL){
		fprintf(stderr, "Tidak dapat membuka file\n");
		exit(EXIT_FAILURE);
	}

	printf("Detail Pemesanan:");
	printf("\nKode Kelas Nama Prodi\tFakultas Status Pemesanan  Tanggal");
	while (fscanf(file, "%s %s %s %s %d %s", &b.kode_kelas, &b.nama, &b.prodi, &b.fakultas, &b.status_pemesanan, &b.tanggal) == 6){
		if ((strcmp(b.nama, username) == 0) && b.status_pemesanan != 0){
			printf("\n%s \t   %s %s \t%s \t   %s \t  %s", b.kode_kelas, b.nama, b.prodi, b.fakultas, b.status_pemesanan? "true":"false", b.tanggal);
		}
	}
	printf("\n");

	fclose(file);
}