#include <mlx.h>
#include <stdio.h>

int main()
{
    void *ptr;

    ptr = mlx_init();
    mlx_loop(ptr);
    printf("%p\n", mlx_new_window(ptr, 100, 100, "title"));
}