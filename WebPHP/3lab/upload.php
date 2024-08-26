<?php
if(isset($_FILES['file'])){
    $uploadFile = $uploadDir . basename($_FILES['file']['name']);
    $Name = $_FILES['file']['tmp_name'];

    if(move_uploaded_file($Name, $uploadFile)){
        echo "Файл успешно загружен.<br>";
        echo "Временное имя файла: " . $Name . "<br>";
        echo "Постоянное имя файла: " . $uploadFile;
    } else {
        echo "Ошибка при загрузке файла.";
    }
}
?>
