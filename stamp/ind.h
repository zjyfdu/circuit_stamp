///
/// @file   ind.h
/// @author Yinghai
/// @date   Fri Sep 12 14:28:21 2008
/// 
/// @brief   header of the Inductor class
/// 
/// 
///

#ifndef IND_H
#define IND_H

#include "device.h"

/// \class Inductor
///
/// \brief The inductor
///
/// A Inductor  instance corrsponds to the "l1 n1 n2 3n" card in the SPICE netlist
/// It records the information of the inductor. In MNA formualtion, an inductor will 
/// introduce a new state variable to the equation, i.e. its current. So we added an 
/// auxiliary node \e _aux_node to store this informatin. 
class Inductor: public Device{
public:
  /// \brief Constructor
  /// \param name name of the inductor
  Inductor(const string& name):Device(name) {}

  /// \brief stamping function of the inductor
  ///
  /// @param C system matrix \f$ C \f$
  /// @param G system matrix \f$ G \f$
  /// @param B system matrix \f$ B \f$
  ///
  /// \todo You have to fills in each stamp function. 
  /// 
  virtual void stamp(Matrix& C, Matrix& G, Matrix& B);

  /// \brief Destructor
  virtual ~Inductor() {}

  /// \brief Get auxiliary node
  ///
  ///
  /// @return auxiliary node (current through the inductor)
  ///
  int auxNode() const {return _aux_node;}

  /// \brief set auxiliary node number
  ///
  /// @param s auxiliary node number
  ///
  void setAux(int s) {_aux_node = s;}
  
  private:

  /// \brief auxiliary node number
  int _aux_node;
};

#endif
