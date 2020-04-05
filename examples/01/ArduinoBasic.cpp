/**
 * @file ArduinoBasic.cpp
 * @author Rafa Couto (caligari@treboada.net)
 * @brief 3 Asynchronous tasks scheduled by LoopTicker
 * @version 0.1
 * @date 2020-04-05
 * 
 */

#include <Arduino.h>
#include <LoopTicker.hpp>

#define BTN_PIN 3
#define LED1_PIN 13
#define LED2_PIN 12


// forward declaration for your tasks (implemented below)
void btn_scan(const void* object_ptr, LoopTicker* loop_ticker);
void led1_blink(const void* object_ptr, LoopTicker* loop_ticker);
void led2_blink(const void* object_ptr, LoopTicker* loop_ticker);


// tasks to execute in loop
#define LOOP_TASKS 3
static const LoopTicker::TaskEntryPoint tasks[LOOP_TASKS] =
{
    { function: btn_scan, object_ptr: nullptr },
    { function: led1_blink, object_ptr: nullptr },
    { function: led2_blink, object_ptr: nullptr },
};


// LoopTicker scheduler
static LoopTicker task_ticker(tasks, LOOP_TASKS);


void setup()
{
    pinMode(BTN_PIN, INPUT_PULLUP);
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
    
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);
}


void loop()
{
    // execute the tasks by calling the loop-ticker methods
    task_ticker.doLoop();
}


static bool btn_status = false;

void btn_scan(const void* object_ptr, LoopTicker* loop_ticker)
{
    // time to do something?
    static int32_t _next_scan = 0;
    int32_t now = loop_ticker->getLoopMs32();
    if (now >= _next_scan)
    {
        // task load: it must be as short as possible
        if (btn_status ^ !digitalRead(BTN_PIN)) 
        {
            btn_status = !btn_status;
        }

        // next scan in 20 milliseconds (soft debouncing)
        _next_scan = now + 20;
    }
}


void led1_blink(const void* object_ptr, LoopTicker* loop_ticker)
{
    static uint32_t _next_toggle = 0;
    uint32_t now = loop_ticker->getLoopMs32();
    if (now >= _next_toggle)
    {
        // blink while button is not pressed
        if (!btn_status) 
        {
            digitalWrite(LED1_PIN, !digitalRead(LED1_PIN));
        }

        // 5 Hz
        _next_toggle = now + 200;
    }
}


void led2_blink(const void* object_ptr, LoopTicker* loop_ticker)
{
    static uint32_t _next_toggle = 0;
    uint32_t now = loop_ticker->getLoopMs32();
    if (now >= _next_toggle)
    {
        // blink always
        digitalWrite(LED2_PIN, !digitalRead(LED2_PIN));

        // 1 Hz
        _next_toggle = now + 1000;
    }
}
