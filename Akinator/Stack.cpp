#include "Akinator_Head.h"



int Stack_Ok(stack_t* stk)
{
    return     (stk )
            && (stk->c1 == 'I' + 'L' + 'y' + 'a')
            && (stk->c2 == 'I' + 'L' + 'y' + 'a')
            && (stk->count >= 0)
            && (stk->data != NULL)
            && (stk->size >= stk->count);
}

int Stack_Dump(stack_t* stk, char* txt)
{
    printf("%s\n", txt);
    printf("stack_t stk (%s) = [%0X] \ncanary 1 stack = %i %s\n{\n",
            (Stack_Ok(stk)) ? "Ok" : "ERROR!!!!\a",
            stk, stk->c1, (stk->c1 == 300+('A'+2)) ? "OK" : "ERROR!!!");
            
    
    for (int i = 0; i < stk->size; i++)
    {
        printf("%c [%i] = %f\n\t\t", (i < stk->count) ? '*' : ' ',
        i, *(stk->data+i) );
    }
    printf("\n\t\t}\n"
           "\t" "count = %i\n"
           "\t" "size = %i\n}\n"
           "canary 2 stack = %i %s\n\n",
                
                stk->count, stk->size, stk->c2, (stk->c2 == 367) ? "OK" : "ERROR!!!");
    printf("==============================================================\n");
    return TRUE;
}

int Stack_Ctor(stack_t* stk, int n)
{

    
    stk->data = ( char** ) calloc(n+2, sizeof( *stk->data ) );
    stk->size = n;
    stk->count = 0;

    return TRUE;
}

int Stack_Dtor(stack_t* stk)
{

    
    free((stk->data));
    stk->data = NULL;
    stk->size = -1;
    stk->count = -1;
    stk->c1 = 0;
    stk->c2 = 0;
    
    return TRUE;
}

int Stack_Push(stack_t* stk, char* n)
{

    
    stk->data[stk->count] = n;
    stk->count++;

    return TRUE;
}

char* Stack_Pop(stack_t* stk)
{
   
    return stk->data[--stk->count];
  
}