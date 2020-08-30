#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

int main(int argc, char *argv[])
{
    FILE *file;
    int height,width;
    int BytesPerPixel;
    if (argc < 3){
        cout << "Error" << endl;
        cout << "Retry" << endl;
        return 0;
    }
    if (argc < 4){
        BytesPerPixel = 1;
    }
    else {
        BytesPerPixel = atoi(argv[3]);
        if (argc >= 5) {
            height = atoi(argv[4]);
            width = atoi(argv[5]);
        }
    }
    unsigned char OutputImage[height][width][BytesPerPixel];
    unsigned char WarpImage[height][width][BytesPerPixel];
    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(WarpImage, sizeof(unsigned char), height*width*BytesPerPixel, file);
    fclose(file);
    int i,j,k,v,y,M,pyth=width/2;
    float u;
    //////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    int h = height/2;
    int temp = pow((pyth*pyth-(pyth-i-1)*(pyth-i-1)),0.5);
    for(i=h;i<height;i++)
     {
        M=temp;
        for (j=pyth;j<width;j++) 
        {
            for(k=0;k<3;k++)
            {
                u= (float(M)/(float)(pyth)*(float)(j-pyth))+pyth;
                v = u - floor(u);
                y = floor(u);
                OutputImage[i][j][k]=WarpImage[i][y][k]*(1-v)+WarpImage[i][y+1][k]*v;
            }
        }
    }
    for(i=0;i<h;i++) 
    {
        M=temp;
        for(j= pyth;j<width;j++) 
        {
            for(k=0;k<3;k++) 
            {
                u = ((float)M/(float)pyth)*(float)(j- pyth)+pyth;
                v = u - floor(u);
                y = floor(u);
                OutputImage[i][j][k]=WarpImage[i][y+1][k]*v+WarpImage[i][y][k]*(1-v);
            }
        }
    }
    for(i=0;i<h;i++)
    {
        M=temp;
        for(j=0;j<M+1;j++)
        {
            for(k=0;k<3;k++) 
            {
                u = ((float)M/(float)pyth)*(float)j;
                y = floor(u);
                v = u - floor(u);
                
                OutputImage[i][j][k]=WarpImage[i][(pyth-M+y)+1][k]*v+WarpImage[i][(pyth-M+y)][k]*(1-v);
            }
        }
    }
    for(i=h;i<height;i++) 
    {
        M=temp;
        for(j=0;j<h;j++)
        {
            for(k=0;k<3;k++)
            {
                u= ((float)M/(float)(pyth)*(float)j)+pyth-M;
                y = floor(u);
                v = u - floor(u);
                
                OutputImage[i][j][k]=WarpImage[i][y+1][k]*v+WarpImage[i][y][k]*(1-v);
            }
        }
    }
    
    ///////////////////////// END /////////////////////////
    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(OutputImage, sizeof(unsigned char),height*width*BytesPerPixel, file);
    fclose(file);
    return 0;
}