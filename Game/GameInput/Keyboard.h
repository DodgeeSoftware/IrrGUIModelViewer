#ifndef KEYBOARD_H
#define KEYBOARD_H

// C++ Includes
#include <iostream>

// Irrlicht Includes
#include <irrlicht.h>

/** The Mouse Class is a container for the keyboard **/
class Keyboard
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default Constructor
        Keyboard()
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
        //! Destructor
        virtual ~Keyboard() {}

    protected:
        //! Copy Constructor
        Keyboard(Keyboard& other) {}

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // No methods or members

    protected:
        // No methods or members

    // *******************
    // * GENERAL METHODS *
    // *******************
    public:
        //! Initialise
        virtual bool init();
        //! Update Keyboard
        virtual void update();
        //! Release
        virtual void free();
        //! Flush (clear all toggles and all keys down)
        virtual void flush();

    public:
        //! Is a key down
        virtual bool isKeyPressed(int key) { return this->keyDown[key]; }
        //! Set a key state
        virtual void setKeyPressed(int key, bool state) { this->keyDown[key] = state; }
        //! Is a key toggled
        virtual bool isKeyToggled(int key) { return this->toggleKeys[key]; }
        //! Is Alt Key Pressed
        virtual bool isAltKeyPressed() { return this->alt; }
        //! Is Alt Key Toggled
        virtual bool isAltKeyToggled() { return this->altToggle; }
        //! Set Alt KeyPressed
        virtual void setAltKeyPressed(bool state) { this->alt = state; }
        //! Is Control KeyPressed
        virtual bool isControlKeyPressed() { return this->control; }
        //! Is Control Key Toggle
        virtual bool isControlKeyToggled() { return this->controlToggle; }
        //! Set Control Key
        virtual void setControlKeyPressed(bool state) { this->control = state; }
        //! Is Shift Key
        virtual bool isShiftKeyPressed() { return this->shift; }
        //! Is Shift Key Toggle
        virtual bool isShiftKeyToggled() { return this->shiftToggle; }
        //! Set Shift Key
        virtual void setShiftKeyPressed(bool state) { this->shift = state; }

    protected:
        // State of alt key
        bool alt;
        // State of shift key last frame
        bool altLastFrame;
        // Toggle Key flag for shift key
        bool altToggle;
        // State of control key
        bool control;
        // State of control key last frame
        bool controlLastFrame;
        // Toggle Key Flag for the control key
        bool controlToggle;
        // State of shift key
        bool shift;
        // State of shift key last frame
        bool shiftLastFrame;
        // Toggle Key flag for shift key
        bool shiftToggle;

    protected:
        // An array representing the states of the keys (true == down, false == up)
        bool keyDown[irr::KEY_KEY_CODES_COUNT];
        // An array representing the states of the keys in the last frame (true == down, false == up)
        bool keyDownLastFrame[irr::KEY_KEY_CODES_COUNT];
        // Key down only for this frame
        bool toggleKeys[irr::KEY_KEY_CODES_COUNT];
};

#endif // KEYBOARD_H
