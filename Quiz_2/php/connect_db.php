<?php
	echo "<script type='text/javascript'> console.log('CONNECTING TO DATABASE') </script>";
	
	// Try to connect to database and catch errors
	try {
		$database = new PDO('mysql:host=localhost;dbname=quizElevator', 'root', 'password');	
	}
	catch (PDOException $e) {
		echo "Error: " . $e->getMessage() . "<br />";
		exit();
	}

	echo "<script type='text/javascript'> console.log('CONNECTED TO DATABASE') </script>";

?>