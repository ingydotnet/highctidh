#ifndef randombytes_h
#define randombytes_h

#include <stdlib.h>
#include "binding1024.h"
#define randombytes NAMESPACEBITS(randombytes)

void randombytes(void *x, size_t l);

#endif
