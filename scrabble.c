#include <stdlib.h>
#include <stdio.h>
#include "util/print_board.h"
#include "util/scrabble.h"
#include <string.h>

#define SIZE 15
void task0(char table[SIZE][SIZE])
{
	int i;
	for(i=0;i<SIZE;++i)
	{
		memset(table[i],'.',SIZE);
	}
}

void place_word(char table[SIZE][SIZE],int X,int Y,int D,char *word)
{
	int i;
	if(D)
		for(i=0;word[i];++i)
		{
			table[Y+i][X] = word[i];
		}
	else
		for(i=0;word[i];++i)
		{
			table[Y][X+i] = word[i];
		}

}
void task1(char table[SIZE][SIZE])
{
	// deci trebuie sa citim N si liniile....
	char char_row[2*SIZE], *p;
	// prima data citim pt N
	gets(char_row);
	int N = atoi(char_row), i,
		X, Y, D;
	for(i=0;i<N;++i)
	{
		gets(char_row);
		p = strtok(char_row," ");
		X = atoi(p);
		p = strtok(NULL," ");
		Y = atoi(p);
		p = strtok(NULL ," ");
		D = atoi(p);
		p = strtok(NULL ," ");
		place_word(table,Y,X,D,p);
	}
}
int score(char* word)
{
	static int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3,
	   	10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
						//A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P,  
		//Q, R, S, T, U, V, W, X, Y,  Z
	int val = 0, i;
	for(i = 0;word[i];++i)
	{
		val += points[word[i]-'A'];
	}
	return val;
}

void task2()
{
	// deci trebuie sa citim N si liniile....
	char char_row[2*SIZE], *p;
	// prima data citim pt N
	gets(char_row);
	int N = atoi(char_row), i;
	int players[2] = {0} ,player = 0;
	for(i=0;i<N;++i)
	{
		gets(char_row);
		p = strtok(char_row," ");
		p = strtok(NULL ," ");
		p = strtok(NULL ," ");
		p = strtok(NULL ," ");
		players[player] += score(p);
		player = !player;
	}
	fprintf(stdout,"Player 1: %d Points\n",players[0]);
	fprintf(stdout,"Player 2: %d Points\n",players[1]);
}

int aparitii_bonus(int tip_bonus, int X, int Y, int D, char* word)
{
	int i, nr_bonus = 0;
	if(D)
		for(i=0;word[i];++i)
		{
			if(bonus_board[Y+i][X] == tip_bonus)
				++nr_bonus;
		}
	else
		for(i=0;word[i];++i)
		{
			if(bonus_board[Y][X+i] == tip_bonus)
				++nr_bonus;
		}
	return nr_bonus;
}
void task3()
{
	// deci trebuie sa citim N si liniile....
	char char_row[2*SIZE], *p;
	char XX[3],YY[3];
	gets(XX);
	gets(YY);
	// citim pt N
	gets(char_row);
	int N = atoi(char_row), i,
		X, Y, D;
	int players[2] = {0} ,player = 0;
	for(i=0;i<N;++i)
	{
		gets(char_row);
		p = strtok(char_row," ");
		X = atoi(p);
		p = strtok(NULL," ");
		Y = atoi(p);
		p = strtok(NULL ," ");
		D = atoi(p);
		p = strtok(NULL ," ");
		// aici trebuie sa facem si bonusurile
		int score_temp = score(p), bonus = 0;
		if(strstr(p,XX)!=NULL)
		{
			bonus = aparitii_bonus(1,Y,X,D,p);
			int j;
			for(j=0;j<bonus;j++)
				score_temp *= 2;
		}
		if(!strcmp(YY,p + (strlen(p)-2) ) )
		{
			bonus = aparitii_bonus(2,Y,X,D,p);
			int j;
			for(j=0;j<bonus;j++)
				score_temp *= 3;
		}
		players[player] += score_temp;
		player = !player;
	}
	fprintf(stdout,"Player 1: %d Points\n",players[0]);
	fprintf(stdout,"Player 2: %d Points\n",players[1]);
}


// s-o apelez pt fiecare linie
// returneze pozita prime litere gasite
int  next_letter(char row[SIZE], int start)
{
	int i;
	for(i = start;i < SIZE;++i)
		if(row[i] != '.')
			return i;
	return -1;
}

// gesete urmatoarea litera pe coloana ceruta
int next_vletter(char table[SIZE][SIZE], int col,int start)
{
	int i;
	for(i=start;i<SIZE;++i)
	{
		if(table[i][col] != '.')
			return i;
	}
	return -1;
}

int find_word(char initial, size_t length)
{
	int i;
	for(i=0;i<NUM_WORDS;++i)
	{
		if(words[i][0] == initial && strlen(words[i]) <= length)
			return i;
	}
	// nu a gasit nici un cuvant bun
	return -1;
 }

int find_letter(char* row, char letter)
{
	static int i = 0;
	static char* this_row = NULL;
	if(row != NULL)
	{
		i = 0;
		this_row = row;
	}
	for(;i<SIZE;++i)
		if(this_row[i] == letter)
			return i++;
	return -1;
}

