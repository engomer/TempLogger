<html>
    <head>
        <title>Günlük Değerler</title>
        <style>
            table {border-collapse: collapse; width: 20%;}
            th, td {text-align: left; padding: 8px;}
            tr:nth-child(even){background-color: #f2f2f2}
            th {background-color: #4CAF50; color: white;}
            table.table1 {text-align:center;}
            button{border-radius: 8px; padding: 12px 28px; font-size: 16px;}
        </style>
    </head>
    <body>
        <div align="center">    
            <h1> Gençay Eczanesi </h1>
            <h2> Günlük Değerler </h2>
        </div>
        <table class="table1" align="center">
        <thead>
            <tr>
                <td>Num</td>
                <td>Tarih</td>
                <td>Buzdolabı</td>
                <td>Oda</td>
                <td>Nem</td>
               
            </tr>
        </thead>
        <tbody>
            <?php
                    $filepath = realpath (dirname(__FILE__));
                    require_once($filepath."/dbconfig.php");
                    $connect = mysqli_connect(DB_SERVER, DB_USER, DB_PASSWORD, DB_DATABASE);
                    if (!$connect) {
                        die(mysql_error());
                    }
                    $results = mysqli_query($connect,"SELECT * FROM log WHERE timestamp BETWEEN DATE_SUB(CURDATE(), INTERVAL 1 DAY) AND CURDATE()");
                    while($row = mysqli_fetch_array($results)) {
                ?>
                <tr>
                    <td><?php echo $row['id']?></td>
                    <td><?php echo $row['timestamp']?></td>
                    <td><?php echo $row['tempin']?></td>
                    <td><?php echo $row['tempout']?></td>
                    <td><?php echo $row['hum']?></td>
                </tr>
                
            <?php
            }
            ?>
          
            </tbody>
            </table>
    </body>
</html>