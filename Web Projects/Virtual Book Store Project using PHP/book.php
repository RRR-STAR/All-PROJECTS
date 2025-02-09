<?php
  session_start();
  $book_isbn = $_GET['bookisbn']; // data fetch from url
  require_once "./functions/database_functions.php";
  $conn = db_connect(); // connecto database
  
  $query = "SELECT * FROM books WHERE book_isbn = '$book_isbn'"; // selecting book by ISBN
  $result = mysqli_query($conn, $query);
  
  if (! $result){ // if connection fails
    echo "Can't retrieve data " . mysqli_error($conn);
    exit;
  }
  $row = mysqli_fetch_assoc($result); // convert into associative array
  if (! $row){
    echo "Empty book";
    exit;
  }
  $title = $row['book_title']; // set the page title
  require "./template/header.php";
?>

<!-- fetch the books titile from the 'books.php' file -->
<p class="lead" style="margin: 25px 0"><a href="books.php"> Books</a> > <?php echo $row['book_title']; ?></p>
<div class="row">
  <div class="col-md-3 text-center">  <!-- change the with-link image to without-link image -->
    <img class="img-responsive img-thumbnail" src="./bootstrap/img/<?php echo $row['book_image']; ?>">
  </div>
  <div class="col-md-6">
    <h4> Book Description </h4>
    <p><?php echo $row['book_descr']; // prints the book description ?></p>
    <br>
    <h4> Book Details </h4>
    <table class="table">
      <?php 
      foreach ($row as $key => $value){
        
        if ($key == "book_descr" || $key == "book_image" || $key == "publisherid" || $key == "book_title"){
          continue; // as this details already printed 
        }
        switch ($key){ // rest of the book details printed in a table format
          case "book_isbn":   $key = "ISBN";    break;
          case "book_title":  $key = "Title";   break;
          case "book_author": $key = "Author";  break;
          case "book_price":  $key = "Price";   break;
        }
      ?>
        <tr>
          <td><?php echo $key; ?></td>
          <td><?php echo $value; ?></td>
        </tr>
      <?php 
      } 
      if (isset($conn)) {mysqli_close($conn); }?>
    </table>
    <br>
    <form method="post" action="cart.php">
      <input type="hidden" name="bookisbn" value="<?php echo $book_isbn;?>">
      <input type="submit" value="Purchase / Add to cart" name="cart" class="btn btn-primary">
    </form>
  </div>
</div>

<?php
  require "./template/footer.php";
?>