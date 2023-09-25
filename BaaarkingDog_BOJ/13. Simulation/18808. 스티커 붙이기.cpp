#include<stdio.h>
#define PAI 3.1415923425345

int main() {

	printf("FILE :%s\n", __FILE__);
	printf("DATE :%s\n", __DATE__);
	printf("TIME :%s\n", __TIME__);
	printf("LINE :%d\n", __LINE__);
	printf("%3lf\n", PAI);

	return 0;
}