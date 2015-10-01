// 3dof quad
//
// coxa

include <servo.scad>
include <servo_arm.scad>

module coxa(servo_height = 29, servo_clearance = 7) {
	arm_thick = 4;
	servo_width = 12;
	flange_length = 3;
	base_thick = 4;
	root_radius = 4;

	fork_width = servo_width + flange_length + servo_clearance + base_thick;
	fork_height = arm_thick * 2 + servo_height;

	servo_cog_offset = 6;

	translate([fork_width/2 - servo_cog_offset, 0, 0])
		union() {
			difference() {
				cube([fork_width, fork_height, 12], center = true);

				// hollow for hip
				translate([-root_radius/2 - base_thick/2 - 1, 0, 0])
					cube([1 + servo_width + flange_length + servo_clearance - root_radius, servo_height, 13], center = true);

				translate([-base_thick/2, 0, 0])
					cube([servo_width + flange_length + servo_clearance, servo_height-2*root_radius, 13], center = true);

				translate([5, -10.5, 0])
					cylinder(r = root_radius, h = 13, center = true);

				translate([5, 10.5, 0])
					cylinder(r = root_radius, h = 13, center = true);

				// hip servo arm
				color("white")
					translate([servo_cog_offset - fork_width/2, 0.1 + fork_height/2, 0])
					rotate([90, 90, 0])
					servo_arm();

				// pilot hole for axle into base of hip servo
				translate([servo_cog_offset - fork_width/2, - fork_height/2, 0])
					rotate([90, 90, 0])
					cylinder(r=1, h=20, center=true);
			}

			// support for coxa servo
			translate([fork_width/2 + 15/2, 0, -3]) {
				difference() {
					union() {
						translate([-5,0,0])
							cube([10, fork_height, 6], center = true);
						roundedRect([15, fork_height, 6], 7.5, center = true);
					}

					translate([-1, 0, 0]) cube([12.5, 23.5, 7], center = true);
					for(i = [-1, 1]) {
						translate([-1, i * 28/2, 0]) cylinder(r=1, h=20, center = true);
					}
				}
			}
		}
}

//translate([0,15,0]) coxa();
//scale([-1, 1, 1]) coxa();
