#include <exception>
#include <string>
#include <string>
#include <iostream>

using namespace std;

inline void errorMessage(string msg) {
    cerr << "\033[1;31m" << msg << "\033[0m" << endl;
}

class DeclaredVarException : public exception {
    public:
        DeclaredVarException(string vN): varName(vN.c_str()) {}
        const string varName; 
    
        const string message () const throw () {
            return "La variable de nom " + varName + " a déjà été déclarée dans ce contexte.";
        }
};

class UndeclaredVarException : public exception {
    public:
        UndeclaredVarException(string vN): varName(vN.c_str()) {}
        const string varName; 
    
        const string message () const throw () {
            return "La variable de nom " + varName + " est utilisée sans avoir été déclarée.";
        }
};
