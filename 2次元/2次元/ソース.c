#include <stdio.h>  // standard input output
#define VSIZE 5 // vertical èc
#define HSIZE 10// horizontal â°


void init_tbl(char tbl[VSIZE][HSIZE]); // initial table èâÉ^Å[ÉuÉã table with numbers from 0-49
void prt_tbl(char tbl[VSIZE][HSIZE]);// print the table
void prt_tbl_rev(char tbl[VSIZE][HSIZE]);//print the table in reverse 
void prt_tbl_y_x(char tbl[VSIZE][HSIZE]);


int main(void) {

	char tbl[VSIZE][HSIZE];
	init_tbl(tbl);
	prt_tbl(tbl);
	printf("\n");
	prt_tbl_rev(tbl);
	printf("\n");
	prt_tbl_y_x(tbl);

	return 0;

}

void init_tbl(char tbl[VSIZE][HSIZE]) {
	int x, y;//we create x and y
	int num = 0;// we specify a counter to count the number of loops
	for (y = 0; y < VSIZE; y++) { //create a loop that will run through y(rows), and increase its value by 1 in each loop until we create 5 rows
		for (x = 0; x < HSIZE; x++) { // creating a loop for will run through x(columns) until we create 10 columns
			tbl[y][x] = num;// will put a number inside the position y(row) x(column) which will increase by 1 each time.
			num++;//increaing the number each time
			//printf("%3d ", tbl[y][x]);
		}
		//printf("\n");
	}
}



// will create a 5*10 table which will have numbers from 0-49
// this table is used as a template table that will be printed differently each time.

void prt_tbl(char tbl[VSIZE][HSIZE]) { // create another table 5*10
	int x, y; 
	for (y = 0; y < VSIZE; y++) {
		for (x = 0; x < HSIZE; x++) {
			printf("%3d ", tbl[y][x]);//printing the number from the previous table
		}
		printf("\n");
	}
	
}//prints the template table
//


 
 
void prt_tbl_rev(char tbl[VSIZE][HSIZE]){ 

	int x, y;
	for (y = VSIZE-1; y > -1; y--) {
		for (x = HSIZE-1; x > -1; x--) {
			printf("%3d ", tbl[y][x]);
		}
		printf("\n");
	}
	
}
 
 
void prt_tbl_y_x(char tbl[VSIZE][HSIZE]) {
	int x, y;
	for (x = 0; x < HSIZE; x++) {
		for (y = 0; y < VSIZE; y++) {
			printf("%3d ", tbl[y][x]);
		}
		printf("\n");
	}

}
	


