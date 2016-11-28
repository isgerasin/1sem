#include "HeadDown.h"


char* s = NULL;
//FILE* out = fopen( "Graph.gv", "w" );

int GetG0( char* str )
{
	assert( str );
	s = str;
	printf( "Я G0, запускаю  E!\n" );
	
	//fprintf( out, "digraph rt {\n" );
	int result = GetE();
	if ( *s != '\0' ) return -1;
	printf( "Я G0, да тут в конце \\0 !\n" );
	//fprintf( out, "}\n" );
	//fclose( out );
	//system( "xdot Graph.gv");
	return result;
}

int GetN()
{
	int res = 0;
	printf( "Я N, начинаю копать!\n" );
	
	while( '0' <= *s && *s <= '9' )
	{
		res = res * 10 + *s - '0';
		s++;
		//check++;
	}
	printf( "Я N, возвращаю %d\n", res );
	return res;
}

int GetE()
{
	printf( "Я E, запускаю T \n" );
	//fprintf( out, "\tE -> T;\n" );
	int res = GetT();
	while ( *s == '+' || *s == '-' )
	{
		char op = *s;
		s++;
		printf( "Я E, Получил _%c\n", op );
		printf( "Я E, запускаю  T\n" );
		//fprintf( out, "\tE -> T;\n");
		int res2 = GetT();
		if ( op == '+' ) res += res2;
		if ( op == '-' ) res -= res2;
	}
	printf( "Я E, Возвращаю %d\n", res );
	return res;
}

int GetT()
{
	printf( "Я T, запускаю D\n" );
	//fprintf( out, "\tT -> N;\n");
	int res = GetD();
	while ( *s == '*' || *s == '/')
	{
		char op = *s;
		s++;
		printf( "Я Т, Получил _%c_\n", op );
		printf( "Я Т, запускаю  D\n" );
		//fprintf( out, "\tT -> N;\n");
		int res2 = GetD();
		if ( op == '*' ) res *= res2;
		if ( op == '/' && *s == '0' ) assert(0);
		if ( op == '/' ) res /= res2;
	}
	printf( "Я T, Возвращаю %d\n", res );
	return res;
}

int GetP()
{
	int res = 0;
	printf( "Я P, Получил %c\n", *s );
	if( *s == '(')
	{
		s++;
		printf( "Я P, запускаю E\n" );
		res = GetE();
		assert( *s == ')' );
		s++;
	}
	else
	{

		res = GetN();
		printf( "Я P, запускаю N \n" );
	}
	printf( "Я P, возвращаю %d\n", res );
	return res;
}

int GetD()
{
	int res = GetP();
	while( *s == '^' )
	{
		s++;
		res = pow( res, GetP() );
		
	}
	return res;
}