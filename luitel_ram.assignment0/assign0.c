#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

typedef struct cell {
	char symbol;
	int live;
} cell_t;

int checkLive(cell_t a[][80], int x, int y);
int countLive(cell_t a[][80], int x, int y);

int main(int argc, char* argv[]) {
	int i, j, x = -1, y = -1;
	int total = 0; 
	if (argc < 2 || argc%2 == 0) {
		printf("Wrong input\n");
		return 0;
	}
	int coor[argc - 1];
	for (i = 0; i < argc - 1; i++) {
		coor[i] = atoi(argv[i + 1]);
	}
///////////////////////////////
	cell_t arr[24][80];
	cell_t update[24][80];
	for (i = 0; i < 24; i++) {
		for (j = 0; j < 80; j++) {
			arr[i][j].symbol = ' ';
			arr[i][j].live = 0;
			update[i][j].symbol = ' ';
			update[i][j].live = 0;
		}
	}
///////////////////////////////
	for (i = 0; i < argc - 1; i += 2) {
		x = coor[i];
		y = coor[i + 1];
		arr[y][x].symbol = 'O';
		arr[y][x].live = 1;
		update[y][x].symbol = 'O';
		update[y][x].live = 1;
	}
	do {
		total = 0;
		//Print out
		for (i = 0; i < 24; i++) {
			for (j = 0; j < 80; j++) {
				printf("%c", arr[i][j].symbol);
				if (arr[i][j].live == 1)
					total++;
			}
			printf("\n");
		}
		printf("%d\n", total);
		usleep(83333);
		//Update 
		for (i = 0; i < 24; i++) {
			for (j = 0; j < 80; j++) {
				if (update[i][j].live == 1) {
					if (countLive(update, i, j) == 0
							|| countLive(update, i, j) == 1) {
						arr[i][j].symbol = ' ';
						arr[i][j].live = 0;
					}
					if (countLive(update, i, j) >= 4) {
						arr[i][j].symbol = ' ';
						arr[i][j].live = 0;
					}
				}	//if
				else {
					if (countLive(update, i, j) == 3) {
						arr[i][j].symbol = 'O';
						arr[i][j].live = 1;
					}
				}	//else
			}	//end 2 loop
		}	//end 1 loop	
	//Copy
		for (i = 0; i < 24; i++) {
			for (j = 0; j < 80; j++) {
				update[i][j].symbol = arr[i][j].symbol;
				update[i][j].live = arr[i][j].live;
			}
		}
	} while (total > 1);
	return 0;
}
int checkLive(cell_t a[][80], int x, int y) {
	if (x < 0)
		x = 23;
	if (x > 23)
		x = 0;
	if (y < 0)
		y = 79;
	if (y > 79)
		y = 0;
	if (a[x][y].live == 1)
		return 1;
	else
		return 0;
}
int countLive(cell_t a[][80], int x, int y) {
	int count = 0;
	if (checkLive(a, x - 1, y - 1) == 1) {
		count++;
	}
	if (checkLive(a, x, y - 1) == 1) {
		count++;
	}
	if (checkLive(a, x + 1, y - 1) == 1) {
		count++;
	}
	if (checkLive(a, x - 1, y) == 1) {
		count++;
	}
	if (checkLive(a, x + 1, y) == 1) {
		count++;
	}
	if (checkLive(a, x - 1, y + 1) == 1) {
		count++;
	}
	if (checkLive(a, x, y + 1) == 1) {
		count++;
	}
	if ((checkLive(a, x + 1, y + 1) == 1)) {
		count++;
	}
	return count;
}
