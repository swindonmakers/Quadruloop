include <moreShapes.scad>;

use <backbone.scad>;
use <hip.scad>;
use <servo.scad>;
include <coxa.scad>;
include <femur.scad>;
include <tibia.scad>;

bb_length=90;
bb_height = 8;

servo_length = 23;
servo_width = 12.5;

h_pos = (bb_length-20)/2;

// parts for printing
// =============================================================================
//tibia2();
//femur();
//mirror([1,0,0])
//coxa();


// assemblies
// =============================================================================
if (false) {
	// wheel mode
	finalAssembly(0, -130, 130);

	// walking mode
	translate([0, 300, 28])
		finalAssembly(45, 0, -20);
}

finalAssembly(0, -130 + 00, 130);

// =============================================================================

module finalAssembly(coxa_rot_angle, femur_angle, tibia_angle) {

		// battery - modelled on a zippy 850mah 2s lipo
		color("yellow")
			translate([-28,-15,-20])
			cube([56,30,14]);

		// APM2.5
		color("grey")
			translate([-33,-21,6])
			cube([66, 42, 10]);

		backbone();

		//for ( i = [1, -1]){
		for ( i = [1]){
			translate([0,i*h_pos,(bb_height/2)])
				hip(servo_length,servo_width);

			for (j = [1, -1]) {
				translate([j*22.5,i*h_pos,8]) {
					rotate([0,0,j*-90]) color("blue") servo();

					translate([j*-.5,0,-2.5]) rotate([90,0,i*j*coxa_rot_angle]) {
						scale([j*1,1,i*-1]) coxa();
						translate([j*26.5,6,0]) rotate([0,90 + i*90,0]) {
							color("blue") servo();
							translate([0,0,12]) scale([j*i,1,1]) rotate([0,0,180 + femur_angle]) {
								femur();
								translate([40, 0, -12]) rotate([0, 0, 90 + tibia_angle]) {
									color("blue") servo();
									translate([0, -22, -4]) rotate([0, 0, -90]) tibia2();
								}
							}
						}
					}
				}
			}
		}
}
