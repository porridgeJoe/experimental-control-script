fs = 48000;
load('totalsound_10.mat');
name='190212_M6_E18';
delete(instrfindall);
s = serial('COM9');
set(s,'DataBits',8);
set(s,'StopBits',1);
set(s,'BaudRate',9600);
set(s,'Parity','none');
set(s,'timeout',120);%timeout period setting
fopen(s);
a=0;
triggernum = 4;
while (size(a,1) ~= triggernum)
    a=fread(s,triggernum);
end

if (size(a,1) == triggernum)%play audio when get how many triggers
    disp(['trigger',num2str(triggernum),'th reached']);
    Snd('Open');
    BlockStart=GetSecs
    Snd('Play',totalsound,fs);
    Snd('Wait');
    BlockEnd=GetSecs
    wholetime = BlockEnd - BlockStart
    Snd('Close');
    save([name,'_PTrecording.mat'],'BlockStart','BlockEnd');
end
delete(instrfindall);
%