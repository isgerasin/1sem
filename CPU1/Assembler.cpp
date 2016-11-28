#include <string.h>
#include "Header.h"



int File_Len( FILE* fl1 )
{
	fseek( fl1, 0, SEEK_END );
	int end = ftell( fl1 );
	
	fseek( fl1, 0, SEEK_SET );
	
	return end;
}

char* File_Open(const char* FlName )
{
	FILE* fl = fopen( FlName, "r" );
	if ( !fl ) return NULL;
	
	int len = File_Len( fl );
	if ( len < 0 ) return NULL;
	
	char* buf = (char*) calloc( len+1, sizeof(*buf) );
	if ( !buf ) return NULL;
	
	int check  = fread( buf, sizeof(*buf), len + 1, fl );
	
	fclose( fl );
	return buf;
}

int File_Write_V(const char* flname, double* vctr, const int len )
{
	FILE* fl = fopen(flname, "wb");
	
	fwrite(vctr, sizeof( *vctr ), len, fl);
	fclose( fl );
	
	return TRUE;
}

int File_Write(const char* flname, char* vctr, const int len )
{
	FILE* fl = fopen(flname, "w");
	
	fwrite(vctr, sizeof( *vctr ), len, fl);
	fclose( fl );
	
	return TRUE;
}

double Assm_Func( char* com )
{
	assert( com );
	
	int i = 0;
	while ( com[i] != '\0' )
		com[i++] += 'A' - 'a';
	
	Commands_t tmp = ( Commands_t ) 0;
	#define DEF_CMD( nm, numm, cnt )	if ( strcmp( com, #nm ) == 0) \
												tmp = nm; \
												else
	#include "Commands.h"
	tmp = ( Commands_t ) atof( com );
	#undef DEF_CMD
	/*
	if ( com[0] == ':' ) 
		return -1;
	else if ( !strcmp( com, "push" ) )
		tmp = PUSH;
	else if ( !strcmp( com, "pop" ) )
		tmp = POP;
	else if ( !strcmp( com, "add" ) )
		tmp = ADD;
	else if ( !strcmp( com, "mul" ) )
		tmp = MUL;
	else if ( !strcmp( com, "sub" ) )
		tmp = SUB;
	else if ( !strcmp( com, "in" ) )
		tmp = IN;
	else if ( !strcmp( com, "out" ) )
		tmp = OUT;
	else if ( !strcmp( com, "div" ) )
		tmp = DIV;
	else if ( !strcmp( com, "pushr" ) )
		tmp = PUSHR;
	else if ( !strcmp( com, "jmp" ) )
		tmp = JMP;
	else if ( !strcmp( com, "end" ) )
		tmp = END;
	else if ( !strcmp( com, "popr" ) )
		tmp = POPR;
	else if ( !strcmp( com, "je" ) )
		tmp = JE;
	else if ( !strcmp( com, "jne" ) )
		tmp = JNE;
	else if ( !strcmp( com, "ja" ) )
		tmp = JA;
	else if ( !strcmp( com, "jb" ) )
		tmp = JB;
	else if ( !strcmp( com, "jae" ) )
		tmp = JAE;
	else if ( !strcmp( com, "jbe" ) )
		tmp = JBE;
	else 
		return atof( com );
	*/
	
	//printf( "%lg %s\n", ( double ) tmp, com );
	
	return ( double ) tmp ;
}

