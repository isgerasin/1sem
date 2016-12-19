#include "Head.h"

//Token* ArrTok = NULL;

TreeList_t* Get0( Token* tmp )
{
	IS_NULL( tmp );
	arr_of_functions_cntr = 0;
	for ( int i = 0; i < MAXFUNCT; arr_of_functions[i++] = NULL );
	
	Token* ArrTok = tmp;
	int i = 0;
	//printf( "Я Get0, запускаю GetOpAB\n");
	
	TreeElem_t* res = GetPiec( ArrTok, &i );
	
	if ( res == NULL && ArrTok[i].type != endofprog )
		printf( "Error at: %d %s\n", i, ArrTok[i].str );
	else if ( res == NULL && ArrTok[i].type == endofprog)
		printf( "Следи за скобками, хоть что-то ты можешь?\n" );
		
	IS_NULL( res );
	res->parent = res;
	TreeList_t* listres = calloc( 1, sizeof( *listres ) );
	
	TreeList_ctor( listres, "0" );
	free( listres->head );
	listres->head = res;
	
	if ( ArrTok[i].type != endofprog )
	{
		printf( "Error at: %d %s\n", i, ArrTok[i].str );
		return NULL;
		
	}
	//printf( "Я Get0, Получил listres\n");
	return listres;
}

TreeElem_t* GetOpAB( Token* ArrTok, int* i )
{
	IS_NULL( ArrTok ); IS_NULL( i );
	
	TreeElem_t* res = GetOpSA( ArrTok, i );
	IS_NULL( res );
	
	while( ArrTok[*i].type == oper &&
		( ( char ) ArrTok[*i].data == E || ( char ) ArrTok[*i].data == NE || 
		  ( char ) ArrTok[*i].data == A || ( char ) ArrTok[*i].data == AE ||
		  ( char ) ArrTok[*i].data == B || ( char ) ArrTok[*i].data == BE   ) )
		{
			res = New_type( ArrTok[*i].data, oper, res, NULL );
			//printf( "Я GetOpmSA, добавил MD\n");
			IS_NULL( res );
			(*i)++;
			res->right = GetOpSA( ArrTok, i );
			IS_NULL( res->right );
			res->right->parent = res;
			//printf( "Я GetOpmSA, получил MD\n");
		}
	//printf( "Я GetOpmSA, Возвращаю res\n");
	return res;
	
}

TreeElem_t* GetOpSA( Token* ArrTok, int* i )
{
	IS_NULL( ArrTok ); IS_NULL( i );
	//printf( "Я GetOpmSA, запускаю GetOpMD\n");
	
	TreeElem_t* res = GetOpMD( ArrTok, i );
	IS_NULL( res );
	//printf( "Я GetOpmSA, получил MD\n");
	
	while( ArrTok[*i].type == oper &&
		( ( char ) ArrTok[*i].data == '+' || ( char ) ArrTok[*i].data == '-') )
		{
			res = New_type( ArrTok[*i].data, oper, res, NULL );
			//printf( "Я GetOpmSA, добавил MD\n");
			IS_NULL( res );
			(*i)++;
			res->right = GetOpMD( ArrTok, i );
			IS_NULL( res->right );
			res->right->parent = res;
			//printf( "Я GetOpmSA, получил MD\n");
		}
	//printf( "Я GetOpmSA, Возвращаю res\n");
	return res;
}



TreeElem_t* GetOpMD( Token* ArrTok, int* i )
{
	IS_NULL( ArrTok ); IS_NULL( i );
	//printf( "Я GetOpmMD, запускаю GetBr\n");
	TreeElem_t* res = GetPow( ArrTok, i );
	IS_NULL( res );
	//printf( "Я GetOpmMD, получил Br\n");
	while( ArrTok[*i].type == oper &&
		( ( char ) ArrTok[*i].data == '*' || ( char ) ArrTok[*i].data == '/') )
		{
			res = New_type( ArrTok[*i].data, oper, res, NULL );
			//printf( "Я GetOpmMD, добавил Br\n");
			IS_NULL( res );
			(*i)++;
			res->right = GetPow( ArrTok, i );
			IS_NULL( res->right );
			res->right->parent = res;
			//printf( "Я GetOpmMD, получил Br\n");
		}
	//printf( "Я GetOpmMD, Возвращаю res\n");
	return res;
}

