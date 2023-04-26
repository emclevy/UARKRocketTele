var launched = 0;

var gpsCanv = document.getElementById("gps");
var gpsCtx = gpsCanv.getContext("2d");


//Load in the images for visualizing the GPS
var gpsImgs = [];
gpsImgs.length = 2;

gpsImgs[0] = new Image();
gpsImgs[0].src = "sprites/gps.png";
gpsImgs[1] = new Image();
gpsImgs[1].src = "sprites/dot.png";

//Centers blip at the origin
var gpsX = gpsCanv.width/2 - 3;
var gpsY = gpsCanv.height/2 - 2;

//Draw graph background once source has loaded
gpsImgs[0].addEventListener("load", function() {
	gpsCtx.drawImage(gpsImgs[0], 0, 0, gpsCanv.width, gpsCanv.height);
	gpsCtx.drawImage(gpsImgs[1], gpsX, gpsY, gpsCanv.width/50, gpsCanv.height/50);
}, false);

//Update blip to reflect new relative position
function updateGPS(velocity, tilt) {
	var lLight = document.getElementById("launchLight");
	
	//Checks if the rocket launch has been initiated
	if(lLight.getAttribute("class") == "green-dot") {
		launched = 1;
	}
	
	var prevGPSX = gpsX;
	var prevGPSY = gpsY;
	gpsCtx.clearRect(prevGPSX, prevGPSY, gpsCanv.width/50, gpsCanv.height/50);
	
	//Given the test data we had, we had no means of calculating an actual displacement from the original position, 
	//as the simulation we sourced the data from only provided vertical velocity
	if(launched) {
		if(prevGPSX < gpsImgs[0].width - 267 && prevGPSX > 5) {
			gpsX = prevGPSX + Math.abs(velocity * 1.75) * Math.abs(Math.sin(90 - tilt) / (163 * 2.5));
		}
		if(prevGPSY < gpsImgs[0].height - 410 && prevGPSY > 5) {
			gpsY = prevGPSY - Math.abs(velocity * 1.75) * Math.abs(Math.sin(90 - tilt) / (250 * 2.5));
		}
	}
	
	//Redraw GPS background
	gpsCtx.drawImage(gpsImgs[0], 0, 0, gpsCanv.width, gpsCanv.height);
	//Redraw GPS blip to reflect new coordinates
	gpsCtx.drawImage(gpsImgs[1], gpsX, gpsY, gpsCanv.width/50, gpsCanv.height/50);
}	