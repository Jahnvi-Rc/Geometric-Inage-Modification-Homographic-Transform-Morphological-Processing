clc;
clear all;
[Img1] = imread('mi.png');
[Img2] = imread('ri.png');
cpselect(Img1,Img2)
x0=834.0;
x1=1343.981;
x2=979.149;
x3=1111.822;
y0=522.125;
y1=687.125;
y2=859.125;
y3=870.562;
u0=45.125;
u1=218.722;
u2=66.125;
u3=190.265;
v0=187.635;
v1=335.375;
v2=523.625;
v3=640.998;
A = [u0 v0 1 0 0 0 -(u0*x0) -(v0*x0);
     0 0 0 u0 v0 1 -(u0*y0) -(v0*y0);
     u1 v1 1 0 0 0 -(u1*x1) -(v1*x1);
     0 0 0 u1 v1 1 -(u1*y1) -(v1*y1);
     u2 v2 1 0 0 0 -(u2*x2) -(v2*x2);
     0 0 0 u2 v2 1 -(u2*y2) -(v2*y2);
     u3 v3 1 0 0 0 -(u3*x3) -(v3*x3);
     0 0 0 u3 v3 1 -(u3*y3) -(v3*y3)];
 B = [x0; y0; x1; y1; x2; y2; x3; y3];
 H_r= A\B;
 H_mr = [H_initial(1) H_initial(2) H_initial(3);
         H_initial(4) H_initial(5) H_initial(6);
         H_initial(7) H_initial(8) 1];
 
format long;
H_MR= inv(H_mr)