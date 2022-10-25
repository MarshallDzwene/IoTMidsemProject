<?PHP
	$servername= "localhost";	
	$username="root";
	$password="";
	$dbname="lab3waterlevel";
$con = mysqli_connect($servername,$username,$password,$dbname);

 	$TankID=$_GET['TankID'];
	$WaterLevel=$_GET['WaterLevel'];
	
$sql = "INSERT INTO main (TankID, WaterLevel) VALUES ('{$TankID}', '{$WaterLevel}')";
if (mysqli_query($con, $sql)) 
	echo "New record created successfully";


?>