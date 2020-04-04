/** LoopTicker.hpp
 *
 * LoopTicker class.
 *
 * @version 1.0.0
 * @author Rafa Couto <caligari@treboada.net>
 * @license GNU General Public License v3.0
 * @see https://github.com/Treboada/LoopTicker
 *
 */

#ifndef _LOOP_TICKER_HPP
#define _LOOP_TICKER_HPP

#include <stdint.h>

class LoopTicker
{
    public:

        struct TaskEntryPoint
        {
            void (*function)(void* data, LoopTicker* loop_ticker);
            void* data;
        };

        LoopTicker(TaskEntryPoint task_entry_points[], uint8_t size);

        void doLoop();

        uint32_t getLoopMs32() { return _loopMsLow; }
        uint64_t getLoopMs64() { return ((uint64_t)_loopMsHigh) << 32 | _loopMsLow; }

    private:

        uint32_t _loopMsHigh;
        uint32_t _loopMsLow;

        TaskEntryPoint* _tasks;
        uint8_t _tasksCount;

        void _updateLoopMillis();
};

#endif // _LOOP_TICKER_HPP
