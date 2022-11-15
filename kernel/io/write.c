#include "drivers/serial.h"
#include "io.h"
#include "memlayout.h"
#include "memop.h"

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

/* The I/O ports */
#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT    0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND  15

static void
move_cursor_(uint16_t pos)
{
        outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
        outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
        outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
        outb(FB_DATA_PORT, pos & 0x00FF);
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
                memmove(buffer, buffer + MAX_COLS,
                        2 * (MAX_COLS * (MAX_ROWS - 1)));
                row--;
                for (int i = 0; i < MAX_COLS; i++)
                        buffer[row * MAX_COLS + i] = TO_VGA(' ');
        }
}

static void
advance_()
{
        if (++col == MAX_COLS) {
                new_line_();
        }
}

static void
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
        move_cursor_(row * MAX_COLS + col);
}

ssize_t
write(const char *str, size_t size)
{
        ssize_t bytes = 0;
        serial_write(str, size);
        for (; size-- != 0; str++, bytes++) {
                putchar(*str);
        }
        return bytes;
}