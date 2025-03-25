using namespace std;
#define Timer1PeriodMilSec 100
void setupTimer1(){
  int OCR1A_Value;
  // = (16*10^6) / (1*1024) (must be <65536) ->'15625' is for ISR interval of 1000ms @16MHz, hence 780-> 100ms for 8Mhz
  OCR1A_Value = (16 * 1000 * Timer1PeriodMilSec) / 1024; // for 16.0 MHz
  //set timer1 interrupt
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register increments
  OCR1A = OCR1A_Value;
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  TCNT1  = 0;//initialize counter value to 0
  TIMSK1 |= (1 << OCIE1A); // enable timer1 compare interrupt
}

void enableTimer1_Int(){
    TCNT1  = 0; //initialize counter value to 0
    TIMSK1 |= (1 << OCIE1A); // enable timer1 compare interrupt
}

void disableTimer1_Int(){
    TIMSK1 &= ~(1 << OCIE1A); // disable timer1 interrupt
}
class Tiks
{
  private:
    int cnt, cntMax;
  
  public:
    Tiks(int tikPeriodMilSec, int timerPeriodMilSec){
      cntMax = tikPeriodMilSec/timerPeriodMilSec;
      cnt = 0;
    }
    boolean execTask(){
      cnt++;
      if(cnt >= cntMax){
        cnt = 0;
        return true;
      }
      else{
        return false;
      }
    }
};
class Buzzer{
  private:
    int onTimeCntMax, onTimeCnt, beepNum, numBeeps;
    boolean isOn;
  public:
    boolean beepingOn;
    Buzzer(int onTimeMilliSec, int _numBeeps, int timerPeriodMilSec){
      onTimeCntMax = onTimeMilliSec/timerPeriodMilSec;
      numBeeps = _numBeeps;
      isOn = false; beepingOn = false;
    }
    void set_OnTimeMilSec_NumBeeps(int onTimeMilliSec, int _numBeeps){
      onTimeCntMax = onTimeMilliSec/Timer1Period;
      numBeeps = _numBeeps;
    }
    void turnOn(){
      isOn = true;
      onTimeCnt = 0;
      digitalWrite(buzzerPin, HIGH);
    }
    void srtBeeping(){
      beepNum = 0;
      beepingOn = true;
    }
    void turnOff_ifReq(){
      if(isOn){ // check for beep duration
        onTimeCnt++;
        if(onTimeCnt>=onTimeCntMax){ // turn off the buzzer & check for numBeeps count
          digitalWrite(buzzerPin, LOW);
          isOn = false;
          if(beepingOn){
            beepNum++;
            if(beepNum >= numBeeps)
              beepingOn = false;
          }         
        }
      }
    }
};

//global variables

Tiks tik_500ms(500, Timer1PeriodMilSec);
Tiks tik_1000ms(1000, Timer1PeriodMilSec);
Buzzer buzzer(400, 90, Timer1PeriodMilSec);

void setup(){
  // setup & start the timer here
  // buzzer.set_OnTimeMilSec_NumBeeps(400, 90);
  // buzzer.turnOn();
  buzzer.srtBeeping(); // max beeps
}

ISR{ // runs after every Timer1Period
  buzzer.turnOff_ifReq();
  
  if(tik_500ms.execTask()){
    
  }
  if(tik_1000ms.execTask()){
    if(buzzer.beepingOn)
      buzzer.turnOn();
  }
  
}

