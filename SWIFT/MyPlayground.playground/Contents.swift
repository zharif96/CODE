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

//FOR LOOP
var shoppingList = ["oranges","apples","banana"]
var legend = ["blue":"ocean","green":"land","red":"hell"]

for num in 1...10{                              //for loop for number
print(num)
}
for num in stride(from: 0 , to: 10, by: 2){     //for loop with increment/decrement
print(num)
}
for item in shoppingList {                      //for loop for array
print(item)
}
for item in legend {                            //for loop for dict
print(item.key)                                 //print key only
print(item.value)                               //print value only
}
for (index,value) in shoppingList.enumerated() {      //enum function, use index of array/dict
print(index)
print(value)
}

//WHILE LOOP & DO WHILE LOOP
var counter = 0
while counter < 10{         //while loop
    print(counter)          //print 1 to 9
    counter += 1
}

repeat{                     //do while loop
    print(counter)          //print 10
    counter += 1
} while counter < 10


//SWITCH STATEMENT
switch age{
    case 15:
        print("Take PMR")
    case 17:
        print("Take SPM")
    default:
        print("You are too old")
}

for i in 1...5{
    if i == 3 {
        continue            //if continue, it skip to the next iteration. whatever code underneat it will not run
    }
    print(i)
}

//FUNCTION
func addition(num1: Int, num2: Int){            //void function
    print(num1 + num2)
}
addition(num1: 5, num2: 6)

func multiply(num1: Int, num2: Int) -> Int {    //return function
    return num1 * num2
}
var result = multiply(num1: 3, num2: 5)
print(result)


//STRUCT
struct userLocation{                                                            //struct initialisation
    var name : String
    var longitude : Double
    var latitude : Double
}
func getLocation(loc:userLocation){                                             //function with struct as parameter
    print(loc.name)
}

var myLoc = userLocation(name: "Zharif", longitude: 22.04, latitude: 28.03)     //assign struct to a struct variable named 'myLoc'

getLocation(loc: myLoc)                                                         //call the function


//ENUMERATION
enum direction:String {             //Enum initialisation
    case North = "Go forward"       //member of enum
    case South = "Go back"          //"Go back" is called raw value
    case East = "Go right"
    case West = "Go left"
}

var dir = direction.West            //assign member of enum to a variable
print(dir.rawValue)                 //print the raw value associated with dir = direction.West

enum day{                           //without raw value
    case Mon
    case Tue
    case Sat
    case Sun
}

var today = day.Mon
    switch today{
    case .Mon:
        print("Today is Monday")
    case .Tue:
        print("Today is Tuesday")
    case .Sat:
        print("Today is Saturday")
    case .Sun:
        print("Today is Sunday")
}


//Classes
class Person {                                                                  //class initialisation
    var name : String                                                           //class attributes
    var age : Int
    
    init(name: String, age: Int) {                                              //constructor
        self.name = name
        self.age = age
    }
    
    func greeting(){                                                            //class method
        print("Hi. My name is \(self.name) and I am \(self.age) years old")
    }
}

var person1 = Person(name: "Zharif", age: 22)                                   //object initialisation
person1.greeting()


//Inheritance and Override
class Parent{
    func parentMethod() {
        print("This is parent method")
    }
    
    func getName(){
    print("I am a parent")
    }
}

class Child: Parent {                       //Child class inherit parent class
    func childMethod(){
        print("This is child method")
    }
    
     override func getName() {               //method named 'getName' already exist in parent. To change it, we need to override the method
        print("I am a child")
    }
}

var parent = Parent()
parent.parentMethod()

var child = Child()
child.childMethod()
child.parentMethod()                        //child class can access method in parent class because it inherit the parent
child.getName()


















