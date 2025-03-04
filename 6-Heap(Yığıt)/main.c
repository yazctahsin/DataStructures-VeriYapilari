#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct dugum {
    int key;
};

struct heap {
    struct dugum* dizi;
    int eleman_sayisi;
    int kapasite;
};

struct heap* heap_olustur(int kapasite) {
    struct heap* temp = (struct heap*)malloc(sizeof(struct heap));
    if (temp == NULL) {
        printf("Hata: Bellek ayrilamadi!\n");
        exit(1);
    }
    temp->dizi = (struct dugum*)malloc(kapasite * sizeof(struct dugum));
    if (temp->dizi == NULL) {
        printf("Hata: Dizi icin bellek ayrilamadi!\n");
        exit(1);
    }
    temp->kapasite = kapasite;
    temp->eleman_sayisi = 0;
    return temp;
}

void heap_yazdir(struct heap* heap) {
    for (int i = 0; i < heap->eleman_sayisi; i++) {
        printf("%5d", heap->dizi[i].key);
    }
    printf("\n");
}

void bubble_down(struct heap* heap, int index) {
    int left, right, largest;
    struct dugum temp_dugum;
    while (1) {
        left = 2 * index + 1;
        right = 2 * index + 2;
        largest = index;

        if (left < heap->eleman_sayisi && heap->dizi[left].key > heap->dizi[largest].key) {
            largest = left;
        }
        if (right < heap->eleman_sayisi && heap->dizi[right].key > heap->dizi[largest].key) {
            largest = right;
        }
        if (largest == index) {
            break;
        }
        temp_dugum = heap->dizi[index];
        heap->dizi[index] = heap->dizi[largest];
        heap->dizi[largest] = temp_dugum;
        index = largest;
    }
}

void bubble_up(struct heap* heap, int index) {
    int parent;
    struct dugum temp_node;
    while (index > 0) {
        parent = (index - 1) / 2;
        if (heap->dizi[index].key <= heap->dizi[parent].key) {
            break;
        }
        temp_node = heap->dizi[index];
        heap->dizi[index] = heap->dizi[parent];
        heap->dizi[parent] = temp_node;
        index = parent;
    }
}

int delete_max(struct heap* heap) {
    if (heap->eleman_sayisi == 0) {
        printf("Heap bos. Silme yapilamadi.\n");
        return -1;
    }
    int max_value = heap->dizi[0].key;
    heap->dizi[0] = heap->dizi[heap->eleman_sayisi - 1];
    heap->eleman_sayisi--;
    bubble_down(heap, 0);
    return max_value;
}

int heap_search(struct heap* heap, int key) {
    for (int i = 0; i < heap->eleman_sayisi; i++) {
        if (heap->dizi[i].key == key) {
            return 1;
        }
    }
    return 0;
}

void heap_insert(struct heap* heap, int key) {
    if (heap->eleman_sayisi >= heap->kapasite) {
        printf("Heap kapasitesi doldu, %d eklenemedi.\n", key);
        return;
    }
    if (heap_search(heap, key)) {
        printf("%d zaten heap icinde.\n", key);
        return;
    }
    heap->dizi[heap->eleman_sayisi].key = key;
    heap->eleman_sayisi++;
    bubble_up(heap, heap->eleman_sayisi - 1);
}

void heap_sort(struct heap* heap) {
    int orjinal_boyut = heap->eleman_sayisi;
    for (int i = (heap->eleman_sayisi / 2) - 1; i >= 0; i--) {
        bubble_down(heap, i);
    }
    for (int i = heap->eleman_sayisi - 1; i > 0; i--) {
        struct dugum temp_node = heap->dizi[0];
        heap->dizi[0] = heap->dizi[i];
        heap->dizi[i] = temp_node;
        heap->eleman_sayisi--;
        bubble_down(heap, 0);
    }
    heap->eleman_sayisi = orjinal_boyut;
}

int main() {
    struct heap* heap = heap_olustur(20);
    heap_insert(heap, 812);
    heap_insert(heap, 900);
    heap_insert(heap, 12);
    heap_insert(heap, 121);
    heap_insert(heap, 989);
    heap_insert(heap, 990);
    heap_insert(heap, 12);

    printf("Heap elemanlari:\n");
    heap_yazdir(heap);

    int max_deger = delete_max(heap);
    printf("Silinen en buyuk deger: %d\n", max_deger);

    printf("Heap elemanlari (silme sonrasi):\n");
    heap_yazdir(heap);

    free(heap->dizi);
    free(heap);

    return 0;
}
