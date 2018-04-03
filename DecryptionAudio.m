function varargout = DecryptionAudio(varargin)
% DECRYPTIONAUDIO MATLAB code for DecryptionAudio.fig
%      DECRYPTIONAUDIO, by itself, creates a new DECRYPTIONAUDIO or raises the existing
%      singleton*.
%
%      H = DECRYPTIONAUDIO returns the handle to a new DECRYPTIONAUDIO or the handle to
%      the existing singleton*.
%
%      DECRYPTIONAUDIO('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in DECRYPTIONAUDIO.M with the given input arguments.
%
%      DECRYPTIONAUDIO('Property','Value',...) creates a new DECRYPTIONAUDIO or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before DecryptionAudio_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to DecryptionAudio_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help DecryptionAudio

% Last Modified by GUIDE v2.5 22-Nov-2017 16:00:06

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @DecryptionAudio_OpeningFcn, ...
                   'gui_OutputFcn',  @DecryptionAudio_OutputFcn, ...
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


% --- Executes just before DecryptionAudio is made visible.
function DecryptionAudio_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to DecryptionAudio (see VARARGIN)

% Choose default command line output for DecryptionAudio
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes DecryptionAudio wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = DecryptionAudio_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output; 

function TQQXSY_Callback(hObject, eventdata, handles)
% hObject    handle to TQQXSY (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% --- Executes on button press in tiquyinpin.
m=imread('I1.bmp');
c=imread('audio_watermarked.bmp');
[Mm,Nm]=size(m);	  %确定水印图像的大小
[Mc,Nc]=size(c);	  %确定载体图像的大小
x = ones(Mm,Nm,'uint8');  %预分配提取图像空间
cx = 1;
cy = 1;
for i=1:Mm
    for j=1:Nm
        for t = 1:8
            x(i,j)=bitset(x(i,j),t,bitget(c(cx,cy),1));
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
axes(handles.axes2); 
imshow(x,[]);
title('提取的水印图');
imwrite(x,'I11.bmp','bmp');

function recoverpicture_Callback(hObject, eventdata, handles)
% hObject    handle to recoverpicture (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%利用4幅全息图获取到达CCD的物光复振幅
global N
global xiao
Ar=170.3963;
 N=700;          %设定取样数
pix=0.00465;      %设定CCD像素间隔
L=N*pix;         %CCD宽度 L=4.76;
z0=1000;         % 衍射距离 mm(可以根据需要修改)
h=0.532e-3;       %光波长 mm(可以根据需要修改)可见光的波长范围780～390nm，波长=速度/频率
k=2*pi/h;         %波数
L0=sqrt(h*z0*N); %FFT计算时同时满足振幅及相位取样条件的物光场宽度
I1=imread('I11.bmp');
I2=imread('I2.bmp');
I3=imread('I3.bmp');
I4=imread('I4.bmp');
I1=double(I1);
I2=double(I2);
I3=double(I3);
I4=double(I4);
U=((I4-I2)+i*(I1-I3))/4/Ar;%到达CCD的共轭物光复振幅
 
%1-IFFT重建
%---------------菲涅耳衍射的S-IFFT计算起始
n=1:N;
x=-L/2+L/N*(n-1);                       
y=x;
[yy,xx] = meshgrid(y,x); 
Fresnel=exp(-i*k/2/z0*(xx.^2+yy.^2));
f2=U.*Fresnel; 
Uf=ifft2(f2,N,N);%对N*N点的离散函数f2作IFFT计算
 
x=-L0/2+L0/N*(n-1);                     
y=x;
[yy,xx] = meshgrid(y,x); 
phase=exp(-i*k*z0)/(i*h*z0)*exp(i*k/2/z0*(xx.^2+yy.^2));%菲涅耳衍射积分号前的相位因子
Uf=Uf.*phase;
T=L/N;          %CCD取样间隔
Us=Uf*T*T;      %二维离散变换量值补偿
%---------------菲涅耳衍射的S-IFFT计算结束
Uh=[0:N-1]-N/2;Vh=[0:N-1]-N/2;   
[mh,nh]=meshgrid(Uh,Vh);
T=L0/N;        % 物光场像素间距 mm;
aaa=abs(Us);
% aaa=abs(Uf);
Imax=max(max(aaa));
cjt=uint8(aaa./Imax*255);%变换为极大值255的整型数
imwrite(cjt,'cjt.bmp','bmp');
xiao = wkeep(cjt,[512 512],[94 94]);
imwrite(xiao,'xiao.bmp');
axes(handles.axes3); imshow(xiao);title('恢复音频图片');

% --- Executes on button press in playmusic.
function playmusic_Callback(hObject, eventdata, handles)
% hObject    handle to playmusic (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global xiao;
global player
Y2=double(xiao);
sample1=Y2(:);
maxs=max(sample1);
sample2=sample1/maxs;
% sample3=mapminmax(sample2);
maxz=0.9194;
sample3=(sample2*2.0-1.0)*maxz;
player = audioplayer(sample3, 11025);
play(player);
% sound(sample3,11025);
Y3=reshape(sample3,512,512);


% --- Executes on button press in stop.
function stop_Callback(hObject, eventdata, handles)
% hObject    handle to stop (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global player
stop(player);
