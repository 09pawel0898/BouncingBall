#pragma once

#include <stdio.h>

#ifdef EN_DEBUG
#define EN_DEBUGMSG(f_, ...) printf("%s", "[Engine] ");\
printf((f_),__VA_ARGS__);\
printf("%s", "\n");
#else
#define EN_DEBUGMSG(f_, ...)
#endif