#pragma once


#ifdef EN_DEBUG
#include <iostream>
#define EN_DEBUGMSG(x) std::cout << x << "\n" 
#else
#define EN_DEBUGMSG(x)
#endif