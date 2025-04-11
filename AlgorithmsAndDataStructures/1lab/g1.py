def min_distances(n, m, grid):
    distances = [[float('inf')] * m for l in range(n)]
    queue = []

    for i in range(n):
        for j in range(m):
            if grid[i][j] == 1:
                distances[i][j] = 0
                queue.append((i, j))

    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]

    while queue:
        x, y = queue.pop(0)
        for dx, dy in directions:
            nx, ny = x + dx, y + dy
            if 0 <= nx < n and 0 <= ny < m:
                if distances[nx][ny] > distances[x][y] + 1:
                    distances[nx][ny] = distances[x][y] + 1
                    queue.append((nx, ny))
    return distances

n, m = map(int, input().split())
grid = [list(map(int, input().split())) for i in range(n)]

result = min_distances(n, m, grid)

for row in result:
    print(" ".join(map(str, row)))