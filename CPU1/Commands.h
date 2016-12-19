

DEF_CMD( PUSH,  10,  2 ) // положить в стек
DEF_CMD( PUSHR, 11,  2 ) // положить в регистр
DEF_CMD( POPR,  12,  2 ) // достать из регистра в стек
DEF_CMD( JMP,   13,  2 ) // переход
DEF_CMD( JE,    14,  2 ) // ==
DEF_CMD( JNE,   15,  2 ) // !=
DEF_CMD( JA,    16,  2 ) // >
DEF_CMD( JB,    17,  2 ) // <
DEF_CMD( JAE,   18,  2 ) // >=
DEF_CMD( JBE,   19,  2 ) // <=
DEF_CMD( CALL,  20,  2 ) // вызов функции4

DEF_CMD( POP,   100, 1 ) // достать из стека
DEF_CMD( ADD,   101, 1 ) // сложить 2 посл числа стека
DEF_CMD( SUB,   102, 1 ) // вычесть 2 посл числа стека
DEF_CMD( MUL,   103, 1 ) // умножить 2 посл числа стека
DEF_CMD( DIV,   104, 1 ) // поделить
DEF_CMD( IN,    105, 1 ) // ввод с консоли
DEF_CMD( OUT,   106, 1 ) // вывод 
DEF_CMD( NOP,   107, 1 ) // пропустить действие
DEF_CMD( SQRT,  108, 1 ) // корень из

DEF_CMD( SIN,   109, 1 ) // sin
DEF_CMD( COS,   110, 1 ) // cos
DEF_CMD( RET,   111, 1 ) // возврат в точку вызова
DEF_CMD( END,   112, 1 ) // конец
DEF_CMD( E,     113, 1 )
DEF_CMD( POW,   114, 1 )

DEF_CMD( A,     115, 1 )
DEF_CMD( B,     116, 1 )
DEF_CMD( AE,    117, 1 )
DEF_CMD( BE,    118, 1 )
DEF_CMD( NE,    119, 1 )