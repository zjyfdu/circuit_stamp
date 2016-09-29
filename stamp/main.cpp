///
/// @file   main.cpp
/// @author Yinghai
/// @date   Fri Sep 12 09:57:35 2008
/// 
/// @brief  This is the main function of STAMP
/// 

#include "stamp.h"
#include <iostream>

using std::cout;
using std::endl;

///
/// \mainpage Guidance for STAMP program
/// \section intro_sec Introduction
/// This docmument aims at helping you to build a STAMP program. 
/// This doc is embbed in a skeleton program show some main steps 
/// recommended in builiding such program. The recommended stamp flow contains
/// -# Parsing the SPICE netlist.
/// -# Stamping the elements from each device to the system matrices.
/// -# Output the matrix to a binary file.
///
/// Please note that the skeleton program is very simple but intuitive. Just 
/// follow the todo items to fill up and expand the functions, and you will
/// have your own STAMP program. Good luck. 
///
/// \section install_sec How to Compile and Install
/// This program is developed under Linux and maintianed by Autotools.
/// However, it can also be compiled in win32 enviroment.
/// To build this program in Linux, type the following commands in the shell:
/// \verbatim
/// ./configure --enable-debug=yes
///  make
/// \endverbatim 
/// Your can drop the \e --enable-debug=yes argument if you don't want to debug 
/// the program After building the program, you will have a binary 
/// executable file in \e src. Then
/// You can run it by typing
/// \verbatim 
/// ./stamp netlist.sp mat.out
/// \endverbatim
/// For windows user, please follow the following instructions:
/// -# Download a VC++6.0 with SP6 from http://10.64.130.17:82/ (search with keyword VC++)
/// -# Go to directory win32/stamp, open the VC++ project file stamp.dsw
/// -# Build the project in VC++6.0
///
/// \section hint_sec Hint
/// - Make good use of this document. Especially, check the TODO list. 
/// - Discuss with your colleagues. But \e don't \e copy!
/// - Read the SPICE manual or some C++ references. 
/// 
/// \section exp_sec How to Expand the Program
/// For Linux user, when you add some new source or header files to this project, you have to update 
/// the \e Makefile.am and reconfig the Autotools. First, you have to add the names
/// of the source files to \e Makefile.am in \e src directory and then type the following commands in the shell
/// \verbatim
/// automake --add-missing
/// autoreconf
/// \endverbatim
/// This will generate a new \e configure file in the project root. Then using the 
/// build commands introduced above to re-build the program.
/// For windows user, just use VC++ to add the source/header files to your VC++ project.
///
/// \section con_sec Contact
/// If you're confused or have any problems. Please contact me. My email is 
/// yangfan@fudan.edu.cn. You can also come to Room 319 at working hours to find me. Thanks. 


/// \brief entrance of the program

int main(int argc, char* argv[]){
	
  if(argc < 3){
    cout<<"usage: stamp input_file output_file"<<endl;
    return 1;
  }

  Stamp s;
  
  /// phase 1: parsing the netlist
  s.parse(argv[1]);

  s.sub_setup();
  /// phase 2: stamping
  s.setup();



  /// phase 3: output
  s.output(argv[2]);

  return 0;
}
