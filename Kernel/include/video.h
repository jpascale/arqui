#define VIDEO_START (0xB8000)
#define VIDEO_HEIGHT (25)
#define VIDEO_WIDTH (80)
#define VIDEO_END (VIDEO_START+VIDEO_HEIGHT*VIDEO_WIDTH*2-2)
#define VIDEO_LAST_LINE_START (VIDEO_START + ((VIDEO_HEIGHT - 1) * VIDEO_WIDTH * 2))

void video_write_byte(char c);
void __video_debug(char c);