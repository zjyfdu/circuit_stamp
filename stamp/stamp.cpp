///
/// @file   stamp.cpp
/// @author Yinghai
/// @date   Fri Sep 12 13:05:24 2008
/// 
/// @brief  Implementation of the Stamp class
/// 
/// 
///



#include "stamp.h"
#include "cap.h"
#include "res.h"
#include "isrc.h"
#include "vsrc.h"
#include "mut.h"
#include "ind.h"
#include "util.h"
#include "subckt.h"
#include <math.h>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

using std::ifstream;
using std::ofstream;
using std::endl;
using std::getline;
using std::map;

//NO_SAFESEH = 1;

/// \brief Initialize the system matrix and carry out the stamping
///
/// This function is most important one because it setups up the liear system
/// \f[
/// \left\{\begin{array}{ccc}
///   y &=& L^T x \end{array}\right.
/// \f]
/// and fills in the elements in the system matrices. 
/// 
/// The matrix class \e Matrix needs to be designed by you.
/// Sparse matrix structure is preferred than the dense one since
/// the matrix will be very large while most of its elemets would be zero. 
/// 
/// In the skeleton program, the devices are enumerated and
/// they contributes to the system matrices by calling thier own stamping function.
/// 
/// \todo 
/// = Some devices such as mutual inductance depends on other devices. You need to 
///  take care of this situation. 
/// - We also have to enumerate the probe list to build the
/// \f$ L^T \f$ matrix. 
/// - SPICE file support multi-line command with a \e '+' at the beginning of the line.
/// Please consider how to support this. 
/// 
void Stamp::setup(){
  int n = static_cast<int>(_node_list.size()) - 1;
  _C = new Matrix(n,n);
  _G = new Matrix(n,n);
  _B = new Matrix(n, _num_in);
  _LT = new Matrix(_num_out, n);
  
  for(size_t i=0; i < _dev_list.size(); ++i)
  {
    _dev_list[i]->stamp(*_C, *_G, *_B);
  }
}

