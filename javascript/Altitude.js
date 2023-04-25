var launched = 0;

var altCanv = document.getElementById("altGraph");
var altCtx = altCanv.getContext("2d");

var altImgs = [];
altImgs.length = 2;

altImgs[0] = new Image();
altImgs[0].src = "sprites/alt.png";
altImgs[1] = new Image();
altImgs[1].src = "sprites/dot.png";

//Draw graph background once source has loaded
altImgs[0].addEventListener("load", function() {
	altCtx.drawImage(altImgs[0], 0, 0, altCanv.width, altCanv.height);
}, false);

//Centers the blip at the origin
var altT = altCanv.width - 280;
var altA = altCanv.height - 13;

//Update blip to reflect new relative position
setInterval(function() {
	var lLight = document.getElementById("launchLight");
	
	if(lLight.getAttribute("class") == "green-dot") {
		launched = 1;
	}
	
	var prevAltT = altT;
	var prevAltA = altA;
	altCtx.clearRect(prevAltT, prevAltA, altCanv.width/50, altCanv.height/50);
	
	if(launched) {
	
	}
	
	//Redraw GPS background
	altCtx.drawImage(altImgs[0], 0, 0, altCanv.width, altCanv.height);
	//Redraw GPS blip to reflect new coordinates
	altCtx.drawImage(altImgs[1], altT, altA, altCanv.width/50, altCanv.height/50);
}, 100);	