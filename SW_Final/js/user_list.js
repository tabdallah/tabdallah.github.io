// https://stackoverflow.com/questions/5835126/javascript-infinite-loop

var users_data = {};
var users = document.getElementById('users');

window.onload = function start(){
    
    // Get users info as JSON from the users table
    $.ajax({
        url: '../php/get_users.php',
        dataType: 'json',
        success: function(data) {
            users_data = data;
            console.log(users_data);

            for (var i in users_data) {
              var table = document.getElementById("users");
              var tr = document.createElement("tr");
              var username = document.createElement("td");
              
              username.appendChild(document.createTextNode(users_data[i].username));
              tr.appendChild(username);

              table.appendChild(tr);
            }
        }
    });
}