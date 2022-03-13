#include "SymbolTable.h"
#include "Exceptions.h"

bool SymbolTable::addEntry(string name, string type) {
	int size = 4;
	// todo : tailles selon type
	/*for (int i = 0; i < sizeof(VarTypeName)/sizeof(VarTypeName[0]) ; i++) { 
		if (type == VarTypeName[i]) {
			size = VarTypeSize[i];
		}
	}*/
    if (table.find(name) == table.end()) {
		// on crée la var°
		table.insert(make_pair(name, new Entry(name, type, topOffset + size, size)));
        topOffset += size;
        return true; 
	} else {
		// la var° a déjà été déclarée dans ce scope
		throw DeclaredVarException(name);
        return false;
	}
}

Entry* SymbolTable::get(string name) {
	if (table.find(name) == table.end()) {
		// !!! var utilisée sans être déclarée
		throw UndeclaredVarException(name);
		return NULL;
	} else {
		return table[name];
	}
}
