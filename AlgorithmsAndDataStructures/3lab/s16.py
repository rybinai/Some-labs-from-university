def phone_to_words(phone, words):
    digit_to_chars = {
        '1': "ij", '2': "abc", '3': "def",
        '4': "gh", '5': "kl", '6': "mn",
        '7': "prs", '8': "tuv", '9': "wxy",
        '0': "oqz"
    }
 
    word_to_digits = {}
 
    for word in words:
        key = ''.join([str([k for k, v in digit_to_chars.items() if letter in v][0]) for letter in word])
        if key not in word_to_digits:
            word_to_digits[key] = []
        word_to_digits[key].append(word)
 
    n = len(phone)
    dp = [float('inf')] * (n + 1)
    previous = [-1] * (n + 1)
 
    dp[0] = 0
 
    for i in range(1, n + 1):
        for j in range(i):
            potential_word = phone[j:i]
            if potential_word in word_to_digits and dp[j] + 1 < dp[i]:
                dp[i] = dp[j] + 1
                previous[i] = j
 
    if dp[n] == float('inf'):
        return "No solution."
 
    result = []
    current_index = n
    while current_index > 0:
        prev_index = previous[current_index]
        for key in word_to_digits:
            if prev_index == current_index - len(key) and key == phone[prev_index:current_index]:
                result.append(word_to_digits[key][0])
                break
        current_index = prev_index
 
    result.reverse()
    return ' '.join(result)
 
 
def main():
    import sys
 
    input = sys.stdin.read
    data = input().strip().splitlines()
 
    i = 0
    results = []
 
    while i < len(data):
        phone_number = data[i].strip()
        if phone_number == "-1":
            break
 
        i += 1
        word_count = int(data[i].strip())
        i += 1
 
        words = []
        for _ in range(word_count):
            words.append(data[i].strip())
            i += 1
        
        result = phone_to_words(phone_number, words)
        results.append(result)
 
    print('\n'.join(results))
 
 
if __name__ == "__main__":
    main()