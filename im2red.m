function redl=im2red(I2)
% I2=imread('erzhi.bmp');
%Clearer.m�Ƚ�ͼ��Ԥ������䣩
%�Զ�ֵͼȡ�����ף����գ���죬��ȥ����ɫ��������ף�
%��ȫϢ��任�õ��ĻҶ�ͼ��ת��ֵͼ����ɫ����ת��ɫͼ����255��죬ȥ��ɫ�����������ո�ԭ����ɫ���ա�
d = size(I2);%ͼ�ĳ���õ�
I2=~I2;
temp = zeros(d(1),d(2),3);%������ɫͼ����ά����
temp(:, :,1 ) = I2;%��ͼ��Ϣ������ͼ�ĺ�ɫ����
y = temp;
% figure, subplot(121), imshow(I2), subplot(122), imshow(y)
%imwrite(y,'HONG1.bmp','bmp')

i=y;
[m,n,q]=size(i);

% for z=1:q
for x=1:m
    for y=1:n
        
        if (i(x,y,1)==0 && i(x,y,2)==0 && i(x,y,3)==0)%�жϸõ�����Ϊ��
           for z=1:q
            i(x,y,z)=255;  end
        end
     end
end
% end
redl=i;
% figure;imshow(redl);
% % imwrite(l,'HONGdanghui.bmp','bmp');
% imwrite(redl,'HONGdanghui.bmp');