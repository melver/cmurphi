--------------------------------------------------------------------------------
--
--  Murphi description of a
--
--            Co-Generative Electric Power Plant
--
--------------------------------------------------------------------------------
-- 
--  version:      2.0
--         
--  written by:   Enrico Tronci
--  date:         Nov 2002
--  affiliation:  University of Rome "La Sapienza"
--
--------------------------------------------------------------------------------
--
--  The power plant controller parameters are taken from:
--  HSDE, Software Functional Design Specification for 
--  an Expanded Digicon Controller for the Nuovo Pignone PGT2 Gas Turbine,
--  document number DS1235
--
--------------------------------------------------------------------------------



-------------------------------------------------
-- constant declarations
-------------------------------------------------

const

    -- model parameters
    SAMPLING_FREQ:       100.0;  -- sampling frequency in Hz.
    MAX_U:               200.0;  -- max value for user demand (kW)
    MAX_D_U:             15;     -- max variation for user demand (kW) in sampling time;
    MAX_PI_DISTURBANCE:  1;      -- max PI disturbance, min = 0
    FREQ_1:              100;    -- frequency injection disturbances

    -- controller parameters
    acceleration:        0.1;
    deceleration:        -0.1;
    disconnect:          1;
    connect:             2;
    rise_min:            75;
    rise_max:            105;
    v_min:               75;
    v_max:               105;
        
    -- PI parameters
    min_v10:             75;
    max_v10:             105;
    max_dv10:            6;
    min_dv10:            5;
    kdr:                 0.0019;   -- (1.9 %/MW == 1.9%/1000kw == 0.0019%/kw)
    x_connect_max:       6;
    y_connect_max:       6;
    
    -- N1 governor parameters
    kp_1:                400;  -- 400kw == 0.4MW
    ki_1:                40;   -- 40kw/s == 0.04MW/s

    -- Power limiter parameters
    kp_2:                1;       -- 1 kw/kw
    ki_2:                0.5;     -- 0.5 kw/s/kw
    Set_Power:           2000.0;  -- 2 MW = 2000 Kw
    T_min:               525;
    T_max:               535;
    min_pressure:        11;
    max_pressure:        13;
    
    -- Exh Temp Limiter parameters
    kp_3:                10;  --10kw/°C
    ki_3:                5;   -- 5kw/°C/s  
    
    c:                   540;
    FG102_max:           1.0;
    FG102_min:           0.0;
    Power_max:           3200.0;
    Power_min:           0;
    OFFSET_P:            0;  -- pg. 13, fig. 1.12
    SMOKES_max:          600;
    SMOKES_setpoint:     552;
    SMOKES_min:          0;
    v_rot_max:           130;
    v_rot_setpoint:      75;
    v_rot_min:           0;
    

    Disturbance_type_L:            0;
    Disturbance_type_H:            0;
    Disturbance_usrdemand_type_L:  -1;
    Disturbance_usrdemand_type_H:  1;
    Disturbance_PI_type_L:         0;   -- must be in 0 .. MAX_PI_DISTURBANCE;
    Disturbance_PI_type_H:         0;   -- must be in 0 .. MAX_PI_DISTURBANCE;

    Clamp_L:      2;  -- 1 acceleration, 2 deceleration
    Clamp_H:      2;

    Modality_L:      2;  -- 1 disconnect, 2 connect 
    Modality_H:      2;

    beta:            0.4;  -- maximum strongness in probability of variation

-------------------------------------------------
-- type declarations
-------------------------------------------------

type
    real_type:          real(4,99);  -- common real type

    Pow_Gen_type:       real_type;   -- power generator type 
    Rot_Speed_type:     real_type;   -- rotation speed type 
    Clamp_type:         1 .. 2;      -- clamp type 
    Mode_type:          1 .. 2;      -- mode type (1 disconnect, 2 connect)
    Press_type:         real_type;   -- compressor pressure type
    Temp_Smokes_type:   real_type;   -- type smoke temperature
    Usrdemand_type:     real_type;   -- user demand type
    FG102_type:         real_type;   -- fg102 opening degree type

    superint_type:      real_type;
    longint_type:       -50000 .. +50000;
    winner_type:        0 .. 3;

    Disturbance_type:            Disturbance_type_L .. Disturbance_type_H;
    Disturbance_usrdemand_type:  Disturbance_usrdemand_type_L .. Disturbance_usrdemand_type_H;
    Disturbance_PI_type:         Disturbance_PI_type_L .. Disturbance_PI_type_H;     
                                 -- must be subset of 0 .. MAX_PI_DISTURBANCE;

--------------------------------------------
--  data structures
--------------------------------------------

var

