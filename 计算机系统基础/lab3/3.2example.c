#include<stdio.h>

int asm_avg(int num1, int num2, int num3);
extern int c_in_asm;

int printv(int v)
{
	printf("avg = %d\n", v);
	return v;
}

int main(void)
{
	int a = 80;
	int b = 90;
	int c = 100;

	c = c_in_asm;

	asm_avg(a, b, c);
}
