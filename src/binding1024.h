#ifndef _BINDING_H
#define _BINDING_H

#ifdef CGONUTS

#include <stdlib.h>
#include <stdint.h>

#if 1024 == BITS

void fillrandom_custom( void *const outptr, const size_t outsz, const uintptr_t context);
void go_fillrandom(void *, void *, size_t);
#define NAMESPACEBITS(x) highctidh_1024_##x
#define NAMESPACEGENERIC(x) highctidh_1024_##x
#define NAMESPACEBITS(go_fillrandom)

__attribute__((weak))
void fillrandom_1024_custom(
  void *const outptr,
  const size_t outsz,
  const uintptr_t context)
{
  go_fillrandom((void *) context, outptr, outsz);
}
#endif

#endif

#endif
