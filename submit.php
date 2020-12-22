<?php
    include 'db_access.php';

    if(isset($_GET['waktu']) && isset($_GET['sen1']) && isset($_GET['sen2']) && isset($_GET['sen3']) && isset($_GET['sen4']) && isset($_GET['sen5'])){

        $waktu = $_GET['waktu'];
        $sen1 = $_GET['sen1'];
        $sen2 = $_GET['sen2'];
        $sen3 = $_GET['sen3'];
        $sen4 = $_GET['sen4'];
        $sen5 = $_GET['sen5'];

        $sql = "INSERT INTO curahujan (sensor1,sensor2,sensor3,sensor4,sensor5,waktu, timestamp) VALUES ('$sen1','$sen2','$sen3','$sen4','$sen5','$waktu',current_timestamp())";
        if (!mysqli_query($conn,$sql)){            
            echo 'Terjadi Kesalahan pada database curahujan';
        
        }else{
            echo 'Data berhasil disimpan';
        }
    }else{
        echo 'Data kurang lengkap';
    }
?>