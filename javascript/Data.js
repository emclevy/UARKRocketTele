
// let count = setInterval(display, 300);
//let end = 15;
// function display(){
	// //live data variables
	// var acceleration = document.getElementById('Accel');
	// var speed = document.getElementById('Vel');
	// //var altitude = document.getElementById('')
	// //peak variables
	// var peakAcceleration = document.getElementById('PAccel');
	// var peakSpeed = document.getElementById('PSpeed');
	// var peakAltitude = document.getElementById('PAlti');
	// var ejectAlt = document.getElementById('Eject');
	


	// //get value for speed
	// var spee = parseFloat(speed.value);
	// spee++
	// speed.value = spee.toFixed(2) + " m/s"; // Replace "units" with the actual units (e.g., "m/s")

	
	// //get value for acc
	// var acc = parseFloat(acceleration.value);
	// acc++
	// acceleration.value = acc.toFixed(2) + " m/s²";

	
	// //get value for alt
	// var alt = 0;
	// alt++
	// // altitude.value = alt;
	// // peakAltitude = alt;
	

	// //gets peak speed
	// if(peakSpeed.value <= spee) {
		// peakSpeed.value = spee;
	// }
	// //gets peak acceleration value
	// if(peakAcceleration.value <= acc) {
		// peakAcceleration.value = acc;
	// }
	// //gets peak alt
	// if(peakAltitude.value <= alt){
		// peakAltitude.value = alt;
	// }


	// //resets testing back to 0 
	// if(speed.value == 50) {
		// speed.value = 0;
		// clearInterval(count);
	// }
	// if(acceleration.value == 50) {
		// acceleration.value = 0;
		// clearInterval(count);
	// }
// }


function beginLaunch() {
	var eLight = document.getElementById("engineLight");
	var lButton = document.getElementById("launchButton");
	
	eLight.setAttribute("class", "green-dot");
	
}

//Upon pressing the button to eject the drogue parachute, change ejection light to green and remove "Eject drogue" button
function toggleDrogue() {
	var dLight = document.getElementById("drogueLight");
	var dButton = document.getElementById("drogueButton");
	
	dLight.setAttribute("class", "green-dot");
}

//Upon pressing the button to eject the primary parachute, change ejection light to green and remove "Eject chute" button
function toggleChute() {
	var cLight = document.getElementById("chuteLight");
	var cButton = document.getElementById("chuteButton");
	
	cLight.setAttribute("class", "green-dot");
	
}






