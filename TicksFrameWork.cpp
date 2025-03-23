using namespace std;
class Tiks
{
  private:
    int _cnt, _cntMax;
  public:
    Tiks(int cntMax){
      _cntMax = cntMax;
      _cnt = 0;
    }
    void incTik(){
      _cnt++;
      if(_cnt > _cntMax){
        _cnt = 0;
        taskTik();
      }
    }
};
