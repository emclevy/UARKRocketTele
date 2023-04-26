var launched = 0;

var rktCanv = document.getElementById('orientation');
var rktCtx = rktCanv.getContext('2d');

var rktImg = new Image();
rktImg.src = "sprites/rocket.png";

var rktTilt = 0;
var rktAspect, rktMaxW, rktMaxH, rktW, rktH, rktX, rktY;


//Draw the rocket's initial orientation once the source image has loaded
rktImg.addEventListener("load", function() {
	rktCtx.clearRect(0, 0, rktCanv.width, rktCanv.height);

	rktAspect = rktImg.width / rktImg.height;

	//Calculate the maximum size of the sprite image based on the canvas size
	rktMaxW = rktCanv.width * 1.4;
	rktMaxH = rktCanv.height * 1.4;

	// Calculate the width and height of the sprite image based on the aspect ratio and canvas size
	rktW = Math.min(rktMaxW, rktMaxH * rktAspect);
	rktH = Math.min(rktMaxH, rktMaxW * rktAspect);

	// Calculate the position to draw the sprite image based on the canvas size and sprite size
	rktX = (rktCanv.width - rktW) / 2;
	rktY = (rktCanv.height - rktH) / 2;

	// Draw the sprite image with the adjusted size and position
	rktCtx.drawImage(rktImg, rktX, rktY, rktW, rktH);
	
}, false);


//Update orientation display
function updateOrientation(tilt) {
	var lLight = document.getElementById("launchLight");
	
	//Check if launch has initiated
	if(lLight.getAttribute("class") == "green-dot") {
		launched = 1;
	}
	
	if(launched) {
		var prevTilt = rktTilt;
		rktCtx.clearRect(0, 0, rktCanv.width, rktCanv.height);
		
		//To account for how the image is drawn through the canvas with rotation, needed some adjustment
		//to make it accurately reflect the tilt
		rktTilt = -(tilt - 90);
		if(rktTilt == 360)
			rktTilt = 0;
		
		rktCtx.translate(rktX + rktW / 2, rktY + rktH / 2);
		
		//Remove previous tilt so rotation stays linear
		rktCtx.rotate(-prevTilt*Math.PI/180);
		//Apply new rotation
		rktCtx.rotate(rktTilt*Math.PI/180);
		
		rktCtx.translate(-(rktX + rktW / 2), -(rktY + rktH / 2));
		
		rktCtx.drawImage(rktImg, rktX, rktY, rktW, rktH);
	}
}