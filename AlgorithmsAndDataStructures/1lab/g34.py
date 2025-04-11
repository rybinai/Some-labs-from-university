from collections import deque
import sys

def find_max_knowledge_rooms(n, m, doors):   
    INF = float('inf')
    knowledge = [-INF] * (n + 1)
    knowledge[1] = 0
    
    for _ in range(n - 1):
        for start, end, knowledge_gain in doors:
            if knowledge[start] > -INF:
                knowledge[end] = max(knowledge[end], knowledge[start] + knowledge_gain)
    
    positive_cycle_rooms = [False] * (n + 1)
    
    for start, end, knowledge_gain in doors:
        if knowledge[start] > -INF and knowledge[start] + knowledge_gain > knowledge[end]:
            positive_cycle_rooms[end] = True
    
    reachable_from_positive_cycles = [False] * (n + 1)
    cycle_queue = deque()
    
    for i in range(1, n + 1):
        if positive_cycle_rooms[i]:
            cycle_queue.append(i)
            reachable_from_positive_cycles[i] = True
    
    while cycle_queue:
        room = cycle_queue.popleft()
        for start, end, knowledge_gain in doors:
            if start == room and not reachable_from_positive_cycles[end]:
                reachable_from_positive_cycles[end] = True
                cycle_queue.append(end)
    
    if reachable_from_positive_cycles[n]:
        return ":)"
    elif knowledge[n] == -INF:
        return ":("
    else:
        return knowledge[n]

if __name__ == "__main__":
    input = sys.stdin.read
    data = input().splitlines()
    
    n, m = map(int, data[0].split())
    
    doors = []
    for i in range(1, m + 1):
        start, end, knowledge_gain = map(int, data[i].split())
        doors.append((start, end, knowledge_gain))
    
    result = find_max_knowledge_rooms(n, m, doors)
    print(result)