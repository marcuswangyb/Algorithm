#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main(int argc,char** argv)
{
    FILE *fin = fopen(".\\etc\\A-small-practice.in","r");
    if(fin == NULL)
        printf("error\n");
    int roundT=0;
    fscanf(fin,"%d",&roundT);
    printf("%d\n",roundT);

    FILE *fout = fopen(".\\etc\\A-small-practice.out","w");

    for(int i = 0; i < roundT;i ++){
        int row1,row2;
        int line1[4];
        int line2[4];
        int tmp[4];
        fscanf(fin,"%d",&row1);
        for(int j = 0;j < row1-1;j ++)
            fscanf(fin,"%d%d%d%d",&tmp[0],&tmp[1],&tmp[2],&tmp[3]);
        fscanf(fin,"%d%d%d%d",&line1[0],&line1[1],&line1[2],&line1[3]);
        for(int j = row1;j < 4;j ++)
            fscanf(fin,"%d%d%d%d",&tmp[0],&tmp[1],&tmp[2],&tmp[3]);

        fscanf(fin,"%d",&row2);
        for(int j = 0;j < row2-1;j ++)
            fscanf(fin,"%d%d%d%d",&tmp[0],&tmp[1],&tmp[2],&tmp[3]);
        fscanf(fin,"%d%d%d%d",&line2[0],&line2[1],&line2[2],&line2[3]);
        for(int j = row2;j < 4;j ++)
            fscanf(fin,"%d%d%d%d",&tmp[0],&tmp[1],&tmp[2],&tmp[3]);

        int cards = 0;
        int cardnum = 0;
        for(int a = 0;a < 4;a ++)
            for(int b = 0;b < 4;b ++)
                if(line1[a] == line2[b])
                {
                    cards++;
                    cardnum = line1[a];
                }
        if(cards == 1)
            fprintf(fout,"Case #%d: %d\n",i+1,cardnum);
        else if(cards > 1)
            fprintf(fout,"Case #%d: Bad magician!\n",i+1);
        else
            fprintf(fout,"Case #%d: Volunteer cheated!\n",i+1);
    }

    fclose(fin);
    fclose(fout);

    printf("success\n");
}