def get_pizza_choice():
    while True:
        pizza_choice = input("Would you like to order a cheese pizza, a pepperoni pizza, or a supreme pizza? ").lower()
        if pizza_choice in ["cheese", "pepperoni", "supreme"]:
            return pizza_choice
        else:
            print("You may choose to order a cheese, pepperoni, or supreme pizza only. Please choose again.")

def main():
    name = input("What is your name? ")
    print("Hello " + name + ". Welcome to the Python Pizza chooser.")

    total_pizzas = 0

    while True:
        pizza_choice = get_pizza_choice()
        total_pizzas += 1
        print("Great choice! You ordered a {} pizza.".format(pizza_choice))

        another_pizza = input("Do you want to order another pizza? (yes/no) ").lower()
        if another_pizza != "yes":
            break

    print("Thank you, {}. The {} pizzas you ordered will be ready in 30 minutes.".format(name, total_pizzas))

if __name__ == "__main__":
    main()
