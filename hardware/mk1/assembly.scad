include <moreShapes.scad>;

use <backbone.scad>;
use <hip.scad>;
use <servo.scad>;
use <coxa.scad>;
include <femur.scad>;
include <tibia.scad>;

bb_length=90;
bb_height = 8;

servo_length = 23;
servo_width = 12.5;

wheel = true;  // true to show in wheel configuration, false for walking config

coxa_rot_angle = wheel ? 0 : 30;
femur_angle = wheel ? -130 : 0;
tibia_angle = wheel ? 130 : -20;

show_full_assembly=1;
h_pos = (bb_length-20)/2;

//tibia2();
//femur();

if (show_full_assembly==1){
	//full assembly example
	backbone();

	for ( i = [1, -1]){
		translate([0,i*h_pos,(bb_height/2)])
			hip(servo_length,servo_width);

		for (j = [1, -1]) {
			translate([j*22.5,i*h_pos,8]) {
				rotate([0,0,j*-90]) color("blue") servo();

				translate([j*-.5,0,-2.5]) rotate([90,0,i*j*coxa_rot_angle]) {
					scale([j*1,1,i*-1]) coxa();
					translate([j*26.5,6,0]) rotate([0,90 + i*90,0]) {
						color("blue") servo();
						translate([0,0,11]) scale([j*i,1,1]) rotate([0,0,180 + femur_angle]) {
							femur();
							translate([40, 0, -11]) rotate([0, 0, 90 + tibia_angle]) {
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
