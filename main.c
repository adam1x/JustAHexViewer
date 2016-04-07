//
//  main.c
//  HexViewer
//
//  Created by Adam Xu on 1/6/16.
//  Copyright © 2016 Adam Xu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void printLine(long offset, unsigned char* pLine, int len)
{
    printf("%010lXh: ", offset);
    
    unsigned char* end = pLine + len;
    for (int i = 0; pLine < end; ++pLine, ++i)
    {
        printf("%02X", *pLine);
        putchar((i == 7) ? '-' : ' ');
    }
    if (len < 16)
    {
        for (int i = len; i < 16; ++i)
        {
            printf("   ");
        }
    }
    
    printf("; ");
    
    for (pLine -= len; pLine < end; ++pLine)
    {
        putchar(isprint(*pLine) ? *pLine : '.');
    }
    
    putchar('\n');
}

int main(int argc, const char * argv[])
{
    if (argc < 2)
    {
        printf("Enter input file path on the command line.\n");
    }
    
    FILE* pFile = fopen(argv[1], "rb");
    if (pFile == NULL)
    {
        printf("Invalid file path.\n");
        return 1;
    }
    
    fseek(pFile, 0L, SEEK_END);
    long fileSize = ftell(pFile);
    rewind(pFile);
    
    unsigned char* buffer;
    buffer = calloc(1, fileSize);
    if (buffer == NULL)
    {
        printf("Failed to allocate enougth memory.");
        fclose(pFile);
        return 2;
    }
    
    unsigned long nread = fread(buffer, 1, fileSize, pFile); //
    fclose(pFile);
    if (nread != fileSize)
    {
        printf("Failed to read file.");
        return 3;
    }

    
    unsigned char* fileEnd = buffer + fileSize;
    for (unsigned char* p = buffer; p < fileEnd; p += 16)
    {
        int len1 = (int)(fileEnd - p);
        int len2 = 16;
        printLine(p-buffer, p, (len1<len2) ? len1 : len2);
    }
    
    return 0;
}