--------------------------------------------
-- state var
--------------------------------------------

    Power:           Pow_Gen_type;      -- electric power generator by Alternator (um = 100kW)
    v_rot:           Rot_Speed_type;    -- rotation speed (percentage)
    SMOKES:          Temp_Smokes_type;  -- smokes temperature (um = C)
    v:               superint_type;     -- PI in N1-governor
    N1_state:        superint_type;
    Powlim_state:    superint_type;
    templim_state:   superint_type;

    minall:          superint_type;
    winner:          winner_type;

    step_counter:    longint_type;

--------------------------
-- input var (disturbances)
-------------------------
         
    pressure:      Press_type;     -- pressure compression (CDP) (bar)
    usrdemand:      Usrdemand_type; -- user demand (kW)
    modality_value: Mode_type;      -- mode value: (1 disconnect, 2 connect)


-------------------------------------------
-- procedures and functions
-------------------------------------------

-- auxiliary functions

-- minimum between three values
function  min3 (x, y, z: superint_type; var winner : winner_type) : superint_type;         
begin
    if (x <= y & x <= z)  then winner := 1; return (x); endif;
    if (y <= x & y <= z)  then winner := 2; return (y); endif;
    if (z <= x & z <= y)  then winner := 3; return (z); endif;
end;

-- maximum between three values
function max3 (x, y, z : superint_type; var winner : winner_type) : superint_type;        
begin
    if (x >= y & x >= z)  then winner := 1; return (x); endif;
    if (y >= x & y >= z)  then winner := 2; return (y); endif;
    if (z >= x & z >= y)  then winner := 3; return (z); endif;
end;

function switcher(y,p,q,z,w: superint_type;) : superint_type;
begin 
    if (y = p) then return (z); 
    elsif (y = q) then return (w); 
    else error "switcher got wrong input";
    endif;
end;

function split_range(x, y_s_min, y_s_max, y_1, y_2 : superint_type) : superint_type;
begin
    if (x <= y_s_min) then return (y_1);
    elsif ((x > y_s_min) & (x < y_s_max)) 
        then return (((y_2 - y_1)*(x - y_s_min))/(y_s_max - y_s_min)+ y_1);
    else -- x >= y_s_max : y_2;
        return (y_2);
    endif;
end;


-- given x, the present state and u, the user demand, returns next state value x_next 
function PI(
            x, -- present state 
            u, -- input 
            min_dx, max_dx, 
            min_x, max_x, 
            reset_val : superint_type; 
            dist : Disturbance_PI_type;
            reset : boolean;) : superint_type;

var
    x_buffer : superint_type;
begin

    x_buffer := ( x*SAMPLING_FREQ + (
        (((MAX_PI_DISTURBANCE - dist)*min_dx + dist*max_dx)*u)
        /MAX_PI_DISTURBANCE))
        /SAMPLING_FREQ;

    if (!reset & (x_buffer > max_x))
        then return (max_x);
    endif;

    if ((!reset) &  (x_buffer <= max_x) & (x_buffer >= min_x))
        then return (x_buffer);
    endif;

    if (!reset & (x_buffer < min_x))
        then return (min_x);
    endif;

    -- reset to (reset_val) 
    if (reset) then 
        return (reset_val); 
    endif;

end;


procedure turbogas(d_pressure : Disturbance_type; -- disturbance
                                -- input
                                valve_fg102: FG102_type; 
                                usrdemand : superint_type;  
                                -- state
                                VAR  v_rot, v_rot_next : Rot_Speed_type; 
                                VAR Power, Power_next :  Pow_Gen_type;
                                VAR SMOKES, SMOKES_next : Temp_Smokes_type; 
                                VAR pressure, pressure_next : Press_type);

VAR 
    Power_buffer, SMOKES_buffer, v_rot_buffer : superint_type;
VAR 
    Power_valve_coeff, SMOKES_valve_coeff, v_rot_valve_coeff : superint_type; 
begin

    -- valve increase rot speed, this increases power which 
    -- in turn increases temperature.
    -- At setpoint with usrdemand = 0, use 10% of valve opening

    Power_valve_coeff := Set_Power;
    SMOKES_valve_coeff :=  0.1*SMOKES_setpoint;
    v_rot_valve_coeff := 2*v_rot_setpoint;

    Power_buffer := Power*SAMPLING_FREQ +(-Power/10 - usrdemand + 
                    (valve_fg102 * Power_valve_coeff));  
    Power_next := Power_buffer/SAMPLING_FREQ;

/* Smoke */

    SMOKES_buffer := SMOKES*SAMPLING_FREQ + (-SMOKES/100 + 
                     (valve_fg102 * SMOKES_valve_coeff) + (Power - Set_Power)/100);

    SMOKES_next := SMOKES_buffer/SAMPLING_FREQ;

/* v_rot */

