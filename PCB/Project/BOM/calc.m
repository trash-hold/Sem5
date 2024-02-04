clear all

%Motor statistics
Lm = 60 * 10^(-3);
Rm = 30;

VM = 12;
I_motor = 0.4;

%DRV8847
I_TRIP = 0.4; %I_Trip = I_RMS of motor 
V_TRIP = 0.150; % typ value

R_sens = V_TRIP / I_TRIP %Theoretical
R_sens_actual = 0.39;
R_delta = (R_sens_actual - R_sens)/R_sens * 100
P_rsens = V_TRIP^2/R_sens_actual 

%P_FAULT_PULLUP = (5 * 10 ^(-3))^2 * 10^4 %Iout = 1uA max with Rpull = 10kOhm
 
%Diode
V_DIN = 5;

R_pull_up = 10 * 10^3; %Pull_up 10kOhm
I_pull = V_DIN/R_pull_up

I_max = 3 * 10^(-3); % Max threshold for calculation is 3mA

V_f = 2;
I_f = I_max - I_pull

R_dmin = (V_DIN - V_f)/I_f
P_dmax = (V_DIN - V_f)^2 / R_dmin


%%Power total
%DRV8847
R_DS_LS = 450 * 10^(-3);
R_DS_HS = 520 * 10^(-3);
I_OUT = 0.4;
P_H = 2*I_OUT^2 * (R_DS_HS + R_DS_LS)

%LDO
I_OUT_MAX = 3 * 10^(-3);
P_LDO = I_OUT_MAX * 7 % P_LDO = I * delta V

%Delta t
R_TH_DRV = 46.4;
R_TH_LDO = 54.7;

Delta_LDO = P_LDO * R_TH_LDO 
Delta_DRV = P_H * R_TH_DRV 



