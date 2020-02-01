#pragma once

#include <stdio.h>
#include <stdlib.h>


char* inputText(int* len) {   //Inputting the array.
	int i;
#pragma warning(suppress : 4996)
	FILE* tes = fopen("input.txt", "r");
	fseek(tes, 0L, SEEK_END);
	int n = ftell(tes)+1;
	fclose(tes);
#pragma warning(suppress : 4996)
	FILE* Input = fopen("input.txt", "r+");
	char* arr = (char*)malloc(sizeof(char) * n);
	fgets(arr, n, Input);
	//for (i = 0; i <= n; i++)
	//	fscanf_s(Input, "%c", &arr[i]);
	len[0] = n;
	fclose(Input);
	return(arr);
}

void printArr(char* arr, int length) {
	int i;
	for (i = 0; i < length; i++)
		printf("%c", arr[i]);
	printf(" Length %d \n", length);
}

int numOfVar(char* arr, int length) {
	int i;

	int t1 = 0;
	int t2 = 0;
	int t3 = 0;
	int t4 = 0;
	int t5 = 0;

	for (i = 0; i < length; i++) {
		if (arr[i] == 'a')
			t1 = 1;
		if (arr[i] == 'b')
			t2 = 1;
		if (arr[i] == 'c')
			t3 = 1;
		if (arr[i] == 'd')
			t4 = 1;
		if (arr[i] == 'e')
			t5 = 1;
	}
	return t1+t2+t3+t4+t5;
}
int Prec(char ch)
{
	switch (ch)
	{
	case '*':
		return 4;

	case '+':
		return 3;

	case '^':
		return 2;

	case '=':
		return 1;

	case '>':
		return 0;

	case '!':
		return 5;
	}
	return -1;
}

int pow(int base, int exp) {
	int i,t = 1;
	for (i = 0; i < exp; i++)
		t *= base;
	return t;
}

int isOperand(char ch)
{
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}
int isdigit(char ch) {
	if (ch - '0' >= 0 && ch - '0' < 10)
		return 1;
	return 0;
}
