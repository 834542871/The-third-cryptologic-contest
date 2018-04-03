#include "SM3.h"
#include <string.h>

BYTE getByte(char a, char b){
	if(a >= '0' && a <= '9'){
		a-='0';
	}else if(a >= 'A' && a <= 'Z'){
		a= a-'A'+10;
	}

	if(b >= '0' && b <= '9'){
		b-='0';
	}else if(b >= 'A' && b <= 'Z'){
		b= b-'A'+10;
	}

	return a*16+b;

}

void charToByte(char* src, BYTE* byte){
	int length = strlen(src);
	int i;
	char a,b;
	for(i = 0; i < length; i++){
		a = src[i];
		i = i+1;
		b = src[i];
		byte[i/2] = getByte(a,b);
	}

}