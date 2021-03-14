#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <string>
#include <time.h>
#include <math.h>
#include <iostream>
#define BLACK 0
#define WHITE 15
#define INCI(x) (((x)+1)%(COL))
#define DECI(x) (((x)+COL-1)%(COL))
#define INCJ(x) (((x)+1)%(RAW))
#define DECJ(x) (((x)+RAW-1)%(RAW))
#define MODE "mode 82,42"
#define COL 41
#define RAW 41
using namespace std;
int ct = 0;
HANDLE hOutput, hOutBuf;//����̨��Ļ���������
COORD coord = { 0,0 };//COORD��ʾһ���ַ��ڿ���̨��Ļ�ϵ�����
WORD att;
DWORD bytes = 0;
char data[COL][RAW];
int clr[8] = { BLACK,WHITE,BLACK,WHITE,BLACK,WHITE,BLACK,WHITE };
int a[COL][RAW] = { 0 }, b[COL][RAW] = { 0 };
unsigned int counts = 0;
char str[11];

void f1()//������Ͳ
{
	int i, j, k;
	memset(b, 0, sizeof(b));
	for (i = 0; i < COL; i++)
		for (j = 0; j < RAW; j++)
		{
			k = a[i][j];
			//b[i][j]+=k;
			b[DECI(i)][j] += k;
			b[INCI(i)][j] += k;
			b[i][DECJ(j)] += k;
			b[i][INCJ(j)] += k;
		}
	for (i = 0; i < COL; i++)
		for (j = 0; j < RAW; j++)
		{
			a[i][j] = b[i][j] % 8;
		}
}

void show()//��ʾ
{
	int i, j;
	for (i = 0; i < COL; i++)
	{
		for (j = 0; j < RAW; j++)
		{
			coord.X = 2 * i;
			coord.Y = j;
			att = clr[a[i][j]];
			if (a[i][j])
			{
				WriteConsoleOutputCharacterA(hOutBuf, "��", 2, coord, &bytes);
			}
			else WriteConsoleOutputCharacterA(hOutBuf, "  ", 2, coord, &bytes);
			WriteConsoleOutputAttribute(hOutBuf, &att, 1, coord, &bytes);
			coord.X++;
			WriteConsoleOutputAttribute(hOutBuf, &att, 1, coord, &bytes);
		}
	}
	itoa(counts, str, 10);
	coord.X = 0; coord.Y = 41;
	WriteConsoleOutputCharacterA(hOutBuf, str, sizeof(str), coord, &bytes);
	att = WHITE;
	WriteConsoleOutputAttribute(hOutBuf, &att, 1, coord, &bytes);
	SetConsoleActiveScreenBuffer(hOutBuf);
	f1();
	getch();//���������
	counts++;//���½Ǽ���++
	for (i = 0; i < COL; i++)
	{
		for (j = 0; j < RAW; j++)
		{
			coord.X = 2 * i;
			coord.Y = j;
			att = clr[a[i][j]];
			if (a[i][j])
			{
				WriteConsoleOutputCharacterA(hOutput, "��", 2, coord, &bytes);
			}
			else WriteConsoleOutputCharacterA(hOutput, "  ", 2, coord, &bytes);
			WriteConsoleOutputAttribute(hOutput, &att, 1, coord, &bytes);
			coord.X++;
			WriteConsoleOutputAttribute(hOutput, &att, 1, coord, &bytes);
		}
	}
	itoa(counts, str, 10);
	coord.X = 0; coord.Y = 41;
	WriteConsoleOutputCharacterA(hOutput, str, sizeof(str), coord, &bytes);
	att = WHITE;
	WriteConsoleOutputAttribute(hOutput, &att, 1, coord, &bytes);
	SetConsoleActiveScreenBuffer(hOutput);
	f1();
	//Sleep(50);
	getch(); counts++;
}
int main()
{
	srand(time(NULL));
	system(MODE);
	hOutBuf = CreateConsoleScreenBuffer(//���ڴ�������̨��Ļ������
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);
	hOutput = CreateConsoleScreenBuffer(
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);
	CONSOLE_CURSOR_INFO cci;//����ṹ�������ǿ���̨������Ϣ
	cci.bVisible = 0;//�Ƿ�ɼ�
	cci.dwSize = 1;// ���ٷֱȺ�ȣ�1~100�� 
	SetConsoleCursorInfo(hOutput, &cci);
	SetConsoleCursorInfo(hOutBuf, &cci);
	a[COL / 2][RAW / 2] = 1;
	while (1)show();
}

