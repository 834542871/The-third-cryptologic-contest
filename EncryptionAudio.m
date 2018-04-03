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
% [y,fs]=wavread(y1,[6980000,8028575]);%512ͼƬ��С������Ƶ,1048576
[y,fs]=audioread(y1,[3200000,4248575]);%512ͼƬ��С������Ƶ,1048576
player = audioplayer(y, fs);
play(player);

% --- Executes on button press in stopmusic.
function stopmusic_Callback(hObject, eventdata, handles)
% hObject    handle to stopmusic (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global player
%512ͼƬ��С������Ƶ,1048576
stop(player); 
% --- Executes on button press in signverity.
function turnpicture_Callback(hObject, eventdata, handles)
% hObject    handle to turnpicture (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global maxz;
global y1;
% [y,fs]=wavread(y1,[6980000,8028575]);%512ͼƬ��С������Ƶ,1048576
[y,fs]=audioread(y1,[3200000,4248575]);%512ͼƬ��С������Ƶ,1048576
 fs=44100;
sample = calsample(y,fs);%��˫������̵���������Ƶ�ʱ�Ϊ���11025,wav��Ͳ���Ƶ��Ϊ11025HZ
fs=fs/(fs/11025);
z1=reshape(sample,512,512);%���512*512ͼƬ�Ĵ�С
% z1=reshape(sample,256,256);%���256*256ͼƬ�Ĵ�С
maxz=max(max(abs(z1)));
z2=z1/maxz;
% ��һ��
z3=(z2+1.0)/2;
% figure (1),imshow(z1);title('-1-1��ƵͼƬ');%��ʾԭʼ��ƵͼƬ
axes(handles.axes1),imshow(z3);title('��ƵͼƬ');%��ʾ��ƵͼƬ
% imwrite(z3,'YPP1.bmp','bmp');%��ͼƬ����Ϊbmp��ʽ   
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
% [filename pathname filter] = uigetfile({'*.bmp';'*.jpg';'*.png'},'ѡ��ͼƬ');
if  filter ~= 0
    X0= imread([pathname,filename]);  
end
axes(handles.axes2); imshow(X0,[]);title('��ƵͼƬ');


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
%% ������СʹͼƬ��Ϊ�����δ�С
[M0,N0]=size(X0);
N1=min(M0,N0);
X1=zeros(N1,N1);
X1(1:N1,1:N1)=X0(1:N1,1:N1);
 
N=700;          %�趨ȡ����
pix=0.00465       %�趨CCD���ؼ��
L=N*pix          %CCD���
X1=imresize(X1,N/N1);
 
z0=1000;         % ������� mm(���Ը�����Ҫ�޸�)
h=0.532e-3;       %�Ⲩ�� mm(���Ը�����Ҫ�޸�)
k=2*pi/h;
L0=h*z0*N/L;     %S-FFT����ʱ��ʼ�����mm
 
Y=double(X1);
bb=rand(N,N)*pi*2;
X=Y.*exp(i.*bb);%���������λ����ģ��ɢ������
 
Uh=[0:N-1]-N/2;Vh=[0:N-1]-N/2;   
[mh,nh]=meshgrid(Uh,Vh);
T=L0/N;        % ��ⳡ���ؼ�� mm;
figstr=strcat('��ƽ����=',num2str(L0),'mm');
% figure(1),
% imagesc(Uh*T,Vh*T,abs(X));colormap(gray); xlabel(figstr);title('��ƽ��ͼ��'); 
U0=double(X);
%% �����������S-FFT������ʼ
n=1:N;
x=-L0/2+L0/N*(n-1);                     
y=x;
[yy,xx] = meshgrid(y,x); 
Fresnel=exp(i*k/2/z0*(xx.^2+yy.^2));
f2=U0.*Fresnel; 
Uf=fft2(f2,N,N);%��N*N�����ɢ����f2��FFT����
Uf=fftshift(Uf);%��FFT��������������
x=-L/2+L/N*(n-1);                       
y=x;
[yy,xx] = meshgrid(y,x); 
phase=exp(i*k*z0)/(i*h*z0)*exp(i*k/2/z0*(xx.^2+yy.^2));%������������ֺ�ǰ������λ����
Uf=Uf.*phase;
Uf=Uf*T*T;      %��ά��ɢ�任��ֵ����
%% �����������S-FFT������� 
%---------------4�������γ�4��ȫϢͼ
Ar=mean(mean(abs(Uf)));%�����䳡���ƽ��ֵ��Ϊ�ο������
figstr1=strcat('ȫϢͼ���=',num2str(L),'mm');
%---------------------------------0����
Ur=Ar;
Uh=Ur+Uf;
Ih=Uh.*conj(Uh);%����������ȫϢͼ
Imax=max(max(Ih));
I1=uint8(Ih./Imax*255);%�任Ϊ����ֵ255��������
imwrite(I1,'I1.bmp','bmp'); 
axes(handles.axes2);imshow(I1,[]);colormap(gray);xlabel(figstr1);axis equal;axis tight;title('ȫϢͼ');
%% ---------------------------------pi/2����
Ur=Ar*exp(i*pi/2);
Uh=Ur+Uf;
Ih=Uh.*conj(Uh);%����������ȫϢͼ
Imax=max(max(Ih));
I2=uint8(Ih./Imax*255);%�任Ϊ����ֵ255��������
imwrite(I2,'I2.bmp','bmp');
% figure(4);imshow(I2,[]);colormap(gray);xlabel(figstr1);axis equal;axis tight;title('ȫϢͼI2');
%% ---------------------------------pi����
Ur=Ar*exp(i*pi);
Uh=Ur+Uf;
Ih=Uh.*conj(Uh);%����������ȫϢͼ
Imax=max(max(Ih));
I3=uint8(Ih./Imax*255);%�任Ϊ����ֵ255��������
imwrite(I3,'I3.bmp','bmp'); 
% figure(5);imshow(I3,[]);colormap(gray);xlabel(figstr1);axis equal;axis tight;title('ȫϢͼI3');
%% ---------------------------------3*pi/2����
Ur=Ar*exp(i*3*pi/2);
Uh=Ur+Uf;
Ih=Uh.*conj(Uh);%����������ȫϢͼ
Imax=max(max(Ih));
I4=uint8(Ih./Imax*255);%�任Ϊ����ֵ255��������
imwrite(I4,'I4.bmp','bmp'); 
% --- Executes on button press in WatermarkQR.
% --- Executes on button press in select_vector.

function selectvector_Callback(hObject, eventdata, handles)
% hObject    handle to selectvector (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
X = imread('taiwan.jpg');
axes(handles.axes3); imshow(X,[]);title('����ͼ��');

% --- Executes on button press in watermark.
function watermark_Callback(hObject, eventdata, handles)
% hObject    handle to watermark (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
X = imread('taiwan.jpg');
% figure(1); imshow(X,[]);title('����ͼ��');
imwrite(X,'taiwan.bmp','bmp')
c = imread('taiwan.bmp');
% c=rgb2gray(Z);  %��������ͼ��
m=imread('I1.bmp');     %����ˮӡͼ��
% figure(2); imshow(m,[]);title('ȫϢˮӡͼ��');
[Mm,Nm]=size(m);	  %ȷ��ˮӡͼ��Ĵ�С
[Mc,Nc]=size(c);	  %ȷ������ͼ��Ĵ�С
cx = 1;
cy = 1;
for i=1:Mm
    for j=1:Nm
        for t = 1:8
            c(cx,cy)=bitset(c(cx,cy),1,bitget(m(i,j),t));
            cy = cy + 1;
            cy = mod(cy,Nc);
            if cy == 0         %����������ƶ�����ĩ
               cy = Nc;
            end
            if cy == 1         %���廻��
               cx = cx + 1;
            end
        end
    end
end
imwrite(c,'audio_watermarked.bmp','bmp');
axes(handles.axes4);imshow(c,[]);title('Ƕ��ˮӡ�������ͼ��');


% --- Executes on button press in pushbutton12.
function pushbutton12_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton12 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
open('C:\Users\Administrator\Desktop\10.10\SM2_Sign_Verify\Debug\SM2_Sign_Verify.exe');