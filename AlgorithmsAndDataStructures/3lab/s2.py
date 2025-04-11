def prefix_function(s):
    n = len(s)
    pi = [0] * n
    for i in range(1, n):
        j = pi[i - 1]
        while j > 0 and s[i] != s[j]:
            j = pi[j - 1]
        if s[i] == s[j]:
            j += 1
        pi[i] = j
    return pi

def find_longest_retrostroke(s):
    n = len(s)
    pi = prefix_function(s)
    
    for k in range(n, 0, -1):
        repeat_count = 0
        j = pi[k - 1]
        while j > 0:
            repeat_count += 1
            j = pi[j - 1]
        
        if repeat_count < pi[k - 1]:
            return s[:k]
    
    return ""

s = input().strip()
print(find_longest_retrostroke(s))