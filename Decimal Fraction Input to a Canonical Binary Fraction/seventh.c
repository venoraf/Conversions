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
  while (fgets(str, 1000, dataFile) != NULL)
    {
      str[strcspn(str, "\n")] = '\0';
      char* t1 = strtok(str, " ");
      char* t2 = strtok(NULL, " ");
      double numVal = atof(t1);
      int rad = atoi(t2);
      //printf("%f, %d", numVal, rad);
      char z = '0';
      char o = '1';
      out[rad]='\0';
      if (numVal < 0){
	memset(out,'1',rad);
	numVal*= -1;
	z ='1';
	o = '0';
      } 
      memset(out,z,rad);

      double maxint = pow(2,rad-1) - 1;
      if (maxint < numVal){
	out[0] = z; 
	for ( int i = 1; i < rad; i++)
	  out[i] = o;
      } else {
	int inx = 1;
	if (z=='1') numVal -=1;
	for ( int i = rad-2; i>=0; i--){
	  //printf("%12.0f , %d\n",numVal, i);
	  if ( numVal > pow(2,i)-1){
	    out[inx] = o;
	    numVal -= pow(2,i);
	  }else{
	    out[inx] = z;
	  }
	  inx++;
	}
      }
      
      out[rad] = '\0';
      printf("%s\n", out);
    }
}
