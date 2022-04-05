#include <exception>
#include <string>
#include <string>
#include <iostream>

using namespace std;

inline void errorMessage(string msg) {
    cerr << "\033[1;31m [E]: " << msg << "\033[0m" << endl;
}

inline void warningMessage(string msg) {
    cerr << "\033[1;33m [W]: " << msg << "\033[0m" << endl;
}

class ifccException : public exception {
public:
    ifccException() {}

    virtual const string message() const throw () = 0;
};

class DeclaredVarException : public ifccException {
    public:
        DeclaredVarException(string vN): varName(vN.c_str()) {}
        const string varName; 
    
        const string message () const throw () {
            return "La variable de nom " + varName + " a déjà été déclarée dans ce contexte.";
        }
};

class UndeclaredVarException : public ifccException {
    public:
        UndeclaredVarException(string vN): varName(vN.c_str()) {}
        const string varName; 
    
        const string message () const throw () {
            return "La variable de nom " + varName + " est utilisée sans avoir été déclarée.";
        }
};

class UndeclaredNameException : public ifccException {
    public:
        UndeclaredNameException(string name): name(name.c_str()) {}
        const string name; 
    
        const string message () const throw () {
            return "Name '" + name + "' was not defined in this scope.";
        }
};

class NameAlreadyDefinedException : public ifccException {
    public:
        NameAlreadyDefinedException(string name): name(name.c_str()) {}
        const string name; 
    
        const string message () const throw () {
            return "Name '" + name + "' was already defined in this scope.";
        }
};

class TooManyParametersException : public ifccException {
    public:
        TooManyParametersException(string fname): fname(fname.c_str()) {}
        const string fname; 
    
        const string message () const throw () {
            return "Function '" + fname + "' has more than 6 parameters. This is currently not supported by this compiler.";
        }
};
