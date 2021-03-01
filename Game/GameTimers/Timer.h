#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <irrlicht.h>

/** The Timer Class functions just like a stopwatch and is used for things such as framerate limiting and animation timing.
    It has a small workaround in it to compensate for an odd design decision in irrlicht. The cross platform timing interface
    is coupled with an IrrlichtDevice and it becomes very unwieldly to create a timer and pass the device in every single time.
    To use this workaround, straight after creating the irrlicht device, pass a pointer to the timer to this class by using the
    static function setIrrlichtTimer(pIrrlichtDevice->getTimer())**/
class Timer
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default Constructor
        Timer()
        {
            this->startFlag = false;
            this->startTime = 0;
            this->pausedTime = 0;
            this->totalPausedTime = 0;
            this->lastTime = 0;
            this->paused = false;
            this->stopped = false;
        }
        //! GameDestructor
        virtual ~Timer() {}

    protected:
        // members and methods

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        //! must call this function to start the timer
        /** calling start again will reset the timer
        use pause and resume to suspend the timer */
        virtual void start();
        //! stop the timer
        /** must use start() if using same timer again */
        virtual void stop();
        //! reset the timer
        /** stops the timer resetting it, then starts it again*/
        virtual void reset();
        //! pause the timer
        /** tracks how much time passes while paused */
        virtual void pause();
        //! resume the current timer
        /** adjusts game time to not count the paused time */
        virtual void resume();
        //! number of m/secs since start() was executed
        /** \return the number of msecs passed since game start
        or 0 if not started or is paused */
        virtual double getTicks();
        //! tracks how many m/secs have passed since the function was last called.
        /** Useful for general purpose timing.
        When used once only in an update and draw cycle for example.
        \return m/secs passed since getDelta() last called */
        virtual double getDelta();
        //! tracks how many m/secs have passed while paused.
        /** Probably useful only for general stats.
        \return m/secs passed in paused state */
        virtual double getTotalPausedTime();
        //! has timer started */
        /** \return true if timer has started */
        virtual bool isStarted();
        //! has timer paused */
        /** \return true if timer is paused */
        virtual bool isPaused();

    protected:
        // the system time when the timer starts
        double startTime;
        // start flag
        bool startFlag;
        // time at which the pause method was called
        double pausedTime;
        // time passed during a pause
        double totalPausedTime;
        // timer has paused
        bool paused;
        // timer stoped
        bool stopped;
        // the last time the get delta function was called
        double lastTime;

    // *********
    // * TIMER *
    // *********
    public:
        //! This function passes the Irrlicht Device Timer into the Timer Class
        static void setIrrlichtTimer(irr::ITimer* pIrrlichtTimer) { Timer::pIrrlichtTimer = pIrrlichtTimer; }

    protected:
        // A pointer to the Irrlicht Device Timer
        static irr::ITimer* pIrrlichtTimer;
};

inline
bool Timer::isStarted()
{
    // if the startTime is 0 then not started yet
    return startFlag;
}

inline
bool Timer::isPaused()
{
    return paused;
}

inline
double Timer::getTotalPausedTime()
{
    return totalPausedTime;
}

#endif // TIMER_H
