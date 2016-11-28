#include "Diff_Head.h"

#define CANARY 0XABBAABBA
#define MAXVAL 100
#define MAXNAME 100
#define TFORMAT "v2.0Trsv"

struct Variable_t
{
	char name[MAXNAME];
	double data;
} typedef Variable_t;

Variable_t array_of_variable_for_Tree_using_only_in_Var_search[MAXVAL] = {};

int DotNumber_For_use_in_Dump_Dot_only = 0;
int TexNumber_For_use_in_Dump_Tex_only = 0;


int File_Len( FILE* fl1 )
{
    fseek( fl1, 0, SEEK_END );
    int end = ftell( fl1 );
    
    fseek( fl1, 0, SEEK_SET );
    
    return end;
}

int TreeElem_ok(   TreeElem_t* telem )
{
    return telem &&
           telem->cnra == CANARY &&
           telem->cnrb == CANARY &&
           telem->parent != NULL;
}

int TreeElem_dump( TreeElem_t* telem )
{
    printf( "____________________________________\n" );
    if ( telem == NULL )
        printf( "ERROR: NULL ADRESS!!\n" );
    else
    {
        printf( "TreeElem_t (%s) [%X]\n"
                "\tCanary 1 = %X\n"
                "\t\tData = \"%lg\"\n"
				"\t \Type = %d\n"
                "\tRight = [%X]\n"
                "\tLeft  = [%X]\n"
                "\tParent = [%X]\n"
                "\tCanary 2 = %X\n",
                TreeElem_ok( telem ) ? "OK" : "ERROR",
                telem, telem->cnra, telem->data, telem->t,
                telem->right, telem->left, telem->parent, telem->cnrb );
    }
    printf( "____________________________________\n" );
    return TRUE;
}

TreeElem_t* TreeElem_ctor( TreeElem_t* telem, const char* data )
{
	ASSERT_OK( TreeElem, telem );
    if ( telem == NULL ) return NULL;
    
    telem->cnra = CANARY;
    telem->cnrb = CANARY;
    //telem->data = data;
    telem->left = NULL;
    telem->right = NULL;
    telem->parent = telem;
    
	TreeElem_Type_Write( telem, data );
	
	
    ASSERT_OK( TreeElem, telem );
    return telem ;
}

int TreeElem_dtor( TreeElem_t* telem )
{
	ASSERT_OK( TreeElem, telem );
    if ( telem == NULL ) return FALSE;
    
    telem->left = NULL;
    telem->right = NULL;
    telem->parent = NULL;
	if ( telem->parent != telem )
		free( telem );
	telem->data = 0;
    return TRUE;
}

TreeElem_t* TreeElem_ctor_sub( TreeElem_t* telem, const char* str, TreeElem_t* sub, const char* side )
{
	ASSERT_OK( TreeElem, telem ); ASSERT_OK( TreeElem, sub );
	if ( telem == NULL || sub == NULL || side == NULL ) return NULL;
    TreeElem_ctor( telem, str );
    switch( *side )
    {
        case 'r' : telem->right = sub; break;
        case 'l' : telem->left  = sub; break;
        default : return FALSE;
    }
    sub->parent = telem;
    ASSERT_OK( TreeElem, telem ); ASSERT_OK( TreeElem, sub );
    return telem;
}

int TreeElem_dtor_sub( TreeElem_t* telem )
{
	ASSERT_OK( TreeElem, telem );
	if ( telem == NULL ) return FALSE;
	
    ASSERT_OK( TreeElem, telem );
    
    if ( telem->right != NULL )
        TreeElem_dtor_sub( telem->right );
    if ( telem->left != NULL )
        TreeElem_dtor_sub( telem->left );
    TreeElem_dtor( telem );
    
	ASSERT_OK( TreeElem, telem );
    return TRUE;
}

