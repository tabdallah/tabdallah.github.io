<?php
	include "users.php";

	session_start();

	$guest = 1;	// By default this is a guest

	if (isset($_SESSION["username"])==0)
	{
		$username = $_POST["username"];	// Get username from input box
		$user = new Guest();
	}
	else
	{
		$username = $_SESSION["username"];
		$user = new User();
		$guest = 0;				// Clear guest flag
	}
	
	// Try to get the specified users profile contents
	try {
		$id = $user->getID($username);
		$email = $user->getEmail($username);

		if($guest) {
			$data = array('username'=>$username, 'id'=>$id, 'email'=>$email);
		}
		else {
			$password = $user->getPassword($username);
			$data = array('username'=>$username, 'id'=>$id, 'email'=>$email, 'password'=>$password);
		}

		$json_data = json_encode($data);
		echo $json_data;
	}
	catch(Exception $e) {
		echo $e->getMessage();
	}
?>