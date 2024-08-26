<?php
error_reporting(E_ALL);
ini_set('display_errors',1);
session_start();

if (!isset($_SESSION["authenticated"]) || $_SESSION["authenticated"] !== true) {
    header("Location: login.php");
    exit(); 
}

if ($_SERVER["REQUEST_METHOD"] === "POST" && isset($_FILES["file"])) {
    // Проверка, является ли файл изображением
    $check = getimagesize($_FILES["file"]["tmp_name"]);
    if($check !== false) {
        $uploadDir = "dir_upload/";
        $uploadedFile = $uploadDir . basename($_FILES["file"]["name"]);

        if (move_uploaded_file($_FILES["file"]["tmp_name"], $uploadedFile)) {
            echo "Файл успешно загружен. <br>";
            echo "<img src='$uploadedFile'><br>";

            echo "<h3>Выберите фильтр:</h3>";
            echo "<ul>";
            echo "<li><a href='./filter.php?type=1&file=$uploadedFile'>Фильтр: Черно-белое </a></li>";
            echo "<li><a href='./filter.php?type=2&file=$uploadedFile'>Фильтр: Негатив</a></li>";
            echo "<li><a href='./filter.php?type=3&file=$uploadedFile'>Фильтр: Сепия</a></li>";
            echo "</ul>";
        } else {
            echo "Ошибка при загрузке файла.";
        }
    } else {
        echo "Файл не является изображением.";
        echo "<a href=''>Вернуться к загрузке</a>";
    }
} else {
    ?>
    <form method="post" action="" enctype="multipart/form-data">
        <label for="file">Выберите файл для загрузки:</label>
        <input type="file" id="file" name="file" required><br>
        <button type="submit">Загрузить</button>
    </form>
    <?php
}
?>
