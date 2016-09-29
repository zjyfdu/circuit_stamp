///
/// @file   vsrc.cpp
/// @author Yinghai
/// @date   Fri Sep 12 14:53:40 2008
/// 
/// @brief  implementation of voltage source
/// 
/// 
///


#include "vsrc.h"

void Vsrc::stamp(Matrix& C, Matrix& G, Matrix& B)
{
   cout<<_name<<' '<<_pnode<<' '<<_nnode<<' '<<_value<<endl;
   if(_pnode!=0)
   {   
         G[_pnode-1][_aux_node-1] -=1;
         G[_aux_node-1][_pnode-1] +=1;
   }
   if(_nnode!=0)
   {    
         G[_nnode-1][_aux_node-1] +=1;
         G[_aux_node-1][_nnode-1] -=1;
   }
   B[_aux_node-1][_num] = 1;
	// to be implemented

}
