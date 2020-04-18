# LoopTicker

A simplistic C++ class for embedded systems to manage tasks on the main loop.

__LoopTicker__ provides a helper to manage asynchronous tasks in a simple way (no complex task scheduler, no hardware interrupts). It supports simple function calls and class methods.

- License: GPLv3
- Updates: https://github.com/Treboada/LoopTicker
- Issues: https://github.com/Treboada/LoopTicker/issues
- Contact: caligari@treboada.net

## Summary

``` C++
#include <LoopTicker.hpp>

// declare forwarding functions here and implement them where you want:
void btn_scan(LoopTicker* loop_ticker);
void LedBlinker::loopUpdate(const void* object_ptr, LoopTicker* loop_ticker);

// put the tasks to execute in this array
static const LoopTicker::Task tasks[] =
{
    Task(btn_scan),             // simple callback function
    Task(&led1, led_blink),     // instance and class method
    Task(&led2, led_blink),     // instance and class method
};
#define LOOP_TASKS_COUNTER (sizeof(tasks)/sizeof(tasks[0]))

// instance a LoopTicker scheduler
static LoopTicker task_ticker(tasks, LOOP_TASKS_COUNTER);

void setup()
{
}

void loop()
{
    // execute the tasks by calling  LoppTicker::doLoop()
    task_ticker.doLoop();
}
```

## Examples

1. [ArduinoBasic](examples/01) 3 Asynchronous tasks scheduled by LoopTicker.
2. [ObjectMethods](examples/02) Usage of object instances instead function callbacks. 

## Simulating the setup-loop pattern

On non-arduino frameworks, you can simulate the setup-loop pattern in this way:

``` C++
#ifndef ARDUINO
int main(void)
{
    setup();
    for (;;) loop();
}
#endif
```

## Roadmap

- C++ templates to avoid static class methods.
- Task sleeping (non-blocking lazy delay).
- Profiling tools.

## Change log

### v1.0.1 

- First release.

### v1.0.2

- Code documentation and README.
- Example with object methods (example 02)

### v1.1.0

- Task constructors.
- No need to declare function parameters if not used.
