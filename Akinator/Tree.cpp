#include <string.h>
#include "Akinator_Head.h"

#define CANARY 0XABBAABBA

int DotNum = 0;

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
           telem->parent != NULL &&
           telem->data != NULL &&
           telem->datalen == strlen( telem->data );
}

int TreeElem_dump( TreeElem_t* telem )
{
    printf( "____________________________________\n" );
    if ( telem == NULL )
        printf( "ERROR: NULL ADRESS!!\n" );
    else
    {
        printf(
                "TreeElem_t (%s) [%X]\n"
                "\tCanary 1 = %X\n"
                "\t\tData = \"%s\"\n"
                "\tData Lenght = %d\n"
                "\tRight = [%X]\n"
                "\tLeft  = [%X]\n"
                "\tParent = [%X]\n"
                "\tCanary 2 = %X\n",
                TreeElem_ok( telem ) ? "OK" : "ERROR",
                telem, telem->cnra, telem->data, telem->datalen,
                telem->right, telem->left, telem->parent, telem->cnrb );
    }
    printf( "____________________________________\n" );
    return true;
}

TreeElem_t* TreeElem_ctor( TreeElem_t* telem, const char* str )
{
    assert( telem ); assert( str );
    
    telem->cnra = CANARY;
    telem->cnrb = CANARY;
    telem->datalen = strlen( str );
    telem->data = str;
    telem->left = NULL;
    telem->right = NULL;
    telem->parent = telem;
    
    ASSERT_OK( TreeElem, telem );
    return telem ;
}

int TreeElem_dtor( TreeElem_t* telem )
{
    ASSERT_OK( TreeElem, telem );
    
    telem->datalen = -1;
    
    telem->left = NULL;
    telem->right = NULL;
    telem->parent = NULL;
	if ( telem->parent != telem )
		free( telem );
	free( (void*) telem->data );
	telem->data = NULL;
	
    return TRUE;
}

TreeElem_t* TreeElem_ctor_sub( TreeElem_t* telem, const char* str, TreeElem_t* sub, const char* side )
{
    assert( telem ); assert( str ); assert( sub ); assert ( side );
    TreeElem_ctor( telem, str );
    switch( *side )
    {
        case 'r' : telem->right = sub; break;
        case 'l' : telem->left  = sub; break;
        default : return FALSE;
    }
    sub->parent = telem;
    telem->datalen = strlen( str );
    ASSERT_OK( TreeElem, telem ); ASSERT_OK( TreeElem, sub );
    return telem;
}

int TreeElem_dtor_sub( TreeElem_t* telem )
{
    ASSERT_OK( TreeElem, telem );
    
    if ( telem->right != NULL )
        TreeElem_dtor_sub( telem->right );
    if ( telem->left != NULL )
        TreeElem_dtor_sub( telem->left );
    TreeElem_dtor( telem );
    free( telem );
    return TRUE;
}

int Tree_ok(       TreeElem_t* telem )
{
    if ( telem == NULL ) return TRUE;
    return TreeElem_ok( telem ) &&
            Tree_ok( telem->left ) &&
            Tree_ok( telem->right );
}

int TreeList_ok(   TreeList_t* tlist )
{
    
    
    return tlist &&
            tlist->cnra == CANARY &&
            tlist->cnrb == CANARY &&
            Tree_ok( &tlist->head );
}

