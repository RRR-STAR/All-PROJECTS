<?php
  session_start();
  $count = 0;
  $title = "Index"; // set the page title
  
  // header files
  require_once "./template/header.php";
  require_once "./functions/database_functions.php";
  
  $conn = db_connect(); // connect to database
  $row = select4LatestBooks($conn); // select row of books fetch by the database
?>

<!-- Example row of columns -->
<p class="lead text-center text-muted"> Latest books </p><br>
<div class="row">
  <?php 
  foreach ($row as $book) { // loop to iterate over books & select based on ISBN  ?>
    
    <div class="col-md-3"> <!-- embdeed book images with book links -->
      <a href="book.php?bookisbn=<?php echo $book['book_isbn']; ?>"><!--book: dictionary-->
      <img class="img-responsive img-thumbnail" src="./bootstrap/img/<?php echo $book['book_image']; ?>">
      </a>
    </div>
    
  <?php 
  } ?>
</div>

<?php
  if (isset($conn)){ mysqli_close($conn); }
  require_once "./template/footer.php";
?>


