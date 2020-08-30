% BW1 = imread('pcb_toned.png');
% figure
% imshow(BW1)
% SE = strel('arbitrary',eye(7))
% BW2 = imerode(BW1,SE);
% figure
% imshow(BW2)

I = imread('pcb_toned.png');
imshow(I)
bw = im2bw(I,0.5)
bwc = imcomplement(bw);
imshow(bwc)
% bwf = imfill(bwc,'holes');
% ch = bwconvhull(bw)
% bwm = imerode(bw,strel('disk',9));
bwe = bwareaopen(bw, 15);
imshow(bwe)
bwt = imsubtract(bw,bwe);
imshow(bwt)
% B = bwskel(BW)

% figure;
% imshowpair(BW1,BW2,'montage')
% title('Sobel Filter                                   Canny Filter');
% BW = edge(img,'canny');
% imshow(bwt);
[L num]=bwlabel(bwt)
% img = im2double(img(:,:,1));
% bw = img > .8; %// get a mask of grid lines (approx.)
% bw = imdilate( imerode( bw, ones(2) ), ones(4) ); %// mask for roifill
% nImg = roifill( img, bw );
% imshow(nImg)


% cmodel=(zeros(300,100,1));
% fid=fopen('pcb_img.raw','w+');
% cnt=fwrite(fid,bwt,'uint8');
% fclose(fid);