<?php
	session_start();
	$title = "List of Books";
	require_once "./functions/admin.php";
	require_once "./template/header.php";
	require_once "./functions/database_functions.php";
	$conn = db_connect();
	$result = getAll($conn);
?> 
<!-- after a successful login admin enters in this page -->
	<br><br>
	<p class="lead" style="display: flex;  flex-direction: row;  justify-content: space-between">
		<a href="admin_show_orders.php">Show Orders</a>
		<a href="admin_add.php">Add a new book</a>
	</p>
	<a href="admin_signout.php" class="btn btn-primary">Sign out!</a>
	<table class="table" style="margin-top: 20px">
		<tr>
			<th>ISBN</th>
			<th>Title</th>
			<th>Author</th>
			<th>Image</th>
			<th>Description</th>
			<th>Price</th>
			<th>Publisher</th>
			<th>&nbsp;</th>
			<th>&nbsp;</th>
		</tr>
		<?php 
		while($row = mysqli_fetch_assoc($result)){ ?>
			<tr>
				<td><?php echo $row['book_isbn']; ?></td>
				<td><?php echo $row['book_title']; ?></td>
				<td><?php echo $row['book_author']; ?></td>
				<td><?php echo $row['book_image']; ?></td>
				<td><?php echo $row['book_descr']; ?></td>
				<td><?php echo $row['book_price']; ?></td>
				<td><?php echo getPubName($conn, $row['publisherid']); ?></td>
				<td><a href="admin_edit.php?bookisbn=<?php echo $row['book_isbn']; ?>">Edit</a></td>
				<td><a href="admin_delete.php?bookisbn=<?php echo $row['book_isbn']; ?>">Delete</a></td>
			</tr>
		<?php 
		} ?>
	</table>
	
	

<?php
	if(isset($conn)) {mysqli_close($conn);}
	// require_once "./template/footer.php";
?>