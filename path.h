#ifndef PATH_H //二重includeの防止
#define PATH_H

// -----------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// -----------------
#define INF 1000000000 //疑似的な無限
#define NUM 102 //駅数+1.配列の引数にする.
#define NAME 32 //駅名
#define MAX_LEN 80 //buffer

// -----------------
typedef struct edgecell edgecell;
typedef edgecell* edgelist;
typedef struct vertex vertex;

// -----------------
/**
 * @brief 構造体edgecell(教科書より).辺のリストを構成する.
 * 単方向リストをなし、nextポインタの他に駅のIDと所要時間を持つ.
 */
struct edgecell
{
    edgelist next;//単方向のポインタ.
    int id;//駅ID.destination.
    int weight;//所要時間.
};

/**
 * @brief 構造体vertex(教科書より).隣接リストの始点となる配列を構成する.
 */
struct vertex
{
    edgelist adj;//辺のリストの一つ目をさすポインタ.
    char name[NAME];//駅名.

    int pos;//ヒープの配列内での位置.heappos.
    int dist;//startからの所要時間.distance.
    int prev;//直前の駅のID.previous.
};

// -----------------
/* 詳しくはpath.cを参照. */
/* read_path.c以降用いる関数群 */
void init_vertex(vertex vertex[]);
edgelist malloc_edge(int id, int weight);
void trans_st(char string[], int index, vertex vertex[]);
void trans_adj(char string[], int index, vertex vertex[]);

void read_files(vertex vertex[]);
void print_adjlist(vertex vertex[]);
void fprint_adjlist(vertex vertex[]);
void free_vertex(vertex vertex[]);

/* find_path.c以降用いる関数群 */
int input_point(vertex vertex[]);

void dijkstra(int start, int goal, vertex vertex[]);
void swap(int a, int b, vertex vertex[], int heap[]);
void upheap(int k, vertex vertex[], int heap[]);
void downheap(int k, int r, vertex vertex[], int heap[]);

void print_path(int goal, vertex vertex[]);

// -----------------
#endif //二重includeの防止