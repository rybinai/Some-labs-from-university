<?php
error_reporting(E_ALL);
ini_set('display_errors',1);
session_start();

if (isset($_SESSION["authenticated"]) && $_SESSION["authenticated"] === true) {
    header("Location: upload.php");
    exit();
}

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $username = $_POST["username"];
    $password = $_POST["password"];

    if ($username == "user" && $password == "qwerty") {
        $_SESSION["authenticated"] = true;
        header("Location: upload.php");
        exit();
    } else {
        echo "Неверное имя пользователя или пароль";
    }
}
?>

<form method="post" action="">
    <label for="username">Логин:</label>
    <input type="text" id="username" name="username" required><br>
    <label for="password">Пароль:</label>
    <input type="password" id="password" name="password" required><br>
    <button type="submit">Войти</button>
</form>
