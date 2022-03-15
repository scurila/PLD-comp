#include "SymbolTable.h"
#include "Exceptions.h"

using namespace std;

bool SymbolTable::addEntry(string name, string type) {
	int size = 4;
	for (int i = 0; i < sizeof(VarTypeName)/sizeof(VarTypeName[0]) ; i++) { 
		if (type == VarTypeName[i]) {
			size = VarTypeSize[i];
		}
	}
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
		table[name]->used = true; // activate used flag
		return table[name];
	}
}

vector<string> SymbolTable::unusedVars() {
	vector<string> res;
	for(unordered_map<string, Entry*>::iterator it=table.begin(); it!=table.end(); ++it) {
		Entry* entry = it->second;
		if (!entry->used) {
			res.push_back(entry->name);
		}
	}
	return res;
}
