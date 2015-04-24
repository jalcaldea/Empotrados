module base(interior,total,altura)
{
		difference() {
			cylinder(h= altura, r=total,$fa=1,$fs=0.1);
			translate([0,0,-1]){
				cylinder(h=altura+2, r=interior,$fa=1,$fs=0.1);
			}
		}
}

module cubo(dim,anc){
difference(){
cube(size=[dim,dim,dim],center=true);
cube(size=[dim-anc,dim-anc,400],center=true);
cube(size=[dim-anc,400,dim-anc],center=true);
cube(size=[400,dim-anc,dim-anc],center=true);}
}


difference(){
translate([0,0,13]){
rotate([35,45,35]){
cubo(20,5);
}
}

translate([0,0,4]){
rotate([0,180,0]){
cylinder(h=100, r=16,$fa=1,$fs=0.1);
}
}
}

base(4,16,4);



