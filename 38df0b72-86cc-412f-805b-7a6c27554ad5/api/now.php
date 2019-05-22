<html>
    <head>
        <title>Now</title>
        <style>
            
           
            .now{background-color:#FFFFFF; color:#FFFFFF;}
            img{width:80px; height:80px; }
           
        </style>
    </head>
    <body>
        <table class="table1" align="center">
        <thead>
            <tr class="noww">
                <td><img src="/img/fridge.png" alt="Fridge Image"></td>
                <td><img src="/img/thermometer.png" alt="Thermometer Image"></td>
                <td><img src="/img/humidity.png" alt="Humidity Image"></td>
               
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
            $results = mysqli_query($connect,"SELECT * FROM log ORDER BY id DESC LIMIT 1");
            while($row = mysqli_fetch_array($results)) {
            
                $tempin = $row['tempin'];
                $tempout = $row['tempout'];
                $hum = $row['hum'];
            }
            ?>
                
                <tr>
                    <td><font face="Verdana" size="3"><b><?php echo $tempin ?></b></font></td>
                    <td><font face="Verdana" size="3"><b><?php echo $tempout ?></b></font></td>
                    <td><font face="Verdana" size="3"><b><?php echo $hum ?></b></font></td>
                </tr>

           
            </tbody>
            </table>
    </body>
</html>