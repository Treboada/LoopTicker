/** LoopTicker.hpp
 *
 * LoopTicker class.
 *
 * @version 1.0.1
 * @author Rafa Couto <caligari@treboada.net>
 * @license GNU General Public License v3.0
 * @see https://github.com/Treboada/LoopTicker
 *
 */

#ifndef _LOOP_TICKER_HPP
#define _LOOP_TICKER_HPP

#include <stdint.h>

/**
 * @brief Simplistic class to manage tasks on the main loop.
 */
class LoopTicker
{
    public:

        /**
         * @brief Define a task entry-point to manage by LoopTicker.
         */
        struct TaskEntryPoint
        {
            /**
             * @brief Function to be called by the LoopTicker.
             */
            void (*function)(const void* object_ptr, LoopTicker* loop_ticker);

            /**
             * @brief Pointer to object instance when function is a instance method.
             */
            void* object_ptr;
        };

        /**
         * @brief Construct a new Loop Ticker object
         * 
         * @param task_entry_points  Array with the task entry-points to call in the loop.
         * @param size  Length ot the array with the task entry-points.
         */
        LoopTicker(const TaskEntryPoint task_entry_points[], uint8_t size);

        /**
         * @brief Receive the program control to execute the tasks, once in a loop.
         */
        void doLoop();

        /**
         * @brief Get the moment (32 bits resolution) when the loop cycle has started.
         * @return uint32_t Milliseconds from the system boot.
         */
        uint32_t getLoopMs32() { return _loopMsLow; }

        /**
         * @brief Get the moment (64 bits resolution) when the loop cycle has started.
         * @return uint64_t Milliseconds from the system boot.
         */
        uint64_t getLoopMs64() { return ((uint64_t)_loopMsHigh) << 32 | _loopMsLow; }

    private:

        uint32_t _loopMsHigh;
        uint32_t _loopMsLow;

        const TaskEntryPoint* _tasksList;
        uint8_t _tasksCount;

        void _updateLoopMillis();
};

#endif // _LOOP_TICKER_HPP