int TreeList_ctor( TreeList_t* tlist, const char* str )
{
	ASSERT_OK( TreeList, tlist ); 
    if ( tlist == NULL )return FALSE;
	
	
	
    tlist->cnra = CANARY;
    tlist->cnrb = CANARY;
    tlist->count = 1;

    TreeElem_ctor( &tlist->head, str );
    tlist->head.parent = &tlist->head;
	
	ASSERT_OK( TreeList, tlist );
    return TRUE;
}

int TreeList_dtor( TreeList_t* tlist )
{
	ASSERT_OK( TreeList, tlist );
    if ( tlist == NULL ) return FALSE;

    
    tlist->cnra = 0;
    tlist->cnrb = 0;
    tlist->count = -1;
    TreeElem_dtor_sub( tlist->head.right );
	TreeElem_dtor_sub( tlist->head.left );
    
    return TRUE;
}

int Tree_ok( TreeElem_t* telem )
{
    if ( telem == NULL ) return TRUE;
    return TreeElem_ok( telem ) &&
            Tree_ok( telem->left ) &&
            Tree_ok( telem->right );
}

int TreeList_ok( TreeList_t* tlist )
{
    
    
    return  tlist &&
			tlist->count >= 1 &&
			tlist->cnra == CANARY &&
            tlist->cnrb == CANARY &&
            Tree_ok( &tlist->head );
}

int TreeElem_dump_dot( TreeElem_t* elem, FILE* out )
{

    if ( elem == NULL ) return TRUE;
	//printf( "%d %lg\n", elem->t, elem->data );
    if ( elem->left != NULL )
    {
		if ( elem->t == oper && elem->left->t == constant )
			fprintf( out, "\t\"%c\n[%X]\"->\"%lg\n[%X]\"\n",
			( char ) elem->data, elem, elem->left->data, elem->left);
		else if ( elem->t == oper && elem->left->t == oper )
			fprintf( out, "\t\"%c\n[%X]\"->\"%c\n[%X]\"\n",
			( char ) elem->data, elem, ( char ) elem->left->data, elem->left );
		else if ( elem->t == oper && elem->left->t == val )
		{
			fprintf( out, "\t\"%c\n[%X]\"->\"%s\n[%X]\"\n",
			( char ) elem->data, elem,
			array_of_variable_for_Tree_using_only_in_Var_search[ ( int ) elem->left->data].name, elem->left );
			//printf( "%d %s\n", ( int ) elem->left->data, array_of_variable_for_Tree_using_only_in_Var_search[ ( int ) elem->left->data].name );
		}
		else 
			return FALSE;
		TreeElem_dump_dot( elem->left, out );
    }
	
     if ( elem->right != NULL )
    {
		if ( elem->t == oper && elem->right->t == constant )
			fprintf( out, "\t\"%c\n[%X]\"->\"%lg\n[%X]\"\n",
			( char ) elem->data, elem, elem->right->data, elem->right);
		else if ( elem->t == oper && elem->right->t == oper )
			fprintf( out, "\t\"%c\n[%X]\"->\"%c\n[%X]\"\n",
			( char ) elem->data, elem, ( char ) elem->right->data, elem->right );
		else if ( elem->t == oper && elem->right->t == val )
		{
			fprintf( out, "\t\"%c\n[%X]\"->\"%s\n[%X]\"\n",
			( char ) elem->data, elem,
			array_of_variable_for_Tree_using_only_in_Var_search[ ( int ) elem->right->data].name, elem->right );
			//printf( "%d %s\n", ( int ) elem->right->data, array_of_variable_for_Tree_using_only_in_Var_search[ ( int ) elem->right->data].name );
		}
		else 
			return FALSE;
		TreeElem_dump_dot( elem->right, out );
    }
	
    return  TRUE;
}

int TreeList_dump( TreeList_t* tlist )
{
    return TreeList_dump_dot( tlist );
}

