#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
// Yapılar
typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
} Graph;

typedef struct Edge {
    int src, dest, weight;
} Edge;

// Yeni düğüm oluşturma
Node* createNode(int vertex, int weight) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Graf oluşturma
Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(Node*));

    for (int i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;

    return graph;
}

// Kenar ekleme fonksiyonu
void addEdgeWithList(Graph* graph, Edge edges[], int* edgeCount, int src, int dest, int weight) {
    Node* newNode = createNode(dest, weight);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src, weight);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;

    edges[*edgeCount].src = src;
    edges[*edgeCount].dest = dest;
    edges[*edgeCount].weight = weight;
    (*edgeCount)++;
}

// BFS Algoritması
void bfs(Graph* graph, int startVertex) {
    bool* visited = malloc(graph->numVertices * sizeof(bool));
    for (int i = 0; i < graph->numVertices; i++)
        visited[i] = false;

    int* queue = malloc(graph->numVertices * sizeof(int));
    int front = 0, rear = 0;

    visited[startVertex] = true;
    queue[rear++] = startVertex;

    printf("BFS Traversal: ");

    while (front < rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }

    printf("\n");
    free(visited);
    free(queue);
}

// DFS Yardımcı Fonksiyonu
void dfsHelper(Graph* graph, int vertex, bool* visited) {
    visited[vertex] = true;
    printf("%d ", vertex);

    Node* temp = graph->adjLists[vertex];
    while (temp) {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex])
            dfsHelper(graph, adjVertex, visited);
        temp = temp->next;
    }
}

// DFS Algoritması
void dfs(Graph* graph, int startVertex) {
    bool* visited = malloc(graph->numVertices * sizeof(bool));
    for (int i = 0; i < graph->numVertices; i++)
        visited[i] = false;

    printf("DFS Traversal: ");
    dfsHelper(graph, startVertex, visited);
    printf("\n");

    free(visited);
}

// Dijkstra Algoritması
void dijkstra(Graph* graph, int startVertex) {
    int* distances = malloc(graph->numVertices * sizeof(int));
    bool* visited = malloc(graph->numVertices * sizeof(bool));

    for (int i = 0; i < graph->numVertices; i++) {
        distances[i] = INT_MAX;
        visited[i] = false;
    }
    distances[startVertex] = 0;

    for (int i = 0; i < graph->numVertices - 1; i++) {
        int minDistance = INT_MAX, minIndex;

        for (int v = 0; v < graph->numVertices; v++) {
            if (!visited[v] && distances[v] < minDistance) {
                minDistance = distances[v];
                minIndex = v;
            }
        }

        visited[minIndex] = true;

        Node* temp = graph->adjLists[minIndex];
        while (temp) {
            int v = temp->vertex;
            if (!visited[v] && distances[minIndex] != INT_MAX &&
                distances[minIndex] + temp->weight < distances[v]) {
                distances[v] = distances[minIndex] + temp->weight;
            }
            temp = temp->next;
        }
    }

    printf("Dijkstra distances from vertex %d:\n", startVertex);
    for (int i = 0; i < graph->numVertices; i++)
        printf("Vertex %d: %d\n", i, distances[i]);

    free(distances);
    free(visited);
}

// Floyd-Warshall Algoritması
void floydWarshall(int** graph, int vertices) {
    int dist[vertices][vertices];

    for (int i = 0; i < vertices; i++)
        for (int j = 0; j < vertices; j++)
            dist[i][j] = graph[i][j];

    for (int k = 0; k < vertices; k++) {
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    printf("Floyd-Warshall shortest paths:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (dist[i][j] == INT_MAX)
                printf("INF ");
            else
                printf("%d ", dist[i][j]);
        }
        printf("\n");
    }
}

// Kruskal Yardımcı Fonksiyonlar
typedef struct Subset {
    int parent;
    int rank;
} Subset;

int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void unionSets(Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank)
        subsets[rootX].parent = rootY;
    else if (subsets[rootX].rank > subsets[rootY].rank)
        subsets[rootY].parent = rootX;
    else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

