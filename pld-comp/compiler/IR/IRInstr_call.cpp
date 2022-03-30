// arguments sur la pile : max 5 
// gérer proprement le nombre d'arguments des fonctions 


#include "IRInstr_call.h"

void IRInstr_call::gen_x86(ostream &o) {//https://www.cs.uaf.edu/2015/fall/cs301/lecture/09_14_call.html
    int nb = nbparam;
    o << "# call\n";
    /*for(int i=0; i<nbparam; i++){

    }*/

}
    //abi linux/apple : (... for integer parameters) the next available register of the sequence %rdi, %rsi, %rdx, %rcx, %r8 and %r9 is used.

void IRInstr_call::gen_arm(ostream &o) {
    
}
