const 
	NPHIL : 3;
	MAX_WAIT : 3;

type 
	phil_range : 1..NPHIL;
	phil_val : 0..10;
	wait_val : 0..MAX_WAIT;
	state_array : array [phil_range] of phil_val;
	wait_array : array [phil_range] of wait_val;
	prob : real(15, 99);

var 
	state : state_array;
	wait : wait_array;

function lfree(i : phil_range) : boolean;
var left : phil_range;
begin
	left := (i < NPHIL? i + 1 : 1);
	return (state[left] != 5 & state[left] != 7 & 
		state[left] != 8 & state[left] != 9);
end;
	
function rfree(i : phil_range) : boolean;
var right : phil_range;
begin
	right := (i > 1? i - 1 : NPHIL);
	return (state[right] != 4 & state[right] != 6 & state[right] != 8 & 
		state[right] != 9 & state[right] != 10);
end;
	
function calc_prob(i : phil_range; c : phil_val) : prob;
/* probability that state[i] becomes c */
begin
	switch state[i]
		case 0: 
			if (c = 0) then
				return 0.2 / NPHIL;
			elsif (c = 1) then
				return 0.8 / NPHIL;
			else
				return 0.0;
			endif
		case 1:
			if (c = 2) then
				return 0.5 / NPHIL;
			elsif (c = 3) then
				return 0.5 / NPHIL;
			else
				return 0.0;
			endif
		case 2:
			if (c = 2 & !lfree(i)) then
				return 1.0 / NPHIL;
			elsif (c = 4 & lfree(i)) then
				return 1.0 / NPHIL;
			else
				return 0.0;
			endif
		case 3:
			if (c = 3 & !rfree(i)) then
				return 1.0 / NPHIL;
			elsif (c = 5 & rfree(i)) then
				return 1.0 / NPHIL;
			else
				return 0.0;
			endif
		case 4:
			if (c = 6 & !rfree(i)) then
				return 1.0 / NPHIL;
			elsif (c = 8 & rfree(i)) then
				return 1.0 / NPHIL;
			else
				return 0.0;
			endif
		case 5:
			if (c = 7 & !lfree(i)) then
				return 1.0 / NPHIL;
			elsif (c = 8 & lfree(i)) then
				return 1.0 / NPHIL;
			else
				return 0.0;
			endif
		case 6: 
			if (c = 1) then
				return 1.0 / NPHIL;
			else
				return 0.0 / NPHIL;
			endif
		case 7: 
			if (c = 1) then
				return 1.0 / NPHIL;
			else
				return 0.0;
			endif
		case 8: 
			if (c = 9) then
				return 1.0 / NPHIL;
			else
				return 0.0;
			endif
		case 9: 
			if (c = 10) then
				return 1.0 / NPHIL;
			else
				return 0.0;
			endif
		case 10: 
			if (c = 0) then
				return 1.0 / NPHIL;
			else
				return 0.0;
			endif
	endswitch
end;

procedure step(i : phil_range; c : phil_val);
begin
	if (c = 1 & (state[i] = 6 | state[i] = 7) & (wait[i] != MAX_WAIT)) then
		wait[i] := wait[i] + 1;
	endif;
	if (state[i] = 10 & c = 0) then
		wait[i] := 0;
	endif;
	state[i] := c;
end;

startstate "initstate"
	for i : phil_range do
		state[i] := 0;
		wait[i] := 0;
	endfor;
end;

ruleset philosophers : phil_range do
	ruleset next : phil_val do
		rule "next"
			calc_prob(philosophers, next) ==>
			begin
				step(philosophers, next);
			end;
	end;
end;

pctl
[
	true UNTIL <= 16 (exists p : phil_range do (wait[p] = MAX_WAIT) endexists)
]<=0.00000001;

