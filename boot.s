# The entry part of Kuan
# This program sets up memory and stuff

.section .multibootHeader
    headerStart:
        .long 0xE85250D6 # Tells GRUB that this program is a kernel
        .long 0 # Tell GRUB to run in 32-bit protected mode
        .long headerEnd - headerStart # Size of the header
        .long -(0xE85250D6 + (headerEnd - headerStart)) 
        # ^ Checksum. Make it so all these numbers add up to zero becaus GRUB wants that for some reason
        # We don't need to add zero      

        # Framebuffer Tag
        .short 5
        .short 0
        .long 20

        # Screen stuff
        .long 0 # width
        .long 0 # height
        .long 32 # depth (colour, 32 for 32 bit colour)

        # Alignment
        .align 8

        # Done!
        .short 0
        .short 0
        .long 8
    headerEnd:

.bss
    .align 16

    stackBottom:
        .skip 16384 # Create the stack (16 KB)
    stackTop:

.text
    .global _start

    _start:
        movl $stackTop, %esp
        push %ebx
        call main
        cli

    loop:
        hlt
        jmp loop
