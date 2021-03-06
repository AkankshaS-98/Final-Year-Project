<!DOCTYPE html>
<html lang="en">
	<head>
	  <title>Body Parameters Monitoring</title>
	  <meta charset="utf-8">
	  <meta http-equiv="refresh" content="5"> 
	  <meta name="viewport" content="width=device-width, initial-scale=1">
	  <link rel="stylesheet" href="bootstrap.min.css">
	  <script src="jquery.min.js"></script>
	  <script src="bootstrap.min.js"></script>
	</head>

	<body>
		<style>
			body
			{
				background-color:#001827;	
			}
			#active
			{
				background:#4db8ff;
				padding:2px;
				color:#ffffff;
				text-decoration:none;
			}
			#deactive
			{
				background:#ffffff;
				padding:2px;	
				color:#ffffff;
				text-decoration:none;
			}
			.table
			{
				text-align: center;
				width: 100% !important;
			}
			.table th
			{
				text-align: center;
			}
		</style>

		<div class="container">
			<?php
				error_reporting(0);
				mysql_connect("localhost", "root", "") or die(mysql_error());
				mysql_select_db("body_parameter") or die(mysql_error());

				echo"<H2 class='text-center' style='color:#fff;'>Body Parameters Monitoring</H2></br>";
				echo "<table class='table col-sm-12' >
				<tr style='color:#fff;'><th>ID</th><th>PulseRate (bpm)</th><th>SystolicBP (mmHg)</th><th>DiastolicBP (mmHg)</th><th>O2Saturation (%)</th><th>TotalHemoglobin (g/dl)</th><th>Temperature (F)</th><th>Date Time</th></tr>";

				$result = mysql_query("SELECT * FROM info  ORDER BY `id` DESC") 
				or die(mysql_error());  

				while($row = mysql_fetch_array( $result ))
				{
					echo "<tr style='color:#fff;'><td>$row[id]</td><td>$row[PulseRate]</td><td>$row[SystolicBP]</td><td>$row[DiastolicBP]</td><td>$row[O2Saturation]</td><td>$row[TotalHemoglobin]</td><td>$row[Temperature]</td><td>$row[DateTime]</td></tr>";
				}
				echo "</table>";
			?>
		</div>
	</body>
</html>