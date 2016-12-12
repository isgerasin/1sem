//#include "C:\Program Files\TX\TXlib.h"
#include <string.h>
#include <locale.h>
#include "Akinator_Head.h"

stack_t stkt, stkf;



int Akin_Loop( TreeList_t* tlist )
{
	setlocale( LC_ALL,"Russian" );
    char str[MAXNAME] = "";
    do
    {
        printf( "Привет! Я Мега_Мозг2050. У меня есть функции:\n"
                "-[У]гадывать персонажа\n"
                "-[З]аписать данные\n"
                "-[П]оказать базу моих знаний\n"
                "-[Д]ать характеристику\n"
                "-[С]равнить обьекты\n"
                "-[В]ыход\n"
                "Чего ты хочешь ;) \?\n"  );
		
        scanf( "%s", str );
		if ( !strcmp( str, "У" ) || !strcmp( str, "у" ) )
			Akin_Guess( &tlist->head );
		else if ( !strcmp( str, "З" ) ||  !strcmp( str, "з" ) )
		{
			TreeList_write_pre( tlist, "List.txt" );
			printf( "Запись прошла успешно!\n");
		}
		else if ( !strcmp( str, "П" ) ||  !strcmp( str, "п" ) )
			TreeList_dump( tlist );
		else if ( !strcmp( str, "Д" ) ||  !strcmp( str, "д" ) )
			Akin_Charac( &tlist->head );
		else if ( !strcmp( str, "С" ) ||  !strcmp( str, "с" ) )
			Akin_Diff( &tlist->head );
		else if ( !strcmp( str, "В" ) ||  !strcmp( str, "в" ) )
		{
			printf( "Досвидули!\n");
			break;
			
		}
		else
			printf( "Неопознанный коммандос!\n" );

    } while (  1 );
	return TRUE;
}

int Akin_Guess( TreeElem_t* telem )
{
    ASSERT_OK( TreeElem, telem );
    if ( telem->left == NULL && telem->right == NULL )
    {
        printf( "%s. Угадал\? [Д]а [Н]ет\n", telem->data );
        char t[MAXNAME] = {};
		scanf( "%s", t );
        if ( !strcmp( t, "Д" ) || !strcmp( t, "д" ) )
            printf( "Елементарно!\n" );
        else if ( !strcmp( t, "Н" ) || !strcmp( t, "н" ) )
        {
			Akin_Add( telem );
        }
		else
			printf( "Ты читать умеешь? Только Д или Н !\n" );
    }
    else
    {
        printf( "%s\? [Д]а [Н]ет\n", telem->data );
        char p[MAXNAME] = "";
        scanf( "%s", p );
		if ( !strcmp( p, "Д") || !strcmp( p, "д" ) )
			Akin_Guess( telem->left );
		else if ( !strcmp( p, "Н") || !strcmp( p, "н" ) )
			Akin_Guess( telem->right );
		else
			printf( "Ты читать умеешь? Только Д или Н !\n" );
    }
	return TRUE;
}


void Akin_Add( TreeElem_t* telem )
{
	char* name = ( char* ) calloc( 2 * MAXNAME, sizeof( *name ) );
		char* diff = name + MAXNAME;
		TreeElem_t* ela = ( TreeElem_t* ) calloc( 1, sizeof( *ela ) );
		TreeElem_t* elb = ( TreeElem_t* ) calloc( 1, sizeof( *elb ) );
		
		scanf( "%*[^\n]" ); scanf( "%*c" );
		
		printf( "А кто это был?\n" );
		scanf( "%[^\n\r]", name );
		
		scanf( "%*[^\n]" ); scanf( "%*c" );
		
		printf( "Чем отличается %s от %s\?\n", name, telem->data );
		scanf( "%[^\n\r]", diff );
		
		scanf( "%*[^\n]" ); scanf( "%*c" );
		
		char sd[3] = "";
		char side = TreeElem_search( (telem->parent), telem );
		sprintf( sd, "%c", side );
		TreeElem_add( TreeElem_ctor( ela, diff ), sd, telem->parent );
		TreeElem_add( telem, "right", ela );
		TreeElem_add( TreeElem_ctor( elb, name ), "left", ela );
}

TreeElem_t* Akin_Search( TreeElem_t* telem, char* txt )
{
	assert( txt );
	//printf( "%s %s;\n", txt, telem->data );
	if ( !strcmp( telem->data, txt ) )
		return telem;
	
	TreeElem_t* ela = NULL;
	TreeElem_t* elb = NULL;
	if ( telem->right != NULL )
		ela = Akin_Search( telem->right, txt );
	if ( telem->left != NULL )
		elb = Akin_Search( telem->left, txt );
	
	if ( ela != NULL )
		return ela;
	if ( elb != NULL )
		return elb;
	
	return NULL;
}