void Stamp::sub_setup()
{
	vector<string>::iterator iter = _subcktname.begin();
    string node_name;

	for (; iter != _subcktname.end(); iter++)
	{
        node_name=_subcktX[(*iter)].getName();
		map<string, string> nodemap;
		//string _subckt_name = _subckt[(*iter)].getName();
		//把.x和.subckt的pinlist用map关联起来 
        for (int i = 0; i < _subckt[node_name].pinlist.size(); i++)
		{
            nodemap[_subckt[node_name].pinlist[i]] = _subcktX[(*iter)].pinlist[i];
		}
        vector<string>::iterator iter1 = _subckt[node_name]._line.begin();
		string sub_line, sub_tmp, delims;
        delims=" \n\r()\t";
		_node_list["0"] = 0;
        int k = _node_list.size()-1;
        for (; iter1 != _subckt[node_name]._line.end(); ++iter1)
		{
            sub_line =(*iter1);
			if (sub_line[0] == 'R')
			{
				sub_tmp = tokenizer(sub_line, delims);
				sub_tmp = (*iter) + ":" + sub_tmp;
				Resistor* r = new Resistor(sub_tmp);

				// pnode
				sub_tmp = tokenizer(sub_line, delims);
                if (nodemap.find(sub_tmp) != nodemap.end())
					sub_tmp = nodemap[sub_tmp];
				else if (sub_tmp != "0")
					sub_tmp = (*iter) + ":" + sub_tmp;
				if (_node_list.find(sub_tmp) == _node_list.end())
				{
					_node_list[sub_tmp] = ++k;
				}
				r->setPnode(_node_list[sub_tmp]);

				// nnode
				sub_tmp = tokenizer(sub_line, delims);
                if (nodemap.find(sub_tmp) != nodemap.end())
					sub_tmp = nodemap[sub_tmp];
				else if (sub_tmp != "0")
					sub_tmp = (*iter) + ":" + sub_tmp;
				if (_node_list.find(sub_tmp) == _node_list.end())
				{
					_node_list[sub_tmp] = ++k;
				}
				r->setNnode(_node_list[sub_tmp]);

				// value
				sub_tmp = tokenizer(sub_line, delims);
				r->setValue(to_double(sub_tmp));

				// add to device list
				_dev_list.push_back(r);
			}
			else if (sub_line[0] == 'C')
			{
				sub_tmp = tokenizer(sub_line, delims);
				sub_tmp = (*iter) + ":" + sub_tmp;
				Capacitor* r = new Capacitor(sub_tmp);

				// pnode
				sub_tmp = tokenizer(sub_line, delims);
                if (nodemap.find(sub_tmp) != nodemap.end())
					sub_tmp = nodemap[sub_tmp];
				else if (sub_tmp != "0")
					sub_tmp = (*iter) + ":" + sub_tmp;
				if (_node_list.find(sub_tmp) == _node_list.end())
				{
					_node_list[sub_tmp] = ++k;
				}
				r->setPnode(_node_list[sub_tmp]);

				// nnode
				sub_tmp = tokenizer(sub_line, delims);
                if (nodemap.find(sub_tmp) != nodemap.end())
					sub_tmp = nodemap[sub_tmp];
				else if (sub_tmp != "0")
					sub_tmp = (*iter) + ":" + sub_tmp;
				if (_node_list.find(sub_tmp) == _node_list.end())
				{
					_node_list[sub_tmp] = ++k;
				}
				r->setNnode(_node_list[sub_tmp]);

				// value
				sub_tmp = tokenizer(sub_line, delims);
				r->setValue(to_double(sub_tmp));

				// add to device list
				_dev_list.push_back(r);
			}
			////////////////////////////////////////////////////////////////////////
			else if (sub_line[0] == 'I') {
				// name
				sub_tmp = tokenizer(sub_line, delims);
				sub_tmp = (*iter) + ":" + sub_tmp;
				_U.push_back(sub_tmp);
				Isrc* r = new Isrc(sub_tmp);

				// pnode
				sub_tmp = tokenizer(sub_line, delims);
                if (nodemap.find(sub_tmp) != nodemap.end())
					sub_tmp = nodemap[sub_tmp];
				else if (sub_tmp != "0")
					sub_tmp = (*iter) + ":" + sub_tmp;
				if (_node_list.find(sub_tmp) == _node_list.end())
				{
					_node_list[sub_tmp] = ++k;
				}
				r->setPnode(_node_list[sub_tmp]);

				// nnode
				sub_tmp = tokenizer(sub_line, delims);
                if (nodemap.find(sub_tmp) != nodemap.end())
					sub_tmp = nodemap[sub_tmp];
				else if (sub_tmp != "0")
					sub_tmp = (*iter) + ":" + sub_tmp;
				if (_node_list.find(sub_tmp) == _node_list.end())
				{
					_node_list[sub_tmp] = ++k;
				}
				r->setNnode(_node_list[sub_tmp]);

				// value
				sub_tmp = tokenizer(sub_line, delims);
				r->setValue(to_double(sub_tmp));

				// add to device list
				r->setInnum(_num_in);
				_dev_list.push_back(r);
				++_num_in;
			}

			/////////////////////////////////////////////////////////////////////////////////
			else if (sub_line[0] == 'V') {
				// name
				sub_tmp = tokenizer(sub_line, delims);
				sub_tmp = (*iter) + ":" + sub_tmp;
				_U.push_back(sub_tmp);
				Vsrc* r = new Vsrc(sub_tmp);

				// aux current
				sub_tmp = "i:" + (*iter) + ":" + sub_tmp;
				if (_node_list.find(sub_tmp) == _node_list.end())
				{
					_node_list[sub_tmp] = ++k;
				}
				r->setAux(_node_list[sub_tmp]);

				// pnode
				sub_tmp = tokenizer(sub_line, delims);
                if (nodemap.find(sub_tmp) != nodemap.end())
					sub_tmp = nodemap[sub_tmp];
				else if (sub_tmp != "0")
					sub_tmp = (*iter) + ":" + sub_tmp;
				if (_node_list.find(sub_tmp) == _node_list.end())
				{
					_node_list[sub_tmp] = ++k;
				}
				r->setPnode(_node_list[sub_tmp]);

				// nnode
				sub_tmp = tokenizer(sub_line, delims);
                if (nodemap.find(sub_tmp) != nodemap.end())
					sub_tmp = nodemap[sub_tmp];
				else if (sub_tmp != "0")
					sub_tmp = (*iter) + ":" + sub_tmp;
				if (_node_list.find(sub_tmp) == _node_list.end())
				{
					_node_list[sub_tmp] = ++k;
				}
				r->setNnode(_node_list[sub_tmp]);

				// value
				sub_tmp = tokenizer(sub_line, delims);
				r->setValue(to_double(sub_tmp));

				// add to device list
				r->setInnum(_num_in);
				_dev_list.push_back(r);
                ++_num_in;
			}

			///////////////////////////////////////////////////////////////
			else if (sub_line[0] == 'L') {
				// name
				sub_tmp = tokenizer(sub_line, delims);
				sub_tmp = (*iter) + ":" + sub_tmp;
				Inductor* r = new Inductor(sub_tmp);

				// aux current
                sub_tmp = "i:"  + sub_tmp;
				if (_node_list.find(sub_tmp) == _node_list.end())
				{
					_node_list[sub_tmp] = ++k;
				}
				r->setAux(_node_list[sub_tmp]);

				// pnode
				sub_tmp = tokenizer(sub_line, delims);
                if (nodemap.find(sub_tmp) != nodemap.end())
					sub_tmp = nodemap[sub_tmp];
				else if (sub_tmp != "0")
					sub_tmp = (*iter) + ":" + sub_tmp;
				if (_node_list.find(sub_tmp) == _node_list.end())
				{
					_node_list[sub_tmp] = ++k;
				}
				r->setPnode(_node_list[sub_tmp]);

				// nnode
				sub_tmp = tokenizer(sub_line, delims);
                if (nodemap.find(sub_tmp) != nodemap.end())
					sub_tmp = nodemap[sub_tmp];
				else if (sub_tmp != "0")
					sub_tmp = (*iter) + ":" + sub_tmp;
				if (_node_list.find(sub_tmp) == _node_list.end())
				{
					_node_list[sub_tmp] = ++k;
				}
				r->setNnode(_node_list[sub_tmp]);

				// value
				sub_tmp = tokenizer(sub_line, delims);
				r->setValue(to_double(sub_tmp));

				indValue.insert(pair<string, double>(r->name(), to_double(sub_tmp)));

				// add to device list
				_dev_list.push_back(r);
			}

			///////////////////////////////////////////////////////////////////
			else if (sub_line[0] == 'K') {
				// name
				sub_tmp = tokenizer(sub_line, delims);
				Mutual* r = new Mutual(sub_tmp);

				// pnode 
				sub_tmp = tokenizer(sub_line, delims);
                if (nodemap.find(sub_tmp) != nodemap.end())
					sub_tmp = nodemap[sub_tmp];
				else if (sub_tmp != "0")
					sub_tmp = (*iter) + ":" + sub_tmp;
				r->setInd1(sub_tmp);
				double _value1 = indValue[sub_tmp];
				//paux current
				sub_tmp = "i:" + sub_tmp;
				if (_node_list.find(sub_tmp) == _node_list.end())
				{
					_node_list[sub_tmp] = ++k;
				}
				r->setAuxPos(_node_list[sub_tmp]);

				// nnode
				sub_tmp = tokenizer(sub_line, delims);
                if (nodemap.find(sub_tmp) != nodemap.end())
					sub_tmp = nodemap[sub_tmp];
				else if (sub_tmp != "0")
					sub_tmp = (*iter) + ":" + sub_tmp;
				r->setInd2(sub_tmp);
				double _value2 = indValue[sub_tmp];
				//naux current
				sub_tmp = "i:" + sub_tmp;
				if (_node_list.find(sub_tmp) == _node_list.end())
				{
					_node_list[sub_tmp] = ++k;
				}
				r->setAuxNeg(_node_list[sub_tmp]);

				// value
				sub_tmp = tokenizer(sub_line, delims);
				r->setValue(sqrt(_value1*_value2)*to_double(sub_tmp));

				// add to device list
				_dev_list.push_back(r);
			}

		}


	}
}

