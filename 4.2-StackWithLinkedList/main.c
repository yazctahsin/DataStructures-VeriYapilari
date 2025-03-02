//STACK LINKED LIST ILE//

#include <stdio.h>
#include <stdlib.h>
#define SENTINEL -10000000

struct dugum{
    int anahtar;
    struct dugum* sonraki
};

struct dugum* dugumOlustur(int anahtar){
    struct dugum* stack = (struct dugum*)malloc(sizeof(struct dugum));
    if(stack == NULL)
    {
        printf("Hata,yer ayrilamadi.");
        exit(1);
    }
    stack -> anahtar = anahtar;
    stack -> sonraki = NULL;
    return stack;
}

void push(int anahtar,struct dugum** stack){
    struct dugum* yigin = dugumOlustur(anahtar);
    yigin -> sonraki = *stack;
    *stack = yigin;
}

int pop(struct dugum **yigin){
    struct dugum *temp;
    int anahtar;
    if(*yigin == NULL) return SENTINEL;
    temp = *yigin;
    *yigin = (*yigin) -> sonraki;
    anahtar = temp -> anahtar;
    printf("Popped : %4d",anahtar);
    printf("\n");
    free(temp);
    return anahtar;
}

void yazdir(struct dugum* yigin){
    if(yigin == NULL)
    {
        printf("Yigin bos.");
        return SENTINEL;
    }
    while(yigin)
    {
        printf("%4d",yigin -> anahtar);
        yigin = yigin->sonraki;
    }
    printf("\n");
}

int yigin_bosmu(struct dugum* yigin){
    if(yigin == NULL) return 1;
    else return 0;
}

void yigin_yok_et(struct dugum** yigin){
    struct dugum* temp;
    while(*yigin != NULL)
    {
        temp = *yigin;
        *yigin = (*yigin) -> sonraki;
        free(temp);
    }
}

int main(int argc, char** argv) {
    struct dugum *yigin=NULL;
    push(100,&yigin);
    push(20,&yigin);
    push(60,&yigin);
    yazdir(yigin);
    pop(&yigin);
    pop(&yigin);
   yazdir(yigin);
   yigin_yok_et(&yigin);
   yazdir(yigin);
    return (EXIT_SUCCESS);
}
