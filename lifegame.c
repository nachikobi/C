/*
  ライフゲーム(周期境界を考慮する)
*/

#include <stdio.h>
#define HEIGHT 50
#define WIDTH 100

void cul(char [HEIGHT+2][WIDTH+2], char [HEIGHT+2][WIDTH+2]);

int main(void)
{
  FILE *fp_in, *fp_out;
  int n, i, j, count;
  char array1[HEIGHT+2][WIDTH+2], array2[HEIGHT+2][WIDTH+2];//全方向の端はずっと死セルとして考えるので+2

  /*ファイルオープン*/
  fp_in = fopen("lifegame.txt", "r");
  if(fp_in == NULL)
  {
    printf("error opening file!\n");
    return 1;
  }
  fp_out = fopen("lifegame_output.txt", "w");
  /*配列1にコピー*/
  for (i = 1; i < HEIGHT+1; i++)
  {
    for (j = 1; j < WIDTH+1; j++)
    {
      fscanf(fp_in, "%c\n", &array1[i][j]);//改行が入るのを回避
    }
  }
  /*ファイルクローズ*/
  fclose(fp_in);
  /*n読み込み*/
  scanf("%d", &n);
  /*count世代*/
  for (count = 0; count < n; count++)
  {
    if (count % 2 == 1)
    {
      cul(array2, array1);
    }
    else
    {
      cul(array1, array2);
    }
  }
  /*ファイルに書き込み*/
  if (n % 2 == 0)
  {
    for (i = 1; i < HEIGHT; i++)
    {
      for (j = 1; j < WIDTH+1; j++)
      {
        fprintf(fp_out, "%c", array1[i][j]);
      }
      fprintf(fp_out, "\n");
    }
    for (j = 1; j < WIDTH+1; j++)
    {
      fprintf(fp_out, "%c", array1[HEIGHT][j]);//最後に改行が入るのを回避
    }
  }
  else
  {
    for (i = 1; i < HEIGHT; i++)
    {
      for (j = 1; j < WIDTH+1; j++)
      {
        fprintf(fp_out, "%c", array2[i][j]);
      }
      fprintf(fp_out, "\n");
    }
    for (j = 1; j < WIDTH+1; j++)
    {
      fprintf(fp_out, "%c", array2[HEIGHT][j]);//最後に改行が入るのを回避
    }
  }
  /*ファイルクローズ*/
  fclose(fp_out);

  return 0;
}

void cul(char array_a[HEIGHT+2][WIDTH+2], char array_b[HEIGHT+2][WIDTH+2])
{
  int i, j, k, l, count = 0;
  /*端の壁の処理*/
  for (i = 1; i < HEIGHT+1; i++)
  {
    array_a[i][0] = array_a[i][WIDTH];
    array_a[i][WIDTH+1] = array_a[i][1];
  }
  for (j = 1; j < WIDTH+1; j++)
  {
    array_a[0][j] = array_a[HEIGHT][j];
    array_a[HEIGHT+1][j] = array_a[1][j];
  }
  array_a[0][0] = array_a[HEIGHT][WIDTH];
  array_a[0][WIDTH+1] = array_a[HEIGHT][1];
  array_a[HEIGHT+1][0] = array_a[1][WIDTH];
  array_a[HEIGHT+1][WIDTH+1] = array_a[1][1];//四隅の処理
  /*次世代の計算*/
  for (i = 1; i < HEIGHT+1; i++)
  {
    for (j = 1; j < WIDTH+1; j++)
    {
      for (k = i-1; k <= i+1; k++)
      {
        for (l = j-1; l <= j+1; l++)
        {
          if (array_a[k][l] == '1') count++;//生セルだったらカウント＋１
        }
      }
      if (array_a[i][j] == '0')//死セルだった場合
      {
        if (count == 3) array_b[i][j] = '1';//生セルになる
        else array_b[i][j] = '0';//死セルのまま
      }
      else//生セルだった場合
      {
        if (count == 3 || count == 4) array_b[i][j] = '1';//生セルのまま
        else array_b[i][j] = '0';//死セルになる
      }
      count = 0;//countの初期化
    }
  }
}
