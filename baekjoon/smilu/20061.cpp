#include <unistd.h>

void ft_print_byte(unsigned char ch) {
	write(1, ("0123456789abcdef") + (ch >> 4), 1);
	write(1, ("0123456789abcdef") + (ch & 0x0F), 1);
}

void ft_print_memory_line(const char *addr, unsigned int size) {
	int i;
	
	i = 0;
	while (i < 8) {
		ft_print_byte(*((char*) (&addr + (7 - i))));
		i++;
	}
	write(1, ": ", 2);

	i = 0;
	while (i < 16) {
		if (i < size)
			ft_print_byte(*((unsigned char*) (addr + i)));
		else write(1, "  ", 2);
		if ((i & 1) && (i != 15))
			write(1, " ", 1);
		i++;
	}
	write(1, " ", 1);

	i = 0;
	while (i < size) {
		char ch = *((char*) (addr + i));
		if (32 <= ch && ch <= 127) write(1, &ch, 1);
		else write(1, ".", 1);
		i++;
	}
}
	

void * ft_print_memory(void *addr, unsigned int size) {
	if (size == 0) return addr;
	const char * base = (const char*) addr;

	int num_line = size >> 4; // size / 16
	int i = 0;
	while (i < num_line) {
		ft_print_memory_line(base + (i << 4), 16);
		write(1, "\n", 1);
		i++;
	}
	ft_print_memory_line(base + (num_line << 4), size - ((num_line) << 4));

	return addr;
}

int strlen(const char *s) {
	int count = 0;
	while (*(s++)) count++;
	return count;
}

int main() {
	const char * mem = "asdjf\n\nl;ksajdl;kfjalsk;djfl;jasdljf;lkasdflk;asdfjas";
	ft_print_memory((char*) mem, strlen(mem));
}
