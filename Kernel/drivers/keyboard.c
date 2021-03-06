#include <keyboard.h>
#include <video.h>

#define is_letter(x) (((x)>='a'&&(x)<='z')||(x>='A'&&x<='Z')?1:0)
char read_port(char * port);


unsigned char keyboard_map[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

unsigned char shift_map[128] =
{
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*', /* 9 */
  '(', ')', '_', '=', '\b', /* Backspace */
  '\t',     /* Tab */
  'Q', 'W', 'E', 'R', /* 19 */
  'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', /* Enter key */
    0,      /* 29   - Control */
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', /* 39 */
 '\"', '~',   0,    /* Left shift */
 '|', 'Z', 'X', 'C', 'V', 'B', 'N',      /* 49 */
  'M', '<', '>', '?',   0,        /* Right shift */
  '*',
    0,  /* Alt */
  ' ',  /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
  '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
  '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
};

char buffer[256];

unsigned int w = 0;
unsigned int r = 0;
int shift1 = 0;
int shift2 = 0;
int control1 = 0;
int alt1 = 0;
int capslock = 0;

/*
Based on code from this link
http://arjunsreedharan.org/post/99370248137/kernel-201-lets-write-a-kernel-with-keyboard
*/
void keyboard_buffer_write(){
  unsigned char status;
  char keycode;

  status = read_port(0x64);

    if (status & 0x01) {
        keycode = read_port(0x60);

        if((unsigned char)keycode == (0x2a|0x80))
        {
            shift1 = 0;
        }

        else if ((unsigned char)keycode == (0x36|0x80))
        {
            shift2 = 0;
        }
        else if ((unsigned char)keycode == (0x1d|0x80))
        {
            control1 = 0;
        }
        else if ((unsigned char)keycode == (0x38|0x80))
        {
            alt1 = 0;
        }
        else if (keycode > 0)
        {
            switch (keycode)
            {
                case 0x3a:
                    capslock =! capslock;
                    break;

                case 0x2a:
                    shift1 = 1;
                    break;

                case 0x1d:
                    control1 = 1;
                    break;

                case 0x38:
                    alt1 = 1;
                    break;

                case 0x36:
                    shift2 = 1;
                    break;

                default:
                    if (keyboard_map[keycode]!=0)
                    {
                      if (shift1 || shift2 || capslock)
                          buffer[w%256] = shift_map[keycode];
                      else
                          buffer[w%256] = keyboard_map[keycode];
                        
                      video_write_byte(buffer[w % 256]);
                      w++;
                    }
                    break;
            }
            

        }
  }

  
}

char keyboard_buffer_read(){

	while (r == w);
	char ret = buffer[r % 256];
  r++;
  return ret;
  
}