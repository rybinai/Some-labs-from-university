def nka_accepts(word, accepting_states, transitions):
    current_states = {1}
    
    for char in word:
        next_states = set()
        
        for state in current_states:
            for (a, b, c) in transitions:
                if a == state and c == char:
                    next_states.add(b)
        current_states = next_states

    if current_states & accepting_states:
        return "Accepts"
    else:
        return "Rejects"

word = input().strip()
n, m, k = map(int, input().split())
accepting_states = set(map(int, input().split()))
transitions = [tuple(input().split()) for _ in range(m)]
transitions = [(int(a), int(b), c) for a, b, c in transitions]

print(nka_accepts(word, accepting_states, transitions))