int edgeComparator(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

// Kruskal Algoritması
void kruskalMST(Edge edges[], int numEdges, int numVertices) {
    Subset* subsets = malloc(numVertices * sizeof(Subset));
    for (int v = 0; v < numVertices; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    qsort(edges, numEdges, sizeof(Edge), edgeComparator);

    Edge* mst = malloc((numVertices - 1) * sizeof(Edge));
    int e = 0, i = 0;

    while (e < numVertices - 1 && i < numEdges) {
        Edge nextEdge = edges[i++];

        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);

        if (x != y) {
            mst[e++] = nextEdge;
            unionSets(subsets, x, y);
        }
    }

    printf("Kruskal's MST:\n");
    for (int j = 0; j < e; j++)
        printf("Edge %d - %d: %d\n", mst[j].src, mst[j].dest, mst[j].weight);

    free(mst);
    free(subsets);
}

// Prim Algoritması
void primMST(Graph* graph) {
    int* parent = malloc(graph->numVertices * sizeof(int));
    int* key = malloc(graph->numVertices * sizeof(int));
    bool* mstSet = malloc(graph->numVertices * sizeof(bool));

    for (int i = 0; i < graph->numVertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;  // Başlangıç düğümü
    parent[0] = -1; // Başlangıç düğümünün ebeveyni yok

    for (int count = 0; count < graph->numVertices - 1; count++) {
        int u = -1;
        for (int v = 0; v < graph->numVertices; v++) {
            if (!mstSet[v] && (u == -1 || key[v] < key[u])) {
                u = v;
            }
        }

        mstSet[u] = true;

        Node* temp = graph->adjLists[u];
        while (temp) {
            int v = temp->vertex;
            if (!mstSet[v] && temp->weight < key[v]) {
                key[v] = temp->weight;
                parent[v] = u;
            }
            temp = temp->next;
        }
    }

    printf("Prim's MST:\n");
    for (int i = 1; i < graph->numVertices; i++) {
        printf("Edge %d - %d: %d\n", parent[i], i, key[i]);
    }

    free(parent);
    free(key);
    free(mstSet);
}

// Bellman-Ford Algoritması
void bellmanFord(Graph* graph, int startVertex) {
    int* distances = malloc(graph->numVertices * sizeof(int));

    for (int i = 0; i < graph->numVertices; i++)
        distances[i] = INT_MAX;
    distances[startVertex] = 0;

    // Relaxation işlemi: V-1 kez tekrarla
    for (int i = 1; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            Node* temp = graph->adjLists[j];
            while (temp) {
                if (distances[j] != INT_MAX && distances[j] + temp->weight < distances[temp->vertex]) {
                    distances[temp->vertex] = distances[j] + temp->weight;
                }
                temp = temp->next;
            }
        }
    }

    // Negatif ağırlık döngüsü kontrolü
    for (int i = 0; i < graph->numVertices; i++) {
        Node* temp = graph->adjLists[i];
        while (temp) {
            if (distances[i] != INT_MAX && distances[i] + temp->weight < distances[temp->vertex]) {
                printf("Graph contains negative weight cycle\n");
                free(distances);
                return;
            }
            temp = temp->next;
        }
    }

    printf("Bellman-Ford distances from vertex %d:\n", startVertex);
    for (int i = 0; i < graph->numVertices; i++) {
        if (distances[i] == INT_MAX)
            printf("Vertex %d: INF\n", i);
        else
            printf("Vertex %d: %d\n", i, distances[i]);
    }

    free(distances);
}


int main() {
    int vertices = 8; // Grafın toplam dügüm sayısı
    int maxEdges = 30; // Maksimum kenar sayısı
    Edge edges[maxEdges]; // Kenar listesi
    int edgeCount = 0; // Kenar sayacı

    Graph* graph = createGraph(vertices);

    addEdgeWithList(graph, edges, &edgeCount, 0, 2, 1);
    addEdgeWithList(graph, edges, &edgeCount, 2, 0, 1);
    addEdgeWithList(graph, edges, &edgeCount, 0, 6, 3);
    addEdgeWithList(graph, edges, &edgeCount, 6, 0, 3);
    addEdgeWithList(graph, edges, &edgeCount, 5, 3, 3);
    addEdgeWithList(graph, edges, &edgeCount, 3, 5, 3);
    addEdgeWithList(graph, edges, &edgeCount, 3, 2, 3);
    addEdgeWithList(graph, edges, &edgeCount, 2, 3, 3);
    addEdgeWithList(graph, edges, &edgeCount, 1, 2, 1);
    addEdgeWithList(graph, edges, &edgeCount, 2, 1, 1);
    addEdgeWithList(graph, edges, &edgeCount, 6, 5, 5);
    addEdgeWithList(graph, edges, &edgeCount, 5, 6, 5);
    addEdgeWithList(graph, edges, &edgeCount, 1, 3, 1);
    addEdgeWithList(graph, edges, &edgeCount, 3, 1, 1);
    addEdgeWithList(graph, edges, &edgeCount, 0, 1, 2);
    addEdgeWithList(graph, edges, &edgeCount, 1, 0, 2);
    addEdgeWithList(graph, edges, &edgeCount, 3, 4, 2);
    addEdgeWithList(graph, edges, &edgeCount, 4, 3, 2);
    addEdgeWithList(graph, edges, &edgeCount, 6, 2, 4);
    addEdgeWithList(graph, edges, &edgeCount, 2, 6, 4);
    addEdgeWithList(graph, edges, &edgeCount, 4, 5, 4);
    addEdgeWithList(graph, edges, &edgeCount, 5, 4, 4);
    addEdgeWithList(graph, edges, &edgeCount, 6, 7, 5);
    addEdgeWithList(graph, edges, &edgeCount, 7, 6, 5);
    addEdgeWithList(graph, edges, &edgeCount, 2, 5, 8);
    addEdgeWithList(graph, edges, &edgeCount, 5, 2, 8);
    addEdgeWithList(graph, edges, &edgeCount, 5, 7, 10);
    addEdgeWithList(graph, edges, &edgeCount, 7, 5, 10);

    // Algoritmaların çalıştırılması
    bfs(graph, 0);
    dfs(graph, 0);
    dijkstra(graph, 0);

    // Floyd-Warshall
    int** graphMatrix = malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        graphMatrix[i] = malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++) {
            if (i == j)
                graphMatrix[i][j] = 0;
            else
                graphMatrix[i][j] = INT_MAX;
        }
    }

    for (int i = 0; i < edgeCount; i++) {
        graphMatrix[edges[i].src][edges[i].dest] = edges[i].weight;
        graphMatrix[edges[i].dest][edges[i].src] = edges[i].weight;
    }
    printf("\n--- Floyd-Warshall Algoritmasi ---\n");
    floydWarshall(graphMatrix, vertices);

    // Kruskal
    printf("\n--- Kruskal Algoritmasi ---\n");
    kruskalMST(edges, edgeCount, vertices);

    printf("\n--- Prim Algoritmasi ---\n");
    primMST(graph);

    printf("\n--- Bellman-Ford Algoritmasi ---\n");
    bellmanFord(graph, 0);

    /*// Bellek temizleme
    for (int i = 0; i < vertices; i++) {
        free(graphMatrix[i]);
    }
    free(graphMatrix);
    free(graph);*/

    return 0;
}



