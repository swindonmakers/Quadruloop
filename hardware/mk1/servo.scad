// 3dof quad
//
// servo



module servo(a = 30, b = 23, c = 27, d = 12, e = 33, f = 16, flange_thickness = 2, top_cap_pct = 0.5) {
	rem_height = c - flange_thickness - f;
	top_cap_height = rem_height * top_cap_pct;
	roundel_height = rem_height * (1.0 - top_cap_pct);	

	translate([0, -d/2, 0]) union() {
		translate([0,0,flange_thickness/2]) cube([d, e, flange_thickness], center = true);
		translate([0,0,-f/2]) cube([d, b, f], center = true);
		translate([0,0,flange_thickness + top_cap_height/2]) cube([d, b, top_cap_height], center = true);
		translate([0,b/2 - d/2,flange_thickness + top_cap_height]) union() {
			cylinder(r = d/2, h = roundel_height);
			translate([0,0,roundel_height]) cylinder(r = 3, h = 3);
		}
	}
}

//color("blue") servo();