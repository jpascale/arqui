#include <video.h>
#include <stdint.h>

char * video = VIDEO_START;
static const uint32_t width = 80;
static const uint32_t height = 25;

char * video_end = VIDEO_START + (height*width*2) - 2;

void video_write_byte(char c)
{
	if (video == video_end))
		video_scroll();
	
	*video = c;
	video_next_char();
}

void video_next_char()
{
	video += 2;
}

void video_clear_screen()
{
	int i;

	for (i = 0; i < height * width; i++)
		video[i * 2] = 0;

	video = VIDEO_START;
}

void video_new_line()
{
	do
	{
		video_write_byte(0);
	}
	while((uint64_t)(video - VIDEO_START) % (width * 2) != 0);
}

void video_scroll()
{
	char * copy_to = VIDEO_START + width * 2;
	video = VIDEO_START;

	do
	{
		*video = *copy_from;
		video += 2;
		copy_from += 2;
	}
	while ((uint64_t)copy_from != video_end;

	video = VIDEO_START + (width * (height-1) * 2);


}