#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <malloc.h> 
#include <CPU_head.h>

#define DBG


int Stack_Ok(stack_t* stk)
{
	return     (stk )
			&& (stk->c1 == 'I' + 'L' + 'y' + 'a') 
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
			stk, stk->c1, (stk->c1 == 300+('A'+2)) ? "OK" : "ERROR!!!");
			
	printf("\tdata[%i] = [%0X]\n\t\tcanary 1 data = %lg %s\n\t\t{\n\t\t",
					stk->size, stk->data, *(stk->data - 1),
					( *(stk->data - 1) == 367) ? "OK" : "ERROR!!!" );
	for (int i = 0; i < stk->size; i++)
	{
		printf("%c [%i] = %f\n\t\t", (i < stk->count) ? '*' : ' ', 
		i, *(stk->data+i) );
	}
	printf("\n\t\t}\n"
		   "\t\t" "canary 2 data = %lg %s\n"
		   "\t" "count = %i\n"
		   "\t" "size = %i\n}\n"
		   "canary 2 stack = %i %s\n\n",
				*(stk->data + stk->size), (*(stk->data + stk->size) == 367) ? "OK" : "ERROR!!!", 
				stk->count, stk->size, stk->c2, (stk->c2 == 367) ? "OK" : "ERROR!!!");
	printf("==============================================================\n");
	return TRUE;
}

int Stack_Ctor(stack_t* stk, int n)
{
	IF_DBG(assert(stk));
	
	stk->data = (double*) calloc(n+2, sizeof(*stk->data));
	stk->size = n;
	stk->count = 0;
	*stk->data           = 'I' + 'L' + 'y' + 'a';
	*(stk->data + n + 1) = 'I' + 'L' + 'y' + 'a';
	stk->data++; 
	
	IF_DBG( Stack_Ok(stk) ? : Stack_Dump(stk, "Ctor") );
	return TRUE;
}

int Stack_Dtor(stack_t* stk)
{
	IF_DBG( assert(stk) );
	IF_DBG( Stack_Ok(stk) ? : Stack_Dump(stk, "Dtor") );
	
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
	IF_DBG(assert(stk));
	IF_DBG(Stack_Ok(stk) ? : Stack_Dump(stk, "Push1") );
	
	stk->data[stk->count] = n;
	stk->count++;
	
	IF_DBG(assert(stk));
	IF_DBG(Stack_Ok(stk) ? : Stack_Dump(stk, "Push2") );
	return TRUE;
}

double Stack_Pop(stack_t* stk)
{
	IF_DBG(assert(stk));
	IF_DBG(Stack_Ok(stk) ? : Stack_Dump(stk, "Pop1") );
	
	double tmp = stk->data[--stk->count];
	
	IF_DBG(assert(stk));
	IF_DBG(Stack_Ok(stk) ? : Stack_Dump(stk, "Pop1") );
	return tmp;
}