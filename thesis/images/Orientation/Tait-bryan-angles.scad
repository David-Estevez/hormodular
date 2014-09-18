use <vector.scad>

rotate([45, 0, 0])
rotate([0, 45, 0])
rotate([0,0,45])
union()
{
	cylinder( r = 15, r2=0, h = 20, $fn=4 );
	#frame(l=30);
};

frame(l=30);