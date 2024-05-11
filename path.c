// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>
// #include <string.h>

// #define INF 1000000000
// #define NUM 102
// #define NAME 32
// #define MAX_LEN 80

#include "path.h"


/**
 * @brief vertexのnextをすべてNULLに初期化.
 * @param[in] vertex 隣接リストの始点.
 */
void init_vertex(vertex vertex[])
{
    int i;
    for (i = 1; i < NUM; i++) {
        vertex[i].adj = NULL;
    }
}

/**
 * @brief edgecellのメモリを動的確保し、隣接駅のIDとその所要時間を登録.
 *  nextは今後の処理のためNULLにする.
 * @param[in] id 隣接駅のID.
 * @param[in] weight 所要時間.
 * @return メモリを確保したedgecellのポインタ.
 */
edgelist malloc_edge(int id, int weight)
{
    edgelist p;

    p = (edgelist)malloc(sizeof(edgecell));
    if (p == NULL) {
        printf("malloc error\n");
        exit(1);
    }

    p->id = id;
    p->weight = weight;
    p->next = NULL;

    return p;
}

/**
 * @brief "stations.txt"の一行分を変換して駅名の辞書に登録.
 * @param[in] string 読み取った一行.
 *  形状は"数字(駅ID) 文字列(駅名)".
 *  例："1 渋谷".
 * @param[in] index 駅IDに対応.
 */
void trans_st(char string[], int index, vertex vertex[])
{
    int i, j;
    char buffer[MAX_LEN];

    /* 先頭の駅ID部分を読み飛ばす. */
    i = 0;
    while (string[i] >= '0' && string[i] <= '9') {
        i++;
    }
    i++;    //スペースの読み飛ばし
    j = 0;
    while (string[i] != '\n') {
        buffer[j++] = string[i++];
    }
    buffer[j++] = '\0';

    strncpy(vertex[index].name, buffer, j);
}

/**
 * @brief "adjlist.txt"の一行分を変換して隣接リストに登録.
 * @param[in] string 読み取った一行.
 *  形状は"数字(駅ID) 数字(隣接駅ID),数字(所要時間) 数字,数字 ...".
 *  例："1 2,2 34,3".
 * @param[in] index 駅IDに対応.
 * @param[in] vertex 隣接リストの始点.
 * @sa malloc_edge()
 */
void trans_adj(char string[], int index, vertex vertex[])
{
    edgelist tail, p, q;

    int id, w;

    char buffer[MAX_LEN];
    int i, j;

    /* 先頭の駅ID部分を読み飛ばす. */
    i = 0;
    while (string[i] >= '0' && string[i] <= '9') {
        i++;
    }

    while (string[i] != '\n') {
        /* 隣接駅のIDを読む. */
        i++;    //スペースの読み飛ばし
        j = 0;
        while (string[i] != ',') {
            buffer[j++] = string[i++];
        }
        buffer[j] = '\0';
        id = strtol(buffer, NULL, 10);

        /* 所要時間weightを読む */
        i++;    //スペースの読み飛ばし
        j = 0;
        while (string[i] >= '0' && string[i] <= '9') {
            buffer[j++] = string[i++];
        }
        buffer[j] = '\0';
        w = strtol(buffer, NULL, 10);

        /* メモリの動的確保・読み取ったidとweightを登録. */
        p = malloc_edge(id, w);

        /* 単方向リストなので、tailに挿入すればよい. */
        if (vertex[index].adj == NULL) { //ここで参照するため、init_vertex()ですべてNULLにしている.
            vertex[index].adj = p;
        } else {
            tail->next = p;
        }

        tail = p;
    }
}

//----------------
// read_path.cのmainで用いる関数
//----------------
/**
 * @brief "stations.txt"と"adjlist.txt"の内容を読み取って隣接リストに登録.
 * @param[in] vertex 隣接リストの始点.
 * @sa init_vertex()
 * @sa trans_st()
 * @sa trans_adj()
 */
