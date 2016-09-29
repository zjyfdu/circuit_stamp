///
/// @file   cap.h
/// @author Yinghai
/// @date   Fri Sep 12 14:21:48 2008
/// 
/// @brief   header of the Capacitor class
/// 
/// 
///

#ifndef CAP_H
#define CAP_H

#include "device.h"


/// \class Capacitor
///
/// \brief The capacitor
///
/// A Capacitor instance corrsponds to the "c1 n1 n2 3p" card in the SPICE netlist
/// It records the information of the capacitor. 
class Capacitor: public Device{
public:
  /// \brief Constructor
  /// \param name name of the capacitor
  Capacitor(const string& name):Device(name) {}
  
  /// \brief stamping function of the capacitor
  ///
  /// @param C system matrix \f$ C \f$
  /// @param G system matrix \f$ G \f$
  /// @param B system matrix \f$ B \f$
  ///
  /// \todo You have to fills in each stamp function. 
  /// 
  virtual void stamp(Matrix& C, Matrix& G, Matrix& B);

  /// \brief Destructor
  virtual ~Capacitor() {}
};

#endif

