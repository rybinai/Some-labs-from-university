import tkinter as tk
from tkinter import messagebox
from pymongo import MongoClient

#client = MongoClient('localhost', 27017) 
client = MongoClient("mongodb://localhost:27017/")  
db = client['football_database']
teams_collection = db['teams']
games_collection = db['games']

# Временное хранилище текущего документа, который показывается в интерфейсе
current_document = {}

def add_key_value():
    global current_document
    key = key_entry.get()
    value = value_entry.get()

    if not key or not value:
        messagebox.showwarning("Ошибка", "Ключ и значение не могут быть пустыми.")
        return

    # Если ключ "players", => обработка для игрока
    if key == "players":
        # Проверка есть ли players, if not => создаем
        if "players" not in current_document:
            current_document["players"] = []
        # Разделение строки + проверка
        parts = value.split(",")
        if len(parts) == 2:
            name, position = map(str.strip, parts)
            current_document["players"].append({"name": name, "position": position})
            messagebox.showinfo("Добавлено", f"Игрок {name} ({position}) добавлен в текущий документ.")
        else:
            messagebox.showerror("Ошибка", "Введите данные игрока в формате: ФИО, позиция")
    # Если ключ "goals", => обработка дял гола
    elif key == "goals":
        # Проверка есть ли goals, if not => создаем
        if "goals" not in current_document:
            current_document["goals"] = [] 
        # Разделение на части + проверка
        parts = value.split(",")
        if len(parts) == 4:  
            position, minute, author, assist = map(str.strip, parts)
            if minute.isdigit():
                current_document["goals"].append({
                    "position": position,
                    "minute": int(minute),  
                    "author": author,
                    "assist": assist if assist != "нет передачи" else None  
                })
                messagebox.showinfo("Добавлено", f"Гол на {minute} минуте, автор: {author}, передача: {assist} добавлен.")
            else:
                messagebox.showerror("Ошибка", "Значение 'минута' должно быть числом.")
        else:
            messagebox.showerror("Ошибка", "Введите данные гола в формате: положение, минута, автор, передача")
    else:
        current_document[key] = value
        messagebox.showinfo("Добавлено", f"{key}: {value} добавлено в текущий документ.")

def save_document(collection):
    global current_document
    if not current_document:
        messagebox.showwarning("Ошибка", "Текущий документ пуст.")
        return
    # Добавление документв в указанную колекцию 
    collection.insert_one(current_document)
    current_document = {}
    messagebox.showinfo("Сохранено", "Документ сохранен в базе данных.")

def show_document():
    documents_list.delete(0, tk.END)
    # Получение данных из колекций
    teams_documents = teams_collection.find()
    games_documents = games_collection.find()

    for doc in teams_documents:
        doc_copy = doc.copy()  
        doc_copy.pop('_id', None)  
        display_text = f"Команда: {str(doc_copy)}"
        documents_list.insert(tk.END, display_text)

    for doc in games_documents:
        doc_copy = doc.copy()  
        doc_copy.pop('_id', None)  
        display_text = f"Игра: {str(doc_copy)}"
        documents_list.insert(tk.END, display_text)

def search_document(collections):
    key = search_key_entry.get()
    operator = search_operator_entry.get()
    value = search_value_entry.get()
    
    if not key or not operator or not value:
        messagebox.showwarning("Ошибка", "Все поля поиска должны быть заполнены.")
        return
    
    query = {}
    if operator in ["=", ">", ">=", "<", "<="]:
        if operator == "=":
            query[key] = value
        else:
            if value.isdigit(): 
                numeric_value = int(value)
                operator_mapping = {
                    ">": "$gt",
                    ">=": "$gte",
                    "<": "$lt",
                    "<=": "$lte",
                }
                query[key] = {operator_mapping[operator]: numeric_value}
            else:
                messagebox.showerror("Ошибка", "Значение должно быть числом для сравнения.")
                return
    else:
        messagebox.showerror("Ошибка", "Недопустимый знак сравнения.")
        return

    documents_list.delete(0, tk.END)
    
    # Выполение поиск в каждой коллекции
    for collection in collections:
        results = collection.find(query)
        for result in results:
            result.pop('_id', None)
            collection_name = "Команды" if collection == teams_collection else "Игры"
            documents_list.insert(tk.END, f"{collection_name} {result}")

def aggregate_query():
    command = aggregate_entry.get() 
    
    if "количество футболистов, забивших более двух голов" in command:
        pipeline = [
            # $unwind - Разворачивает массив для обработки элементов как документов
            {"$unwind": "$goals"},
            # Группируем по имени игрока и считаем количество голов
            {"$group": {
                "_id": "$goals.author",  # Группировка по автору гола
                "goal_count": {"$sum": 1}  # Кол-во голов
            }},
            # match - фильтр по условию больше 2 голов
            {"$match": {"goal_count": {"$gt": 2}}}
        ]
        
        # Агрегация
        results = games_collection.aggregate(pipeline)
        
    else:
        messagebox.showerror("Ошибка", "Неизвестная команда.")
        return
    
    documents_list.delete(0, tk.END)
    for result in results:
        documents_list.insert(tk.END, f"Игрок: {result['_id']}, Голов: {result['goal_count']}")

# Создание окна приложения
app = tk.Tk()
app.title("Управление футбольными данными")

# Поля ввода и кнопки для текущего документа
tk.Label(app, text="Ключ:").grid(row=0, column=0)
key_entry = tk.Entry(app)
key_entry.grid(row=0, column=1)

tk.Label(app, text="Значение:").grid(row=1, column=0)
value_entry = tk.Entry(app)
value_entry.grid(row=1, column=1)

add_button = tk.Button(app, text="Добавить ключ-значение", command=add_key_value)
add_button.grid(row=2, column=0, columnspan=2)

save_team_button = tk.Button(app, text="Сохранить команду", command=lambda: save_document(teams_collection))
save_team_button.grid(row=4, column=0, columnspan=2)

save_game_button = tk.Button(app, text="Сохранить игру", command=lambda: save_document(games_collection))
save_game_button.grid(row=5, column=0, columnspan=2)

# Поля поиска и кнопка
tk.Label(app, text="Поиск:").grid(row=6, column=0, columnspan=2)

tk.Label(app, text="Ключ:").grid(row=7, column=0)
search_key_entry = tk.Entry(app)
search_key_entry.grid(row=7, column=1)

tk.Label(app, text="Знак сравнения:").grid(row=8, column=0)
search_operator_entry = tk.Entry(app)
search_operator_entry.grid(row=8, column=1)

tk.Label(app, text="Значение:").grid(row=9, column=0)
search_value_entry = tk.Entry(app)
search_value_entry.grid(row=9, column=1)

search_button = tk.Button(app, text="Поиск", command=lambda: search_document([teams_collection, games_collection]))
search_button.grid(row=10, column=0, columnspan=2)

# Поля агрегации и кнопка
tk.Label(app, text="Агрегация:").grid(row=11, column=0, columnspan=2)

aggregate_entry = tk.Entry(app)
aggregate_entry.grid(row=12, column=0, columnspan=2)

aggregate_button = tk.Button(app, text="Выполнить агрегацию", command=lambda: aggregate_query())
aggregate_button.grid(row=13, column=0, columnspan=2)

# Список для отображения документов
documents_list = tk.Listbox(app, width=80, height=15)
documents_list.grid(row=14, column=0, columnspan=2)

# Кнопка для отображения данных о командах и играх
show_document_button = tk.Button(app, text="Показать документ", command=show_document)
show_document_button.grid(row=15, column=0, columnspan=2)

app.mainloop()