

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
        // var peakAltitude = document.getElementById('PAlti');
        
        //get value for speed
        var spee = speed.value;
        spee++
        speed.value = spee;
        //get value for acc
        var acc = acceleration.value;
        acc++
        acceleration.value = acc;
        //get value for alt
        // var alt = altitude.value;
        // alt++
        // altitude.value = alt;
        // peakAltitude = alt;

        //gets peak speed
        if(peakSpeed.value <= spee) {
            peakSpeed.value = spee;
        }
        //gets peak acceleration value
        if(peakAcceleration.value <= acc) {
            peakAcceleration.value = acc;
        }
        //gets peak alt
        

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





