from collections import defaultdict, deque

MOD = 10**9 + 7

def bfs_reachable(start_nodes, graph, n):
    reachable_states = [False] * (n + 1)
    queue = deque(start_nodes)
    for node in start_nodes:
        reachable_states[node] = True

    while queue:
        current_node = queue.popleft()
        for neighbor in graph[current_node]:
            if not reachable_states[neighbor]:
                reachable_states[neighbor] = True
                queue.append(neighbor)
    return reachable_states

def has_cycle(graph, reachable_states, n):
    in_degree = [0] * (n + 1)
    for state in range(1, n + 1):
        if not reachable_states[state]:
            continue
        for neighbor in graph[state]:
            if reachable_states[neighbor]:
                in_degree[neighbor] += 1

    queue = deque([state for state in range(1, n + 1) if reachable_states[state] and in_degree[state] == 0])
    visited_count = 0

    while queue:
        current_node = queue.popleft()
        visited_count += 1
        for neighbor in graph[current_node]:
            if reachable_states[neighbor]:
                in_degree[neighbor] -= 1
                if in_degree[neighbor] == 0:
                    queue.append(neighbor)

    reachable_count = sum(reachable_states)
    return visited_count < reachable_count

def count_paths(graph, start_state, accept_states, reachable_states, n):
    dp = [0] * (n + 1)
    dp[start_state] = 1

    order = []
    in_degree = [0] * (n + 1)
    for state in range(1, n + 1):
        if not reachable_states[state]:
            continue
        for neighbor in graph[state]:
            if reachable_states[neighbor]:
                in_degree[neighbor] += 1

    queue = deque([state for state in range(1, n + 1) if reachable_states[state] and in_degree[state] == 0])
    while queue:
        current_node = queue.popleft()
        order.append(current_node)
        for neighbor in graph[current_node]:
            if reachable_states[neighbor]:
                in_degree[neighbor] -= 1
                if in_degree[neighbor] == 0:
                    queue.append(neighbor)

    for node in order:
        for neighbor in graph[node]:
            if reachable_states[neighbor]:
                dp[neighbor] += dp[node]
                dp[neighbor] %= MOD

    return sum(dp[state] for state in range(1, n + 1) if accept_states[state]) % MOD

def main():
    n, m, k = map(int, input().split())
    accept_states = [False] * (n + 1)
    if k > 0:
        for state in map(int, input().split()):
            accept_states[state] = True

    graph = defaultdict(list)
    reverse_graph = defaultdict(list)
    for _ in range(m):
        a, b, c = input().split()
        a, b = int(a), int(b)
        graph[a].append(b)
        reverse_graph[b].append(a)

    reachable_from_start = bfs_reachable([1], graph, n)
    reachable_to_accept = bfs_reachable([u for u in range(1, n + 1) if accept_states[u]], reverse_graph, n)

    reachable_states = [reachable_from_start[i] and reachable_to_accept[i] for i in range(n + 1)]

    if not reachable_states[1]:
        print(0)
        return

    if has_cycle(graph, reachable_states, n):
        print(-1)
        return
    
    result = count_paths(graph, 1, accept_states, reachable_states, n)
    print(result)  

if __name__ == "__main__":
    main()