%module mercury

// Add necessary symbols to generated header
%{
   #include "../../include/mercury/theme/theme.h"
    %}

// Process symbols in header
%include "../../include/mercury/theme/theme.h"
