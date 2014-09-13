const 
	NPHIL : 2;

type 
	phil_range : 1..NPHIL;
	phil_val : 0..10;
	state_array : array [phil_range] of phil_val;
	prob : real(4, 99);

var 
	state : state_array;

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
	state[i] := c;
end;

startstate "initstate"
	for i : phil_range do
		state[i] := 0;
	endfor;
end;

ruleset philosophers : phil_range do
	ruleset succ : phil_val do
		rule "next"
			calc_prob(philosophers, succ) ==>
			begin
				step(philosophers, succ);
			end;
	end;
end;

pctl
[
	true 
	UNTIL<=11
	((state[1]=2 & (forall p : phil_range do (p = 1 | state[p] < 8) endforall))
	&&
	(!!([ 
		true 
		UNTIL<= 4
		(state[1]=4 | (exists p : phil_range do (p != 1 & state[p] > 7) endexists))
	]>=0.999)))
]<=1;
