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

#define MAX_ROWS 25
#define MAX_COLS 80

#define VGA_MEMORY_ADDRESS (void *)0xB8000
#define TO_VGA(c) \
        (((uint16_t)(c)) | ((VGA_COLOR_LIGHT_GREY | VGA_COLOR_BLACK << 4)) << 8)

static uint16_t *buffer = MM_VIRTADDR(VGA_MEMORY_ADDRESS);

static int col;
static int row;

static void *
memmov(void *dst, const void *src, size_t size) {
        char *dst_ = dst;
        const char *src_ = src;
        while (size-- != 0) {
                *dst_++ = *src_++;
        }
        return dst;
}

static void
init_buffer_()
{
        for (int i = 0; i < (MAX_COLS * MAX_ROWS); i++) buffer[i] = TO_VGA(' ');
        col = 0;
        row = 0;
}

static void
new_line_()
{
        col = 0;
        row++;
        if (row == MAX_ROWS) {
                memmov(buffer, buffer + MAX_COLS, MAX_COLS * (MAX_ROWS-1));
                row--;
        }
}

static void
advance_()
{
        if (++col == MAX_COLS) {
                new_line_();
        }
}

void
putchar(char c)
{
        if (col == 0 && row == 0) {
                init_buffer_();
        }
        if (c == '\n') {
                new_line_();
        }
        else {
                buffer[row * MAX_COLS + col] = TO_VGA(c);
                advance_();
        }
}