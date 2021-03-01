#include "Timer.h"

irr::ITimer* Timer::pIrrlichtTimer = 0;

void Timer::start()
{
    // If there is no timer then don't do anything
    if (Timer::pIrrlichtTimer == 0)
    {
        return;
    }
    // set the time at which the time started
    this->startTime = pIrrlichtTimer->getTime();
    // set startFlag to true
    this->startFlag = true;
    // set paused status to false
    this->paused = false;
    // set stopped to false
    this->stopped = false;
    // reset the amount of time this time has been caused
    this->totalPausedTime = 0;
    // last time get delta was called
    this->lastTime = 0;
}

void Timer::stop()
{
    // If there is no timer then don't do anything
    if (Timer::pIrrlichtTimer == 0)
        return;
    // set startFlag to false
    this->startFlag = false;
    // set the start time to 0
    this->startTime = 0;
    // set paused status to false
    this->paused = false;
    // set stopped to true
    this->stopped = true;
}

void Timer::reset()
{
    // If there is no timer then don't do anything
    if (Timer::pIrrlichtTimer == 0)
        return;
    // stop the timer
    this->stop();
    // start the timer
    this->start();
}

void Timer::pause()
{
    // If there is no timer then don't do anything
    if (Timer::pIrrlichtTimer == 0)
        return;
    // if the timer is not already paused then pause it
    if (this->paused == false)
    {
        // set paused status to true
        this->paused = true;
        // store the time at which the pause instruction was executed
        this->pausedTime = pIrrlichtTimer->getTime();;
    }
}

void Timer::resume()
{
    // If there is no timer then don't do anything
    if (Timer::pIrrlichtTimer == 0)
        return;
    // if the timer is paused then resume it
    if (this->paused == true)
    {
        // set paused status to false
        this->paused = false;
        // save total time level timer has been paused
        this->totalPausedTime += Timer::pIrrlichtTimer->getTime() - this->pausedTime;
    }
}

double Timer::getTicks()
{
    // If there is no timer then don't do anything
    if (Timer::pIrrlichtTimer == 0)
        return 0.0f;
    // if the timer is paused and has not been stopped
    if (this->paused == true && this->startFlag == true)
    {
        // return the time at which the timer was paused
        return this->pausedTime - this->startTime - this->totalPausedTime;
    }
    // if the timer has been stopped
    if (this->stopped == true)
    {
        // return zero because the timer has been stopped
        return 0;
    }
    // return the total time running minus time paused
    return Timer::pIrrlichtTimer->getTime() - this->startTime - this->totalPausedTime;

}

double Timer::getDelta()
{
    // If there is no timer then don't do anything
    if (Timer::pIrrlichtTimer == 0)
        return 0.0f;
    // get the current time ( relative to this timer )
    unsigned timeNow = this->getTicks();
    // the number of m/secs since last called
    unsigned timeDelta = timeNow - this->lastTime;
    // save the current time
    this->lastTime = timeNow;
    // the amount of time since the last access to this function
    return timeDelta;
}
