#include <stdio.h>
#include <stdlib.h>

void extractColumns(char *inFileName, char *outFileName, int numOfCols, int colNums[], char *inBuf, char*outBuf){
  FILE *inFile = fopen(inFileName, "r");
  FILE *outFile = fopen(outFileName, "w");

  while(fgets(inBuf, 500, inFile)){
    char inChar;
    int inPos = 0;
    char outChar;
    int  outPos = 0;
    int currentCol = 0;
    int inQuote = 0;

    while(inChar = inBuf[inPos]){
      if(inChar == '\0')break;
      // quote
      if(inChar == '"' && inQuote == 0){
	inQuote = 1;
      }
      if(inChar == '"' && inQuote == 1){
	inQuote = 0;
      }
      
      // separator (ignore when inside the quotation)
      if(inChar == ',' && inQuote == 0){
	currentCol++;
      }
      // extract target
      int extractTarget = 0;
      for(int i=0; i < numOfCols; i++){
	if(colNums[i] == currentCol){
	  extractTarget = 1;
	  break;
	}
      }

      if(extractTarget == 1){
	if(! ( (outPos == 0 && inChar == ',') || inChar == '\n')){
	  outBuf[outPos] = inChar;
	  outPos++;
	}
      }
      
      inPos++;
    }
    outBuf[outPos] = '\n';
    outPos++;
    outBuf[outPos] = '\0';
    
    fputs(outBuf, outFile);
  }
  
  fclose(inFile);
  fclose(outFile);

}

int main(int argc, char * argv[]){
  FILE *inFile;
  FILE *outFile;
  char inBuf[500];
  char outBuf[500];
  int numOfCols = 0;
  int colNums[20];
  char *endPtr;
  // args 1: inFile 2: outFile 3-...: col1, col2
  // TODO: check args

  for(int i=3; i < argc; i++){
    colNums[ i - 3] = (int)strtol(argv[i], &endPtr, 10);
    numOfCols++;
  }

  extractColumns(argv[1], argv[2], numOfCols, colNums, inBuf, outBuf);
}


