
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
        printf("3���̐�������͂��Ă�������:\n");
        (void)scanf("%d",&su);
		tbl[loop + 1] = su;
		if(ransu>su){
			printf("%d �́A�������ł�\n", su);
		}else if(ransu< su){
			printf("%d �́A�傫���ł�\n", su);
		}else if (ransu == su){
			printf("%d�ŁA������ł��B\n", su);
			for (kaisu = 1; kaisu <= temp; kaisu++) {
				printf("%2d��ڂ�%d\n", kaisu, tbl[kaisu]);
			}
			break;
		}
        temp++;
	}
	return 0;
}