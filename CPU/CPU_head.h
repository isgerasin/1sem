#define BADVAL -1
#define TRUE 1
#define FALSE 0

#ifdef DBG
    #define IF_DBG(code)  { code; }
#else
    #define IF_DBG(code)  {     ; }
#endif

#define DECLARE_COMMAND(name,  num)

struct stack_t
{
	int c1 = 'ILya';
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

int File_Len(FILE* fl1);

char* File_Open(const char* FlName);

int File_Write(char* buf, const char* FlName);

char* Ass(char* buf);

char* Dis_Assm( char* bufa );

int Ass_Func(char* com);

char* DisAss_Func(char* com);

double* Assm_V(char* bufa);

int File_Write_V(const char* flname, double* vctr, const int len );


