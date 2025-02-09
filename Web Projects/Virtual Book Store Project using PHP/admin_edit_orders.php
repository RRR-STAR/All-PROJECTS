<?php
	session_start();
	require_once "./functions/admin.php";
	$title = "Edit Order";
	require_once "./template/header.php";
	require_once "./functions/database_functions.php";
	$conn = db_connect();

	if (isset($_GET['orderid'])){
		$orderID = $_GET['orderid'];
	} 
  else {
		echo "Empty query!";
		exit;
	}
	if (! isset($orderID)){
		echo "Empty order id! check again!";
		exit;
	}
  
	// get book data
	$query = "SELECT * FROM orders WHERE orderid = '$orderID'";
	$result = mysqli_query($conn, $query);
	if (! $result){
		echo "Can't retrieve data " . mysqli_error($conn);
		exit;
	}
	$row = mysqli_fetch_assoc($result);
?>
	<form method="post" action="edit_order.php?orderid=<?php echo $row['orderid'];?>" enctype="multipart/form-data">
		<table class="table">
			<tr>
				<th>Order ID</th>
				<td><p><?php echo $row['orderid'];?></p></td>
			</tr>
      <tr>
				<th>Order Date</th>
				<td><p><?php echo $row['date'];?></p></td>
			</tr>
      <tr>
        <th>Order Item</th>
        <td><p><?php echo getOrderItem($conn, $row['orderid']); ?></p></td>
      </tr>
			<tr>
				<th>Customer Name</th>
				<td><input type="text" name="c_name" value="<?php echo $row['ship_name'];?>" required></td>
			</tr>
			<tr>
				<th>Address</th>
				<td><textarea name="c_address" cols="30" rows="3"><?php echo $row['ship_address'];?></textarea></td>
			</tr>
			<tr>
				<th>City</th>
				<td><input type="text" name="c_city" value="<?php echo $row['ship_city'];?>" required></td>
			</tr>
			<tr>
				<th>Country</th>
				<td><input type="text" name="c_country" value="<?php echo $row['ship_country'];?>" required></td>
			</tr>
			<tr>
				<th>Zip Code</th>
				<td><input type="text" name="c_zip" value="<?php echo $row['ship_zip_code'];?>" required></td>
			</tr>
			<tr>
				<th>Total Amount</th>
				<td><input type="text" name="c_total" value="<?php echo $row['amount'];?>" required></td>
			</tr>
		</table>
    
		<input type="submit" name="save_change" value="Change" class="btn btn-primary">
		<input type="reset" value="cancel" class="btn btn-default">
	</form>
	<br>
	<a href="admin_show_orders.php" class="btn btn-success">Confirm</a>

<?php
	if(isset($conn)) {mysqli_close($conn);}
	// require "./template/footer.php"
?>