#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SEPARATIONS " ;:.,?-!\n\r\t"
#define TRUE 1
#define FALSE 0
#define IS_NULL_RET( pntr ) if ( !pntr ) return NULL

size_t File_Len( FILE* fl1 )
{
	if ( fl1 == NULL ) return 0;
	
	fseek (fl1, 0, SEEK_END);
	size_t end = ftell (fl1);
	fseek (fl1, 0, SEEK_SET);
	
	return end;
}

char* FileOpen_to_text( const char* flname )
{
	IS_NULL_RET( flname );
	
	FILE* file = fopen( flname, "r" );
	IS_NULL_RET( file );
	size_t lenght = File_Len( file );
	
	char* buf = ( char* ) calloc( File_Len( file ), sizeof( *buf ) );
	IS_NULL_RET( buf );
	fread( buf, sizeof( *buf ), lenght + 1, file );
	fclose( file );
	
	return buf;
}

char** Set_Pntrs( char* text, size_t* pntrcount )
{
	IS_NULL_RET( text );
	
	char** ArrofP = ( char** ) calloc( strlen( text ), sizeof( *ArrofP ) );
	
	char* word = strtok( text, SEPARATIONS );
	size_t i = 0;
	for ( i = 0; word != NULL; i++ )
	{
		ArrofP[i] = word;
		word = strtok( NULL, SEPARATIONS );
	}
	*pntrcount = i;
	
	return ArrofP;
}

int CompABC( const void** stringa, const void** stringb )
{
	char* stra = ( char* ) *stringa;
	char* strb = ( char* ) *stringb;
	
	size_t lena = strlen( stra );
	size_t lenb = strlen( strb );
	
	size_t lenmin = 0;
	if ( lena > lenb )
		lenmin = lenb;
	else
		lenmin = lena;
	
	for ( size_t i = 0 ; i < lenmin; i++ )
		if( stra[i] != strb[i] )
			return stra[i] - strb[i];
			
	if ( lena != lenb ) 
		return lena - lenb;
	
	return 0;
}

int CompRhyme( const void** stringa, const void** stringb )
{
	char* stra = ( char* ) *stringa;
	char* strb = ( char* ) *stringb;
	
	size_t lena = strlen( stra );
	size_t lenb = strlen( strb );
	
	size_t lenmin = 0;
	if ( lena > lenb )
		lenmin = lenb;
	else
		lenmin = lena;
	size_t acount = lena - 1;
	size_t bcount = lenb - 1;
	
	for ( acount = lena - 1 ; acount >= 0 && bcount >= 0; acount-- )
	{
		if( stra[acount] != strb[bcount] )
			return stra[acount] - strb[bcount];
		bcount--;
	}
	if ( lena != lenb ) 
		return lena - lenb;
	return 0;
}

int FileWriteWords( const char* filename, const char** ArrofP, size_t pntrcount )
{
	if ( filename == NULL ) return FALSE;
	if ( ArrofP == NULL ) return FALSE;
	
	FILE* file = fopen( filename, "w" );
	
	for ( size_t i = 0; i < pntrcount; i++ )
		fprintf( file, "%s\n", ArrofP[i] );
	
	fclose( file );
	return TRUE;
}

int main(int argc, char **argv)
{
	char* text = FileOpen_to_text( "Text.txt" );
	if ( text == NULL )
	{
		printf( "Error! Can\'t open The file!\n" );
		return 1;
	}
	
	size_t pntrcount = 0;
	char** ArrofP = Set_Pntrs( text, &pntrcount );
	if ( text == NULL )
	{
		printf( "Error! Can\'t ser the pointers\n!" );
		return 2;
	}
	
	qsort( ArrofP, pntrcount, sizeof( *ArrofP ), CompABC );
	int check = FileWriteWords( "ABCsort.txt", ArrofP, pntrcount );
	if ( check == FALSE )
	{
		printf( "Error! Can\'t write file!" );
		return 3;
	}
	
	
	qsort( ArrofP, pntrcount, sizeof( *ArrofP ), CompRhyme );
	check = FileWriteWords( "Rhsort.txt", ArrofP, pntrcount );
	if ( check == FALSE )
	{
		printf( "Error! Can\'t write file!" );
		return 3;
	}
	
	free( ArrofP );
	free( text );
	
	
}
