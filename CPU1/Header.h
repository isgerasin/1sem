#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <malloc.h> 
#include <stdlib.h>

#define BADVAL -1
#define TRUE 1
#define FALSE 0
#define MAXCOMNUM 10
#define MAXPNTR 100
#define MAXPNTRNAME 20
#define MAXVAL 100

#define DBG

#ifdef DBG
    #define IF_DBG(code)  { code; }
#else
    #define IF_DBG(code)  {     ; }
#endif

#define DECLARE_COMMAND(name,  num)


// Stack===================================================
struct stack_t
{
	int c1 = 'I' + 'L' +'y' + 'a';
	double* data = NULL;
	int count = BADVAL;
	int size = BADVAL;
	int c2 = 'I' + 'L' + 'y' + 'a';
};

int Stack_Ok(     stack_t* stk );

int Stack_Dump(   stack_t* stk, char* txt );

int Stack_Ctor(   stack_t* stk, int n );

int Stack_Dtor(   stack_t* stk );

int Stack_Push(   stack_t* stk, double n );

double Stack_Pop( stack_t* stk );
//=========================================================

//Assembler================================================
enum Commands_t
{
	#define DEF_CMD( nm, numm, cnt ) nm = numm,
		#include <Commands.h>
		MAX
	#undef DEF_CMD
	/*
	PUSH = 10,  // положить в стек
	PUSHR = 11, // положить в регистр
	JMP = 12,   // переход
	POPR = 13,  // достать из регистра в стек
	JE = 14,    // ==
	JNE = 15,   // !=
	JA = 16,    // >
	JB = 17,    // <
	JAE = 18,   // >=
	JBE = 19,   // <=
	
	POP = 20,   // достать из стека
	ADD = 21,   // сложить 2 посл числа стека
	SUB = 22,   // вычесть 2 посл числа стека
	MUL = 23,   // умножить 2 посл числа стека
	DIV = 24,   // поделить
	IN = 25,    // ввод с консоли
	OUT = 26,   // вывод в консоль
	END = 30    // конец
	*/
};

struct point_t
{
	//int from;
	stack_t from;
	int to;
	
	char name[MAXPNTRNAME];
};

static point_t pntrs[MAXPNTR] = {};

int File_Len( FILE* fl1 );

char* File_Open( const char* FlName );

int File_Write_V( const char* flname, double* vctr, const int len );

int File_Write( const char* flname, char* vctr, const int len );

double Assm_Func( char* com );

char* Dis_Assm_Func( int comnum );

double* Assm_V( const char* bufa );

char* Dis_Assm_V( const double* buf, int len );

int Pntr_Found( const char* name, int j );

double Assm_V_P(double* vctr);

//=========================================================

//CPU======================================================
struct CPU_t
{
	int c1 = 0xFC;
	stack_t Stk_data;
	stack_t Stk_pntr;
	stack_t Stk_of_var_address;
	double ax;
	double bx;
	double cx;
	double dx;
	double ex;
	double fx;
	double gx;
	double hx;
	double ix;
	double jx;
	double kx;
	double lx;
	double mx;
	double nx;
	double ox;
	double px;
	double dinmem[MAXVAL];
	int c2 = 0xFC;
};



int CPU_Dump(    CPU_t* cpu );

int CPU_Ctor(    CPU_t* cpu, int lend, int lenp );

int CPU_Dtor(    CPU_t* cpu );

int CPU_Ok(      CPU_t* cpu );

int CPU_Cmp(     CPU_t* cpu );

int CPU_Cmp(     CPU_t* cpu );

int CPU_PUSH(    CPU_t* cpu, const double* code, int* i, int len );

double CPU_POP(  CPU_t* cpu, const double* code, int* i, int len );

int CPU_ADD(     CPU_t* cpu, const double* code, int* i, int len );

int CPU_SUB(     CPU_t* cpu, const double* code, int* i, int len );

int CPU_MUL(     CPU_t* cpu, const double* code, int* i, int len );

int CPU_DIV(     CPU_t* cpu, const double* code, int* i, int len );

int CPU_IN(      CPU_t* cpu, const double* code, int* i, int len );

int CPU_OUT(     CPU_t* cpu, const double* code, int* i, int len );

int CPU_POPR(    CPU_t* cpu, const double* code, int* i, int len );

int CPU_PUSHR(   CPU_t* cpu, const double* code, int* i, int len );

int CPU_JE(      CPU_t* cpu, const double* code, int* i, int len );

int CPU_JNE(     CPU_t* cpu, const double* code, int* i, int len );

int CPU_JA(      CPU_t* cpu, const double* code, int* i, int len );

int CPU_JB(      CPU_t* cpu, const double* code, int* i, int len );

int CPU_JAE(     CPU_t* cpu, const double* code, int* i, int len );

int CPU_JBE(     CPU_t* cpu, const double* code, int* i, int len );

int CPU_JMP(     CPU_t* cpu, const double* code, int* i, int len );

int CPU_END(     CPU_t* cpu, const double* code, int* i, int len );

int CPU_CALL(    CPU_t* cpu, const double* code, int* i, int len );

int CPU_RET(     CPU_t* cpu, const double* code, int* i, int len );

int CPU_Command( CPU_t* cpu, int comm, const double* code, int* i, int len );

int CPU_Loop(    CPU_t* cpu, const double* code, int len );


//====================================================