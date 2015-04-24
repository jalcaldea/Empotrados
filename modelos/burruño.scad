module base(interior,total,altura)
{
		difference() {
			cylinder(h= altura, r=total,$fa=1,$fs=0.1);
			translate([0,0,-1]){
				cylinder(h=altura+2, r=interior,$fa=1,$fs=0.1);
			}
		}
}


translate([0,0,4])
{linear_extrude(height = 40, center = false, convexity = 10, twist = -1000, $fn = 50)

translate([6, 0, 0])

circle(r = 2);}

base(4,16,4);
