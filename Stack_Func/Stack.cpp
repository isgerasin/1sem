#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <malloc.h> 

#define DBG
#define TRUE 1
#define FALSE 0
#define BADVAL -1

struct stack_t
{
	int c1 = 'I' + 'L' + 'y' + 'a';
	double* data = NULL;
	int count = BADVAL;
	int size = BADVAL;
	int c2 = 'I' + 'L' + 'y' + 'a';
};

int Stack_Ctor(stack_t* stk, int n);

int Stack_Dtor(stack_t* stk);

int Stack_Ok(stack_t* stk);

int Stack_Dump(stack_t* stk, char* txt);

int Stack_Push(stack_t* stk, double n);

double Stack_Pop(stack_t* stk);

int main(int argc, char **argv)
{
	stack_t stk;
	Stack_Ctor(&stk, 10);
	for (int i = 0; i < 11; i++)
		Stack_Push(&stk, 45*i);
	//Stack_Dump(&stk);
	//for (int i = 0; i < 0; i++)
	//	Stack_Pop(&stk);
	Stack_Dump(&stk, "Main" );
	Stack_Dtor(&stk);
}

int Stack_Ok(stack_t* stk)
{
	assert(stk);
	
	return (stk->c1 == 'I' + 'L' + 'y' + 'a') 
			&& (stk->c2 == 'I' + 'L' + 'y' + 'a') 
			&& (stk->count >= 0)
			&& (stk->data != NULL) 
			&& (stk->size >= stk->count) 
			&& ( *(stk->data - 1) == 'I' + 'L' + 'y' + 'a') 
			&& ( *(stk->data + stk->size) == 'I' + 'L' + 'y' + 'a');
}

int Stack_Dump(stack_t* stk, char* txt)
{
	printf("%s\n", txt);
	printf("stack_t stk (%s) = [%0X] \ncanary 1 stack = %i %s\n{\n", 
			(Stack_Ok(stk)) ? "Ok" : "ERROR!!!!\a", 
			stk, stk->c1, (stk->c1 == 367) ? "OK" : "ERROR!!!");
			
	printf("\tdata[%i] = [%0X]\n\t\tcanary 1 data = %lg %s\n\t\t{\n\t\t",
					stk->size, stk->data, *(stk->data - 1),
					( *(stk->data - 1) == 367) ? "OK" : "ERROR!!!" );
	for (int i = 0; i < stk->size; i++)
	{
		printf("%c [%i] = %f\n\t\t", (i < stk->count) ? '*' : ' ', 
		i, *(stk->data+i) );
	}
	printf("\n\t\t}\n\t\tcanary 2 data = %lg %s\n\tcount= \
%i\n\tsize = %i\n}\ncanary 2 stack = %i %s\n\n",
				*(stk->data + stk->size), (*(stk->data + stk->size) == 367) ? "OK" : "ERROR!!!", 
				stk->count, stk->size, stk->c2, (stk->c2 == 367) ? "OK" : "ERROR!!!");
	printf("==============================================================\n");
	return TRUE;
}

int Stack_Ctor(stack_t* stk, int n)
{
#ifdef DBG
	assert(stk);
#endif
	
	stk->data = (double*) calloc(n+2, sizeof(*stk->data));
	stk->size = n;
	stk->count = 0;
	*stk->data= 'I' + 'L' + 'y' + 'a';
	*(stk->data + n + 1) = 'I' + 'L' + 'y' + 'a';
	stk->data++; 
	
#ifdef DBG
	Stack_Ok(stk) ? : Stack_Dump(stk, "Ctor");
#endif
	return TRUE;
}

int Stack_Dtor(stack_t* stk)
{
#ifdef DBG
	assert(stk);
	Stack_Ok(stk) ? : Stack_Dump(stk, "Dtor");
#endif
	
	
	free((stk->data) - 1);
	stk->data = NULL;
	stk->size = BADVAL;
	stk->count = BADVAL;
	stk->c1 = 0;
	stk->c2 = 0;
	
	return TRUE;
}

int Stack_Push(stack_t* stk, double n)
{
#ifdef DBG
	assert(stk);
	Stack_Ok(stk) ? : Stack_Dump(stk, "Push1");
#endif
	
	stk->data[stk->count] = n;
	stk->count++;
	
#ifdef DBG
	assert(stk);
	Stack_Ok(stk) ? : Stack_Dump(stk, "Push2");
#endif
	return TRUE;
}

double Stack_Pop(stack_t* stk)
{
#ifdef DBG
	assert(stk);
	Stack_Ok(stk) ? : Stack_Dump(stk, "Pop1");
#endif
	
	double tmp = stk->data[--stk->count];
	
	
#ifdef DBG
	assert(stk);
	Stack_Ok(stk) ? : Stack_Dump(stk, "Pop2");
#endif
	
	return tmp;
}