int TreeList_dump_dot( TreeList_t* tlist )
{
	ASSERT_OK( TreeList, tlist );
	
    DotNumber_For_use_in_Dump_Dot_only++;
    if ( tlist == NULL )
	{
		printf( "ERROR!! NULL ADRESS LIST" );
		return FALSE;
	}
    char fname[ sizeof( "graph_tree.gv" ) + 3 ];
    sprintf( fname, "graph_tree%d.gv", DotNumber_For_use_in_Dump_Dot_only );
    FILE* out = fopen( fname, "w" );
    if ( out == NULL ) return FALSE;
    
    fprintf( out, "digraph Tree\n{\n\tnode[shape = polygon]; edge[dir=both];\n" );
    
    if ( TreeElem_dump_dot( &tlist->head, out ) == FALSE )
	{
		
		fprintf( out, "}" );
		fclose( out );
		printf( "Error! Can't dump the tree!\n" );
		return FALSE;
	}
    
    fprintf( out, "}" );
    fclose( out );
    char com[100] = "";
    sprintf( com, "dot"
            " -Tsvg -O %s", fname );
    system( com );
    char com1[20] = "";
    sprintf( com1, "xdot %s", fname );
    system( com1 );
	ASSERT_OK( TreeList, tlist );
    return TRUE;
}

char TreeElem_search( TreeElem_t* elem, TreeElem_t* what )
{
	ASSERT_OK( TreeElem, elem ); ASSERT_OK( TreeElem, what );
	if ( elem == NULL || what == NULL ) return 'e';
	
	if ( elem->right == what ) return 'r';
	else if ( elem->left == what ) return 'l';
	else return 'n';

}

int TreeElem_write_pre( TreeElem_t* elem, FILE* out )
{
	ASSERT_OK( TreeElem, elem );
    if ( elem == NULL || out == NULL ) return FALSE;
    printf( "%lg\n", elem->data );
	if ( elem->t == constant || elem->t == unformat )
		fprintf( out, "( %d ", elem->data );
	else if ( elem->t == oper )
		fprintf( out, "( %c ",  ( char ) elem->data );
	else if ( elem->t == val )
		fprintf( out, "( %s ",  array_of_variable_for_Tree_using_only_in_Var_search[( int ) elem->data].name );
		
    
    if ( elem->left == NULL )
        fprintf( out, "nil " );
    else
        if ( TreeElem_write_pre( elem->left, out ) == FALSE )
			return FALSE;
    if ( elem->right == NULL )
        fprintf( out, "nil " );
    else
        if ( TreeElem_write_pre( elem->right, out ) == FALSE )
			return FALSE;
    
    fprintf( out, ") " );
    
    ASSERT_OK( TreeElem, elem );
    return TRUE;
}

int TreeElem_Type_Write( TreeElem_t* elem, const char* tmp )
{
	ASSERT_OK( TreeElem, elem ); 
	//printf( "%s\n", tmp );
	if ( elem == NULL || tmp == NULL ) return FALSE;
	
	if ( '0' <= tmp[0] && tmp[0] <= '9')
	{
		elem->t = constant;
		elem->data = ( Tree_Type ) atof( tmp );
	}
	else if ( tmp[0] == sub || tmp[0] == add || tmp[0] == mul || tmp[0] == divv  )
	{
		elem->t = oper;
		elem->data = ( Tree_Type ) tmp[0];
		//printf( "%c ", ( char ) elem->data );
	}
	else if ( 'A' <= tmp[0] && tmp[0] <= 'z')
	{
		elem->t = val;
		elem->data = ( Tree_Type ) Var_search( tmp );
	}
	else 
	{
		elem->t = unformat;
		elem->data = ( Tree_Type ) 0;
	}
	
	return ( int ) elem->t;
}

//array_of_variable_for_Tree_using_only_in_Var_search

int Var_search( const char* tmp )
{
	if ( tmp == NULL ) return -1;
	//printf ( "%s \n", tmp );
	Variable_t* pntr = array_of_variable_for_Tree_using_only_in_Var_search;
	int i = 0;
	
	for ( i = 0; pntr[i].name[0] != '\0'; i++ )
		if ( strcmp( pntr[i].name, tmp ) == 0 )
			return i;
	strncpy( pntr[i].name, tmp, MAXNAME );
	return i;
}

