//
// Swig Definition file to generate Python bindings
//

%module mercury

%include <std_string.i>

// Add necessary symbols to generated header
%{
   #include "../../include/mercury/theme/theme.h"
%}

// Process symbols in header
%include "../../include/mercury/theme/theme.h"