void Akin_Charac( TreeElem_t* telem )
{
	ASSERT_OK( TreeElem, telem );
	Stack_Ctor( &stkt, MAXELEM );
	char* name = ( char* ) calloc( 2 * MAXNAME, sizeof( *name ) );
	
	scanf( "%*[^\n]" ); scanf( "%*c" );
	printf( "Введите имя персонажа: " );
	scanf( "%[^\n\r]", name );
	scanf( "%*[^\n]" ); scanf( "%*c" );
	
	TreeElem_t* pers = Akin_Search( telem, name );
	if ( pers == NULL )
		printf( "Нет такого персонажа!\n");
	else
	{
		TreeElem_t* tmp = pers;
		//TreeElem_dump( pers );
		printf( "Он:" );
		while ( tmp != tmp->parent )
		{
			TreeElem_t* tmpa = tmp;
			tmp = tmp->parent;
			char* text = NULL;
			if  ( TreeElem_search( tmp, tmpa ) == 'r' )
			{
				text = ( char* )  calloc( strlen( tmp->data ) + 5, sizeof( *text ) );
				sprintf( text, "не %s", tmp->data  );
			}
			else if ( TreeElem_search( tmp, tmpa ) == 'l')
			{
				text = ( char* )  calloc( strlen( tmp->data ) + 2, sizeof( *text ) );
				sprintf( text, "%s", tmp->data  );
			}
			Stack_Push( &stkt, text);
		}
		//Stack_Dump( &stkt, "efd");
		while ( stkt.count > 1 )
		{
			char* text = Stack_Pop( &stkt );
			printf( " %s,", text );
			free( text );
		}
		char* text = Stack_Pop( &stkt );
		printf( " %s.\n", text );
		free( text );
		
		Stack_Dtor( &stkt );
		
	}
	free( name );
}

int Akin_Diff( TreeElem_t* telem )
{
	ASSERT_OK( TreeElem, telem );
	Stack_Ctor( &stkt, MAXELEM );
	Stack_Ctor( &stkf, MAXELEM );
	
	char* name1 = ( char* ) calloc( 2 * MAXNAME, sizeof( *name1 ) );
	char* name2 = ( char* ) calloc( 2 * MAXNAME, sizeof( *name2 ) );
	scanf( "%*[^\n]" ); scanf( "%*c" );
	printf( "Введите имя первого персонажа: " );
	scanf( "%[^\n\r]", name1 );
	scanf( "%*[^\n]" ); scanf( "%*c" );

	printf( "Введите имя второго персонажа: " );
	scanf( "%[^\n\r]", name2 );
	scanf( "%*[^\n]" ); scanf( "%*c" );
	TreeElem_t* pers1 = Akin_Search( telem, name1 );
	TreeElem_t* pers2 = Akin_Search( telem, name2 );
	if ( pers1 == NULL || pers2 == NULL )
	{
		printf( "Некорректно введен один из персонажей \n");
		return FALSE;
	}
	
	TreeElem_t* tmp = pers1;
	//TreeElem_dump( pers );

	while ( tmp != tmp->parent )
	{
		TreeElem_t* tmpa = tmp;
		tmp = tmp->parent;
		char* text = NULL;
		if  ( TreeElem_search( tmp, tmpa ) == 'r' )
		{
			text = ( char* )  calloc( strlen( tmp->data ) + 5, sizeof( *text ) );
			sprintf( text, "не %s", tmp->data  );
		}
		else if ( TreeElem_search( tmp, tmpa ) == 'l')
		{
			text = ( char* )  calloc( strlen( tmp->data ) + 2, sizeof( *text ) );
			sprintf( text, "%s", tmp->data  );
		}
		Stack_Push( &stkt, text);
		
	}
	
	tmp = pers2;
	//TreeElem_dump( pers );
	
	while ( tmp != tmp->parent )
	{
		TreeElem_t* tmpa = tmp;
		tmp = tmp->parent;
		char* text = NULL;
		if  ( TreeElem_search( tmp, tmpa ) == 'r' )
		{
			text = ( char* )  calloc( strlen( tmp->data ) + 5, sizeof( *text ) );
			sprintf( text, "не %s", tmp->data  );
		}
		else if ( TreeElem_search( tmp, tmpa ) == 'l')
		{
			text = ( char* )  calloc( strlen( tmp->data ) + 2, sizeof( *text ) );
			sprintf( text, "%s", tmp->data  );
		}
		Stack_Push( &stkf, text);
		
	}
	
	char* chara = Stack_Pop( &stkt );
	char* charb = Stack_Pop( &stkf );
	int check = 0;
	if ( !strcmp( chara, charb ) )
	{
		printf( "Они оба:" );
		check++;
	}
	while( !strcmp( chara, charb ) )
	{
		printf( " %s,", chara );
		chara = Stack_Pop( &stkt );
		charb = Stack_Pop( &stkf );
	}
	if ( check > 0)
		printf( " но %s:", name1 );
	else
		printf( "%s:", name1 );
	printf( " %s,", chara );
	while( stkt.count > 0)
	{
		
		chara = Stack_Pop( &stkt );
		printf( " %s,", chara );
		free( chara);
	}
	printf( " а %s:", name2);
	printf( " %s,", charb );
	while( stkf.count > 0)
	{
		charb  = Stack_Pop( &stkf );
		printf( " %s,", charb );
		free( charb  );
	}
	printf( "\n" );
	Stack_Dtor( &stkt );
	Stack_Dtor( &stkf );
	return TRUE;
}