/// \brief Output the system matrix to disk
///
/// @param filename output file name
///
/// This function will write the system matrix to the disk. 
/// Binary file format is preferred over the ASCII one. Sparse
/// matrix structure is preferred over the dense one. 
/// 
/// \todo Please fill in this function. 
void Stamp::output(char* filename)
{
  string outputfile=filename;
  outputfile+=".out";
  ofstream outstuf;
  outstuf.open(filename, ios::out);
  
  //output _C
  outstuf<<"** Matrix C (Size: "<<_C->row()<<" x "<<_C->column()<<") **" <<endl;
  outstuf<<(*_C)<<endl;
  
  //output _G
  outstuf<<"** Matrix G (Size: "<<_G->row()<<" x "<<_G->column()<<") **" <<endl;
  outstuf<<(*_G)<<endl;
  
  //output _B
  outstuf<<"** Matrix B (Size: "<<_B->row()<<" x "<<_B->column()<<") ** "<<endl;
  for(int i=0; i<_B->row(); i++)
  {
	  for(int j=0; j<_B->column(); j++)
		  if ((*_B)[i][j]!=0)
			  outstuf<<"(  "<<i+1<<",   "<<j+1<<")     "<<(*_B)[i][j]<<endl;
  }
  
  //output LT
  outstuf<<"** Matrix LT (Size: "<<_LT->row()<<" x "<<_LT->column()<<") ** "<<endl;
  for(int i=0; i<_probe_list.size(); i++)
      outstuf<<"(  "<<i+1<<",   "<<_probe_list[i]<<")     "<<1<<endl;

  //output vector X


  outstuf<<"** Vector X (Size: "<<_node_list.size()-1<<" x 1) **"<<endl;
  nodeList::iterator iter;

  for(int i=1; i<_node_list.size();i++)
  {
      iter=_node_list.begin();
      iter++;
     for(;iter != _node_list.end(); iter++){
         if((*iter).second==i){
         outstuf <<"   "<<(*iter).first;
         break;
         }
     }
  }

  outstuf <<endl;

  outstuf << "** Vector Y (Size: 1 x "<<_Y.size()<<") **"<<endl;
  for( int ii = 0; ii < _Y.size();ii++)
      outstuf << "   "<<_Y[ii];
  outstuf<<endl;

  outstuf << "** Vector U (Size: 1 x "<<_U.size()<<") **"<<endl;
  for (int ii = 0; ii < _U.size(); ii++)
      outstuf << "   " << _U[ii];
  outstuf <<endl;

  //output the binary file

  string filename1=filename;
  outputfile=filename1+"_C.bin";
  writeBinaryfile(outputfile.c_str(), *_C);
  outputfile=filename1+"_G.bin";
  writeBinaryfile(outputfile.c_str(), *_G);
  outputfile=filename1+"_LT.bin";
  writeBinaryfile(outputfile.c_str(), *_LT);
  outputfile=filename1+"_B.bin";
  writeBinaryfile(outputfile.c_str(), *_B);

}


