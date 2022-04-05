grammar ifcc;

axiom : (main | function)* ;

main: 'int' 'main' '(' ')' instrblock ;

function: type LITERAL '(' (type LITERAL (',' type LITERAL)* )? ')' instrblock # DeclareFunc ;

instrblock: '{' instrlist* '}' ;

instrlist:  ( instr ';' | cflow_block | instrblock ) (instrlist)* ;

cflow_block:  
     'if' '(' expr ')' instrblock ('else if' '(' expr ')' instrblock)* ('else' instrblock )? # IfElseIfElse
     | 'while' '(' expr ')' instrblock  # WhileLoop
     ;

instr: RETURN expr   # ReturnExpr
     | RETURN  # ReturnVoid
     | type LITERAL '=' CONST (',' LITERAL '=' CONST)* # InitVarConst
     | type LITERAL '=' expr (',' LITERAL '=' expr)* # InitVarExpr
     | type LITERAL (',' LITERAL)*  # DeclareVar
     | LITERAL '=' LITERAL # AssignVar
     | LITERAL '=' CONST   # AssignConst
     | LITERAL '=' expr # AssignExpr
     | expr # ExprAlone
     |  # Nop
     ;

expr: '(' expr ')' # OperatorPar
     | LITERAL ('++'| '--') #OperatorUnaryPostfix
     | expr ( '*' | '/' | '%') expr # OperatorMultDivMod
     | expr ( '+' | '-' ) expr # OperatorAddSub
     | expr ( '==' | '<' | '<=' | '>' | '>=' | '!=' ) expr # OperatorCmp
     | expr ( '&' | '|' ) expr # OperatorBinary
     | ( '-' | '!' ) expr # OperatorUnaryPrefix
     | LITERAL '('')' #CallFuncNoArgs
     | LITERAL '(' expr (',' expr)* ')' #CallFuncArgs
     | CONST # ConstExpr
     | LITERAL # LiteralExpr
     | CHAR # CharExpr
;

/* literallist: LITERAL ',' literallist | LITERAL ; */

type : 'char' | 'int' | 'void';

RETURN : 'return' ;

CONST : [0-9]+ ;
LITERAL: [a-zA-Z0-9_]+ ;
CHAR: '\'' .? '\'' ;

ML_COMMENT : '/*' .*? '*/' -> skip ;
SL_COMMENT : '//' .*? '\n' -> skip ;
DOC_COMMENT : '/**' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN) ;

