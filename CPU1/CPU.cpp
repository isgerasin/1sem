#include <math.h>
#include <assert.h>
#include "Header.h"


int CPU_Ctor(   CPU_t* cpu, int lend, int lenp )
{
	assert( cpu );
	
	Stack_Ctor( &cpu->Stk_data, lend );
	Stack_Ctor( &cpu->Stk_pntr, lenp );
	cpu->ax = 0;
	cpu->bx = 0;
	cpu->cx = 0;
	cpu->dx = 0;
	return CPU_Ok( cpu );
}

int CPU_Dtor(   CPU_t* cpu )
{
	assert( cpu );
	
	Stack_Dtor( &cpu->Stk_data );
	Stack_Dtor( &cpu->Stk_pntr );
	cpu->ax = 0;
	cpu->bx = 0;
	cpu->cx = 0;
	cpu->dx = 0;
	cpu->c1 = 0;
	cpu->c2 = 0;
	return TRUE;
}

int CPU_Ok(     CPU_t* cpu )
{
	assert( cpu );
	
	return Stack_Ok( &cpu->Stk_data )
		&& Stack_Ok( &cpu->Stk_pntr )
		&& (cpu->c1 ==  0xFC )
		&& (cpu->c2 ==  0xFC );
}

int CPU_Dump(   CPU_t* cpu )
{
	assert( cpu );
	printf( "Canary 1 = %d (%s)\n", cpu->c1, ( cpu->c1 ==  0xFC ) ? "ok" : "ERROR!!!");
	printf( "CPU (%s)\n", CPU_Ok( cpu ) ? "ok" : "ERROR!!!");
	
	Stack_Dump( &cpu->Stk_data, " CPU Dump " );

	printf( " ax = %f [%0X]\n", cpu->ax, &cpu->ax );
	printf( " bx = %f [%0X]\n", cpu->bx, &cpu->bx );
	printf( " cx = %f [%0X]\n", cpu->cx, &cpu->cx );
	printf( " dx = %f [%0X]\n", cpu->dx, &cpu->dx );
	printf( "Canary 2 = %d (%s)\n", cpu->c1, ( cpu->c2 ==  0xFC ) ? "ok" : "ERROR!!!");

}

int CPU_Cmp(    CPU_t* cpu )
{
	assert( cpu );
	
	double a = Stack_Pop( &cpu->Stk_data );
	double b = Stack_Pop( &cpu->Stk_data );
	
	Stack_Push( &cpu->Stk_data, b );
	Stack_Push( &cpu->Stk_data, a );
	//printf( "!%d!", b - a );
	return b - a;
}

int CPU_NOP(    CPU_t* cpu, const double* code, int* i, int len )
{
	return CPU_Ok( cpu );
}

int CPU_PUSH(   CPU_t* cpu, const double* code, int* i, int len )
{
	assert( cpu );
	
	Stack_Push( &cpu->Stk_data, code[++(*i)]  );
	return CPU_Ok( cpu );
}

double CPU_POP( CPU_t* cpu, const double* code, int* i, int len )
{
	assert( cpu );
	
	return Stack_Pop( &cpu->Stk_data );
}

int CPU_ADD(    CPU_t* cpu, const double* code, int* i, int len )
{
	assert( cpu );
	
	Stack_Push( &cpu->Stk_data, Stack_Pop( &cpu->Stk_data ) + Stack_Pop( &cpu->Stk_data ) );
	
	return CPU_Ok( cpu );
}

int CPU_SUB(    CPU_t* cpu, const double* code, int* i, int len )
{
	assert( cpu );
	
	Stack_Push( &cpu->Stk_data, -( Stack_Pop( &cpu->Stk_data ) - Stack_Pop( &cpu->Stk_data ) ) );
	return CPU_Ok( cpu );
}

int CPU_MUL(    CPU_t* cpu, const double* code, int* i, int len )
{
	assert( cpu );
	
	Stack_Push( &cpu->Stk_data, Stack_Pop( &cpu->Stk_data ) * Stack_Pop( &cpu->Stk_data ) );
	return CPU_Ok( cpu );
}

int CPU_DIV(    CPU_t* cpu, const double* code, int* i, int len )
{
	assert( cpu );
	
	Stack_Push( &cpu->Stk_data, 1 / Stack_Pop( &cpu->Stk_data ) * Stack_Pop( &cpu->Stk_data ) );
	return CPU_Ok( cpu );
}

int CPU_SQRT(   CPU_t* cpu, const double* code, int* i, int len )
{
	Stack_Push( &cpu->Stk_data, sqrt( Stack_Pop( &cpu->Stk_data ) ) );
	return CPU_Ok( cpu );
}

int CPU_SIN(    CPU_t* cpu, const double* code, int* i, int len )
{
	Stack_Push( &cpu->Stk_data, sin( Stack_Pop( &cpu->Stk_data ) ) );
	return CPU_Ok( cpu );
}

int CPU_COS(    CPU_t* cpu, const double* code, int* i, int len )
{
	Stack_Push( &cpu->Stk_data, cos( Stack_Pop( &cpu->Stk_data ) ) );
	return CPU_Ok( cpu );
}

int CPU_IN(     CPU_t* cpu, const double* code, int* i, int len )
{
	assert( cpu );
	
	double tmp = 0;
	scanf( "%lg", &tmp );
	Stack_Push( &cpu->Stk_data, tmp );
	return CPU_Ok( cpu );
}

