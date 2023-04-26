var launched = 0;

var altCanv = document.getElementById("altGraph");
var altCtx = altCanv.getContext("2d");

var altImgs = [];
altImgs.length = 2;

altImgs[0] = new Image();
altImgs[0].src = "sprites/alt.png";
altImgs[1] = new Image();
altImgs[1].src = "sprites/rocket.png";

//Centers the blip at the origin
// var altT = altCanv.width - 284;
var altT = .053*altCanv.width;
var altA = .875*altCanv.height;


//Draw graph background once source has loaded
altImgs[0].addEventListener("load", function() {
	altCtx.drawImage(altImgs[0], 0, 0, altCanv.width, altCanv.height);
	altCtx.drawImage(altImgs[1], altT, altA, altCanv.width/25, altCanv.height/10);
}, false);


//Update blip to reflect new relative position
function updateAltitude(time, altitude) {
	var lLight = document.getElementById("launchLight");
	
	if(lLight.getAttribute("class") == "green-dot") {
		launched = 1;
	}
	
	var prevAltT = altT;
	var prevAltA = altA;
	altCtx.clearRect(prevAltT, prevAltA, altCanv.width/25, altCanv.height/10);
	
	if(launched) {
		altT = .053*altCanv.width + 2.172 * (time / 1000);
		if(!(altT >= .053*altCanv.width && altT <= .85*altCanv.width))
			altT = prevAltT;
		
		altA = .875*altCanv.height - .1067 * altitude;
		if(!(altA >= .02*altCanv.height && altA <= .875*altCanv.height)) {
			altA = prevAltA;
		}
	}
	
	//Redraw GPS background
	altCtx.drawImage(altImgs[0], 0, 0, altCanv.width, altCanv.height);
	//Redraw GPS blip to reflect new coordinates
	altCtx.drawImage(altImgs[1], altT, altA, altCanv.width/25, altCanv.height/10);
}