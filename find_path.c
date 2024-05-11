// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>
// #include <string.h>

// #define INF 1000000000
// #define NUM 102
// #define NAME 32
// #define MAX_LEN 80

#include "path.h"

/*
    流れ
    ・重み付き隣接リストの始点を用意.
    ・"stations.txt"と"adjlist.txt"を開いて重み付き隣接リストを作成.>>>read_files()
    　>read_files()内部
    　・vertexのadjをすべてNULLに初期化.(trans_adj()で利用するため)>>>init_vertex()
    　・"stations.txt"をもとに、駅名を登録する.>>>trans_st()
    　・"adjlist.txt"をもとに、所要時間を作成する.>>>trans_adj()
        >trans_adj()内部
        ・読み取ったものを新しくリストにつなぐため、メモリの動的確保.>>>malloc_edge()
    ・出発駅名を標準入力から受け取り、駅IDに変換.>>>input_point()
    　ただし、見つからなければもう一度受け取り直す.
    ・到着駅名を標準入力から受け取り、駅IDに変換.>>>input_point()
    　ただし、見つからない・あるいは出発駅名と同じであればもう一度受け取り直す.
    ・Dijkstra法に基づき出発駅と到着駅を結ぶ張る木を作成.>>>dijkstra()
    　>dijkstra()内部
      基本教科書通り。ただし、計算時間短縮のため、全駅には訪問せず、到着駅に訪問できた時点で終了とする.
      ・教科書に従い、swap, downheap, upheapを作成.
      　vertex/heapのscopeの関係上、教科書よりも引数は多く取っている.
    ・張る木をもとにして経路および総所要時間を出力.>>>print_path()
    ・メモリ開放.>>>free_vertex()
*/


int main()
{
    vertex vertex[NUM];    //隣接リストの始点.
    int s, g;

    read_files(vertex);

    while (true) {
        printf("Input Start: ");
        s = input_point(vertex);
        if (s == NUM) {
            printf("Sorry! Could not find the station.\n");
        } else {
            break;
        }
    }

    while (true) {
        printf("Input Goal: ");
        g = input_point(vertex);
        if (g == NUM) {
            printf("Sorry! Could not find the station.\n");
        } else if (g == s) {
            printf("Oops! It's same as the Start.\n");
        } else {
            break;
        }
    }

    dijkstra(s, g, vertex);
    print_path(g, vertex);

    free_vertex(vertex);

    return 0;
}