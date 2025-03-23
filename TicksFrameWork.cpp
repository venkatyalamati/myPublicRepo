using namespace std;
#define Timer1Period 100 //in milli sec
boolean startBeeping = false;
class Tiks
{
  private:
    int _cnt, _cntMax;
    boolean _maxReached;
  public:
    Tiks(int cntMax_ms){
      _cntMax = cntMax_ms/Timer1Period;
      _cnt = 0;
    }
    boolean incTik(){
      _cnt++;
      if(_cnt >= _cntMax){
        _cnt = 0;
        _maxReached = true;;
      }
      else{
        _maxReached = false;
      }
      return _maxReached;
    }
};
class Buzzer{
  private:
    int onTimeCntMax, onTimeCnt;
    boolean isOn;
  public:
    Buzzer(){
      isOn = false; startBeeping = false;
    }
    void turnOn(int onTime_ms){
      onTimeCntMax = onTime_ms/Timer1Period;
      isOn = true;
      onTimeCnt = 0;
      digitalWrite(buzzerPin, HIGH);
    }
    void check_turnOff(){
      if(isOn){
        onTimeCnt++;
        if(onTimeCnt>=onTimeCntMax){
          digitalWrite(buzzerPin, LOW);
          isOn = false;
        }
      }
    }
};
//global variables

Tiks tik_500ms(500);
Tiks tik_1000ms(1000);
Buzzer buzzer;

void setup(){
  // setup & start the timer here
  startBeeping = true;
}
ISR{ // runs once in every Timer1Period
  buzzer.check_turnOff();
  
  if(tik_500ms.incTik()){
    
  }
  if(tik_1000ms.incTik()){
    if(startBeeping)
      buzzer.turnOn(400);
    
  }
  
}

