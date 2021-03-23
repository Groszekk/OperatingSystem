#include "screen.h"
#include "../../libc/mem.h"
#include "../ports/ports.h"

int get_offset(int col, int row)
{
    return 2 * (row * MAX_COLS + col);
}

int get_offset_row(int offset)
{
    return offset / (2 * MAX_COLS);
}

int get_offset_col(int offset)
{
    return (offset - (get_offset_row(offset)*2*MAX_COLS))/2;
}

void screen_scroll(int* offset)
{
    if (*offset >= MAX_ROWS * MAX_COLS * 2)
    {
        for(int i = 1; i < MAX_ROWS; i++) 
            memory_copy((unsigned char*)(get_offset(0, i) + VIDEO_ADDRESS), (unsigned char*)(get_offset(0, i-1) + VIDEO_ADDRESS), MAX_COLS * 2);

        char *last_line = (char*)(get_offset(0, MAX_ROWS-1) + (unsigned char*)VIDEO_ADDRESS); // Blank last line
        for(int i = 0; i < MAX_COLS * 2; i++)
            last_line[i] = 0;

        *offset -= 2 * MAX_COLS;
    }
}

int print_char(char c, int col, int row)
{
    unsigned char *VGA = (unsigned char*)VIDEO_ADDRESS;

    int offset;
    if (col >= 0 && row >= 0) offset = get_offset(col, row);
    else offset = get_cursor_offset();

    if (c == '\n')
    {
        row = get_offset_row(offset);
        offset = get_offset(0, row+1);
    } else if (c == 0x08) // backspace
    {
        VGA[offset] = ' ';
        VGA[offset+1] = WHITE_ON_BLACK;
    } else
    {
        VGA[offset] = c;
        VGA[offset+1] = WHITE_ON_BLACK;
        offset += 2;
    }

    screen_scroll(&offset);

    set_cursor_offset(offset);

    return offset;
}

void kprint_at(char *message, int col, int row)
{
    int offset;
    if (col >= 0 && row >= 0) // if col and row are negative
        offset = get_offset(col, row);
    else
    {
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }

    int i = 0;
    while (message[i] != 0) // loop through message and print it
    {
        offset = print_char(message[i++], col, row);
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}

void kprint(char *message) {
    kprint_at(message, -1, -1);
}

void kprint_backspace()
{
    int offset = get_cursor_offset() - 2;
    int row = get_offset_row(offset);
    int col = get_offset_col(offset);
    print_char(0x08, col, row);
}

int get_cursor_offset()
{
    outb(CTRL, 14); // get high byte of the cursor offset
    int offset = inb(DATA) << 8;
    outb(CTRL, 15);
    offset += inb(DATA);
    return offset * CHARCELLSZ; // position * size of character cell
}

void set_cursor_offset(int offset)
{
    offset /= CHARCELLSZ;
    outb(CTRL, 14);
    outb(DATA, (unsigned char)(offset >> 8));
    outb(CTRL, 15);
    outb(DATA, (unsigned char)(offset & 0xff));
}

void clear_screen()
{
    int screen_size = MAX_COLS * MAX_ROWS;
    int i;
    unsigned char *screen = (unsigned char*) VIDEO_ADDRESS;

    for (i = 0; i < screen_size; i++) {
        screen[i*CHARCELLSZ] = ' ';
        screen[i*CHARCELLSZ+1] = WHITE_ON_BLACK;
    }
    set_cursor_offset(get_offset(0, 0));
}