///
/// @file   mut.cpp
/// @author Yinghai
/// @date   Fri Sep 12 15:06:23 2008
/// 
/// @brief  implementation of mutual inductance
/// 
/// 
///

#include "mut.h"

void Mutual::stamp(Matrix& C, Matrix& G, Matrix& B)
{
  cout<<_name<<' '<<_ind1<<' '<<_ind2<<' '<<_value<<endl;
  C[_aux_node_pos-1][_aux_node_neg-1]-=_value;
  C[_aux_node_neg-1][_aux_node_pos-1]-=_value;
	// to be implemented

}
