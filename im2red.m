function redl=im2red(I2)
% I2=imread('erzhi.bmp');
%Clearer.m先将图像预处理（填充）
%对二值图取反，白（党徽）变红，在去除黑色背景（变白）
%将全息逆变换得到的灰度图，转二值图（反色），转彩色图（白255变红，去黑色背景），最终复原出红色党徽。
d = size(I2);%图的长宽得到
I2=~I2;
temp = zeros(d(1),d(2),3);%构建彩色图的三维矩阵
temp(:, :,1 ) = I2;%将图信息赋给彩图的红色分量
y = temp;
% figure, subplot(121), imshow(I2), subplot(122), imshow(y)
%imwrite(y,'HONG1.bmp','bmp')

i=y;
[m,n,q]=size(i);

% for z=1:q
for x=1:m
    for y=1:n
        
        if (i(x,y,1)==0 && i(x,y,2)==0 && i(x,y,3)==0)%判断该点像素为黑
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