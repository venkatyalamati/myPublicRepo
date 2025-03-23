using namespace std;
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

//global variables
#define Timer1Period 100 //in milli sec
Tiks tik_500ms(500);
Tiks tik_1000ms(1000);

void setup(){
  // setup & start the timer here
}
ISR{ // runs once in every Timer1Period
  if(tik_500ms.incTik()){
    
  }
  if(tik_1000ms.incTik()){
    
  }
  
}

