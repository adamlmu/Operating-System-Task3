#include <stdint.h>
#include "kernel/types.h"

#define MAX_ALLOC_SZ 512
#define PGSIZE 4096

void *ustack_malloc(uint len);
int ustack_free(void);