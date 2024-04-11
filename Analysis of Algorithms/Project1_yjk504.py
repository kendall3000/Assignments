#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Mar  5 18:44:37 2023

@author: kendallramos
"""

print('UTSA – Semester Year - CS1063 – Section 001 - Project 1 - written by Kendall Ramos')

#Section 1
#get the class size making sure it isnt larger than 10
cSize = 0;
print('Please, enter the class size:', end=' ')
cSize = int(input())
while cSize >= 10:
    print('Error class must be no larger than 10. Please, enter the class size:', end=' ')
    cSize = int(input())
   
#gets the students information
i = 0
stuNum = 1;
cName = [0 for i in range(cSize)]
cGrade = [0 for i in range(cSize)]
for stuNum in range(cSize):
    print('Please, enter the student name:', end=' ')
    cName[i] = str(input())
    print('Please, enter the students grade:', end=' ')
    cGrade[i] = int(input())
    while cGrade[i] > 100:
        print('Error the grade must be between 0-100. Please, enter the students grade:', end=' ')
        cGrade[i] = int(input())
    print()
    stuNum += 1
    i +=1
    
#Section 2
print()
print("Do you wish to continue(Y/N)? ", end='')
cont= str(input())
print()
while cont != 'Y' and cont != 'N' and cont != 'y' and cont != 'y':
    print("Please try again, must select either Y or N. Do you wish to continue(Y/N)? ", end='')
    cont= str(input())
    print()
    
while cont == 'Y' or cont == 'y':
    print('Main Menu')
    print('1. List Student Grade')
    print('2. Report of Grades')
    print('3. Modify a Grade')
    print('4. Exit Program')
    print('Select an Option:', end=' ')
    choice = int(input())
    
    while choice > 4 and choice < 1:
        print('Error not an option')
        print('Main Menu')
        print('1. List Student Grades')
        print('2. Report of Grades')
        print('3. Modify a Grade')
        print('4. Exit Program')
        print('Select an Option:', end=' ')
        choice = int(input())
    print()
    
    #Display a list of the students grades
    i = 0
    stuNum = 0
    if choice == 1:
        for stuNum in range(cSize):
            #print(f'{cName[i]}',end='')
            print(f'{cName[i]}', end='')
            print("'s exam grade is", f'{cGrade[i]}')
            print()
            i +=1
    
    #reporting the number of letter grades in system
    i = 0
    stuNum = 0
    a = 0
    b = 0
    c = 0
    d = 0
    f = 0
    if choice == 2:
        for stuNum in range(cSize):
            if cGrade[i] < 60:
                f += 1
            if cGrade[i] < 70 and cGrade[i] >=60:
                d += 1
            if cGrade[i] < 80 and cGrade[i] >= 70:
                c += 1
            if cGrade[i] < 90 and cGrade[i] >= 80:
                b += 1
            if cGrade[i] <= 100 and cGrade[i] >= 90:
                a += 1
            i += 1
        
        print("A:", f'{a}')
        print("B:", f'{b}')
        print("C:", f'{c}')
        print("D:", f'{d}')
        print("F:", f'{f}')
  
    
    if choice == 3:
        i = 0
        k = 0
        print('Please provide the name of the student: ', end='')
        tempName = str(input())
        while k != -1:
            for i in range(cSize):
                if tempName == cName[i]:
                    print('Please provide the new exam grade: ', end='')
                    cGrade[i] = int(input())
                    print(f'{cName[i]}', end='')
                    print("'s new exam grade is", f'{cGrade[i]}')
                    print()
                    k = -1
                i += 1
            if k != -1:
                print("Invalid Name, do you wish to continue(Y/N)? ", end='')
                cont1= str(input())
                print()
                while cont1 != 'Y' and cont1 != 'N'and cont1 != 'y' and cont1 != 'y':
                    print("Please try again, must select either Y or N. Do you wish to continue(Y/N)? ", end='')
                    cont= str(input())
                    print()
                if cont1 == 'Y' or cont1 == 'y':
                    print('Please resubmit the name of the student: ', end='')
                    tempName = str(input())
                    i = 0
                if cont1 == 'N' or cont1 == 'n':
                    break
                    

    #Exits the program
    if choice == 4:
        print('Thank you. This program is brought to you by Python Expert: Kendall Ramos.')
        exit()
    
    print("Do you wish to continue(Y/N)? ", end='')
    cont= str(input())
    print()
    while cont != 'Y' and cont != 'N' and cont != 'y' and cont != 'y':
        print("Please try again, must select either Y or N. Do you wish to continue(Y/N)? ", end='')
        cont= str(input())
        print()
    
if cont == 'N' or cont =='n':
    print('Thank you. This program is brought to you by Python Expert: Kendall Ramos.')
    