int CPU_OUT(    CPU_t* cpu, const double* code, int* i, int len )
{
	assert( cpu );
	
	double tmp = Stack_Pop( &cpu->Stk_data );
	printf( "%f\n", tmp );
	Stack_Push( &cpu->Stk_data, tmp );
	return CPU_Ok( cpu );
}

int CPU_POPR(   CPU_t* cpu, const double* code, int* i, int len )
{
	assert( cpu );
	
	*( &cpu->ax + ( char ) code[++(*i)] - 'a') = Stack_Pop( &cpu->Stk_data );
	return CPU_Ok( cpu );
}

int CPU_PUSHR(  CPU_t* cpu, const double* code, int* i, int len )
{
	assert( cpu );
	
	Stack_Push( &cpu->Stk_data, *( &cpu->ax + ( char ) code[++(*i)] - 'a') );
	return CPU_Ok( cpu );
}

int CPU_JE(     CPU_t* cpu, const double* code, int* i, int len )
{
	 CPU_Cmp( cpu ) == 0 ?  *i = code[++(*i)] - 1 : ++(*i);
	 return CPU_Ok( cpu );
}

int CPU_JNE(    CPU_t* cpu, const double* code, int* i, int len )
{
	CPU_Cmp( cpu ) != 0 ?  *i = code[++(*i)] - 1 : ++(*i) ;
	return CPU_Ok( cpu );
}

int CPU_JA(     CPU_t* cpu, const double* code, int* i, int len )
{
	CPU_Cmp( cpu ) > 0 ? *i = code[++(*i)] - 1 :  ++(*i) ;
	return CPU_Ok( cpu );
}

int CPU_JB(     CPU_t* cpu, const double* code, int* i, int len )
{
	CPU_Cmp( cpu ) < 0 ?  *i = code[++(*i)] - 1: ++(*i) ;
	return CPU_Ok( cpu );
}

int CPU_JAE(    CPU_t* cpu, const double* code, int* i, int len )
{
	CPU_Cmp( cpu ) >= 0 ? *i = code[++(*i)] - 1 : ++(*i) ;
	return CPU_Ok( cpu );
}

int CPU_JBE(    CPU_t* cpu, const double* code, int* i, int len )
{
	CPU_Cmp( cpu ) <= 0 ? *i = code[++(*i)] - 1: ++(*i) ;
	return CPU_Ok( cpu );
}

int CPU_JMP(    CPU_t* cpu, const double* code, int* i, int len )
{
	*i = code[++(*i)] - 1;
	return CPU_Ok( cpu );
}

int CPU_CALL(   CPU_t* cpu, const double* code, int* i, int len )
{
	Stack_Push( &cpu->Stk_pntr, *i );
	*i = code[++(*i)] - 1;
	return CPU_Ok( cpu );
}

int CPU_RET(    CPU_t* cpu, const double* code, int* i, int len )
{
	*i = ( int ) Stack_Pop( &cpu->Stk_pntr );
	return CPU_Ok( cpu );
}

int CPU_END(    CPU_t* cpu, const double* code, int* i, int len )
{
	*i = len+1; 
	return CPU_Ok( cpu );
}

int CPU_Command( CPU_t* cpu, int comm, const double* code, int* i, int len )
{
	assert( cpu );
	assert( i );
	assert( code );
	
	#define DEF_CMD( nm, numm, par) case numm: CPU_##nm(cpu, code, i, len); \
																			break;
	switch( comm )
	{
	#include <Commands.h>
	default: break;
	}
	#undef DEF_CMD
	
	/*
	switch (comm)
	{
		
		case PUSH: CPU_Push( cpu, code[++(*i)] ); break;
		case 11: CPU_Pushr( cpu, ( char ) code[++(*i)] ); break;
		case 12: *i = code[++(*i)] - 1; break;
		case 13: CPU_Popr( cpu, ( char ) code[++(*i)] ); break;
		case 14: CPU_Cmp( cpu ) == 0 ? ++(*i) : *i = code[++(*i)] - 1; break;
		case 15: CPU_Cmp( cpu ) != 0 ? ++(*i) : *i = code[++(*i)] - 1; break;
		case 16: CPU_Cmp( cpu ) > 0 ? ++(*i) : *i = code[++(*i)] - 1; break;
		case 17: CPU_Cmp( cpu ) < 0 ? ++(*i) : *i = code[++(*i)] - 1; break;
		case 18: CPU_Cmp( cpu ) >= 0 ? ++(*i) : *i = code[++(*i)] - 1; break;
		case 19: CPU_Cmp( cpu ) <= 0 ? ++(*i) : *i = code[++(*i)] - 1; break;
		
		case 100: CPU_Pop( cpu ); break;
		case 101: CPU_Add( cpu ); break;
		case 102: CPU_Sub( cpu ); break;
		case 103: CPU_Mul( cpu ); break;
		case 104: CPU_Div( cpu ); break;
		case 105: CPU_In( cpu ); break;
		case 106: CPU_Out( cpu ); break;
		
		case 110: *i = len+1; break;
		default: break;
	}
	*/
	
	return CPU_Ok( cpu ) ;
}

int CPU_Loop( CPU_t* cpu, const double* code, int len )
{
	assert( cpu );
	assert( code );
	
	for ( int i = 0; i < len; i++ )
	{
		int check = CPU_Command( cpu, ( int ) code[i], code, &i, len );
		assert( check );
	}
	
	return CPU_Ok( cpu );
}

