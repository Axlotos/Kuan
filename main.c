// Main C program for Kernel of Unlimited AwsomeNess (Kuan)

typedef struct 
{
    int type;
    int size;
    long long frameBufferAddr;
    int pitch;
    int width;
    int height;
    char bpp; // Char for 8 bits
} multibootTag;

void kuanMain(unsigned int multibootInfoAddr)
{
    unsigned int *tagPtr = &multibootInfoAddr + 8; // + 8 to skip the header

    while (1)
    {
        if (tagPtr == 8) { break; }
        else 
        {
            tagPtr += 4;
        }
    }


}