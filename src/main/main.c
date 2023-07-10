#include <stdint.h>
#include "../kernel/stdbool.h"
#include "../kernel/kernel.h"
#include "../kernel/util.h"
#include "../drivers/pic.h"
#include "../drivers/pit.h"
#include "../drivers/monitor_mode_txt.h"
#include "../drivers/kbd.h"

int key_pressed;

void getch1(int scan_code);
void check_kbd(void);

void getch1(int scan_code)
{
	/* get scan codes and print them */
	key_pressed = scan_code;	
	print_number(scan_code, 16);
	print_c('\n');
}


void os_main(void) {
    char msg[] = "OS HAS LOADED!";
    print_at(msg, MAX_COLS / 2 - strlen(msg) / 2, 1);
	print_c('\n');
	set_input_function(getch1);
}

