<?php
// тип содержимого - jpg
// header - Отправка HTTP заголовка 
header('Content-Type: image/jpeg');

// открытие файла с картинкой и связываем его с идентификатором $im
$im = imagecreatefromjpeg("./1.jpg");

// создание цвета текста    
$text_color = imagecolorallocate($im, 255, 255, 255); // Белый цвет текста

// Загрузка arial шрифта
$font = 'arial.ttf';
$text  = "ЕГЭ ПО РИСОВАНИЮ";

// Прорисовка строки текста шрифтом (латиница!)
imagettftext($im, 36, 0, 65, 380, $text_color, $font, $text);

// Сохранение изображение в файл demotivator.jpg
imagejpeg($im)  ;

// imagedestroy - освобождает память, занятую изображением image
imagedestroy($im);
?>