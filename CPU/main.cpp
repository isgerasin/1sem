#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <malloc.h> 
#include "CPU_head.h"

int main()
{
	char* bufa = File_Open( "ass.txt" );
	double* bufb = Assm_V( bufa );
	File_Write_V( "ass_go.txt", bufb, strlen( bufa ) );
	free( bufa );
	//free( bufb );
	//bufa = Dis_Assm( bufb );
	//File_Write( bufa, "ass_copy.txt");
	return 0;
}
