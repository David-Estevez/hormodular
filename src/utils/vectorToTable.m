function T, f = vectorToTable( v, n, max_a, max_o, max_p, max_f )
	a = (v(1:n).+1).*(max_a/2);
	o = v(n+1:2*n).*max_o;
	p = (v(2*n+1:3*n).+1).*(max_p/2);
	f = (v(3*n+1).+1).*(max_f/2);
	
	T = [ [1:n]; a; o; p ]';
	
endfunction
