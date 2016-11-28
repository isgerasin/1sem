#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <malloc.h> 
#include <stdlib.h>
#include "CPU_head.h"


#define MAXCHAR 2

#define NAMEVAR(var) #var

/*
#define DECLARE_COMMAND(name, num) name = num 

enum Commands_t
{
	#include "Commands.h";
};

#undef DECLARE_COMMAND
*/

enum Commands_t
{
	PUSH = 10, // положить в стек
	PUSHR = 11, // 
	JMP = 12,
	
	POP = 20,
	ADD = 21,
	SUB = 22,
	MUL = 23,
	DIV = 24,
	IN = 25,
	OUT = 26,
	END = 30
};

int File_Len( FILE* fl1 )
{
	fseek( fl1, 0, SEEK_END );
	int end = ftell( fl1 );
	
	fseek( fl1, 0, SEEK_SET );
	
	return end;
}

char* File_Open(const char* FlName )
{
	FILE* fl = fopen( FlName, "r+" );
	if ( !fl ) return NULL;
	
	int len = File_Len( fl );
	if ( len < 0 ) return NULL;
	
	char* buf = (char*) calloc( len+1, sizeof(*buf) );
	if ( !buf ) return NULL;
	
	int check = fread( buf, sizeof(*buf), len + 1, fl );
	if (check != len ) return NULL;
	
	fclose( fl );
	return buf;
}

int File_Write(const char* buf, const char* FlName)
{
	IF_DBG( assert( buf ) );
	FILE* fl = fopen( FlName, "w+" );
	if ( !fl ) return NULL;
	
	fputs(buf, fl);
	fclose( fl );
	return TRUE;
}

/*
char* DisAss_Func( char* com )
{
	static char comm[6] = {};

#define DECLARE_COMMAND(name, num)  if (stricmp (com, #num) == 0) \
                                       strcpy (comm, #name);     \
									else   
	#include "Commands.h"
	;

#undef DECLARE_COMMAND
 	
	return comm;
}
*/

int Ass_Func( char* com )
{
	/*
	#define DECLARE_COMMAND( com, num)	if ( strcmp( com, #num ) == 0) \
												return num; \
												else
	#include "Commands.h";
	*/
	
	if ( !strcmp( com, "push" ) )
		return PUSH;
	else if ( !strcmp( com, "pop" ) )
		return POP;
	else if ( !strcmp( com, "add" ) )
		return ADD;
	else if ( !strcmp( com, "mul" ) )
		return MUL;
	else if ( !strcmp( com, "sub" ) )
		return SUB;
	else if ( !strcmp( com, "in" ) )
		return IN;
	else if ( !strcmp( com, "pushr" ) )
		return PUSHR;
	else if ( !strcmp( com, "jmp" ) )
		return JMP;
	else if ( !strcmp( com, "end" ) )
		return END;
	
	return 0;
}

/*
char* Assm( char* bufa )
{
	char* bufb = (char*) calloc( strlen( bufa ), sizeof( *bufb ));
	
	char* p = strtok( bufa, " \n");
	//itoa( Ass_Func( p ), bufb, 10);
	
	//char* pi = itoc( Ass_Func(p) );
	
	char pi[MAXCHAR+1] = {};
	sprintf( pi, "%i", Ass_Func( p ) );
	strcat( bufb, pi );
	//free( pi );
	if ( Ass_Func(p) <= 12 )
	{
		strcat( bufb, " " );
		p = strtok( NULL, " \n" );
		strcat( bufb, p );
		strcat( bufb, "\n" );
	}
	else
	{
		strcat( bufb, "\n" );
	}
	
	while ( p != NULL )
	{
		p= strtok( NULL, " \n" );
		if ( p == NULL )
			break;
		//pi = itoc( Ass_Func(p) );
		sprintf( pi, "%i", Ass_Func( p ) );
		strcat( bufb, pi );
		//free( pi );
		
		//itoa( Ass_Func( p ), bufb, 10);
		
		if ( Ass_Func(p) <= 12 )
		{
			strcat( bufb, " " );
			p = strtok( NULL, " \n" );
			strcat( bufb, p );
			strcat( bufb, "\n" );
		}
		else
		{
			strcat( bufb, "\n" );
		}
	}
	return bufb;
}
*/


/*
char* Dis_Ass( char* bufa )
{
	char* bufb = (char*) calloc( 2 * strlen( bufa ) + 1, sizeof( *bufb ));
	
	char* p = strtok( bufa, " \n" );
	char* pi = DisAss_Func( p );
	strcat( bufb, pi );
	//free( pi );
	
	if ( atoi(p) <= 20)
	{
		strcat( bufb, " ");
		p = strtok( NULL, " \n");
		strcat( bufb, p );
		strcat( bufb, "\n" );
	}
	else
	{
		strcat( bufb, "\n" );
	}
	
	while ( p != NULL )
	{
		p = strtok( NULL, " \n" );
		if (p == NULL)
			break;
		pi = DisAss_Func( p );
		strcat( bufb, pi );
		//free( pi );
		
		if ( atoi(p) <= 20)
		{
			strcat( bufb, " ");
			p = strtok( NULL, " \n");
			if (p == NULL)
				break;
			strcat( bufb, p );
			strcat( bufb, "\n" );
		}
		else
		{
			strcat( bufb, "\n" );
		}
		
	}
	
	return bufb;
}
*/
  
double* Assm_V(const char* bufa)
{
	
	double* vctr = ( double* ) calloc( strlen( bufa ), sizeof( *vctr ) );
	if ( !vctr ) return NULL;
	
	char* p = strtok( ( char* ) bufa, " \n");
	int comnum = Ass_Func( p );
	int i = 0;
	vctr[i++] = ( double ) comnum;
	if ( comnum <= 20 )
		vctr[i++] = atof( strtok( NULL, " \n" ) );
	while ( p )
	{
		p = strtok( NULL, " \n");
		int comnum = Ass_Func( p );
		vctr[i++] = ( double ) comnum;
		
		if ( comnum <= 20 )
			vctr[i++] = atof( strtok( NULL, " \n" ) );
	}
	
	return vctr;
}

int File_Write_V(const char* flname, double* vctr, const int len )
{
	FILE* fl = fopen(flname, "wb");
	
	fwrite(vctr, sizeof( *vctr ), len, fl);
	fclose( fl );
}