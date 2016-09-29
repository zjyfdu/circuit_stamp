///
/// @file   ind.cpp
/// @author Yinghai
/// @date   Fri Sep 12 14:32:59 2008
/// 
/// @brief  implementation of inductor
/// 
/// 
///

#include "ind.h"

void Inductor::stamp(Matrix& C, Matrix& G, Matrix& B)
{
       cout<<_name<<' '<<_pnode<<' '<<_nnode<<' '<<_value<<endl;
    C[_aux_node-1][_aux_node-1] +=_value;
    if(_pnode!=0)
    {
         G[_pnode-1][_aux_node-1] +=1;
         G[_aux_node-1][_pnode-1] -=1;
    }
    if(_nnode!=0)
    {
         G[_nnode-1][_aux_node-1] -=1;
         G[_aux_node-1][_nnode-1] +=1;
    }
	// to be implemented

}
