clc 
clear all
g = 9.81; % [m/s^2]

%% Controller Values
%lambda = .00000000001;%[1/s] Control Variable (Subject of Parametric Study)
lambda = 0.001
tau = .5;  %[s]  Time constant of acceleration response
h = 2;    %[s]    Headway to preceding vehicle desired

%% Simulation Setup
Time1 = 2;
DTime = 5;
Time2 = Time1 + DTime;
StartVel = 7; % [m/s]
Slope = 0.5*g;
EndVel = (Time2-Time1)*Slope+StartVel

InputNum = 3; %This variable controls which input the switch is on 
InputTime = 1;%Tells when the input signal should start

tsim = Time2 + 10;
sim('HeadwayControl_CleanedUpVFinal')

%% String Stability Verification
trans_fun = tf([1 lambda], [h*tau h (1+lambda*h) lambda])

figure(1)
[ImpSE,T] = impulse(-trans_fun);
plot(T,ImpSE)
any(ImpSE>0)
xlabel('Time [s]')
ylabel('Spacing Error Amplitude')
title('Impulse Response of Spacing Error Transfer Function')

% [maxJerkCustom, index] = max(abs(Jerk(:)))

%% Response Plots and Optimizing Lambda
n = 1000;
%lambda = zeros(1,length(n)) 

InputNum = 3;
StartVel = 7;
sim('HeadwayControl_CleanedUp')

figure(2) 
plot(tout, SpacingError)
xlabel('Time [s]')
ylabel('Spacing Error [m]')
title('Spacing Error Response')

[maxJerkStep, index] = max(abs(Jerk(:)))

figure(3)
plot(tout, Velocity, tout, Input)
xlabel('Time [s]')
xlabel('Time [s]')
ylabel('Velocity [m/s]')
ylim([0 (EndVel+.2*EndVel)])
legend('Velocity Response', 'Preceding Vehicle Velocity','Location','southeast')

% figure(4)
% plot(tout, Input)
% xlabel('Time [s]')
% ylabel('Velocity [m/s]')
% ylim([0 (EndVel+.2*EndVel)])
% title('Velocity of Preceding Car (Input)')
% legend(['Acc = ' ,num2str(Slope/g), ' gs'])
% InputNum = 2;
% StartVel = 0;
% EndVel = 1;
% sim('HeadwayControl')
% [maxJerkStep, index] = max(abs(Jerk(:)))
% figure(3) 
% plot(tout, Jerk)


%% R vs Rdot
figure(5)
plot(Rdot,R)
xlabel('Rdot [m/s]')
ylabel('R [m]')
title('Rangefinder States')


% figure(2)
% pzmap(trans_fun)
% 
% figure(3)
% step(trans_fun)
% 
% figure(4)
% bode(trans_fun)

% S  = stepinfo(trans_fun)










