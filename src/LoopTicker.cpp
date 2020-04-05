/** LoopTicker.cpp
 *
 * LoopTicker class.
 *
 * @version 1.0.1
 * @author Rafa Couto <caligari@treboada.net>
 * @license GNU General Public License v3.0
 * @see https://github.com/Treboada/LoopTicker
 *
 */

#include "LoopTicker.hpp"

#ifdef ARDUINO
#   include <Arduino.h>
#endif


void LoopTicker::_updateLoopMillis()
{
#   ifdef ARDUINO

    uint32_t millis32 = millis();
    if (millis32 < _loopMsLow) _loopMsHigh++;
    _loopMsLow = millis32;

#   else

    // implement here: non-arduino time milliseconds adquisition
#   error "LoopTicker::_updateLoopMillis() not implemented"

#   endif
}


LoopTicker::LoopTicker(const TaskEntryPoint tasks[], uint8_t size)
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
        void* instance = _tasksList[t].object_ptr;
        (_tasksList[t].function)(instance, this);
    }
}

