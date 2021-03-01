#ifndef GAMEPAD_H
#define GAMEPAD_H

// C++ Includes
#include <iostream>
#include <string>

// Irrlicht Includes
#include <irrlicht.h>

/** The Mouse Class is a container for the GamePad **/
class GamePad
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default Constructor
        GamePad();
        //! Destructor
        virtual ~GamePad();

    protected:
        //! Copy Constructor
        GamePad(GamePad& other) {}

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
        virtual bool init(irr::SJoystickInfo& gamePadInfo);
        //! Update
        virtual void update();
        //! Release
        virtual void free();
        //! Flush (clear all toggles and buttons down)
        virtual void flush();

    protected:
        //! Process Axes
        virtual void doAxisStates();
        //! Process Button States
        virtual void doButtonStates();

    // ************************
    // * QUERIES AND TRACKING *
    // ************************
    public:
        //! Get the GamePad ID
        virtual unsigned char getID() { return this->ID; }
        //! Get the GamePad name
        virtual const std::string& getName() { return this->name; }
// NOTE: Not cross platform
//        /** Is Point of View Hat (A Windows device will identify the presence or absence or the POV hat. A Linux device cannot, and will always return POV_HAT_UNKNOWN.)
//          * I believe strong that the POV hat will simly come back as an Axis on a linux platform but I can't be sure until I do alot of testing
//        **/
//        virtual bool isPOVHat() { return this->povHat; }

    protected:
        // GamePadID
        unsigned char ID;
        // GamePad Name
        std::string name;
// NOTE: Not cross platform
//        // POV Hat
//        bool povHat;

    public:
        //! Get the number of axes the GamePad has
        virtual unsigned int getAxisCount() { return this->axisCount; }
        //! Get the Axis
        virtual float getAxis(long axisNumber);
        //! Set the Axis
        virtual void setAxis(long axisNumber, float value);
        //!
    protected:
        // Number of axes the GamePad has
        unsigned int axisCount;
        // axis States
        float axisStates[255];
        // axis States Last Frame
        float axisStatesLastFrame[255];
        // axis State Toggles
        bool axisStatesToggles[255];
        // Is GamePad being pushed up? (true only once, while being pushed)
        bool upToggle;
        // Is GamePad being pushed down? (true only once, while being pushed)
        bool downToggle;
        // Is GamePad being pushed left? (true only once, while being pushed)
        bool leftToggle;
        // Is GamePad being pushed right? (true only once, while being pushed)
        bool rightToggle;


    public:
        //! Get the number of buttons the GamePad has
        virtual unsigned int getButtonCount() { return this->buttonCount; }
        //! Is Button down
        virtual bool isButtonPressed(unsigned int button);
        //! Set button state
        virtual void setButtonPressed(unsigned int button, bool state);
        //! Is Button toggled
        virtual bool isButtonToggled(unsigned int button);
        //! Set Button toggled
        virtual void setButtonToggled(unsigned int button, bool state);

    protected:
        // Number of buttons the GamePad has
        unsigned int buttonCount;
        // Button State
        bool buttonStates[255];
        // Button State for last frame
        bool buttonStatesLastFrame[255];
        // Button State for the last frame
        bool buttonToggleStates[255];

    // ****************************************
    // * SPECIAL XBOX360 CONTROLLER FUNCTIONS * // TODO: Manage toggles too
    // ****************************************
    // Axes
    public:
        //! Get the Left Stick XAxis
        virtual float getLeftStickXAxis();
        //! Get the Left Stick YAxis
        virtual float getLeftStickYAxis();
        //! Get the Right Stick XAxis
        virtual float getRightStickXAxis();
        //! Get the Right Stick YAxis
        virtual float getRightStickYAxis();
        // NOTE: DPad is a button on MacOS and Linux and an Axis on Windows
        //! Get the DPadX Axis
        virtual float getDPadXAxis();
        // NOTE: DPad is a button on MacOS and Linux and an Axis on Windows
        //! Get the DPadY Axis
        virtual float getDPadYAxis();
        //! Get the Triggers (in range 0 to 1 for right trigger and range 0 to -1 for left trigger)
        virtual float getTriggers();
        //! Get Left Trigger
        virtual float getLeftTrigger();
        //! Get Right Trigger
        virtual float getRightTrigger();

    // Buttons
    public:
        //! Is A Button Pressed
        virtual bool isAButtonPressed();
        //! Is A Button Toggled
        virtual bool isAButtonToggled();
        //! Is B Button Pressed
        virtual bool isBButtonPressed();
        //! Is B Button Toggled
        virtual bool isBButtonToggled();
        //! Is X Button Pressed
        virtual bool isXButtonPressed();
        //! Is X Button Toggled
        virtual bool isXButtonToggled();
        //! Is Y Button Pressed
        virtual bool isYButtonPressed();
        //! Is Y Button Toggled
        virtual bool isYButtonToggled();
        //! Is LeftBumper Button Pressed
        virtual bool isLeftBumperButtonPressed();
        //! Is LeftBumper Button Toggled
        virtual bool isLeftBumperButtonToggled();
        //! Is RightBumper Button Pressed
        virtual bool isRightBumperButtonPressed();
        //! Is RightBumper Button Toggled
        virtual bool isRightBumperButtonToggled();
        //! Is Back Button Pressed
        virtual bool isBackButtonPressed();
        //! Is Back Button Toggled
        virtual bool isBackButtonToggled();
        //! Is Start Button Pressed
        virtual bool isStartButtonPressed();
        //! Is Start Button Toggled
        virtual bool isStartButtonToggled();
        //! Is LeftStick Button Pressed
        virtual bool isLeftStickButtonPressed();
        //! Is LeftStick Button Toggled
        virtual bool isLeftStickButtonToggled();
        //! Is RightStick Button Pressed
        virtual bool isRightStickButtonPressed();
        //! Is RightStick Button Toggled
        virtual bool isRightStickButtonToggled();
        // NOTE: DPad is a button on MacOS and Linux and an Axis on Windows
        //! Is Up Button Pressed
        virtual bool isDPadUpButtonPressed();
        // NOTE: DPad is a button on MacOS and Linux and an Axis on Windows
        //! Is Up Button Toggled
        virtual bool isDPadUpButtonToggled();
        // NOTE: DPad is a button on MacOS and Linux and an Axis on Windows
        //! Is Down Button Pressed
        virtual bool isDPadDownButtonPressed();
        // NOTE: DPad is a button on MacOS and Linux and an Axis on Windows
        //! Is Down Button Toggled
        virtual bool isDPadDownButtonToggled();
        // NOTE: DPad is a button on MacOS and Linux and an Axis on Windows
        //! Is Left Button Pressed
        virtual bool isDPadLeftButtonPressed();
        // NOTE: DPad is a button on MacOS and Linux and an Axis on Windows
        //! Is Left Button Toggled
        virtual bool isDPadLeftButtonToggled();
        // NOTE: DPad is a button on MacOS and Linux and an Axis on Windows
        //! Is Right Button Pressed
        virtual bool isDPadRightButtonPressed();
        // NOTE: DPad is a button on MacOS and Linux and an Axis on Windows
        //! Is Right Button Toggled
        virtual bool isDPadRightButtonToggled();
        // NOTE: DPad is a button on MacOS and Linux and an Axis on Windows
        //! Is XBox Button Pressed
        virtual bool isXboxButtonPressed();
        //! Is XBox Toggle Button
        virtual bool isXboxButtonToggled();

    protected:
        // Members and methods
};

#endif // GAMEPAD_H
