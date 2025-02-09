<?php
	$orderID = $_GET['orderid'];

	require_once "./functions/database_functions.php";
	$conn = db_connect();

	$query = "DELETE FROM orders WHERE orderid = '$orderID'";
	$result = mysqli_query($conn, $query);
	if(!$result){
		echo "Delete data unsuccessfully " . mysqli_error($conn);
		exit;
	}
	header("Location: admin_show_orders.php");
?>