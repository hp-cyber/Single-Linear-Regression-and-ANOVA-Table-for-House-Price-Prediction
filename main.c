#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int countLines(FILE *fp){

  char buf[BUFSIZ];
  int numberLines = 0;

  long int start = ftell(fp);

  while(fgets(buf, BUFSIZ, fp)){
    ++numberLines;
  }

  fseek(fp, start, SEEK_SET);

  return numberLines;
}

int main(int argc, char **argv){

    FILE *fp = fopen(argv[1],"r");

    int numberLines = countLines(fp);

    double n[numberLines][2];

    double arrayX[100], arrayY[100];

    double meanX, meanY, sumX, sumY, differenceX, differenceY, difference, Sx, Sy;

    while(!feof(fp)){

        for(int i = 0; i < numberLines; i++){

            fscanf(fp, "%lf %lf ", &n[i][0], &n[i][1]);

            sumX += n[i][0];
            arrayX[i] = n[i][0];

            sumY += n[i][1];
            arrayY[i] = n[i][1];

            meanX = sumX / numberLines;
            meanY = sumY / numberLines;
        }
    }

    for(int i = 0; i < numberLines; i++){

        differenceX += pow((arrayX[i] - meanX), 2);
        differenceY += pow((arrayY[i] - meanY), 2);

    }

    Sx = sqrt(differenceX / numberLines);
    Sy = sqrt(differenceY / numberLines);


    for(int i = 0; i < numberLines; i++){

        difference += (((arrayX[i] - meanX) / Sx) * ((arrayY[i] - meanY) / Sy));

    }

    //Correlation
    double r = difference / numberLines;

    double b1, b0;
    b1 = r * Sy / Sx;
    b0 = meanY - b1 * meanX;

    printf(" \n");
    printf("y = %lf + %lfx \n", b0, b1);
    printf(" \n");

    double sumOfSquredXY, sx, sy, multiXY, SST;
    for(int i = 0; i < numberLines; i++){
        sumOfSquredXY += arrayX[i] * arrayY[i];
        sx += arrayX[i];
        sy += arrayY[i];
        multiXY = sx * sy;
        SST += pow((arrayY[i] - meanY), 2);
    }
    double SSxy = sumOfSquredXY - multiXY / numberLines;

    double SSR = b1 * SSxy;

    double SSE = SST - SSR;

    int DFR = 1;

    double MSR = SSR / DFR;

    int DFE = numberLines - DFR - 1;

    int DFT = numberLines - 1;

    double MSE = SSE / DFE;

    double F = MSR / MSE;

    printf("Source     DF     AdjSS         AdjMS       F-value\n");
    printf("Regression  %d  %lf  %lf  %lf\n", DFR, SSR, MSR, F);
    printf("Error       %d  %lf   %lf\n", DFE, SSE, MSE);
    printf("Total      %d  %lf", DFT, SST);
    printf(" \n");

    fclose(fp);
    return 0;
}

