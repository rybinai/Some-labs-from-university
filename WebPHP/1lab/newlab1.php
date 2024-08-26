<?php
error_reporting(E_ALL);
ini_set('display_errors',1);
// Описание скалярных переменных
$a = 15;                       // целое
$fl = 3.14;                   // с плавающей точкой
$boo = true;                  // boolean
$str = "stroka";              // строка
$nol = 0;
$pusto = "";

$s1 = "Переменная a = $a \n"; // разбираемая строка
$s2 = 'Переменная a = $a \n'; // неразбираемая строка

// Описание массива 
$mas = array( "one" => TRUE,
        1   => -20,
          "three" => 3.14);
$mas[]="two";
$mas["four"]=4;

// Описание константы 
define("HOST", "");

$resultS1 = $s1;
$resultS2 = $s2;
 
// 7 задание

$ans_7 = 'array(5) { ["one"]=> bool(true) [1]=> int(-20) ["three"]=> float(3.14) [2]=> string(3) "two" ["four"]=> int(4) } ';

// 10 задание

$ans_9 = '
$name = "a";
$ref = &$a;     
$ref = 1;
';
$name = "a";
$ref = &$a; 
$ref = 1;

// Ассоциативный массив $colours
$colors = [
    "каждый" => '#ff0000',
    "охотник" => '#ffa500',
    "желает" => '#ffff00',
    "знать" => '#008000',
    "где" => '#87cefa',
    "сидит" => '#0000ff',
    "фазан" => '#9400d3'
];

asort($colors);

$table = '<table>';
$table .= '<thead><tr>';
foreach ($colors as $key => $value) {
    $table .= '<th style="background-color: ' . $value . '">' . $key . '</th>';
}
$table .= '</tr></thead>';
$table .= '<tbody><tr>';
foreach ($colors as $key => $value) {
    $table .= '<td style="background-color: ' . $value . '">' . $key . '</td>';
}
$table .= '</tr></tbody>';
$table .= '</table>';

$file_name = basename(__FILE__);
$link = '<a href=""> link </a>';

$ans_15 = $colors = [
        "каждый" => '#ff0000',
        "охотник" => '#ffa500',
        "желает" => '#ffff00',
        "знать" => '#008000',
        "где" => '#87cefa',
        "сидит" => '#0000ff',
        "фазан" => '#9400d3'
    ]; 

    asort($colors);

    $table = '<table>';
    $table .= '<thead><tr>';
    foreach ($colors as $key => $value) {
        $table .= '<th style="background-color: ' . $value . '">' . $key . '</th>';
    }
    $table .= '</tr></thead>';
    $table .= '<tbody><tr>';
    foreach ($colors as $key => $value) {
        $table .= '<td style="background-color: ' . $value . '">' . $key . '</td>';
    }
    $table .= '</tr></tbody>';
    $table .= '</table>';

$ans_15 = ' <xmp>
$colors = [
    "каждый" => \'#ff0000\',
    "охотник" => \'#ffa500\',
    "желает" => \'#ffff00\',
    "знать" => \'#008000\',
    "где" => \'#87cefa\',
    "сидит" => \'#0000ff\',
    "фазан" => \'#9400d3\'
]; 

asort($colors);

$table = \'<table>\';
$table .= \'<thead><tr>\';
foreach ($colors as $key => $value) {
    $table .= \'<th style="background-color: \' . $value . \'">\' . $key . \'</th>\';
}
$table .= \'</tr></thead>\';
$table .= \'<tbody><tr>\';
foreach ($colors as $key => $value) {
    $table .= \'<td style="background-color: \' . $value . \'">\' . $key . \'</td>\';
}
$table .= \'</tr></tbody>\';
$table .= \'</table>\';
</xmp>';  

//Фукнция f-color
function f_color($number = 0) {
    $output_str = ($number % 2 ==0) ? "<span style=\"color: green\">" . $number . "</span>" : 
    "<span style=\"color: red\">" . $number . "</span>";
    return $output_str;
}
$ans_16 = '
<xmp>function f_color($number = 0) { 
    $output_str = ($number % 2 ==0) ? " <span style=\"color: green\">". $number . "</span>" : 
    "<span style=\"color: red\">" . $number . "</span>";
    return $output_str; </xmp>
    }
   ';
// Массив заданий
$tasks = array(
    1 => ["echo", "echo \$a, \$fl, \$boo, \$str", 
        "$a$fl$boo$str"],
    2 => ["echo", "echo \$a . \$str", 
        $a . $str],
    3 => ["echo", "echo \$a > \$str, \$a < \$str, \$a == \$str, \$a === \$str",
        ($a > $str) . ", " . ($a < $str) . ", " . ($a == $str) . ", " . ($a === $str)],
    4 => ["echo", "echo \$nol == \$pusto, \$nol === \$pusto",
        ($nol == $pusto) . ", " . ($nol === $pusto)],
    5 => ["echo", "echo $s1 $s2", "{$resultS1}, {$resultS2}"],    
    6 => ["echo", "echo \$mas[\"one\"], \$mas[2], \$mas[3]",
        "{$mas["one"]}, {$mas[2]}, {$mas[3]}"],
    7 => ["echo", "echo var_dump(\$mas)",   
        $ans_7],
    8 => ["echo", "echo implode(\$mas)", 
        implode(',', $mas)],
    9 => ["echo", "echo $ans_9",     
        ${$name}],
    10 => ["echo", "echo \$a", 
        $a],
    11 => ["echo", "echo HOST", 
        HOST], 
    12 => ["echo", "echo shell_exec('ls -a')",
        shell_exec('ls -a')],
    13 => ["echo", "echo gettype(\$str).\$nol . 1",
        gettype($str).$nol . 1],
    14 => ["echo", ' <xmp> echo  $file_name = basename(__FILE__); </xmp> <br> 
    <xmp> echo $link = "<a href="$file_name"> $file_name </a>"; 
    </xmp>' , $link ],
    15 => ["echo","$ans_15", $table],
    16 => ["echo", "$ans_16", 
    f_color(1) . f_color(2) . f_color(0)]
);

echo "<table border='1'>";
echo "<tr><th>Номер задания</th><th>Решение</th><th>Результат</th></tr>";
foreach ($tasks as $taskNumber => $task) {
    echo "<tr><td>$taskNumber</td><td>{$task[1]}</td><td>{$task[2]}</td></tr>";
}
echo "</table>";