char* Dis_Assm_Func( int comnum )
{
	static char com[MAXCOMNUM] = {};
	#define DEF_CMD(nm, numm, cnt) if ( comnum == numm ) \
										strcpy( com, #nm ); \
									else
	#include "Commands.h"
	;
	#undef DEF_CMD
	
	
	return com;
}

double Assm_V_P(double* vctr)
{
	int i = 0;
	while ( (pntrs[i].from != 0) || (pntrs[i].to != 0) )
		vctr[pntrs[i].from] = pntrs[i++].to;
	
	return TRUE;
}

int Pntr_Found( const char* name, int j )
{
	for ( int i = 0; i <= j; i++)
		if ( strcmp( name, pntrs[i].name) == 0)
			return i;
	return j;
}

double* Assm_V(const char* bufa)
{
	
	double* vctr = ( double* ) calloc( strlen( bufa ), sizeof( *vctr ) );
	
	
	
	if ( !vctr ) return NULL;
	
	char* p = strtok( ( char* ) bufa, " \n\r");
	
	int j = 0;
	int i = 0;
	if ( p[0] == ':' )
	{
		int tmpj = j;
		j = Pntr_Found( &p[1], j );
		pntrs[j].to = i;
		strcpy( pntrs[j].name, &p[1] );
		vctr[i++] = NOP;
		if ( j == tmpj )
			j = ++tmpj;
		else
			j = tmpj;
	}
	else
	{
		int comnum = Assm_Func( p );
		vctr[i++] = ( double ) comnum;
		if ( ( 13 <= comnum ) && ( comnum <= 21 ) )
		{
			p = strtok( NULL, " \n\r" );
			pntrs[j].from = i;
			strcpy( pntrs[j++].name, p );
			vctr[i++] = -1;
		}
		else if ( comnum < 100 )
		{
			p = strtok( NULL, " \n\r" );
			if (p[0] < 'a' )
				vctr[i++] = atof( p );
			else 
				vctr[i++] = p[0];
		}
	}
	while ( p )
	{
		p = strtok( NULL, " \n\r" );
		if ( p == NULL ) break;
		
		if ( p[0] == ':' )
		{
			int tmpj = j;
			j = Pntr_Found( &p[1], j );
			pntrs[j].to = i;
			strcpy( pntrs[j].name, &p[1] );
			vctr[i++] = NOP;
			if ( j == tmpj )
				j = ++tmpj;
			else
				j = tmpj;
		}
		else
		{
			int comnum = Assm_Func( p );
			vctr[i++] = ( double ) comnum;
			
			if ( ( 13 <= comnum ) && ( comnum <= 20 ) )
			{
				p = strtok( NULL, " \n\r" );
				int tmpj = j;
				j = Pntr_Found( p , j );
				pntrs[j].from = i;
				strcpy( pntrs[j].name, p );
				//printf( "!%s! %i \n", p, i);
				vctr[i++] = -1;
				if ( j == tmpj )
					j = ++tmpj;
				else
					j = tmpj;
			}
			else if ( comnum < 100 )
			{
				p = strtok( NULL, " \n\r" );
				if (p[0] < 'a')
					vctr[i++] = atof( p );
				else 
					vctr[i++] = p[0];
			}
		}
	}
	
	//for (int i = 0; i < MAXPNTR; i++)
	//{
	//	printf( "%s %d %d\n", pntrs[i].name, pntrs[i].from, pntrs[i].to );
	//}
	
	return vctr;
}

char* Dis_Assm_V(const double* buf, int len)
{
	char* str = ( char* ) calloc( sizeof( buf ) * 10, sizeof( *str ) );
	if ( !str ) return NULL;
	char* c = str;
	
	for (int i = 0; i < len; i++)
	{
		if ( buf[i] == 0 ) break;
		else if ( buf[i] < 100)
		{
			c += sprintf( c, "%s %f\n", Dis_Assm_Func( ( int ) buf[i] ), buf[++i] );
			//printf( "%d_____%s %f\n",buf[i-1],  Dis_Assm_Func( buf[i-1] ), buf[i] );
		}
		else
		{
			c += sprintf( c, "%s\n", Dis_Assm_Func( ( int ) buf[i] ) );
			//printf("%s\n", Dis_Assm_Func( buf[i] ) );
		}
		if ( buf[i-1] == END ) break;
	}
	//printf("\n!!!%s!!!!", str);
	return str;
	
}