<?php
error_reporting(E_ALL);
ini_set('display_errors',1);
session_start();

if (!isset($_SESSION["authenticated"]) || $_SESSION["authenticated"] !== true) {
    header("Location: login.php");
    exit();
}

if (isset($_GET["type"]) && isset($_GET["file"])) {
    $filterType = $_GET["type"];
    $uploadedFile = $_GET["file"];

    $uploadDir = "dir_upload/";
    $sourceImage = $uploadDir . basename($uploadedFile);

    $image = imagecreatefromstring(file_get_contents($sourceImage));

    if ($image !== false) {
        // Применение выбранного фильтра
        switch ($filterType) {
            case 1:
                // Фильтр для черно-белого изображения
                imagefilter($image, IMG_FILTER_GRAYSCALE);
                break;
            case 2:
                // Фильтр для негатива
                imagefilter($image, IMG_FILTER_NEGATE);
                break;
            case 3:
                // Фильтр для сепии
                imagefilter($image, IMG_FILTER_COLORIZE, 90, 60, 40);
                break;
        }

        $filteredDir = "dir_filtered/";
        $filteredFileName = "filter_" . $filterType . "_" . basename($uploadedFile);
        $filteredImage = $filteredDir . $filteredFileName;

        imagejpeg($image, $filteredImage);

        imagedestroy($image);

        echo "<h3>Фото с фильтром:</h3>";
        echo "<img src='$filteredImage'>";
        echo "<a href='upload.php'><button>Назад</button></a>";
    } else {
        echo "Ошибка при обработке изображения.";
    }
} else {
    echo "Выберите фильтр для изображения.";
}
?>
