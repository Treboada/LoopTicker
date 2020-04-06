
#ifndef _LED_BLINKER_HPP
#define _LED_BLINKER_HPP

#ifdef ARDUINO
#   include <Arduino.h>
#endif

#include "LoopTicker.hpp"

class LedBlinker
{
    public:

        // constructor
        LedBlinker(uint8_t led_pin, uint16_t toggle_ms) 
        { 
            _ledPin = led_pin; 
            _toggleMs = toggle_ms;
            _nextUpdate = 0;
        }

        // initialize hardware component
        void init()
        {
#           ifdef ARDUINO
            pinMode(_ledPin, OUTPUT);
#           endif
        }

        // class method to call instance methods at runtime
        static void loopTickerUpdate(const void* object_ptr, LoopTicker* loop_ticker)
        {
            // data reference is used as a pointer to the instance
            LedBlinker* instance = (LedBlinker*) object_ptr;
            instance->_tickerUpdate(loop_ticker);
        }

    private:

        // component properties
        uint8_t _ledPin;
        uint16_t _toggleMs;
        int32_t _nextUpdate;

        // component behaviour
        void _toggle()
        {
#           ifdef ARDUINO
            digitalWrite(_ledPin, !digitalRead(_ledPin));
#           endif
        }

        // instance method executed for each loop cycle
        void _tickerUpdate(LoopTicker* loop_ticker)
        {
            int32_t now = loop_ticker->getLoopMs32();

            // check if it is time to do something
            if (now >= _nextUpdate)
            {
                _toggle();

#               ifdef ARDUINO
                // debug
                Serial.print("led=");
                Serial.print(_ledPin);
                Serial.print(" update=");
                Serial.print(_nextUpdate);
                Serial.print("\n");
#               endif

                // next time to do something
                _nextUpdate = now + _toggleMs;
            }
        }
};

#endif //  _LED_BLINKER_HPP
