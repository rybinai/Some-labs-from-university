<?php
session_start();

if ($_SERVER["REQUEST_METHOD"] == "POST") { 
    $username = $_POST["username"]; 
    $password = $_POST["password"]; 

    if ($username === "user" && $password === "qwerty") { 
        $_SESSION["authenticated"] = true; 
        header("Location: info.php"); 
        exit; 
    } else {
        echo "Неверный логин или пароль!"; 
    }
}
?>

<!DOCTYPE html>
<html>
<head>
    <title>Вход</title>
</head>
<body>
    <h3>Авторизация</h3>
    <form method="post" action="<?php echo $_SERVER["PHP_SELF"]; ?>">
        <label>Логин: </label>
        <input type="text" name="username" required><br> 
        <label>Пароль: </label>
        <input type="password" name="password" required><br> 
        <input type="submit" value="Войти"> 
    </form>
</body>
</html>
