// test.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include <stdio.h>

unsigned int E1 = 0x00;
int row;

void stack()
{
	printf("Enter : ");
	scanf_s("%d", &row);

	if (row == 1)
	{
		E1 = (E1 << 1) | 1;
	}
}

int main()
{
	printf("%d \n", E1);
	stack();
	printf("%d", E1);
	stack();
	printf("%d", E1);
	stack();
	printf("%d", E1);
	stack();
	printf("%d", E1);
	stack();
	printf("%d", E1);
}

