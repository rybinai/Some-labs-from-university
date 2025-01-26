import tkinter as tk
from tkinter import messagebox
from pymongo import MongoClient

client = MongoClient("mongodb://localhost:27017/")
db = client["store"]
collection = db["products"]

#1
def get_products_by_category():
    category = category_entry.get()
    if category:
        results = collection.find({"category": category})
        product_names = [product["name"] for product in results]
        result_label.config(text=f"Товары в категории '{category}':\n" + "\n".join(product_names))
    else:
        messagebox.showwarning("Ошибка", "Введите категорию.")
#2
def get_characteristics_by_category():
    category = category_entry.get()
    if category:
        results = collection.find({"category": category})
        characteristics = []
        for product in results:
            characteristics.append(str(product["characteristics"]))
        result_label.config(text=f"Характеристики товаров в категории '{category}':\n" + "\n".join(characteristics))
    else:
        messagebox.showwarning("Ошибка", "Введите категорию.")
#3
def get_products_by_buyer():
    buyer_name = buyer_entry.get()
    if buyer_name:
        results = collection.find({"buyers.name": buyer_name})
        product_info = []
        for product in results:
            for buyer in product["buyers"]:
                if buyer["name"] == buyer_name:
                    product_info.append(f"Товар: {product['name']}, Цена: {product['price']}")
        result_label.config(text=f"Товары, купленные покупателем '{buyer_name}':\n" + "\n".join(product_info))
    else:
        messagebox.showwarning("Ошибка", "Введите имя покупателя.")
#4
def get_products_by_color():
    color = color_entry.get()
    if color:
        results = collection.find({"characteristics.color": color})
        product_info = []
        for product in results:
            product_info.append(f"Товар: {product['name']}, Производитель: {product['manufacturer']}, Цена: {product['price']}")
        result_label.config(text=f"Товары с цветом '{color}':\n" + "\n".join(product_info))
    else:
        messagebox.showwarning("Ошибка", "Введите цвет.")
#5  
def get_total_sales():
    results = collection.find()
    total_sum = sum(product["price"] for product in results)
    result_label.config(text=f"Общая сумма проданных товаров: {total_sum}")
#6
def get_product_counts():
    results = collection.aggregate([
        {"$group": {"_id": "$category", "count": {"$sum": 1}}}
    ])
    category_counts = [f"{result['_id']}: {result['count']} товаров" for result in results]
    result_label.config(text="Количество товаров в каждой категории:\n" + "\n".join(category_counts))
#7
def get_buyers_by_product():
    product_name = product_entry.get()
    if product_name:
        results = collection.find({"name": product_name})
        buyer_names = []
        for product in results:
            for buyer in product["buyers"]:
                buyer_names.append(buyer["name"])
        result_label.config(text=f"Покупатели товара '{product_name}':\n" + "\n".join(buyer_names))
    else:
        messagebox.showwarning("Ошибка", "Введите название товара.")
#8
def get_buyers_by_product_and_delivery_service():
    product_name = product_entry.get()
    delivery_service = delivery_service_entry.get()
    if product_name and delivery_service:
        results = collection.find({
            "name": product_name,
            "buyers.delivery_service": delivery_service
        })
        buyer_names = []
        for product in results:
            for buyer in product["buyers"]:
                if buyer["delivery_service"] == delivery_service:
                    buyer_names.append(buyer["name"])
        result_label.config(text=f"Покупатели товара '{product_name}' с доставкой '{delivery_service}':\n" + "\n".join(buyer_names))
    else:
        messagebox.showwarning("Ошибка", "Введите название товара и доставку.")

root = tk.Tk()
root.title("Запросы к базе данных")

category_label = tk.Label(root, text="Категория товара:")
category_label.grid(row=0, column=0)
category_entry = tk.Entry(root)
category_entry.grid(row=0, column=1)
category_button = tk.Button(root, text="Получить товары по категории", command=get_products_by_category)
category_button.grid(row=0, column=2)

characteristics_button = tk.Button(root, text="Получить характеристики по категории", command=get_characteristics_by_category)
characteristics_button.grid(row=1, column=2)

buyer_label = tk.Label(root, text="Имя покупателя:")
buyer_label.grid(row=2, column=0)
buyer_entry = tk.Entry(root)
buyer_entry.grid(row=2, column=1)
buyer_button = tk.Button(root, text="Получить товары покупателя", command=get_products_by_buyer)
buyer_button.grid(row=2, column=2)

color_label = tk.Label(root, text="Цвет товара:")
color_label.grid(row=3, column=0)
color_entry = tk.Entry(root)
color_entry.grid(row=3, column=1)
color_button = tk.Button(root, text="Получить товары по цвету", command=get_products_by_color)
color_button.grid(row=3, column=2)

total_sales_button = tk.Button(root, text="Общая сумма проданных товаров", command=get_total_sales)
total_sales_button.grid(row=4, column=2)

category_counts_button = tk.Button(root, text="Количество товаров в категории", command=get_product_counts)
category_counts_button.grid(row=5, column=2)

product_label = tk.Label(root, text="Название товара:")
product_label.grid(row=6, column=0)
product_entry = tk.Entry(root)
product_entry.grid(row=6, column=1)
buyers_button = tk.Button(root, text="Получить покупателей товара", command=get_buyers_by_product)
buyers_button.grid(row=6, column=2)

delivery_service_label = tk.Label(root, text="Служба доставки:")
delivery_service_label.grid(row=7, column=0)
delivery_service_entry = tk.Entry(root)
delivery_service_entry.grid(row=7, column=1)
buyers_delivery_service_button = tk.Button(root, text="Получить покупателей с доставкой", command=get_buyers_by_product_and_delivery_service)
buyers_delivery_service_button.grid(row=7, column=2)

result_label = tk.Label(root, text="", justify=tk.LEFT)
result_label.grid(row=8, column=0, columnspan=3)

root.mainloop()