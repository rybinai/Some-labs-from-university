<?php

// открытие файла с картинкой и связываем его с идентификатором $im
$im = imagecreatefromjpeg("./cat.jpg");

// Применяем фильтр для преобразования изображения в черно-белый формат
imagefilter($im, IMG_FILTER_NEGATE);

// устанавливаем тип содержимого 
// header - Отправка HTTP заголовка 
header('content-type: image/jpeg');
  
// вывод изображения на экран 
imagejpeg($im);
  
// imagedestroy - освобождает память, занятую изображением image
imagedestroy($im);

?>