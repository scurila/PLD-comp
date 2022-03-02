grammar ifcc;

axiom : prog ;

prog : 'int' 'main' '(' ')' '{' instrlist ;

instrlist: ( instr ';' instrlist ) | '}' ;

instr: RETURN CONST   # ReturnConst
     | TYPE LITERAL  # DeclareVar
     ;

RETURN : 'return' ;
TYPE : 'char' | 'int' ;
CONST : [0-9]+ ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
LITERAL: [a-zA-Z]+ ;
