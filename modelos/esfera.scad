module base(interior,total,altura)
{
		difference() {
			cylinder(h= altura, r=total,$fa=1,$fs=0.1);
			translate([0,0,-1]){
				cylinder(h=altura+2, r=interior,$fa=1,$fs=0.1);
			}
		}
}

translate([0,0,11]){
difference(){
sphere(r=12);
sphere(r=10);

rotate([90,0,0]){
for(j = [0 : 30 : 180]){
for(i = [0 : 30 : 180]){
rotate([0,j,0]){
rotate([i,0,0]) {
cylinder(h= 100, r=2.3,$fa=1,$fs=0.1, center = true);
}}}
}
}

cylinder(h= 100, r=5,$fa=1,$fs=0.1, center = true);

}}

base(4,16,4);
//}