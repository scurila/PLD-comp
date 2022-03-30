grammar ifcc;

axiom : prog ;

prog : 'int' 'main' '(' ')' instrblock ;

instrblock: '{' instrlist '}' ;

instrlist:  ( instr ';' | cf_struct ) (instrlist)* ;

cf_struct:  
     'if' '(' expr ')' instrblock ('else if' '(' expr ')' instrblock)* ('else' instrblock )? # IfElse
     ;

instr: RETURN expr   # ReturnExpr
     | type LITERAL '=' CONST (',' LITERAL '=' CONST)* # InitVarConst
     | type LITERAL (',' LITERAL)*  # DeclareVar
     | LITERAL '=' LITERAL # AssignVar
     | LITERAL '=' CONST   # AssignConst
     | LITERAL '=' expr # AssignExpr
     |  # Nop
     ;

expr: '(' expr ')' # OperatorPar
     | expr ( '*' | '/' ) expr # OperatorMultDiv
     | expr ( '+' | '-' ) expr # OperatorAddSub
     | expr ( '==' | '<' | '<=' | '>' | '>=' | '!=') expr # OperatorCmp
     | expr ( '&' | '|' ) expr # OperatorBinary
     | ( '-' | '!' ) expr # OperatorUnaryPrefix
     | CONST # ConstExpr
     | LITERAL # LiteralExpr
;

/* literallist: LITERAL ',' literallist | LITERAL ; */

type : 'char' | 'int' ;

RETURN : 'return' ;

CONST : [0-9]+ ;
LITERAL: [a-zA-Z]+ ;

ML_COMMENT : '/*' .*? '*/' -> skip ;
SL_COMMENT : '//' .*? '\n' -> skip ;
DOC_COMMENT : '/**' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN) ;

