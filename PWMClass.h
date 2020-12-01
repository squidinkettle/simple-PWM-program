/* **********************
*PWM Header
*
*********************** */

#ifndef PWM_h
#define PWM_h
#include<cstdint>
#include<ctime>

template<typename T>
class PWM{
private:
    uint8_t duty;
    float dutyCycle;
    float totalPeriod;
    
    float timeOn;
    float timeOff;
    bool HIGH;
    bool LOW;
    float lowCount;
    float highCount;
  
    
public:
   
    PWM(uint8_t, float);
    
    
    
    void SetDuty(int);
    float GetDuty();
    
    void SetTotalPeriodSignal(float);
    float GetTotalPeriodSignal();
    
    void SetTimeOn();
    float GetTimeOn();
    
    void SetTimeOff();
    float GetTimeOff();
    
    void SetHigh(bool);
    bool GetHigh();
    void SetLow(bool);
    bool GetLow();
    
    void ISR();
    void Sleep(float);
    
    void CycleHighLow();
    
    void DisplayHighAndLow();
    
    void AttachISR(void *);
    
    
    
};



#endif /* PWM_h */
