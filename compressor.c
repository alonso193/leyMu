#include "compressor.h"
int binToInt(char *cadenaBinaria, int longitud) {
  int decimal = 0;
  int multiplicador = 1;
  char caracterActual;
  for (int i = longitud - 1; i >= 0; i--) {
    caracterActual = cadenaBinaria[i];
    if (caracterActual == '1') {
      decimal += multiplicador;
    }
    multiplicador = multiplicador * 2;
  }
  return decimal;
}

void compressor(char *fileName)
{
    int lineCounter = 0;
    char character[16];
    //open file as read only
    FILE *inFile = fopen (fileName, "r");
    FILE *outFile = fopen ("outFile.txt", "w");
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
    for (int i = 0; i < lines; i++)
    {
        fgets(character, 100, inFile);
        //saving the sign bit
        //step 1
        char sign = character[0];
        int magnitudeLenght = 15;
        char magnitude[magnitudeLenght];
        //getting the magnitude
        for (int j = 0; j < magnitudeLenght; j++) {
            magnitude[j] = character[j+1];
        }
        int magDec = binToInt(magnitude, magnitudeLenght);
        //step2
        if (magDec > 32635)
        {
            char temp[15] = "111111101111011";
            for (int k = 0; k < 15; k++) {
                magnitude[k] = temp[k];
            }
            magDec = 32635;
        }

        /*
        step 3
        */
        int c, d, count;

        count = 0;

        for (c = 14 ; c >= 0 ; c--)
        {
           d = (magDec+132) >> c;

           if (d & 1)
              magnitude[count] = 1 + '0';
           else
              magnitude[count] = 0 + '0';

           count++;
        }
        magnitude[count] = '\0';
        //printf("%s", character);
        //printf("%s\n", magnitude);
        /*
        */

        /*
        step 4
        */
        char exponent[8];
        int p;
        int flag = 1;
        int mantissaIndex;
        for (int m = 0; m < 8; m++) {
            exponent[m] = magnitude[m];
            if (exponent[m] == '1' && flag == 1) {
                flag = 0;
                p = 7 - m;
                mantissaIndex = m;
            }
        }
        exponent[8] = '\0';
        char mantissa[4];
        int mantissaCount = 0;
        //printf("%i\n", mantissaIndex);
        for (int n = mantissaIndex+1; n < (mantissaIndex+5); n++) {
            mantissa[mantissaCount] = exponent[n];
            mantissaCount++;
        }
        mantissa[mantissaCount] = '\0';
        /*
        */
        char encoding[8];
        encoding[0] = sign;
        count = 0;

        for (c = 2 ; c >= 0 ; c--)
        {
           d = (p) >> c;

           if (d & 1)
              encoding[count+1] = 1 + '0';
           else
              encoding[count+1] = 0 + '0';
           count++;
        }

        for (int a = 0; a < 4; a++) {
            encoding[a+4] = mantissa[a];
        }
        encoding[8] = '\0';
        fputs(encoding, outFile);
    }
    fclose(outFile);
    fclose(inFile);
}
