#include "io.h"
#include "memlayout.h"

enum vga_color {
        VGA_COLOR_BLACK = 0,
        VGA_COLOR_BLUE = 1,
        VGA_COLOR_GREEN = 2,
        VGA_COLOR_CYAN = 3,
        VGA_COLOR_RED = 4,
        VGA_COLOR_MAGENTA = 5,
        VGA_COLOR_BROWN = 6,
        VGA_COLOR_LIGHT_GREY = 7,
        VGA_COLOR_DARK_GREY = 8,
        VGA_COLOR_LIGHT_BLUE = 9,
        VGA_COLOR_LIGHT_GREEN = 10,
        VGA_COLOR_LIGHT_CYAN = 11,
        VGA_COLOR_LIGHT_RED = 12,
        VGA_COLOR_LIGHT_MAGENTA = 13,
        VGA_COLOR_LIGHT_BROWN = 14,
        VGA_COLOR_WHITE = 15,
};

#define VGA_MEMORY_ADDRESS (void *)0xB8000
#define TO_VGA(c) \
        (((uint16_t)(c)) | ((VGA_COLOR_LIGHT_GREY | VGA_COLOR_BLACK << 4)) << 8)

uint16_t *buffer = MM_VIRTADDR(VGA_MEMORY_ADDRESS);
uint16_t *curr_buffer = MM_VIRTADDR(VGA_MEMORY_ADDRESS);

static void
init_buffer()
{
        for (int i = 0; i < (80 * 24); i++) buffer[i] = TO_VGA(' ');
}

void
putchar(char c)
{
        if (curr_buffer == buffer) {
                init_buffer();
        }
        if (c == '\n') {
                curr_buffer =
                    buffer +
                    ((((uint32_t)(curr_buffer - buffer) / 80) + 1) * 80);
        }
        else {
                *curr_buffer++ = TO_VGA(c);
        }
}