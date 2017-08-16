// Event listener to ensure that username and password are both at least 7 characters long
//focus username text input when page has loaded

window.onload = function start() {
	var username = document.getElementById('username');
	var username_alert = document.getElementById('username_alert');
	var password = document.getElementById('password');
	var password_alert = document.getElementById('password_alert');
	var form = document.getElementById('submit');

	form.onsubmit = function() {
		if(username.value.length < 7) {
			username_alert.innerHTML = '<i>7 character minimum</i>';
			return false;
		}
		if(password.value.length < 7) {
			password_alert.innerHTML = '<i>7 character minimum</i>';
			return false;
		}
	}
}


function focus_username() {
	var user_input = document.getElementById('username');
	user_input.focus();
}

window.addEventListener('load', focus_username, false);