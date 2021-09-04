#include "EngineMain.h"
#include "Variable.h"
#include "CallBack.h"
#include <avr/eeprom.h>

using namespace OperationArchitecture;
using namespace EmbeddedIOServices;
using namespace Engine;

//TODO: figure out config storage
char _config;

extern "C"
{
  EmbeddedIOServiceCollection _embeddedIOServiceCollection;
  EngineMain *_engineMain;
  Variable *loopTime;
  uint32_t prev;
  
  bool val = true;
  void test() {
      _embeddedIOServiceCollection.DigitalService->WritePin(45, val);
      val = !val;
  }
  Task t = Task(&test);

  void Setup() 
  {
    // TODO HAL implementation
    // _embeddedIOServiceCollection.DigitalService =   new AvrHalDigitalService();
    // _embeddedIOServiceCollection.AnalogService =    new AvrHalAnalogService();
    // _embeddedIOServiceCollection.TimerService =     new AvrHalTimerService(TimerIndex::Index3);
    // _embeddedIOServiceCollection.PwmService =       new AvrHalPwmService();

    _embeddedIOServiceCollection.DigitalService->InitPin(45, Out);
    _embeddedIOServiceCollection.TimerService->ScheduleTask(&t, _embeddedIOServiceCollection.TimerService->GetTick() + _embeddedIOServiceCollection.TimerService->GetTicksPerSecond());

    unsigned int _configSize = 0;
    _engineMain = new EngineMain(reinterpret_cast<void*>(&_config), _configSize, &_embeddedIOServiceCollection);

    _engineMain->Setup();
    loopTime = _engineMain->SystemBus->GetOrCreateVariable(250);
  }
  void Loop() 
  {
    if(!t.Scheduled)
        _embeddedIOServiceCollection.TimerService->ScheduleTask(&t, t.ScheduledTick + _embeddedIOServiceCollection.TimerService->GetTicksPerSecond());

    const tick_t now = _embeddedIOServiceCollection.TimerService->GetTick();
    loopTime->Set((float)(now-prev) / _embeddedIOServiceCollection.TimerService->GetTicksPerSecond());
    prev = now;
    _engineMain->Loop();
  }
}

int main() {
    Setup();
    while(true)
    {
        Loop();
    }
}