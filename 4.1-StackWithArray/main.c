//YIGIN STATIK (DIZI ILE YIGIN OLUSTURMA)

#include <stdio.h>
#include <stdlib.h>
#define SENTINEL -10000000

struct yigin{
    int *dizi;      //Yigindaki tam sayilara isaretci
    int kapasite;   //Yiginin tutabilecegi max eleman sayisi
    int tepe;       //Yigina en son itilen sayinin index degeri
};

struct yigin* yiginOlustur(int kapasite)
{
    if(kapasite <= 0)
    {
        printf("Kapasite pozitif bir tam sayi olmalidir. \n");
        exit(1);
    }
    struct yigin * stack = (struct yigin*)malloc(sizeof(struct yigin));
    stack -> dizi = (int*)malloc(kapasite * sizeof(int));
    stack -> kapasite = kapasite;
    stack -> tepe = -1;
    return stack;
}

int yigin_bosmu(struct yigin *y){
    if(y->tepe==-1) return 1;
    else return 0;
}
int yigin_dolumu(struct yigin *y){
    if(y->tepe>=y->kapasite-1) return 1;
    else return 0;
}

void yiginYazdir(struct yigin* stack)
{
    if(stack == NULL) return printf("Yigin bulunamadi...\n");
    printf("Yiginin Kapasitesi    : %4d \n", stack -> kapasite);
    printf("Yiginin Eleman Sayisi : %4d \n",stack -> tepe + 1);
    for(int i = stack ->tepe;i>=0;i--)
    {
        printf("%4d",stack -> dizi[i]);
    }
    printf("\n\n");
}

void push(struct yigin** stack,int deger)
{
    if(yigin_dolumu(*stack))
    {
        kapasiteyi_artir(stack,2);
    }
    (*stack) -> dizi[++(*stack) -> tepe] = deger;
}

void pop(struct yigin* stack)
{
    if(yigin_bosmu(stack)) return SENTINEL;
    printf("Popped : %2d\n",stack->dizi[stack -> tepe]);
    return stack ->dizi[stack ->tepe--];
}

// Kapasiteyi artirmak için `realloc` ile yeniden boyutlandirma
void kapasiteyi_artir(struct yigin **yigin, int kackat){

    (*yigin)->dizi=(int*)realloc((*yigin)->dizi,kackat*(*yigin)->kapasite*sizeof(int));
    (*yigin)->kapasite = 2*(*yigin)->kapasite;
}

void yigin_yok_et(struct yigin **y){
    free((*y)->dizi);
    free(*y);
    *y=NULL;
}

int main()
{
    struct yigin *yigin=NULL;
    yigin=yiginOlustur(3);
    push(&yigin,10);
    push(&yigin,40);
    push(&yigin,5);
    yiginYazdir(yigin);
    push(&yigin,-10);
    push(&yigin,-40);
    push(&yigin,25);
    yiginYazdir(yigin);
    push(&yigin,89);
    push(&yigin,189);
    yiginYazdir(yigin);
    pop(yigin);
    yiginYazdir(yigin);
    return 0;
}
