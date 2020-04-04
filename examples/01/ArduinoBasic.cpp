
#include <Arduino.h>

#include <LoopTicker.hpp>


// forward declaration for your tasks (implemented below)
void my_task_1(void* data, LoopTicker* loop_ticker);
void my_task_2(void* data, LoopTicker* loop_ticker);
void my_task_3(void* data, LoopTicker* loop_ticker);


// tasks to execute in loop
#define LOOP_TASKS 3
static LoopTicker::TaskEntryPoint tasks[LOOP_TASKS] =
{
    // function (loop-ticker method) and data (pointer passed as function param)
    { function: my_task_1, data: "in task 1" },
    { function: my_task_2, data: "in task 2" },
    { function: my_task_3, data: "in task 3" },
};


// LoopTicker scheduler
static LoopTicker task_ticker(tasks, LOOP_TASKS);


void setup()
{
    Serial.begin(9600);
}


void loop()
{
    // execute the tasks by calling the loop-ticker methods
    task_ticker.doLoop();
}


void print_msg(const char* msg, uint32_t now)
{
        Serial.print(msg);
        Serial.print(" - ");
        Serial.println(now);
}


void my_task_1(void* data, LoopTicker* loop_ticker)
{
    // important: this variable must be static
    static int32_t _task_1_next_update = 0;

    // time to do something?
    int32_t now = loop_ticker->getLoopMs32();
    if (now >= _task_1_next_update)
    {
        // data is a pointer to any structure containing state
        const char* msg = (const char*) data;

        // task load: it must be as short as possible
        print_msg(msg, now);

        // next time to do something (in 1 second)
        _task_1_next_update = now + 1000;
    }
}


void my_task_2(void* data, LoopTicker* loop_ticker)
{
    static int32_t _task_2_next_update = 0;
    int32_t now = loop_ticker->getLoopMs32();
    if (now >= _task_2_next_update)
    {
        const char* msg = (const char*) data;
        print_msg(msg, now);
        _task_2_next_update = now + 2000;
    }
}


void my_task_3(void* data, LoopTicker* loop_ticker)
{
    static int32_t _task_3_next_update = 0;
    int32_t now = loop_ticker->getLoopMs32();
    if (now >= _task_3_next_update)
    {
        const char* msg = (const char*) data;
        print_msg(msg, now);
        _task_3_next_update = now + 3000;
    }
}


