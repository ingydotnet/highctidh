#ifndef _BINDING_H
#define _BINDING_H

#ifdef CGONUTS

#include <stdlib.h>
#include <stdint.h>

#if 2048 == BITS

void fillrandom_custom( void *const outptr, const size_t outsz, const uintptr_t context);
void go_fillrandom(void *, void *, size_t);
#define NAMESPACEBITS(x) highctidh_2048_##x
#define NAMESPACEGENERIC(x) highctidh_2048_##x
#define go_fillrandom NAMESPACEBITS(go_fillrandom)

__attribute__((weak))
void fillrandom_2048_custom(
  void *const outptr,
  const size_t outsz,
  const uintptr_t context)
{
  go_fillrandom((void *) context, outptr, outsz);
}
#endif

#endif

#endif
