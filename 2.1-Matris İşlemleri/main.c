#include <stdio.h>
#include <stdlib.h>
void iki_boyutlu_matris_olustur(int*** matris, int satir, int sutun){
    *matris = (int**)malloc(sizeof(int*) * satir);
    for(int i = 0; i < satir; i++ )
    {
        *(*matris + i) = (int*)malloc(sizeof(int) * sutun);

        for(int j = 0; j < sutun; j++)
        {
            *(*(*matris + i) + j) = rand() % 100;

        }
    }
}
void matris_yaz(int** matris, int satir, int sutun)
{
    for(int i = 0; i < satir; i++)
    {
        for(int j = 0; j < sutun; j++)
        {
            printf("%d ", *(*(matris + i) + j));//matris[i][j];
            if(j == sutun - 1)
            {
                printf("\n");
            }
        }
        printf("\n");
    }
}
int main(){
    int ** m1;  //m1 matrisi
    int ** m2;  //m2 matrisi

    int satir1, satir2, sutun1, sutun2;

    printf("Satir1 giriniz : ");
    scanf("%d",&satir1);

    printf("Sutun1 giriniz : ");
    scanf("%d",&sutun1);

    printf("Satir2 giriniz : ");
    scanf("%d",&satir2);

    printf("Sutun2 giriniz : ");
    scanf("%d",&sutun2);

    iki_boyutlu_matris_olustur(&m1,satir1,sutun1);
    printf("----------------\n");
    iki_boyutlu_matris_olustur(&m2,satir2,sutun2);

    matris_yaz(m1,satir1,sutun1);
     printf("----------------\n");
    matris_yaz(m2,satir2,sutun2);
    return 0;
}


