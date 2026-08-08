// Main C program for Kuan

typedef struct 
{
    int type;
    int size;
    long long framebufferAddr;
    int pitch;
    int width;
    int height;
    char bpp; // Char for 8 bits
} multibootTag;

int main(unsigned int multibootInfoAddr)
{
    unsigned char *tagPtr = (unsigned char *)multibootInfoAddr + 8;

while (1)
    {
        // Read the type and size temporarily without moving tagPtr
        unsigned int type = *(unsigned int *)tagPtr;
        unsigned int size = *(unsigned int *)(tagPtr + 4);

        // Now use the type variable for the condition
        if (type == 8 || type == 0) 
        { 
            break; 
        }
        else 
        {
            // Use the size variable to jump forward
            tagPtr += (size + 7) & ~7;
        }
    }

    unsigned int finalType = *(unsigned int *)tagPtr;
    if (finalType == 0) { return 1; }

    // Once type = 8, store that tag in a struct
    multibootTag *framebufferTag = (multibootTag *)tagPtr;

    // Draw the first two rows of pixels blue
    unsigned int *framebufferAddr = (unsigned int *)(unsigned int)framebufferTag->framebufferAddr;

    for (int pixel = 0; pixel < (framebufferTag->width * 2); pixel++)
        { *(framebufferAddr + pixel) = 0x0000FFFF; }

    return 0;
}