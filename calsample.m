function sample = calsample(sampledata,FS)
temp_sample = resample(sampledata,1,FS/11025);%y = resample(x, p, q) ���ö����˲�����ʱ�����н����ز������õ�������y�ĳ���Ϊԭ��������x�ĳ��ȵ�p/q����p��q��Ϊ����������ʱ��Ĭ�ϵز���ʹ��FIR������ƵĿ�����ĵ�ͨ�˲�����
[m,n] = size(temp_sample);
if (n == 2)
    sample = temp_sample(:,1);
else
    sample = temp_sample;
end
end