///
/// @file   isrc.cpp
/// @author Yinghai
/// @date   Fri Sep 12 14:45:16 2008
/// 
/// @brief  implementation of current source
/// 
/// 
///

#include "isrc.h"

void Isrc::stamp(Matrix& C, Matrix& G, Matrix& B)
{
  cout<<_name<<' '<<_pnode<<' '<<_nnode<<' '<<_value<<endl;
  B[_pnode-1][_num] -= 1;
  // to be implemented

}
