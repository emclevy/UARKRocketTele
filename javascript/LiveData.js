
let count = setInterval(display, 300);
//let end = 15;
function display(){
        //live data variables
        var acceleration = document.getElementById('Accel');
        var speed = document.getElementById('Vel');
        //var altitude = document.getElementById('')
        //peak variables
        var peakAcceleration = document.getElementById('PAccel');
        var peakSpeed = document.getElementById('PSpeed');
        var peakAltitude = document.getElementById('PAlti');
        var ejectAlt = document.getElementById('Eject');
        
        var boost1 = document.getElementById('Boost1');
        var boost2 = document.getElementById('Boost2');
        var boost3 = document.getElementById('Boost3');

    
        //get value for speed
        var spee = parseFloat(speed.value);
        spee++
        speed.value = spee.toFixed(2) + " m/s"; // Replace "units" with the actual units (e.g., "m/s")

        
        //get value for acc
        var acc = parseFloat(acceleration.value);
        acc++
        acceleration.value = acc.toFixed(2) + " m/s²";

        
        //get value for alt
        var alt = 0;
        alt++
        // altitude.value = alt;
        // peakAltitude = alt;
        

        //boost
        if(boost1.value < 16){
            boost1.value++;
        } else if(boost2.value < 32 && boost1.value === 16){
            boost2.value++;
        } else if(boost3.value < 48 && boost2.value === 32){
            boost3.value++;
        }
        

        //gets peak speed
        if(peakSpeed.value <= spee) {
            peakSpeed.value = spee;
        }
        //gets peak acceleration value
        if(peakAcceleration.value <= acc) {
            peakAcceleration.value = acc;
        }
        //gets peak alt
        if(peakAltitude.value <= alt){
            peakAltitude.value = alt;
        }

        // boosters
  var boost1MaxSpeed = 16;
  var boost2MaxSpeed = 32;
  var boost3MaxSpeed = 48;
  if (boost1.value < boost1MaxSpeed) {
    boost1.value++;
  } else if (boost2.value < boost2MaxSpeed) {
    boost2.value++;
  } else if (boost3.value < boost3MaxSpeed) {
    boost3.value++;
  }


   

        //resets testing back to 0 
        if(speed.value == 50) {
            speed.value = 0;
            clearInterval(count);
        }
        if(acceleration.value == 50) {
            acceleration.value = 0;
            clearInterval(count);
        }

       
         
    }





