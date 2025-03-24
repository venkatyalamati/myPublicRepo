using namespace std;
#define Timer1Period 100 //in milli sec
class Tiks
{
  private:
    int cnt, cntMax;
    boolean maxReached;
  public:
    Tiks(int cntMax_ms){
      cntMax = cntMax_ms/Timer1Period;
      cnt = 0;
    }
    boolean incTik(){
      cnt++;
      if(cnt >= cntMax){
        cnt = 0;
        maxReached = true;
      }
      else{
        maxReached = false;
      }
      return maxReached;
    }
};
class Buzzer{
  private:
    int onTimeCntMax, onTimeCnt, numBeeps, maxBeeps;
    boolean isOn, beepingOn;
  public:
    Buzzer(){
      isOn = false;
      onTimeCntMax = 600/Timer1Period;
    }
    void checkIfBeepingReq(){
      if(beepingOn)
        turnOn();
    }
    void srtBeeping(int _maxBeeps){
      maxBeeps = _maxBeeps;
      numBeeps = 0;
      beepingOn = true;
    }
    void turnOn(){
      isOn = true;
      onTimeCnt = 0;
      digitalWrite(buzzerPin, HIGH);
    }
    void checkIfTurnOffReq(){
      if(isOn){ // check for beep duration
        onTimeCnt++;
        if(onTimeCnt>=onTimeCntMax){ // turn off the buzzer & check for numBeeps count
          digitalWrite(buzzerPin, LOW);
          isOn = false;
          numBeeps++;
          if(numBeeps>=maxBeeps){
            beepingOn = false;
          }
        }
      }
    }
};

void setupTimer1(){
  int OCR1A_Value;
  // = (16*10^6) / (1*1024) - 1 (must be <65536) ->'15625' is for ISR interval of 1000ms @16MHz, hence 780-> 100ms for 8Mhz
  OCR1A_Value = (16 * 1000 * Timer1Period) / 1024; // for 16.0 MHz
  OCR1A_Value--;
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
//global variables

Tiks tik_500ms(500);
Tiks tik_1000ms(1000);
Buzzer buzzer;

void setup(){
  // setup & start the timer here
  buzzer.srtBeeping(90); // max beeps
}
ISR{ // runs after every Timer1Period
  buzzer.checkIfTurnOffReq();
  
  if(tik_500ms.incTik()){
    
  }
  if(tik_1000ms.incTik()){
    buzzer.checkIfBeepingReq();
  }
  
}