/*// Grafýn kenar ekleme fonksiyonu
void addEdge(Graph* graph, int src, int dest, int weight) {
    Node* newNode = createNode(dest, weight);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Yönsüz graf için ikinci kenar
    newNode = createNode(src, weight);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}*/

    /*int vertices = 5;
    Graph* graph = createGraph(vertices);

    addEdge(graph, 0, 1, 2);
    addEdge(graph, 0, 4, 9);
    addEdge(graph, 1, 2, 4);
    addEdge(graph, 1, 3, 7);
    addEdge(graph, 2, 3, 1);
    addEdge(graph, 3, 4, 3);

    printf("Dijkstra Algorithm:\n");
    dijkstra(graph, 0);

    int** adjacencyMatrix = malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        adjacencyMatrix[i] = malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++)
            adjacencyMatrix[i][j] = (i == j) ? 0 : INT_MAX;
    }

    adjacencyMatrix[0][1] = 2;
    adjacencyMatrix[0][4] = 9;
    adjacencyMatrix[1][2] = 4;
    adjacencyMatrix[1][3] = 7;
    adjacencyMatrix[2][3] = 1;
    adjacencyMatrix[3][4] = 3;

    printf("\nFloyd-Warshall Algorithm:\n");
    floydWarshall(adjacencyMatrix, vertices);

    printf("\nBFS Algorithm:\n");
    bfs(graph, 0);

    printf("\nDFS Algorithm:\n");
    dfs(graph, 0);

    /*for (int i = 0; i < vertices; i++)
        free(adjacencyMatrix[i]);
    free(adjacencyMatrix);

    return 0;*/


