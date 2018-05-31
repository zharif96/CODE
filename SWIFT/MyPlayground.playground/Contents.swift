//: Playground - noun: a place where people can play

import UIKit


//variable
var name = "Zharif"     //String
var age = 22            //integer
var condition = true    //boolean
var pi = 3.142          //float

//constant variable
let klccFloor = 88

//multiple assignment
var (age1,age2,age3) = (20,21,22)

//arithmetic operator
var num1 = 8
var num2 = 2
num1 + num2     //addition
num1 - num2     //subtraction
num1 * num2     //multiplication
num1 / num2     //division
num1 % num2     //modulus

//increment
num1 += 1   // == num1 + 1
num1 -= 1   // == num1 - 1

//escape character
var sent = "My name is \"Zharif\""      // use \ for escape character

//conditional operator
num1 > num2
num1 < num2
num1 == num2
num1 != num2

//conditional statement
if age == 17 {
    print("You are allowed to take SPM")
}
else if age > 20 && age == 22{
    print ("You can vote")
}
else{
    print("You are young and dumb ")
}


//ARRAY
var toDoList = ["tidur","makan","study"]    //initialize array
toDoList[2]                                 //select value at array 2
toDoList.append("solat")                    //add value to array
toDoList.count                              //count total number of value in array
toDoList.first                              //select first value in array
toDoList.last                               //select last value in array
toDoList.remove(at:1)                       //remove value at array 1
print(toDoList)
toDoList.removeAll()                        //remove all values in array
print(toDoList)

var newArr = [Int]()                        //initiate empty array
newArr.append(1)                            //add value to array
newArr.append(2)
print(newArr)
newArr[0] = 3                               //update value at array 0 to 3
print(newArr)


//DICTIONARY
var myDict = ["red":"marah","blue":"sedih"]     //dictionary initialisation
myDict["red"]                                   //select "red" key
myDict["yellow"] = "gembira"                    //add key to dictionary
myDict["red"] = "angry"                         //change value of key
myDict.removeValue(forKey: "yellow")            //remove value for key "yellow"
myDict.count                                    //count number of key in dictionary





















