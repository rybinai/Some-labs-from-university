import redis
import tkinter as tk
from tkinter import ttk

r = redis.Redis(host='127.0.0.1', port=6379, db=1)

users = ['', 'Алексей', 'Никита', 'Виктор']

font_styles = ['Arial', 'Times New Roman', 'Courier New', 'Verdana']

color_dict = {
    'Черный': '#000000',
    'Красный': '#FF0000',
    'Зеленый': '#00FF00',
    'Синий': '#0000FF',
    'Желтый': '#FFFF00',
    'Фиолетовый': '#800080',
}

style_dict = {
    'Обычный': 'normal',
    'Курсив': 'italic',
    'Жирный': 'bold',
    'Подчеркнутый': 'underline'
}

def save_settings():
    user = user_var.get()
    if user:
        settings = {
            'font_name': font_var.get(),
            'font_size': size_var.get(),
            'font_color': color_dict[color_var.get()],
            'font_style': style_dict[style_var.get()],
            'text': text_var.get()
        }
        r.hset(f"user:{user}:text_settings", mapping=settings)

        update_text()

def update_text(event=None):
    user = user_var.get()
    # Очищаем все поля перед обновлением
    font_var.set('')
    size_var.set('')
    color_var.set('')
    style_var.set('')
    text_var.set('')
    formatted_label.config(text='', font=('', 12), fg='black')

    if not user:
        return
    
    if r.exists(f"user:{user}:text_settings"):
        settings = r.hgetall(f"user:{user}:text_settings")
        font_name = settings[b'font_name'].decode('utf-8')
        font_size = int(settings[b'font_size'].decode('utf-8'))
        font_color = settings[b'font_color'].decode('utf-8')
        font_style = settings[b'font_style'].decode('utf-8')
        text = settings[b'text'].decode('utf-8') if b'text' in settings else ''

        # Обновляем поля с новыми значениями из redis
        font_var.set(font_name)
        size_var.set(str(font_size))
        for k, v in color_dict.items():
            if v == font_color:
                color_var.set(k)
                break
        for k, v in style_dict.items():
            if v == font_style:
                style_var.set(k)
                break
        text_var.set(text)

        # Обновление экрана
        formatted_label.config(
            font=(font_name, font_size, font_style),
            fg=font_color,
            text=text
        )

def on_text_change(event=None):
    formatted_label.config(text=text_var.get())

root = tk.Tk()
root.title("Бд-Redis-1")

user_var = tk.StringVar(value=users[0])
font_var = tk.StringVar()
size_var = tk.StringVar()
color_var = tk.StringVar()
style_var = tk.StringVar()
text_var = tk.StringVar()

ttk.Label(root, text="Пользователь").pack()
user_combobox = ttk.Combobox(root, textvariable=user_var, values=users)
user_combobox.pack()
user_combobox.bind("<<ComboboxSelected>>", update_text)

ttk.Label(root, text="Шрифт").pack()
font_option = ttk.Combobox(root, textvariable=font_var, values=font_styles)
font_option.pack()

ttk.Label(root, text="Размер").pack()
size_option = ttk.Combobox(root, textvariable=size_var, values=[str(i) for i in range(12, 20, 2)])
size_option.pack()

ttk.Label(root, text="Цвет").pack()
color_option = ttk.Combobox(root, textvariable=color_var, values=list(color_dict.keys()))
color_option.pack()

ttk.Label(root, text="Начертание").pack()
style_option = ttk.Combobox(root, textvariable=style_var, values=list(style_dict.keys()))
style_option.pack()

ttk.Button(root, text="Сохранить настройки", command=save_settings).pack()

ttk.Label(root, text="Введите текст").pack()    
text_entry = ttk.Entry(root, textvariable=text_var, width=50)
text_entry.pack()
text_entry.bind("<KeyRelease>", on_text_change)

formatted_label = tk.Label(root, text="", wraplength=400, justify=tk.LEFT)
formatted_label.pack(pady=20)

root.mainloop()