void read_files(vertex vertex[])
{
    FILE *fp1, *fp2;
    if ((fp1 = fopen("stations.txt", "r")) == NULL) {
        perror("stations.txt");
        exit(1);
    }
    if ((fp2 = fopen("adjlist.txt", "r")) == NULL) {
        perror("adjlist.txt");
        exit(1);
    }

    init_vertex(vertex);

    int i;
    char buffer[MAX_LEN];
    for (i = 1; i < NUM; i++) {
        /* "stations.txt"の変換 */
        fgets(buffer, MAX_LEN, fp1);
        trans_st(buffer, i, vertex);

        /* "adjlist.txt"の変換 */
        fgets(buffer, MAX_LEN, fp2);
        trans_adj(buffer, i, vertex);
    }

    fclose(fp1);
    fclose(fp2);
}

/**
 * @brief 読み取り結果の標準出力.
 * @param[in] vertex 隣接リストの始点.
 */
void print_adjlist(vertex vertex[])
{
    int i;
    edgelist p;

    // /* 書き方１ */
    // for (i = 1; i < NUM; i++) {
    //     printf("From %s\n", vertex[i].name);
    //     for (p = vertex[i].adj; p != NULL; p = p->next) {
    //         printf("  To %s is %d min.\n", vertex[p->id].name, p->weight);
    //     }
    //     printf("\n");
    // }

    /* 書き方２ */
    for (i = 1; i < NUM; i++) {
        printf("%s\n", vertex[i].name);
        for (p = vertex[i].adj; p != NULL; p = p->next) {
            printf("- %s\n  >> %d min.\n", vertex[p->id].name, p->weight);
        }
        printf("\n");
    }
}

/**
 * @brief 読み取り結果のファイル出力.
 * @param[in] vertex 隣接リストの始点.
 */
