///
/// @file   vsrc.h
/// @author Yinghai
/// @date   Fri Sep 12 14:45:49 2008
/// 
/// @brief  header of voltage source
/// 
/// 
///


#ifndef VSRC_H
#define VSRC_H

#include "device.h"

/// \class Vsrc
///
/// \brief The voltage source
///
/// A Vsrc instance corrsponds to the "v1 n1 n2 1" card in the SPICE netlist
/// It records the information of the voltage source. Like the inductor, 
/// a voltage source will also introduce a new variable to the equation, we 
/// have to record its current. 
class Vsrc: public Device{
public:
  /// \brief Constructor
  /// \param name name of the voltage source
  Vsrc(const string& name):Device(name) {}

  /// \brief stamping function of the voltage source
  ///
  /// @param C system matrix \f$ C \f$
  /// @param G system matrix \f$ G \f$
  /// @param B system matrix \f$ B \f$
  ///
  /// \todo You have to fills in each stamp function. 
  ///
  virtual void stamp(Matrix& C, Matrix& G, Matrix& B);

  /// \brief Destructor
  virtual ~Vsrc() {}

  /// \brief Get auxiliary node
  ///
  /// @return auxiliary node (current through the inductor)
  int auxNode() const {return _aux_node;}

  /// \brief set auxiliary node number
  ///
  /// @param s auxiliary node number
  ///
  void setAux(int s) {_aux_node = s;}

  void setInnum(int num){ _num=num;}
  
  
private:
  /// \brief auxiliary node number
  int _aux_node;
  int _num;
};

#endif
