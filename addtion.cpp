#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {

	int a1=0;
	int a2=0;

	printf("두 정수를 입력하세요: ");
	scanf("%d %d", &a1,&a2);
	int result = a1+a2;

	printf("%d\n",result);

	return 0;
}
