// alternate femur

include <servo_arm.scad>;

module body(thickness, center_to_center, width) {
	difference() {
		translate([0,0,thickness/2]) union() {
			difference() {
				cube([center_to_center, width, thickness], center = true);
				translate([0,-31, -.1]) cylinder(r=30, h=thickness+.3, center = true);
			}
			for(x = [+center_to_center/2, -center_to_center/2]) 
				translate([x, 0, 0]) cylinder(r = width/2, h = thickness, center = true);
		}
	}

}


module femur(thickness = 4, center_to_center = 40, width = 12) {
	translate([center_to_center/2, 0, 0])
	difference() {
		body(thickness, center_to_center, width);
		color("red") translate([center_to_center/2,0,thickness + 0.01]) rotate([0, 180, 80]) servo_arm();
		color("red") translate([-center_to_center/2,0,thickness + 0.01]) rotate([0, 180, -80]) servo_arm();
	}
}

femur();