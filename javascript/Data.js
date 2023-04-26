var dataLoaded = 0;
var launched = 0;
var dataDict = {};
var currentTime = 0;


//Loads in file from selected source (should always be "realtime.csv" in our case, if not, warn user and don't load)
function loadData(input) {
	if(input.files[0].name != "realtime.csv")
		alert("Program can currently only simulate over realtime.csv.");
	else {
		//Takes file from the HTML file input
		var dataFile = input.files[0];

		var dataReader = new FileReader();
		
		//Turns file contents into a string
		dataReader.readAsText(dataFile);

		//Once the file has loaded, read it into a dictionary with time as keys
		dataReader.onload = function() {
			var dataText = dataReader.result;
			//Start at the first line after the headers
			var i = dataText.indexOf('\n') + 1;
			var j = 0;
			var nextComma = 0;
			
			var nextTime = 0;
			var nextAlt = 0;
			var nextVel = 0;
			var nextAccel = 0;
			var nextVert = 0;
			var nextLat = 0;
			
			//Read each line into an array with the time (in ms) as the key
			while(i < dataText.length) {
				for(var j = 0; j <= 5; j++) {
					//Find index of the next comma (delimiting end of value to read)
					nextComma = dataText.indexOf(',', i);
					if(j == 0) {
						//Copy string from the current index until the next comma, exclusively
						nextTime = dataText.substring(i, nextComma);
						//Since time values are in seconds and will yield floats for milliseconds, multiply by 1000 and round
						nextTime = Math.round(nextTime * 1000);
						//Set index to just after the next comma
						i = nextComma + 1;
					}
					else if(j == 1) {
						nextAlt = dataText.substring(i, nextComma);
						i = nextComma + 1;
					}
					else if(j == 2) {
						nextVel = dataText.substring(i, nextComma);
						i = nextComma + 1;
					}
					else if(j == 3) {
						nextAccel = dataText.substring(i, nextComma);
						i = nextComma + 1;
					}
					else if(j == 4) {
						nextVert = dataText.substring(i, nextComma);
						//In the simulation, after the drogue chute deploys, vertical alignment becomes NaN, presumably 90 degrees
						//given the use of the drogue parachute
						if(nextVert == 'nan')
							nextVert = 90.00;
						i = nextComma + 1;
					}
					else if(j == 5) {
						//If not at end of file, copy value up to carriage return
						if(dataText.indexOf('\r', i) != -1)
							nextLat = dataText.substring(i, dataText.indexOf('\r', i));
						//Same as with vertical alignment, although lateral isn't really used much
						if(nextLat == 'nan')
							nextLat = 0.00;
						//Move all values into a key-value set, with time as the key and the array of associated data as the values
						dataDict[nextTime] = [nextAlt, nextVel, nextAccel, nextVert, nextLat];
						//Check if at the end of the file; if so, break, as no more values can be read
						i = dataText.indexOf('\n', i) + 1;
						if(i == 0)
							break;
					}
					if(i == 0)
						break;
				}
				if(i == 0)
					break;
			}
			
			//Broadcast test data as loaded, remove file selector and inform user
			dataLoaded = 1;
			document.getElementById("fileInField").remove();
			document.getElementById("fileLoaded").hidden = false;
		}

		dataReader.onerror = function() {
			console.log(dataReader.error);
		}
	}
}

