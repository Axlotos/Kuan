/* linker script for compiling Kuan with ld*/bob
ENTRY(_start)

SECTIONS
{
    . = 1M;

    .boot : { *(.multibootHeader) }
    .text : { *(.text) }
    .bss : { *(.bss) }
}