int TreeElem_read_pre(  TreeElem_t* elem )
{
	ASSERT_OK( TreeElem, elem );
    if ( elem == NULL ) return FALSE;
	
    int check = 0;
    char* tmp = strtok( NULL, " " );
	
	
	TreeElem_Type_Write( elem, tmp );
	
	//elem->data = ( Tree_Type ) atof( tmp );
	
    tmp = strtok( NULL, " " );

    switch ( *tmp )
    {
        case 'n' : elem->left = NULL; break;
        case '(' : TreeElem_read_pre( elem->left =
                    TreeElem_ctor( ( TreeElem_t* ) calloc( 1, sizeof( TreeElem_t ) ), 0 ) );
					elem->left->parent = elem; break;
        default : check++;
    }
    tmp = strtok( NULL, " " );
    //printf( "!%s!\n", tmp );
    switch ( *tmp )
    {
        case 'n' : elem->right = NULL; break;
        case '(' : TreeElem_read_pre( elem->right =
                    TreeElem_ctor( ( TreeElem_t* ) calloc( 1, sizeof( TreeElem_t ) ), 0 ) );
					elem->right->parent = elem; break;
        default: check++;
    }
    if ( *strtok( NULL, " " ) != ')' ) check++;
    
    ASSERT_OK( TreeElem, elem );
    return !check;
}

int TreeList_write_pre( TreeList_t* tlist, const char* fname )
{
	ASSERT_OK( TreeList, tlist );
    if ( tlist == NULL || fname == NULL ) return FALSE;
    
    FILE* out = fopen( fname, "wb" );
    if ( out == NULL ) return FALSE;
    fprintf( out, TFORMAT " " );
    
    if ( TreeElem_write_pre( &tlist->head, out ) == FALSE )
	{
		fclose( out );
		return FALSE;
	}
    
    fclose( out );
	ASSERT_OK( TreeList, tlist );
    return TRUE;
}

int TreeList_read_pre( TreeList_t* tlist, const char* fname )
{
    if ( tlist == NULL || fname == NULL ) return FALSE;
    
    FILE* in = fopen( fname, "r" );
    if ( in == NULL ) return FALSE;

    
    char* buff = ( char* ) calloc( File_Len( in ) + 2, sizeof( *buff ) );
    fread( buff, File_Len( in ) + 2, sizeof( *buff ), in );
    fclose( in );
    char* tmp = strtok( buff, " ");
    //printf( "!%s!%d\n", tmp, strcmp( tmp, "v1.0Trsv" ) );
    if ( strcmp( tmp, TFORMAT ) )
    {
        printf( "Error! Unknown Format %s\n", fname );
        return FALSE;
    }
    
    tmp = strtok( NULL, " " );
    if ( tmp == NULL || *tmp != '(' )
    {
        printf( "Error! Can't read the file or it empty %s\n", fname );
        return FALSE;
    }
    else
        if ( !TreeElem_read_pre( &tlist->head ) )
        {
            
            printf( "Error! Can't read the file %s\n", fname );
            TreeList_dtor( tlist );
            return FALSE;
            
        }
    return TRUE;
}

int TreeList_write_in( TreeList_t* tlist, const char* fname )
{
	ASSERT_OK( TreeList, tlist );
    if ( tlist == NULL || fname == NULL ) return FALSE;
    
    FILE* out = fopen( fname, "wb" );
    if ( out == NULL ) return FALSE;
    fprintf( out, TFORMAT " " );
    
    if ( TreeElem_write_in( &tlist->head, out ) == FALSE )
	{
		fclose( out );
		return FALSE;
	}
    
    fclose( out );
	ASSERT_OK( TreeList, tlist );
    return TRUE;
}

