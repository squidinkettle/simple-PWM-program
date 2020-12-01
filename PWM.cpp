/* ***********************
*PWM implementation
*
************************* */
#include <stdio.h>
#include <cstdint>
#include <iostream>
#include <chrono>
#include <thread>



#include "PWMClass.h"
using namespace std;


//Class initialization
/* *******************************************************************************************************************
*Takes 2 parameters from the user, the duty cycle and thre frequency
*These 2 parameters will calculate the duty cycle and the total period signal
*Then will go and call 'SetTimeOn()' and 'SetTimeOff()' which will calculate how long the signal will be on HIGH and LOW
*
************************************************************************************************************************* */
template<typename T>
PWM<T>::PWM(uint8_t dutyCycle, float frequency){
    dutyCycle=static_cast<int>(dutyCycle);
    
    SetDuty(dutyCycle);
    SetTotalPeriodSignal(frequency);
    SetTimeOn();
    SetTimeOff();
    highCount=GetTimeOn();
    lowCount=GetTimeOff();
    
}

///Duty cycle setters and getters
/* ***********************************************************************************
* 'SetDuty()' divides user's duty input by 255 in order to get the duty cycle
*
***************************************************************************************/
template<typename T>
void PWM<T>::SetDuty(int dutyC){
    dutyC=static_cast<float>(dutyC);
    dutyCycle=dutyC/255.0;
}
template<typename T>
float PWM<T>::GetDuty(){
    return dutyCycle;
}


///Total Period Signal setter and getter
/* **********************************************************************************
* Divides 1.0 by the user's frequency input to get the Total Period Signal
* Then it converts the result to miliseconds
*
**************************************************************************************/
template<typename T>
void PWM<T>::SetTotalPeriodSignal(float frec){

    totalPeriod=1.0/frec;
  
    totalPeriod=totalPeriod*1000;        //convert from seconds to miliseconds
    
}
template<typename T>
float PWM<T>::GetTotalPeriodSignal(){
    return totalPeriod;
}



///Time On & Off setters and getters
/* ****************************************************************************************
* Will help us determine how long each cycle will last in milliseconds
* 'SetTimeOn()' multiplies the TotalPeriodSignal by Duty in order to set the HIGH time
* 'SetTimeOff()' subtracts Total Period Signal by Time On in order set the LOW time
* 
*********************************************************************************************/
template<typename T>
void PWM<T>::SetTimeOn(){
    float d=GetDuty();
    float tps=GetTotalPeriodSignal();

    
    //Time on in MS
    timeOn=tps*d;
    
}

template<typename T>
float PWM<T>::GetTimeOn(){
    return timeOn;
}

template<typename T>
void PWM<T>::SetTimeOff(){
    float timeOn=GetTimeOn();
    float tps=GetTotalPeriodSignal();


    //Time off in MS
    timeOff=tps-timeOn;
    
}

template<typename T>
float PWM<T>::GetTimeOff(){
    return timeOff;
}



///HIGH and LOW flag setters and getters
/********************************************************************
* Will let us know when the cycle is in a state of high/low mode
*
********************************************************************/
template<typename T>
void PWM<T>::SetHigh(bool h){
    HIGH=h;
}
template<typename T>
bool PWM<T>::GetHigh(){
    return HIGH;
    
}
template<typename T>
void PWM<T>::SetLow(bool l){
    LOW=l;
}
template<typename T>
bool PWM<T>::GetLow(){
    return LOW;
}


///Will control the HIGH and LOW flags
/***********************************************************************************************************************
* Will print first HIGH and once the time of that period is over, it will set the HIGH flag to false and LOW to true and vise versa
* Will also call 'Sleep()' to get accurately display how long the cycle will last
* 
**************************************************************************************************************************/
template<typename T>
void PWM<T>::CycleHighLow(){
    auto currentTimeOn=GetTimeOn();
    auto currentTimeOff=GetTimeOff();
    if(currentTimeOn>0){
        SetLow(false);
        SetHigh(true);
        Sleep(currentTimeOn);
        
    }if(currentTimeOff>0){
        SetLow(true);
        SetHigh(false);
        Sleep(currentTimeOff);
    }
    cout<<"|\n\n";
    cout<<"Time On: "<<GetTimeOn()<<"ms\tTime Off: "<<GetTimeOff()<<"ms\nTotal Time: "<<GetTimeOn()+GetTimeOff()<<"ms\n";

    highCount=GetTimeOn();
    lowCount=GetTimeOff();

    
    
}

///Will countdown the time on each HIGH/LOW period
/* *********************************************************************
* Will also call 'DisplayHighAndLow()' to visualize the cycle
*
************************************************************************/
template<typename T>
void PWM<T>::Sleep(float seconds) {

    auto totalTime = GetTimeOn() + GetTimeOff();
    while (totalTime > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        totalTime -= 1;
        DisplayHighAndLow();

    }


}



///Will display when the cycle is going through HIGH and LOW
/**************************************************************************************************
* Also makes sure that it doesn't goes beyond or below the established HIGH LOW times
*
***********************************************************************************************/
template<typename T>
void PWM<T>::DisplayHighAndLow(){
    bool currentHigh=GetHigh();
    bool currentLow=GetLow();
    if(currentHigh && !currentLow && highCount>0){
        cout<<"^";
        highCount-=1.0;
    }
    if(!currentHigh && currentLow && lowCount>0){
        cout<<"_";
       lowCount-=1.0;
    }
    
}



///ISR attachment
/**********************************************
* Allows attaching an ISR to the program
* Provides the necesary flags
* Was usure how ISR exactly worked so it may need further implementation
***********************************************/
template<typename T>
void PWM<T>::AttachISR(void (*ISR)){
    auto HIGH = GetHigh();
    auto LOW = GetLow();
    ISR;
    
    
}


/// Possible class template uses
template class PWM<int>;
template class PWM<uint8_t>;
template class PWM<float>;
template class PWM<string>;
template class PWM<double>;
template class PWM<char>;

