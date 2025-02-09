<?php
	session_start();
	require_once "./functions/database_functions.php";
	$conn = db_connect();
	$query = "SELECT * FROM publisher ORDER BY publisherid";
	$result = mysqli_query($conn, $query);
	if(!$result){
		echo "Can't retrieve data " . mysqli_error($conn);
		exit;
	}
	if(mysqli_num_rows($result) == 0){
		echo "Empty publisher ! Something went wrong! check again.";
		exit;
	}
	$title = "List Of Publishers";
	require "./template/header.php";
?>
	<p class="lead">List of Publisher</p>
	<ul>
	<?php // prints the list of publisher's with the link of books per publisher
		while($row = mysqli_fetch_assoc($result)){
			$count = 0; 
			$query = "SELECT publisherid FROM books";
			$result2 = mysqli_query($conn, $query);
			if(!$result2){
				echo "Can't retrieve data " . mysqli_error($conn);
				exit;
			}
			while ($pubInBook = mysqli_fetch_assoc($result2)){
				if($pubInBook['publisherid'] == $row['publisherid']){
					$count++; // counter to show no. of books per publisher
				}
			}
		?>
			<li>
				<span class="badge"><?php echo $count; ?></span> <!-- print the books count and the publisher name -->
				<a href="bookPerPub.php?pubid=<?php echo $row['publisherid']; ?>"><?php echo $row['publisher_name']; ?></a>
			</li><br>
		<?php 
		} ?>
		<br>
			<!-- <a href="books.php">List full of books</a> -->
		
	</ul>
<?php
	mysqli_close($conn);
	require "./template/footer.php";
?>