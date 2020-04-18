
#include "LoopTicker.hpp"
#include "LedBlinker.hpp"

// component instances
LedBlinker led1(11, 1000); // pin 11, blink interval is 1 second
LedBlinker led2(12, 2000); // pin 12, blink interval is 2 seconds
LedBlinker led3(13, 4000); // pin 13, blink interval is 4 seconds


// tasks to execute in loop
static LoopTicker::Task tasks[] =
{
    // see LedBlinker class
    LoopTicker::Task(&led1, LedBlinker::loopTickerUpdate),
    LoopTicker::Task(&led2, LedBlinker::loopTickerUpdate),
    LoopTicker::Task(&led3, LedBlinker::loopTickerUpdate),
};
#define LOOP_TASKS_COUNTER (sizeof(tasks)/sizeof(tasks[0]))


// LoopTicker scheduler
static LoopTicker task_ticker(tasks, LOOP_TASKS_COUNTER);


void setup()
{
#   ifdef ARDUINO
    // just for debug
    Serial.begin(9600);
#   endif

    led1.init();
    led2.init();
    led3.init();
}


void loop()
{
    // execute the tasks by calling the loop-ticker methods
    task_ticker.doLoop();
}


// simulate setup-loop on frameworks those are not implementing it
#ifndef ARDUINO
int main(void)
{
    setup();
    for (;;) loop();
}
#endif
