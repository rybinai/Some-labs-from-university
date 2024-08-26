<?php
ini_set('display_errors', 1); 
ini_set('display_startup_errors', 1); 
error_reporting(E_ALL);
// 1    
class NotePad {
    public $phone;  // свойство должно быть доступно только в контексте класса;
    public $name;  // свойство должно быть доступно как в контексте класса, так и вне его;
    public $surname;  // свойство должно быть доступно как в контексте класса, так и вне его;

    const TEXT_SIZE = 20;  // конста

    // 3 пункт
    public function __construct($phone, $name, $surname) {
        // this - обращение к переменной в классе
        $this->phone = $phone;
        $this->name = $name;
        $this->surname = $surname;
    }

    public function note_show() {
        echo "Phone: " . $this->phone . ", Name: " . $this->name . ", Surname: " . $this->surname . ", TEXT_SIZE: " . self::TEXT_SIZE . "<br>";
    }
    // 4 пункт
    public function __clone() {
        $this->phone = null;
        $this->name = null;
        $this->surname = null;
    }   
}
// 5 пункт
class NoteChild extends NotePad {
    public function note_show() {
        echo "Текщий класс" . __CLASS__ . "<br>";
        echo "Вызов родительского метода note_show<br>";
        parent::note_show();
        // Вызов родительского класса
    }

    public function cut_note() {
        $this->phone = mb_substr($this->phone, 0, parent::TEXT_SIZE, 'UTF-8');
        $this->name = mb_substr($this->name, 0, parent::TEXT_SIZE, 'UTF-8');
        $this->surname = mb_substr($this->surname, 0, parent::TEXT_SIZE, 'UTF-8');
    }
}
 

// 2 пункт
echo " 2 пункт " . "<br>";
$note1 = new NotePad("1111", "", "");
$note1->note_show();
echo NotePad::TEXT_SIZE . "<br>";

// 3 пункт
echo " 3 пункт " . "<br>";  
$note2 = new NotePad("3333", "3", "");
$note2->note_show();

// 4 пункт
echo " 4 пункт " . "<br>";
$note2_copy = clone $note2;
$note2_copy->note_show();

// 5 пункт  
echo " 5 пункт " . "<br>";
$note_child = new NoteChild("5555", "5", "");
$note_child->note_show();

// 6 пункт
echo " 6 пункт " . "<br>";
$child1 = new NoteChild("6666", "6", "");
$child1->note_show();
echo " Копия    " . "<br>";
$child1_copy = $child1;
$child1_copy->note_show(); 

// 7 пункт
echo " 7 пункт " . "<br>";
$child2 = new NoteChild("7777", "7", "");
$child2->cut_note();
$child2->note_show();
