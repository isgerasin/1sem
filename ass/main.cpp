#in#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <malloc.h> 
#include "CPU_head.h"

#define PUSH 10 // добавка к стеку
#define POP 11 // вытащить из стека
#define ADD 12 // сложить 2 последних числа
#define MUL 13 // поделить 
#define SUB 14 // вычитание
#define IN 15 // ввод с консоли
#define PUSHR 16 // добавка в регистр
#define JMP 17 // переход
#define END 20 // Конец


int File_Len(FILE* fl1)
{
#ifdef DEBUG
	assert(fl1);
#endif
	
	fseek(fl1, 0, SEEK_END);
	int end = ftell(fl1);
	
	fseek(fl1, 0, SEEK_SET);
	
	return end;
}

char* File_Open(char* FlName)
{
	fl = fopen(FlName, "w+");
	int len = File_Len(fl);
	char* buf = (char*) calloc(len+1, sizeof(*buf));
	fread(buf, sizeof(*buf), len + 1, fl);
	return buf;
}

int Ass_Func(char* com)
{
	if (!strcmp(com, "push"))
		return PUSH;
	else if (!strcmp(com, "pop"))
		return POP;
	else if (!strcmp(com, "add"))
		return ADD;
	else if (!strcmp(com, "mul"))
		return MUL;
	else if (!strcmp(com, "sub"))
		return SUB;
	else if (!strcmp(com, "in"))
		return IN;
	else if (!strcmp(com, "pushr"))
		return PUSHR;
	else if (!strcmp(com, "pushr"))
		return PUSHR;
	else if (!strcmp(com, "jmp"))
		return JMP;
	else if (!strcmp(com, "end"))
		return END;
	
}

char* Ass(char* bufa)
{
	char* bufb = (char*) calloc( 1, sizeof(bufa) + 1);
	
	char com[10] = {}; 
	double arg = 0;
	int c = 0;
	
	do {
		sscanf(bufa, "%s %f\n", com, &arg);
		c = Ass_Func(com);
		printf(bufb, "%i %f/n", c, arg);
	} while ( c != END);
	assert(0)
	return bufb;
}

int main()
{
	FILE* fl;
	File_Open("Ass.txt", fl);
	
}