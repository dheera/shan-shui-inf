H=228 - 0.3;
W = 60;
WC=40;
T = 1;
HX=175+0.4;
WX1=31.5;
WX2=5;

module partA() {
    difference() {
        cube([H,W,T+2]);
        translate([1,1,T])
        cube([H-2,W,T+3]);
        
        translate([-15,15,T])
        cube([H+30,W,T+3]);
        
        translate([15,-15,T])
        cube([H-30,W+30,T+3]);
        
        translate([H/2-HX/2+(14-4)/2,WX1,0])
        cube([HX,W,T]);
    }
}

module partB() {
    mirror([0,1,0])
    partA();
}

module partC() {
    difference() {
        translate([0,-WC/2,0])
        cube([H,WC,T+2]);
        
        translate([0,-WC/2,0])
        translate([1,0,T])
        cube([H-2,WC,T+3]);
        
        translate([H/2-HX/2+(14-4)/2,WX2/2,0])
        cube([HX,W,T]);
        
        mirror([0,1,0]) 
        translate([H/2-HX/2+(14-4)/2,WX2/2,0])
        cube([HX,W,T]);
    }
}

/*
partA();
translate([0,-3,0])
partB();
*/
partC();