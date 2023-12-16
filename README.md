# Sistem Booking Kelas

## Deskripsi

Sistem Informasi Booking Kelas yang diimplementasikan dengan bahasa C. Program ini memiliki fitur simple menu interface, autentikasi sebagai user dan admin, booking kelas, batal booking kelas, cari dan sortir data, generate laporan pemesanan kelas, dan crud(create, read, update, delete) data.

## Fitur 
- Login
- Booking Kelas
- Batal Booking Kelas
- Cari Data Booking 
- Sortir Data Booking
- Generate Laporan Booking Kelas
- CRUD (create, read, update, delete) data user sebagai admin

## Cara Menjalankan
1. Clone project ini (jika punya git), jika tidak maka download zip melalui platform github.

```bash
git clone https://github.com/rakaiskandar/sistem-booking-kelas.git
```

2. Masuk ke project directory:

```bash
cd sistem-booking-kelas
cd src
```

3. Compile code dengan command `gcc`:

```bash
gcc include/user/user.c include/auth/auth.c include/admin/admin.c include/utils/utils.c main.c -o ../bin/main
```

4. Jalankan program, dengan mengeksekusi hasil dari compile:

```bash
../bin/main
```
5. Login dengan `username` dan `password`
```bash
untuk admin
username: admin
password: admin123

untuk user
username: kamu
password: kamu123
```
## Struktur Folder

- `src`: berisikan source code utama dan fitur - fitur program
- `bin`: berisikan file hasil compile yaitu `.exe`
- `data`: berisikan file `txt` untuk menyimpan data 

## License

[MIT](https://github.com/rakaiskandar/sistem-booking-kelas/blob/main/LICENSE)
