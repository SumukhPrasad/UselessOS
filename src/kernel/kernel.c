/* Amen. */

#include "kernel.h"
#include "util.h"
#include "stdbool.h"
#include "../drivers/monitor_mode_txt.h"
#include "../drivers/interrupts.h"
#include "../drivers/pic.h"
#include "../drivers/pit.h"
#include "../drivers/kbd.h"

#include "../main/main.h"


// globals
static INPUT_HNDLR input_f = default_input;

// code
void main() {
    /* the main kernel function */

    // initiate interrupt descriptor table and drivers
    idt_init(IDT); // set id table
    pic_initialize(); // intialize the pic
    set_interval_size(1000); // count every 1000 ticks
    pit_initialize(1000); // start timer ticking every ms
    kbd_initialize(); // enable keyboard

    __asm__("sti"); // enable interrupts
    clear_screen();
    greet(); // say welcome

    os_main(); 

    // system loop
    while (true)
        halt(); // halts until interrupted
}

void kbd_dispatch(int kbd_scan_code) {
    input_f(kbd_scan_code);
}

void greet(void) {
    /* prints the welcome message */
    set_attribute_byte(GRAY_ON_BLACK);

    char msg[] = "Welcome!";
    print_at(msg, MAX_COLS / 2 - strlen(msg) / 2, 1);
}

void set_input_function(INPUT_HNDLR proc_input) {
    input_f = proc_input;
}

void default_input(int code) {
    return;
}