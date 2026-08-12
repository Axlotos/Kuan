// Main program for Kuan

typedef struct multibootTag
{
    int type;
    int size;
    long long framebufferAddr;
    int pitch;
    int width;
    int height;
    char bpp; // Char for 8 bits
} multibootTag;

typedef struct rect
{
    int x, y;
    int width, height;
} rect;

void drawPixel(multibootTag *framebufferTag, int pixelX, int pixelY, unsigned int colour)
{
    int row = pixelY * framebufferTag->pitch;
    int col = pixelX * 4;

    unsigned char *pixelPtr = (unsigned char *)(unsigned int)framebufferTag->framebufferAddr;

    pixelPtr += (row + col);


    unsigned int *pixelAddr = (unsigned int *)pixelPtr;

    *pixelAddr = colour;
}

void drawRect(multibootTag *framebufferTag, rect *rectangle, unsigned int colour)
{
    for (int row = rectangle->y; row < rectangle->height + rectangle->y; row++)
    {
        for (int col = rectangle->x; col < rectangle->width + rectangle->x; col++)
        {
            drawPixel(framebufferTag, col, row, colour);
        }
    }
}

int main(unsigned int multibootInfoAddr)
{
    rect rectangle1 = { 100, 100, 150, 120 };
    rect rectangle2 = { 100, 400, 180, 200 };
    rect rectangle3 = { 400, 300, 400, 300 };

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

    // Draw the first row of pixels purple
    for (int pixel = 0; pixel < (framebufferTag->width); pixel++)
    { drawPixel(framebufferTag, pixel, 0, 0xFFFF00FF); }

    // Do the same with the second row
    for (int pixel = 0; pixel < (framebufferTag->width); pixel++)
    { drawPixel(framebufferTag, pixel, 1, 0xFFFF00FF); }

    // Draw rectangle1
    drawRect(framebufferTag, &rectangle1, 0xFFFF0000);

    // Draw rectangle2
    drawRect(framebufferTag, &rectangle2, 0xFF0000FF);

    // Draw rectangle3
    drawRect(framebufferTag, &rectangle3, 0xFF00FF00);

    return 0;
}
