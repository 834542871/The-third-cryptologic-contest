function varargout = Audio_System(varargin)
% AUDIO_SYSTEM MATLAB code for Audio_System.fig
%      AUDIO_SYSTEM, by itself, creates a new AUDIO_SYSTEM or raises the existing
%      singleton*.
%
%      H = AUDIO_SYSTEM returns the handle to a new AUDIO_SYSTEM or the handle to
%      the existing singleton*.
%
%      AUDIO_SYSTEM('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in AUDIO_SYSTEM.M with the given input arguments.
%
%      AUDIO_SYSTEM('Property','Value',...) creates a new AUDIO_SYSTEM or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before Audio_System_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to Audio_System_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help Audio_System

% Last Modified by GUIDE v2.5 17-Oct-2017 20:38:08

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Audio_System_OpeningFcn, ...
                   'gui_OutputFcn',  @Audio_System_OutputFcn, ...
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
function onTimer (obj,events,arg)
data=datestr(date,29);
cur_data = data;
cur_time = fix(clock);
% str = sprintf('%s %.2d:%.2d:%.2d', cur_data, cur_time(4), cur_time(5), cur_time(6));
str1 = sprintf('%s', cur_data);
str2 = sprintf('%.2d:%.2d:%.2d', cur_time(4), cur_time(5), cur_time(6));
 set(arg(1),'String',str1);
 set(arg(2),'String',str2);
%  set(arg,'String','111111');
% --- Executes just before DateTime is made visible.

%  set(arg,'String','111111');
% --- Executes just before DateTime is made visible.
% --- Executes just before Audio_System is made visible.
function Audio_System_OpeningFcn(hObject, eventdata, handles, varargin)
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

T = timer('Period',1.0,'ExecutionMode','FixedRate', 'TimerFcn',{@onTimer,[handles.edit3,handles.edit4]});
start(T);

% UIWAIT makes DateTime wait for user response (see UIRESUME)
% uiwait(handles.figure1);

% --- Outputs from this function are returned to the command line.
function varargout = Audio_System_OutputFcn(hObject, eventdata, handles) 

varargout{1} = handles.output;

% --------------------------------------------------------------------
function Untitled_1_Callback(hObject, eventdata, handles)

% --------------------------------------------------------------------
function Untitled_2_Callback(hObject, eventdata, handles)

% --------------------------------------------------------------------
function Untitled_3_Callback(hObject, eventdata, handles)

% --------------------------------------------------------------------
function ATPSize_Callback(hObject, eventdata, handles)

% --------------------------------------------------------------------
function Size64_Callback(hObject, eventdata, handles)
global N;
N=64;%64*64=4096=16384/4

% --------------------------------------------------------------------
function Size128_Callback(hObject, eventdata, handles)
global N;
N=128;%128*128=16384=65536/4

function Size256_Callback(hObject, eventdata, handles)
global N;
N=256;%256*256=65536=262144/4

function Size512_Callback(hObject, eventdata, handles)
global N;
N=512;%512*512=262144=1048576/4
% --------------------------------------------------------------------
function Size1024_Callback(hObject, eventdata, handles)
global N;
N=1024;%1024*1024=1048576=4194304/4


% --------------------------------------------------------------------


% --- Executes on button press in pushbutton2.
function pushbutton2_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
str=date;
set(handles.text8,'String',str);



function edit2_Callback(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit2 as text
%        str2double(get(hObject,'String')) returns contents of edit2 as a double


% --- Executes during object creation, after setting all properties.
function edit2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit3_Callback(hObject, eventdata, handles)
% hObject    handle to edit3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit3 as text
%        str2double(get(hObject,'String')) returns contents of edit3 as a double


% --- Executes during object creation, after setting all properties.
function edit3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit4_Callback(hObject, eventdata, handles)
% hObject    handle to edit4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit4 as text
%        str2double(get(hObject,'String')) returns contents of edit4 as a double


% --- Executes during object creation, after setting all properties.
function edit4_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
% %--------------------------------------------------------------------
function Untitled_5_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Untitled_8_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
