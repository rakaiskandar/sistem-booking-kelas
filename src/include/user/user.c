#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "user.h"
#include "../utils/utils.h"

void booking(books b[], char *username)
{
	FILE *file, *file_class;
	classes c;

	int jumlah_booking;

	printf("Berapa kelas yang akan dibooking: ");
	scanf("%d", &jumlah_booking);

	for (int i = 0; i < jumlah_booking; i++)
	{
		printf("Masukkan kode kelas: ");
		scanf("%s", &b[i].kode_kelas);
		printf("Masukkan prodi pemesan: ");
		scanf("%s", &b[i].prodi);
		printf("Masukkan gedung kelas: ");
		scanf("%s", &b[i].fakultas);

		strcpy(b[i].nama, username);
		strcpy(c.kode_kelas, b[i].kode_kelas);
		strcpy(c.gedung, b[i].fakultas);

		b[i].status_pemesanan = false;
	}

	file = fopen("../data/data.txt", "a");
	file_class = fopen("../data/kelas.txt", "a");

	if ((file == NULL) && (file_class == NULL))
	{
		fprintf(stderr, "Tidak dapat membuka file\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < jumlah_booking; i++)
	{
		bool is_booked = false;

		rewind(file_class);

		while (fscanf(file_class, "%s %s", c.kode_kelas, c.gedung) == 2)
		{
			if ((strcmp(b[i].kode_kelas, c.kode_kelas) == 0))
			{
				is_booked = true;
				printf("Kelas sudah dipesan, Coba cari kelas lain!\n");
				break;
			}
		}

		if (!is_booked)
		{
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

			printf("Selamat, Booking Kelas Berhasil!!");
			printf("\n");
		}
	}

	fclose(file);
	fclose(file_class);
}

void cancel(char *username)
{
	FILE *file = fopen("../data/data.txt", "r+");

	books b;

	if (file == NULL)
	{
		fprintf(stderr, "Tidak dapat membuka file\n");
		exit(EXIT_FAILURE);
	}

	int data_edited = 0;

	// Create a temporary filename
	char temp_filename[] = "../data/book_tmp.txt";
	FILE *temp_file = fopen(temp_filename, "w");

	if (temp_file == NULL)
	{
		fclose(file);
		fprintf(stderr, "Tidak dapat membuka file temporary\n");
		exit(EXIT_FAILURE);
	}

	char ch[20];
	printf("Masukkan kode kelas: ");
	scanf("%s", &ch);

	while (fscanf(file, "%s %s %s %s %d %s", b.kode_kelas, b.nama, b.prodi, b.fakultas, &b.status_pemesanan, b.tanggal) == 6)
	{
		if ((strcmp(b.nama, username) == 0) && (strcmp(b.kode_kelas, ch) == 0))
		{
			b.status_pemesanan = 0;

			fprintf(temp_file, "%s %s %s %s %d %s\n", b.kode_kelas, b.nama, b.prodi, b.fakultas, b.status_pemesanan, b.tanggal);

			data_edited = 1;
			delete_class(ch);
		}
		else
		{
			fprintf(temp_file, "%s %s %s %s %d %s\n", b.kode_kelas, b.nama, b.prodi, b.fakultas, b.status_pemesanan, b.tanggal);
		}
	}

	fclose(file);
	fclose(temp_file);

	if (!data_edited)
	{
		remove(temp_filename);
		printf("Kode kelas '%s' tidak ditemukan\n", ch);
	}
	else
	{
		// Remove the original file
		if (remove("../data/data.txt") != 0)
		{
			perror("Error removing the original file");
			exit(EXIT_FAILURE);
		}
		// Rename the temporary file to the original filename
		if (rename(temp_filename, "../data/data.txt") != 0)
		{
			perror("Error renaming the temporary file");
			exit(EXIT_FAILURE);
		}

		printf("Pemesanan kode kelas '%s' berhasil dibatalkan.\n", ch);
	}
}

void retrieve_class(char *username)
{
	FILE *file = fopen("../data/data.txt", "r+");

	books b;

	if (file == NULL)
	{
		fprintf(stderr, "Tidak dapat membuka file\n");
		exit(EXIT_FAILURE);
	}

	int data_edited = 0;

	// Create a temporary filename
	char temp_filename[] = "../data/book_tmp.txt";
	FILE *temp_file = fopen(temp_filename, "w");

	if (temp_file == NULL)
	{
		fclose(file);
		fprintf(stderr, "Tidak dapat membuka file temporary\n");
		exit(EXIT_FAILURE);
	}

	char ch[20];
	printf("Masukkan kode kelas: ");
	scanf("%s", &ch);

	while (fscanf(file, "%s %s %s %s %d %s", b.kode_kelas, b.nama, b.prodi, b.fakultas, &b.status_pemesanan, b.tanggal) == 6)
	{
		if ((strcmp(b.nama, username) == 0) && (strcmp(b.kode_kelas, ch) == 0))
		{
			data_edited = 1;
			delete_class(ch);
		}
		else
		{
			fprintf(temp_file, "%s %s %s %s %d %s\n", b.kode_kelas, b.nama, b.prodi, b.fakultas, b.status_pemesanan, b.tanggal);
		}
	}

	fclose(file);
	fclose(temp_file);

	if (!data_edited)
	{
		remove(temp_filename);
		printf("Kode kelas '%s' tidak ditemukan\n", ch);
	}
	else
	{
		// Remove the original file
		if (remove("../data/data.txt") != 0)
		{
			perror("Error removing the original file");
			exit(EXIT_FAILURE);
		}
		// Rename the temporary file to the original filename
		if (rename(temp_filename, "../data/data.txt") != 0)
		{
			perror("Error renaming the temporary file");
			exit(EXIT_FAILURE);
		}

		printf("Kelas '%s' dikembalikan.\n", ch);
	}
}

void sort_record(books b[], char *username, int user)
{
	FILE *file = fopen("../data/data.txt", "r");
	int num_records = 0, pilihan;

	if (file == NULL)
	{
		fprintf(stderr, "Tidak dapat membuka file..\n");
		exit(EXIT_FAILURE);
	}

	printf("[1] Ascending\n");
	printf("[2] Descending\n");
	printf("Pilih filter data: ");
	scanf("%d", &pilihan);

	while (num_records < user && fscanf(file, "%s %s %s %s %d %s", b[num_records].kode_kelas, b[num_records].nama, b[num_records].prodi, b[num_records].fakultas, &b[num_records].status_pemesanan, b[num_records].tanggal) == 6)
	{
		if ((strcmp(b[num_records].nama, username) == 0) && b[num_records].status_pemesanan != 0)
		{
			num_records++;
		}
	}

	fclose(file);

	if (num_records > 0)
	{
		switch (pilihan)
		{
		case 1:
			sorting(b, 0, num_records - 1, compare_tanggal_asc);
			break;
		case 2:
			sorting(b, 0, num_records - 1, compare_tanggal_desc);
			break;
		}

		file = fopen("../data/data.txt", "w");

		if (file == NULL)
		{
			fprintf(stderr, "Tidak dapat membuka file..\n");
			exit(EXIT_FAILURE);
		}

		for (int i = 0; i < num_records; i++)
		{
			fprintf(file, "%s %s %s %s %d %s\n", b[i].kode_kelas, b[i].nama, b[i].prodi, b[i].fakultas, b[i].status_pemesanan, b[i].tanggal);
		}

		fclose(file);

		printf("Data tersortir:\n");
		print_record(b, num_records);
	}
	else
	{
		printf("Kamu belum memesan kelas\n");
	}
}

int partition(books b[], int left, int right, int (*compare)(const char *, const char *))
{
	char pivot_tanggal[50];
	strcpy(pivot_tanggal, b[right].tanggal);

	int i = left - 1;

	for (int j = left; j < right; j++)
	{
		if (compare(b[j].tanggal, pivot_tanggal) <= 0)
		{
			i++;
			swap_book(&b[i], &b[j]);
		}
	}

	swap_book(&b[i + 1], &b[right]);

	return i + 1;
}

void sorting(books b[], int left, int right, int (*compare)(const char *, const char *))
{
	if (left < right)
	{
		int pivot_index = partition(b, left, right, compare);
		sorting(b, left, pivot_index - 1, compare);
		sorting(b, pivot_index + 1, right, compare);
	}
}

void print_record(books b[], int n)
{
	printf("Kode Kelas Nama Prodi\t Gedung Status Pemesanan   Tanggal\n");
	for (int i = 0; i < n; i++)
	{
		printf("%10s %2s %2s %8s %18s %12s\n", b[i].kode_kelas, b[i].nama, b[i].prodi, b[i].fakultas, b[i].status_pemesanan ? "true" : "false", b[i].tanggal);
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

	file = fopen("../data/data.txt", "r");
	if (file == NULL)
	{
		fprintf(stderr, "Tidak dapat membuka file\n");
		exit(EXIT_FAILURE);
	}

	while (fscanf(file, "%s %s %s %s %d %s", &b.kode_kelas, &b.nama, &b.prodi, &b.fakultas, &b.status_pemesanan, &b.tanggal) == 6)
	{
		if ((strcmp(b.kode_kelas, ch) == 0) && (strcmp(b.nama, username) == 0))
		{
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

void view_class()
{
	FILE *file;
	classes c;

	file = fopen("../data/kelas.txt", "r");
	if (file == NULL)
	{
		fprintf(stderr, "Tidak dapat membuka file\n");
		exit(EXIT_FAILURE);
	}

	printf("Kode Kelas Gedung\n");
	while (fscanf(file, "%s %s", &c.kode_kelas, &c.gedung) == 2)
	{
		printf("%10s %4s\n", c.kode_kelas, c.gedung);
	}

	fclose(file);
}

void delete_class(char *kode_kelas)
{
	FILE *file = fopen("../data/kelas.txt", "r+");

	classes c;

	if (file == NULL)
	{
		fprintf(stderr, "Tidak dapat membuka file\n");
		exit(EXIT_FAILURE);
	}

	int data_edited = 0;

	// Create a temporary filename
	char temp_filename[] = "../data/class_tmp.txt";
	FILE *temp_file = fopen(temp_filename, "w");

	if (temp_file == NULL)
	{
		fclose(file);
		fprintf(stderr, "Tidak dapat membuka file temporary\n");
		exit(EXIT_FAILURE);
	}

	while (fscanf(file, "%s %s", &c.kode_kelas, &c.gedung) == 2)
	{
		if (strcmp(c.kode_kelas, kode_kelas) == 0)
		{
			data_edited = 1;
		}
		else
		{
			fprintf(temp_file, "%s %s\n", c.kode_kelas, c.gedung);
		}
	}

	fclose(file);
	fclose(temp_file);

	if (!data_edited)
	{
		remove(temp_filename);
	}
	else
	{
		// Remove the original file
		if (remove("../data/kelas.txt") != 0)
		{
			perror("Error removing the original file");
			exit(EXIT_FAILURE);
		}

		// Rename the temporary file to the original filename
		if (rename(temp_filename, "../data/kelas.txt") != 0)
		{
			perror("Error renaming the temporary file");
			exit(EXIT_FAILURE);
		}
	}
}

void view_record(char *username, int user)
{
	FILE *file;
	books b;

	file = fopen("../data/data.txt", "r");
	if (file == NULL)
	{
		fprintf(stderr, "Tidak dapat membuka file\n");
		exit(EXIT_FAILURE);
	}

	int data_found = 0;
	while (fscanf(file, "%s %s %s %s %d %s", &b.kode_kelas, &b.nama, &b.prodi, &b.fakultas, &b.status_pemesanan, &b.tanggal) == 6)
	{
		if ((strcmp(b.nama, username) == 0) && b.status_pemesanan != 0)
		{
			printf("%s %s %s %s %d %s\n", b.kode_kelas, b.nama, b.prodi, b.fakultas, b.status_pemesanan, b.tanggal);
			data_found++;
		}

		if (data_found >= user)
		{
			break;
		}
	}

	if (data_found == 0)
	{
		printf("Kamu belum memesan kelas\n");
	}

	fclose(file);
}

void generate_report(char *username, int user)
{
	FILE *file;
	books b;

	file = fopen("../data/data.txt", "r");
	if (file == NULL)
	{
		fprintf(stderr, "Tidak dapat membuka file\n");
		exit(EXIT_FAILURE);
	}

	int data_found = 0;

	printf("Detail Pemesanan:\n");
	while (fscanf(file, "%s %s %s %s %d %s", &b.kode_kelas, &b.nama, &b.prodi, &b.fakultas, &b.status_pemesanan, &b.tanggal) == 6)
	{
		if ((strcmp(b.nama, username) == 0) && b.status_pemesanan != 0)
		{
			printf("\n%10s %2s %2s %8s %18s %12s", b.kode_kelas, b.nama, b.prodi, b.fakultas, b.status_pemesanan ? "true" : "false", b.tanggal);
			data_found++;
		}

		if (data_found >= user)
		{
			break;
		}
	}

	if (data_found == 0)
	{
		printf("Kamu belum memesan kelas\n");
	}
	else
	{
		printf("\nKode Kelas Nama Prodi\t Fakultas Status Pemesanan   Tanggal\n"); 
	}

	printf("\n");

	fclose(file);
}