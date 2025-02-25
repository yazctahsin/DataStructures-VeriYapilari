#include <stdio.h>
#include <stdlib.h>

//4byte yer kaplar. Listedeki degeri tutan degisken.
//4 Byte yer kaplar listedeki sonradan gelen dügümün adresini tutar. TOPLAM = 8 BYTE
struct dugum{
    int anahtar;
    struct dugum* sonraki;
};

struct dugum* dugum_olustur(int anahtar){
    struct dugum *a;
    a = (struct dugum*)malloc(sizeof(struct dugum));
    if(a == NULL)
    {
        printf("Heapte yer ayrýlamadý...");
        exit(1);
    }
    a ->anahtar = anahtar;
    a->sonraki = NULL;
    return a;
}

void liste_basina_ekle(int anahtar,struct dugum** liste_basi){
    struct dugum* a = dugum_olustur(anahtar);
    a -> sonraki = *liste_basi;
    *liste_basi = a;
}

void liste_sonuna_ekle(int icerik,struct dugum** liste_basi){
    struct dugum* a=dugum_olustur(icerik);
    if(liste_basi == NULL)
    {
        a -> sonraki = *liste_basi;
        *liste_basi = a;
    }
    else
    {
        struct dugum * x = *liste_basi;
        while(x -> sonraki != NULL)
        {
            x = x -> sonraki;
        }

        x -> sonraki = a;
    }

}

void liste_yaz_recursive(struct dugum *liste_basi){
    if(liste_basi != NULL)
    {
        printf("%4d ",liste_basi->anahtar);
        liste_yaz_recursive(liste_basi->sonraki);
    }
    else
    {
        printf("\n");
    }
}

void liste_yaz(struct dugum *liste_basi){
    while(liste_basi != NULL){
        printf("%4d ",liste_basi -> anahtar);
        liste_basi = liste_basi -> sonraki;
    }
    printf("\n");
}

void tersten_liste_yaz_recursive(struct dugum *liste_basi){
    if(liste_basi != NULL)
    {
        tersten_liste_yaz_recursive(liste_basi->sonraki);
        printf("%4d ",liste_basi->anahtar);
    }
}

void liste_yok_et(struct dugum **liste_basi){
    struct dugum *simdiki;
    while(*liste_basi != NULL)
    {
      //  simdiki =(*liste_basi);
      //  *liste_basi = (*liste_basi)->sonraki;
      //  free(simdiki);
        free(*liste_basi);
        *liste_basi=(*liste_basi)->sonraki;
    }
}

void liste_sirali_ekle(int anahtar, struct dugum **liste_basi){
   struct dugum *a, *b, *eklenen;
   b=*liste_basi;
   while(b!=NULL && b->anahtar <= anahtar){
       if(b->anahtar==anahtar) return;
       a = b;
       b= b->sonraki;
   }
   eklenen=dugum_olustur(anahtar);
   if(b==*liste_basi){
       eklenen->sonraki=*liste_basi;
       *liste_basi=eklenen;
   }
   else {
       a->sonraki=eklenen;
       eklenen->sonraki=b;
   }
}

void liste_eleman_sil(int anahtar, struct dugum **liste_basi){
    struct dugum *temp=*liste_basi;
    struct dugum *once;

    while(temp!=NULL && temp->anahtar!=anahtar){
        once = temp;
        temp=temp->sonraki;
    }
    if(temp==NULL) return;
    else {
        if(temp==*liste_basi) *liste_basi=(*liste_basi)->sonraki;
        else once->sonraki=temp->sonraki;
        free(temp);
    }

}

// verilen bir listenin sıralanması
void liste_sirala(struct dugum **liste_basi){
    struct dugum *a,*b,*c,*d;
    if(*liste_basi == NULL || (*liste_basi)->sonraki==NULL) return;
    d=(*liste_basi)->sonraki;
    (*liste_basi)->sonraki=NULL;
    while(d!=NULL){
        c=d;
        d=d->sonraki;
        b=*liste_basi;
        while(b!=NULL && b->anahtar < c->anahtar){
            a=b;
            b=b->sonraki;
        }
        if(b==*liste_basi){
            c->sonraki=*liste_basi;
            *liste_basi=c;
        }
        else {
            a->sonraki = c;
            c->sonraki = b;
        }
        }
    }

// dügümlerde tutulan isaretçi degeri degistirilerek listenin ters çevrilmesi.
// liste basi isaretcisi ilk listenin en sondaki dügümüne isaret edecektir.
void liste_ters_cevir(struct dugum **liste_basi){
    struct dugum *a,*b;
    a=NULL;
    while(*liste_basi!=NULL){
        b=*liste_basi;
        *liste_basi=(*liste_basi)->sonraki;
        b->sonraki=a;
        a=b;
    }
    *liste_basi=a;
}

// Anahtar1 ve Anahtar2 degerleri ardisik iki dügümün anahatarlarina karsilik
// gelip gelmedigini belirleyen fonksiyon.
int ardisik_mi(struct dugum *liste_basi,int anahtar1, int anahtar2){
    struct dugum *onceki;
    onceki=NULL;
    while(liste_basi!=NULL){
        if(liste_basi->anahtar==anahtar1) break;
        onceki=liste_basi;
        liste_basi=liste_basi->sonraki;
    }
    if(liste_basi!=NULL && (onceki!=NULL && onceki->anahtar==anahtar2 ||
                            liste_basi->sonraki!=NULL && liste_basi->sonraki->anahtar==anahtar2))
        return printf("Evet\n");
    return printf("Hayir\n");
 }

// anahar degeri verilen anahatar degerinden küçük olan dügümlerin
// listeden silinmesi
void listeden_cikar(struct dugum **liste_basi, int anahtar){
    struct dugum *b=*liste_basi, *a=*liste_basi;
    while(b!=NULL){
        if(anahtar > b->anahtar){
            if(b==*liste_basi){
                *liste_basi=(*liste_basi)->sonraki;
                free(b);
                a=b=*liste_basi;
            }
            else{
                a->sonraki=b->sonraki;
                free(b);
                b=a->sonraki;
            }
        }
        else{
            a=b;
            b=b->sonraki;
        }

    } //while
}


int main()
{
    struct dugum * liste = NULL;
    liste_basina_ekle(5,&liste);
    liste_yaz(liste);
    liste_sonuna_ekle(65,&liste);
    liste_basina_ekle(1,&liste);
    liste_sonuna_ekle(15,&liste);;
    liste_yaz(liste);
    liste_sirala(&liste);
    liste_yaz(liste);
    liste_sonuna_ekle(27,&liste);
    liste_basina_ekle(18,&liste);
    liste_sonuna_ekle(139,&liste);
    liste_yaz(liste);
    ardisik_mi(liste,1,7);
    liste_eleman_sil(5,&liste);
    liste_yaz(liste);

    return 0;
}

