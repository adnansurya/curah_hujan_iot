<?php
    include 'db_access.php';
    $date = new DateTime("now", new DateTimeZone('Asia/Makassar') );
    $timestamp = $date->format('Y-m-d H:i:s');

    // Takes raw data from the request
    $json = file_get_contents('php://input');

    // Converts it into a PHP object
    $data = new \stdClass();
    $data = json_decode($json);

    $waktu = $data -> waktu;
    $sen1 = $data -> sen1;
    $sen2 = $data -> sen2;
    $sen3 = $data -> sen3;
    $sen4 = $data -> sen4;
    $sen5 = $data -> sen5;

    $sql = "INSERT INTO curahujan (sensor1,sensor2,sensor3,sensor4,sensor5,waktu, timestamp) VALUES ('$sen1','$sen2','$sen3','$sen4','$sen5','$waktu','$timestamp')";
    if (!mysqli_query($conn,$sql)){            
        echo 'Terjadi Kesalahan pada database curahujan';
    
    }else{
        echo 'Data berhasil disimpan';
    }
    
?>