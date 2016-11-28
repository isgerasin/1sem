#include <stdio.h>
#include "Header.h"

int main( int argc, const char* argv[] )
{
	/*
	stack_t stk;
	Stack_Ctor(&stk, 10);
	Stack_Push(&stk, 329.3746);
	Stack_Dump(&stk, "main1");
	Stack_Dtor(&stk);
	Stack_Dump(&stk, "main2");
	
	
	char str[6] = {};
	
	while ( str )
	{
		scanf("%s", &str );
		printf(" %d\n", Ass_Func( strtok( str, "\n") ) );
	}
	*/
	char* bufa = File_Open( "assm.txt" );
	int len = strlen( bufa );
	

	double* bufb = Assm_V( bufa);
	
	free( bufa );
	File_Write_V( "assm_go.txt", bufb, len );
	free( bufb );
	bufb = NULL;
	

	
	
	FILE* fl = fopen( "assm_go.txt", "rb" );
	len = File_Len( fl ) / 8;
	bufb = ( double* ) calloc( len , sizeof( double ) );
	fread( bufb, sizeof( *bufb ), len, fl );
	Assm_V_P( bufb );
	//for (int i = 0; i < len / 3; i++)
	//	printf( "%2d |%lg\n", i, bufb[i] );
	
	
	//char* das = Dis_Assm_V( bufb, len);
	
	//File_Write( "disasm.txt", das, strlen( das ) );
	
	CPU_t cpu;
	CPU_Ctor( &cpu, 30, 30 );
	//for (int i = 0; i < len / 3; i++)
		//printf( "%2d |%lg\n", i, bufb[i] );
	CPU_Loop( &cpu, bufb, len);
	CPU_Dump( &cpu );
	
	//Stack_Dump( &cpu.Stk_data, "Main" );

	
	
	
	CPU_Dtor( &cpu );
	return 0;
}
