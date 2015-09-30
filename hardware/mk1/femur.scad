// alternate femur

include <servo_arm.scad>;

module femurBody(thickness, center_to_center, width) {

	sp = 30;

	difference() {
		for (z=[-sp-2.5, 0])
			translate([0,0,thickness/2 + z])
				hullInPairs() {
					// end
					translate([center_to_center/2, 0, 0])
						cylinder(r = width/2, h = thickness, center = true);

					// midpoint
					translate([0, 0, 0])
						cylinder(r = width/2, h = thickness, center = true);

					// end
					translate([-center_to_center/2, 0, 0])
						cylinder(r = width/2, h = thickness, center = true);
				}

		// holes for screws in back of servos
		for (i=[-1,1])
			translate([i * center_to_center/2, 0, 0])
			cylinder(r = 1, h = 100, center = true, $fn=12);
	}


	// cross beam
	hull() {
		translate([5, -width/2, -sp])
			cube([2,1,sp+1]);

		translate([-4, width/2 - 1, -sp])
			cube([2,1,sp+1]);
	}
}


module femur(thickness = 4, center_to_center = 40, width = 12) {
	translate([center_to_center/2, 0, 0])
	difference() {
		femurBody(thickness, center_to_center, width);

		// tibia
		color("red")
			translate([center_to_center/2,0,thickness + 0.01])
			rotate([0, 180, 90])
			servo_arm();

		// hip
		color("red")
			translate([-center_to_center/2,0,thickness + 0.01])
			rotate([0, 180, -90])
			servo_arm();

		// servo arm secondary fixings
		for (i=[-1,1])
			translate([i*(center_to_center/2 - 14.5), 0, 0])
			cylinder(r=0.7, h=20, center=true, $fn=12);
	}
}

//femur();
