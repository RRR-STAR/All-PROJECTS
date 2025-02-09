<?php
	session_start();
	$title = "List of Orders";
	require_once "./functions/admin.php";
	require_once "./template/header.php";
	require_once "./functions/database_functions.php";
	$conn = db_connect();
	$result = getAllOrders($conn);
?> 
<!-- after a successful login admin enters in this page -->

<a href="admin_signout.php" class="btn btn-primary">Sign out!</a>
<br><br>
<table class="table" style="margin-top: 20px">
	<tr>
		<th>Customer Name</th>
		<th>Country</th>
		<th>Zip Code</th>
		<th>Order Date</th>
		<th>Ordered Book Name</th>
		<th>Total</th>
		<th>&nbsp;</th>
		<th>&nbsp;</th>
	</tr>
	<?php 
	while ($row = mysqli_fetch_assoc($result)){ ?>
		<tr>
			<td><?php echo $row['ship_name']; ?></td>
			<td><?php echo $row['ship_country']; ?></td>
			<td><?php echo $row['ship_zip_code']; ?></td>
			<td><?php echo $row['date']; ?></td>
			<td><?php echo getOrderItem($conn, $row['orderid'], false); ?></td>
			<td><?php echo $row['amount']; ?></td>
      <!-- edit & delete options -->
			<td><a href="admin_edit_orders.php?orderid=<?php echo $row['orderid']; ?>">Edit</a></td>
			<td><a href="admin_delete_orders.php?orderid=<?php echo $row['orderid']; ?>">Delete</a></td>
		</tr>
	<?php 
	} ?>
</table>

<?php
	if(isset($conn)) {mysqli_close($conn);}
	// require_once "./template/footer.php";
?>