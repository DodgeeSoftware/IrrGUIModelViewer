#include "FrameCounter.h"

void FrameCounter::start()
{
    // start the FPS timer
    this->timer.start();
    // reset the frame counter
    this->frameCounter = 0;
}

void FrameCounter::update()
{
    // has the timer started
    if (this->timer.isStarted() == true && this->timer.isPaused() == false)
    {
        // has 1 second elapsed
        if (this->timer.getTicks() > 1000.0f)
        {
            // update the framesPerSecond
            this->framesPerSecond = this->frameCounter;
            // reset the timer
            this->start();
        }
        else
        {
            // increment the frame counter
            this->frameCounter++;
        }
    }
}

void FrameCounter::pause()
{
    // pause the frame rate counter
    this->timer.pause();
}

void FrameCounter::resume()
{
    // resume the frame rate counter
    this->timer.resume();
}

void FrameCounter::stop()
{
    // stop the FPS timer
    this->timer.stop();
    // reset the frame counter
    this->frameCounter = 0;
}

const char* FrameCounter::getFPSasChar()
{
    std::stringstream ss;
    ss << framesPerSecond;
    return ss.str().c_str();
}