TreeElem_t* GetN( Token* ArrTok, int* i )
{
	IS_NULL( ArrTok ); IS_NULL( i );
	if ( ArrTok[*i].type == constant || ArrTok[*i].type == val )
	{
		TreeElem_t* res = New_type( ArrTok[*i].data, ArrTok[*i].type, NULL, NULL );
		IS_NULL( res );
		res->str = ArrTok[*i].str;
		//printf( "Я GetN, Возвращаю res\n" );
		(*i)++;
		return res;
	}
	else 
	{
		//printf( "Я GetN, НЕ Получил res\n" );
		return NULL;
	}
}

TreeElem_t* GetFoP( Token* ArrTok, int* i )
{
	IS_NULL( ArrTok ); IS_NULL( i );
	
	TreeElem_t* res = New_type( ArrTok[*i].data, ArrTok[*i].type, NULL, NULL );
	IS_NULL( res );
	res->str = ArrTok[*i].str;
	(*i)++;
	TreeElem_t* resarg = GetOpAB( ArrTok, i );
	IS_NULL( resarg );
	res->left = resarg ;
	resarg->parent = res ;
	
	return res;
}

TreeElem_t* GetBr( Token* ArrTok, int* i )
{
	IS_NULL( ArrTok ); IS_NULL( i );
	TreeElem_t* res = NULL;
	
	if ( ArrTok[*i].type == leftbrac )
	{
		//printf( "Я GetBr,  Получил (\n" );
		(*i)++;
		res = GetOpAB( ArrTok, i );
		IS_NULL( res );
		//printf( "Я GetBr,  Получил OpSA\n" );
		if( ArrTok[*i].type != rightbrac )
			return NULL;
		(*i)++;
		//printf( "Я GetBr,  Получил )\n" );
	}
	else if ( ArrTok[*i].type == function && ( ArrTok[*i].data == sinus || ArrTok[*i].data == cosinus ) )
		res = GetFoP( ArrTok, i );
	else
	{
		//printf( "Я GetBr,  Получил цифру или переменную\n" );
		
		res = GetN( ArrTok, i );
		IS_NULL( res );
		//(*i)++;
		//printf( "Я GetBr,  Получил N\n" );
	}
	
	IS_NULL( res );
	
	return res;
}

TreeElem_t* GetPow( Token* ArrTok, int* i )
{
	IS_NULL( ArrTok ); IS_NULL( i );
	
	//printf( "Я GetOpmPow, запускаю GetBr\n");
	TreeElem_t* res = GetBr( ArrTok, i );
	IS_NULL( res );
	//printf( "Я GetOpmMD, получил Br\n");
	while( ArrTok[*i].type == oper &&
		( ( char ) ArrTok[*i].data == '^') )
		{
			res = New_type( ArrTok[*i].data, oper, res, NULL );
			//printf( "Я GetOpmMD, добавил Br\n");
			IS_NULL( res );
			(*i)++;
			
			res->right = GetBr( ArrTok, i );
			IS_NULL( res->right );
			res->right->parent = res;
			//printf( "Я GetOpmMD, получил Br\n");
		}
		
	//printf( "Я GetOpmMD, Возвращаю res\n");
	IS_NULL( res );
	return res;
}
// презентация дани байгушеве ded32.ru
//стек для переменных ( таблица имен )
//страу струп 2е издание 85-87 год ~300 стр
//Брюс эйкел философия с++ 
TreeElem_t* GetAssig( Token* ArrTok, int* i )
{
	IS_NULL( ArrTok ); IS_NULL( i );
	
	TreeElem_t* res = GetN( ArrTok, i );
	IS_NULL( res );
	//printf( "Я GetAssig,  Получил N\n" );
	if ( ArrTok[*i].data != '=' ||  ArrTok[*i].type != oper )
	{
		printf( "Where is the assignment? Error at: %s", ArrTok[*i].str );
		return NULL;
	}
	
	res = New_type( ArrTok[*i].data, ArrTok[*i].type, res, NULL );
	IS_NULL( res );
	(*i)++;
	//printf( "Я GetAssig,  Получил =\n" );
	if ( ArrTok[*i].type == myfunc )
		res->right = GetFoo( ArrTok, i );
	else
		res->right = GetOpAB( ArrTok, i );
	
	IS_NULL( res->right );
	res->right->parent = res;
	//res->str = ";";
	//TreeElem_dump( res );
	//printf( "Я GetAssig,  Получил N справа\n" );
	
	return res;
}



