<?php
  session_start();
  $count = 0;
  require_once "./functions/database_functions.php";
  $conn = db_connect(); // connecto database
  
  $query = "SELECT book_isbn,book_image FROM books"; // select all books records from the database
  $result = mysqli_query($conn, $query);
  if(! $result){
    echo "Can't retrieve data " . mysqli_error($conn);
    exit;
  }
  $title = "Full Catalogs of Books"; // set the title of the page
  require_once "./template/header.php"; // for menu bar
?>
  <p class="lead text-center text-muted"> Full Catalogs of Books </p>
    <?php 
    for($i = 0; $i < mysqli_num_rows($result); $i++){ ?> <!-- iterate based on number of rows --> 
      <div class="row">
        <?php 
        while($query_row = mysqli_fetch_assoc($result)){ ?> <!-- find the right books based on ISBN and print it -->
          <div class="col-md-3">
            <a href="book.php?bookisbn=<?php echo $query_row['book_isbn']; ?>">
              <img class="img-responsive img-thumbnail" src="./bootstrap/img/<?php echo $query_row['book_image']; ?>">
            </a>
          </div><br>
          <?php
          $count++;
          if($count >= 4){ // only 4 books in a row
              $count = 0;
              break;
            }
        } ?> 
      </div>
    <?php
    }
  if(isset($conn)) { mysqli_close($conn); }
  require_once "./template/footer.php";
?>