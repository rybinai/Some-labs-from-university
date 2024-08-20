#include <stdio.h>

int main(void){
	int n = 5;
	int i = 1;
	while (n > 0){
		i = n * i;
	n = n - 1;
	}
	return 0; 
}