<?php
	// Class definition for Guests
	class Guest {
		// Properties of a Guest - None
		// Accessor functions - none because there are no properties to access

		// Constructor for Guest
		public function __construct() {
		}

		// Function to generate the page contents
		public function generatePage() {
			// Show list of available blogs
			echo('
				<br>		
				<form class="center-block">
					<fieldset class="fieldset-auto-width">
						<legend>Available Logbooks</legend>
						<div>
							<table align="center" id="users">
								<thead>
								</thead>
							</table>
						</div>
					</fieldset>
				</form>
				');

			// Let guests select a blog to view
			echo('
				<br>
				<form class="center-block" id="submit" method="post">
					<fieldset class="fieldset-auto-width">
						<legend>Retrieve a Logbooks</legend>				
						<div class="form-group">
							<input type="username" class="form-control" name="username" id="username" placeholder="Enter a Username">
						</div>
						<div class="pull-right">
							<button type="submit" class="btn btn-default center-block">Submit</button>
						</div>
					</fieldset>
				</form>
				
				');

			// Predefine the table for the blog entires
			echo('<h2 id="profile_header"></h2>');
			echo('<p id="profile_id"></p>');
			echo('<p id="profile_username"></p>');
			echo('<p id="profile_email"></p>');
			echo('<br><h2 id="blog_header"></h2>');
			echo('<div>');
			echo('<table align="center" id="blogs">');
			echo('<thead></thead>');
			echo('</table></div>');

			echo('<script src="js/blogs.js"></script>');
		}


		// Function to print out a users own blog
		public function getBlog($id, $username) {
			$data = array();

			// Query database for blog entries
			include "connect_db.php";		// Connect to the remote database			
			$query = "SELECT * FROM posts WHERE id = '" . $id . "'";
			$query_result = $database->query($query);

			// Check if there are any blog posts
			if($query_result->rowCount() >= 0) {
				foreach($query_result as $row) {
					$new_row = array('title'=>$row['title'], 'content'=>$row['content'], 'timestamp'=>$row['timestamp']);
					array_push($data, $new_row);
				}

				// encode the data as a json string and push it up to javascript land
				$json_data = json_encode($data);
				echo $json_data;
			}
			else {
				//echo '{"Error": "No Blog Entries"}';	
			}	
		}

		// Function to get a user ID from a username
		public function getID($username) {
			include "connect_db.php";		// Connect to the remote database

			//check if the username entered is in the database.
			$query = "SELECT * FROM users WHERE username = '".$username."'";
			$query_result = $database->query($query);

			// Check if query returned anything
			if($query_result->rowCount() > 0) {
				foreach($query_result as $row_query) {
					return $row_query['id'];
		        }
			}
			else {
				throw new Exception('Error: MySQL query returned no user ID.');
			}
		}

		// Function to get a users email from a username
		public function getEmail($username) {
			include "connect_db.php";		// Connect to the remote database

			//check if the username entered is in the database.
			$query = "SELECT * FROM users WHERE username = '".$username."'";
			$query_result = $database->query($query);

			// Check if query returned anything
			if($query_result->rowCount() > 0) {
				foreach($query_result as $row_query) {
					return $row_query['email'];
		        }
			}
			else {
				throw new Exception('Error: MySQL query returned no user Email.');
				return 0;
			}
		}


	}// End of Guest Class

	// Class definition for registered users
	class User extends Guest {
		// Properties of a User
		private $id = 0;
		private $username;
		private $password;
		private $email;

		// Constructor accepts username, password and id in that order
		public function __construct() {
			//parent::__construct(); only add if we need to allow registered users to view other peoples blogs
			$argv = func_get_args();
			$this->username = $argv[0];
			$this->password = $argv[1];

			if(func_num_args() > 2) {
				$this->email = $argv[2];
			}
		}		

		// Accessor functions for the User class
		public function getUsername(){
			return $this->username;
		}

		// Function to get a users password from a username
		public function getPassword($username) {
			include "connect_db.php";		// Connect to the remote database

			//check if the username entered is in the database.
			$query = "SELECT * FROM users WHERE username = '".$username."'";
			$query_result = $database->query($query);

			// Check if query returned anything
			if($query_result->rowCount() > 0) {
				foreach($query_result as $row_query) {
					return $row_query['password'];
		        }
			}
			else {
				throw new Exception('Error: MySQL query returned no user password.');
				return 0;
			}
		}

		public function setEmail($email){
			include "connect_db.php";		// Connect to the remote database			

			$query = "UPDATE users SET email = '" . $email . "' WHERE username = '" . $this->username . "'";
			$query_result = $database->query($query);

			if($query_result->rowCount() > 0) {
				throw new Exception('Email update failed.');
			}
		}

		public function setPassword($password){
			include "connect_db.php";		// Connect to the remote database			

			$query = "UPDATE users SET password = '" . $password . "' WHERE username = '" . $this->username . "'";
			$query_result = $database->query($query);

			if($query_result->rowCount() > 0) {
				throw new Exception('Password update failed.');
			}
		}

		// Login, logout, request access functions
		public function requestAccess() {
			include "connect_db.php";		// Connect to the remote database			

			// Check that this username doesn't already exist.
			$query = "SELECT * FROM users WHERE username = '".$this->username."'";
			$query_result = $database->query($query);

			if($query_result->rowCount() > 0) {
				throw new Exception('Request access failed.  Username already taken.');
			}

			// Prep a query for inputting into the database
			$query = 'INSERT INTO users (username, password, email) VALUES(:username, :password, :email)';
			$statement = $database->prepare($query);
			
			$params = [
				'username' => $this->username,
				'password' => $this->password,
				'email' => $this->email,
			];

			// Execute the query
			$result = $statement->execute($params);
			if($result == FALSE) {
				throw new Exception('Request access failure: MySQL Insert Failed');
			}
		}	// End of requestaccess function

		public function login() {
			session_start();
			include "connect_db.php";		// Connect to the remote database

			//check if the username entered is in the database.
			$login_query = "SELECT * FROM users WHERE username = '".$this->username."'";
			$query_result = $database->query($login_query);

			//conditions
			if($query_result->rowCount() > 0) {
				foreach($query_result as $row_query) {
					// check if password are equal
			        if($row_query['password']==$this->password)
			        {
						// remember username & password to session if "Remember me" was set
			            $_SESSION["username"] = $this->username;
						$_SESSION["password"] = $this->password; 

			            header("Location: ../blogs.html"); // Redirect browser
			            exit();
			        }
			        else
					{
						throw new Exception('Login error: Invalid credentials');
					}
				}
			}
			else {
				throw new Exception('Login error: Username does not exist.');
			}
			
			echo "Invalid login info.";
			header("Location: ../login.html"); // Redirect browser
			exit();			
		}	// End of login function

		public function logout() {
			session_start();
			session_destroy();

			echo "<p>You have been successfully logged out!</p>";
			sleep(1);
			header("Location: ../login.html"); // Redirect browser
			exit();
		}	// End of logout function	

		// Function to generate the page for the user
		public function generatePage() {
		// Let users add new blog entries
			//<fieldset class="fieldset-auto-width">
		echo('
			<br>
			<div class="row">
				<div class="col-sm-6">
					
					
						<fieldset class="fieldset-60-width">
							
							<legend>Update Profile</legend>

							<form class="form-auto" action="php/update_email.php" id="submit_email" method="post">
								<div class="form-group">
									<label class="pull-left" for="email">Email:</label>
									<input type="email" class="form-control" name="email" id="email">
								</div>
								<div class="pull-right">
									<button type="submit_email" class="btn btn-default">Update</button>
								</div>
							</form>
							
							<form class="form-auto" action="php/update_password.php" id="submit_password" method="post">
								<div class="form-group">
									<label class="pull-left" for="password">Password:</label>
									<input type="password" class="form-control" name="password" id="password">
									<div id="password_alert" class="warning">
									</div>
								</div>
								<div class="pull-right">
									<button type="submit_password" class="btn btn-default">Update</button>
								</div>
							</form>

						</fieldset>
					
				</div>

				<div class="col-sm-6">
					<h2 id="profile_header"></h2>
					<p id="profile_id"></p>
					<p id="profile_username"></p>
					<p id="profile_password"></p>
					<p id="profile_email"></p>
				</div>
			</div>

			<div class="row">
				<div class="col-sm-6">
					<form class="center-block" action="php/new_blog.php" id="submit" method="post">
						<fieldset class="fieldset-auto-width">
							<legend>New Logbook Entry</legend>				
							<div class="form-group">
								<input type="title" class="form-control" name="title" id="title" placeholder="Enter a Title">
							</div>
							<div class="form-group">

							<div class="form-group">
								<label for="info">Content:</label>
								<textarea class="form-control" rows="5" id="content" name="content" placeholder="Details..."></textarea>
							</div>

							<div class="pull-right">
								<button type="submit" class="btn btn-default center-block">Submit</button>
							</div>
						</fieldset>
					</form>					
				</div>

				<div class="col-sm-6">
					<h2 id="blog_header"></h2>
					<div>
						<table align="center" id="blogs">
						<thead></thead>
						</table></div>	
					</div>
				</div>		
			</div>		
			');

		echo('<script src="js/blogs.js"></script>');
		}

		// Function to enter a new blog post into the database
		public function newPost($title, $content) {
			include "connect_db.php";		// Connect to the remote database			

			// Prep a query for inputting into the database
			$query = 'INSERT INTO posts (id, title, content) VALUES(:id, :title, :content)';
			$statement = $database->prepare($query);

			$params = [
				'id' => $this->getID($this->username),
				'title' => $title,
				'content' => $content
			];

			// Execute the query
			$result = $statement->execute($params);
			if($result == FALSE) {
				throw new Exception('Request access failure: MySQL Insert Failed');
			}
		}
	}	// End of user class
?>