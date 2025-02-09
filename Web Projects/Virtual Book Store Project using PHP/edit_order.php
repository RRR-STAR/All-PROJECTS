<?php	
	// if save change happen
	if(!isset($_POST['save_change'])){
		echo "Something went wrong!";
		exit;
	}
  
  $orderID = $_GET['orderid'];
	$newName = trim($_POST['c_name']);
	$newAddress = trim($_POST['c_address']);
	$newCity = trim($_POST['c_city']);
	$newCountry = trim($_POST['c_country']);
	$newZipCode = floatval(trim($_POST['c_zip']));
	$newPrice = trim($_POST['c_total']);
  
	require_once("./functions/database_functions.php");
	$conn = db_connect();
  
	$query = "UPDATE orders SET  
	ship_name = '$newName', 
	ship_address = '$newAddress', 
	ship_city = '$newCity', 
	ship_country = '$newCountry',
	ship_zip_code = '$newZipCode',
	amount = '$newPrice'
  WHERE orderid = '$orderID'";
  
	$result = mysqli_query($conn, $query);
	if (! $result){
		echo "Can't update data " . mysqli_error($conn);
		exit;
	} 
	else {
		header("Location: admin_edit_orders.php?orderid=$orderID");
	}
?>