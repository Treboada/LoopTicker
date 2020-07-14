/** LoopTicker.cpp
 *
 * LoopTicker class.
 *
 * @version 1.1.0
 * @author Rafa Couto <caligari@treboada.net>
 * @license GNU General Public License v3.0
 * @see https://github.com/Treboada/LoopTicker
 *
 */

#include "LoopTicker.hpp"

#ifdef ARDUINO
#   include <Arduino.h>
#elif defined(linux)
#   include <sys/time.h>
#endif


void LoopTicker::_updateLoopMillis()
{
    uint32_t millis32 = 0;

#   ifdef ARDUINO

    millis32 = millis();

#   elif defined(linux)

    timeval tv;
    gettimeofday(&tv, 0);
    millis32 = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);

#   else

    // implement here: non-arduino time milliseconds adquisition
#   error "LoopTicker::_updateLoopMillis() not implemented"

#   endif

    // manage 32 bits overflow
    if (millis32 < _loopMsLow) _loopMsHigh++;
    _loopMsLow = millis32;
}


LoopTicker::LoopTicker(const Task tasks[], uint8_t size)
{
    _tasksList = tasks;
    _tasksCount = size;
    _loopMsLow = 0;
    _loopMsHigh = 0;
}


void LoopTicker::doLoop()
{
    // time at loop beginning
    _updateLoopMillis();

    // execute each task entrypoint
    for (uint8_t t = 0; t < _tasksCount; t++)
    {
        const void* instance = _tasksList[t].object_ptr;
        if (instance == nullptr)
        {
            Task::callback cb = (Task::callback)(_tasksList[t].function_ptr);
            cb(this);
        }
        else
        {
            Task::handler hl = (Task::handler)(_tasksList[t].function_ptr);
            hl(instance, this);
        }

    }
}

