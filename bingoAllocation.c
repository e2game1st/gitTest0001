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

//< 빙고판 보여주기
void display(const int(**numArr), int(**flagArr), int row, int col, int mode);

//< 숫자추출
void initNumber(int(**numArr), int(**flagArr), int row, int col);

//< 섞기
void shuffle(int(**numArr), int row, int col, int shuffleCount);

//< 바꾸기 
void swap(int *left, int *right);

//< 숫자 오픈
void openNumber(int(**numArr), int(**flagArr), int row, int col, int number);

//< 빙고 확인
int bingoCount(int(**flagArr), int row, int col);

//< 게임 루프
void gameLoop(int(**numArrUser), int(**flagArrUser), int(**numArrCom), int(**flagArrCom), int row, int col);

//< 숫자 입력
int inputNumber(void);

//< 출력
void output(int(**numArrUser), int(**flagArrUser), int(**numArrCom), int(**flagArrCom), int row, int col);

//< 동적할당
void* allocation(int (**numArr), int row, int col);

//< 해제
void* freeAlloc(int (**numArr), int row, int col);

int main(int argc, char *args[])
{
	int **numArrUser = NULL, **flagArrUser = NULL;
	int **numArrCom = NULL, **flagArrCom = NULL;
	int row, col;

	//< 시간설정
	randomize();

	while (TRUE)
	{
		system("cls");
		printf("줄수입력:");
		row = inputNumber();
		col = row;
		if (row != col || row < 3)
		{
			//< 재입력
			system("cls");
			puts("너무 작습니다");
			puts("다시입력");
			system("pause");
		}
		else
		{
			//< 동적할당
			system("cls");
			puts("동적할당시작");
			//< User 동적할당
			numArrUser=(int**)allocation(numArrUser, row, col);
			flagArrUser = (int**)allocation(flagArrUser, row, col);
			//< Com 동적할당
			numArrCom = (int**)allocation(numArrCom, row, col);
			flagArrCom = (int**)allocation(flagArrCom, row, col);
			puts("동적할당완료");
			break;
		}
	}
	
	system("cls");

	//< 숫자추출
	initNumber(numArrCom, flagArrCom, row, col);
	shuffle(numArrCom, row, col, getRandomRange(500, 100));
	initNumber(numArrUser, flagArrUser, row, col);
	shuffle(numArrUser, row, col, getRandomRange(1000, 500));

	//< 게임반복
	gameLoop(numArrUser, flagArrUser, numArrCom, flagArrCom, row, col);

	//< 동적할당 해제
	//< User 동적할당해제
	freeAlloc(numArrUser, row, col);
	freeAlloc(flagArrUser, row, col);
	//< Com 동적할당해제
	freeAlloc(numArrCom, row, col);
	freeAlloc(flagArrCom, row, col);
	return 0;
}

//< 빙고판 보여주기
void display(const int(**numArr), int(**flagArr), int row, int col, int mode)
{
	//< 반복변수
	int i, j;
	
	setTextcolor(WHITE_BG);

	for (i = 0; i < col; i++)
	{
		for (j = 0; j < row; j++)
		{
			//< 유저
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
			//< 컴퓨터
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

//< 숫자추출
void initNumber(int(**numArr), int(**flagArr), int row, int col)
{
	//< 반복변수, 숫자
	int i, j, number = 1;

	//< 시간설정
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

//< 섞기
void shuffle(int(**numArr), int row, int col, int shuffleCount)
{
	//< 반복용 변수
	int i;

	//< 인덱스 추출 변수
	int dest, src;

	for (i = 0; i < shuffleCount; i++)
	{
		//< 인덱스
		dest = getRandomRange(row * col - 1, 0);
		src = getRandomRange(row * col - 1, 0);

		if (dest != src)
		{
			swap(&numArr[dest / row][dest%row],
				&numArr[src / row][src%row]);
		}
	}
}

//< 바꾸기 
void swap(int *left, int *right)
{
	int temp = *left;
	*left = *right;
	*right = temp;
}

//< 숫자 오픈
void openNumber(int(**numArr), int(**flagArr), int row, int col, int number)
{
	//< 반복용 변수
	int i, j;

	//< 반복
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

//< 게임 루프
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
				printf("입력[1~%d][0:종료] : ", row*col);
				number = inputNumber();
				while (getchar() != '\n');
				//< 종료플래그
				if (number == 0){ return; }
				openNumber(numArrUser, flagArrUser, row, col, number);
				openNumber(numArrCom, flagArrCom, row, col, number);
				turn++;
				userBingo = bingoCount(flagArrUser, row, col);
				if (userBingo >= row)
				{
					system("cls");
					puts("유저승리!!!");
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
						puts("컴승리!!!");
						system("pause");
						return;
					}
					break;
				}
			}
		}
		//< 화면지우기
		system("cls");

		//< 다시 출력
		output(numArrUser, flagArrUser, numArrCom, flagArrCom, row, col);
	}
}

//< 빙고 확인
int bingoCount(int(**flagArr), int row, int col)
{
	//< 반복용 변수
	int i, j;

	//< 빙고 카운트
	int bingo = 0;

	//< 인덱스
	int cross = 0, checkCount = 0;

	//< 반복
	for (i = 0; i < col; i++)
	{
		checkCount = 0;
		for (j = 0; j < row; j++)
		{
			// 가로 빙고
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

	//< 반복
	for (i = 0; i < col; i++)
	{
		checkCount = 0;
		for (j = 0; j < row; j++)
		{
			//< 세로 빙고
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

	//< 반복
	for (i = 0; i < col; i++)
	{
		//< 대각선1
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
	//< 반복
	for (i = 0; i < col; i++)
	{
		//< 대각선2
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

//< 숫자 입력
int inputNumber(void)
{
	int number;
	//< 입력, 에러처리
	if (scanf_s("%d", &number) != 1)
	{
		puts("오류");
		system("pause");
		while (getchar() != '\n');
	}
	return number;
}

//< 출력
void output(int(**numArrUser), int(**flagArrUser), int(**numArrCom), int(**flagArrCom), int row, int col)
{
	int com = 0, user = 0;

	com = bingoCount(flagArrCom, row, col);
	setTextcolor(PINK);
	printf("[Com빙고판] : %d\n", com);

	display(numArrCom, flagArrCom, row, col, COM);//USER); 

	user = bingoCount(flagArrUser, row, col);
	setTextcolor(YELLOW);
	printf("[내빙고판] : %d\n", user);

	display(numArrUser, flagArrUser, row, col, USER);
}

//< 동적할당
void* allocation(int(**numArr), int row, int col)
{
	//< 반복용 변수
	int i;
	//< 2차원 할당
	if (numArr == NULL)
	{
		numArr = (int**)malloc(sizeof(int*) * col);
		//< 1차원 할당
		for (i = 0; i < row; i++)
		{
			numArr[i] = (int*)malloc(sizeof(int) * row);
		}
	}
	else
	{
		puts("오류");
		return NULL;
	}
	
	return numArr;
}

//< 해제
void* freeAlloc(int(**numArr), int row, int col)
{
	//< 반복용 변수
	int i;
	if (numArr != NULL)
	{
		//< 1차원 해제
		for (i = 0; i < row; i++)
		{
			free(numArr[i]);
		}

		//< 2차원 해제
		free(numArr);
	}
	else
	{
		puts("오류");
		return NULL;
	}

	return numArr;
}
