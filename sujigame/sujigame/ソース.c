
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#pragma warning(disable:4996)
#define MAX 900
int main() {
	int tbl[MAX];
	int su;
    int loop;
	int temp=1;
	int ransu;
	int kaisu=0;
	srand((unsigned int)time(NULL));
	ransu = (100 + rand() % 900);
	for(loop=0;loop<MAX;loop++){
        printf("3桁の数字を入力してください:\n");
        (void)scanf("%d",&su);
		tbl[loop + 1] = su;
		if(ransu>su){
			printf("%d は、小さいです\n", su);
		}else if(ransu< su){
			printf("%d は、大きいです\n", su);
		}else if (ransu == su){
			printf("%dで、当たりです。\n", su);
			for (kaisu = 1; kaisu <= temp; kaisu++) {
				printf("%2d回目は%d\n", kaisu, tbl[kaisu]);
			}
			break;
		}
        temp++;
	}
	return 0;
}