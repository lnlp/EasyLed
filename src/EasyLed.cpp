/*******************************************************************************  
 * 
 *  File:         EasyLed.cpp
 * 
 *  Description:  Arduino library that makes controlling standard LEDs easy. 
 *                Use simple logical functions like led.on(), led.toggle(), 
 *                led.flash(), led.isOff() and more. Helps to write clean code 
 *                that is easy to read and understand.
 * 
 *  Author:       Leonel Lopes Parente
 * 
 *  Copyright:    Copyright (c) 2019-2021 Leonel Lopes Parente
 *
 *                Permission is hereby granted, free of charge, to anyone 
 *                obtaining a copy of this document and accompanying files to do, 
 *                whatever they want with them without any restriction, including,
 *                but not limited to, copying, modification and redistribution.
 *                The above copyright notice and this permission notice shall be 
 *                included in all copies or substantial portions of the Software.
 * 
 *                The software is provided "as is", without any warranty.
 * 
 *  License:      MIT License. See included LICENSE file.
 * 
 ******************************************************************************/

#include "EasyLed.h"

EasyLed::EasyLed(
    const uint8_t pin,              // GPIO pin to which the LED is connected.
    const ActiveLevel activeLevel,  // The logic level when the LED is on.
    const State initialState,       // Default is off.
    const uint8_t pinmode           // Default is OUTPUT, some Arduino cores also 
)                                   // support OUTPUT_OPEN_DRAIN which can be
{                                   // optionally specified here.
    pin_ = pin;
    activeLevel_ = activeLevel;
    // Initialize state_ to inverse of initialState otherwise 
    // setState(initialState) will not set state. 
    state_ = (initialState == State::Off ? State::On : State::Off); 
    pinMode(pin, pinmode);
    setState(initialState);
}


EasyLed::State EasyLed::getState() const
{
    return state_;
} 


void EasyLed::setState(const State state)
{
    // Only perform actions when state is different from current state_.
    if (state != state_)
    {
        if (state == State::On)
            digitalWrite(pin_, static_cast<uint8_t>(activeLevel_));        // LOW or HIGH
        else
            digitalWrite(pin_, static_cast<uint8_t>(activeLevel_) ^ 1);    // For On use inverse of value for Off.
        state_ = state;
    }
}


uint8_t EasyLed::pin() const
{
    return pin_;
}    


EasyLed::ActiveLevel EasyLed::activeLevel() const
{
    return activeLevel_;
}


void EasyLed::on()
{
    setState(State::On);
}


void EasyLed::off()
{
    setState(State::Off);
}    


bool EasyLed::isOn() const
{
    return (state_ == State::On ? true : false);
}


bool EasyLed::isOff() const
{
    return !isOn();
}


void EasyLed::toggle()
{
    setState(state_ == State::On ? State::Off : State::On);
}


void EasyLed::flash(
    const uint8_t count, 
    const uint16_t onTimeMs, 
    const uint16_t offTimeMs, 
    const uint16_t leadOffTimeMs, 
    const uint16_t trailOffTimeMs)
{
    // Simple flash implementation.
    // Synchronous, caller has to wait for completion.
    // leadOffTimeMs and trailOffTimeMs are only
    // used if LED is currently on.
    
    State savedState = state_;

    if (savedState == EasyLed::State::On)
    {
        setState(State::Off);
        delay(leadOffTimeMs);
    }

    for (uint8_t flash = 0; flash < count; ++flash)
    {
        setState(State::On);
        delay(onTimeMs);

        if (flash < count - 1)
        {
            setState(State::Off);
            delay(offTimeMs);                
        }
    }

    if (savedState == EasyLed::State::On)
    {
        setState(State::Off);
        delay(trailOffTimeMs);
    }
    setState(savedState);
}





