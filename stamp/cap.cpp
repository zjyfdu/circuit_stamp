///
/// @file   cap.cpp
/// @author Yinghai
/// @date   Fri Sep 12 14:25:35 2008
/// 
/// @brief  implementation of Capacitor
/// 
/// 
///

#include "cap.h"

void Capacitor::stamp(Matrix& C, Matrix& G, Matrix& B)
{
      cout<<_name<<' '<<_pnode<<' '<<_nnode<<' '<<_value<<endl;
    if (_pnode==0)
		C[_nnode-1][_nnode-1]+=_value;
    else if (_nnode==0)
		C[_pnode-1][_pnode-1]+=_value;
	else
	{
		C[_pnode-1][_nnode-1] -=_value;
        C[_nnode-1][_pnode-1] -=_value;
		C[_pnode-1][_pnode-1]+=_value;
        C[_nnode-1][_nnode-1]+=_value;
	}
	// to be implemented

}


