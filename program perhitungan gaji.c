#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nama[32];
    int rekening;
}Karyawan;

typedef struct {
    char divisi[50];
    int hari_kerja;
    int jam_lembur;
    int absen;
}DataKerja;

union Pajak{
    float persentase;
    float jumlah_pajak;
};

void input_karyawan(Karyawan *karyawan, DataKerja *datakerja) {
    printf("Masukkan nama karyawan: ");
    scanf("%31s", karyawan-> nama);

    printf("Masukkan rekening karyawan: ");
    scanf("%d", &karyawan-> rekening);

    printf("Masukkan divisi: ");
    scanf("%49s", datakerja->divisi);

    do {
        printf("Masukkan jumlah hari kerja dalam sebulan (maksimal 22): ");
        scanf("%d", &datakerja->hari_kerja);

        if (datakerja->hari_kerja > 22 || datakerja->hari_kerja <= 0) {
            printf("-- Input tidak valid. Hari kerja harus antara 0 dan 22 --\n");
            printf("-- program dengan perhitungan 5 hari kerja --\n");
        }
    } while (datakerja->hari_kerja > 22 || datakerja->hari_kerja <= 0);

    printf("Masukkan jumlah jam lembur dalam sebulan: ");
    scanf("%d", &datakerja->jam_lembur);

    int max_absen = 22 - datakerja->hari_kerja;

    do {
        printf("Masukkan jumlah absen (maksimal %d): ", max_absen);
        scanf("%d", &datakerja->absen);

        if (datakerja->absen > max_absen || datakerja->absen < 0) {
            printf("-- Input tidak valid. Absen harus antara 0 dan %d --\n", max_absen);
            printf("-- program dengan perhitungan 5 hari kerja --\n");
        }
    } while (datakerja->absen > max_absen || datakerja->absen < 0);
}

float hitung_gaji(int upah_bulanan, DataKerja *datakerja) {
    float gaji_per_hari = (float)upah_bulanan / 22;
    float bonus_lembur = datakerja->jam_lembur * (gaji_per_hari / 8) * 1.5;
    float potongan_gaji = datakerja->absen * gaji_per_hari;

    float gaji = ((datakerja->hari_kerja * gaji_per_hari) + bonus_lembur) - potongan_gaji;

    return gaji;
}

float hitung_pajak(union Pajak *pajak, float gaji, int persen){
    if(persen){
        pajak->jumlah_pajak = gaji * (pajak->persentase/ 100);
    }
    return pajak->jumlah_pajak;
}

void cetak_karyawan(Karyawan *karyawan, DataKerja *datakerja, float gaji, float pajak) {
    printf("\n=== Data Karyawan ===\n");
    printf("Nama: %s\n", karyawan->nama);
    printf("Rekening: %d\n", karyawan->rekening);
    printf("Divisi: %s\n", datakerja->divisi);  
    printf("Total Gaji: Rp.%.2f\n", gaji);
    printf("Total Gaji dipotong pajak: Rp.%.2f\n", gaji - pajak);
    printf("\n==============================");
}

int main() {
    int lanjut = 1;

    while (lanjut){
        Karyawan *karyawan = malloc(sizeof(Karyawan));
        DataKerja *kerja = malloc(sizeof(DataKerja));
        union Pajak pajak;

        if (karyawan == NULL || kerja == NULL) {
            printf("Gagal mengalokasikan memori->\n");
            return 1;
        }

        input_karyawan(karyawan, kerja);

        int upah_bulanan;
        printf("Masukkan gaji bulanan: ");
        scanf("%d", &upah_bulanan);

        float gaji = hitung_gaji(upah_bulanan, kerja);

        printf("Masukkan persentase pajak (contoh 10 untuk 10%%): ");
        scanf("%f", &pajak.persentase);

        float total_pajak = hitung_pajak(&pajak, gaji, 1);

        cetak_karyawan(karyawan, kerja, gaji, total_pajak);

        free(karyawan);
        free(kerja);

        printf("\nApakah ingin memasukkan data karyawan lain? \n1 = ya \n0 = tidak");
        printf("\nPilih: ");
        scanf("%d", &lanjut);
    }

    printf("Program selesai. Terima kasih!\n");
    return 0;
}
