#include <stdio.h>
#include <string.h>

#define MAX_MAHASISWA 100           // jumlah maksimum data mahasiswa yang dapat disimpan
#define FILE_NAME "data_mahasiswa.txt" // nama file untuk menyimpan data mahasiswa

// Struktur data mahasiswa yang memiliki atribut nama, nim, alamat, kelas dan tempat tanggal lahir
struct Mahasiswa
{
    char nama[50];
    char nim[20];
    char alamat[100];
    char kelas[10];
    char tempatTanggalLahir[50];
};

// Array yang berguna untuk menyimpan data mahasiswa sebanyak max mahasiswa. max mahasiswa sendiri sudah ditentutukan dari awal yaitu 100.
struct Mahasiswa dataMahasiswa[MAX_MAHASISWA];
int jumlahMahasiswa = 0; // Variabel yng berguna untuk mendeteksi jumlah data mahasiswa yang disimpan

// Fungsi untuk menyimpan data mahasiswa dari array jumlahMahasiswa ke dalam file "data_mahasiswa.txt" yang udah didefinisikan diawal
void simpanDataKeFile()
{
    FILE *file = fopen(FILE_NAME, "w"); // membuka file dalam mode w (menghapus data yang sudah ada dan menambah data baru)
    if (file == NULL)
    {
        printf("Gagal membuka file untuk menyimpan data.\n");
        return;
    }
    for (int i = 0; i < jumlahMahasiswa; i++)
    {
        fprintf(file, "%s\n%s\n%s\n%s\n%s\n\n", // menulis data ke dalam file yang ditunjuk oleh pointer file dan menentukan string sebagai tipe data yang akan ditulis
                dataMahasiswa[i].nama,
                dataMahasiswa[i].nim,
                dataMahasiswa[i].alamat,
                dataMahasiswa[i].kelas,
                dataMahasiswa[i].tempatTanggalLahir);
    }
    fclose(file); // menutup file untuk menghindari kerusakan data
}

// Fungsi untuk membaca data mahasiswa dari file
void bacaDataDariFile()
{
    FILE *file = fopen(FILE_NAME, "r"); // membuka file dalam mode r untuk membaca
    if (file == NULL)
    {
        printf("Belum ada data tersimpan.\n");
        return;
    }

    // membaca seluruh data mahasiswa (nama, nim, alamat, kelas, ttl) dengan perulangan hingga fungsi fscanf tidak membaca lima elemen.
    while (fscanf(file, " %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] ", 
                  dataMahasiswa[jumlahMahasiswa].nama,
                  dataMahasiswa[jumlahMahasiswa].nim,
                  dataMahasiswa[jumlahMahasiswa].alamat,
                  dataMahasiswa[jumlahMahasiswa].kelas,
                  dataMahasiswa[jumlahMahasiswa].tempatTanggalLahir) == 5)
    {
        jumlahMahasiswa++; // jika berhasil, maka jumlahMahasiswa akan bertambah 1 untuk menunjuk ke element berikutnya dlm array dan melanjutkan membaca array yg baru
    }
    fclose(file); // menutup file untuk menghindari kerusakan file
}

// Fungsi untuk menambahkan data mahasiswa kedalam array dataMahasiswa dan menyimpan data kedalam file melalui fungsi simpanDataKeFile()
void tambahMahasiswa()
{
    if (jumlahMahasiswa < MAX_MAHASISWA)
    { // cek apakah jumlah mahasiswa sudah penuh atau belum. jika belum, lakukan perintah didalam {}
        printf("Masukkan Nama Mahasiswa: ");
        getchar(); // membersihkan buffer input
        fgets(dataMahasiswa[jumlahMahasiswa].nama, sizeof(dataMahasiswa[jumlahMahasiswa].nama), stdin);
        strtok(dataMahasiswa[jumlahMahasiswa].nama, "\n"); // menghapus karakter new line setelah pengguna menekan enter yang terbaca dari keyboard 

        printf("Masukkan NIM: ");
        fgets(dataMahasiswa[jumlahMahasiswa].nim, sizeof(dataMahasiswa[jumlahMahasiswa].nim), stdin);
        strtok(dataMahasiswa[jumlahMahasiswa].nim, "\n");

        printf("Masukkan Alamat: ");
        fgets(dataMahasiswa[jumlahMahasiswa].alamat, sizeof(dataMahasiswa[jumlahMahasiswa].alamat), stdin);
        strtok(dataMahasiswa[jumlahMahasiswa].alamat, "\n");

        printf("Masukkan Kelas: ");
        fgets(dataMahasiswa[jumlahMahasiswa].kelas, sizeof(dataMahasiswa[jumlahMahasiswa].kelas), stdin);
        strtok(dataMahasiswa[jumlahMahasiswa].kelas, "\n");

        printf("Masukkan Tempat dan Tanggal Lahir: ");
        fgets(dataMahasiswa[jumlahMahasiswa].tempatTanggalLahir, sizeof(dataMahasiswa[jumlahMahasiswa].tempatTanggalLahir), stdin);
        strtok(dataMahasiswa[jumlahMahasiswa].tempatTanggalLahir, "\n");

        jumlahMahasiswa++; // menambahkan jumlah mahasiswa sebanyak satu kedalam variabel jumlahMahasiswa.

        // menyimpan data ke file setiap kali ada penambahan
        simpanDataKeFile();
    }
    else
    {
        printf("Data mahasiswa penuh!\n");
    }
}

// Fungsi untuk menampilkan data mahasiswa ke terminal
void tampilkanMahasiswa()
{
    if (jumlahMahasiswa == 0)
    {
        printf("Tidak ada data mahasiswa.\n");
        return;
    }

    printf("\n%-3s %-25s %-15s %-30s %-10s %-30s\n", "No", "Nama", "NIM", "Alamat", "Kelas", "Tempat Tanggal Lahir");
    printf("-----------------------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < jumlahMahasiswa; i++)
    {
        printf("%-3d %-25s %-15s %-30s %-10s %-30s\n",
               i + 1,
               dataMahasiswa[i].nama,
               dataMahasiswa[i].nim,
               dataMahasiswa[i].alamat,
               dataMahasiswa[i].kelas,
               dataMahasiswa[i].tempatTanggalLahir);
    }
}

// Fungsi utama
int main()
{
    int pilihan,
        status; // variabel status untuk menvalidasi bahwa opsi yang dipilih user harus bertipe integer (angka)

    // Membaca data dari file saat program dimulai
    bacaDataDariFile();

    do
    {
        printf("\nMenu:\n");
        printf("1. Tambah Data Mahasiswa\n");
        printf("2. Tampilkan Data Mahasiswa\n");
        printf("3. Keluar\n");
        printf("Pilih menu: ");
        status = scanf("%d", &pilihan);

        if (status != 1) // status tidak valid jika user tidak memasukkan angka melainkan memasukkan huruf ataupun simbol pada menu. maka lakukan kondisi selanjutnya
        {
            printf("Jawaban tidak valid. silahkan masukan angka sesuai pilihan anda\n");
            while (getchar() != '\n') 
                ;
            continue;
        }

        switch (pilihan)
        {
        case 1:
            tambahMahasiswa();
            break;
        case 2:
            tampilkanMahasiswa();
            break;
        case 3:
            printf("Terima kasih!\n");
            break;
        default:
            printf("Pilihan tidak valid. Masukan angka 1, 2 atau 3\n");
        }
    } while (pilihan != 3);

    return 0;
}
