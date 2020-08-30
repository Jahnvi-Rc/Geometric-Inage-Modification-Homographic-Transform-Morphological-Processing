#include <cmath> 
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;
const int height = 720, width = 480;
const int BytesPerPixel = 3;
const int inc = 250;
const int N = 8;
unsigned char OutputImage[height+2*inc][width*3+2*inc][BytesPerPixel];
int main(int argc, char *argv[])
{
    FILE *file1, *file;
    int BytesPerPixel = 3, byteRange = 256;
    unsigned char img_l[height][width][BytesPerPixel];
    unsigned char img_m[height][width][BytesPerPixel];
    unsigned char img_r[height][width][BytesPerPixel];
    unsigned char result_reversed[height][width][BytesPerPixel];
    if (!(file1=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(img_l, sizeof(unsigned char), height*width*BytesPerPixel, file1);
    fclose(file1);
    if (!(file1=fopen(argv[2],"rb"))) {
        cout << "Cannot open file: " << argv[2] <<endl;
        exit(1);
    }
    fread(img_m, sizeof(unsigned char), height*width*BytesPerPixel, file1);
    fclose(file1);
    if (!(file1=fopen(argv[3],"rb"))) {
        cout << "Cannot open file: " << argv[3] <<endl;
        exit(1);
    }
    fread(img_r, sizeof(unsigned char), height*width*BytesPerPixel, file1);
    fclose(file1);
    //COde
    double hlm[8];
    double hmr[8];
    int count = 0;
    int i,j,k;
    double val1,val2,val3,val4;
    int u=0,v=0,uv = 0, uv1 = 0, u1v1 = 0, u1v = 0, final;
    for(i=-inc;i<(height+inc);i++)
    {
        for(j=-inc;j<(3*width)+inc;j++)
        {
            for(k=0;k<BytesPerPixel;k++)
            {
                val1 = (hlm[2]+((double)j*hlm[1])+((double)i)*hlm[0])/(1+((double)j*hlm[7])+((double)i)*hlm[6]);
                val2 = (hlm[5]+((double)j*hlm[4])+((double)i)*hlm[3])/(1+((double)j*hlm[7])+((double)i)*hlm[6]);
                val3 = (hmr[2]+((double)j*hmr[1])+((double)i)*hmr[0])/(1+((double)j*hmr[7])+((double)i)*hmr[6]);
                val4 = (hmr[5]+((double)j*hmr[4])+((double)i)*hmr[3])/(1+((double)j*hmr[7])+((double)i)*hmr[6]);
                if((val4<3*width)&(val3<height)&(val4>=2*width)&(val3>=0))
                {
                    count++;
                    u = floor(val3);
                    v = floor(val4 - 2 * width);
                    u1v1 = (int)img_r[u+1][v+1][k];
                    uv1 = (int)img_r[u+1][v][k];
                    uv = (int)img_r[u][v][k];
                    u1v = (int)img_r[u][v+1][k];
                    final =uv1*((val3-u))*(1-(val4-2*width-v))+u1v1*((val3-u))*((val4-2*width-v))+(int)uv*(1-(val3-u))*(1-(val4-2*width-v))+u1v*(1-(val3-u))*((val4-2*width-v));
                }
                else if((val2<width)&(val1<height)&(val1>=0)&(val2>=0))
                {
                    v = floor(val2);
                    u = floor(val1);
                    u1v1 = (int)img_l[u+1][v+1][k];
                    uv1 = (int)img_l[u+1][v][k];
                    uv = (int)img_l[u][v][k];
                    u1v = (int)img_l[u][v+1][k];
                    final = uv1*(val1-u)*(1-(val2-v))+(int)uv*(1-(val1-u))*(1-(val2-v))+u1v*(1-(val1-u))*(val2-v)+u1v1*(val1-u)*(val2-v);
                }
                else
                    final = 0;
                if ((i>=0)&(i<height)&(j>=width)&(j<2*width))
                        OutputImage[i+inc][j+inc][k] = img_m[i][j-width][k];  
                else
                    OutputImage[i+inc][j+inc][k] =(char)(int(final));
            }
        }
    }
    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(OutputImage, sizeof(unsigned char),height*height*BytesPerPixel, file);
    fclose(file);
    return 0;
}