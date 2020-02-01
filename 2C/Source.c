#include<stdio.h>
#include<stdlib.h>

void removeZeros(int* a) {
	while (a[0] > 1 && !a[a[0]])
		a[0]--;
}

int* multiply(int* a, int b) {
	int i, j;
	int* c = a;
	int t = 0;
	for (i = 1; i <= a[0] || t; i++) {
		t /= 10;
		t = (t + a[i] * b);
		c[i] = t % 10;
	}

	c[0] = i - 1;
	removeZeros(c);
	return c;
}

int* divide(int* a, int b) {
	int* c =  a;
	int i, j, t = 0; c[0] = a[0];
	for (i = a[0]; i >= 1; i--) {
		t %= b;
		t = t * 10 + a[i];
		c[i] = t / b;
	}
	removeZeros(c);
	return c;
}

void printarr(int* a) {
	int i;
	for (i = a[0]; i; i--)
		printf("%d", a[i]);
	printf("\n");
}

int main() {
	int n;
	int i;

	scanf_s("%d", &n);
	long int maxSize = (n * 100 + 2);
	int* a = (int*)malloc(sizeof(int) * maxSize);
	
	for (i = 0; i < maxSize; i++) {
		a[i] = 0;
	}

	a[0] = 1;   //Length is stored in the 0th node
	a[1] = 1;
	for (i = n + 2; i <= 2 * n; i++)
		a = multiply(a, i);    //multiply array to all i from n+2 until 2n;

	for (i = 1; i <= n; i++)
		a = divide(a, i);      //divide array by n factorial, factor by factor

	printarr(a);

	free(a);
	return 0;
}