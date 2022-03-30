grammar ifcc;

axiom : prog ;

prog : 'int' 'main' '(' ')' '{' instrlist ;

instrlist: ( instr ';' instrlist ) 
     | '}' | (';'instrlist ) ;

instr: RETURN expr   # ReturnExpr
     | type LITERAL '('')' #CallFuncNoArgs
     | type LITERAL '(' expr (',' expr)* ')' #CallFuncArgs
     | type LITERAL '=' CONST (',' LITERAL '=' CONST)* # InitVarConst
     | type LITERAL (',' LITERAL)*  # DeclareVar
     | LITERAL '=' LITERAL # AssignVar
     | LITERAL '=' CONST   # AssignConst
     | LITERAL '=' expr # AssignExpr
     ;

expr: '(' expr ')' # OperatorPar
     | expr ( '*' | '/' | '%') expr # OperatorMultDivMod
     | expr ( '+' | '-' ) expr # OperatorAddSub
     | expr ( '==' | '<' | '<=' | '>' | '>=' | '!=' ) expr # OperatorCmp
     | expr ( '&' | '|' ) expr # OperatorBinary
     | ( '-' | '!' ) expr # OperatorUnaryPrefix
     | CONST # ConstExpr
     | LITERAL # LiteralExpr
     | CHAR # CharExpr
;

/* literallist: LITERAL ',' literallist | LITERAL ; */

type : 'char' | 'int' | 'void';

RETURN : 'return' ;

CONST : [0-9]+ ;
LITERAL: [a-zA-Z]+ ;
CHAR: '\'' .? '\'' ;

ML_COMMENT : '/*' .*? '*/' -> skip ;
SL_COMMENT : '//' .*? '\n' -> skip ;
DOC_COMMENT : '/**' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN) ;

