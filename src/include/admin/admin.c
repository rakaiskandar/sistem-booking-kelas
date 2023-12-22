#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"
#include "../utils/utils.h"

int count_user(int *user_count)
{
	FILE *fp;
	users u;

	fp = fopen("../data/user.txt", "r");

	if (fp == NULL)
	{
		fprintf(stderr, "Tidak dapat membuka file.\n");
		exit(EXIT_FAILURE);
	}

	*user_count = 0;

	while (fscanf(fp, "%s %s %s", u.username, u.password, u.role) == 3)
	{
		(*user_count)++;
	}

	fclose(fp);

	return *user_count;
}

void view_user(int user)
{
	FILE *file;
	users u;

	file = fopen("../data/user.txt", "r");
	if (file == NULL)
	{
		fprintf(stderr, "Tidak dapat membuka file\n");
		exit(EXIT_FAILURE);
	}

	int data_found = 0;

	printf("Username \tPassword \tRole\n");
	while (fscanf(file, "%s %s %s", &u.username, &u.password, &u.role) == 3)
	{
		if (strcmp(u.role, "user") == 0)
		{
			printf("%8s %14s %12s\n", u.username, u.password, u.role);
			data_found++;
		}

		if (data_found >= user)
		{
			break;
		}
	}

	fclose(file);
}

