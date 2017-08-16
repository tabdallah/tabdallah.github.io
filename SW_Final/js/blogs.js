// https://stackoverflow.com/questions/5835126/javascript-infinite-loop
var users_data = {};
var users = document.getElementById('users');
var form = document.getElementById('submit');

window.onload = function start(){
  // Check if the users table exits
  if (!users) {
    console.log('This is a user rendering');

    // Make an Ajax call to get the blog post info
    console.log('Running get_blog.php');

    $.ajax({
            url: '../php/get_blog.php',
            dataType: 'json',
            success: function(data) {
                blog_data = data;
                console.log(blog_data);
                showBlog();
            },
            error: function() {
              console.log('get_blog.php failed.');
            }
        });
    return false;


  }
  else {
    console.log('This is a guest rendering.');

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

    form.onsubmit = function() {
      // Make sure a valid username was entered
      if(username.value.length < 7) {
        alert('Username must be at least 7 characters long');
        return false;
      }

      // Make an Ajax call to get the blog post info
      console.log('Running get_blog.php');

      $.ajax({
              url: '../php/get_blog.php',
              type:'POST',
              data:
              {
                username: username.value
              },
              dataType: 'json',
              success: function(data) {
                  blog_data = data;
                  console.log(blog_data);
                  showBlog();
              
              },
              error: function() {
                console.log('get_blog.php failed.');
              }
          });
      return false;
    }
  }
}

// Function that actually pumps the blog data into the table
function showBlog() {
  // Add the blog data to the page
  var header = document.getElementById('blog_header');
  
  if (!users) {
    header.innerHTML = "Your Blog Entires";
  }
  else {
    header.innerHTML = username.value + "'s Blog";
  }

  // Clear existing table
  var table = document.getElementById("blogs");
  while(table.hasChildNodes()) {
    table.removeChild(table.firstChild);
  }


  if(Object.keys(blog_data).length == 1) {
    // Insert no blog posts into table
    var tr = document.createElement("tr");
    var data = document.createElement("td");
    data.appendChild(document.createTextNode('No Blog Posts'));
    tr.appendChild(data);
    table.appendChild(tr);
  }
  else {
    for (var i in blog_data) {      
      // Add title to page
      var tr = document.createElement("tr");
      var data = document.createElement("td");
      data.style.fontWeight = "bold";
      data.style.fontSize = "25px";
      data.appendChild(document.createTextNode(blog_data[i].title));
      tr.appendChild(data);
      table.appendChild(tr);

      // Add timestamp to page
      var tr = document.createElement("tr");
      var data = document.createElement("td");
      data.style.fontStyle = "italic";
      data.appendChild(document.createTextNode(blog_data[i].timestamp));
      tr.appendChild(data);
      table.appendChild(tr);

      // Add post content to page
      var tr = document.createElement("tr");
      var data = document.createElement("td");
      data.appendChild(document.createTextNode(blog_data[i].content));
      tr.appendChild(data);
      table.appendChild(tr);
    }
  }
}