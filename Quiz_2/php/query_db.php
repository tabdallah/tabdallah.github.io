<?php
	include "connect_db.php";		// Connect to the remote database

	// Query for values with floor numbers
	$rows = $database->query("SELECT t1.nodeID, t1.info, t1.status, t2.floorNumber FROM elevatorNodes t1, carNode t2 WHERE t1.nodeID = t2.nodeID");
	if($rows != FALSE) {
		foreach($rows as $row) {
			$nodeID_1 = $row['nodeID'];
			$info_1 = $row['info'];
			$status_1 = $row['status'];
			$floor_1 = $row['floorNumber'];
		}	
	}

	// Query for other node values
	$rows = $database->query("SELECT nodeID, info, status FROM elevatorNodes WHERE nodeID=2");
	if($rows != FALSE) {
		foreach($rows as $row) {
			$nodeID_2 = $row['nodeID'];
			$info_2 = $row['info'];
			$status_2 = $row['status'];
			$floor_2 = $row['floorNumber'];
		}	
	}
	
	$rows = $database->query("SELECT nodeID, info, status FROM elevatorNodes WHERE nodeID=3");
	if($rows != FALSE) {
		foreach($rows as $row) {
			$nodeID_3 = $row['nodeID'];
			$info_3 = $row['info'];
			$status_3 = $row['status'];
			$floor_3 = $row['floorNumber'];
		}	
	}

	$rows = $database->query("SELECT nodeID, info, status FROM elevatorNodes WHERE nodeID=4");
	if($rows != FALSE) {
		foreach($rows as $row) {
			$nodeID_4 = $row['nodeID'];
			$info_4 = $row['info'];
			$status_4 = $row['status'];
			$floor_4 = $row['floorNumber'];
		}	
	}

	$rows = $database->query("SELECT nodeID, info, status FROM elevatorNodes WHERE nodeID=5");
	if($rows != FALSE) {
		foreach($rows as $row) {
			$nodeID_5 = $row['nodeID'];
			$info_5 = $row['info'];
			$status_5 = $row['status'];
			$floor_5 = $row['floorNumber'];
		}	
	}

	echo '
	<table id="database" align="center">
				<thead>
					<tr>
						<th>Node ID</th>
						<th>Node Info</th>
						<th>Node Status</th>
						<th>Floor Number</th>
					</tr>
				</thead>
				<tbody>
					<tr>
						<th id="nodeID_1">' . $nodeID_1 . '</th>
						<td id="info_1">' . $info_1 . '</td>
						<td id="status_1">' . $status_1 . '</td>
						<td id="floor_1">' . $floor_1 . '</td>
					</tr>
					<tr>
						<th id="nodeID_2">' . $nodeID_2 . '</th>
						<td id="info_2">' . $info_2 . '</td>
						<td id="status_2">' . $status_2 . '</td>
						<td id="floor_2"></td>
					</tr>
					<tr>
						<th id="nodeID_3">' . $nodeID_3 . '</th>
						<td id="info_3">' . $info_3 . '</td>
						<td id="status_3">' . $status_3 . '</td>
						<td id="floor_3"></td>
					</tr>
					<tr>
						<th id="nodeID_4">' . $nodeID_4 . '</th>
						<td id="info_4">' . $info_4 . '</td>
						<td id="status_4">' . $status_4 . '</td>
						<td id="floor_4"></td>
					</tr>
					<tr>
						<th id="nodeID_5">' . $nodeID_5 . '</th>
						<td id="info_5">' . $info_5 . '</td>
						<td id="status_5">' . $status_5 . '</td>
						<td id="floor_5"></td>
					</tr>
				</tbody>
			</table>
	';
?>