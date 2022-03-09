grammar ifcc;

axiom : prog ;

prog : 'int' 'main' '(' ')' '{' instrlist ;

instrlist: ( instr ';' instrlist ) 
     | '}' ;

instr: RETURN expr   # ReturnExpr
     | type LITERAL '=' CONST  # InitVarConst
     | type literallist  # DeclareVar
     | LITERAL '=' LITERAL # AssignVar
     | LITERAL '=' CONST   # AssignConst
     | LITERAL '=' expr # AssignExpr
     ;

expr:  expr '*' expr # OperatorMult
     | expr '/' expr # OperatorDiv
     | expr '+' expr # OperatorAdd
     | expr '-' expr # OperatorSub
     | CONST # ConstExpr
     | LITERAL # LiteralExpr
     | '(' expr ')' # OperatorPar
;

literallist: LITERAL ',' literallist | LITERAL ;

type : 'char' | 'int' ;

RETURN : 'return' ;

CONST : [0-9]+ ;
LITERAL: [a-zA-Z]+ ;

COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);

