//
// FIXME: I suspect the import problem is addressed on discussions below:
//
// https://github.com/swig/swig/issues/769
// http://www.swig.org/Doc3.0/Python.html#Python_modulepackage
// https://stackoverflow.com/questions/24920357/initialize-a-sub-module-within-a-package-with-swig-and-python-3
// https://stackoverflow.com/questions/1183716/python-properties-swig/4750081
//

%module mercury

%include <std_string.i>

// Add necessary symbols to generated header
%{
   #include "../../include/mercury/theme/theme.h"
%}

// Process symbols in header
%include "../../include/mercury/theme/theme.h"
