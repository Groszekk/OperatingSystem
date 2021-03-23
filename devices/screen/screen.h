#ifndef SCREEN_H
#define SCREEN_H

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f

#define CHARCELLSZ 2
#define CTRL 0x3d4
#define DATA 0x3d5

void kprint(char *message);
void kprint_backspace();
int get_cursor_offset();
void set_cursor_offset(int offset);

#endif