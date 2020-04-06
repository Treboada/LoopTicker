# LoopTicker

A simplistic C++ class for embedded systems to manage tasks on the main loop.

__LoopTicker__ provides a helper to manage asynchronous tasks in a simple way (no complex task scheduler, no hardware interrupts). It supports simple function calls and class methods.

- License: GPLv3
- Updates: https://github.com/Treboada/LoopTicker
- Issues: https://github.com/Treboada/LoopTicker/issues
- Contact: caligari@treboada.net

## Summary

```
#include <LoopTicker.hpp>

// declare forwarding functions here and implement them where you want:
void btn_scan(const void* object_ptr, LoopTicker* loop_ticker);
void LedBlinker::loopUpdate(const void* object_ptr, LoopTicker* loop_ticker);

// put the tasks to execute in this array
#define LOOP_TASKS 3
static const LoopTicker::TaskEntryPoint tasks[LOOP_TASKS] =
{
    { .function = btn_scan,  .object_ptr = nullptr },  // simple function call
    { .function = led_blink, .object_ptr = &led1 },    // class method
    { .function = led_blink, .object_ptr = &led2 },    // class method
};

// instance a LoopTicker scheduler
static LoopTicker task_ticker(tasks, LOOP_TASKS);

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
2. [ObjectMethods](examples/02) Usage of *object_ptr* to refer to object instances.

## Simulating the setup-loop pattern

On non-arduino frameworks, you can simulate the setup-loop pattern in this way:

```
#ifndef ARDUINO
int main(void)
{
    setup();
    for (;;) loop();
}
#endif
```

## Roadmap

- Task sleeping (non-blocking delay)
- Profiling

## Change log

### v1.0.1 

- First release.

### v1.0.2

- Code documentation and README.
- Example with object methods (example 02)


