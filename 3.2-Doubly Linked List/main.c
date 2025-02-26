//CIFT YONLU BAGLI LISTE

#include <stdio.h>
#include <stdlib.h>

//Dugum Yapısı
struct dugum {
    struct dugum* geri;
    int x;
    struct dugum* ileri;
};

//listenin bas ve son dügümlerini tutan yapi
struct ciftYonluListe {
    struct dugum *bas;
    struct dugum *son;
};

//liste baslatma
void ciftYonluListeBaslat(struct ciftYonluListe **liste) {
    *liste = (struct ciftYonluListe*)malloc(sizeof(struct ciftYonluListe));
    if (*liste == NULL) {
        printf("Hata, yer ayrilamadi. Sonlaniyor...\n");
        exit(1);
    }
    (*liste)->bas = NULL; //Bas dügüm
    (*liste)->son = NULL; // Son dügümü
}

// Listeyi yazdirma
void yazdir(struct ciftYonluListe* liste) {
    if (liste == NULL) return;

    struct dugum* temp = liste->bas;
    while (temp != NULL) {
        printf("%4d ", temp->x);
        temp = temp->ileri;
    }
    printf("\n");
}

// Dügüm olusturma
struct dugum* dugumOlustur(int deger) {
    struct dugum *a = malloc(sizeof(struct dugum));
    if (a == NULL) {
        printf("Hata, yer ayrilamadi\n");
        exit(1);
    }
    a->x = deger;
    a->ileri = NULL;
    a->geri = NULL;
    return a;
}

// Liste basina eleman ekleme
void liste_basina_ekle(struct ciftYonluListe *liste,int anahtar) {
    struct dugum *yeni = dugumOlustur(anahtar);
    if (liste->bas == NULL) {
        liste->bas = yeni;
        liste->son = yeni; // Bossa bas ve son aynidir.
    } else {
        yeni->ileri = liste->bas; // Yeni dügümün ilerisin eski basa bagla
        liste->bas->geri = yeni; // Eski basin gerisini yeniye bagla
        liste->bas = yeni; // Yeni dügümü bas olarak ayarla
    }
}

// Liste sonuna eleman ekleme
void liste_sonuna_ekle(struct ciftYonluListe *liste, int anahtar) {
    struct dugum *yeni = dugumOlustur(anahtar);
    if (liste->bas == NULL) {
        liste->bas = yeni;
        liste->son = yeni; // Bossa bas ve son ayni olmali
    } else {
        liste->son->ileri = yeni; // Eski sonun ilerisini yeni dügüme bagla
        yeni->geri = liste->son; // Yeni dügümün gerisini eski sona bagla
    }
    liste->son = yeni; // Sonu güncelle
}

// Listeyi yok etme
void liste_yok_et(struct ciftYonluListe** liste) {
    struct dugum* temp;
    if (*liste == NULL) return;
    while ((*liste)->bas != NULL) {
        temp = (*liste)->bas;
        (*liste)->bas = (*liste)->bas->ileri; // Bir sonraki dügüme gec
        free(temp);
    }
    free(*liste);
    *liste = NULL; // Listeyi NULL yap
}

// Listeyi sondan yazdirma
void liste_yazdir_sondan(struct ciftYonluListe* liste) {
    if (liste == NULL) return;
    struct dugum* son = liste->son;
    while (son != NULL) {
        printf("%4d ", son->x);
        son = son->geri;
    }
    printf("\n");
}

int main(int argc, char** argv) {
    struct ciftYonluListe *liste;
    ciftYonluListeBaslat(&liste);
    liste_basina_ekle(liste,40);
    liste_sonuna_ekle(liste, 60);
    liste_basina_ekle(liste,90);
    liste_sonuna_ekle(liste, 5);
    liste_sonuna_ekle(liste, 15);

    printf("Liste bastan yazdirma:\n");
    yazdir(liste);

    printf("Liste sondan yazdirma:\n");
    liste_yazdir_sondan(liste);

    liste_yok_et(&liste);

    return EXIT_SUCCESS;
}
