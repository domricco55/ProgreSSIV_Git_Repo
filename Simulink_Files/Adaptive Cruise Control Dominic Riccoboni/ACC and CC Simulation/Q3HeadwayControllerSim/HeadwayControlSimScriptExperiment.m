clc 
clear all
g = 9.81; % [m/s^2]

%% Controller Values
%lambda = .00000000001;%[1/s] Control Variable
lambda = 0.135
tau = .5;  %[s]  Time constant of acceleration response
h = 2;    %[s]    Headway to preceding vehicle desired

%% String Stability Verification
trans_fun = tf([1 lambda], [h*tau h (1+lambda*h) lambda])

figure(1)
[ImpSE,T] = impulse(-trans_fun);
plot(T,ImpSE)
any(ImpSE>0)
xlabel('Time [s]')
ylabel('Spacing Error Amplitude')
title('Impulse Response of Spacing Error Transfer Function')

%% Ramp Input Simulation
%ramp input setup
Time1 = 35;
DTime = 5;
Time2 = Time1 + DTime;
StartVel = 7; % [m/s]
Slope = 0.5*g;
EndVel = (Time2-Time1)*Slope+StartVel

InputNum = 3; %This variable controls which input the switch is on 
InputTime = 1;%Tells when the input signal should start

%Initial Condition of ACC car Setup
Vinit = StartVel*1.5; %Start the car a good amount faster than the preceding vehicle
Rinit = StartVel*h*4; %Start the car at a larger distance away than desired 

%Sim time
tsim =2*( Time2 + 10);

%Run the Simulation
sim('HeadwayControlExperimenting')

%Plot the results
figure(2) 
plot(tout, SpacingError)
xlabel('Time [s]')
ylabel('Spacing Error [m]')
title('Spacing Error Response')

figure(3)
plot(tout, Velocity, tout, Input)
xlabel('Time [s]')
ylabel('Velocity [m/s]')
ylim([0 (EndVel+.2*EndVel)])
title('Velocity Response')
legend('ACC Vehicle Velocity', 'Preceding Vehicle Velocity','Location','southeast')

figure(4)
plot(tout, R, tout, Velocity*h)%[0 tout(length(tout))], [EndVel*h EndVel*h])
xlabel('Time [s]')
ylabel('Range [m]')
title('Inter-Vehicle Spacing')
ylim([0 (Velocity(length(tout))*h+.2*Velocity(length(tout))*h)])
legend('Actual Inter-Vehicle Spacing', 'Desired Inter-Vehicle Spacing','Location','southeast')

% R v Rdot for this response
figure(5)
plot(Rdot,R)%,R(2),Rdot(2),'*',R(7),Rdot(7),'*',R(17),Rdot(17),'*')
xlabel('Rdot [m/s]')
ylabel('R [m]')
title('Rangefinder States')
ax = gca;
ax.XAxisLocation = 'origin';
ax.YAxisLocation = 'origin';

% %% Constant Velocity Input Response Simulation 
% %Step Input Setup
% InputNum = 2;
% InputTime = 0;
% StarVel = 0;
% EndVel = 7;
% 
% %Initial Condition of ACC car Setup
% Vinit = 1.5*StartVel; %Start the car a good amount faster than the preceding vehicle
% Rinit = StartVel*h*4; %Start the car at a larger distance away than desired
% 
% %Sim time
% tsim = 15;
% 
% %Run the Simulation
% sim('HeadwayControlExperimenting')
% 
% %Plot the results
% figure(5) 
% plot(tout, SpacingError)
% xlabel('Time [s]')
% ylabel('Spacing Error [m]')
% title('Spacing Error Response')
% 
% figure(6)
% plot(tout, Velocity, tout, Input)
% xlabel('Time [s]')
% ylabel('Velocity [m/s]')
% ylim([0 (Vinit+.2*Vinit)])
% legend('Velocity Response', 'Preceding Vehicle Velocity','Location','southeast')
% title('Velocity Response')
% 
% % R v Rdot for this response
% figure(7)
% plot(Rdot,R)%,R(2),Rdot(2),'*',R(7),Rdot(7),'*',R(17),Rdot(17),'*')
% xlabel('Rdot [m/s]')
% ylabel('R [m]')
% title('Rangefinder States')
% %% Constant Acceleration of Preceding Vehicle
% 
% InputNum = 4;%This is just a single ramp, the velocity does not tail off to a constant with this input
% StartVel = 7;
% 
% %Initial Condition of ACC car Setup
% Vinit = StartVel; %Start the car a good amount faster than the preceding vehicle
% Rinit = StartVel*h; %Start the car at a larger distance away than desired
% 
% %Sim time
% tsim = 15;
% 
% %Run the simulation
% sim('HeadwayControlExperimenting')
% 
% figure(8)
% plot(Rdot,R)
% xlabel('Rdot [m/s]')
% ylabel('R [m]')
% ylim([0 R(length(tout))+1/5*R(length(tout))])
% %title('Rangefinder States')
