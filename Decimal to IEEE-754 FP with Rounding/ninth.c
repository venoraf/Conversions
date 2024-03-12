#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

int main(int argc, char* argv[]) {
  if (argc == 1) {
    printf("\nNo arg recieved");
    return -1;
  }

  if (argc > 2) {
    printf("\nToo many arguments: %d where only 1 expected", argc);
    return -2;
  }

  FILE* dataFile;
  char str[1000];
  char out[1000];

  // open file
  //printf("Opening %s", argv[1]);
  dataFile = fopen(argv[1], "r");

  if (NULL == dataFile) {
    printf("file can't be opened \n");
    return -3;
  }

  while (fgets(str, 1000, dataFile) != NULL) {
    str[strcspn(str, "\n")] = '\0';
    //printf("%s\n",str);
    char* t1 = strtok(str, " ");
    char* t2 = strtok(NULL, " ");
    char* t3 = strtok(NULL, " ");
    char* t4 = strtok(NULL, " ");
    double numVal = atof(t1);
    double tmpVal;
    int size = atoi(t2);
    int exp = atoi(t3);
    int mat = atoi(t4);
    memset(out, '\0', 1000);
    //Sign of the number
    if (numVal >= 0) {
      out[0] = '0';
    } else {
      out[0] = '1';
      numVal = numVal * -1;
    }
    //calculate exponent
    tmpVal = numVal;
    int pwr = 0;
    while (tmpVal > 2) {
      tmpVal = tmpVal / 2;
      pwr++;
    }
    while (tmpVal < 1) {
      tmpVal = tmpVal * 2;
      pwr--;
    }

    int bias = (pow(2, exp) - 1)/2;
    //printf("B %d P %d\n", bias, pwr);
    pwr = bias + pwr;
    //exponent
    int iszero = 0;
    int totpwr = pow(2, exp) - 1;
    int inx = 1;
    int places = exp;
    for (int i = places; i >= 0; i--) {
      totpwr -= pow(2, i-1);
      //printf("%d, %d -> %s\n", totpwr, pwr,out);
      if (pwr > totpwr) {
	out[inx] = '1';
	pwr -= pow(2, i-1);
      } else {
	out[inx] = '0';
	iszero = 1;
      }
      inx++;
    }
    //Mantissa
    tmpVal -= 1;
    //printf("M=%f,", tmpVal);
    inx = exp + 1;
   
    for (int i = 1; i <= mat + 1; i++) {
      //printf("%f %f\n", tmpVal,pow(2,i * -1));
      if (tmpVal < pow(2, i * -1)) {
	out[inx] = '0';
	if (inx < size) iszero = 1;
      } else {
	out[inx] = '1';
	tmpVal -= pow(2, i * -1);
      }
      inx++;
    }
    int carry = 0;
    inx = size - 1;
    //printf("%c%c, %f, %f\n", out[inx], out[inx+1], tmpVal, pow(2, (mat + 1) * -1));
    //rounding
    if (out[size] == '1' && tmpVal >= pow(2, (mat + 2) * -1)) carry = 1;
    if (out[size] == '1' && tmpVal == 0 && out[inx] == '1') carry = 1;
    //printf("Carry %d, %d\n", carry,iszero);
    while (carry == 1 && iszero) {
      if (out[inx] == '1') {
	carry = 1;
	out[inx] = '0';
      } else {
	carry = 0;
	out[inx] = '1';
      }
      inx--;
    }
    out[size] = '\0';
    printf("%s\n", out);
  }
}
