<html>
<!--  
    CHANGE COLUMN NAMES WITH REQUIRED VALUES
    DATABASE CONFIGURATION FILE IS ON API FOLDER
-->
    <head>
        <title>TITLE</title>
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
            <h1> WORDSWORDWORDSWORDS </h1>
            <h2> WORDSWORDWORDSWORDS </h2>
        </div>
        <table class="table1" align="center">
        <thead>
            <tr>
                <td>COLUMN1</td>
                <td>COLUMN2</td>
                <td>COLUMN3</td>
                <td>COLUMN4</td>
               
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
                    $results = mysqli_query($connect,"SELECT * FROM " .DB_TABLE. " WHERE columnName BETWEEN DATE_SUB(CURDATE(), INTERVAL 1 DAY) AND CURDATE()"); //query for 1 day long logs
                    while($row = mysqli_fetch_array($results)) {
                        $end_date = date("Y-m-d H:i:s", strtotime("+" . 3 . " hours", strtotime($row["columnName"]))); //this row for the timezone difference
                ?>
                <tr>
                    <td><?php echo $end_date?></td>  <!-- Change this values with database column names -->
                    <td><?php echo $row['DBCOLUMN1']?></td>
                    <td><?php echo $row['DBCOLUMN2']?></td>
                    <td><?php echo $row['DBCOLUMN3']?></td>
                </tr>
                
            <?php
            }
            ?>
          
            </tbody>
            </table>
    </body>
</html>