void fprint_adjlist(vertex vertex[])
{
    int i;
    edgelist p;
    FILE *fp;

    if ((fp = fopen("timelist.txt", "w")) == NULL) {
        perror("timelist.txt");
        exit(1);
    }

    // /* 書き方１ */
    // for (i = 1; i < NUM; i++) {
    //     fprintf(fp, "From %s\n", vertex[i].name);
    //     for (p = vertex[i].adj; p != NULL; p = p->next) {
    //         fprintf(fp, "  To %s is %d min.\n", vertex[p->id].name, p->weight);
    //     }
    //     fprintf(fp, "\n");
    // }

    /* 書き方２ */
    for (i = 1; i < NUM; i++) {
        fprintf(fp, "%s\n", vertex[i].name);
        for (p = vertex[i].adj; p != NULL; p = p->next) {
            fprintf(fp, "- %s\n  >> %d min.\n", vertex[p->id].name, p->weight);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}


void free_vertex(vertex vertex[])
{
    int i;

    for (i = 1; i < NUM; i++) {
        free(vertex[i].adj);
    }

}


//----------------
// find_path.cで用いる関数
//----------------
/**
 * @brief 標準入力から駅名を受けつけ、それに対応するIDを返す.
 * @param[in] vertex 隣接リストの始点.
 * @return 入力された駅名に対応する駅ID.
 */
int input_point(vertex vertex[])
{
    char point[NAME];
    int id;

    scanf("%s", point, NAME);
    getchar();

    /* 一致する駅名を探す */
    for (id = 1; id < NUM; id++) {
        if (strcmp(point, vertex[id].name) == 0) {
            break;
        }
    }

    return id;
}

/**
 * @brief Dijkstra法.(ほぼ教科書ママの実装.)
 * @param[in] start Start.
 * @param[in] goal Goal.
 * @param[in] vertex 隣接リストの始点.
 * @sa swap()
 * @sa upheap()
 * @sa downheap()
 */
void dijkstra(int start, int goal, vertex vertex[])
{
    int heap[NUM]; //集合Uのdistanceによる間接ヒープ.IDで表す.
    int size;
    int p, x, i;
    edgelist t;

    /* スタートの初期化 */
    vertex[start].dist = 0;
    vertex[start].prev = 0;
    heap[1] = start;
    size = 1;

    /* スタート以外のdistanceをINFにしてヒープを作成 */
    for (i = 1; i < NUM; i++) {
        if (i != start) {
            size++;
            heap[size] = i;
            vertex[i].dist = INF;
        }
    }

    /* 配列内での位置を初期化. */
    for (i = 1; i < NUM; i++) {
        vertex[heap[i]].pos = i;
    }

    /* Dijkstraの基本操作 */
    while (size > 0) {
        /* ヒープの先頭(Uの中でdistanceが最小のもののID)を取り出す. */
        p = heap[1];

        printf("Visiting %s\n", vertex[p].name);

        if (vertex[p].dist == INF) { //StartとGoalの間が連結でない場合.
            printf("Sorry! There is no path between %s and %s.\n", vertex[start].name, vertex[goal].name);
            exit(1);
        } else if (p == goal) { //ゴールを訪問出来たら早期終了.
            return;
        }

        /* Uの更新.ヒープの先頭と最後尾の位置を交換、最後尾を削除したものとしてヒープを再構成する. */
        swap(1, size, vertex, heap);
        size--;
        if (size > 0) {
            downheap(1, size, vertex, heap);
        }

        /* 隣接する駅xのdistanceを現在地pからのweightを加味した値と比較して更新. */
        t = vertex[p].adj;
        while (t != NULL) {
            x = t->id;
            if (vertex[x].pos <= size) {
                if (vertex[p].dist + t->weight < vertex[x].dist) {
                    vertex[x].dist = vertex[p].dist + t->weight;
                    vertex[x].prev = p;
                    upheap(vertex[x].pos, vertex, heap);
                }
            }
            t = t->next;
        }
    }
}

/**
 * @brief heapにおける位置をswapする.
 * @param[in] a heapの位置1.
 * @param[in] b　heapの位置2.
 * @param[in] vertex 隣接リストの始点.
 * @param[in] heap 集合Uのdistanceによる間接ヒープ.IDで表されている.
 */
void swap(int a, int b, vertex vertex[], int heap[])
{
    int w;

    vertex[heap[a]].pos = b;
    vertex[heap[b]].pos = a;

    w = heap[a];
    heap[a] = heap[b];
    heap[b] = w;
}

/**
 * @brief upheap.親に向かってのヒープの更新.
 *  kとその親のdistanceを比較し、小さいほうが親になるように交換する(根までループ).
 * @param[in] k heapの位置.
 * @param[in] vertex 隣接リストの始点.
 * @param[in] heap 集合Uのdistanceによる間接ヒープ.IDで表されている.
 * @sa swap()
 */
void upheap(int k, vertex vertex[], int heap[])
{
    int j;

    while (true) {
        if (k <= 1) {
            break;
        }
        j = k / 2;
        if (vertex[heap[j]].dist <= vertex[heap[k]].dist) {
            break;
        }
        swap(k, j, vertex, heap);
        k = j;
    }
}

/**
 * @brief downheap.子に向かってのヒープの再構成.
 *  kとその子のdistanceを比較し、小さいほうが親になるように交換する(葉までループ).
 * @param[in] k heapの位置.
 * @param[in] r heapsize.
 * @param[in] vertex 隣接リストの始点.
 * @param[in] heap 集合Uのdistanceによる間接ヒープ.IDで表されている.
 * @sa swap()
 */
void downheap(int k, int r, vertex vertex[], int heap[])
{
    int j;

    while (true) {
        j = 2 * k;
        if (j > r) {
            break;
        }
        if (j != r) {
            if (vertex[heap[j+1]].dist < vertex[heap[j]].dist) {
                j++;
            }
        }
        if (vertex[heap[k]].dist <= vertex[heap[j]].dist) {
            break;
        }
        swap(k, j, vertex, heap);
        k = j;
    }
}

/**
 * @brief StartとGoalを繋ぐ最短経路および総所要時間を標準出力する.
 * @param[in] goal Goal.
 * @param[in] vertex 隣接リストの始点.
 */
void print_path(int goal, vertex vertex[])
{
    int pathlist[NUM];
    int p;
    int size;

    /* Goalから遡って経路を調べる. */
    p = goal;
    size = 0;
    do {
        pathlist[size] = p;
        size++;
        p = vertex[p].prev;
    } while (p != 0);

    /* 出力. */
    printf("\n**Shortest Path**\n");
    while (size > 0) {
        size--;
        printf("%s", vertex[pathlist[size]].name);
        if (size > 0) {
            printf(" - ");
        }
    }
    printf("\n\n**Total Time**\n");
    printf("  %d min.\n\n", vertex[goal].dist);
}