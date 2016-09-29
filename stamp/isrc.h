///
/// @file   isrc.h
/// @author Yinghai
/// @date   Fri Sep 12 14:35:29 2008
/// 
/// @brief  header of the Current source class
/// 
/// 
///

#ifndef ISRC_H
#define ISRC_H

#include "device.h"

/// \class Isrc
///
/// \brief The current source
///
/// An Isrc instance corrsponds to the "i1 n1 n2 1" card in the SPICE netlist
/// It records the information of the current source. 
class Isrc: public Device{
public:
  /// \brief Constructor
  /// \param name name of the current source
  Isrc(const string& name):Device(name) {}

  /// \brief stamping function of the current source
  ///
  /// @param C system matrix \f$ C \f$
  /// @param G system matrix \f$ G \f$
  /// @param B system matrix \f$ B \f$
  ///
  /// \todo You have to fills in each stamp function. 
  ///
  virtual void stamp(Matrix& C, Matrix& G, Matrix& B);

  void setInnum(int num){ _num=num;}

  /// \brief Destructor
  virtual ~Isrc() {}

private:
	int _num;
};

#endif
