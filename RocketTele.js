

let count = setInterval(display, 300);
let end = 15;
function display(){
        var answer = document.getElementById('Accel');
        answer.value = ++end;
        if(end === 200) {
            clearInterval(count)
        }
    }





