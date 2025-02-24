#include <stdio.h>
#include <stdlib.h>

struct dugum
{
    int deger;
    struct dugum * next;
};

void list_yazdir(struct dugum* liste_basi)
{
    while(liste_basi != NULL)
    {
        printf("%5d",liste_basi -> deger);
        liste_basi = liste_basi -> next;
    }
    printf("\n");
}

struct dugum* dugum_olustur(int deger)
{
    struct dugum * a = (struct dugum*)malloc(sizeof(struct dugum));
    if(a == NULL)
    {
        printf("Hata, heapte yer ayrılamadı...");
        exit(1);
    }
    a -> deger = deger;
    a -> next = NULL;
    return a;
}

void liste_basina_ekle(struct dugum ** liste_basi, int deger)
{
    struct dugum* a = dugum_olustur(deger);
    a -> next = *liste_basi;
    *liste_basi = a;
}

void liste_sonuna_ekle(struct dugum **liste_basi,int icerik){
    struct dugum* a=dugum_olustur(icerik);
    if(*liste_basi==NULL){
        *liste_basi=a;
    }
    else {
        struct dugum *x=*liste_basi;
        while(x->next!=NULL){
            x=x->next;
        }
        x->next=a;
    }
}

void liste_sirali_ekle(struct dugum **liste_basi,int anahtar)
{
   struct dugum *a = NULL, *b = *liste_basi, *eklenen;

   // Sirali ekleme için dogru konumu bul
   while(b != NULL && b->deger < anahtar)
   {
       a = b;
       b = b->next;
   }

   // Ayni degerde anahtar varsa ekleme yapma
   if(b != NULL && b->deger == anahtar) return;

   eklenen = dugum_olustur(anahtar);

   // Listenin basina ekleme yapma durumu
   if(b == *liste_basi)
   {
       eklenen->next = *liste_basi;
       *liste_basi = eklenen;
   }
   else
   {
       a->next = eklenen;
       eklenen->next = b;
   }
}

void tersten_liste_yaz_recursive(struct dugum *liste_basi){

    if(liste_basi!=NULL){
        tersten_liste_yaz_recursive(liste_basi->next);
        printf("%5d",liste_basi->deger);
    }
}

void liste_eleman_sil(struct dugum **liste_basi,int deger)
{
    struct dugum *temp = *liste_basi;
    struct dugum *once = NULL;

    while(temp != NULL && temp->deger != deger)
    {
        once = temp;
        temp = temp->next;
    }

    if(temp == NULL) return;  // Aranan eleman listede yoksa cik

    if(temp == *liste_basi)   // Silinecek eleman listenin basindaysa
        *liste_basi = temp->next;
    else                      // Silinecek eleman listenin ortasinda veya sonundaysa
        once->next = temp->next;

    free(temp);               // Dügümü bellekte serbest birak
}


void liste_sirala(struct dugum **liste_basi)
{
    if(*liste_basi == NULL || (*liste_basi)->next == NULL) return;

    struct dugum *d = (*liste_basi)->next; // Islenmemis listeden gelen dügümler
    (*liste_basi)->next = NULL;            // Sirali listeyi baslatmak için ilk dügüm

    while(d != NULL)
    {
        struct dugum *c = d;
        d = d->next;

        struct dugum *a = NULL;
        struct dugum *b = *liste_basi;

        // Yeni dügümün konumunu bul
        while(b != NULL && b->deger < c->deger)
        {
            a = b;
            b = b->next;
        }

        // Yeni dügüm en basa ekleniyorsa
        if(b == *liste_basi)
        {
            c->next = *liste_basi;
            *liste_basi = c;
        }
        else  // Yeni dügüm ortada veya sonda bir yere ekleniyorsa
        {
            a->next = c;
            c->next = b;
        }
    }
}

int main()
{
    struct dugum* liste = NULL;
    liste_basina_ekle(&liste,1);
    liste_basina_ekle(&liste,8);
    liste_basina_ekle(&liste,15);
    liste_basina_ekle(&liste,3);
    liste_basina_ekle(&liste,57);
    liste_basina_ekle(&liste,105);
    liste_sonuna_ekle(&liste,10);
    liste_sonuna_ekle(&liste,158);
    list_yazdir(liste);
    tersten_liste_yaz_recursive(liste);
    printf("\n");
    liste_sirali_ekle(&liste,12);
    list_yazdir(liste);
    //liste_eleman_sil(&liste,7);
    list_yazdir(liste);
    liste_sirala(&liste);
    list_yazdir(liste);

    return 0;
}


