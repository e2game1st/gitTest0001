/*
����
project:bingo(5x5)
day:160418
*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include "JUtil.h"


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

//< ������ �����ֱ�
void display(const int(**numArr), int(**flagArr), int row, int col, int mode);

//< ��������
void initNumber(int(**numArr), int(**flagArr), int row, int col);

//< ����
void shuffle(int(**numArr), int row, int col, int shuffleCount);

//< �ٲٱ� 
void swap(int *left, int *right);

//< ���� ����
void openNumber(int(**numArr), int(**flagArr), int row, int col, int number);

//< ���� Ȯ��
int bingoCount(int(**flagArr), int row, int col);

//< ���� ����
void gameLoop(int(**numArrUser), int(**flagArrUser), int(**numArrCom), int(**flagArrCom), int row, int col);

//< ���� �Է�
int inputNumber(void);

//< ���
void output(int(**numArrUser), int(**flagArrUser), int(**numArrCom), int(**flagArrCom), int row, int col);

//< �����Ҵ�
void* allocation(int (**numArr), int row, int col);

//< ����
void* freeAlloc(int (**numArr), int row, int col);

int main(int argc, char *args[])
{
	int **numArrUser = NULL, **flagArrUser = NULL;
	int **numArrCom = NULL, **flagArrCom = NULL;
	int row, col;

	//< �ð�����
	randomize();

	while (TRUE)
	{
		system("cls");
		printf("�ټ��Է�:");
		row = inputNumber();
		col = row;
		if (row != col || row < 3)
		{
			//< ���Է�
			system("cls");
			puts("�ʹ� �۽��ϴ�");
			puts("�ٽ��Է�");
			system("pause");
		}
		else
		{
			//< �����Ҵ�
			system("cls");
			puts("�����Ҵ����");
			//< User �����Ҵ�
			numArrUser=(int**)allocation(numArrUser, row, col);
			flagArrUser = (int**)allocation(flagArrUser, row, col);
			//< Com �����Ҵ�
			numArrCom = (int**)allocation(numArrCom, row, col);
			flagArrCom = (int**)allocation(flagArrCom, row, col);
			puts("�����Ҵ�Ϸ�");
			break;
		}
	}
	
	system("cls");

	//< ��������
	initNumber(numArrCom, flagArrCom, row, col);
	shuffle(numArrCom, row, col, getRandomRange(500, 100));
	initNumber(numArrUser, flagArrUser, row, col);
	shuffle(numArrUser, row, col, getRandomRange(1000, 500));

	//< ���ӹݺ�
	gameLoop(numArrUser, flagArrUser, numArrCom, flagArrCom, row, col);

	//< �����Ҵ� ����
	//< User �����Ҵ�����
	freeAlloc(numArrUser, row, col);
	freeAlloc(flagArrUser, row, col);
	//< Com �����Ҵ�����
	freeAlloc(numArrCom, row, col);
	freeAlloc(flagArrCom, row, col);
	return 0;
}

//< ������ �����ֱ�
void display(const int(**numArr), int(**flagArr), int row, int col, int mode)
{
	//< �ݺ�����
	int i, j;
	
	setTextcolor(WHITE_BG);

	for (i = 0; i < col; i++)
	{
		for (j = 0; j < row; j++)
		{
			//< ����
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
			//< ��ǻ��
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

//< ��������
void initNumber(int(**numArr), int(**flagArr), int row, int col)
{
	//< �ݺ�����, ����
	int i, j, number = 1;

	//< �ð�����
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

//< ����
void shuffle(int(**numArr), int row, int col, int shuffleCount)
{
	//< �ݺ��� ����
	int i;

	//< �ε��� ���� ����
	int dest, src;

	for (i = 0; i < shuffleCount; i++)
	{
		//< �ε���
		dest = getRandomRange(row * col - 1, 0);
		src = getRandomRange(row * col - 1, 0);

		if (dest != src)
		{
			swap(&numArr[dest / row][dest%row],
				&numArr[src / row][src%row]);
		}
	}
}

//< �ٲٱ� 
void swap(int *left, int *right)
{
	int temp = *left;
	*left = *right;
	*right = temp;
}

//< ���� ����
void openNumber(int(**numArr), int(**flagArr), int row, int col, int number)
{
	//< �ݺ��� ����
	int i, j;

	//< �ݺ�
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

//< ���� ����
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
				printf("�Է�[1~%d][0:����] : ", row*col);
				number = inputNumber();
				while (getchar() != '\n');
				//< �����÷���
				if (number == 0){ return; }
				openNumber(numArrUser, flagArrUser, row, col, number);
				openNumber(numArrCom, flagArrCom, row, col, number);
				turn++;
				userBingo = bingoCount(flagArrUser, row, col);
				if (userBingo >= row)
				{
					system("cls");
					puts("�����¸�!!!");
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
						puts("�Ľ¸�!!!");
						system("pause");
						return;
					}
					break;
				}
			}
		}
		//< ȭ�������
		system("cls");

		//< �ٽ� ���
		output(numArrUser, flagArrUser, numArrCom, flagArrCom, row, col);
	}
}

//< ���� Ȯ��
int bingoCount(int(**flagArr), int row, int col)
{
	//< �ݺ��� ����
	int i, j;

	//< ���� ī��Ʈ
	int bingo = 0;

	//< �ε���
	int cross = 0, checkCount = 0;

	//< �ݺ�
	for (i = 0; i < col; i++)
	{
		checkCount = 0;
		for (j = 0; j < row; j++)
		{
			// ���� ����
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

	//< �ݺ�
	for (i = 0; i < col; i++)
	{
		checkCount = 0;
		for (j = 0; j < row; j++)
		{
			//< ���� ����
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

	//< �ݺ�
	for (i = 0; i < col; i++)
	{
		//< �밢��1
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
	//< �ݺ�
	for (i = 0; i < col; i++)
	{
		//< �밢��2
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

//< ���� �Է�
int inputNumber(void)
{
	int number;
	//< �Է�, ����ó��
	if (scanf_s("%d", &number) != 1)
	{
		puts("����");
		system("pause");
		while (getchar() != '\n');
	}
	return number;
}

//< ���
void output(int(**numArrUser), int(**flagArrUser), int(**numArrCom), int(**flagArrCom), int row, int col)
{
	int com = 0, user = 0;

	com = bingoCount(flagArrCom, row, col);
	setTextcolor(PINK);
	printf("[Com������] : %d\n", com);

	display(numArrCom, flagArrCom, row, col, COM);//USER); 

	user = bingoCount(flagArrUser, row, col);
	setTextcolor(YELLOW);
	printf("[��������] : %d\n", user);

	display(numArrUser, flagArrUser, row, col, USER);
}

//< �����Ҵ�
void* allocation(int(**numArr), int row, int col)
{
	//< �ݺ��� ����
	int i;
	//< 2���� �Ҵ�
	if (numArr == NULL)
	{
		numArr = (int**)malloc(sizeof(int*) * col);
		//< 1���� �Ҵ�
		for (i = 0; i < row; i++)
		{
			numArr[i] = (int*)malloc(sizeof(int) * row);
		}
	}
	else
	{
		puts("����");
		return NULL;
	}
	
	return numArr;
}

//< ����
void* freeAlloc(int(**numArr), int row, int col)
{
	//< �ݺ��� ����
	int i;
	if (numArr != NULL)
	{
		//< 1���� ����
		for (i = 0; i < row; i++)
		{
			free(numArr[i]);
		}

		//< 2���� ����
		free(numArr);
	}
	else
	{
		puts("����");
		return NULL;
	}

	return numArr;
}