/**
 * @file ArduinoBasic.cpp
 * @author Rafa Couto (caligari@treboada.net)
 * @brief 3 Asynchronous tasks scheduled by LoopTicker
 * @version 0.2
 *
 */

#include <Arduino.h>
#include <LoopTicker.hpp>

#define BTN_PIN 3
#define LED1_PIN 13
#define LED2_PIN 12


// forward declaration for your tasks (implemented below)
void btn_scan(LoopTicker* loop_ticker);
void led1_blink(LoopTicker* loop_ticker);
void led2_blink(LoopTicker* loop_ticker);


// tasks to execute in loop
static const LoopTicker::Task tasks[] =
{
    LoopTicker::Task(btn_scan),
    LoopTicker::Task(led1_blink),
    LoopTicker::Task(led2_blink),
};
#define LOOP_TASKS_COUNTER (sizeof(tasks)/sizeof(tasks[0]))


// LoopTicker scheduler
static LoopTicker task_ticker(tasks, LOOP_TASKS_COUNTER);


void setup()
{
    pinMode(BTN_PIN, INPUT_PULLUP);
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
}


void loop()
{
    // execute the tasks by calling the loop-ticker methods
    task_ticker.doLoop();
}


static bool btn_status = false;

void btn_scan(LoopTicker* loop_ticker)
{
    // time to do something?
    static int32_t _next_scan = 0;
    int32_t now = loop_ticker->getLoopMs32();
    if (now >= _next_scan)
    {
        // task load: it must be as short as possible
        if (btn_status ^ !digitalRead(BTN_PIN))
        {
            // update button status
            btn_status = !btn_status;
        }

        // next scan in 20 milliseconds (soft debouncing)
        _next_scan = now + 20;
    }
}


void led1_blink(LoopTicker* loop_ticker)
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


void led2_blink(LoopTicker* loop_ticker)
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
