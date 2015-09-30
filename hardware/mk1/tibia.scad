
module tibia(sl = 23, sw = 12.5){
	difference(){
		//solid parts
		union(){
			hull(){
				//main inner square
				translate([-30,-10,0]) cube([28,20,4]);
				//lower taper
				translate([5,-1.5,0]) cube([2,3,4]);
			}

			//leg
			translate([0,-1.5,0]) cube([40,3,4]);
			//top bar
			translate([-33,-7,0]) cube([6,14,4]);
			//rounded corners
			for (i = [ [-30,7,0],[-30,-7,0] ]){
				translate(i) cylinder(r=3,h=4,$fn=50);
			}
		}
		//servo mounts
		for (i = [ [-3,0,-2],[-31,0,-2] ]){
			translate(i) cylinder(r=1,h=20,$fn=20);
		}
		//hole for servo body
		translate([-17,0,2])  cube([sl,sw,22], center=true);
	}
}

// rounded tibia for rolling on :)
module tibia2(sl = 23, sw = 12.5) {
	wheelThickness = 6;
	or = 70;
	ir = or - wheelThickness;
	flangeW = 12;

	difference(){
		//solid parts
		union(){
			hull(){
				//main inner square
				translate([-30,-10,0]) cube([28,20,4]);
				//lower taper
				translate([5,-1.5,0]) cube([2,3,4]);
			}

			//top bar
			translate([-33,-7,0]) cube([6,14,4]);
			//rounded corners
			for (i = [ [-30,7,0],[-30,-7,0] ]){
				translate(i) cylinder(r=3,h=4,$fn=50);
			}

			// wheel section
			translate([-44, ir - 20,0]) {
				// main section
				rotate([0,0,-80]) {

					// section
					sector3D(r=or, ir=ir, a=160, h=4, center = false, $fn=64);

					//flange
					sector3D(r=or, ir=or-1, a=155, h=flangeW, center = false, $fn=64);

					// add rounded tips to the wheel section
					for (i=[0,1])
						rotate([0,0,i*160])
						translate([or - wheelThickness/2,0,0])
						cylinder(r=3, h=4);
				}

			}





		}
		//servo mounts
		for (i = [ [-3,0,-2],[-31,0,-2] ]){
			translate(i) cylinder(r=1,h=20,$fn=20);
		}
		//hole for servo body
		translate([-17,0,2])  cube([sl,sw,22], center=true);
	}
}
