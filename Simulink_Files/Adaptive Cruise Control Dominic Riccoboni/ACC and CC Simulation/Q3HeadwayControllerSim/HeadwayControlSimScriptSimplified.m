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
sim('HeadwayControlSimplified')

%% String Stability Verification
trans_fun = tf([1 lambda], [h*tau h (1+lambda*h) lambda])

figure(1)
[ImpSE,T] = impulse(-trans_fun);
plot(T,ImpSE)
any(ImpSE>0)
xlabel('Time [s]')
ylabel('Spacing Error Amplitude')
title('Impulse Response of Spacing Error Transfer Function')

%% Response Plots 
InputNum = 3;
StartVel = 7;
sim('HeadwayControlSimplified')

figure(2) 
plot(tout, SpacingError)
xlabel('Time [s]')
ylabel('Spacing Error [m]')
title('Spacing Error Response')

figure(3)
plot(tout, Velocity, tout, Input)
xlabel('Time [s]')
xlabel('Time [s]')
ylabel('Velocity [m/s]')
ylim([0 (EndVel+.2*EndVel)])
legend('Velocity Response', 'Preceding Vehicle Velocity','Location','southeast')

















