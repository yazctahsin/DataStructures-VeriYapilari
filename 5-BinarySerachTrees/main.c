// IKILI ARAMA AGACI (BST) LINKEDLIST
#include <stdio.h>
#include <stdlib.h>
#define SENTINEL -100000

//INORDER : LNR,RNL
//PREORDER : NLR,NRL
//POSTORDER : LRN,RLN

typedef struct dugum{
    int data;
    struct dugum* sol;
    struct dugum* sag;
} node;

node* dugumOlustur(int icerik)
{
    node* d = (node*)malloc(sizeof(node));
    if(d == NULL)
    {
        printf("HATA YER AYRILAMADI...\n");
        exit(1);
    }
    d->data = icerik;
    d->sag = d->sol = NULL;
    return d;
}
node* ekle(node** agac, int x)
{
    if(*agac == NULL)
    {
        *agac = dugumOlustur(x); // root'u olusturup dogrudan d�nd�r�yoruz
        return;
    }
    if((*agac)->data < x)
    {
        ekle(&(*agac)->sag,x);
    }
    else
    {
        ekle(&(*agac)->sol,x);
    }
    return agac;
}

void inorderDolas(node* agac)
{
    if(agac == NULL) return;
    inorderDolas(agac->sol);
    printf("%5d", agac->data);
    inorderDolas(agac->sag);
}
void preorderDolas(node* agac)
{
    if(agac == NULL) return;
    printf("%5d", agac->data);
    preorderDolas(agac->sol);
    preorderDolas (agac->sag);
}
void postOrderDolas(node* agac)
{
    if(agac == NULL) return;
    postOrderDolas(agac->sol);
    postOrderDolas(agac->sag);
    printf("%5d", agac->data);
}

int bul(node* agac,int aranan)
{
   if(agac == NULL){
        return -1;}
   if(agac -> data == aranan) return 1;
   if(bul(agac -> sag,aranan)==1) return 1;
   if(bul(agac -> sol,aranan)==1) return 1;
   return -1;
}
int max(node*agac)
{
    while(agac ->sag != NULL)
    {
        agac = agac -> sag;
    }
    return agac -> data;
}

int min(node*agac)
{
    while(agac -> sol != NULL)
    {
        agac = agac -> sol;
    }
    return agac -> data;
}

// D�g�m silme fonksiyonu
node* sil(node** agac, int x) {
    if (*agac == NULL) return NULL; // Agac bossa, NULL d�nd�r

    // D�g�mde aranan veri bulunursa
    if (x < (*agac)->data) {
        (*agac)->sol = sil(&(*agac)->sol, x); // Sol alt agaca git
    } else if (x > (*agac)->data) {
        (*agac)->sag = sil(&(*agac)->sag, x); // Sag alt agaca git
    } else {
        // D�g�m bulundu, silme islemi basliyor
        if ((*agac)->sol == NULL) {
            node* temp = (*agac)->sag; // Sadece sag alt agac var
            free(*agac); // Bellegi serbest birak
            return temp; // Sag alt agac d�nd�r
        } else if ((*agac)->sag == NULL) {
            node* temp = (*agac)->sol; // Sadece sol alt agac var
            free(*agac); // Belle�i serbest birak
            return temp; // Sol alt agac d�nd�r
        }
        // Her iki alt aga� da varsa, in-order �ncesi en k���k degeri bul
        // En k���k d�g�m� bulmak i�in min fonksiyonu kullaniyoruz
        int minValue = min((*agac)->sag); // Sag alt agacin en k���k degeri
        (*agac)->data = minValue; // D�g�m�n verisini g�ncelle

        // D�g�m� sil
        (*agac)->sag = sil(&(*agac)->sag, minValue);
    }
    return *agac; // G�ncellenen k�k d�g�m� d�nd�r
}

int yukseklik(node* agac) {
    if (agac == NULL) return 0; // Bod agacin y�ksekligi 0
    int solYukseklik = yukseklik(agac->sol); // Sol alt agacin y�ksekligi
    int sagYukseklik = yukseklik(agac->sag); // Sag alt agacin y�ksekligi
    return 1 + (solYukseklik > sagYukseklik ? solYukseklik : sagYukseklik);
}

