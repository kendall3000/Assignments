# Corrected code

# Output for the first one:
print("Output for the first one:")
print("-------------------------")

end = 5
increment = 2
for number in range(0, end, increment):
    print(number)
print('outside', number)

# Output for the Second one:
print("\nOutput for the Second one:")
print("----------------------------")
end = 5
increment = 2
for number in range(0, end, increment):
    print("in top", number)
    number += 1
    print('\t after', number)
print('outside', number)

# Output for the Third one:
print("\nOutput for the Third one:")
print("----------------------------")
end = 5
increment = 2
for number in range(0, end, increment):
    print(number)
end = 9
print('outside', number)

# Output for the Fourth one:
print("\nOutput for the Fourth one:")
print("----------------------------")
end = 5
increment = 2
for number in range(0, end, increment):
    print(number)
increment = 3
print('outside', number)