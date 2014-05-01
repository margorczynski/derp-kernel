/*
 * The main source file containing the entry point (the function/symbol called by the bootloader) of the kernel
 */

void kernel_main(void)
{
    char *video_memory = (char*) 0xb8000;

    *video_memory = 'K';
}