void task4(char table[SIZE][SIZE])
{
	// deci trebuie sa citim N si liniile....
	char char_row[2*SIZE], *p;
	char XX[3],YY[3];
	char used[NUM_WORDS][SIZE];
	gets(XX);
	gets(YY);
	// prima data citim pt N
	gets(char_row);
	int N = atoi(char_row), i,
		X, Y, D;
	for(i=0;i<N;++i)
	{
		gets(char_row);
		p = strtok(char_row," ");
		X = atoi(p);
		p = strtok(NULL," ");
		Y = atoi(p);
		p = strtok(NULL ," ");
		D = atoi(p);
		p = strtok(NULL ," ");
		strcpy(used[i],p);
		place_word(table,Y,X,D,p);
	}
	// incepem sa cautam o pozitie
	for(i=0;i<NUM_WORDS;++i)
	{
		int j;
		for(j=0;j<N;++j)
		{
			if(strcmp(words[i],used[j])==0)
				break;
		}
		if(j!=N)
			continue;	// sari la urmatorul cuvant
		// pana aici e bine
		// cautam prima litera
		for(j=0;j<SIZE;++j)
		{
			int pos = find_letter(table[j],words[i][0]);

			while(pos > -1)
			{	// vedem daca avem loc
				int k, ok = 1;
				for(k = 1;words[i][k] && ok;++k)
				{
					if(k + pos >= SIZE || table[j][pos + k] != '.')
						ok = 0;
				}
				if(ok)
				{
					place_word(table, pos, j, 0,words[i]);
					return;
				}
				// cautam loc in jos
				ok = 1;
				for(k = 1; words[i][k] && ok; ++k)
				{
					if(k + i >= SIZE || table[j + k][pos] != '.')
						ok = 0;
				}
				if(ok)
				{
					place_word(table, pos, j, 1,words[i]);
					return;
				}
				pos = find_letter(NULL,words[i][0]);
			}
		}
	}
}

void task5(char table[SIZE][SIZE])
{
	// deci trebuie sa citim N si liniile....
	char char_row[2*SIZE], *p;
	char XX[3],YY[3];
	char used[NUM_WORDS][SIZE];
	gets(XX);
	gets(YY);
	// citim pt N
	gets(char_row);
	int N = atoi(char_row), i,
		X, Y, D;
	int players[2] = {0} ,player = 0;
	for(i=0;i<N;++i)
	{
		gets(char_row);
		p = strtok(char_row," ");
		X = atoi(p);
		p = strtok(NULL," ");
		Y = atoi(p);
		p = strtok(NULL ," ");
		D = atoi(p);
		p = strtok(NULL ," ");
		strcpy(used[i],p);
		place_word(table,Y,X,D,p);
		// aici trebuie sa facem si bonusurile
		int score_temp = score(p), bonus = 0;
		if(strstr(p,XX)!=NULL)
		{
			bonus = aparitii_bonus(1,Y,X,D,p);
			int j;
			for(j=0;j<bonus;j++)
				score_temp *= 2;
		}
		if(!strcmp(YY,p + (strlen(p)-2) ) )
		{
			bonus = aparitii_bonus(2,Y,X,D,p);
			int j;
			for(j=0;j<bonus;j++)
				score_temp *= 3;
		}
		players[player] += score_temp;
		player = !player;
	}
	// retinem cuvantul, pozitia,directia pt cel mai bun scor
	int X_max, Y_max, D_max, index_max, score_max = 0;
	// petru fiecare cuvant
	for(i = 0;i < NUM_WORDS; ++i)
	{
		int j;
		// sa nu fie pe tabla
		for(j=0;j<N;++j)
		{
			if(strcmp(words[i],used[j])==0)
				break;
		}
		if(j!=N)
			continue;	// sari la urmatorul cuvant

		for(j=0;j<SIZE;++j)
		{
			int pos = find_letter(table[j],words[i][0]);

			while(pos > -1)
			{	// vedem daca avem loc
				int k, ok = 1;
				for(k = 1;words[i][k] && ok;++k)
				{
					if(k + pos >= SIZE || table[j][pos + k] != '.')
						ok = 0;
				}
				if(ok)
				{
					int score_temp = score(words[i]), bonus = 0;
					if(strstr(wors[i],XX)!=NULL)
					{
						bonus = aparitii_bonus(1,pos,j,0,words[i]);
						int j;
						for(j=0;j<bonus;j++)
							score_temp *= 2;
					}
					if(!strcmp(YY,wors[i] + (strlen(words[i])-2) ) )
					{
						bonus = aparitii_bonus(2,pos,j,0,words[i]);
						int j;
						for(j=0;j<bonus;j++)
							score_temp *= 3;
					}
					if(score_temp > score_max)
					{
						score_max = score_temp;
						X_max = pos;
						Y_max = j;
					}
				}
				// cautam loc in jos
				ok = 1;
				for(k = 1; words[i][k] && ok; ++k)
				{
					if(k + i >= SIZE || table[j + k][pos] != '.')
						ok = 0;
				}
				if(ok)
				{
					int score_temp = score(p), bonus = 0;
					if(strstr(p,XX)!=NULL)
					{
						bonus = aparitii_bonus(1,Y,X,D,p);
						int j;
						for(j=0;j<bonus;j++)
							score_temp *= 2;
					}
					if(!strcmp(YY,p + (strlen(p)-2) ) )
					{
						bonus = aparitii_bonus(2,Y,X,D,p);
						int j;
						for(j=0;j<bonus;j++)
							score_temp *= 3;
					}
				}
				pos = find_letter(NULL,words[i][0]);
			}
	}
}
    
int main()
{
	// de gasit o dimensiune
	char table[SIZE][SIZE];
	char task[2*SIZE];
	gets(task);
	int task_val = atoi(task);
	switch(task_val)
	{
		case 0:
			{
				task0(table);
				print_board(table);
			}break;
		case 1:
			{
				task0(table);
				task1(table);
				print_board(table);
			}break;
		case 2:
			{
				task2();
			}break;
		case 3:
			{
				task3();
			}break;
		case 4:
			{
				task0(table);
				task4(table);
				print_board(table);
			}break;
		default:
			{
				printf("ce plm?");
			}
	}
	return 0;
}
