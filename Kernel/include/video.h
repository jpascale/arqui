#ifndef _VIDEO_DRIVER_H

#define _VIDEO_DRIVER_H
#define VIDEO_START ((char *)0xB8000)
#define VIDEO_HEIGHT (25)
#define VIDEO_WIDTH (80)
#define VIDEO_SIZE (VIDEO_HEIGHT * VIDEO_WIDTH * 2)
#define VIDEO_END (char *)(VIDEO_START+VIDEO_HEIGHT*VIDEO_WIDTH*2-2)
#define VIDEO_LAST_LINE_START (char *)(VIDEO_START + ((VIDEO_HEIGHT - 1) * VIDEO_WIDTH * 2))

#define BACKSPACE_BYTE '\b'

void video_write_byte(char c);
void __video_debug(char c);
void video_screen_saver_check_count(void);
void video_screen_saver_check_restore(void);

#endif