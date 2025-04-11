from collections import defaultdict

def normalize_automaton(state_count, transitions, terminal_states):
    transition_map = defaultdict(dict)
    for start, end, symbol in transitions:
        transition_map[start][symbol] = end
    
    visited = [-1] * (state_count + 1)
    stack = [1]
    visited[1] = 0
    normalized_state_count = 1
    normalized_automaton = []
    
    while stack:
        current_state = stack.pop()
        current_transitions = []
        
        for symbol in sorted(transition_map[current_state].keys()):
            next_state = transition_map[current_state][symbol]
            if visited[next_state] == -1:
                visited[next_state] = normalized_state_count
                normalized_state_count += 1
                stack.append(next_state)
            current_transitions.append((symbol, visited[next_state]))
        normalized_automaton.append((visited[current_state], tuple(sorted(current_transitions))))
    
    normalized_terminal_states = {visited[state] for state in terminal_states}
    return normalized_automaton, normalized_terminal_states

def check_isomorphism(state_count1, transitions1, terminal_states1, state_count2, transitions2, terminal_states2):
    normalized1, terminal_states1_normalized = normalize_automaton(state_count1, transitions1, terminal_states1)
    normalized2, terminal_states2_normalized = normalize_automaton(state_count2, transitions2, terminal_states2)
    return normalized1 == normalized2 and terminal_states1_normalized == terminal_states2_normalized

def main():
    state_count1, transition_count1, _ = map(int, input().split())
    terminal_states1 = list(map(int, input().split()))
    transitions1 = [tuple(input().split()) for _ in range(transition_count1)]
    transitions1 = [(int(start), int(end), symbol) for start, end, symbol in transitions1]
    
    state_count2, transition_count2, _ = map(int, input().split())
    terminal_states2 = list(map(int, input().split()))
    transitions2 = [tuple(input().split()) for _ in range(transition_count2)]
    transitions2 = [(int(start), int(end), symbol) for start, end, symbol in transitions2]
    
    if check_isomorphism(state_count1, transitions1, terminal_states1, state_count2, transitions2, terminal_states2):
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    main()