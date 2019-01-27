<?php 

$filepath = realpath (dirname(__FILE__));
require_once($filepath."/dbconfig.php");

$connect = mysqli_connect(DB_SERVER, DB_USER, DB_PASSWORD, DB_DATABASE);
$query = "SELECT * FROM log";
$result = mysqli_query($connect, $query);
$chart_data = '';
while($row = mysqli_fetch_array($result))
{
 $chart_data .= "{ timestamp:'".$row["timestamp"]."', tempin:".$row["tempin"].", tempout:".$row["tempout"].", hum:".$row["hum"]."}, ";
}
$chart_data = substr($chart_data, 0, -2);
?>


<DOCTYPE! html>
<html>
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
		<title> Temperature and Humidity Sensor | ogencay.com </title>
		<link rel="stylesheet" href="//cdnjs.cloudflare.com/ajax/libs/morris.js/0.5.1/morris.css">
  		<script src="//ajax.googleapis.com/ajax/libs/jquery/1.9.0/jquery.min.js"></script>
  		<script src="//cdnjs.cloudflare.com/ajax/libs/raphael/2.1.0/raphael-min.js"></script>
  		<script src="//cdnjs.cloudflare.com/ajax/libs/morris.js/0.5.1/morris.min.js"></script>
		<style>
			
			body { background-color: #FFFFFF;}
			table{ border-collapse:collapse;}
			td{ text-align: center; }
			button{border-radius: 8px; padding: 12px 28px; font-size: 16px;}
			.headers{ color:#000000; }
			.buttons{margin-right:15px; margin-left:15px; }
			.button:hover { background-color: #4CAF50; /* Green */  color: white;}
			img{width:80px; height:80px; }
			th{text-align:center;}
			</style>

	</head>

	<body >
		<p>
			<h1 class="headers" align = center>Temperature and Humidity Sensor</h1>
			<h1 class="headers" align = center>Pharmacy of Gençay</h2>
			</br>
		</p>
		<table align="center" style="width:70%">
			<tr >
				<?php include 'now.php'; ?>
			</tr>
			<tr align="center" style="text-align:center;">
				<th align="center" style="text-align:center;"><h1>Graph for all data</h1></th>
			</tr>
			<tr>
				<td class="linegraph"> <div id="chart"></div> </td>
			</tr>
		</table>
		<table align="center">	
			<tr "width:50px;">
				<td class="buttons" style="padding:70px;"><a href="http://ogencay.com/wp-content/api/daily_index.php"><button>Display Daily Logs</button></a></td>
				<td class="buttons" style="padding:70px;" ><a href="http://ogencay.com/wp-content/api/all_index.php"><button>Display All Logs</button></a></td>
			</tr>
			
		</table>
		</table>
	</body>
    
    <script>
		Morris.Line({
		    element : 'chart',
		    data:[<?php echo $chart_data; ?>],
		    xkey:'timestamp',
		    ykeys:['tempin', 'tempout', 'hum'],
		    labels:['Sicaklik', 'Buzdolabi', 'Nem'],
			lineColors:['#ffff00' , '#3ADFFF' , '#B000E8' ],
		    hideHover:'auto',
		    stacked:true
		});
	</script>
</html>
