#include <stdio.h>
#define V 5
#define H 10

void imit(char tbl[V][H]);
void prt1(char tbl[V][H]);
void prt2(char tbl[V][H]);
void prt3(char tbl[V][H]);


int main(void) {
	char tbl[V][H];
	imit(tbl);
	prt1(tbl);
	printf("\n");
	prt2(tbl);
	printf("\n");
	prt3(tbl);
}

void imit(char tbl[V][H]){
	int x, y;
	int num=0;
	for ( x = 0; x < V; x++)
	{
		for (y = 0; y < H; y++)
		{
			tbl[x][y] = num;
			num++;
		}
	}
}
void prt1(char tbl[V][H]) {
	int x, y;
	for ( x = 0; x < V; x++)
	{
		for ( y = 0; y < H; y++)
		{
			printf("%3d", tbl[x][y]);
		}
		printf("\n");
	}
}

void prt2(char tbl[V][H]) {
	int x, y;
	for (  x= V-1;  x>-1;x--)
	{
		for ( y = H-1; y > -1; y--)
		{
			printf("%3d", tbl[x][y]);
		}
		printf("\n");
	}
}

void prt3(char tbl[V][H]) {
	int x, y;
	for ( y = 0; y < H; y++)
	{
		for ( x = 0; x < V; x++)
		{
			printf("%3d", tbl[y][x]);
		}
		prtinf("\n");
	}
}