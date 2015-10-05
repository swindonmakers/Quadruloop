include <moreShapes.scad>;

use <backbone.scad>;
use <hip.scad>;
use <servo.scad>;
include <coxa.scad>;
include <femur.scad>;
include <tibia.scad>;

bb_length=110;
bb_height = 8;

servo_length = 23;
servo_width = 12.5;

h_pos = (bb_length-20)/2;

hexapod = false;

// parts for printing
// =============================================================================
//mirror([1,0,0])
//tibia2();
//mirror([0,0,1])
//femur();
//mirror([1,0,0])
//coxa();
//servoDrillJig();
//backbone();

// assemblies
// =============================================================================
if (true) {
	// wheel mode
	finalAssembly(0, -130, 130, hexapod);

	// walking mode
	translate([0, 300, 28])
		finalAssembly(45, 0, -20, hexapod);
}

// =============================================================================

module finalAssembly(coxa_rot_angle, femur_angle, tibia_angle, hexapod) {

		if (hexapod) {
			hexapodBackbone();

			hipAssembly(0, femur_angle, tibia_angle);

			for ( i = [0, 1]){
				rotate([0,0,i*180])
				translate([0, 2*h_pos,0])
					hipAssembly(coxa_rot_angle, femur_angle, tibia_angle);
			}

		} else {
			// battery - modelled on a zippy 850mah 2s lipo
			color("yellow")
				translate([-28,-15,-20])
				cube([56,30,14]);

			// APM2.5
			color("grey")
				translate([-33,-21,6])
				cube([66, 42, 10]);

			backbone();

			for ( i = [0, 1]){
				rotate([0,0,i*180])
				translate([0, h_pos,0])
					hipAssembly(coxa_rot_angle, femur_angle, tibia_angle);
			}
		}
}

module hipAssembly(coxa_rot_angle, femur_angle, tibia_angle) {
	translate([0,0,(bb_height/2)])
		hip(servo_length,servo_width);

	for (j = [1, -1]) {
		translate([j*22.5,0,8]) {
			rotate([0,0,j*-90]) color("blue") servo();

			translate([j*-.5,0,-2.5]) rotate([90,0,j*coxa_rot_angle]) {
				scale([j*1,1,-1]) coxa();
				translate([j*26.5,6,0]) rotate([0,180,0]) {
					color("blue") servo();
					translate([0,0,12]) scale([j,1,1]) rotate([0,0,180 + femur_angle]) {
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
