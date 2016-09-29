///
/// @file   stamp.h
/// @author Yinghai
/// @date   Fri Sep 12 10:58:14 2008
/// 
/// @brief  Header file for Stamp class
/// 



#ifndef STAMP_H
#define STAMP_H

#include "mat.h"
#include "subckt.h"
#include <map>
#include <vector>
#include <string>

class Device;
class Subckt;

using std::vector;


/// \class Stamp 
///
/// \brief Stamp engine
/// 
/// The class Stamp is actually the syamp engine. It contains necessary data
/// structures for completing the work. 
class Stamp{
public:
  typedef std::vector<Device*> devList;
  typedef std::map<std::string, int> nodeList;
	
  /// \brief Constructor
  Stamp():_C(NULL),_G(NULL),_B(NULL),_LT(NULL) {}

  /// \brief Destructor
  /// 
  /// It destroys the system matrix and release the allocated memory. 
  ~Stamp() {
    if(_C) delete _C; 
    if(_G) delete _G;
    if(_B) delete _B;
    if(_LT) delete _LT;
  }



  void parse(char* filename);

  void output(char* filename);

  void setup();

  void sub_setup();
 
  
private:
  /// \brief device list 
  ///
  /// Device list holds all the components in the netlist. It is 
  /// implemented using std::vector. You can find an specified device
  /// in it or enumerate the device using iterator. 
  devList _dev_list;

  /// \brief node list
  ///
  /// Node list holds all the node in the netlist. The node list is a 
  /// dictionary that every node name has a corresponding index number. 
  nodeList _node_list;

  /// \brief probe list
  ///
  /// Probe list is built up from the .PROBE card in the SPICE netlist.
  /// It specifies which nodes needs to be examined. And system matrix
  /// \f$ L^T \f$ is built from it. 
  vector<int> _probe_list;

  vector<string> _U;

  vector<string> _Y;

  /// \brief system matrix \f$ C \f$
  ///
  /// Matrix \f$ C \f$ holds the contribution from capacitors and inductors.
  Matrix* _C;

  /// \brief system matrix \f$ G \f$
  ///
  /// Matrix \f$ G \f$ holds conductance.
  Matrix* _G;

  /// \brief system matrix \f$ B \f$
  ///
  /// Matrix \f$ B \f$ is the input incident matrix
  Matrix* _B;

  /// \brief system matrix \f$ L^T \f$
  ///
  /// Matrix \f$ L^T \f$ is the output incident matrix
  Matrix* _LT;

  /// \brief #inputs
  int _num_in;

  /// \brief #outputs
  int _num_out;

  /// for ind and mut
  map<string, double> indValue;

  /// for subskt
  map<string, Subckt> _subckt;
  map<string, Subckt> _subcktX;
  vector<string> _subcktname;
};

#endif
