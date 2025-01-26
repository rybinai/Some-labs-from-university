import redis
import tkinter as tk
from tkinter import ttk

r = redis.Redis(host='127.0.0.1', port=6379, db=5)

judges = ['Судья 1', 'Судья 2', 'Судья 3']
athletes = ['Спортсмен 1', 'Спортсмен 2', 'Спортсмен 3']

def update_ranking():
    scores = {}
    for athlete in athletes:
        total_score = 0
        for judge in judges:
            score = r.get(f"{athlete}:{judge}")
            total_score += int(score) if score else 0
        scores[athlete] = total_score
    
    sorted_athletes = sorted(scores.items(), key=lambda item: item[1], reverse=True)

    ranking_list.delete(0, tk.END)
    for athlete, score in sorted_athletes:
        ranking_list.insert(tk.END, f"{athlete}: {score} баллов")

def save_score():
    athlete = athlete_var.get()
    judge = judge_var.get()
    score = int(score_var.get())
    r.set(f"{athlete}:{judge}", score)
    score_label.config(text="Баллы успешно сохранены.", foreground='green')
    update_ranking()

root = tk.Tk()
root.title("Мониторинг спортивных соревнований")
root.geometry("800x420")

style = ttk.Style()
style.configure("TLabel", padding=5)
style.configure("TButton", padding=5)

judge_var = tk.StringVar(value=judges[0])
ttk.Label(root, text="Выберите судью:").pack(pady=(10, 5))
judge_combobox = ttk.Combobox(root, textvariable=judge_var, values=judges)
judge_combobox.pack(pady=(0, 10))

score_var = tk.StringVar(value='1')
ttk.Label(root, text="Выберите баллы (от 1 до 5):").pack(pady=(10, 5))
score_combobox = ttk.Combobox(root, textvariable=score_var, values=['1', '2', '3', '4', '5'], state="readonly")
score_combobox.pack(pady=(0, 10))

athlete_var = tk.StringVar(value=athletes[0])
ttk.Label(root, text="Выберите спортсмена:").pack(pady=(10, 5))
athlete_combobox = ttk.Combobox(root, textvariable=athlete_var, values=athletes)
athlete_combobox.pack(pady=(0, 10))

ttk.Button(root, text="Сохранить баллы", command=save_score).pack(pady=(5, 10))

score_label = ttk.Label(root, text="")
score_label.pack(pady=(0, 10))

frame = ttk.Frame(root)
frame.pack(pady=10)

ranking_list = tk.Listbox(frame, height=10, width=40)
ranking_list.pack()

update_ranking()

root.mainloop()