///
/// @file   res.cpp
/// @author Yinghai
/// @date   Fri Sep 12 14:21:15 2008
/// 
/// @brief  implementation of Resistor
/// 
/// 
///

#include "res.h"

void Resistor::stamp(Matrix& C, Matrix& G, Matrix& B)
{
  cout<<_name<<"  "<<_pnode<<"  "<<_nnode<<"  "<<_value<<endl;
  if (_pnode==0)
		G[_nnode-1][_nnode-1]+=1/_value;
	else if (_nnode==0)
		G[_pnode-1][_pnode-1]+=1/_value;
	else
	{
		G[_pnode-1][_nnode-1] -=1/_value;
        G[_nnode-1][_pnode-1] -=1/_value;
		G[_pnode-1][_pnode-1]+=1/_value;
        G[_nnode-1][_nnode-1]+=1/_value;
	}
  // to be implemented

}
