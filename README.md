# Operating-System-Task3
This assignment focuses on implementing memory management features in the xv6 operating system. The assignment is divided into three main tasks:

Userspace Stack Memory Allocator: Implementing a user-space stack-based memory allocator that functions like a LIFO stack for allocating and freeing memory buffers. The allocator should use the sbrk() system call to request memory from the kernel.
Swapping Pages Out and In: Extending the xv6 kernel to support paging, which allows storing parts of a process's memory on disk (swapping out) and retrieving them back into physical memory on demand (swapping in). This task involves modifying the process control block (PCB), handling page faults, and managing swap files.
Page Replacement Algorithms: Implementing different page replacement algorithms to decide which pages should be swapped out when physical memory is exhausted. The algorithms to be implemented are: Not Frequently Used + Aging (NFUA), Least Accessed Page + Aging (LAPA), Second Chance FIFO (SCFIFO), and a disabled mode (NONE).

The assignment covers important aspects of memory management, including user-space memory allocation, virtual memory management, paging, and page replacement algorithms. It involves modifying the xv6 kernel code and implementing new features to support these memory management techniques.
