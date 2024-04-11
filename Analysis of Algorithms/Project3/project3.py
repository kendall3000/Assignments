
#!/usr/bin/env python3

import os

print(os.listdir())
def can_be_split(dictionary, word):
    n = len(word)
    dp = [False] * (n + 1)
    dp[0] = True

    for i in range(1, n + 1):
        for j in range(i):
            if dp[j] and word[j:i] in dictionary:
                dp[i] = True
                break

    return dp[n]

def main():
    with open("aliceInWonderlandDictionary.txt", "r") as file:
        dictionary = set(line.strip() for line in file)

    with open("input.txt", "r") as file:
        words = [line.strip() for line in file]

    with open("output.txt", "w") as file:
        for word in words:
            if can_be_split(dictionary, word):
                splits = []
                for i in range(1, len(word) + 1):
                    prefix = word[:i]
                    suffix = word[i:]
                    if prefix in dictionary and can_be_split(dictionary, suffix):
                        splits.append(prefix)
                if splits:
                    splits_str = " ".join(splits)
                    file.write(f"{word} can be split into {len(splits)} AiW words: {splits_str}\n")
                else:
                    file.write(f"{word} can be split into 1 AiW word: {word}\n")
            else:
                file.write(f"{word} cannot be split into AiW words.\n")

if __name__ == "__main__":
    main()
