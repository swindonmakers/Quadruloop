// alternate femur

include <servo_arm.scad>;

module femurBody(thickness, center_to_center, width) {
	translate([0,0,thickness/2])
		hullInPairs() {
			// end
			translate([center_to_center/2, 0, 0])
				cylinder(r = width/2, h = thickness, center = true);

			// midpoint
			translate([-7, 9, 0])
				cylinder(r = width/3, h = thickness, center = true);

			// end
			translate([-center_to_center/2, 0, 0])
				cylinder(r = width/2, h = thickness, center = true);
		}
}


module femur(thickness = 4, center_to_center = 40, width = 12) {
	translate([center_to_center/2, 0, 0])
	difference() {
		femurBody(thickness, center_to_center, width);

		// tibia
		color("red")
			translate([center_to_center/2,0,thickness + 0.01])
			rotate([0, 180, 71])
			servo_arm();

		// hip
		color("red")
			translate([-center_to_center/2,0,thickness + 0.01])
			rotate([0, 180, -55])
			servo_arm();
	}
}

//femur();
