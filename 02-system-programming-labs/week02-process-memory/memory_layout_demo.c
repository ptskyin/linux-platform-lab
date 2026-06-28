#include <stdio.h>
#include <stdlib.h>

int global_var = 42;

void demo_function(void)
{
    /* empty */
}

int main(void)
{
    int stack_var = 24;
    int *heap_var = malloc(sizeof(int));
    void (*func_ptr)(void) = demo_function;

    if (heap_var == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    *heap_var = 99;

    printf("Address of global_var:    %p\n", (void *)&global_var);
    printf("Address of stack_var:     %p\n", (void *)&stack_var);
    printf("Address of heap_var data: %p\n", (void *)heap_var);
    printf("Address of func_ptr:      %p\n", (void *)&func_ptr);
    printf("Address of demo_function: %p\n", (void *)demo_function);

    free(heap_var);
    return EXIT_SUCCESS;
}
