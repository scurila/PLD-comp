#include "SymbolTable.h"
#include "Exceptions.h"
#include "Utils.h"

using namespace std;

bool SymbolTable::addEntry(string name, string type) {
	int size = typeSize(type);

    if (table.find(name) == table.end()) {
		// on crée la var°
		if(topOffset % size != 0) {
			topOffset += size - (topOffset % size);
		}

		table.insert(make_pair(name, new Entry(name, type, topOffset, size)));
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
