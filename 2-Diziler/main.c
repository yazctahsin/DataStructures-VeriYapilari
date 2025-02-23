#include <stdio.h>
#include <stdlib.h>

// Fonksiyon Bildirimleri
void diziYazdir(int *arr, int size);
int* elemanEkle(int *arr, int *size, int newElement);
int* elemanSil(int *arr, int *size, int index);
void matrisYazdir(int **matrix, int rows, int cols);
void matrisToplama(int **mat1, int **mat2, int **result, int rows, int cols);
void matrisCikarma(int **mat1, int **mat2, int **result, int rows, int cols);
void matrisCarpma(int **mat1, int **mat2, int **result, int rows, int cols);
void menuGoster();

int main() {
    int size, choice, newElement, index, exitFlag = 0;

    // Dizi boyutunu al
    printf("Tek boyutlu dizi boyutunu girin: ");
    scanf("%d", &size);
    int *arr = (int*)malloc(size * sizeof(int));

    // Dizi elemanlarini al
    printf("Dizi elemanlarini girin(sayilari bosluklu giriniz 5 6 7 vb.):\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    int rows, cols;
    printf("Matrisin satir ve sutun sayisini girin (ornek: 2 2):");
    scanf("%d %d", &rows, &cols);

    // Matrisleri Dinamik Ayirma
    int **mat1 = (int**)malloc(rows * sizeof(int*));
    int **mat2 = (int**)malloc(rows * sizeof(int*));
    int **result = (int**)malloc(rows * sizeof(int*));

    for (int i = 0; i < rows; i++) {
        mat1[i] = (int*)malloc(cols * sizeof(int));
        mat2[i] = (int*)malloc(cols * sizeof(int));
        result[i] = (int*)malloc(cols * sizeof(int));
    }

    // Matris Elemanlarini Alma
    printf("Birinci matris elemanlarini girin:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &mat1[i][j]);
        }
    }

    printf("Ikinci matris elemanlarini girin:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &mat2[i][j]);
        }
    }

    while (!exitFlag) {
        menuGoster();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                diziYazdir(arr, size);
                break;
            case 2:
                printf("Eklemek istediginiz elemani girin: ");
                scanf("%d", &newElement);
                arr = elemanEkle(arr, &size, newElement);
                break;
            case 3:
                printf("Silmek istediginiz elemanin indeksini girin: ");
                scanf("%d", &index);
                arr = elemanSil(arr, &size, index);
                break;
            case 4:
                printf("\nMatris Toplama Sonucu:\n");
                matrisToplama(mat1, mat2, result, rows, cols);
                matrisYazdir(result, rows, cols);
                break;
            case 5:
                printf("\nMatris Cikarma Sonucu:\n");
                matrisCikarma(mat1, mat2, result, rows, cols);
                matrisYazdir(result, rows, cols);
                break;
            case 6:
                printf("\nMatris Carpma Sonucu:\n");
                matrisCarpma(mat1, mat2, result, rows, cols);
                matrisYazdir(result, rows, cols);
                break;
            case 0:
                exitFlag = 1;
                printf("Program Sonlaniyor...\n");
                break;
            default:
                printf("Gecersiz secim! Tekrar deneyin.\n");
        }
    }

    // Belleði Serbest Birak
    free(arr);
    for (int i = 0; i < rows; i++) {
        free(mat1[i]);
        free(mat2[i]);
        free(result[i]);
    }
    free(mat1);
    free(mat2);
    free(result);

    return 0;
}

// Menü Gösterme
void menuGoster() {
    printf("\n------ MENU ------\n");
    printf("1. Diziyi Yazdir\n");
    printf("2. Diziye Eleman Ekle\n");
    printf("3. Diziden Eleman Sil\n");
    printf("4. Matris Toplama\n");
    printf("5. Matris Cikarma\n");
    printf("6. Matris Carpma\n");
    printf("0. Cikis\n");
    printf("Secim yapin: ");
}

// Tek Boyutlu Dizi Yazdirma
void diziYazdir(int *arr, int size) {
    printf("Dizi Elemanlari: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Diziye Eleman Ekleme
int* elemanEkle(int *arr, int *size, int newElement) {
    *size += 1;
    arr = realloc(arr, (*size) * sizeof(int)); // Boyutu arttir
    arr[*size - 1] = newElement; // Yeni elemani ekle
    return arr;
}

// Diziden Eleman Silme
int* elemanSil(int *arr, int *size, int index) {
    if (index < 0 || index >= *size) {
        printf("Gecersiz indeks!\n");
        return arr;
    }
    for (int i = index; i < (*size) - 1; i++) {
        arr[i] = arr[i + 1];
    }
    *size -= 1;
    arr = realloc(arr, (*size) * sizeof(int)); // Boyutu kücült
    return arr;
}

// 2D Matris Yazdýrma
void matrisYazdir(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Matris Toplama
void matrisToplama(int **mat1, int **mat2, int **result, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}

// Matris Cikarma
void matrisCikarma(int **mat1, int **mat2, int **result, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = mat1[i][j] - mat2[i][j];
        }
    }
}

// Matris Carpma
void matrisCarpma(int **mat1, int **mat2, int **result, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = 0;
            for (int k = 0; k < cols; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}
