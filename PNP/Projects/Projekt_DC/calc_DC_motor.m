clear all
%%MMock data
% V_IN = 420;
% n = 995;
% P_n = 3.15*1000;
% T_n = 302;
% I_n = 90;
% eta = 79;
% R_a = 0.65;
% L_a = 6.6/1000;
% 
% U_fn = 310;
% P_f = 1.81*1000;
% J = 0.32

%% Dane wejsciowe
V_IN = 310;
n = 1220;
P_n = 3.15*1000;
T_n = 24.6;
I_n = 13.5;
eta = 69;
R_a = 4.53;
L_a = 17.5/1000;
L_s = 37/1000;

U_fn = 310;
P_f = 0.33*1000;
J = 0.02


%% Rezystancja obwodu wzbudzenia
R_f = U_fn^2/P_f
I_fn = P_f/U_fn

%%Napiecie indukowane i znamionowa elektromotoryczna
E_an = V_IN - I_n*R_a
omega_n = 2*pi/60 * n
L_af = E_an / (I_fn*omega_n)

%%Współczynnik tarcia wiskotycznego 
T_en = E_an * I_n / omega_n
F = (T_en - T_n) / omega_n

%%Obliczenia do dopasowania członów regulatora od prędkości 
tm = J/F
tm_min = tm*0.02;
tm_max = tm*0.03;

%%Obliczenia do prostownika
U_siec = 230;
L_1 = 0.09*U_siec^2/(2 * pi * 50 * V_IN * I_n)

%%Obliczenia do odzyskiwania energii
U_dcl = 550;
R_br = U_dcl^2/(V_IN * 1.5 * I_n)
