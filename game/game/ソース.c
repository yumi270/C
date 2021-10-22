#include <stdio.h> //printf
#include <stdlib.h> //srand()
#include <Windows.h>
#include <time.h>
#pragma warning(disable:4996)
#define WORLD_H 38// 横の大きさ
#define WORLD_W 76// 縦の大きさ
#define LOOP_NO 1000

void init_map(char map[WORLD_H][WORLD_W]);
void prt_map(char map[WORLD_H][WORLD_W]);
void copy_map(char map[WORLD_H][WORLD_W]);
void file_map(char map[WORLD_H][WORLD_W], FILE* fp);

int main(void){

	//ファイルポインタ定義
	FILE* fp; 
	char* filename = "sample_data1.txt";

	char map[WORLD_H][WORLD_W];
	
	//ファイルオープン
	if ((fp = fopen(filename, "r")) != NULL) {
	
		printf( "sample_data1\n");// オープン成功


	//二次元配列

	printf("\033[2J");// 画面を消す
	file_map(map, fp);

	int i;
	for (i = 0; i <= LOOP_NO; i++)
	{

		printf("\033[2;1H");// カーソル位置を、高さ2行目、横1文字目に移動
		printf("世代数:%d\n", i);


		prt_map(map);
		copy_map(map);
	}
}else {
	printf("ファイルオープン失敗\n");// オープン失敗

	}
	return 0;
}
//マップを初期化する関数,
void init_map(char map[WORLD_H][WORLD_W]) {
	srand((unsigned int)time(NULL));

	//初期化ルーチン
	int y;//纵
	int x;//横
	for (y = 0; y < WORLD_H; y++)//ループ	
	{

		for (x = 0; x < WORLD_W; x++) {

			if (rand()%10>6)
			{
				map[y][x] = 0;
			}
			else {
				map[y][x] = 1;
			}		
		}
	}
}
// map表示
void prt_map(char map[WORLD_H][WORLD_W]) {

	int y;
	int x;

	for (y = 0; y < WORLD_H; y++) {
		for (x = 0; x < WORLD_W; x++) {
			if (map[y][x] == 1) {
				printf("@");
			}
			else
			{
				printf(".");
			}	
		}
		printf("\n");
	}
}
// copy map
void copy_map(char map[WORLD_H][WORLD_W]) {
	char temp[WORLD_H][WORLD_W];

	int y;//纵
	int x;//横
	int sum;

	//copyパート
	for (y = 0; y < WORLD_H; y++) {
		for (x = 0; x < WORLD_W; x++)
		{
			temp[y][x] = map[y][x];
		}

	}
	//世代を進める
	for (y = 0; y < WORLD_H; y++)
	{
		for (x = 0; x < WORLD_W; x++)
		{
			sum = 0;//0クリア
			if (y - 1 >= 0 && x - 1 >= 0)
				sum += temp[y - 1][x - 1];//左上
			if (x - 1 >= 0)
				sum += temp[y][x - 1];//左
			if (y + 1 < WORLD_H && x - 1 >= 0)
				sum += temp[y + 1][x - 1];//左下
			if (y + 1 < WORLD_H)
				sum += temp[y + 1][x];//下
			if (y + 1 < WORLD_H && x + 1 < WORLD_W)
				sum += temp[y + 1][x + 1];//右下
			if (x + 1 < WORLD_W)
				sum += temp[y][x + 1];//右
			if (y - 1 >= 0 && x + 1 < WORLD_W)
				sum += temp[y - 1][x + 1];////右上
			if (y - 1 >= 0)
				sum += temp[y - 1][x];//上
				//判定temp[y][x]
			if (map[y][x] == 0 && sum == 3) {
				map[y][x] = 1;
			}
			if (map[y][x] == 1 && (sum <= 1 || sum>=4)) {
				map[y][x] = 0;
			}
		}
	}
}
//初期データをファイルから読込み初期化する
void file_map(char map[WORLD_H][WORLD_W], FILE* fp) {

	/// ファイルの読み込み
	
	int y;//纵
	int x;//横
	int len;//長さ
	char buf[128];
	for (y = 0; y < WORLD_H; y++) {
		for (x = 0; x < WORLD_W; x++) {
			map[y][x] = 0;	//mapの内容をすべて0クリアする
		}
	}
	y = 0;
	while (fgets(buf, 128, fp) >0)  //buf1行の読み込み

	{
		len = strlen(buf); //1行の長さ

		if (len > WORLD_W)//配列より大き
		{
			len = WORLD_W;//配列の最大値
		}

		for (x = 0; x < len; x++) {
			if (buf[x] == '1')
			{
				map[y][x] = 1;
			}
			else {
				map[y][x] = 0;
			}
		}
		while (x < WORLD_W) {
			map[y][x] = 0;
			x++;
		}

		y++;
		if (y >= WORLD_H) {
			break;
		}
	}	
	fclose(fp);
}
