%%%%%%%%%%%
% ��ͨ�����
%%%%%%%%%%%
function TT2=Clearer(Uf1)

 ff=imfill(Uf1,'holes');%��f���п׶����
% subplot(325),imshow(ff);
%  title('��f���׶����ͼ��');
 
 fc=imclearborder(Uf1,8);%����߽磬2ά8�ڽ�
%  subplot(326),imshow(fc);
%  title('��f����߽���ͼ��');
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
se=strel('square',3);%�߳�Ϊ3�ķ��νṹԪ��
%  subplot(121),imshow(f);
%  title('ԭʼͼ��');
A=imerode(f1,se);%��ʴ
%  subplot(122),imshow(A);
%  title('��ʴ���ԭʼͼ��');
 fo=imopen(f1,se);
%  figure,subplot(221),imshow(fo);
%  title('ʹ��square(3)���������ͼ��');
%  
 fc=imclose(f1,se);
%  subplot(222),imshow(fc);
%  title('ʹ��square�ղ������ͼ��');
%  
 foc=imclose(fo,se);
%  subplot(223),imshow(foc);
%  title('ʹ��square(3)�ȿ���ղ������ͼ��')
%  
 fco=imopen(fc,se);
%  subplot(224),imshow(fco);
%  title('ʹ��square(3)�ȱպ󿪲������ͼ��');
 
 TT=foc;
 thresh = graythresh(TT);     %�Զ�ȷ����ֵ����ֵ��

TT1 = im2bw(TT,thresh);       %��ͼ���Զ���ֵ�����ɡ�
TT2=imopen(TT1,se);
% imwrite(TT2,'erzhi.bmp','bmp');
% figure;imshow(TT2); title('TT2');
% 
% TT3(:,:,1)=TT2(:,:);
% TT3(:,:,2)=TT2(:,:);
% TT3(:,:,3)=TT2(:,:);
% imwrite(TT3,'erzhii.jpg','jpg');
% figure;image(TT3); title('TT3');
