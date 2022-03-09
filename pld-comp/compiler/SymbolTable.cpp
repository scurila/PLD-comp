#include "SymbolTable.h"

bool SymbolTable::addEntry(string name, string type, int size) {
    if (table.find(name) == table.end()) {
		// on crée la var°
		table.insert(make_pair(name, new Entry(name, type, topOffset + size, size)));
        topOffset += size;
        return true; 
	} else {
		// la var° a déjà été déclarée dans ce scope
        return false;
	}
}

Entry* SymbolTable::get(string name) {
	return table[name];
}
