clc 
clear all
g = 9.81; % [m/s^2]

%% Controller Values
tau = .5;  %[s]  Time constant of acceleration response

%% Simulation Setup
%Input Setup (the switch in the simulink model chooses between inputs)
Time1 = 2;
DTime = 5;
Time2 = Time1 + DTime;
StartVel = 7; % [m/s]
Slope = 0.5*g;
EndVel = (Time2-Time1)*Slope+StartVel

InputNum = 2; %This variable controls which input the switch is on 
InputTime = 0;%Tells when the input signal should start

%Simulation time
tsim = Time2 + 10;

%% Response Plots

%Set up a unit step input
StartVel = 0;
EndVel = 1;
InputNum = 2;%Input Switch Number for Step Input
%Select PI Controller Gains (NOT DESIGNED YET)
Kp = 1;
Ki = 1;
%Simulate
sim('CruiseControllerSim')
%Plot output
figure(1) 
plot(tout, xd_act, tout, Input)
xlabel('Time [s]')
ylabel('Velocity [m/s]')
title('Spacing Error Response')
legend('Velocity Response', 'Desired Velocity','Location','southeast')

%Set up a ramp input 
StartVel = 7; % [m/s]
Slope = 0.5*g;
EndVel = (Time2-Time1)*Slope+StartVel;
InputNum = 3;%Input Switch Number for Ramp
%Select PI Controller Gains (NOT DESIGNED YET)
Kp = 1;
Ki = 1;
%Simulate
sim('CruiseControllerSim')
%Plot output
figure(3)
plot(tout, xd_act, tout, Input)
xlabel('Time [s]')
ylabel('Velocity [m/s]')
legend('Velocity Response', 'Desired Velocity','Location','southeast')







