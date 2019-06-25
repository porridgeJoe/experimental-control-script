clear;
clc;
Array=[1 2 4 8 1 2 4 8 1 2 4 8 1 2 4 8 1 2 4 8];
for Num = 1 : 20
    randomArray(Num,:) = Shuffle(Array);
end
save('randomArray','randomArray')
delay = 15;
fs = 48000;
frequencyRange = [5500 6000 6500 7000 7500 8000 8500 9000 9500 10000 5500 6000 6500 7000 7500 8000 8500 9000 9500 10000];
rest = zeros(1,fs*delay);
%{
 Sound_Generator
%fs, randomArray and frequencyRange are in use
% single sound generates by shufflling frequencyRange and sine it
% single sound array tone_Hz contains 20 puretones
totalsound=zeros(1,fs*15);
frequencyArray = shuffle(frequencyRange); % number in this array is frequency of each puretone
for EventNum = 1 : 20
    toneTime = 0.05;
    toneNum = 20 ;
    tone_Hz = zeros(1,toneNum,fs*toneTime); % number in this is the frequency transfered into function of sine
    sp = fs*toneTime; %sample points of one puretone
    
    for puretoneNum = 1 : toneNum*randomArray1(EventNum)*10
        freq_temp = sin(2*pi*frequencyArray(EventNum)*((1:sp))/fs);
        tone_Hz(EventNum,puretoneNum,:)=freq_temp;
    end
    
    Record_toneArray(EventNum,:) = frequencyArray;
end

%total sound contains 15s delay at begining and random ordered sound trains
%sound trains have different length and played with 15s delay between each
%other
% for EventNum = 1 : size(tone_Hz,1)
% totalsound = cat(1,totalsound,tone_Hz(:,));
% totalsound = cat(1,totalsound,fs*15);
% end
%}
%% another strategy

totalsound=[];
for randNum = 1:20
    for eventNum = 1 : 20
        totalsound = cat(2,totalsound,rest);
        for  secNum = 1 : randomArray(randNum,eventNum)
            freqArray = Shuffle(frequencyRange);
            RecfreqArray(randNum,eventNum,secNum,:) = freqArray;
            for freqNum = 1 : length(freqArray)
                toneTime = 0.05;
                sp = fs*toneTime; %sample points of one puretone
                tonetrain(freqNum,:) = sin(2*pi*freqArray(freqNum)*((1:sp))/fs);
            end
            for trainNum = 1 : size(tonetrain,1)
                totalsound = cat(2,totalsound,tonetrain(trainNum,:));
            end
        end
    end
    save(['totalsound_',num2str(randNum)],'totalsound')
    totalsound= [];
end
save('RecfreqArray','RecfreqArray');