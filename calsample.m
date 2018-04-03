function sample = calsample(sampledata,FS)
temp_sample = resample(sampledata,1,FS/11025);%y = resample(x, p, q) 采用多相滤波器对时间序列进行重采样，得到的序列y的长度为原来的序列x的长度的p/q倍，p和q都为正整数。此时，默认地采用使用FIR方法设计的抗混叠的低通滤波器。
[m,n] = size(temp_sample);
if (n == 2)
    sample = temp_sample(:,1);
else
    sample = temp_sample;
end
end