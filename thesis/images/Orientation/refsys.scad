use <vector.scad>


import("/home/def/Repositories/REPY-2.0/stl/REPY Futaba 3003s/assembly.stl");

translate([ -12, 0, 0])
rotate([-90,0,0])
rotate([0,0,90])
frame(l=10);

translate([ 15, 0, 0])
rotate([90,0,0])
rotate([0,0,-90])
frame(l=10);

translate([ 0, 12, 0])
rotate([0,90,0])
frame(l=10);

rotate([180, 0, 0])
frame(l=10);
