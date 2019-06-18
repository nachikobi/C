/*
  最短経路問題
  動的計画法を用いてスタートsとゴールtの最短経路を求める
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define H_MAX 100
#define W_MAX 100
int main(void)
{
  FILE *fp;
  int i, j, k, H, W;
  unsigned long int dp[H_MAX][W_MAX];
  char dp_c[H_MAX][W_MAX];
  clock_t start, end;

  /*ファイルオープン*/
  fp = fopen("maze.txt","r");
  if(fp == NULL)
  {
    printf("error opening file!\n");
    return 1;
  }

  /*HとMの値*/
  fscanf(fp, "%d %d", &H, &W);
  /*格子の読み込み*/
  for (i = 0; i < H; i++)
  {
    for (j = 0; j < W; j++)
    {
      fscanf(fp, "%s", &dp_c[i][j]);
    }
  }
  /*ファイルクローズ*/
  fclose(fp);

  start = clock();

  i = 1;
  j = 1;
  dp[0][0] = 1;
  /*0行目*/
  while (dp_c[0][j] == '.')
  {
    dp[0][j] = 1;
    j++;
  }
  if (dp_c[0][j] == 't')
  {
    dp[0][j] = 1;//ゴールだったら1を入力
  }
  else
  {
    for (k = j; k < W; k++)
    {
      dp[0][k] = 0;//障害物に当たったら、それとそれより右に0を入力
    }
  }

  /*0列目*/
  while (dp_c[i][0] == '.')
  {
    dp[i][0] = 1;
    i++;
  }
  if (dp_c[i][0] == 't')
  {
    dp[i][0] = 1;//ゴールだったら1を出力
  }
  else
  {
    for (k = i; k < H; k++)
    {
      dp[k][0] = 0;//障害物に当たったら、それ以降を0にする
    }
  }

  /*1行目以降*/
  for (i = 1; i < H; i++)
  {
    for (j = 1; j < W; j++)
    {
      if (dp_c[i][j] == '.' || dp_c[i][j] == 't') dp[i][j] = 1;//何もない道、またはゴールなら1を入力
      else dp[i][j] = 0;//障害物なら0を入力
    }
  }

  /*動的計画法*/
  for (j = 1; j < W; j++)
  {
    for (i = 1; i < H; i++)
    {
      if (dp[i][j] != 0) dp[i][j] = dp[i-1][j] + dp[i][j-1];
    }
  }
  /*出力部分*/
  printf("%ld\n", dp[H-1][W-1]);

  end = clock();

  printf("プログラム実行時間 : %f秒\n", (double)(end - start) / CLOCKS_PER_SEC);

  return 0;
}
