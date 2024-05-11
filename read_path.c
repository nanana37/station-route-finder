// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define NUM 102
// #define NAME 32
// #define MAX_LEN 80

#include "path.h"

/*
    重み付き隣接リスト：各駅から出ている辺の情報を登録.
    構造:配列 + 線形リスト
    ・リストの始点となる駅の配列vertexを用意.
    ・各駅に対し、辺の情報を単方向につないでいく.
    ・各辺は構造体edgecellによって表される.
    ・edgecellのポインタは教科書に合わせ、edgelistと呼称する.
*/
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
    ・各駅について、隣接駅の駅名と所要時間を出力する.>>>print_adjlist()/fprint_adjlist()
    　書き方は2種類用意したが、2のほうが簡潔で適切と考えている.
    ・メモリ開放.>>>free_vertex()
*/

int main()
{
    vertex vertex[NUM];    //隣接リストの始点.

    read_files(vertex);
    print_adjlist(vertex);
    fprint_adjlist(vertex);

    free_vertex(vertex);

    return 0;
}