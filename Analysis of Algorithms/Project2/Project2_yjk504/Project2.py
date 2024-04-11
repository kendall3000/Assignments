#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Apr 20 17:35:57 2023

@author: kendallramos
"""

import pandas as pd 
#import numpy as np
import matplotlib.pyplot as plt 
df = pd.read_csv("/Users/kendallramos/Python/Project2/section1-students.csv")
choice = 0 
while(choice!=5):
    print("UTSA – CS1063 – Section 1 - Project 2 - written by Kendall Ramos")
    print("Main menu: ")
    print ('1.Exam Scores')
    print ('2.Graphs')
    print('3.Class Graph')
    print('4.Output Grades File')
    print('5.Exit program')
    print("Select an option: ", end= "")
    choice=int(input())
    print()
    if choice==1:
        subchoice=0 
        while(subchoice!=5):
            print("Individual Student Exam Menu: ")
            print('1.List All')
            print ('2.Average')
            print('3.Low Score')
            print("4.High Score")
            print('5.Exit program')
            print('Select an option from the menu: ', end='')
            subchoice=int(input())
            print()
            print("Enter the abc123 of Student: ", end="")
            s=input()
            print()
            
            if subchoice==1:
                mark=0
                for i in range(len(df)):
                    print(df.abc123[i],s)
                    if df.abc123[i]==s:
                        mark=1
                        list_exams = (df.exam1[i],df.exam2[i], df.exam3[i])
                        print ("Exam Scores:",list_exams )
                if mark==0:
                    print("Not Found: provided student id")
            elif subchoice==2:
                mark=0
                for i in range(len(df)):
                    if df.abc123[i]==s:
                        mark=1
                        cal_ave = (df.exam1[i]+df.exam2[i]+df.exam3[1])/3
                        print("Student Average:", cal_ave)
                if mark==0:
                    print("Not Found: provided student id")
            elif subchoice==3:
                mark=0
                for i in range(len (df)):
                    if df.abc123[i]==s:
                        mark=1
                        cal_low = min(df.exam1[i],df.exam2[i],df.exam3[i])
                        print("Low Score:", cal_low)
                if mark==0:
                    print ("Not Found: provided student id")
            elif subchoice==4:
                mark=0
                for i in range(len (df)):
                    if df.abc123[i]==s:
                        mark=1 
                        cal_high = max (df.exam1[i], df.exam2[i], df.exam3[i])
                        print("High Score:", cal_high)
                if mark==0:
                    print("Not Found: provided student id")
            elif subchoice==5:
                break 
            else:
                print("Invalid Input")
                
    elif choice==2:
        print("Enter the abc123 of Student")
        s=input()
        mark=0
        for i in range(len(df)):
            if df.abc123[i]==s:
                mark=1
                x = ['exam_1_score', 'exam 2 score', 'exam_3_score']
                y=[df.exam1[i],df.exam2[i],df.exam3[i]]
                plt.plot(x, y) 
                plt.show()
        if mark==0:
            print("Not Found: provided_student_id")
    elif choice==3:
        continue
    elif choice==4:
        for i in range(len(df)) :
            results = open("SectioniResults.txt", "W")
            s=df.lastname[i]+","+df.firstname[i]+","+str(cal_ave)
            results.write(5)
    elif choice==5:
        break
    else:
        print("Value is out of range, Please resubmit: ")
        print()

        
        
        