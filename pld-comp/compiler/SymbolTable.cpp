#include "SymbolTable.h"
#include "Exceptions.h"
#include "Utils.h"

#include <algorithm>

using namespace std;

bool SymbolTable::addEntry(string name, string type) {
	int size = typeSize(type);
	auto innerScope = table.back();

    if (innerScope->find(name) == innerScope->end()) { // only need to check inner scope (for shadowing)
		// on crée la var°
		if(topOffset % size != 0) {
			topOffset += size - (topOffset % size);
		}

		innerScope->insert(make_pair(name, new Entry(name, type, topOffset, size)));
		topOffset += size;
        return true; 
	} else {
		// la var° a déjà été déclarée dans cette scope
		throw DeclaredVarException(name);
        return false;
	}
}

Entry* SymbolTable::get(string name) {
	return get(name, table.size() - 1);
}

Entry* SymbolTable::get(string name, int layer) {
	if(layer == -1) {  // TODO will need to check global variables before
		throw new UndeclaredVarException(name);
		return nullptr;
	}

	if(table[layer]->find(name) == table[layer]->end()) {  
		// variable does not exist in this scope. try to look it up in the parent scope
		return get(name, layer - 1);
	}
	else { // variable found in this scope (may shadow a variable from parent scopes)
		table[layer]->at(name)->used = true; // enable 'used' flag
		return table[layer]->at(name); 
	}
}

vector<string> SymbolTable::unusedVars() {
	unordered_set<string> res = unordered_set<string>(unusedVarNames);

	std::for_each(table.begin(), table.end(), [&res](auto scope) {
		std::for_each(scope->begin(), scope->end(), [&res](auto keyValue) {
			Entry* entry = keyValue.second;
			if (!entry->used) {
				res.insert(entry->name);
			}
		});
	});
/*
	for(auto &scopeIt : table) {
		for(auto &entryIt : scopeIt) {
			Entry* entry = entryIt->second;
			if (!entry->used) {
				res.insert(entry->name);
			}
		}
	}*/

	return vector<string>(res.begin(), res.end());
}


void SymbolTable::push_context() {
	table.push_back(new unordered_map<string, Entry*>());
}

void SymbolTable::pop_context() {

	auto innerScope = table[table.size() - 1];
	for(auto it = innerScope->begin(); it != innerScope->end(); ++it) {
		Entry* entry = it->second;
		if (!entry->used) {
			unusedVarNames.insert(entry->name);
		}
	}

	delete table.back();
	table.pop_back();
}
