<!DOCTYPE html>
<html>
<body>

<?php
exec("./a3 choose");
?>

<body background="bg.jpg">

<h2>log in </h2>
<hr>
<form method="post" id="form" >
User Name:<br><input type="text" name="username"><br><br>
<form form="form" ><input type="submit" value="login" /></form>


<?php

if(isset($_POST["username"])){
	$username=$_POST["username"];
	header("Location: choose.php?username=$username");
}
?>

</body>
</html>
