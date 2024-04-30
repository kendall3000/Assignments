// JavaScript Document
var today = new Date();
var hourNow = today.getHours();
var greeting;
var el=document.getElementById("greeting");

if (hourNow > 18){
	greeting = 'Good evening!'
} else if(hourNow > 12){
	greeting = 'Good afternoon!'
}else if(hourNow > 0){
	greeting = 'Good morning!'
} else{
	greeting = 'Welcome!'
}
el.innerHTML='<h3>' + greeting + '</h3>';
//document.write('<h3>' + greeting + '</h3>');
