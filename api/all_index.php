<html>
    <head>
        <title>Tüm Değerler</title>
        <style>
            table {
                border-collapse: collapse;
                width: 20%;
            }

            th, td {
                text-align: left;
                padding: 8px;
            }

            tr:nth-child(even){background-color: #f2f2f2}

            th {
                background-color: #4CAF50;
                color: white;
            }
            table.table1 {
                text-align:center;
                
            }
        </style>
    </head>
    <body>
        <div align="center">    
            <h1> Gençay Eczanesi </h1>
            <h2> Tüm Değerler </h2>
        </div>
        <table class="table1" align="center">
        <thead>
            <tr>
                <td>Tarih</td>
                <td>Buzdolabı</td>
                <td>Oda</td>
                <td>Nem</td>
               
            </tr>
        </thead>
        <tbody>
        <?php
            $filepath = realpath (dirname(__FILE__));
            require_once($filepath."/38df0b72-86cc-412f-805b-7a6c27554ad5/dbconfig.php");
            $connect = mysqli_connect(DB_SERVER, DB_USER, DB_PASSWORD, DB_DATABASE);
            if (!$connect) {
                die(mysql_error());
            }
            $results = mysqli_query($connect,"SELECT * FROM " .DB_TABLE. " ORDER BY id");
            while($row = mysqli_fetch_array($results)) {
                $end_date = date("Y-m-d H:i:s", strtotime("+" . 3 . " hours", strtotime($row["timestamp"])));
            ?>
                <tr>
                    <td><?php echo $end_date?></td>
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
