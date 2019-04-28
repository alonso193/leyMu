#include "compressor.h"

void decompressor(char *fileName)
{
    int lineCounter = 0;
    char character[16];
    //open file as read only
    FILE *inFile = fopen (fileName, "r");
    FILE *outFile = fopen ("coeffs.txt", "w");
    if (inFile == NULL)
    {
        printf("\nError de apertura del archivo. \n\n");
    }
    //get the number of lines in the file
    while (feof(inFile) != 1)
    {
        fgets(character, 100, inFile);
        lineCounter++;
    }
    rewind(inFile);
    int lines = lineCounter - 1;
    for (int i = 0; i < lines; i++) {
        fgets(character, 100, inFile);
        //saving the sign bit
        //step 1
        char sign = character[0];

        //step 2
        char e[3] = {character[1],character[2],character[3]};
        e[3] = '\0';
        int eDec = binToInt(e,3);

        int a = 3 + eDec;

        //step 3
        char m[4] = {character[4],character[5],character[6],character[7]};
        m[4] = '\0';
        int mDec = binToInt(m,4);

        int num = 132;
        int numShiffted = num << eDec;
        int b = numShiffted - 132;
        int decodedDec = (mDec << a) + b;
        char decoded[16];
        decoded[0] = sign;
        int c, d, count;


        count = 1;

        for (c = 14 ; c >= 0 ; c--)
        {
           d = (decodedDec) >> c;

           if (d & 1)
              decoded[count] = 1 + '0';
           else
              decoded[count] = 0 + '0';

           count++;
        }
        decoded[count] = '\0';
        fputs(decoded, outFile);
    }
}