int TreeElem_write_in( TreeElem_t* elem, FILE* out )
{
	ASSERT_OK( TreeElem, elem );
    if ( elem == NULL || out == NULL ) return FALSE;
    
	fprintf( out, "( " );
    
    if ( elem->left == NULL )
        fprintf( out, "nil " );
    else

        if ( TreeElem_write_in( elem->left, out ) == FALSE )
			return FALSE;
			
	//printf( " %lg %d\n", elem->data, elem->t );
	
	if ( elem->t == constant || elem->t == unformat )
		fprintf( out, "%lg ", elem->data );
	else if ( elem->t == oper )
		fprintf( out, "%c ",  ( char ) elem->data );
	else if ( elem->t == val )
		fprintf( out, "%s ",  array_of_variable_for_Tree_using_only_in_Var_search[( int ) elem->data].name );
	
    if ( elem->right == NULL )
        fprintf( out, "nil " );
    else
        if ( TreeElem_write_in( elem->right, out ) == FALSE )
			return FALSE;
    
    fprintf( out, ") " );
    
    ASSERT_OK( TreeElem, elem );
    return TRUE;
}

int TreeElem_read_in(  TreeElem_t* elem )
{
	ASSERT_OK( TreeElem, elem );
    if ( elem == NULL ) return FALSE;
	
    int check = 0;
    char* tmp = strtok( NULL, " " );

    switch ( *tmp )
    {
        case 'n' : elem->left = NULL; break;
        case '(' : TreeElem_read_in( elem->left =
                    TreeElem_ctor( ( TreeElem_t* ) calloc( 1, sizeof( TreeElem_t ) ), "0" ) );
					elem->left->parent = elem; break;
        default : check++;
    }
    tmp = strtok( NULL, " " );
	
	TreeElem_Type_Write( elem, tmp );
	//TreeElem_dump( elem );
	
	tmp = strtok( NULL, " " );
    //printf( "!%s!\n", tmp );
    switch ( *tmp )
    {
        case 'n' : elem->right = NULL; break;
        case '(' : TreeElem_read_in( elem->right =
                    TreeElem_ctor( ( TreeElem_t* ) calloc( 1, sizeof( TreeElem_t ) ), "0" ) );
					elem->right->parent = elem; break;
        default: check++;
    }
    if ( *strtok( NULL, " " ) != ')' ) check++;
    
    ASSERT_OK( TreeElem, elem );
    return !check;
}

int TreeList_read_in( TreeList_t* tlist, const char* fname )
{
    if ( tlist == NULL || fname == NULL ) return FALSE;
    
    FILE* in = fopen( fname, "r" );
    if ( in == NULL ) return FALSE;

    
    char* buff = ( char* ) calloc( File_Len( in ) + 2, sizeof( *buff ) );
    fread( buff, File_Len( in ) + 2, sizeof( *buff ), in );
    fclose( in );
    char* tmp = strtok( buff, " ");
    //printf( "!%s!%d\n", tmp, strcmp( tmp, "v1.0Trsv" ) );
    if ( strcmp( tmp, TFORMAT ) )
    {
        printf( "Error! Unknown Format %s\n", fname );
        return FALSE;
    }
    
    tmp = strtok( NULL, " " );
    if ( tmp == NULL || *tmp != '(' )
    {
        printf( "Error! Can't read the file or it empty %s\n", fname );
        return FALSE;
    }
    else
        if ( !TreeElem_read_in( &tlist->head ) )
        {
            
            printf( "Error! Can't read the file %s\n", fname );
            TreeList_dtor( tlist );
            return FALSE;
        }
    return TRUE;
}

