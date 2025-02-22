#include <stdio.h>

int main() {
    int a = 10;         // Normal bir tamsayi degiskeni
    int *p;             // Pointer (isaretçi) degiskeni

    p = &a;             // 'p' degiskenine 'a' degiskeninin adresini atiyoruz

    // Degiskenlerin adres ve degerleri
    printf("a degiskeninin degeri: %d\n", a);
    printf("a degiskeninin adresi: %p\n", &a);
    printf("p pointer'inin degeri (a'nin adresi): %p\n", p);
    printf("p pointer'inin gösterdiði deðer: %d\n", *p);

    // Pointer ile degeri adresten degistirebiliriz
    *p = 20;
    printf("Pointer kullanarak a'nýn deðerini deðiþtirdik: %d\n", a);

    // Pointer ile dizi elemanlarina erisim
    int arr[] = {1, 2, 3, 4, 5};
    int *ptr = arr; // Dizi adi zaten bir pointer'dir, ilk elemanin adresini tutar

    printf("Dizinin ilk elemaný: %d\n", *ptr);
    printf("Dizinin ikinci elemaný: %d\n", *(ptr + 1));
    printf("Dizinin üçüncü elemaný: %d\n", *(ptr + 2));

    return 0;
}
