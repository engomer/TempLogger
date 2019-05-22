<?php

header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json; charset=UTF-8");

//Creating Array for JSON response
$response = array();

// Check if we got the field from the user
if (isset($_GET['tempin']) && isset($_GET['tempout']) && isset($_GET['hum'])) {

    $tempin = $_GET['tempin'];
	$tempout = $_GET['tempout'];
    $hum = $_GET['hum'];


    // Include data base connect class
    $filepath = realpath (dirname(__FILE__));
	require_once($filepath."/dbconfig.php");


    // Connecting to database
    
	$con = mysqli_connect(DB_SERVER, DB_USER, DB_PASSWORD, DB_DATABASE);

    // Fire SQL query to insert data in weather
    $result = mysqli_query($con, "INSERT INTO log(tempin,tempout,hum) VALUES('$tempin' ,'$tempout','$hum')");

    // Check for succesfull execution of query
    if ($result) {
        // successfully inserted
        $response["success"] = 1;
        $response["message"] = "Log successfully added to table.";

        // Show JSON response
        echo json_encode($response);
    } else {
        // Failed to insert data in database
        $response["success"] = 0;
        $response["message"] = "Something has been wrong";

        // Show JSON response
        echo json_encode($response);
    }
} else {
    // If required parameter is missing
    $response["success"] = 0;
    $response["message"] = "Parameter(s) are missing. Please check the request";

    // Show JSON response
    echo json_encode($response);

}
?>