-- use 105 setpoint instead of 75 for acceleration

    v_rot_buffer := v_rot*SAMPLING_FREQ+(-v_rot/10 + (valve_fg102 * v_rot_valve_coeff)  
                    + (Power - Set_Power)/10);
    v_rot_next := v_rot_buffer/SAMPLING_FREQ;

    if (pressure + d_pressure < max_pressure) & (pressure + d_pressure > min_pressure) 
    then
        pressure_next := pressure + d_pressure;
    else 
        pressure_next := pressure;
    endif;

end;


-- generator output 
function output( --input
                 x: superint_type; 
                 kp, ki, x_min, y_min, val: superint_type; 
                 loosing : boolean; 
                 -- state
                 pstate_x : superint_type;     -- present state 
                 VAR nstate_x : superint_type; -- next state 
                 disturbance : Disturbance_PI_type): superint_type;
const
    x1_min: -10000;  -- -10000 kw
    x1_max: 10000;   -- 10000 kw
    y1_min: -10000;  -- -10000 kw
    y1_max: 10000;   -- 10000 kw

    x2_max: 10000;   -- 10000 kw
    y2_max: 10000;   -- 10000 kw

    -- PI settings
    min_dx2: 1;
    max_dx2: 3;
    min_x2:  -20000;
    max_x2:  20000;

VAR
    y1, y2 : superint_type;

begin
    y1 := split_range(x*kp, x1_min, x1_max,  y1_min, y1_max);

    nstate_x := PI(pstate_x, x*ki, min_dx2, max_dx2, min_x2, max_x2, val, disturbance, (x>0 & loosing));
    y2 := split_range(pstate_x, x_min, x2_max, y_min, y2_max);    
    return (y1 + y2);
end;


procedure N1_governor( -- input
                       clamp : Clamp_type;
                       Modality : Mode_type;
                       maxall : superint_type; -- max methane demand + 4KW fir hysteresis
                       -- state
                       VAR v10, v10_next : superint_type;
                       VAR p1_next : superint_type; -- output of N1_governor
                       mystate : superint_type;
                       VAR mystate_next : superint_type;
                       disturbance1, disturbance2 : Disturbance_PI_type;
                       winner : winner_type);
VAR
    acc, rise, y_connect, v_N1 : superint_type;
begin

    acc := switcher(clamp, 1, 2, acceleration, deceleration);
    v10_next := PI(v10, acc, min_dv10, max_dv10, min_v10, max_v10 , 0, disturbance1,false);
    rise := split_range(v10, v_min, v_max, rise_min, rise_max);
    y_connect := split_range((Power * kdr), 0, x_connect_max, 0, y_connect_max);
    v_N1 := switcher(Modality, disconnect, connect, rise, (rise - y_connect));

    p1_next := output(v_N1 - v_rot, kp_1, ki_1, 0, 0, maxall, (winner != 1), -- loosing
                      mystate, mystate_next,disturbance2);

end; 


procedure power_limiter( -- input
                         maxall : superint_type; -- max methane demand + 4KW fir hysteresis
                         -- state
                         VAR p2_next : superint_type;
                         VAR mystate, mystate_next : superint_type;
                         disturbance : Disturbance_PI_type;
                         winner : winner_type);
begin

    p2_next := output((Set_Power - Power), kp_2, ki_2, 300, 300, maxall, winner != 2, 
                       mystate, mystate_next, disturbance); 

end; 


procedure exh_temp_limiter( -- input
                            maxall : superint_type; -- max methane demand + 4KW fir hysteresis
                            pressure : superint_type;
                            -- state
                            VAR p3_next : superint_type;
                            VAR mystate, mystate_next : superint_type;
                            disturbance : Disturbance_PI_type;
                            winner : winner_type);
VAR
    temp : superint_type;

begin

    temp := split_range(pressure, min_pressure, max_pressure, T_max, T_min);   
    temp := c + temp;

    p3_next := output((temp  - SMOKES), kp_3, ki_3, 0, 0, maxall, winner != 3,
                      mystate, mystate_next, disturbance);

end; 


procedure valve_fg102_opening( --input
                               N1_gov, Pow_lim, temp_lim : superint_type;
                               -- output
                               VAR fg102 : FG102_type;
                               minall : superint_type);
VAR
    x_min, W : superint_type;

begin

    W := split_range(minall, 0, 12000, 0, 12000);
    fg102 := split_range(W + OFFSET_P, 0, 10000, 0, FG102_max);

end;



-- init + main

procedure init();
begin
   Power := Set_Power;
   Powlim_state := 1000;

   SMOKES := SMOKES_setpoint;
   templim_state := 1000;

    -- deceleration (setpoint)
   v_rot := v_rot_setpoint;
   N1_state := 1000;  
   v := 750; 
 
   -- acceleration  (setpoint)
   minall := 1000; 
   winner := 2;  -- power limiter

   pressure := 12;
   usrdemand := 0;

   step_counter := 0;
   modality_value := 1; -- disconnect

