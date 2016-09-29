#include "subckt.h"

#include <vector>
#include <string>

using namespace std;

void Subckt::addpin(string pinname) {
	pinlist.push_back(pinname);
}

void Subckt::setName(string name) {
	this->name = name;
}

void Subckt::setXName(string Xname) {
	this->Xname = Xname;
}

string Subckt::getName() {
	return name;
}