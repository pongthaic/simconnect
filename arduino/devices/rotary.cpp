#include "rotary.h"

#define MAX_ROTARY_COUNT 8

RotaryEncoder **_encoders = (RotaryEncoder **)malloc(sizeof(RotaryEncoder) * MAX_ROTARY_COUNT);
volatile int _encodersCount = 0;

void ICACHE_RAM_ATTR _rotaryHandler()
{
    for (int i = 0; i < _encodersCount; i++)
    {
        RotaryEncoder *pEnc = _encoders[i];
        int _newclk = digitalRead(pEnc->clk);

        if (_newclk != pEnc->lastClk)
        {
            digitalRead(pEnc->dt) != _newclk ? pEnc->value-- : pEnc->value++;
            _encoders[i]->lastClk = _newclk;
            _encoders[i]->detents++;
        }
    }
}

RotaryEncoder::RotaryEncoder(int _clk, int _dt)
{
    this->clk = _clk;
    this->dt = _dt;
    this->lastClk = 0;
    this->detents = 0;
    _encoders[_encodersCount] = this;
    _encodersCount++;
}

void RotaryEncoder::setup()
{
    attachInterrupt(this->clk, _rotaryHandler, CHANGE);
}

void RotaryEncoder::loop()
{
    if (this->onValueChanged != NULL && (this->lastValue != this->value))
    {
        this->onValueChanged(this->value, this->lastValue);
        this->lastValue = this->value;
    }
}