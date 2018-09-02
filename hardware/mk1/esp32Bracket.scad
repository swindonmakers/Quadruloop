$fn=50;
esp32Bracket();

module esp32Bracket()
{
	linear_extrude(2) {
		// central strut
		rotate([0, 0, 90])
			backbone(bl = 41.5);
			
		difference() {
			// end bars
			union() {
				for (i=[0, 1])
				mirror([i, 0, 0])
				translate([41.5/2 + 5.5/2, 0])
					roundedSquare(5.5, 29, 2.25);
				
			}

			// modeMcu mount holes
			for (i=[0, 1], j=[0, 1])
			mirror([i, 0, 0])
			mirror([0, j, 0])
			//translate([43.5/2, 21/2])
			translate([47/2, 23.5/2])
				circle(d=3);
		}
	}

	// Center protruding mount
	linear_extrude(10)
		square([8,14], center=true);

	// circluar mount plug
	linear_extrude(10 + 8)
	difference() {
		circle(d=5.5);
		circle(d=2);
	}
}

module roundedSquare(x, y, r)
{
	hull()
	for (i=[0,1], j=[0,1])
	mirror([i, 0, 0])
	mirror([0, j, 0])
	translate([x/2 - r, y/2 - r])
		circle(r=r);
}

module backbone(bl = 110,bw = 14,bh = 8,sl = 23,sw = 12.5){
	h_pos = ((bl-20) / 2);
	difference(){
		// main
		translate([-(bw/2),-(bl/2)]) 
			square([bw,bl]);

		//round side indents
		for (i = [[34,17,0],[34,-17,0],[-34,17,0],[-34,-17,0]]) {
			translate(i) 
				circle(r=30,$fn=64);
		}

		//center hole
		circle(r=3,$fn=32);
	}
}