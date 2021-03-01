#ifndef FRAMECOUNTER_H
#define FRAMECOUNTER_H

// C++ Includes
#include <sstream>

// Timer Includes
#include "Timer.h"

/** The FrameCounter is a simple timing system to track the
    number of frames that pass in certain time periods **/
class FrameCounter
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default Constructor
        FrameCounter()
        {
            this->framesPerSecond = 0;
            this->frameCounter = 0;
        }
        //! Destructor
        virtual ~FrameCounter() {}

    public:
        //! Start the FPSCounter
        void start();
        //! Update the FPSCounter
        void update();
        //! Pause the FPSCounter
        void pause();
        //! Resume the FPSCounter
        void resume();
        //! Stop the FPSCounter
        void stop();
        //! Get the current frames per second
        float getFPS() { return framesPerSecond; }
        //! Get the current frames per second as a string
        const char* getFPSasChar();

    private:
        //! Maintain a local timer
        Timer timer;
        //! Frame rate counter
        float frameCounter;
        //! Frames per second
        float framesPerSecond;
};

#endif // FRAMECOUNTER_H