/// \brief Parsing the SPICE netlist
///
/// @param filename SPICE filename
///
/// This is the first step of STAMP. It reads in the SPICE file and
/// extracts device and node information from it. The devices and nodes
/// are stored in \e _dev_list and \e _node_list for later usage. 
/// The parser reads in the SPICE netlist line by line. It breaks each line into
/// string tokens according to the delimiters, and then processes each token case by case.
/// Notice the using of \e tokenizer and \e captilizer. These two functions break the
/// line and convert them to upper case. (SPICE file are not case-sensitive)
///
/// \todo Currently, only limited devices cards for SPICE are considered. You can 
/// Further develop this fucntion to  accomodate more SPICE elements or cards such as 
/// subcircuit or controlled sources. 
void Stamp::parse(char* filename)
{
	ifstream ifid(filename);
	_num_in = 0;
	_num_out = 0;

	string line;
	string delims(" \n\r()\t");
	int k = 0;
	_node_list["0"] = 0;

	while (getline(ifid, line))
	{
        string tmp;
		capitalize(line);

		//////////////////RRRRRRRRRRRRRRRRRRRRRRRRRR///////////////////////////
		if (line[0] == 'R') {
			// name
			tmp = tokenizer(line, delims);
			Resistor* r = new Resistor(tmp);

			// pnode
			tmp = tokenizer(line, delims);
			if (_node_list.find(tmp) == _node_list.end())
			{
				_node_list[tmp] = ++k;
			}
			r->setPnode(_node_list[tmp]);

			// nnode
			tmp = tokenizer(line, delims);
			if (_node_list.find(tmp) == _node_list.end())
			{
				_node_list[tmp] = ++k;
			}
			r->setNnode(_node_list[tmp]);

			// value
			tmp = tokenizer(line, delims);
			r->setValue(to_double(tmp));

			// add to device list
			_dev_list.push_back(r);
		}

		//////////////////CCCCCCCCCCCCCCCCCCCCCCCCCCCCC///////////////////////////
		else if (line[0] == 'C') {
			// name
			tmp = tokenizer(line, delims);
			Capacitor* r = new Capacitor(tmp);

			// pnode
			tmp = tokenizer(line, delims);
			if (_node_list.find(tmp) == _node_list.end())
			{
				_node_list[tmp] = ++k;
			}
			r->setPnode(_node_list[tmp]);

			// nnode
			tmp = tokenizer(line, delims);
			if (_node_list.find(tmp) == _node_list.end())
			{
				_node_list[tmp] = ++k;
			}
			r->setNnode(_node_list[tmp]);

			// value
			tmp = tokenizer(line, delims);
			r->setValue(to_double(tmp));

			// add to device list
			_dev_list.push_back(r);
		}

		////////////////////IIIIIIIIIIIIIIIIIIII/////////////////////////////////////////////////
		else if (line[0] == 'I') {
			// name
			tmp = tokenizer(line, delims);
			_U.push_back(tmp);
			Isrc* r = new Isrc(tmp);

			// pnode
			tmp = tokenizer(line, delims);
			if (_node_list.find(tmp) == _node_list.end())
			{
				_node_list[tmp] = ++k;
			}
			r->setPnode(_node_list[tmp]);

			// nnode
			tmp = tokenizer(line, delims);
			if (_node_list.find(tmp) == _node_list.end())
			{
				_node_list[tmp] = ++k;
			}
			r->setNnode(_node_list[tmp]);

			// value
			tmp = tokenizer(line, delims);
			r->setValue(to_double(tmp));

			// add to device list
			r->setInnum(_num_in);
			_dev_list.push_back(r);
			++_num_in;
		}

		/////////////////////////////////////////////////////////////////////////////////
		else if (line[0] == 'V') {
			// name
			tmp = tokenizer(line, delims);
			_U.push_back(tmp);
			Vsrc* r = new Vsrc(tmp);

			// aux current
			tmp = "i:" + tmp;
			if (_node_list.find(tmp) == _node_list.end())
			{
				_node_list[tmp] = ++k;
			}
			r->setAux(_node_list[tmp]);
			// pnode
			tmp = tokenizer(line, delims);
			if (_node_list.find(tmp) == _node_list.end())
			{
				_node_list[tmp] = ++k;
			}
			r->setPnode(_node_list[tmp]);
			// nnode
			tmp = tokenizer(line, delims);
			if (_node_list.find(tmp) == _node_list.end())
			{
				_node_list[tmp] = ++k;
			}
			r->setNnode(_node_list[tmp]);
			// value
			tmp = tokenizer(line, delims);
			r->setValue(to_double(tmp));

				// add to device list
			r->setInnum(_num_in);
			_dev_list.push_back(r);
            ++_num_in;
		}

		///////////////////////////////////////////////////////////////
		else if (line[0] == 'L') {
			// name
			tmp = tokenizer(line, delims);
			Inductor* r = new Inductor(tmp);

			// aux current
			tmp = "i:" + tmp;
			if (_node_list.find(tmp) == _node_list.end())
			{
				_node_list[tmp] = ++k;
			}
			r->setAux(_node_list[tmp]);

			// pnode
			tmp = tokenizer(line, delims);
			if (_node_list.find(tmp) == _node_list.end())
			{
				_node_list[tmp] = ++k;
			}
			r->setPnode(_node_list[tmp]);

			// nnode
			tmp = tokenizer(line, delims);
			if (_node_list.find(tmp) == _node_list.end())
			{
				_node_list[tmp] = ++k;
			}
			r->setNnode(_node_list[tmp]);

			// value
			tmp = tokenizer(line, delims);
			r->setValue(to_double(tmp));

			indValue.insert(pair<string, double>(r->name(), to_double(tmp)));

			// add to device list
			_dev_list.push_back(r);
		}

		///////////////////////////////////////////////////////////////////
		else if (line[0] == 'K') {
			// name
			tmp = tokenizer(line, delims);
			Mutual* r = new Mutual(tmp);

			// pnode 
			tmp = tokenizer(line, delims);
			r->setInd1(tmp);
			double _value1 = indValue[tmp];
			//paux current
			tmp = "i:" + tmp;
			if (_node_list.find(tmp) == _node_list.end())
			{
				_node_list[tmp] = ++k;
			}
			r->setAuxPos(_node_list[tmp]);

			// nnode
			tmp = tokenizer(line, delims);
			r->setInd2(tmp);
			double _value2 = indValue[tmp];
			//naux current
			tmp = "i:" + tmp;
			if (_node_list.find(tmp) == _node_list.end())
			{
				_node_list[tmp] = ++k;
			}
			r->setAuxNeg(_node_list[tmp]);

			// value
			tmp = tokenizer(line, delims);
			r->setValue(sqrt(_value1*_value2)*to_double(tmp));

			// add to device list
			_dev_list.push_back(r);
		}
		////////////////////////////////////////////////////////////////////
		else if (line[0] == 'X')
		{
			Subckt s;
			string Xname;
			Xname = tokenizer(line, delims);
			s.setXName(Xname);
			_subcktname.push_back(Xname);
            tmp = tokenizer(line, delims);
            string tmp2=tmp;
			while ((tmp = tokenizer(line, delims)) != "")
			{
                s.addpin(tmp2);
                tmp2=tmp;
            }

            s.setName(tmp2);
			_subcktX[Xname] = s; //seems not necessary to add s into _subckt?
		}
		////////////////////////////////////////////////////////////////////
		else
		{
			string token = tokenizer(line, delims);
			// netlist file ends
			if (token == ".END") {
				return;
			}
			// specify output node
			else if (token == ".PROBE" /*|| token == ".PRINT"*/) {
				token = tokenizer(line, delims);
				while (!token.empty()) {
					if (token == "V")
					{
						token = tokenizer(line, delims);
						continue;
					}
                    //token = "V<" + token + ">";
					_Y.push_back(token);

					_probe_list.push_back(_node_list[token]);
					++_num_out;
					token = tokenizer(line, delims);
				}
			}
			else if (token == ".SUBCKT")
			{
				Subckt s;
				tmp = tokenizer(line, delims);
				s.setName(tmp);
				while ((tmp = tokenizer(line, delims)) != "")
				{
					s.addpin(tmp);
				}
				while (getline(ifid, line))
				{
					capitalize(line);
					if (line[0] != '.') {
						s._line.push_back(line);
					}
					else
					{
						tmp = tokenizer(line, delims);
						if (tmp == ".ENDS")
						{
							_subckt[s.getName()] = s;
							break;
						}
					}
				}
			} // end while
		}

    }ifid.close();
}
