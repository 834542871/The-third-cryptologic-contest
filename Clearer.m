%%%%%%%%%%%
% 连通域调用
%%%%%%%%%%%
function TT2=Clearer(Uf1)

 ff=imfill(Uf1,'holes');%对f进行孔洞填充
% subplot(325),imshow(ff);
%  title('对f填充孔洞后的图像');
 
 fc=imclearborder(Uf1,8);%清除边界，2维8邻接
%  subplot(326),imshow(fc);
%  title('对f清除边界后的图像');
%  
 
 
 J=ff;
 K1=medfilt2(J);
K2=medfilt2(J,[5 5]);
K3=medfilt2(J,[7 7]);
K4=medfilt2(J,[9 9]);
% subplot(233);
% imshow(K1);
% subplot(234);
% imshow(K2);
% subplot(235);
% imshow(K3);
% subplot(236);
% imshow(K4);

f1=K2;
se=strel('square',3);%边长为3的方形结构元素
%  subplot(121),imshow(f);
%  title('原始图像');
A=imerode(f1,se);%腐蚀
%  subplot(122),imshow(A);
%  title('腐蚀后的原始图像');
 fo=imopen(f1,se);
%  figure,subplot(221),imshow(fo);
%  title('使用square(3)开操作后的图像');
%  
 fc=imclose(f1,se);
%  subplot(222),imshow(fc);
%  title('使用square闭操作后的图像');
%  
 foc=imclose(fo,se);
%  subplot(223),imshow(foc);
%  title('使用square(3)先开后闭操作后的图像')
%  
 fco=imopen(fc,se);
%  subplot(224),imshow(fco);
%  title('使用square(3)先闭后开操作后的图像');
 
 TT=foc;
 thresh = graythresh(TT);     %自动确定二值化阈值；

TT1 = im2bw(TT,thresh);       %对图像自动二值化即可。
TT2=imopen(TT1,se);
% imwrite(TT2,'erzhi.bmp','bmp');
% figure;imshow(TT2); title('TT2');
% 
% TT3(:,:,1)=TT2(:,:);
% TT3(:,:,2)=TT2(:,:);
% TT3(:,:,3)=TT2(:,:);
% imwrite(TT3,'erzhii.jpg','jpg');
% figure;image(TT3); title('TT3');