int TreeElem_dump_tex(  TreeElem_t* elem, FILE* out )
{
	if ( elem == NULL || out == NULL ) return FALSE;
	ASSERT_OK( TreeElem, elem );
	
	if ( elem->t == oper )
		fprintf( out, "( " );
    
    if ( elem->left != NULL )
        if ( TreeElem_dump_tex( elem->left, out ) == FALSE )
			return FALSE;
			
	//printf( " %lg %d\n", elem->data, elem->t );
	
	if ( elem->t == constant || elem->t == unformat )
		fprintf( out, "%lg ", elem->data );
	else if ( elem->t == oper )
		fprintf( out, "%c ",  ( char ) elem->data );
	else if ( elem->t == val )
		fprintf( out, "%s ",  array_of_variable_for_Tree_using_only_in_Var_search[( int ) elem->data].name );
	
	
    if ( elem->right != NULL )
        if ( TreeElem_dump_tex( elem->right, out ) == FALSE )
			return FALSE;
    
	if ( elem->t == oper )
		fprintf( out, ") " );
		
	ASSERT_OK( TreeElem, elem );
	return TRUE;
}

int TreeList_dump_tex(  TreeList_t* tlist )
{
	if ( tlist == NULL ) return FALSE;
	ASSERT_OK( TreeList, tlist );
	
	TexNumber_For_use_in_Dump_Tex_only++;
	
	char flname[ sizeof( "Tree_Tex" ) + 3 ] = {};
	sprintf( flname, "Tree_Tex%d.tex",  TexNumber_For_use_in_Dump_Tex_only );
	
	FILE* fl = fopen( flname, "w" );
	if ( fl == FALSE ) return FALSE;
	
	
	
	fprintf( fl, "\\documentclass{article}\n\\begin{document}\n$" );
	
	if ( TreeElem_dump_tex( &tlist->head, fl ) == FALSE )
	{
		printf( "Error! Can't write tree in file!\n" );
		return FALSE;
	}
	
	fprintf( fl, "$\n\\end{document}" );
	
	fclose( fl );
	
	char com1[200] = "";
	sprintf( com1, "pdflatex %s", flname );
	system( com1 );
	char com2[200] = "";
	sprintf( com2, "xpdf Tree_Tex%d.pdf", TexNumber_For_use_in_Dump_Tex_only );
	system( com2 );
	
	ASSERT_OK( TreeList, tlist );
	
	return TRUE;
}

TreeElem_t* TreeElem_cpy_sub( TreeElem_t* elem )
{
	if ( elem == NULL ) return NULL;
	ASSERT_OK( TreeElem, elem );
	
	TreeElem_t* telem = ( TreeElem_t* ) calloc( 1, sizeof ( *telem ) );
	
	TreeElem_ctor( telem, "1" );
	telem->data = elem->data;
	telem->t = elem->t;
	
	
	if ( elem->left != NULL )
	{
		telem->left = TreeElem_cpy_sub( elem->left );
		if ( telem->left != NULL  )
			telem->left->parent = telem;
	}
	
	if ( elem->right != NULL )
	{
		telem->right = TreeElem_cpy_sub( elem->right );
		if ( telem->right != NULL )
			telem->right->parent = telem;
	}
	
	//TreeElem_dump( telem );
	//printf( "++++++===++++===++++===++++===+++===+++\n");
	//TreeElem_dump( elem );
	//assert( 0);
	return telem;
}

TreeList_t* TreeList_cpy_sub( TreeList_t* list )
{
	if ( list == NULL ) return FALSE;
	ASSERT_OK( TreeList, list );
	
	TreeList_t* tlist = ( TreeElem_t* ) calloc( 1, sizeof ( *tlist ) );
	
	TreeList_ctor( tlist, "1" );
	tlist->head.data = list->head.data;
	tlist->head.t = list->head.t;
	
	if ( ( tlist->head.right = TreeElem_cpy_sub( list->head.right ) ) != NULL )
		list->head.right->parent = &list->head;
	
	if ( ( tlist->head.left = TreeElem_cpy_sub( list->head.left ) ) != NULL )
		list->head.left->parent = &list->head;
	
	//TreeElem_dump( &tlist->head );
	//printf( "++++++===++++===++++===++++===+++===+++\n");
	//TreeElem_dump( &list->head);
	
	return tlist;
}
