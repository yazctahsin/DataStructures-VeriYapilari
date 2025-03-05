#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dügüm
struct CELL {
    char *anahtar;
    struct CELL *next;
};

// Hash tablosu dügümü
struct table_node {
    int counter;
    struct CELL *header;
};

// Tablo yapisi
struct hash_tablosu {
    struct table_node *tablo_basi;
    int tablo_uzunlugu;
    int multiplier;
};

// Hash fonksiyonu
unsigned hash(char *anahtar, int multiplier, int table_size) {
    unsigned int value = 0;
    while (*anahtar) {
        value = (*anahtar++ + multiplier * value) % table_size;
    }
    return value;
}

// Hash tablosu baslatma
void initialize_hash_table(struct hash_tablosu **hash_table, int multiplier, int table_size) {
    *hash_table = malloc(sizeof(struct hash_tablosu));
    if (*hash_table == NULL) {
        fprintf(stderr, "Hash tablosu için bellek ayrilamadi.\n");
        exit(EXIT_FAILURE);
    }
    (*hash_table)->tablo_basi = calloc(table_size, sizeof(struct table_node));
    if ((*hash_table)->tablo_basi == NULL) {
        fprintf(stderr, "Hash tablosu için bellek ayrilamadi.\n");
        free(*hash_table);
        exit(EXIT_FAILURE);
    }
    (*hash_table)->tablo_uzunlugu = table_size;
    (*hash_table)->multiplier = multiplier;
}

// Dügüm ekleme
int insert_hash_table(struct hash_tablosu *hash_table, char *anahtar) {
    unsigned int index = hash(anahtar, hash_table->multiplier, hash_table->tablo_uzunlugu);
    struct CELL **header = &(hash_table->tablo_basi[index].header);

    // Anahtar var mi kontrolu
    struct CELL *iter = *header;
    while (iter != NULL) {
        if (strcmp(iter->anahtar, anahtar) == 0)
            return 0; // Zaten mevcut
        iter = iter->next;
    }

    // Yoksa yeni dügüm olustur ve listeye ekle
    struct CELL *new_node = malloc(sizeof(struct CELL));
    if (new_node == NULL) {
        fprintf(stderr, "Düðüm için bellek ayrýlamadý.\n");
        exit(EXIT_FAILURE);
    }
    new_node->anahtar = strdup(anahtar);
    new_node->next = *header;
    *header = new_node;
    hash_table->tablo_basi[index].counter++;
    return 1;
}

// Yazdirma fonksiyonu
void print_hash_table(struct hash_tablosu *hash_table) {
    printf("----- HASH TABLOSU -----\n");
    for (int i = 0; i < hash_table->tablo_uzunlugu; i++) {
        printf("%d (%d): ", i, hash_table->tablo_basi[i].counter);
        struct CELL *iter = hash_table->tablo_basi[i].header;
        while (iter != NULL) {
            printf("%s -> ", iter->anahtar);
            iter = iter->next;
        }
        printf("NULL\n");
    }
}


// Hash icin ayrilan bellegi serbest birakma
void free_hash_table(struct hash_tablosu *hash_table) {
    for (int i = 0; i < hash_table->tablo_uzunlugu; i++) {
        struct CELL *iter = hash_table->tablo_basi[i].header;
        while (iter != NULL) {
            struct CELL *temp = iter;
            iter = iter->next;
            free(temp->anahtar);
            free(temp);
        }
    }
    free(hash_table->tablo_basi);
    free(hash_table);
}

int main(){
    struct hash_tablosu *htable = NULL;
    initialize_hash_table(&htable, 3, 5);

    insert_hash_table(htable, "istanbul");
    insert_hash_table(htable, "izmir");
    insert_hash_table(htable, "tekirdag");
    insert_hash_table(htable, "adana");
    insert_hash_table(htable, "samsun");

    print_hash_table(htable);

    free_hash_table(htable);
    return 0;
    }
