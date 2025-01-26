from pymongo import MongoClient
from datetime import datetime

client = MongoClient("mongodb://localhost:27017/")
db = client["store"]
collection = db["products"]

collection.delete_many({})

products = [
    # Электроника
    {
        "name": "Ноутбук ASUS",
        "manufacturer": "ASUS",
        "price": 50000,
        "category": "Электроника",
        "characteristics": {"model": "ZenBook", "year": 2023, "color": "серый"},
        "buyers": [
            {"name": "Иван Иванов", "purchase_date": "2024-01-10", "review": "Отличный ноутбук", "delivery_service": "Доставка.РФ"}
        ],
    },
    {
        "name": "Смартфон Samsung Galaxy",
        "manufacturer": "Samsung",
        "price": 40000,
        "category": "Электроника",
        "characteristics": {"model": "Galaxy S21", "year": 2021, "color": "черный"},
        "buyers": [
            {"name": "Иван Иванов", "purchase_date": "2023-11-15", "review": "Очень доволен", "delivery_service": "Почта России"},
            {"name": "Мария Петрова", "purchase_date": "2023-12-01", "review": "Хороший смартфон", "delivery_service": "Boxberry"}
        ]
    },
    {
        "name": "Ноутбук ASUS ZenBook",
        "manufacturer": "ASUS",
        "price": 75000,
        "category": "Электроника",
        "characteristics": {"model": "ZenBook 14", "year": 2023, "color": "серебристый"},
        "buyers": [
            {"name": "Алексей Смирнов", "purchase_date": "2024-01-15", "review": "Превосходно", "delivery_service": "СДЭК"}
        ]
    },
    {
        "name": "Наушники Sony WH-1000XM4",
        "manufacturer": "Sony",
        "price": 25000,
        "category": "Электроника",
        "characteristics": {"model": "WH-1000XM4", "year": 2022, "color": "черный"},
        "buyers": [
            {"name": "Сергей Кузнецов", "purchase_date": "2023-09-10", "review": "Хороший звук", "delivery_service": "Доставка.РФ"}
        ]
    },
    {
        "name": "Смарт-часы Apple Watch",
        "manufacturer": "Apple",
        "price": 35000,
        "category": "Электроника",
        "characteristics": {"model": "Series 8", "year": 2023, "color": "серый"},
        "buyers": [
            {"name": "Ольга Сергеева", "purchase_date": "2024-02-12", "review": "Очень удобные", "delivery_service": "Boxberry"},
            {"name": "Дмитрий Петров", "purchase_date": "2024-01-20", "review": "Полезный гаджет", "delivery_service": "СДЭК"}
        ]
    },
    # Одежда
    {
        "name": "Куртка Adidas",
        "manufacturer": "Adidas",
        "price": 12000,
        "category": "Одежда",
        "characteristics": {"size": "XL", "color": "черный", "material": "полиэстер"},
        "buyers": [
            {"name": "Мария Петрова", "purchase_date": "2024-01-20", "review": "Теплая и легкая", "delivery_service": "Доставка.РФ"}
        ]
    },
    {
        "name": "Футболка Nike",
        "manufacturer": "Nike",
        "price": 3500,
        "category": "Одежда",
        "characteristics": {"size": "M", "color": "белый", "material": "хлопок"},
        "buyers": [
            {"name": "Иван Иванов", "purchase_date": "2024-02-01", "review": "Качественная ткань", "delivery_service": "Boxberry"},
            {"name": "Анна Смирнова", "purchase_date": "2024-01-18", "review": "Идеально сидит", "delivery_service": "СДЭК"}
        ]
    },
    {
        "name": "Джинсы Levi's",
        "manufacturer": "Levi's",
        "price": 8000,
        "category": "Одежда",
        "characteristics": {"size": "L", "color": "синий", "material": "деним"},
        "buyers": [
            {"name": "Алексей Павлов", "purchase_date": "2023-12-15", "review": "Очень удобные", "delivery_service": "Доставка.РФ"}
        ]
    },
    {
        "name": "Спортивные штаны Puma",
        "manufacturer": "Puma",
        "price": 5000,
        "category": "Одежда",
        "characteristics": {"size": "L", "color": "серый", "material": "полиэстер"},
        "buyers": [
            {"name": "Сергей Кузнецов", "purchase_date": "2023-11-10", "review": "Комфортные", "delivery_service": "СДЭК"},
            {"name": "Марина Васильева", "purchase_date": "2024-01-05", "review": "Отлично подходят для спорта", "delivery_service": "Boxberry"}
        ]
    },
    {
        "name": "Кроссовки New Balance",
        "manufacturer": "New Balance",
        "price": 15000,
        "category": "Одежда",
        "characteristics": {"size": "42", "color": "белый", "material": "кожа"},
        "buyers": [
            {"name": "Дмитрий Петров", "purchase_date": "2024-02-10", "review": "Удобные и стильные", "delivery_service": "Почта России"},
            {"name": "Анна Смирнова", "purchase_date": "2024-01-25", "review": "Отличное качество", "delivery_service": "СДЭК"}
        ]
    },
    # Игрушки
    {
        "name": "Кукла Барби",
        "manufacturer": "Mattel",
        "price": 3000,
        "category": "Игрушки",
        "characteristics": {"age_category": "3+", "material": "пластик", "brand": "Barbie"},
        "buyers": [
            {"name": "Елена Васильева", "purchase_date": "2024-01-10", "review": "Дочка счастлива", "delivery_service": "Boxberry"}
        ]
    },
    {
        "name": "Конструктор LEGO",
        "manufacturer": "LEGO",
        "price": 8000,
        "category": "Игрушки",
        "characteristics": {"age_category": "6+", "material": "пластик", "brand": "LEGO"},
        "buyers": [
            {"name": "Андрей Орлов", "purchase_date": "2023-12-25", "review": "Отличный подарок", "delivery_service": "Почта России"}
        ]
    },
    {
        "name": "Мягкая игрушка мишка",
        "manufacturer": "Мир игрушек",
        "price": 1500,
        "category": "Игрушки",
        "characteristics": {"age_category": "0+", "material": "ткань", "brand": "SoftBear"},
        "buyers": [
            {"name": "Наталья Климова", "purchase_date": "2023-12-15", "review": "Очень мягкий", "delivery_service": "СДЭК"}
        ]
    },
    {
        "name": "Радиоуправляемая машина",
        "manufacturer": "Carrera",
        "price": 5500,
        "category": "Игрушки",
        "characteristics": {"age_category": "8+", "material": "пластик", "brand": "Carrera"},
        "buyers": [
            {"name": "Виктор Иванов", "purchase_date": "2024-01-05", "review": "Сын в восторге", "delivery_service": "Boxberry"},
            {"name": "Марина Петрова", "purchase_date": "2023-11-30", "review": "Качественная игрушка", "delivery_service": "Почта России"}
        ]
    },
    {
        "name": "Настольная игра Монополия",
        "manufacturer": "Hasbro",
        "price": 4000,
        "category": "Игрушки",
        "characteristics": {"age_category": "7+", "material": "картон, пластик", "brand": "Monopoly"},
        "buyers": [
            {"name": "Александр Смирнов", "purchase_date": "2024-01-20", "review": "Весёлая игра", "delivery_service": "СДЭК"},
            {"name": "Екатерина Орлова", "purchase_date": "2024-01-15", "review": "Понравилось всей семье", "delivery_service": "Boxberry"}
        ]
        },
        # Книги
        {
        "name": "Гарри Поттер и философский камень",
        "manufacturer": "Bloomsbury",
        "price": 1500,
        "category": "Книги",
        "characteristics": {"author": "Дж.К. Роулинг", "genre": "Фэнтези", "language": "русский"},
        "buyers": [
            {"name": "Ирина Смирнова", "purchase_date": "2023-12-20", "review": "Книга детства", "delivery_service": "Boxberry"},
            {"name": "Антон Климов", "purchase_date": "2024-01-05", "review": "Отличный перевод", "delivery_service": "СДЭК"}
        ]
        },
    {
        "name": "Война и мир",
        "manufacturer": "Эксмо",
        "price": 2000,
        "category": "Книги",
        "characteristics": {"author": "Лев Толстой", "genre": "Классика", "language": "русский"},
        "buyers": [
            {"name": "Мария Петрова", "purchase_date": "2023-11-30", "review": "Мастерское произведение", "delivery_service": "Почта России"}
        ]
    },
    {
        "name": "Властелин колец: Братство кольца",
        "manufacturer": "HarperCollins",
        "price": 2200,
        "category": "Книги",
        "characteristics": {"author": "Дж.Р.Р. Толкин", "genre": "Фэнтези", "language": "русский"},
        "buyers": [
            {"name": "Алексей Иванов", "purchase_date": "2024-02-01", "review": "Захватывающая эпопея", "delivery_service": "Boxberry"},
            {"name": "Ольга Сергеева", "purchase_date": "2024-01-18", "review": "Магия Толкина", "delivery_service": "СДЭК"}
        ]
    },
    {
        "name": "1984",
        "manufacturer": "Penguin Books",
        "price": 1600,
        "category": "Книги",
        "characteristics": {"author": "Джордж Оруэлл", "genre": "Антиутопия", "language": "русский"},
        "buyers": [
            {"name": "Виктор Петров", "purchase_date": "2024-01-10", "review": "Захватывающее чтение", "delivery_service": "Boxberry"}
        ]
    },
    {
        "name": "Три товарища",
        "manufacturer": "Издательство АСТ",
        "price": 1800,
        "category": "Книги",
        "characteristics": {"author": "Эрих Мария Ремарк", "genre": "Драма", "language": "русский"},
        "buyers": [
            {"name": "Екатерина Васильева", "purchase_date": "2024-01-25", "review": "Трогательная и глубокая книга", "delivery_service": "СДЭК"},
            {"name": "Дмитрий Орлов", "purchase_date": "2024-01-15", "review": "Печальная, но сильная история", "delivery_service": "Почта России"}
        ]
    }
]

collection.insert_many(products)
print("База данных создана и заполнена")