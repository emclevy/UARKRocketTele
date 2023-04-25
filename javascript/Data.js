var dataLoaded = 0;
var launched = 0;


//Loads in file from selected source (should always be "realtime.csv" in our case, if not, warn user and don't load)
function loadData(input) {
	if(input.files[0].name != "realtime.csv")
		alert("Program can currently only simulate over realtime.csv.");
	else {
		var dataFile = input.files[0];

		var dataReader = new FileReader();

		dataReader.readAsText(dataFile);

		dataReader.onload = function() {
			console.log(dataReader.result);
		}

		dataReader.onerror = function() {
			console.log(dataReader.error);
		}
		
		dataLoaded = 1;
		document.getElementById("fileInField").remove();
		document.getElementById("fileLoaded").hidden = false;
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
	}
	else if(!dataLoaded) {
		alert("Please select launch data to simulate.");
	}
}

//Upon pressing the button to eject the drogue parachute, change ejection light to green and remove "Eject drogue" button
function toggleDrogue() {
	var dLight = document.getElementById("drogueLight");
	var dButton = document.getElementById("drogueButton");
	
	//If rocket has been launched, allow marking the drogue as deployed
	if(launched) {
		dLight.setAttribute("class", "green-dot");
		dButton.setAttribute("class", "button-grayed");
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



