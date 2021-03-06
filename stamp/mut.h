///
/// @file   mut.h
/// @author Yinghai
/// @date   Fri Sep 12 14:54:59 2008
/// 
/// @brief  Header of the mutual inductance
/// 
/// 
///


#ifndef MUTUAL_H
#define MUTUAL_H

#include "device.h"

/// \class Mutual
///
/// \brief The mutual inductance between two inductors
///
/// An Mutual instance corrsponds to the "k1 l1 l2 0.5" card in the SPICE netlist
/// It records the information of the mutual inductance. Differnt from other devices
/// in the SPICE netlist, the mutual inductance doesn't have the concept of pins. 
/// Instead, it records the name of two inductors which will also appear in the 
/// the netlist. However, it is not sure that the two inductors will appear before or
/// after the mutual indectance card. so we have to record the name of these two inductors.
/// Additionally, we also have to record currents through the inductors as auxiliary vairiables. 
class Mutual: public Device{
public:
  /// \brief Constructor
  /// \param name name of the mutual inductance
  Mutual(const string& name):Device(name) {}

  /// \brief stamping function of the mutual inductance
  ///
  /// @param C system matrix \f$ C \f$
  /// @param G system matrix \f$ G \f$
  /// @param B system matrix \f$ B \f$
  ///
  /// \todo You have to fills in each stamp function. 
  /// 
  virtual void stamp(Matrix& C, Matrix& G, Matrix& B);

  /// \brief Destructor
  virtual ~Mutual() {}

  /// \brief return the auxiliary current node  of L1
  /// @return auxiliary current node of L1
  int auxPosNode() const {return _aux_node_pos;}

  /// \brief set the auxiliary current node  of L1
  /// @param s auxiliary current node of L1
  void setAuxPos(int s) {_aux_node_pos = s;}

  /// \brief return the auxiliary current node  of L2
  /// @return auxiliary current node of L2
  int auxNegNode() const {return _aux_node_neg;}

  /// \brief set the auxiliary current node  of L2
  /// @param s auxiliary current node of L2
  void setAuxNeg(int s) {_aux_node_neg = s;}

  /// \brief return the name of L1
  /// @return name of inductor L1
  string ind1() const {return _ind1;}

  /// \brief set the name of L1
  /// @param l  name of inductor L1
  void setInd1(const string& l) {_ind1=l;}

  /// \brief return the name of L2
  /// @return name of inductor L2
  string ind2() const {return _ind2;}

  /// \brief set the name of L2
  /// @param l  name of inductor L2
  void setInd2(const string& l) {_ind2=l;}
  
  private:
  /// \brief auxiliary current node of L1
  int _aux_node_pos;

  /// \brief auxiliary current node of L2
  int _aux_node_neg;

  /// \brief name of inductor L1
  string _ind1;
  
  /// \brief name of inductor L2
  string _ind2;
};

#endif
