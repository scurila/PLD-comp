grammar ifcc;

axiom : prog ;

prog : 'int' 'main' '(' ')' '{' instrlist ;

instrlist: ( instr ';' instrlist ) 
     | '}' ;

instr: RETURN CONST   # ReturnConst
     | type LITERAL '=' CONST  # InitVarCte
     ;

type : 'char' | 'int' ;


RETURN : 'return' ;

CONST : [0-9]+ ;
LITERAL: [a-zA-Z]+ ;

COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);

