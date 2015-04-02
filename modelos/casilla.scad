module arandela(interior,total,altura)
{
		difference() {
			cylinder(h= altura, r=total,$fa=1,$fs=0.1);
			translate([0,0,-1]){
				cylinder(h=altura+2, r=interior,$fa=1,$fs=0.1);
			}
		}
}

module base(alto,ancho,largo,anc){
	difference() {
		cylinder(h=alto, r=ancho+largo,$fa=1,$fs=0.1);
		translate([0,0,-1]){
			difference() {
				cylinder(h=alto-anc, r=ancho+largo+1,$fa=1,$fs=0.1);
				translate([0,0,-1]){
					cylinder(h=alto-anc+2, r=ancho,$fa=1,$fs=0.1);
				}
			}
		}
	}
}

module led(ancho1, profundo1, ancho2){
translate([0,0,ha+1]){
rotate([180,0,0]){
	cylinder(h=profundo1, r=ancho1,$fa=1,$fs=0.1);
	difference(){
		hull(){
		translate([ancho1/2,0,0]){
		cylinder(h=ha+2,r=ancho2,$fa=1,$fs=0.1);
		}
		translate([-(ancho1/2),0,0]){
		cylinder(h=ha+2,r=ancho2,$fa=1,$fs=0.1);
		}}
		cube(size = [1,2,ha+100], center = true);
	}
}}
}

module toSubstract(){
		arandela(8.5,15.4,3.9);
		arandela(3.5,7,2.2);
}

module base_arandelas(a,ab,b){

translate([0,0,ha+0.1]){
rotate([180,0,0]){
difference(){

translate([0,0,ha+0.1]){
rotate([180,0,0]){
		base(ha,a,ab,b);
}
}
		toSubstract();
	}
}}}

module cable(dist){
translate([dist,0,-3]){
cylinder(h=ha, r=1,$fa=1,$fs=0.1);
translate([0,0,ha]){
sphere(2, $fa=1, $fs=0.1);
}
}
}

module cable2(dist){
translate([-dist,0,-1.5]){
cylinder(h=ha, r=1,$fa=1,$fs=0.1);
translate([0,0,ha]){
sphere(1.5, $fa=1, $fs=0.1);
}
}
}


ha=20;
a=17;
ab=2;
b=1;


difference(){
base_arandelas(a,ab,b);
led(3.1,8,1);
cable(12.25);
cable2(5.25);
}
