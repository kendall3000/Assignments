// JavaScript Document
function checkUsername() 
{// Declare function  
    var elMsg = document.getElementById('feedback');// Get feedback element  
    var elUsername = document.getElementById('username');// Get username input  
    if (elUsername.value.length < 5)// If username too short
    {    
        elMsg.classList.add("red");
        elMsg.innerHTML = 'Username must be 5 characters or more'; // Set msg  
    } 
    else 
    {
        elMsg.innerHTML = '';
    }
}
var el = document.getElementById('username');
el.addEventListener('blur',checkUsername,false);