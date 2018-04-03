  function varargout = EncryptionAudio(varargin)
% ENCRYPTIONAUDIO MATLAB code for EncryptionAudio.fig
%      ENCRYPTIONAUDIO, by itself, creates a new ENCRYPTIONAUDIO or raises the existing
%      singleton*.
%
%      H = ENCRYPTIONAUDIO returns the handle to a new ENCRYPTIONAUDIO or the handle to
%      the existing singleton*.
%
%      ENCRYPTIONAUDIO('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in ENCRYPTIONAUDIO.M with the given input arguments.
%
%      ENCRYPTIONAUDIO('Property','Value',...) creates a new ENCRYPTIONAUDIO or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before EncryptionAudio_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to EncryptionAudio_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help EncryptionAudio

% Last Modified by GUIDE v2.5 22-Nov-2017 17:00:26

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @EncryptionAudio_OpeningFcn, ...
                   'gui_OutputFcn',  @EncryptionAudio_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before EncryptionAudio is made visible.
function EncryptionAudio_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to EncryptionAudio (see VARARGIN)

% Choose default command line output for EncryptionAudio
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes EncryptionAudio wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = EncryptionAudio_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;

function selectmusic_Callback(hObject, eventdata, handles)
% hObject    handle to selectmusic (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global y1;
[filename pathname filter] = uigetfile('*.wav');
if  filter ~= 0
    y1= fullfile(pathname,filename);  
end
function playmusic_Callback(hObject, eventdata, handles)
% hObject    handle to playmusic (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global y1;
global player
% [y,fs]=wavread(y1,[6980000,8028575]);%512图片大小所需音频,1048576
[y,fs]=audioread(y1,[3200000,4248575]);%512图片大小所需音频,1048576
player = audioplayer(y, fs);
play(player);

% --- Executes on button press in stopmusic.
function stopmusic_Callback(hObject, eventdata, handles)
% hObject    handle to stopmusic (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global player
%512图片大小所需音频,1048576
stop(player); 
% --- Executes on button press in signverity.
function turnpicture_Callback(hObject, eventdata, handles)
% hObject    handle to turnpicture (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global maxz;
global y1;
% [y,fs]=wavread(y1,[6980000,8028575]);%512图片大小所需音频,1048576
[y,fs]=audioread(y1,[3200000,4248575]);%512图片大小所需音频,1048576
 fs=44100;
sample = calsample(y,fs);%将双声道编程单声道并且频率变为最低11025,wav最低采样频率为11025HZ
fs=fs/(fs/11025);
z1=reshape(sample,512,512);%变成512*512图片的大小
% z1=reshape(sample,256,256);%变成256*256图片的大小
maxz=max(max(abs(z1)));
z2=z1/maxz;
% 归一化
z3=(z2+1.0)/2;
% figure (1),imshow(z1);title('-1-1音频图片');%显示原始音频图片
axes(handles.axes1),imshow(z3);title('音频图片');%显示音频图片
% imwrite(z3,'YPP1.bmp','bmp');%将图片保存为bmp格式   
% a=imread('YPP1.bmp');
a=im2double(z3);
b=zeros(700,700);
b(94:605,94:605)=a;
imwrite(b,'zengjia.bmp');
% --- Executes on button press in SELECTpicture.

function SELECTpicture_Callback(hObject, eventdata, handles)
% hObject    handle to SELECTpicture (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global X0;
global filename;
[filename pathname filter] = uigetfile('*.bmp;*.jpg;*.png;*.tif;*.gif;*.avi');
% [filename pathname filter] = uigetfile({'*.bmp';'*.jpg';'*.png'},'选择图片');
if  filter ~= 0
    X0= imread([pathname,filename]);  
end
axes(handles.axes2); imshow(X0,[]);title('音频图片');


% --- Executes on button press in scqxt.
function scqxt_Callback(hObject, eventdata, handles)
% hObject    handle to scqxt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global N;
global pix;
global z0;
global X0;
global Ar
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% 调整大小使图片成为正方形大小
[M0,N0]=size(X0);
N1=min(M0,N0);
X1=zeros(N1,N1);
X1(1:N1,1:N1)=X0(1:N1,1:N1);
 
N=700;          %设定取样数
pix=0.00465       %设定CCD像素间隔
L=N*pix          %CCD宽度
X1=imresize(X1,N/N1);
 
z0=1000;         % 衍射距离 mm(可以根据需要修改)
h=0.532e-3;       %光波长 mm(可以根据需要修改)
k=2*pi/h;
L0=h*z0*N/L;     %S-FFT计算时初始场宽度mm
 
Y=double(X1);
bb=rand(N,N)*pi*2;
X=Y.*exp(i.*bb);%叠加随机相位噪声模拟散射物体
 
Uh=[0:N-1]-N/2;Vh=[0:N-1]-N/2;   
[mh,nh]=meshgrid(Uh,Vh);
T=L0/N;        % 物光场像素间距 mm;
figstr=strcat('物平面宽度=',num2str(L0),'mm');
% figure(1),
% imagesc(Uh*T,Vh*T,abs(X));colormap(gray); xlabel(figstr);title('物平面图像'); 
U0=double(X);
%% 菲涅耳衍射的S-FFT计算起始
n=1:N;
x=-L0/2+L0/N*(n-1);                     
y=x;
[yy,xx] = meshgrid(y,x); 
Fresnel=exp(i*k/2/z0*(xx.^2+yy.^2));
f2=U0.*Fresnel; 
Uf=fft2(f2,N,N);%对N*N点的离散函数f2作FFT计算
Uf=fftshift(Uf);%将FFT计算结果进行整序
x=-L/2+L/N*(n-1);                       
y=x;
[yy,xx] = meshgrid(y,x); 
phase=exp(i*k*z0)/(i*h*z0)*exp(i*k/2/z0*(xx.^2+yy.^2));%菲涅耳衍射积分号前方的相位因子
Uf=Uf.*phase;
Uf=Uf*T*T;      %二维离散变换量值补偿
%% 菲涅耳衍射的S-FFT计算结束 
%---------------4步相移形成4幅全息图
Ar=mean(mean(abs(Uf)));%将衍射场振幅平均值设为参考光振幅
figstr1=strcat('全息图宽度=',num2str(L),'mm');
%---------------------------------0相移
Ur=Ar;
Uh=Ur+Uf;
Ih=Uh.*conj(Uh);%浮点型数字全息图
Imax=max(max(Ih));
I1=uint8(Ih./Imax*255);%变换为极大值255的整型数
imwrite(I1,'I1.bmp','bmp'); 
axes(handles.axes2);imshow(I1,[]);colormap(gray);xlabel(figstr1);axis equal;axis tight;title('全息图');
%% ---------------------------------pi/2相移
Ur=Ar*exp(i*pi/2);
Uh=Ur+Uf;
Ih=Uh.*conj(Uh);%浮点型数字全息图
Imax=max(max(Ih));
I2=uint8(Ih./Imax*255);%变换为极大值255的整型数
imwrite(I2,'I2.bmp','bmp');
% figure(4);imshow(I2,[]);colormap(gray);xlabel(figstr1);axis equal;axis tight;title('全息图I2');
%% ---------------------------------pi相移
Ur=Ar*exp(i*pi);
Uh=Ur+Uf;
Ih=Uh.*conj(Uh);%浮点型数字全息图
Imax=max(max(Ih));
I3=uint8(Ih./Imax*255);%变换为极大值255的整型数
imwrite(I3,'I3.bmp','bmp'); 
% figure(5);imshow(I3,[]);colormap(gray);xlabel(figstr1);axis equal;axis tight;title('全息图I3');
%% ---------------------------------3*pi/2相移
Ur=Ar*exp(i*3*pi/2);
Uh=Ur+Uf;
Ih=Uh.*conj(Uh);%浮点型数字全息图
Imax=max(max(Ih));
I4=uint8(Ih./Imax*255);%变换为极大值255的整型数
imwrite(I4,'I4.bmp','bmp'); 
% --- Executes on button press in WatermarkQR.
% --- Executes on button press in select_vector.

function selectvector_Callback(hObject, eventdata, handles)
% hObject    handle to selectvector (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
X = imread('taiwan.jpg');
axes(handles.axes3); imshow(X,[]);title('载体图像');

% --- Executes on button press in watermark.
function watermark_Callback(hObject, eventdata, handles)
% hObject    handle to watermark (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
X = imread('taiwan.jpg');
% figure(1); imshow(X,[]);title('载体图像');
imwrite(X,'taiwan.bmp','bmp')
c = imread('taiwan.bmp');
% c=rgb2gray(Z);  %读入载体图像
m=imread('I1.bmp');     %读入水印图像
% figure(2); imshow(m,[]);title('全息水印图像');
[Mm,Nm]=size(m);	  %确定水印图像的大小
[Mc,Nc]=size(c);	  %确定载体图像的大小
cx = 1;
cy = 1;
for i=1:Mm
    for j=1:Nm
        for t = 1:8
            c(cx,cy)=bitset(c(cx,cy),1,bitget(m(i,j),t));
            cy = cy + 1;
            cy = mod(cy,Nc);
            if cy == 0         %载体横座标移动到行末
               cy = Nc;
            end
            if cy == 1         %载体换行
               cx = cx + 1;
            end
        end
    end
end
imwrite(c,'audio_watermarked.bmp','bmp');
axes(handles.axes4);imshow(c,[]);title('嵌入水印后的载体图像');


% --- Executes on button press in pushbutton12.
function pushbutton12_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton12 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
open('C:\Users\Administrator\Desktop\10.10\SM2_Sign_Verify\Debug\SM2_Sign_Verify.exe');