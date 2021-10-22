#include <stdio.h>

int main(void) {
	int a[10][10];
	int i, j;
#


	printf("+----+----+----+----+----+----+----+----+----+----+\n");
	printf("   ");
	printf("  |");
	i = 0;
		for (j = 0; j < 9; j++)
		{
			a[i][j]= (i + 1) * (j+1);
			printf("%3d", a[i][j]);
			printf(" |");
		}
		printf("\n");
//ˆê—ñ

		
for (i = 0; i < 9; ++i) {
	
		for (j = i; j < 9; ++j) {
		
		a[i][j] = (i + 1) * (j + 1);
			a[j][i] = a[i][j];
			
		}
	}

	printf("+----+----+----+----+----+----+----+----+----+----+\n");
	
	for (i = 0; i < 9; i++) {

		int j = 0;
		
		
		printf("%3d  ", a[i][j]);
	
		for (j = 0; j < 9; j++) {
			printf("|");
			printf("%3d ", a[i][j]);
	
		}printf("|\n");
		printf("+----+----+----+----+----+----+----+----+----+----+\n");
	}
	return 0;
}