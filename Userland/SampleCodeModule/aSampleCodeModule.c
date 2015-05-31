#include <stdint.h>

char * v = (char*)0xB8000 + 79 * 2;

extern char bss;
extern char endOfBinary;

static int var1 = 0;
static int var2 = 0;

void print(char * str);
void sys_read(char * p);

void * memset(void * destiny, int32_t c, uint64_t length);

int main() {
	//Clean BSS
	memset(&bss, 0, &endOfBinary - &bss);

	//All the following code may be removed 
	//*v = 'X';
	//char str[]="GDSGFDSGFDSGFDSGDF";
	print("Dimusa6$ Hola, este es el mejor sistema operativo del mundo, los otros son caca, aguante Visual Basic");
	//putchar(-1);

	while(1){
		char c;
		sys_read(&c);

		if (c != -1){
			putchar(c);
			//*((char*)0xB800C)=c;
		}
	}

	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;
}

void * memset(void * destiation, int32_t c, uint64_t length) {
	uint8_t chr = (uint8_t)c;
	char * dst = (char*)destiation;

	while(length--)
		dst[length] = chr;

	return destiation;
}
