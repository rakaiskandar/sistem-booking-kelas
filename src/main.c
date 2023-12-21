#include <stdio.h>
#include <stdlib.h>
#include "include/user/user.h"
#include "include/auth/auth.h"
#include "include/admin/admin.h"
#include "include/interface/interface.h"

books b[100];
users u[100];

int total_book = 100, pilihan, total_user = 0;

int main(void)
{
	char username[12], password[12];
	int is_login, is_admin;

	do
	{
		printf(" ___       __   _______   ___       ________  ________  _____ ______   _______      \n");
		printf("|\\  \\     |\\  \\|\\  ___ \\ |\\  \\     |\\   ____\\|\\   __  \\|\\   _ \\  _   \\|\\  ___ \\     \n");
		printf("\\ \\  \\    \\ \\  \\ \\   __/|\\ \\  \\    \\ \\  \\___|\\ \\  \\|\\  \\ \\  \\\\\\__\\ \\  \\ \\   __/|\n");
		printf(" \\ \\  \\  __\\ \\  \\ \\  \\_|/_\\ \\  \\    \\ \\  \\    \\ \\  \\\\\\  \\ \\  \\|__| \\  \\ \\  \\_|/__\n");
		printf("  \\ \\  \\|\\__\\_\\  \\ \\  \\_|\\ \\ \\  \\____\\ \\  \\____\\ \\  \\\\\\  \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\ \n");
		printf("   \\ \\____________\\ \\_______\\ \\_______\\ \\_______\\ \\_______\\ \\__\\    \\ \\__\\ \\_______\\\n");
		printf("    \\|____________|\\|_______|\\|_______|\\|_______|\\|_______|\\|__|     \\|__|\\|_______|\n");
		printf("                                                                                     \n");
		printf("Sistem Informasi Penyewaan Kelas\n");
		printf("Masukkan username: ");
		scanf("%s", &username);
		printf("Masukkan password: ");
		display_password(password);

		is_login = login(username, password);
		is_admin = get_roles(username, password);

		if (is_login != 1)
		{
			printf("Username atau password salah!\n");
			system("cls");
		}

	} while (is_login != 1);

	if (is_admin == 0)
	{
		do
		{
			printf("==================================\n");
			printf("\tSistem Booking Kelas\n");
			printf("\tSelamat Datang %s\n", username);
			printf("==================================\n");
			printf("1. Pesan Kelas");
			printf("\n2. Lihat Pesanan");
			printf("\n3. Lihat Kelas Yang Sudah Dipesan");
			printf("\n4. Batalkan Pesanan");
			printf("\n5. Kembalikan Kelas");
			printf("\n6. Cari Pesanan");
			printf("\n7. Sortir Pesanan");
			printf("\n8. Inisiasi Laporan");
			printf("\n0. Keluar");

			printf("\nPilih Menu: ");
			scanf("%d", &pilihan);
			switch (pilihan)
			{
			case 1:
				booking(b, username);
				system("pause");
				system("cls");
				break;
			case 2:
				view_record(username, total_book);
				system("pause");
				system("cls");
				break;
			case 3:
				view_class();
				system("pause");
				system("cls");
				break;
			case 4:
				cancel(username);
				system("pause");
				system("cls");
				break;
			case 5:
				retrieve_class(username);
				system("pause");
				system("cls");
				break;
			case 6:
				search_record(username);
				system("pause");
				system("cls");
				break;
			case 7:
				sort_record(b, username, total_book);
				system("pause");
				system("cls");
				break;
			case 8:
				generate_report(username);
				system("pause");
				system("cls");
				break;
			case 0:
				exit(0);
				break;
			default:
				printf("Pilihan anda salah!");
				break;
			}
		} while (pilihan != 0);
	}
	else
	{
		total_user = count_user(&total_user);
		do
		{
			printf("==================================\n");
			printf("\tSistem Booking Kelas\n");
			printf("\tSelamat Datang %s\n", username);
			printf("==================================\n");
			printf("1. Lihat Semua User");
			printf("\n2. Tambah User");
			printf("\n3. Edit User");
			printf("\n4. Delete User");
			printf("\n5. Sortir User");
			printf("\n6. Cari User");
			printf("\n7. Lihat Semua Pemesanan");
			printf("\n8. Hapus Pemesanan");
			printf("\n9. Cari Data Pemesanan");
			printf("\n10. Sortir Data Pemesanan");
			printf("\n0. Keluar");

			printf("\nPilih Menu: ");
			scanf("%d", &pilihan);
			switch (pilihan)
			{
			case 1:
				view_user(total_user);
				system("pause");
				system("cls");
				break;
			case 2:
				add_user(u);
				system("pause");
				system("cls");
				break;
			case 3:
				edit_user();
				system("pause");
				system("cls");
				break;
			case 4:
				delete_user();
				system("pause");
				system("cls");
				break;
			case 5:
				sort_user(u, total_user);
				system("pause");
				system("cls");
				break;
			case 6:
				search_user();
				system("pause");
				system("cls");
				break;
			case 7:
				view_all_records(total_book);
				system("pause");
				system("cls");
				break;
			case 8:
				delete_records();
				system("pause");
				system("cls");
				break;
			case 9:
				search_all_records();
				system("pause");
				system("cls");
				break;
			case 10:
				sort_all_records(b, total_book);
				system("pause");
				system("cls");
				break;
			case 0:
				exit(0);
				break;
			default:
				printf("Pilihan anda salah!");
				break;
			}
		} while (pilihan != 0);
	}
}