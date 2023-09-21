#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {


	char arr[1000000] = "";

	scanf("%[^\n]s", arr);

	int cnt = 0;
	int debugging = -1;
	
	for (char* p = strtok(arr, " "); p != NULL; p = strtok(NULL, " ")) {
		cnt++;
	}



	printf("%d", cnt);


	return 0;

}