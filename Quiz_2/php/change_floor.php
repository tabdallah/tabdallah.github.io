<?php
	// Connect to database and overwrite value for floor number in carNode table
	$floor = $_POST['floor'];

	include "connect_db.php";		// Connect to the remote database

	// Prep a query for inputting into the database
	$query = 'UPDATE carNode SET floorNumber=' . $floor;
	$statement = $database->prepare($query);

	// Execute the query
	$result = $statement->execute();

	// Redirect back to members page
	header("Location: ../members.html"); 	// Redirect to members page
	exit();
?>
