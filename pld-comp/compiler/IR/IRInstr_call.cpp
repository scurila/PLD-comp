#include "IRInstr_call.h"

void IRInstr_call::gen_x86(ostream &o) {
    string abi  [6] =  {"%rdi","%rsi", "%rdx", "%rcx", "%r8", "%r9"};
    o << "# call\n";
   
    for(int i=0; i<nbParams && i<6; i++){
        o   << "  popq %rbx\n"
            << "  mov %rbx, "+abi[i]+"\n";
    }
    //TODO : gérer proprement si trop de paramètres !
    #ifdef APPLE
        o   << "  callq _"+functionName+"\n";
    #else
    	o   << "  callq "+functionName+"\n";
    #endif

    o   << "  pushq %rax\n";

}
    //abi linux/apple : (... for integer parameters) the next available register of the sequence %rdi, %rsi, %rdx, %rcx, %r8 and %r9 is used.
    ////https://www.cs.uaf.edu/2015/fall/cs301/lecture/09_14_call.html

void IRInstr_call::gen_arm(ostream &o) {
    
}
