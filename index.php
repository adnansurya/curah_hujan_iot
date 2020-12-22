<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Curah Hujan</title>
</head>
<body>
    <h1>Curah Hujan</h1>
    <table  id="dataTable" width="100%" cellspacing="0" border="1">
        <thead>
            <tr> 
                <th>No</th>
                <th>Waktu</th>	                                               
                <th>Sensor 1</th>
                <th>Sensor 2</th>                                              
                <th>Sensor 3</th>
                <th>Sensor 4</th>
                <th>Sensor 5</th>
                <th>Timestamp</th>
            </tr>
        </thead>                                        
        <tbody>
        <?php   
            include 'db_access.php';                                         
            $load = mysqli_query($conn, "SELECT * FROM curahujan ORDER BY id DESC");   
            while ($row = mysqli_fetch_array($load)){
            echo '<tr>';
                echo '<td>'.$row['id'].'</td>';
                echo '<td>'.$row['waktu'].'</td>';
                echo '<td>'.$row['sensor1'].'</td>';
                echo '<td>'.$row['sensor2'].'</td>'; 
                echo '<td>'.$row['sensor3'].'</td>'; 
                echo '<td>'.$row['sensor4'].'</td>'; 
                echo '<td>'.$row['sensor5'].'</td>';
                echo '<td>'.$row['timestamp'].'</td>';                                        
            echo '</tr>';
            }                      
        ?>                                           
        </tbody>
    </table>
    
</body>
</html>