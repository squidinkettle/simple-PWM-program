//
//  main.cpp
//  PWM
//
//  Created by Jarl Chabolla on 16/11/20.
//  Copyright © 2020 Jarl Chabolla. All rights reserved.
//

#include <iostream>
#include<sstream>
#include<string>
#include <chrono>
#include <thread>
#include "PWMClass.h"


void UserInterface();
void PrintInstructions();

int main() {


    PrintInstructions();
    UserInterface();
    
    
    
//Allows to exit upon hitting enter
  std::cin.clear();
  std::cout << "\n\n<ENTER> to exit: ";
  std::cin.get();
    
}



///User Interface
/********************************************************
* Prompts user to type down 2 arguments to instantiate a PWM object
* Will ask the user how many cycles should the program iterate
* Will display how long it took it miliseconds to iterate
*
*************************************************************/
void UserInterface(){
    uint8_t duty;
    std::string d;
    int frequency;
    int cycles;
    bool done=false;
    while(!done){
 
    std::cout<<"Set Duty Cycle (number between 0 - 255)\n";
    std::getline (std::cin,d);
    

    
    duty=static_cast<uint8_t>(std::stoi(d));

    std::cout<<"\nSet Frequency\n";
    
    std::getline(std::cin,d);
        
        
    frequency=std::stof(d);
    
    std::cout<<"\nSet Number of cycles\n";

     std::getline(std::cin,d);
    cycles=std::stoi(d);
    
    
    PWM<int> pwmClass(duty,frequency);

	auto start = std::chrono::high_resolution_clock::now();
    for(int x=0;x<cycles;x++)
        pwmClass.CycleHighLow();
    
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed = end - start;
	std::cout << "Time elapsed during "<<cycles<<" cycles: " << elapsed.count() << " ms\n";
        std::cout<<"Press 1 to make another cycle, press 0 to exit"<<std::endl;


      std::getline(std::cin,d);
        if(d=="0"){
            done=true;
            break;
            }
    }
}

void PrintInstructions(){
    
    std::cout<<"=========================\n";
    std::cout<<"=\tPWM Class\t=\n=========================\n\n";
    std::cout<<"This program takes from the user a set Duty Cycle, Frequency and number of cycles the user wishes to see.\n\nThen this program will print out a visual representation of user's input.\n\n '^'=High Pulse\n '_'=Low Pulse\n\n";
    
    
    
}
