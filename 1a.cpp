#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

int main(int argc, char *argv[])
{
    FILE *file;
    int height=512,width=512;
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
    unsigned char InputImage[height][width][BytesPerPixel];
    unsigned char WarpImage[height][width][BytesPerPixel];
    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(InputImage, sizeof(unsigned char), height*width*BytesPerPixel, file);
    fclose(file);
    int i,j,k,v,y,M,pyth=width/2;
    float u;
    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    int h = height/2;
    int temp = pow((pyth*pyth-(pyth-i-1)*(pyth-i-1)),0.5);
    for(i=h;i<height;i++)
    {
        M=temp;
        for(j=pyth;j<width-(pyth-M);j++)
        {
            for(k=0;k<3;k++) 
            {
                u= (float(pyth)/(float)(M)*(float)(j-pyth))+pyth;
                y = floor(u);
                v = u - floor(u);
                
                WarpImage[i][j][k] = InputImage[i][y+1][k]*v+InputImage[i][y][k]*(1-v);
            }
        }
    }
    for (i=h;i<height;i++)
    {
        M=temp;
        for(j=0;j<M;j++)
        {
            for(k=0;k<3;k++)
            {

                u = ((float)pyth/(float)(M)*(float)j);
                y = floor(u);
                v = u-floor(u);
                
                WarpImage[i][j+pyth-M][k] = InputImage[i][y][k]*(1-v)+InputImage[i][y+1][k]*v;
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
                u = ((float)pyth/(float)j*(float)(M));
                y = floor(u);
                v = u-floor(u);
                WarpImage[i][j+(pyth-1)-M][k]=InputImage[i][y][k]*(1-v)+v*InputImage[i][y+1][k];

            }
        }
    }
    for (i=0;i<h;i++) 
    {
        M=temp;
        for (j=pyth;j<(pyth+M);j++) 
        {
            for(k=0;k<3;k++)
            {
                u=((float)pyth/(float)(M))*(float)(j- pyth)+pyth;
                y=floor(u);
                v=u-floor(u);
                WarpImage[i][j][k]=InputImage[i][y][k]*(1-v)+InputImage[i][y+1][k]*v;
            }
        }
    }
    ////Write Image////
    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(WarpImage, sizeof(unsigned char), height*width*BytesPerPixel, file);
    fclose(file);
    return 0;
}