TreeElem_t* GetFun( Token* ArrTok, int* i )
{
	IS_NULL( ArrTok ); IS_NULL( i );
	
	TreeElem_t* res = NULL;
	TreeElem_t* res_r = NULL;
	//printf( "%d %s\n", *i, ArrTok[*i].str );
	
	#define  DEF_CMD( ttype, word, num, name ) \
	if ( ttype == function && ArrTok[*i].type == ttype \
		&& ArrTok[*i].data == num ) \
	{ \
		res = New_type( ArrTok[*i].data, ArrTok[*i].type, NULL, NULL ); \
		IS_NULL( res ); \
		res->str = ArrTok[*i].str; \
		(*i)++; \
		res_r = GetOpAB( ArrTok, i ); \
		IS_NULL( res_r ); \
		res->left = res_r; \
		res_r->parent = res; \
	} \
	else
		
	#include "KeyWords.h"
		res = NULL;
	
	#undef DEF_CMD
	
	IS_NULL( res );
	
	return res;
}


TreeElem_t* GetIfWh( Token* ArrTok, int* i )
{
	IS_NULL( ArrTok ); IS_NULL( i );
	
	TreeElem_t* res = New_type( ArrTok[*i].data, ArrTok[*i].type, NULL, NULL );
	IS_NULL( res );
	res->str = ArrTok[*i].str;
	(*i)++;
	res->left = GetOpAB( ArrTok, i );
	IS_NULL( res->left );
	res->left->parent = res;
	if ( res->t == ifel )
	{
		TreeElem_t* res_T = GetPiec( ArrTok, i );
		IS_NULL( res_T );
		res_T->parent = res;
		if ( ArrTok[*i].type != ifel )
		{
			printf( "Where fi ???\n" );
			return NULL;
			
		}
	
		res->right = New_type( ArrTok[*i].data, ArrTok[*i].type, NULL, NULL );
		IS_NULL( res->right );
		res->right->parent = res;
		res->right->str = ArrTok[*i].str;
		(*i)++;
		
		res->right->left = res_T;
		res_T->parent = res->right;
		
		res->right->right = GetPiec( ArrTok, i );
		IS_NULL( res->right->right );
		res->right->right->parent = res->right;
	}
	else 
	{
		res->right = GetPiec( ArrTok, i );
		IS_NULL( res->right );
		res->right->parent = res;
	}
	TreeElem_t* res_parent = New_type( (Tree_Type)';', separ, res, NULL );
	IS_NULL( res_parent );
	res->parent = res_parent;
	res_parent->str = ";";
	
	return res_parent ;
	
}

TreeElem_t* Find_in_arr_of_functions( const char* f)
{
	IS_NULL( f );
	//fprintf( stderr, "%s", arr_of_functions[0]->str );
	for ( int i = 0;  arr_of_functions[i] != NULL; i++ )
	{
		
		if ( !strcmp( f, arr_of_functions[i]->str ) )
			return arr_of_functions[i];
			
	}
	
	return NULL;
}

TreeElem_t* GetAdFoo( Token* ArrTok, int* i )
{
	IS_NULL( ArrTok ); IS_NULL( i );
	
	//(*i)++;
	
	TreeElem_t* res = New_type( ArrTok[*i].data, ArrTok[*i].type, NULL, NULL );
	IS_NULL( res );
	res->str = ArrTok[*i].str;
	
	(*i)++;
	
	res->left = New_type( ArrTok[*i].data, ArrTok[*i].type, NULL, NULL );
	IS_NULL( res->left );
	res->left->str = ArrTok[*i].str;
	res->left->parent = res;
	TreeElem_t* res_left = res->left;
	
	(*i)++;
	
	while( ArrTok[*i].type != rightbrac )
	{
		TreeElem_t* restmp = GetN( ArrTok, i );
		//Token_dump( &ArrTok[*i], 1 );
		IS_NULL( restmp );
		res_left->left = restmp;
		restmp->parent = res_left;
		res_left = res_left->left;
		//(*i)++;
	}
	(*i)++;
	arr_of_functions[arr_of_functions_cntr++] = res->left;
	IS_NULL( res->left );
	res->right = GetPiec( ArrTok, i );
	IS_NULL( res->right );
	res->right->parent = res;
	
	//TreeElem_dump( res->left );
	
	TreeElem_t* res_parent = New_type( (Tree_Type)';', separ, res, NULL );
	IS_NULL( res_parent );
	res->parent = res_parent;
	res_parent->str = ";";
	
	return res_parent;
	
}

