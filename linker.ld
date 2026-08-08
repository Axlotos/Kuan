/* linker script for compiling Kuan */
ENTRY(_start)

SECTIONS
{
    . = 1M;

    .boot : { *(.multibootHeader) }
    .text : { *(.text) }
    .bss : { *(.bss) }
}