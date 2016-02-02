$fn=50;
batteryMount();

module batteryMount()
{
	linear_extrude(2) {
		// battery plate
		difference() {
			roundedSquare(55, 30, 2);
			
			for (x=[-20, -10, 10, 20])
			translate([x, 0, 0])
			roundedSquare(5, 20, 2);
		}
	}

	// Center protruding mount
	linear_extrude(2 + 5)
		square([8,14], center=true);

	// circluar mount plug
	linear_extrude(2 + 5 + 8)
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
