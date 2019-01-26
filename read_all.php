<?php

header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json; charset=UTF-8");


//Creating Array for JSON response
$response = array();

// Include data base connect class
$filepath = realpath (dirname(__FILE__));
require_once($filepath."/dbconfig.php");

 // Connecting to database
$db = mysqli_connect(DB_SERVER, DB_USER, DB_PASSWORD, DB_DATABASE);

 // Fire SQL query to get all data from log
$result = mysqli_query($db, "SELECT *FROM log") or die(mysqli_error($db));

// Check for succesfull execution of query and no results found
if (mysqli_num_rows($result) > 0) {

	// Storing the returned array in response
    $response["log"] = array();

	// While loop to store all the returned response in variable
    while ($row = mysqli_fetch_array($result)) {
        // temperoary user array
        $log = array();
        $log["id"] = $row["id"];
        $log["timestamp"] = $row["timestamp"];
        $log["tempin"] = $row["tempin"];
		$log["tempout"] = $row["tempout"];
		$log["hum"] = $row["hum"];

		// Push all the items
        array_push($response["log"], $log);
    }
    // On success
    $response["success"] = 1;

    // Show JSON response
    echo json_encode($response);
}
else
{
    // If no data is found
	$response["success"] = 0;
    $response["message"] = "No data on log found";

    // Show JSON response
    echo json_encode($response);
}
?>