TreeElem_t* GetFoo( Token* ArrTok, int* i )
{
	IS_NULL( ArrTok ); IS_NULL( i );
	
	TreeElem_t* res = New_type( ArrTok[*i].data, ArrTok[*i].type, NULL, NULL );
	IS_NULL( res );
	res->str = ArrTok[*i].str;
	res->parent = res;
	TreeElem_t* res_left = res;
	(*i)++;
	//printf( " %s\n", res->str );
	
	res->right =  Find_in_arr_of_functions( res->str )->left ;
	
	IS_NULL( res->right );
	//TreeElem_dump( res->right );
	
	while( ArrTok[*i].type != rightbrac )
	{
		TreeElem_t* restmp = GetN( ArrTok, i );
		//Token_dump( &ArrTok[*i], 1 );
		IS_NULL( restmp );
		res_left->left = restmp;
		restmp->parent = res_left;
		res_left = res_left->left;
		//(*i)++;
	}
	(*i)++;
	

	return res;
}

TreeElem_t* GetPiec( Token* ArrTok, int* i )
{
	IS_NULL( ArrTok ); IS_NULL( i );
	TreeElem_t* res = NULL;
	if ( ArrTok[*i].type == begin )
	{
		(*i)++;
		res = GetStr( ArrTok, i );
		IS_NULL( res );
	}
	else 
		return NULL;

	
	TreeElem_t* res_parent = res;
	TreeElem_t* res_left = NULL;
	while ( ArrTok[*i].type != end )
	{
		
		res_left = GetStr( ArrTok, i );
		
		IS_NULL( res_left );
		res_left->parent = res_parent;
		res_parent->right = res_left;
		res_parent = res_left;
		
	}
	
	if ( ArrTok[*i].type != end )
		return NULL;
	(*i)++;
	
	res_parent = New_type( (Tree_Type)';', separ, res, NULL );
	IS_NULL( res_parent );
	res->parent = res_parent;
	res_parent->str = ";";
	
	return res_parent;
}


TreeElem_t* GetStr( Token* ArrTok, int* i )
{
	IS_NULL( ArrTok ); IS_NULL( i );
	TreeElem_t* res = NULL;
	
	if ( ArrTok[*i].type == val && ArrTok[*i+1].type == oper && ArrTok[*i+1].data == '=' )
		res = GetAssig( ArrTok, i );
	else if ( ArrTok[*i].type == function )
		res = GetFun( ArrTok, i );
	else if ( ArrTok[*i].type == begin )
		return GetPiec( ArrTok, i );
	else if ( ArrTok[*i].type == ifel || ArrTok[*i].type == cycle )
		return GetIfWh( ArrTok, i );
	else if ( ArrTok[*i].type == separ )
	{
		res = New_type( ArrTok[*i].data, ArrTok[*i].type, NULL, NULL );
		IS_NULL( res );
		(*i)++;
		return res;
	}
	else if ( ArrTok[*i].type == admyfunc )
		return GetAdFoo( ArrTok, i );
	else if ( ArrTok[*i].type == myfunc )
		res = GetFoo( ArrTok, i );
	else 
		res = GetOpAB( ArrTok, i );
	IS_NULL( res );
	
	res = New_type( (double ) ';' , separ , res, NULL );
	if ( ArrTok[*i].type != separ )
		return NULL;
	IS_NULL( res );
	(*i)++;
	//Token_dump( &ArrTok[*i], 1 );
	//TreeElem_dump( res );
	
	return res;
}
