#include <user/ustack.h>
#include <stdint.h>
#include <kernel/types.h>
#include <unistd.h>

typedef struct Header
{
    uint len;
    uint left;
    struct Header *prev;
    char *address;
} Header;

static Header *stack_top = 0; // Points to the top of the stack
static Header stack_base;

void *ustack_malloc(uint len)
{
    Header *h;
    void *buffer;
    // Check if the requested length is within the allowed range
    if (len > MAX_ALLOC_SZ || len <= 0)
    {
        return (void *)-1;
    }

    // Check if the stack is empty or uninitialized
    if (stack_top == 0)
    {
        if ((stack_base.address = sbrk(PGSIZE)) == (void *)-1) // Allocate the first page
            return (void *)-1;
        // initialize stack base
        stack_base.left = PGSIZE;
        stack_base.len = 0;
        stack_base.prev = stack_top = &stack_base;
        stack_top->address = (char *)(stack_top + 1);
    }

    if (stack_top->left >= len + sizeof(Header))
    {
        h = (Header *)(stack_top->address + stack_top->len);
        h->prev = stack_top;
        h->len = len;
        h->left = h->prev->left - len - sizeof(Header);
        h->address = (char *)(stack_top->address + stack_top->len + sizeof(Header));
        stack_top = h;
        buffer = h->address;
    }

    // Check if there is enough space on the stack to accommodate the new allocation
    else
    {
        if ((h = sbrk(PGSIZE)) == (void *)-1) // Request another page from the kernel
            return (void *)-1;
        h->address = (char *)(h + 1); // skip the sizeof Header
        h->prev = stack_top;
        h->len = len;
        h->left = PGSIZE - (len + sizeof(Header) - h->prev->left);
        stack_top = h;
        buffer = h->address;
    }

    return buffer; // Return pointer to the beginning of the allocated buffer
}

int ustack_free(void)
{

    // If stack is empty
    if (stack_top == 0 || stack_top == &stack_base)
        return -1;

    Header *h = stack_top;
    int len = (int)h->len;
    int left_size = (int)(PGSIZE - h->left);
    Header *prev = h->prev;

    // Check if the last allocated buffer was the only one
    // Or if the buffer is divided between 2 pages
    if (stack_top == 0 || len > left_size)
        sbrk(-PGSIZE);

    stack_top = prev;

    return len;
}