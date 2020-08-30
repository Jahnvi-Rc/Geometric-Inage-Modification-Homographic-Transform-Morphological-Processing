I = imread('gearss.png');
bw = im2bw(I);
bwc = imcomplement(bw);
% bws = bwmorph(bwc,'skel',Inf)


bwf = imfill(bw,'holes');
ch = bwconvhull(bw)
stats = regionprops('table', ch, 'Centroid', 'Eccentricity', 'EquivDiameter');
% [centers,radii] = imfindcircles(bwf,[20 25],'ObjectPolarity','bright','Sensitivity',0.9);
% viscircles(center,radii);
bwm = imerode(ch,strel('disk',9));
bwt = imsubtract(bwf,bwm)
bwl=im2bw(bwt);
bwa = bwareaopen(bwl,8);
[L num]=bwlabel(bwa);
bwp = bwmorph(bwa,'shrink');
bwm1 = bwareaopen(bwp,8);
se = strel('disk',1);
bwm2 = imopen(bwm1,se);
bwp1 = bwmorph(bwm2,'shrink');
bwp2 = bwmorph(bwp1,'shrink');
bwp3 = bwmorph(bwp2,'shrink');
bwp4 = bwmorph(bwp3,'shrink');
bwp5 = bwmorph(bwp4,'shrink');
[L num]=bwlabel(bwp1)

bb= bwperim(bwp1);
imshow(bwp1)
bwlabel(bb)
pixl = regionprops('table', bb, 'PixelIdxList');
hold on 
r= (stats.EquivDiameter)/2;
x =stats.Centroid(1)
y =stats.Centroid(2)
circum = 2*3.14*r;
each_circ = circum/12;
theta = 0 : (2 * pi / 10000) : (2 * pi);
pline_x = r * cos(theta) + x;
pline_y = r * sin(theta) + y;
plot(pline_x, pline_y, '-');
T = pi

x2 = fix(x+r * cos(theta));
y2 = fix(y + r * sin(theta));

% pixel_is_white = ~logical(bb(x2,y2));
% res = find(pixel_is_white==1)
hold off

% [xgrid, ygrid] = meshgrid(1:size(ch,2), 1:size(ch,1));
% mask = ((xgrid-x).^2 + (ygrid-y).^2) <= r.^2;
% values = ch(mask);
% result = find(values==0);
% diff_res=diff(result)
% plot(result)