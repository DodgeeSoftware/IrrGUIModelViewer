#include "Keyboard.h"

bool Keyboard::init()
{
    // Reset Keys
    this->flush();

    // Success
    return true;
}

void Keyboard::update()
{
    // Handle alt toggle
    this->altToggle = false;
    if (this->alt == true && this->altLastFrame == false)
        this->altToggle = true;
    this->altLastFrame = this->alt;

    // Handle control toggle
    this->controlToggle = false;
    if (this->control == true && this->controlLastFrame == false)
        this->controlToggle = true;
    this->controlLastFrame = this->control;

    // Handle shift toggle
    this->shiftToggle = false;
    if (this->shift == true && this->shiftLastFrame == false)
        this->shiftToggle = true;
    this->shiftLastFrame = this->shift;

    // Go through each key to process toggled keys
    for (int i = 0; i < irr::KEY_KEY_CODES_COUNT; i++)
    {
        // Turn off all the toggle keys
        this->toggleKeys[i] = false;
        // If a key has changed between this and the last frame set the toggle to true
        if (this->keyDown[i] == true && this->keyDownLastFrame[i] == false)
        {
            this->toggleKeys[i] = true;
            /*std::cout << "### key toggled " << i << std::endl;
            std::cout << "### keydown" << this->keyDown[i] << std::endl;
            std::cout << "### lastframekeydown" << this->keyDownLastFrame[i] << std::endl;*/
        }
        // Store a cache of the state of the keyboard for this frame
        this->keyDownLastFrame[i] = this->keyDown[i];
    }
}

void Keyboard::free()
{
    // nothing to free
}

void Keyboard::flush()
{
    for (int i = 0; i < irr::KEY_KEY_CODES_COUNT; i++)
    {
        this->keyDown[i] = false;
        this->keyDownLastFrame[i] = false;
        this->toggleKeys[i] = false;
    }
    this->alt = false;
    this->altLastFrame = false;
    this->altToggle = false;
    this->control = false;
    this->controlLastFrame = false;
    this->controlToggle = false;
    this->shift = false;
    this->shiftLastFrame = false;
    this->shiftToggle = false;
}
