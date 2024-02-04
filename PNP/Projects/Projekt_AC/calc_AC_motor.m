MOCK = false;

Un = 400;
fn = 50;

if MOCK == true
    Pn = 7.5 * 1000;
    n = 975;
    ns = 1000;
    In = 16.6;
    eta = 87.2;
    cos = 0.75;
    Tn = 73.5;
    Ma_Mn = 1.8;
    Ia_In = 6.5;
    Mk_Mn = 2.8;
    Ms_Mn = 1.7;
    J = 0.1;
    Lpa = 59;
    m = 87;

    p = 3
else
    Pn = 1.1 * 1000;
    n = 1425;
    ns = 1500;
    In = 2.5;
    eta = 81.4;
    cos = 0.77;
    Tn = 7.4;
    Ma_Mn = 2.3;
    Ia_In = 5.2;
    Mk_Mn = 2.9;
    Ms_Mn = 2.3;
    J = 0.0034;
    Lpa = 48;
    m = 30.5;

    p = 2
end

%%Indukcyjnosci rozporszenia
I_sdN = sqrt(2)*In*sqrt(1 - cos);
I_sqN = sqrt(2*In^2 - I_sdN^2);

L_ls = Un*(sqrt(1 - cos^2) - I_sdN * cos / I_sqN)/(2*sqrt(3) * pi * fn * In)

%Indukcyjność magnesująca 
Xm = Un/sqrt(3) * (sqrt(2)/I_sdN - sqrt(1 - cos^2)/In + I_sdN * cos / (I_sqN * In))*0.9;
Lm = Xm /(2 * pi * fn)

%Rezystancja stojana Rs
omega_slipn = 2 * pi * (fn - n*p/60);
Rs = omega_slipn * I_sdN * Xm / (2 * pi * fn * I_sqN)

%Rezystancja wirnika Rr
sn = (ns - n)/ns ;
Rr = sn * Un / (sqrt(3)* In)

%Tarcie wiskotyczne 
omega_n = n * 2 * pi / 60;
cl = 2;
F = (sqrt(3) * Un * In * cos - Tn * omega_n - cl * In^2 * Rs) / (omega_n ^2)

%%
%widelki bledow
if false
    n_val = [n * 0.99, n*1.01]
    i_val = [In * 0.99, In * 1.01]
    eta_val = [eta*0.99, eta * 1.01]
    cos_val = [cos * 0.99, cos *1.01]
end


new_F =  0.0076552*0.7;
tau = J/new_F
tau_val = [0.2*tau, tau*0.4]