int TreeElem_dump_dot( TreeElem_t* elem, FILE* out )
{
    assert( out );
    if ( elem == NULL ) return TRUE;
    if ( elem->left )
    {
        fprintf( out, "\t\"%s\"->\"%s\"[label = да]\n", elem->data, elem->left->data );
        TreeElem_dump_dot( elem->left, out );
    }
    if ( elem->right )
    {
        fprintf( out, "\t\"%s\"->\"%s\"[label = нет]\n", elem->data, elem->right->data );
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
    DotNum++;
    if ( tlist == NULL ) printf( "ERROR!! NULL ADRESS LIST" );
    char fname[ sizeof( "graph_tree.gv" ) + 3 ];
    sprintf( fname, "graph_tree%d.gv", DotNum );
    FILE* out = fopen( fname, "w" );
    if ( !out ) return FALSE;
    
    fprintf( out, "digraph Tree\n{\n\tnode[shape =polygon]; edge[dir=both];\n" );
    
    if ( !TreeElem_dump_dot( &tlist->head, out ) ) return FALSE;
    
    fprintf( out, "}" );
    fclose( out );
    char com[100] = "";
    sprintf( com, "dot"
            " -Tsvg -O %s", fname );
    system( com );
    char com1[20] = "";
    sprintf( com1, "xdot %s", fname );
    system( com1 );
    return TRUE;
}

int TreeList_ctor( TreeList_t* tlist, const char* str )
{
    
    
    tlist->cnra = CANARY;
    tlist->cnrb = CANARY;
    tlist->count = 1;
	tlist->head.parent = &tlist->head;
    TreeElem_ctor( &tlist->head, str );
    tlist->head.parent = &tlist->head;
    return TRUE;
}

int TreeList_dtor( TreeList_t* tlist )
{
    ASSERT_OK( TreeList, tlist );

    
    tlist->cnra = 0;
    tlist->cnrb = 0;
    tlist->count = -1;
    TreeElem_dtor_sub( tlist->head.right );
	TreeElem_dtor_sub( tlist->head.left );
    
    return TRUE;
}

int TreeElem_write_pre( TreeElem_t* elem, FILE* out )
{
    ASSERT_OK( TreeElem, elem ); assert( out );
    
    fprintf( out, "( \"%s\" ", elem->data );
    
    if ( elem->left == NULL )
        fprintf( out, "nil " );
    else
        TreeElem_write_pre( elem->left, out );
    if ( elem->right == NULL )
        fprintf( out, "nil " );
    else
        TreeElem_write_pre( elem->right, out );
    
    fprintf( out, ") " );
    
    ASSERT_OK( TreeElem, elem );
    return TRUE;
}

int TreeElem_read_pre(  TreeElem_t* elem )
{
    ASSERT_OK( TreeElem, elem );
    int check = 0;
    char* tmp = strtok( NULL, "\"" );
    elem->data = tmp;
    elem->datalen = strlen( tmp );
    tmp = strtok( NULL, " " );
    //printf( "!%s!\n", tmp );
    switch ( *tmp )
    {
        case 'n' : elem->left = NULL; break;
        case '(' : TreeElem_read_pre( elem->left =
                    TreeElem_ctor( ( TreeElem_t* ) calloc( 1, sizeof( TreeElem_t ) ), "" ) );
					elem->left->parent = elem; break;
        default : check++;
    }
    tmp = strtok( NULL, " " );
    //printf( "!%s!\n", tmp );
    switch ( *tmp )
    {
        case 'n' : elem->right = NULL; break;
        case '(' : TreeElem_read_pre( elem->right =
                    TreeElem_ctor( ( TreeElem_t* ) calloc( 1, sizeof( TreeElem_t ) ), "" ) );
					elem->right->parent = elem; break;
        default: check++;
    }
    if ( *strtok( NULL, " " ) != ')' ) check++;
    
    
    return !check;
}

int TreeList_write_pre( TreeList_t* tlist, const char* fname )
{
    assert( fname ); ASSERT_OK( TreeList, tlist );
    
    FILE* out = fopen( fname, "wb" );
    if ( out == NULL ) return FALSE;
    fprintf( out, "v1.0Trsv " );
    
    TreeElem_write_pre( &tlist->head, out );
    
    fclose( out );
    return TRUE;
}

int TreeList_read_pre( TreeList_t* tlist, const char* fname )
{
    assert( fname ); ASSERT_OK( TreeList, tlist );
    
    FILE* in = fopen( fname, "r" );
    if ( in == NULL ) return FALSE;

    
    char* buff = ( char* ) calloc( File_Len( in ) + 2, sizeof( *buff ) );
    fread( buff, File_Len( in ) + 2, sizeof( *buff ), in );
    fclose( in );
    char* tmp = strtok( buff, " ");
    //printf( "!%s!%d\n", tmp, strcmp( tmp, "v1.0Trsv" ) );
    if ( strcmp( tmp, "v1.0Trsv" ) )
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
    tlist->head.parent = &tlist->head;
    return TRUE;
}

TreeElem_t* TreeElem_add( TreeElem_t* telem, const char* side, TreeElem_t* to )
{
    ASSERT_OK( TreeElem, telem ); ASSERT_OK( TreeElem, to ); assert( side );
    
    switch( side[0] )
    {
        case 'r': to->right = telem; break;
        case 'l': to->left = telem; break;
        default : return FALSE;
    }
    telem->parent = to;
    
    ASSERT_OK( TreeElem, telem ); ASSERT_OK( TreeElem, to );
    return telem;
}

char TreeElem_search( TreeElem_t* elem, TreeElem_t* what )
{
	ASSERT_OK( TreeElem, elem ); ASSERT_OK( TreeElem, what );

	if ( elem->right == what ) return 'r';
	else if ( elem->left == what ) return 'l';
	else return 'q';

}