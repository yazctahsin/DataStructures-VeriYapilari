#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Dugum {
    char *anahtar;           // Anahtar degeri (örnegin bir sehir adi)
    struct Dugum *sonraki;   // Bir sonraki dügümü isaret eden gösterici
};

// Hash tablosundaki her bir sütun
struct TabloSutunu {
    int elemanSayisi;     // Sütundaki eleman sayisi
    struct Dugum *bas;    // Sütundaki bagli listenin basi
};

// Hash tablosu yapisi
struct HashTablosu {
    int carpan;              // Hash fonk. carpani
    int tabloUzunlugu;       // Hash sütun sayisi
    struct TabloSutunu *sutunlar; // Hash tablosunun baslangic adresi (sütunlar)
};

// Hash tablosunu baslatma
void hashTablosuBaslat(struct HashTablosu **tablo, int carpan, int tabloUzunlugu) {
    *tablo = (struct HashTablosu *)malloc(sizeof(struct HashTablosu));
    (*tablo)->carpan = carpan;
    (*tablo)->tabloUzunlugu = tabloUzunlugu;
    (*tablo)->sutunlar = (struct TabloSutunu *)calloc(tabloUzunlugu, sizeof(struct TabloSutunu));
}

// Hash fonksiyonu
int hashHesapla(char *anahtar, int carpan, int tabloUzunlugu) {
    int hashDegeri = 0;
    while (*anahtar)
        hashDegeri = (hashDegeri * carpan + *anahtar++) % tabloUzunlugu;
    return hashDegeri;
}

// Listeye dügüm ekleme
void dugumEkle(struct Dugum **bas, char *anahtar) {
    struct Dugum *yeniDugum = (struct Dugum *)malloc(sizeof(struct Dugum));
    yeniDugum->anahtar = strdup(anahtar);
    yeniDugum->sonraki = *bas;
    *bas = yeniDugum;
}

// Hash tablosuna bir sehir ekleyen fonksiyon
void sehirEkle(struct HashTablosu *tablo, char *sehir) {
    int index = hashHesapla(sehir, tablo->carpan, tablo->tabloUzunlugu);
    dugumEkle(&tablo->sutunlar[index].bas, sehir);
    tablo->sutunlar[index].elemanSayisi++;
}

// Ekrana yazdirma
void hashTablosuYazdir(struct HashTablosu *tablo) {
    printf("----- HASH TABLOSU -----\n");
    for (int i = 0; i < tablo->tabloUzunlugu; i++) {
        printf("%5d : (%2d) ", i, tablo->sutunlar[i].elemanSayisi);
        struct Dugum *gecici = tablo->sutunlar[i].bas;
        while (gecici) {
            printf("-> %s ", gecici->anahtar);
            gecici = gecici->sonraki;
        }
        printf("\n");
    }
}

// Hash sütunu silme
void listeSil(struct Dugum **bas) {
    struct Dugum *gecici;
    while (*bas) {
        gecici = *bas;
        *bas = (*bas)->sonraki;
        free(gecici->anahtar);
        free(gecici);
    }
}

// Hash tablosu yeniden boyutlandirma
void hashTablosuGenislet(struct HashTablosu **tablo, int yeniCarpan, int yeniUzunluk) {
    struct HashTablosu *yeniTablo;
    hashTablosuBaslat(&yeniTablo, yeniCarpan, yeniUzunluk);
    for (int i = 0; i < (*tablo)->tabloUzunlugu; i++) {
        struct Dugum *gecici = (*tablo)->sutunlar[i].bas;
        while (gecici) {
            sehirEkle(yeniTablo, gecici->anahtar);
            gecici = gecici->sonraki;
        }
    }
    for (int i = 0; i < (*tablo)->tabloUzunlugu; i++) {
        listeSil(&(*tablo)->sutunlar[i].bas);
    }
    free((*tablo)->sutunlar);
    free(*tablo);
    *tablo = yeniTablo;
}

// Hash tablosunu yok etme
void hashTablosuYokEt(struct HashTablosu **tablo) {
    for (int i = 0; i < (*tablo)->tabloUzunlugu; i++) {
        listeSil(&(*tablo)->sutunlar[i].bas);
    }
    free((*tablo)->sutunlar);
    free(*tablo);
    *tablo = NULL;
}

int main() {
    struct HashTablosu *tablo = NULL;
    hashTablosuBaslat(&tablo, 3, 5);
    sehirEkle(tablo, "istanbul");
    sehirEkle(tablo, "izmir");
    sehirEkle(tablo, "tekirdag");
    sehirEkle(tablo, "adana");
    sehirEkle(tablo, "samsun");
    sehirEkle(tablo, "kocaeli");
    sehirEkle(tablo, "kayseri");
    sehirEkle(tablo, "everest");
    hashTablosuYazdir(tablo);
    hashTablosuGenislet(&tablo, 7, 11);
    hashTablosuYazdir(tablo);
    hashTablosuYokEt(&tablo);
    return 0;
}
