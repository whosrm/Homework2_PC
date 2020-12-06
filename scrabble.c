#include <stdlib.h>
#include <stdio.h>
#include "util/print_board.h"
#include "util/scrabble.h"
#include <string.h>

#define SIZE 15
#define gets(s) fgets(s,sizeof s,stdin);\
	if(s[strlen(s)-1] == '\n')\
	   s[strlen(s)-1]= 0

struct Word
{
	int X,Y,D;
	char word[SIZE];
};
void task0(char table[SIZE][SIZE])
{
	int i;
	for(i=0;i<SIZE;++i)
	{
		memset(table[i],'.',SIZE);
	}
}

void place_word(char table[SIZE][SIZE],int X,int Y,int D,char *word)
{	// X - coloana, Y - rand
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

struct Word read_word()
{
	char char_row[2*SIZE],*p;
	struct Word res;
	gets(char_row);
	p = strtok(char_row," ");
	res.X = atoi(p);
	p = strtok(NULL," ");
	res.Y = atoi(p);
	p = strtok(NULL ," ");
	res.D = atoi(p);
	p = strtok(NULL ," ");
	strcpy(res.word,p);
	return res;
}
void task1(char table[SIZE][SIZE])
{
	// deci trebuie sa citim N si liniile....
	char char_row[2*SIZE];
	// prima data citim pt N
	gets(char_row);
	int N = atoi(char_row), i,
		X, Y, D;
	for(i=0;i<N;++i)
	{
		struct Word this_word = read_word();
		Y = this_word.Y;
		X = this_word.X;
		D = this_word.D;
		place_word(table,Y,X,D,this_word.word);
	}
}
int score(char* word)
{	// calculeaza scorul in functi de litere
	// fara bonus
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
	char char_row[2*SIZE];
	// prima data citim pt N
	gets(char_row);
	int N = atoi(char_row), i;
	int players[2] = {0} ,player = 0;
	for(i=0;i<N;++i)
	{
		struct Word this_word = read_word();
		players[player] += score(this_word.word);
		player = !player;
	}
	fprintf(stdout,"Player 1: %d Points\n",players[0]);
	fprintf(stdout,"Player 2: %d Points\n",players[1]);
}

int aparitii_bonus(int tip_bonus, int X, int Y, int D, char* word)
{	// cauta numerul de aparitii ale unui bonus
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

int calc_bonus(struct Word this,char XX[4], char YY[4])
{		// calculeaza scorul cu tot cu bonus
		int score_temp = score(this.word), bonus = 0;
		int Y = this.Y;
		int X = this.X;
		int D = this.D;
		if(strstr(this.word,XX)!=NULL)
		{
			bonus = aparitii_bonus(1,Y,X,D,this.word);
			int j;
			for(j=0;j<bonus;j++)
				score_temp *= 2;
		}
		if(!strcmp(YY,this.word + (strlen(this.word)-2) ) )
		{
			bonus = aparitii_bonus(2,Y,X,D,this.word);
			int j;
			for(j=0;j<bonus;j++)
				score_temp *= 3;
		}
		return score_temp;
}
void task3()
{
	// deci trebuie sa citim N si liniile....
	char char_row[2*SIZE];
	char XX[4],YY[4];
	gets(XX);
	gets(YY);
	// citim pt N
	gets(char_row);
	int N = atoi(char_row), i;
	int players[2] = {0} ,player = 0;
	for(i=0;i<N;++i)
	{
		struct Word this_word = read_word();
		// aici trebuie sa facem si bonusurile
		players[player] += calc_bonus(this_word,XX,YY);
		player = !player;
	}
	fprintf(stdout,"Player 1: %d Points\n",players[0]);
	fprintf(stdout,"Player 2: %d Points\n",players[1]);
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

int check_used(int N,char used[NUM_WORDS][SIZE], char word[SIZE])
{
		int j;
		for(j=0;j<N;++j)
		{
			if(strcmp(word,used[j])==0)
				return 1;
		}
		return 0;	// ok
}

void task4(char table[SIZE][SIZE])
{
	// deci trebuie sa citim N si liniile....
	char char_row[2*SIZE];
	char XX[4],YY[4];
	char used[NUM_WORDS][SIZE];
	gets(XX);
	gets(YY);
	// prima data citim pt N
	gets(char_row);
	int N = atoi(char_row), i,
		X, Y, D;
	for(i=0;i<N;++i)
	{
		struct Word this_word = read_word();
		strcpy(used[i],this_word.word);
		Y = this_word.Y;
		X = this_word.X;
		D = this_word.D;
		place_word(table,Y,X,D,this_word.word);
	}
	// incepem sa cautam o pozitie
	for(i=0;i<NUM_WORDS;++i)
	{
		if(check_used(N,used,words[i]))
			continue;
		// pana aici e bine
		// cautam prima litera
		int j;
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

/*
                  _           
  ___ ___   _ __ | |_ __ ___  
 / __/ _ \ | '_ \| | '_ ` _ \ 
| (_|  __/ | |_) | | | | | | |
 \___\___| | .__/|_|_| |_| |_|
           |_|                
*/

	// deci trebuie sa citim N si liniile....
	char char_row[2*SIZE];
	char XX[4],YY[4];
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
		struct Word this_word = read_word();
		strcpy(used[i],this_word.word);
		Y = this_word.Y;
		X = this_word.X;
		D = this_word.D;
		place_word(table,Y,X,D,this_word.word);
		players[player] += calc_bonus(this_word,XX,YY);
		player = !player;
	}
	// retinem cuvantul, pozitia,directia pt cel mai bun scor
	int X_max, Y_max, D_max, index_max = 0, score_max = 0;
	// petru fiecare cuvant
	for(i = 0;i < NUM_WORDS; ++i)
	{
		if(check_used(N,used,words[i]))
			continue;
		int j;
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
					struct Word this_word = {
						.X = pos,
						.Y = j,
						.D = 0
					};
					strcpy(this_word.word,words[i]);
					int score_temp = calc_bonus(this_word,XX,YY);
					if(score_temp > score_max)
					{
						score_max = score_temp;
						X_max = pos;
						Y_max = j;
						D_max = 0;
						index_max = i;
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
					struct Word this_word = {
						.X = pos,
						.Y = j,
						.D = 1
					};
					strcpy(this_word.word,words[i]);
					int score_temp = calc_bonus(this_word,XX,YY);
					if(score_temp > score_max)
					{
						score_max = score_temp;
						X_max = pos;
						Y_max = j;
						D_max = 1;
						index_max = i;
					}
				}
				pos = find_letter(NULL,words[i][0]);
			}	// while pozitie
		}	// for linii
	}	// for cuvinte
	if(players[1]+score_max >= players[1])
	{
		place_word(table,X_max,Y_max,D_max,words[index_max]);
		print_board(table);
	}
	else
		fprintf(stdout,"Fail!");
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
		case 5:
			{
				task0(table);
				task5(table);
			}break;
		default:
			{
				printf("ce plm?");
			}
	}
	return 0;
}
