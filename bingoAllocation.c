/*
ผ๖มค
project:bingo(5x5)
day:160418
*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include "JUtil.h"

#define MOON 5
#define BLACK_BG (RED_BG & GREEN_BG & BLUE_BG)

#define TRUE 1
#define FALSE 0

#define SHOW TRUE
#define HIDE FALSE

#define USER TRUE
#define COM FALSE

#define ROW 5
#define COL 5

#define random(value)               (rand() % value)
#define randomize()                 srand((unsigned int)time(0))
#define getRandomRange(_max,_min)   (random((_max-_min)+1) + _min)

//< ๋น๊ณ ํ ๋ณด์ฌ์ฃผ๊ธฐ
void display(const int(**numArr), int(**flagArr), int row, int col, int mode);

//< ์ซ์์ถ์ถ
void initNumber(int(**numArr), int(**flagArr), int row, int col);

//< ์๊ธฐ
void shuffle(int(**numArr), int row, int col, int shuffleCount);

//< ๋ฐ๊พธ๊ธฐ 
void swap(int *left, int *right);

//< ์ซ์ ์คํ
void openNumber(int(**numArr), int(**flagArr), int row, int col, int number);

//< ๋น๊ณ  ํ์ธ
int bingoCount(int(**flagArr), int row, int col);

//< ๊ฒ์ ๋ฃจํ
void gameLoop(int(**numArrUser), int(**flagArrUser), int(**numArrCom), int(**flagArrCom), int row, int col);

//< ์ซ์ ์๋ ฅ
int inputNumber(void);

//< ์ถ๋ ฅ
void output(int(**numArrUser), int(**flagArrUser), int(**numArrCom), int(**flagArrCom), int row, int col);

//< ๋์ ํ ๋น
void* allocation(int (**numArr), int row, int col);

//< ํด์ 
void* freeAlloc(int (**numArr), int row, int col);

int main(int argc, char *args[])
{
	int **numArrUser = NULL, **flagArrUser = NULL;
	int **numArrCom = NULL, **flagArrCom = NULL;
	int row, col;

	//< ์๊ฐ์ค์ 
	randomize();

	while (TRUE)
	{
		system("cls");
		printf("์ค์์๋ ฅ:");
		row = inputNumber();
		col = row;
		if (row != col || row < 3)
		{
			//< ์ฌ์๋ ฅ
			system("cls");
			puts("๋๋ฌด ์์ต๋๋ค");
			puts("๋ค์์๋ ฅ");
			system("pause");
		}
		else
		{
			//< ๋์ ํ ๋น
			system("cls");
			puts("๋์ ํ ๋น์์");
			//< User ๋์ ํ ๋น
			numArrUser=(int**)allocation(numArrUser, row, col);
			flagArrUser = (int**)allocation(flagArrUser, row, col);
			//< Com ๋์ ํ ๋น
			numArrCom = (int**)allocation(numArrCom, row, col);
			flagArrCom = (int**)allocation(flagArrCom, row, col);
			puts("๋์ ํ ๋น์๋ฃ");
			break;
		}
	}
	
	system("cls");

	//< ์ซ์์ถ์ถ
	initNumber(numArrCom, flagArrCom, row, col);
	shuffle(numArrCom, row, col, getRandomRange(500, 100));
	initNumber(numArrUser, flagArrUser, row, col);
	shuffle(numArrUser, row, col, getRandomRange(1000, 500));

	//< ๊ฒ์๋ฐ๋ณต
	gameLoop(numArrUser, flagArrUser, numArrCom, flagArrCom, row, col);

	//< ๋์ ํ ๋น ํด์ 
	//< User ๋์ ํ ๋นํด์ 
	freeAlloc(numArrUser, row, col);
	freeAlloc(flagArrUser, row, col);
	//< Com ๋์ ํ ๋นํด์ 
	freeAlloc(numArrCom, row, col);
	freeAlloc(flagArrCom, row, col);
	return 0;
}

//< ๋น๊ณ ํ ๋ณด์ฌ์ฃผ๊ธฐ
void display(const int(**numArr), int(**flagArr), int row, int col, int mode)
{
	//< ๋ฐ๋ณต๋ณ์
	int i, j;
	
	setTextcolor(WHITE_BG);

	for (i = 0; i < col; i++)
	{
		for (j = 0; j < row; j++)
		{
			//< ์ ์ 
			if (mode == USER)
			{
				if (flagArr[i][j] == SHOW)
				{
					setTextcolor(RED);
					printf("[%4s]", "*");
				}
				else
				{
					setTextcolor(WHITE);
					printf("[%4d]", numArr[i][j]);
				}
			}
			//< ์ปดํจํฐ
			else
			{
				if (flagArr[i][j] == HIDE)
				{
					setTextcolor(RED);
					printf("[%4s]", "*");
				}
				else
				{
					setTextcolor(WHITE);
					printf("[%4d]", numArr[i][j]);
				}
			}
		}
		puts("");
	}
	setTextcolor(WHITE);
}

//< ์ซ์์ถ์ถ
void initNumber(int(**numArr), int(**flagArr), int row, int col)
{
	//< ๋ฐ๋ณต๋ณ์, ์ซ์
	int i, j, number = 1;

	//< ์๊ฐ์ค์ 
	randomize();

	for (i = 0; i < col; i++)
	{
		for (j = 0; j < row; j++)
		{
			flagArr[i][j] = HIDE;
			numArr[i][j] = (i * row) + j + 1;
		}
	}
}

//< ์๊ธฐ
void shuffle(int(**numArr), int row, int col, int shuffleCount)
{
	//< ๋ฐ๋ณต์ฉ ๋ณ์
	int i;

	//< ์ธ๋ฑ์ค ์ถ์ถ ๋ณ์
	int dest, src;

	for (i = 0; i < shuffleCount; i++)
	{
		//< ์ธ๋ฑ์ค
		dest = getRandomRange(row * col - 1, 0);
		src = getRandomRange(row * col - 1, 0);

		if (dest != src)
		{
			swap(&numArr[dest / row][dest%row],
				&numArr[src / row][src%row]);
		}
	}
}

//< ๋ฐ๊พธ๊ธฐ 
void swap(int *left, int *right)
{
	int temp = *left;
	*left = *right;
	*right = temp;
}

//< ์ซ์ ์คํ
void openNumber(int(**numArr), int(**flagArr), int row, int col, int number)
{
	//< ๋ฐ๋ณต์ฉ ๋ณ์
	int i, j;

	//< ๋ฐ๋ณต
	for (i = 0; i < col; i++)
	{
		for (j = 0; j < row; j++)
		{
			if (numArr[i][j] == number)
			{
				if (flagArr[i][j] != SHOW)
				{
					flagArr[i][j] = SHOW;
					return;
				}
			}
		}
	}
}

//< ๊ฒ์ ๋ฃจํ
void gameLoop(int(**numArrUser), int(**flagArrUser), int(**numArrCom), int(**flagArrCom), int row, int col)
{
	int turn = 0, userBingo = 0, comBingo = 0, number;
	output(numArrUser, flagArrUser, numArrCom, flagArrCom, row, col);

	while (TRUE)
	{
		if (turn % 2 == USER)
		{
			while (TRUE)
			{
				printf("์๋ ฅ[1~%d][0:์ข๋ฃ] : ", row*col);
				number = inputNumber();
				while (getchar() != '\n');
				//< ์ข๋ฃํ๋๊ทธ
				if (number == 0){ return; }
				openNumber(numArrUser, flagArrUser, row, col, number);
				openNumber(numArrCom, flagArrCom, row, col, number);
				turn++;
				userBingo = bingoCount(flagArrUser, row, col);
				if (userBingo >= row)
				{
					system("cls");
					puts("์ ์ ์น๋ฆฌ!!!");
					system("pause");
					return;
				}
				break;
			}
		}
		else
		{
			randomize();
			while (TRUE)
			{
				int index = random(row*col);
				if (flagArrCom[index / row][index % row] == HIDE)
				{
					number = numArrCom[index / row][index%row];
					openNumber(numArrUser, flagArrUser, row, col, number);
					openNumber(numArrCom, flagArrCom, row, col, number);
					turn++;
					comBingo = bingoCount(flagArrCom, row, col);
					if (comBingo >= row)
					{
						system("cls");
						puts("์ปด์น๋ฆฌ!!!");
						system("pause");
						return;
					}
					break;
				}
			}
		}
		//< ํ๋ฉด์ง์ฐ๊ธฐ
		system("cls");

		//< ๋ค์ ์ถ๋ ฅ
		output(numArrUser, flagArrUser, numArrCom, flagArrCom, row, col);
	}
}

//< ๋น๊ณ  ํ์ธ
int bingoCount(int(**flagArr), int row, int col)
{
	//< ๋ฐ๋ณต์ฉ ๋ณ์
	int i, j;

	//< ๋น๊ณ  ์นด์ดํธ
	int bingo = 0;

	//< ์ธ๋ฑ์ค
	int cross = 0, checkCount = 0;

	//< ๋ฐ๋ณต
	for (i = 0; i < col; i++)
	{
		checkCount = 0;
		for (j = 0; j < row; j++)
		{
			// ๊ฐ๋ก ๋น๊ณ 
			if (flagArr[i][j] == SHOW)
			{
				checkCount++;
			}
		}
		if (checkCount == row)
		{
			bingo++;
		}
	}

	//< ๋ฐ๋ณต
	for (i = 0; i < col; i++)
	{
		checkCount = 0;
		for (j = 0; j < row; j++)
		{
			//< ์ธ๋ก ๋น๊ณ 
			if (flagArr[j][i] == SHOW)
			{
				checkCount++;
			}
		}
		if (checkCount == col)
		{
			bingo++;
		}
	}

	//< ๋ฐ๋ณต
	for (i = 0; i < col; i++)
	{
		//< ๋๊ฐ์ 1
		if (flagArr[i][i] == SHOW)
		{
			cross++;
		}

	}
	if (cross == row)
	{
		bingo++;
	}
	cross = 0;
	//< ๋ฐ๋ณต
	for (i = 0; i < col; i++)
	{
		//< ๋๊ฐ์ 2
		if (flagArr[i][(row - 1) - i] == SHOW)
		{
			cross++;
		}
	}
	if (cross == row)
	{
		bingo++;
	}
	return bingo;
}

//< ์ซ์ ์๋ ฅ
int inputNumber(void)
{
	int number;
	//< ์๋ ฅ, ์๋ฌ์ฒ๋ฆฌ
	if (scanf_s("%d", &number) != 1)
	{
		puts("์ค๋ฅ");
		system("pause");
		while (getchar() != '\n');
	}
	return number;
}

//< ์ถ๋ ฅ
void output(int(**numArrUser), int(**flagArrUser), int(**numArrCom), int(**flagArrCom), int row, int col)
{
	int com = 0, user = 0;

	com = bingoCount(flagArrCom, row, col);
	setTextcolor(PINK);
	printf("[Com๋น๊ณ ํ] : %d\n", com);

	display(numArrCom, flagArrCom, row, col, COM);//USER); 

	user = bingoCount(flagArrUser, row, col);
	setTextcolor(YELLOW);
	printf("[๋ด๋น๊ณ ํ] : %d\n", user);

	display(numArrUser, flagArrUser, row, col, USER);
}

//< ๋์ ํ ๋น
void* allocation(int(**numArr), int row, int col)
{
	//< ๋ฐ๋ณต์ฉ ๋ณ์
	int i;
	//< 2์ฐจ์ ํ ๋น
	if (numArr == NULL)
	{
		numArr = (int**)malloc(sizeof(int*) * col);
		//< 1์ฐจ์ ํ ๋น
		for (i = 0; i < row; i++)
		{
			numArr[i] = (int*)malloc(sizeof(int) * row);
		}
	}
	else
	{
		puts("์ค๋ฅ");
		return NULL;
	}
	
	return numArr;
}

//< ํด์ 
void* freeAlloc(int(**numArr), int row, int col)
{
	//< ๋ฐ๋ณต์ฉ ๋ณ์
	int i;
	if (numArr != NULL)
	{
		//< 1์ฐจ์ ํด์ 
		for (i = 0; i < row; i++)
		{
			free(numArr[i]);
		}

		//< 2์ฐจ์ ํด์ 
		free(numArr);
	}
	else
	{
		puts("์ค๋ฅ");
		return NULL;
	}

	return numArr;
}