end;


procedure main(clamp: Clamp_type; Modality : Mode_type; 
               d_pressure : Disturbance_type; 
               N1_d1 : Disturbance_PI_type; N1_d2 : Disturbance_PI_type;
               Powlim_d : Disturbance_PI_type; templim_d : Disturbance_PI_type;
               usrdemand_d : Disturbance_usrdemand_type);
VAR 
    -- auxiliary variables
    maxall : superint_type;
    minall_next : superint_type;
    winner_next : winner_type;

    -- state variables
    Power_next : Pow_Gen_type;       -- electric power generator by Alternator (um = kW)
    v_rot_next : Rot_Speed_type;     -- rotation speed (percentage)
    SMOKES_next : Temp_Smokes_type;  -- smokes temperature (um = C)
    v_next: superint_type;           -- PI in N1_governor 
    N1_gov_next, Pow_lim_next, 
    Temp_lim_next: superint_type;
    valve_fg102_next : FG102_type;
    N1_state_next, templim_state_next, 
    Powlim_state_next : superint_type;

    -- input variables (disturbances)
    pressure_next : Press_type;       -- pressure compression (CDP) (bar)
    usrdemand_next : Usrdemand_type;  -- user demand (kW)
    step_counter_next : longint_type;

begin

    -- update disturbances value 
    if (step_counter%FREQ_1 = FREQ_1 - 1) 
    then
        modality_value := Modality;
    endif;

    -- new power
    N1_governor(clamp, modality_value, minall + 4, v, v_next, N1_gov_next, 
                N1_state, N1_state_next, N1_d1, N1_d2, winner);
    power_limiter(minall + 4, Pow_lim_next, Powlim_state, Powlim_state_next, 
                  Powlim_d, winner);
    exh_temp_limiter(minall + 4, pressure, Temp_lim_next, templim_state, 
                     templim_state_next, templim_d, winner);

    /* compute winner (min) */
    minall_next := min3(N1_gov_next, Pow_lim_next, Temp_lim_next, winner_next);
    valve_fg102_opening(N1_gov_next, Pow_lim_next, Temp_lim_next, valve_fg102_next, minall);

    turbogas(d_pressure, valve_fg102_next, usrdemand, v_rot, v_rot_next, Power, 
             Power_next, SMOKES, SMOKES_next, pressure, pressure_next);

    -- user demand dynamics 
    if (usrdemand + MAX_D_U*usrdemand_d <= MAX_U) & 
       (usrdemand + MAX_D_U*usrdemand_d >= 0) & 
       (step_counter%FREQ_1 = FREQ_1 - 1) 
    then
        usrdemand_next := usrdemand + MAX_D_U*usrdemand_d;
    else
        usrdemand_next := usrdemand;
    endif;

    step_counter_next := (step_counter + 1)%FREQ_1;


    -- sync updating 
    Power := Power_next;
    SMOKES := SMOKES_next ;
    v_rot := v_rot_next ;
    pressure := pressure_next;
    v := v_next;  
    N1_state := N1_state_next;
    Powlim_state := Powlim_state_next;
    templim_state:= templim_state_next;
    usrdemand := usrdemand_next;
    winner := winner_next;
    minall := minall_next;
    step_counter := step_counter_next;

end;


-------------------------
-- startstate
------------------------

startstate "initstate" init(); end;


---------------------------------------
-- rules
---------------------------------------

ruleset clamp: Clamp_L .. Clamp_H  do
    ruleset Modality: Modality_L .. Modality_H  do
        ruleset d_pressure: Disturbance_type  do
            ruleset N1_d1: Disturbance_PI_type do
                ruleset N1_d2: Disturbance_PI_type do
                    ruleset Powlim_d: Disturbance_PI_type do
                        ruleset templim_d: Disturbance_PI_type do
                            ruleset usrdemand_d: Disturbance_usrdemand_type do 
           
                                rule "time step"
                                   true ==> 
                                   begin
                                      main(clamp, Modality, d_pressure, N1_d1, N1_d2, Powlim_d, templim_d, usrdemand_d);
                                   end;
                             
                             end; -- usrdemand_d
                        end; -- templim_d
                    end; -- Powlim_d
                end; -- N1_d2
            end; -- N1_d1
        end; -- d_pressure
    end; -- Modality
end; -- clamp


----------------------------------
-- invariants
--------------------------------

invariant "power ok"
    (Power>=1300) & (Power<=2500);


invariant "smokes ok"
    (SMOKES>=200) & (SMOKES<=580);


invariant "rot speed ok"
    (v_rot>=40) & (v_rot<=120);

