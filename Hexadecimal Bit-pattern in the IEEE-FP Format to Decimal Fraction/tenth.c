#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

typedef union {

    float numVal;
    struct
    {
        unsigned int man : 23;
        unsigned int exp : 8;
        unsigned int sign : 1;

    } maskVal;
} printfloat;

int main(int argc, char* argv[]) {
    if (argc == 1)
    {
        printf("\nNo arg recieved");
        return -1;
    }

    if (argc > 2)
    {
        printf("\nToo many arguments: %d where only 1 expected", argc);
        return -2;
    }

    FILE* dataFile;
    char str[1000];

    // open file
    //printf("Opening %s", argv[1]);
    dataFile = fopen(argv[1], "r");

    if (NULL == dataFile) {
        printf("file can't be opened \n");
        return -3;
    }
    while (fgets(str, 1000, dataFile) != NULL) {
        str[strcspn(str, "\n")] = '\0';
        char* t1 = strtok(str, " ");
        char* t2 = strtok(NULL, " ");
        char* t4 = strtok(NULL, " ");
        t4 = strtok(NULL, " ");
        char* t5 = strtok(NULL, " ");

        int size = atoi(t1);
        int exp = atoi(t2);
        char hex[20];
        memset(hex, '\0', 20);
        int prec = atoi(t5);
        for (int i = 0; i < strlen(t4) - 2; i++)
            hex[i] = t4[i + 2];
        //printf("%i, %i,%s, %i\n", size, exp, hex, dec);
        //Convert to Binary
        int bin[256];
        int inx = 0;
        for (int i = 0; i < strlen(hex); i++) {
            switch (hex[i]) {
            case '0':
                bin[inx++] = 0;
                bin[inx++] = 0;
                bin[inx++] = 0;
                bin[inx++] = 0;
                break;
            case '1':
                bin[inx++] = 0;
                bin[inx++] = 0;
                bin[inx++] = 0;
                bin[inx++] = 1;
                break;
            case '2':
                bin[inx++] = 0;
                bin[inx++] = 0;
                bin[inx++] = 1;
                bin[inx++] = 0;
                break;
            case '3':
                bin[inx++] = 0;
                bin[inx++] = 0;
                bin[inx++] = 1;
                bin[inx++] = 1;
                break;
            case '4':
                bin[inx++] = 0;
                bin[inx++] = 1;
                bin[inx++] = 0;
                bin[inx++] = 0;
                break;
            case '5':
                bin[inx++] = 0;
                bin[inx++] = 1;
                bin[inx++] = 0;
                bin[inx++] = 1;
                break;
            case '6':
                bin[inx++] = 0;
                bin[inx++] = 1;
                bin[inx++] = 1;
                bin[inx++] = 0;
                break;
            case '7':
                bin[inx++] = 0;
                bin[inx++] = 1;
                bin[inx++] = 1;
                bin[inx++] = 1;
                break;
            case '8':
                bin[inx++] = 1;
                bin[inx++] = 0;
                bin[inx++] = 0;
                bin[inx++] = 0;
                break;
            case '9':
                bin[inx++] = 1;
                bin[inx++] = 0;
                bin[inx++] = 0;
                bin[inx++] = 1;
                break;
            case 'a':
                bin[inx++] = 1;
                bin[inx++] = 0;
                bin[inx++] = 1;
                bin[inx++] = 0;
                break;
            case 'b':
                bin[inx++] = 1;
                bin[inx++] = 0;
                bin[inx++] = 1;
                bin[inx++] = 1;
                break;
            case 'c':
                bin[inx++] = 1;
                bin[inx++] = 1;
                bin[inx++] = 0;
                bin[inx++] = 0;
                break;
            case 'd':
                bin[inx++] = 1;
                bin[inx++] = 1;
                bin[inx++] = 0;
                bin[inx++] = 1;
                break;
            case 'e':
                bin[inx++] = 1;
                bin[inx++] = 1;
                bin[inx++] = 1;
                bin[inx++] = 0;
                break;
            case 'f':
                bin[inx++] = 1;
                bin[inx++] = 1;
                bin[inx++] = 1;
                bin[inx++] = 1;
                break;
            }
        }
        //printf("offset to adjust %d\n", adjust);
        //print bin
        //for (int i = 0; i < inx; i++)
        //    printf("%i", bin[i]);
        //printf("\n");
        int adjust = inx - size;

        if (size == 32) {
            int pwr = 0;
            unsigned int rm = 0;
            int offset = 0;
            offset = 0;
            for (int i = size - 1; i >= 1 + exp; i--) {
                rm = rm + (pow(2, offset++)) * bin[i];
            }
            //exponential
            int x = 1;
            for (int i = exp - 1; i >= 0; i--) {
                pwr += pow(2, i) * bin[(x++) + adjust];
            }
            //printf("exp %d, man %d \n", pwr, rm);
            printfloat val;
            val.maskVal.man = rm;
            val.maskVal.exp = pwr;
            val.maskVal.sign = bin[adjust];
            printf("%.*f\n", prec, val.numVal);
        }
        else {
            int sign = 1;
            int pwr = 0;
            //sign
            if (bin[adjust] == 1) {
                sign = -1;
            }
            int base = 0;
            base = pow(2, exp - 1) - 1;
            //base = pow(2, base + 1) - 1;
            int re = 0;
            double rm = 0;
            int offset = 0;
            for (int i = 1; i < exp + 1; i++) {
                re += pow(2, offset++) * bin[i + adjust];
            }
            offset = -1;
            for (int i = 1 + exp; i < size; i++) {
                rm += pow(2, offset--) * bin[i + adjust];
            }
            //exponential
            int x = 1;
            for (int i = exp - 1; i >= 0; i--) {
                pwr += pow(2, i) * bin[(x++) + adjust];
            }
            long double val = 0;
            int allzero = 1;

            for (int i = 1; i < inx; i++) {
                if (bin[i + adjust] == 1) {
                    allzero = 0;
                }
            }
            if (allzero == 1) {
                val = 0;
            }
            else if (re == 0) {
                pwr = 1 - base;
                val = rm * pow(2, pwr);
            }
            else {
                pwr = pwr - base;
                //mantissa
                val = pow(2, pwr) * (1 + rm);

            }
            long double tmp = val;
            for (int i = 0; i < prec; i++) {
                tmp = tmp * 10;
            }
            if (sign == -1) {
                printf("-");
		tmp = tmp + 0.5;
            } else
                tmp = tmp + .5;
            for (int i = 0; i < prec; i++) {
                tmp = tmp / 10;
            }

            int numsize = 1;
            while (tmp >= 10) {
                tmp /= 10;
                numsize++;
            }
            for (int i = 0; i < numsize + prec; i++) {
                int digit = tmp;
                if (i == numsize && prec > 0) printf(".");
                printf("%d", digit);
                tmp = tmp - digit;
                tmp = tmp * 10;
            }
            printf("\n");
        }
    }
}
