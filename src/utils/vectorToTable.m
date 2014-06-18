function T, f = vectorToTable( v, n, max_a, max_o, max_p, max_f , configuration )
	ids_11_2 = [ 31466;80628;80339;80917;70056;82651;83229;83523;83524;83521;83522];
	ids_9 = [ 31464;80628;80339;80917;83523;83522;83524;80050;83521];
	ids_7 = [ 31466;80628;80339;80917;83523;83522;83524];
	
	a = (v(1:3:3*n).+1).*(max_a/2);
	o = v(2:3:3*n).*max_o;
	p = (v(3:3:3*n).+1).*(max_p/2);
	f = [configuration (v(3*n+1).+1).*(max_f/2)];
	
	T = [ a; o; p ]';
	
	if configuration == 0 
		T = [ids_11_2 T];
		save 'T0.txt' T;
		save 'f0.txt' f;
	elseif configuration == 1
		T = [ids_7 T];
		save 'T1.txt' T;
		save 'f1.txt' f;
	elseif configuration == 2
		T = [ids_9 T];
		save 'T2.txt' T;
		save 'f2.txt' f;
	endif
	

endfunction
