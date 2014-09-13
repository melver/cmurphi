const
	NPHIL : 3;	/* not modifiable, it is not a parameter */
	N : 4;
	MAX_WAIT : 3;
	MAX_WAIT_MINOR : 2;

type
	phil_range : 1..NPHIL;
	phil_val : 0..13;
	wait_val : 0..MAX_WAIT;
	n_val : 0..N;
	state_array : array [phil_range] of phil_val;
	wait_array : array [phil_range] of wait_val;
	cont_array : array [phil_range] of n_val;
	prob : real(10, 99);

var
	state : state_array;
	wait : wait_array;
	cont : cont_array;

function left(i : phil_range) : phil_range;
begin
	return (i < NPHIL? i + 1 : 1);
end;

function right(i : phil_range) : phil_range;
begin
	return (i > 1? i - 1 : NPHIL);
end;

function lfree(i : phil_range) : boolean;
var left_v : phil_range;
begin
	left_v := left(i);
	return (state[left_v] != 5 & state[left_v] != 7 &
		state[left_v] != 8 & state[left_v] != 9 &
		state[left_v] != 10 & state[left_v] != 12);
end;

function rfree(i : phil_range) : boolean;
var right_v : phil_range;
begin
	right_v := right(i);
	return (state[right_v] != 4 & state[right_v] != 6 & state[right_v] != 8 &
		state[right_v] != 9 & state[right_v] != 10 & state[right_v] != 11);
end;

function can(i : phil_range) : boolean;
begin
	switch (i)
		case 1 : 
			return !((cont[2] = N) | (cont[3] = N) | ((cont[2] = N - 1) & (cont[3] = N - 1)));
		case 2:
			return !((cont[1] = N) | (cont[3] = N) | ((cont[1] = N - 1) & (cont[3] = N - 1)));
		case 3:
			return !((cont[1] = N) | (cont[2] = N) | ((cont[1] = N - 1) & (cont[2] = N - 1)));
	endswitch
end;

function count(i : phil_range) : boolean;
begin
	return (state[i] != 13 & state[i] != 0);
end;

function ncount(i : phil_range) : boolean;
begin
	return !count(i);
end;

function calc_prob(i : phil_range; c : phil_val) : prob;
/* probability that state[i] becomes c */
var to_divide : phil_range;	/* how many philosopher can make a transition */
begin
	to_divide := 1;
	for j : phil_range do
		if (i != j & can(j)) then
			to_divide := to_divide + 1;
		endif
	endfor;
	if !(can(i)) then
		return 0.0;
	endif;
	switch state[i]
		case 0: 
			if (c = 0) then
				return 0.2 / to_divide;
			elsif (c = 1) then
				return 0.8 / to_divide;
			else
				return 0.0;
			endif
		case 1:
			if (c = 2) then
				return 0.5 / to_divide;
			elsif (c = 3) then
				return 0.5 / to_divide;
			else
				return 0.0;
			endif
		case 2:
			if (c = 2 & !lfree(i)) then
				return 1.0 / to_divide;
			elsif (c = 4 & lfree(i)) then
				return 1.0 / to_divide;
			else
				return 0.0;
			endif
		case 3:
			if (c = 3 & !rfree(i)) then
				return 1.0 / to_divide;
			elsif (c = 5 & rfree(i)) then
				return 1.0 / to_divide;
			else
				return 0.0;
			endif
		case 4:
			if (c = 6 & !rfree(i)) then
				return 1.0 / to_divide;
			elsif (c = 8 & rfree(i)) then
				return 1.0 / to_divide;
			else
				return 0.0;
			endif
		case 5:
			if (c = 7 & !lfree(i)) then
				return 1.0 / to_divide;
			elsif (c = 8 & lfree(i)) then
				return 1.0 / to_divide;
			else
				return 0.0;
			endif
		case 6: 
			if (c = 1) then
				return 1.0 / to_divide;
			else
				return 0.0 / to_divide;
			endif
		case 7: 
			if (c = 1) then
				return 1.0 / to_divide;
			else
				return 0.0;
			endif
		case 8: 
			if (c = 9) then
				return 1.0 / to_divide;
			else
				return 0.0;
			endif
		case 9: 
			if (c = 10) then
				return 1.0 / to_divide;
			else
				return 0.0;
			endif
		case 10: 
			if (c = 11) then
				return 0.5 / to_divide;
			elsif (c = 12) then
				return 0.5 / to_divide;
			else
				return 0.0;
			endif
		case 11: 
			if (c = 13) then
				return 1.0 / to_divide;
			else
				return 0.0;
			endif
		case 12: 
			if (c = 13) then
				return 1.0 / to_divide;
			else
				return 0.0;
			endif
		case 13: 
			if (c = 0) then
				return 0.5 / to_divide;
			elsif (c = 13) then
				return 0.5 / to_divide;
			else
				return 0.0;
			endif
	endswitch
end;

procedure step(i : phil_range; c : phil_val);
var altri : array [1..NPHIL - 1] of phil_range;
begin
	/* handling wait[i] */
	if (c = 1 & (state[i] = 6 | state[i] = 7) & (wait[i] != MAX_WAIT)) then
		wait[i] := wait[i] + 1;
	endif;
	if (state[i] = 13 & c = 0) then
		wait[i] := 0;
	endif;
	/* handling cont */
	altri[1] := left(i);
	altri[2] := right(i);
	cont[i] := 0;
	if (count(altri[2])) then
		cont[altri[2]] := cont[altri[2]] + 1;
	endif;
	if (count(altri[1])) then
		cont[altri[1]] := cont[altri[1]] + 1;
	endif;
	/* handling state[i] */
	state[i] := c;
end;

startstate "initstate"
	for i : phil_range do
		state[i] := 0;
		wait[i] := 0;
		cont[i] := 0;
	endfor;
end;

ruleset philosophers : phil_range do
	ruleset succ : phil_val do
		rule "succ"
			calc_prob(philosophers, succ) ==>
			begin
				step(philosophers, succ);
			end;
	end;
end;

pctl
[
	true
	UNTIL <= 20
	(
	(exists p: phil_range do (wait[p] >= MAX_WAIT_MINOR) endexists)
	&&
	(!!([
		true
		UNTIL <= 2
		(forall p: phil_range do (wait[p] < MAX_WAIT) endforall)
	]>=0.999))
	)
]<=0.001;
