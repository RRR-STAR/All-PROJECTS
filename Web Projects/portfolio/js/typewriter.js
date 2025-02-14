document.addEventListener('DOMContentLoaded',function(event){
    
    // array with texts to type in typewriter
    var dataText = [
        "Modern C++ Developer",
        "Object Oriented Programming",
        "Game Devlopment",
        "Python Programmer",
        "MySQL & DBMS",
        "Operating Systems",
        "Software Engineering",
    ];
    
    // type one text in the typwriter
    // keeps calling itself until the text is finished
    function typeWriter(text, i, fnCallback) {
        
        // chekc if text isn't finished yet
        if (i < (text.length)) {
            
            // add next character to h1
            document.querySelector("h2").innerHTML = "<i>" + text.substring(0, i+1) + " ></i>";
            
            // wait for a while and call this function again for next character
            setTimeout(function(){ typeWriter(text, i + 1, fnCallback) }, 50);
        }
        // text finished, call callback if there is a callback function
        else if (typeof fnCallback == 'function') { // call callback after timeout
            setTimeout(fnCallback, 1500);
        }
    }
    
    // start a typewriter animation for a text in the dataText array
    function StartTextAnimation(i) {
        
        if (typeof dataText[i] == 'undefined'){
            setTimeout(function(){ StartTextAnimation(0); }, 300);
        }
        // check if dataText[i] exists
        if (i < dataText[i].length){
            // text exists! start typewriter animation
            // after callback (and whole text has been animated), start next text
            typeWriter(dataText[i], 0, function(){ StartTextAnimation(i + 1); });
        }
    }
    // start the text animation
    StartTextAnimation(0);
});