void add_user(users u[])
{
	FILE *file;
	int jumlah_user;

	printf("Berapa user yang akan ditambah: ");
	scanf("%d", &jumlah_user);

	for (int i = 0; i < jumlah_user; i++)
	{
		printf("Masukkan username: ");
		scanf("%s", &u[i].username);
		printf("Masukkan password: ");
		scanf("%s", &u[i].password);
		strcpy(u[i].role, "user");
	}

	file = fopen("../data/user.txt", "a");

	if (file == NULL)
	{
		fprintf(stderr, "Tidak dapat membuka file\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < jumlah_user; i++)
	{
		fprintf(file, "%s %s %s\n", u[i].username, u[i].password, u[i].role);
	}

	printf("Data user berhasil ditambahkan!");
	printf("\n");

	fclose(file);
}

void edit_user()
{
	FILE *file = fopen("../data/user.txt", "r");
	users u;

	if (file == NULL)
	{
		fprintf(stderr, "Tidak dapat membuka file\n");
		exit(EXIT_FAILURE);
	}

	int data_edited = 0;

	char username[20], password_new[20], username_new[20];
	printf("Masukkan username yang akan diedit: ");
	scanf("%s", &username);

	// Create a temporary filename
	char temp_filename[] = "../data/user_tmp.txt";
	FILE *temp_file = fopen(temp_filename, "w");

	if (temp_file == NULL)
	{
		fclose(file);
		fprintf(stderr, "Tidak dapat membuka file temporary\n");
		exit(EXIT_FAILURE);
	}

	while (fscanf(file, "%s %s %s", u.username, u.password, u.role) == 3)
	{
		if ((strcmp(u.role, "user") == 0) && (strcmp(u.username, username) == 0))
		{

			// Modify the data as needed
			printf("Masukkan username baru: ");
			scanf("%s", &username_new);
			printf("Masukkan password baru: ");
			scanf("%s", &password_new);

			strcpy(u.username, username_new);
			strcpy(u.password, password_new);

			// Write the modified data to the temporary file
			fprintf(temp_file, "%s %s %s\n", u.username, u.password, u.role);

			data_edited = 1;
		}
		else
		{
			// Write the unchanged data to the temporary file
			fprintf(temp_file, "%s %s %s\n", u.username, u.password, u.role);
		}
	}

	fclose(file);
	fclose(temp_file);

	// Remove the original file
	if (remove("../data/user.txt") != 0)
	{
		perror("Error removing the original file");
		exit(EXIT_FAILURE);
	}

	// Rename the temporary file to the original filename
	if (rename(temp_filename, "../data/user.txt") != 0)
	{
		perror("Error renaming the temporary file");
		exit(EXIT_FAILURE);
	}

	if (data_edited)
	{
		printf("Data '%s' berhasil diupdate.\n", username_new);
	}
	else
	{
		printf("'%s' tidak ditemukan di file.\n", username_new);
	}
}

void delete_user()
{
	FILE *file = fopen("../data/user.txt", "r+");

	if (file == NULL)
	{
		fprintf(stderr, "Tidak dapat membuka file\n");
		exit(EXIT_FAILURE);
	}

	users u;
	char username_delete[20];

	printf("Masukkan username yang ingin dihapus: ");
	scanf("%s", username_delete);

	// Create a temporary filename
	char temp_filename[] = "../data/user_tmp.txt";

	FILE *temp_file = fopen(temp_filename, "w");
	if (temp_file == NULL)
	{
		fclose(file);
		fprintf(stderr, "Tidak dapat membuka file temporary\n");
		exit(EXIT_FAILURE);
	}

	int data_deleted = 0;

	// Read and copy data, excluding the record to be deleted
	while (fscanf(file, "%s %s %s", u.username, u.password, u.role) == 3)
	{
		if (strcmp(u.username, username_delete) == 0)
		{
			data_deleted = 1;
		}
		else
		{
			fprintf(temp_file, "%s %s %s\n", u.username, u.password, u.role);
		}
	}

	fclose(file);
	fclose(temp_file);

	if (!data_deleted)
	{
		remove(temp_filename); // Remove the temporary file if no data was deleted
		printf("'%s' tidak ditemukan.\n", username_delete);
	}
	else
	{
		// Remove the original file
		if (remove("../data/user.txt") != 0)
		{
			perror("Error removing the original file");
			exit(EXIT_FAILURE);
		}

		// Rename the temporary file to the original filename
		if (rename(temp_filename, "../data/user.txt") != 0)
		{
			perror("Error renaming the temporary file");
			exit(EXIT_FAILURE);
		}

		printf("Data untuk '%s' berhasil dihapus.\n", username_delete);
	}
}

void sort_user(users u[], int user)
{
	FILE *file = fopen("../data/user.txt", "r");

	if (file == NULL)
	{
		fprintf(stderr, "Tidak dapat membuka file..\n");
		exit(EXIT_FAILURE);
	}

	int num_records = 0, pilihan;
	printf("[1] Ascending\n");
	printf("[2] Descending\n");
	printf("Pilih filter data: ");
	scanf("%d", &pilihan);

	while (num_records < user && fscanf(file, "%s %s %s", u[num_records].username, u[num_records].password, u[num_records].role) == 3)
	{
		if (strcmp(u[num_records].role, "user") == 0)
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
			sorting_user(u, 0, num_records - 1, compare_nama_asc);
			break;
		case 2:
			sorting_user(u, 0, num_records - 1, compare_nama_desc);
			break;
		}

		file = fopen("../data/user.txt", "w");

		if (file == NULL)
		{
			fprintf(stderr, "Tidak dapat membuka file..\n");
			exit(EXIT_FAILURE);
		}

		for (int i = 0; i < num_records; i++)
		{
			fprintf(file, "%s %s %s\n", u[i].username, u[i].password, u[i].role);
		}

		fclose(file);
		
		printf("Data tersortir:\n");
		print_record_user(u, num_records);
	}
	else
	{
		printf("Data tidak ditemukan.\n");
	}
}

void print_record_user(users u[], int n)
{
	printf("Username \tPassword \tRole\n");
	for (int i = 0; i < n; i++)
	{
		printf("%8s %14s %12s\n", u[i].username, u[i].password, u[i].role);
	}
	printf("\n");
}

void print_record_book(books b[], int n)
{
	printf("Kode Kelas Nama Prodi\t Fakultas Status Pemesanan   Tanggal\n");
	for (int i = 0; i < n; i++)
	{
		printf("%10s %2s %2s %8s %18s %12s\n", b[i].kode_kelas, b[i].nama, b[i].prodi, b[i].fakultas, b[i].status_pemesanan ? "true" : "false", b[i].tanggal);
	}
	printf("\n");
}

void sorting_user(users u[], int left, int right, int (*compare)(const char *, const char *))
{
	if (left < right)
	{
		int pivot_index = partition_user(u, left, right, compare);
		sorting_user(u, left, pivot_index - 1, compare);
		sorting_user(u, pivot_index + 1, right, compare);
	}
}

int partition_user(users u[], int left, int right, int (*compare)(const char *, const char *))
{
	char pivot_nama[50];
	strcpy(pivot_nama, u[right].username);

	int i = left - 1;

	for (int j = left; j < right; j++)
	{
		if (compare(u[j].username, pivot_nama) <= 0)
		{
			i++;
			swap_user(&u[i], &u[j]);
		}
	}

	swap_user(&u[i + 1], &u[right]);

	return i + 1;
}

void sorting_book(books b[], int left, int right, int (*compare)(const char *, const char *))
{
	if (left < right)
	{
		int pivot_index = partition_book(b, left, right, compare);
		sorting_book(b, left, pivot_index - 1, compare);
		sorting_book(b, pivot_index + 1, right, compare);
	}
}

int partition_book(books b[], int left, int right, int (*compare)(const char *, const char *))
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

void search_user()
{
	FILE *file;
	users u;

	char username[12];
	printf("Masukkan nama user: ");
	scanf("%s", &username);

	file = fopen("../data/user.txt", "r");

	if (file == NULL)
	{
		fprintf(stderr, "Tidak dapat membuka file\n");
		exit(EXIT_FAILURE);
	}

	while (fscanf(file, "%s %s %s", u.username, u.password, u.role) == 3)
	{
		if ((strcmp(u.role, "user") == 0) && (strcmp(u.username, username) == 0))
		{
			printf("Data ditemukan!\n");
			printf("Username: %s\n", u.username);
			printf("Password: %s\n", u.password);
			break;
		}
	}

	fclose(file);
}

void delete_records()
{
	FILE *file = fopen("../data/data.txt", "r+");

	if (file == NULL)
	{
		fprintf(stderr, "Tidak dapat membuka file\n");
		exit(EXIT_FAILURE);
	}

	books b;
	char kode_kelas[20];

	printf("Masukkan kode kelas pemesanan yang akan dihapus: ");
	scanf("%s", &kode_kelas);

	// Create a temporary filename
	char temp_filename[] = "../data/hapus_tmp.txt";
	FILE *temp_file = fopen(temp_filename, "w");
	if (temp_file == NULL)
	{
		fclose(file);
		fprintf(stderr, "Tidak dapat membuka file temporary\n");
		exit(EXIT_FAILURE);
	}

	int data_deleted = 0;

	// Read and copy data, excluding the record to be deleted
	while (fscanf(file, "%s %s %s %s %d %s", b.kode_kelas, b.nama, b.prodi, b.fakultas, &b.status_pemesanan, b.tanggal) == 6)
	{
		if (strcmp(b.kode_kelas, kode_kelas) == 0)
		{
			data_deleted = 1;
		}
		else
		{
			fprintf(temp_file, "%s %s %s %s %d %s\n", b.kode_kelas, b.nama, b.prodi, b.fakultas, b.status_pemesanan, b.tanggal);
		}
	}

	fclose(file);
	fclose(temp_file);

	if (!data_deleted)
	{
		// Remove the temporary file if no data was deleted
		remove(temp_filename);
		printf("'%s' tidak ditemukan.\n", kode_kelas);
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

		printf("Data untuk '%s' berhasil dihapus.\n", kode_kelas);
	}
}

void view_all_records(int user)
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

	printf("Kode Kelas Nama  Prodi\t Fakultas Status Pemesanan   Tanggal\n");
	while (fscanf(file, "%s %s %s %s %d %s", &b.kode_kelas, &b.nama, &b.prodi, &b.fakultas, &b.status_pemesanan, &b.tanggal) == 6)
	{
		printf("%10s %2s %4s %8s %18s %12s\n", b.kode_kelas, b.nama, b.prodi, b.fakultas, b.status_pemesanan ? "true" : "false", b.tanggal);
		data_found++;

		if (data_found >= user)
		{
			break;
		}
	}

	if (data_found == 0)
	{
		printf("Tidak ada data pemesanan\n");
	}

	fclose(file);
}

void search_all_records()
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
		if (strcmp(b.kode_kelas, ch) == 0)
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

void sort_all_records(books b[], int user)
{
	FILE *file = fopen("../data/data.txt", "r");

	if (file == NULL)
	{
		fprintf(stderr, "Tidak dapat membuka file..\n");
		exit(EXIT_FAILURE);
	}

	int num_records = 0, pilihan;
	printf("[1] Ascending\n");
	printf("[2] Descending\n");
	printf("Pilih filter data: ");
	scanf("%d", &pilihan);

	while (num_records < user && fscanf(file, "%s %s %s %s %d %s", b[num_records].kode_kelas, b[num_records].nama, b[num_records].prodi, b[num_records].fakultas, &b[num_records].status_pemesanan, b[num_records].tanggal) == 6)
	{
		num_records++;
	}

	fclose(file);

	if (num_records > 0)
	{
		switch (pilihan)
		{
		case 1:
			sorting_book(b, 0, num_records - 1, compare_tanggal_asc);
			break;
		case 2:
			sorting_book(b, 0, num_records - 1, compare_tanggal_desc);
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
		print_record_book(b, num_records);
	}
	else
	{
		printf("Data tidak ditemukan.\n");
	}
}
