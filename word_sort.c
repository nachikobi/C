/*
  二分探索を用いてランダムに並べられた単語を辞書順にする
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tnode{
  char word[22];  //単語
  struct tnode *lt; //左の子
  struct tnode *rt; //右の子
} tnode;

tnode *createTNode(char *array){ //単語ノードの作成をする関数
  tnode *tree;
  tree = malloc(sizeof(tnode));
  if (tree==NULL) exit(2); //ノード作成失敗
  strcpy(tree->word,array);
  tree->lt = NULL;
  tree->rt = NULL;
  return tree;
}

tnode *insertTerm(tnode *tree, char *array){  //二分探索木への単語の追加する関数
  if (tree==NULL) { //新たに単語を追加するとき
    tree = createTNode(array);
  }else if (strcmp(tree->word, array)>0) {  //探索続行(左)
    tree->lt = insertTerm(tree->lt, array); 
  }else if (strcmp(tree->word, array)<0) {  //探索続行(右)
    tree->rt = insertTerm(tree->rt, array);
  }
  return tree;
}

void printTree(tnode *tree){  //中間順巡回による単語の出力をする関数
  if (tree!=NULL) {
    printTree(tree->lt);
    printf("%s", tree->word);
    printTree(tree->rt);
  }
}

void freeTree(tnode *tree){ //メモリの解放をする関数
  if (tree!=NULL) {
    freeTree(tree->lt);
    freeTree(tree->rt);
    free(tree);
  }
}

int main(int argc, char **argv) {
  tnode *root_tree=NULL;
  char *fname, array[22]={};
  FILE *fp;
  if (argc!=2) {  //引数の数が想定と異なるとき
    fprintf(stderr, "Usage: %s prob_file\n", argv[0]);
  }
  fname = argv[1];

  fp = fopen(fname, "r"); //ファイルオープン
  if (fp==NULL) {
    printf("error opening file!\n");
    return 1;
  }

  while (fgets(array, 21, fp)!=NULL) { //二分探索木の作成
    root_tree = insertTerm(root_tree, array);
  }
  printTree(root_tree);  //単語の出力
  freeTree(root_tree); //メモリの解放
  return 0;
}
