from collections import deque

def find_minimum(m, n, graph, matching):
    free_left = []
    left_match = [0] * (m + 1)
    right_match = [0] * (n + 1)

    for i in range(1, m + 1):
        if matching[i - 1] != 0:
            left_match[i] = matching[i - 1]
            right_match[matching[i - 1]] = i
        else:
            free_left.append(i)

    visited_left = [False] * (m + 1)
    visited_right = [False] * (n + 1)
    queue = deque(free_left)

    for u in free_left:
        visited_left[u] = True

    while queue:
        u = queue.popleft()
        for v in graph[u]:
            if not visited_right[v]:
                visited_right[v] = True
                if right_match[v] != 0 and not visited_left[right_match[v]]:
                    visited_left[right_match[v]] = True
                    queue.append(right_match[v])

    left_cover = []
    right_cover = []
    for i in range(1, m + 1):
        if not visited_left[i]:
            left_cover.append(i)
    for i in range(1, n + 1):
        if visited_right[i]:
            right_cover.append(i)

    return left_cover, right_cover

def main():
    import sys
    input = sys.stdin.read
    data = input().splitlines()
    
    m, n = map(int, data[0].split())
    graph = [[] for _ in range(m + 1)]
    for i in range(1, m + 1):
        parts = list(map(int, data[i].split()))
        graph[i] = parts[1:]
    matching = list(map(int, data[m + 1].split()))

    left_cover, right_cover = find_minimum(m, n, graph, matching)

    print(f"{len(left_cover) + len(right_cover)}")
    print(f"{len(left_cover)} {' '.join(map(str, left_cover))}")
    print(f"{len(right_cover)} {' '.join(map(str, right_cover))}")

if __name__ == "__main__":
    main()