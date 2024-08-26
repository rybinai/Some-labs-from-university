<?php
// imagecreatetruecolor - Возвращает идентификатор изображения, представляющий черное изображение заданного размера. 
$im = imagecreatetruecolor(200, 200);

$blue = imagecolorallocate($im, 0, 0, 255);
$red = imagecolorallocate($im, 255, 0, 0);
$green = imagecolorallocate($im, 0, 255, 0);


// Зеленый треугольник вверху
$values = array(
    100, 20,   // Верхняя точка
    50, 100,   // Левая точка
    150, 100,  // Правая точка
);

// imagefilledpolygon - Создает закрашенный многоугольник в заданном изображении image. 
imagefilledpolygon($im, $values, 3, $green);

// imagefilledellipse - Рисует эллипс с центром в заданных координатах изображения image. 
imagefilledellipse($im, 100, 100, 80, 80, $red); // Красный круг в середине

// imagefilledrectangle - Создает прямоугольник закрашенный цветом color в заданном изображении image. 
imagefilledrectangle($im, 50, 130, 150, 180, $blue); // Синий квадрат внизу

// прорисовка
// header - Отправка HTTP заголовка 
header("Content-type: image/png");
// imagepng - Вывод PNG изображения в броузер или файл 
imagepng($im);

// imagedestroy - освобождает память, занятую изображением image
imagedestroy($im);
