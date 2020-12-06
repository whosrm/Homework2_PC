#include <stdio.h>
#include "uti/print_board.h"
#include <string.h>

#define MY_SIZE 15

int main()
{
	char table[MY_SIZE][MY_SIZE];
	int i,j;
	for(i=0;i<MY_SIZE;++i)
	{
		memset(table[i],'.',MY_SIZE);
	}
	print_board(table);
	return 0;
}
