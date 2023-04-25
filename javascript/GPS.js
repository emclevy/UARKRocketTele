var launched = 0;

var gpsCanv = document.getElementById("gps");
var gpsCtx = gpsCanv.getContext("2d");

var gpsImgs = [];
gpsImgs.length = 2;

gpsImgs[0] = new Image();
gpsImgs[0].src = "sprites/gps.png";
gpsImgs[1] = new Image();
gpsImgs[1].src = "sprites/dot.png";

//Draw graph background once source has loaded
gpsImgs[0].addEventListener("load", function() {
	gpsCtx.drawImage(gpsImgs[0], 0, 0, gpsCanv.width, gpsCanv.height);
}, false);

//Centers the blip at the origin
var gpsX = gpsCanv.width/2 - 3;
var gpsY = gpsCanv.height/2 - 2;

//Update blip to reflect new relative position
setInterval(function() {
	var lLight = document.getElementById("launchLight");
	
	if(lLight.getAttribute("class") == "green-dot") {
		launched = 1;
	}
	
	var prevGPSX = gpsX;
	var prevGPSY = gpsY;
	gpsCtx.clearRect(prevGPSX, prevGPSY, gpsCanv.width/50, gpsCanv.height/50);
	
	if(launched) {
		if(prevGPSX < gpsImgs[0].width - 267) {
			gpsX++;
			<!-- console.log("Current gps X: " + gpsX); -->
		}
		if(prevGPSY < gpsImgs[0].height - 410) {
			gpsY++;
			<!-- console.log("Current GPS Y: " + gpsY); -->
		}
	}
	
	//Redraw GPS background
	gpsCtx.drawImage(gpsImgs[0], 0, 0, gpsCanv.width, gpsCanv.height);
	//Redraw GPS blip to reflect new coordinates
	gpsCtx.drawImage(gpsImgs[1], gpsX, gpsY, gpsCanv.width/50, gpsCanv.height/50);
}, 100);	