%%%%%%%%%%%
% 二值均可调用
%%%%%%%%%%%

function TT2=Clearer1(Uf1)
 f=Uf1;

 [m,n,q]=size(f);
 for x=1:m
    for y=1:n  
        if (f(x,y)<=128)%判断该点像素为黑
            f(x,y)=0;
        else
            f(x,y)=255;
        end
     end
 end
TT2=f;
% figure;imshow(TT2);
% % imwrite(l,'HONGdanghui.bmp','bmp');
% imwrite(TT2,'HDH.bmp');