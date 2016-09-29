#ifndef SUBCKT_H
#define SUBCKT_H

#include "stamp.h"
#include "cap.h"
#include "res.h"
#include "isrc.h"
#include "vsrc.h"
#include "mut.h"
#include "ind.h"
#include "util.h"
#include "device.h"
#include <vector>
#include <string>
using namespace std; 

class Subckt
{
public:
	Subckt() {
	}
	void addpin(string pinname);
	void setName(string name);
	void setXName(string Xname);
	string getName();
	//void printinfo();
	friend class Stamp;

private:
	vector<string> pinlist;
	string Xname;
	string name;
	vector<Device*> _devlist;
	vector<string> _line;
};

#endif