// Dengeli olup olmadigini kontrol eden fonksiyon
int dengeliMi(node* agac) {
    if (agac == NULL) return 1; // Bos aga� dengelidir

    // Sol ve sag alt agaclarin y�ksekligini bul
    int solYukseklik = yukseklik(agac->sol);
    int sagYukseklik = yukseklik(agac->sag);

    // Y�kseklik farki 1'den b�y�kse dengeli degil
    if (abs(solYukseklik - sagYukseklik) > 1) return 0;

    // Sol ve sag alt aga�lar da dengeliyse, aga� dengelidir
    return dengeliMi(agac->sol) && dengeliMi(agac->sag);
}

// T�m d�g�mleri sayan fonksiyon
int dugumSayisi(node* agac) {
    if (agac == NULL) return 0; // Bos agacta d�g�m yoktur
    return 1 + dugumSayisi(agac->sol) + dugumSayisi(agac->sag); // Her d�g�m i�in 1 ekle
}

// Yaprak d�g�mleri sayan fonksiyon
int yaprakSayisi(node* agac) {
    if (agac == NULL) return 0; // Bos agacta yaprak yoktur
    if (agac->sol == NULL && agac->sag == NULL) return 1; // Yaprak d�g�m bulduk
    return yaprakSayisi(agac->sol) + yaprakSayisi(agac->sag); // Sol ve sag alt agaclari dolas
}

void agaciYokEt(node* agac) {
    if (agac == NULL) return; // Agac bossa islemi sonlandir

    // �nce sol ve sag alt aga�lari serbest birak
    agaciYokEt(agac->sol);
    agaciYokEt(agac->sag);

    // simdi bu d�g�m� serbest birak
    printf("Dugum serbest birakiliyor: %d\n", agac->data);
    free(agac);
}
// ic d�g�m sayisini bulan fonksiyon
int ic_dugum_sayisi(node* kok) {
    if (kok == NULL) return 0; // Aga� bossa, ic d�g�m yoktur

    // D�g�mde en az bir �ocuk olup olmadigini kontrol et
    if (kok->sol == NULL && kok->sag == NULL) return 0; // Yaprak d�g�m, ic d�g�m sayilmaz

    // ic d�g�m sayisini hesapla
    return 1 + ic_dugum_sayisi(kok->sol) + ic_dugum_sayisi(kok->sag);
}

// ikili arama agaci olup olmadigini kontrol eden fonksiyon
int ikili_arama_agaci_mi(node* kok) {
    if (kok == NULL) return 1; // Bos aga� BST olarak kabul edilir

    // Sol alt aga� i�in kontrol: sol alt a�gac k�k�n�n degeri daha k���k olmali
    if (kok->sol != NULL && kok->sol->data >= kok->data) return 0;

    // Sag alt agac icin kontrol: sag alt agac k�k�n�n degeri daha b�y�k olmali
    if (kok->sag != NULL && kok->sag->data <= kok->data) return 0;

    // Sol ve sag alt aga�lari rek�rsif olarak kontrol et
    return ikili_arama_agaci_mi(kok->sol) && ikili_arama_agaci_mi(kok->sag);
}
int main()
{
    node* agac = NULL;
    ekle(&agac, 56);   // Agacin k�k isaretcisini ge�iyoruz
    ekle(&agac, 26);
    ekle(&agac, 200);
    ekle(&agac, 18);
    ekle(&agac, 28);
    ekle(&agac, 190);
    ekle(&agac, 213);
    ekle(&agac, 12);
    ekle(&agac, 24);
    ekle(&agac, 27);
    ekle(&agac, 500);
   /* ekle(&agac, 10);
    ekle(&agac, 9);*/

    printf("Arama sonucu : %d\n",bul(agac,50));
    printf("Agacin Min Elemani : %d\n",min(agac));
    printf("Agacin Max Elemani : %d\n",max(agac));

    printf("InOrderDolasma : ");
    inorderDolas(agac);
    printf("\n\n");
    printf("PreOrderDolasma : ");
    preorderDolas(agac);
    printf("\n\n");
    printf("PostOrderDolasma : ");
    postOrderDolas(agac);
    printf("\n\n");
    //sil(&agac,190);
   //inorderDolas(agac);
    printf("\n\n");
    sil(&agac,56);
    preorderDolas(agac);
    printf("\nAgac dengeli mi : %d",dengeliMi(agac));
    printf("\nToplam dugum sayisi: %d\n", dugumSayisi(agac));
    printf("\nYaprak dugum sayisi: %d\n", yaprakSayisi(agac));
    printf("Ic dugum sayisi: %d\n", ic_dugum_sayisi(agac));
    int sonuc = ikili_arama_agaci_mi(agac);
    printf("\nAgac ikili arama agaci mi : %d",sonuc);
    return 0;
}

