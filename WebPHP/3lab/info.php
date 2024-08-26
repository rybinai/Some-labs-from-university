<?php
session_start(); 

if (!isset($_SESSION["authenticated"]) || $_SESSION["authenticated"] !== true) {
    header("Location: login.php"); 
    exit; 
}

if($_SERVER['HTTP_REFERER'] !== "http://localhost:3000/3lab/login.php"){
    header("Location: login.php"); 
    exit; 
}
?>  

<!DOCTYPE html>
<html>
<head>
    <title>Информация</title>
</head>
<body>  
    <?php
    echo "<h3>Информация</h3>";
    echo "User: " . get_current_user() . "<br/><br/>"; // имя текущего пользователя
    echo "Web-сервер: " . $_SERVER['SERVER_NAME'] . "<br/>"; // имя веб-сервера
    echo "Версия браузера: " . $_SERVER['HTTP_USER_AGENT'] . "<br/>"; // версия браузера
    echo "Адрес перехода: " . $_SERVER['HTTP_REFERER'] . "<br/>"; // URL предыдущей страницы
    ?>
    <br>
    <a href="login.php">Выйти</a>
</body>
</html>
