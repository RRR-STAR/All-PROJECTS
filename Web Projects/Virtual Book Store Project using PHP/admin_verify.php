<?php
	session_start();
	if(!isset($_POST['submit'])){
		echo "Something wrong! Check again!";
		exit;
	}
	require_once "./functions/database_functions.php";
	$conn = db_connect();
	
	$name = trim($_POST['name']); // trim the wihite spaces 
	$pass = trim($_POST['pass']); // from the begning
	if($name == "" || $pass == ""){
		echo "Name or Pass is empty!";
		exit;
	}
	$name = mysqli_real_escape_string($conn, $name);
	$pass = mysqli_real_escape_string($conn, $pass);
	$pass = sha1($pass); // convert the pass into hash string
	// get from db
	$query = "SELECT name, pass from admin";
	$result = mysqli_query($conn, $query);
	if(!$result){
		echo "Empty data " . mysqli_error($conn);
		exit;
	}
	$row = mysqli_fetch_assoc($result);
	// verify the admin details provided
	if($name != $row['name'] && $pass != $row['pass']){
		echo "Name or pass is wrong. Check again!";
		$_SESSION['admin'] = false;
		exit;
	}
	if(isset($conn)){ mysqli_close($conn); }
	$_SESSION['admin'] = true;
	header("Location: admin_book.php");
?>