function beginLaunch() {
	var lButton = document.getElementById("launchButton");
	var dButton = document.getElementById("drogueButton");
	var cButton = document.getElementById("chuteButton");
	
	var lLight = document.getElementById("launchLight");
	var aLight = document.getElementById("apogeeLight");
	var dLight = document.getElementById("drogueLight");
	var cLight = document.getElementById("chuteLight");
	var lanLight = document.getElementById("landLight");
	
	//Initiate rocket launch simulation
	if(!launched && dataLoaded) {
		lLight.setAttribute("class", "green-dot");
		lButton.setAttribute("class", "button-grayed");
		dButton.setAttribute("class", "button-active");
		dLight.setAttribute("class", "red-dot");
		cButton.setAttribute("class", "button-active");
		cLight.setAttribute("class", "red-dot");
		aLight.setAttribute("class", "red-dot");
		lanLight.setAttribute("class", "red-dot");
		launched = 1;
		
		//Update other displays every 10ms if an array exists in the read data
		setInterval(function() {
			if(dataDict[currentTime] == null) {
				// console.log("No data found for current time " + currentTime);
				currentTime += 10;
				return;
			}
			else {
				updateData(dataDict[currentTime][0], dataDict[currentTime][1], dataDict[currentTime][2], dataDict[currentTime][3]);
				updateOrientation(dataDict[currentTime][3]);
				updateGPS(dataDict[currentTime][1], dataDict[currentTime][3]);
				updateAltitude(currentTime, dataDict[currentTime][0]);
			}
			
			currentTime += 10;
		}, 10);
	}
	else if(!dataLoaded) {
		alert("Please select launch data to simulate.");
	}
}

function updateData(altitude, velocity, acceleration, tilt) {
	var altField = document.getElementById("altitude");
	var velField = document.getElementById("velocity");
	var accelField = document.getElementById("acceleration");
	
	var altPeak = document.getElementById("peakAlt");
	var speedPeak = document.getElementById("peakSpeed");
	var accelPeak = document.getElementById("peakAccel");
	
	var lanLight = document.getElementById("landLight");
	
	//Update altitude, velocity, and acceleration fields
	altField.setAttribute("value", altitude + " m");
	velField.setAttribute("value", velocity + " m/s");
	accelField.setAttribute("value", (acceleration / 9.81).toFixed(3) + " Gs");
	
	
	//Update peak altitude, speed, and acceleration fields
	if(altitude > parseFloat(altPeak.getAttribute("value").substring(0, altPeak.getAttribute("value").indexOf(" "))))
		altPeak.setAttribute("value", altitude + " m");
	
	if(Math.abs(velocity) > parseFloat(speedPeak.getAttribute("value").substring(0, speedPeak.getAttribute("value").indexOf(" "))))
		speedPeak.setAttribute("value", Math.abs(velocity) + " m/s");
	
	if(Math.abs(acceleration) > parseFloat(accelPeak.getAttribute("value").substring(0, accelPeak.getAttribute("value").indexOf(" "))))
		accelPeak.setAttribute("value", Math.abs(acceleration) + " Gs");
	
	
	//If the rocket's orientation drops below 55 degrees and the velocity is
	//verifiably downward, deploy the drogue chute
	if(tilt < 55 && velocity < -.2) {
		toggleDrogue();
	}
	
	//If altitude drops below 200 and the velocity is downward, deploy main parachute
	if(altitude <= 200 && velocity < -.2)
		toggleChute();
	
	//If altitude is very low and the velocity is downward, rocket has landed
	if(altitude < .33 && velocity < -.33) {
		lanLight.setAttribute("class", "green-dot");
		altField.setAttribute("value", "0 m");
		velField.setAttribute("value", "0 m/s");
		accelField.setAttribute("value", "0 Gs");
	}
}


//Upon pressing the button to eject the drogue parachute, change ejection light to green and remove "Eject drogue" button
function toggleDrogue() {
	var dLight = document.getElementById("drogueLight");
	var dButton = document.getElementById("drogueButton");
	
	var aLight = document.getElementById("apogeeLight");
	
	//If rocket has been launched, allow marking the drogue as deployed
	if(launched) {
		dLight.setAttribute("class", "green-dot");
		dButton.setAttribute("class", "button-grayed");
		aLight.setAttribute("class", "green-dot");
	}
}

//Upon pressing the button to eject the primary parachute, change ejection light to green and remove "Eject chute" button
function toggleChute() {
	var cLight = document.getElementById("chuteLight");
	var cButton = document.getElementById("chuteButton");
	
	//If rocket has been launched, allow marking main chute as deployed
	if(launched) {
		cLight.setAttribute("class", "green-dot");
		cButton.setAttribute("class", "button-grayed");
	}
}


