<html>
<!--  
    CHANGE COLUMN NAMES WITH REQUIRED VALUES
    DATABASE CONFIGURATION FILE IS ON API FOLDER
-->
    <head>
        <title>All Logs</title>
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
            <h1>Title</h1>
            <h2>All Logs</h2>
        </div>
        <table class="table1" align="center">
        <thead>
            <tr>
                <td>Column1</td>
                <td>Column2</td>
                <td>Column3</td>
                <td>Column4</td>
               
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
            $results = mysqli_query($connect,"SELECT * FROM " .DB_TABLE. " ORDER BY id");
            while($row = mysqli_fetch_array($results)) {
                $end_date = date("Y-m-d H:i:s", strtotime("+" . 3 . " hours", strtotime($row["columnName"]))); //this row for the timezone difference
            ?>
                <tr>
                    <td><?php echo $end_date?></td>
                    <td><?php echo $row['db_column1']?></td> <!-- Change this values with database column names -->
                    <td><?php echo $row['db_column2']?></td>
                    <td><?php echo $row['db_column3']?></td>
                </tr>

            <?php
            }
            ?>
            </tbody>
            </table>
    </body>
</html>
