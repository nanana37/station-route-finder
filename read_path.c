// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define NUM 102
// #define NAME 32
// #define MAX_LEN 80

#include "path.h"

/*
    �d�ݕt���אڃ��X�g�F�e�w����o�Ă���ӂ̏���o�^.
    �\��:�z�� + ���`���X�g
    �E���X�g�̎n�_�ƂȂ�w�̔z��vertex��p��.
    �E�e�w�ɑ΂��A�ӂ̏���P�����ɂȂ��ł���.
    �E�e�ӂ͍\����edgecell�ɂ���ĕ\�����.
    �Eedgecell�̃|�C���^�͋��ȏ��ɍ��킹�Aedgelist�ƌď̂���.
*/
/*
    ����
    �E�d�ݕt���אڃ��X�g�̎n�_��p��.
    �E"stations.txt"��"adjlist.txt"���J���ďd�ݕt���אڃ��X�g���쐬.>>>read_files()
    �@>read_files()����
    �@�Evertex��adj�����ׂ�NULL�ɏ�����.(trans_adj()�ŗ��p���邽��)>>>init_vertex()
    �@�E"stations.txt"�����ƂɁA�w����o�^����.>>>trans_st()
    �@�E"adjlist.txt"�����ƂɁA���v���Ԃ��쐬����.>>>trans_adj()
        >trans_adj()����
        �E�ǂݎ�������̂�V�������X�g�ɂȂ����߁A�������̓��I�m��.>>>malloc_edge()
    �E�e�w�ɂ��āA�אډw�̉w���Ə��v���Ԃ��o�͂���.>>>print_adjlist()/fprint_adjlist()
    �@��������2��ޗp�ӂ������A2�̂ق����Ȍ��œK�؂ƍl���Ă���.
    �E�������J��.>>>free_vertex()
*/

int main()
{
    vertex vertex[NUM];    //�אڃ��X�g�̎n�_.

    read_files(vertex);
    print_adjlist(vertex);
    fprint_adjlist(vertex);

    free_vertex(vertex);

    return 0;
}