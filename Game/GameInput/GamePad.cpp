#include "GamePad.h"

GamePad::GamePad()
{
    // ID
    this->ID = 0;
    // Name
    this->name.clear();
    // Axes
    this->axisCount = 255;
    for (long i = 0; i < this->axisCount; i++)
    {
        this->axisStates[i] = 0.0f;
        this->axisStatesLastFrame[i] = 0.0f;
        this->axisStatesToggles[i] = false;
    }
    // Directional Toggles
    this->upToggle = false;
    this->downToggle = false;
    this->leftToggle = false;
    this->rightToggle = false;
    // Buttons
    this->buttonCount = 255;
    for (unsigned int i = 0; i < this->buttonCount; i++)
    {
        this->buttonStates[i] = false;
        this->buttonStatesLastFrame[i] = false;
        this->buttonToggleStates[i] = false;
    }
// NOTE: Not Cross Platform
//    // POV Hat
//    this->povHat = false;
}

GamePad::~GamePad()
{

}

bool GamePad::init(irr::SJoystickInfo& gamePadInfo)
{
    // ********
    // * INIT *
    // ********

    this->ID = gamePadInfo.Joystick;
    this->name = gamePadInfo.Name.c_str();
    //this->axisCount = gamePadInfo.Axes;
    //this->buttonCount = gamePadInfo.Buttons;
    // NOTE: Not Cross Platform
    //this->povHat = (gamePadInfo.PovHat == irr::SJoystickInfo::POV_HAT_PRESENT) ? true : false;
    for (unsigned int i = 0; i < this->buttonCount; i++)
    {
        this->buttonStates[i] = false;
        this->buttonStatesLastFrame[i] = false;
        this->buttonToggleStates[i] = false;
    }

    // Success
    return true;
}

void GamePad::update()
{
    // **********
    // * UPDATE *
    // **********

    // Do Axis States
    this->doAxisStates();
    // Do Button States
    this->doButtonStates();
}

void GamePad::free()
{
    // ********
    // * FREE *
    // ********

    // NOTE: No resources allocated to 'free' function is here for api symmetry
    this->flush();

}

void GamePad::flush()
{
    // *********
    // * FLUSH *
    // *********

    // FLUSH AXES
    for (unsigned int i = 0; i < this->axisCount; i++)
    {
        this->axisStates[i] = 0.0f;
        this->axisStatesLastFrame[i] = 0.0f;
        this->axisStatesToggles[i] = false;
    }

    // FLUSH DIRECTIONAL TOGGLES
    this->upToggle = false;
    this->downToggle = false;
    this->leftToggle = false;
    this->rightToggle = false;

    // FLUSH BUTTONS
    for (unsigned int i = 0; i < this->buttonCount; i++)
    {
        this->buttonStates[i] = false;
        this->buttonStatesLastFrame[i] = false;
        this->buttonToggleStates[i] = false;
    }
}

void GamePad::doAxisStates()
{
    // ******************
    // * DO AXIS STATES *
    // ******************

    // DIRECTIONAL TOGGLES
    // Reset Toggles
    this->downToggle = false;
    this->upToggle = false;
    this->leftToggle = false;
    this->rightToggle = false;
    // Set Horizontal Toggles
    if (this->axisStates[0] < 0 && axisStatesLastFrame[0] >= 0) // NOTE: VERY IMPORTANT ON OTHER OPERATING SYSTEMS THE DPAD IS A BUTTON NOT AN AXIS, WE NEED TO FIX THIS WHEN PORTING
    {
        this->rightToggle = false;
        this->leftToggle = true;
    }
    if (this->axisStates[0] > 0 && axisStatesLastFrame[0] <= 0)
    {
        this->leftToggle = false;
        this->rightToggle = true;
    }
    // Set Vertical Toggles
    if (this->axisStates[1] > 0 && axisStatesLastFrame[1] <= 0)
    {
        this->downToggle = false;
        this->upToggle = true;
    }
    if (this->axisStates[1] < 0 && axisStatesLastFrame[1] >= 0)
    {
        this->upToggle = false;
        this->downToggle = true;
    }
    // AXES
    // Go through each Axis
    for(int i = 0; i < this->axisCount; i++)
    {
        // Turn off our toggle Flag for this axis
        this->axisStatesToggles[i] = false;
        // If an axis has changed between this and the last frame set the toggle to true
        if (this->axisStates[i] == true && this->axisStatesLastFrame[i] == false)
            this->axisStatesToggles[i] = true;
        // Store a cache of the state of the axis for this frame
        this->axisStatesLastFrame[i] = this->axisStates[i];
    }

}

void GamePad::doButtonStates()
{
    // *************
    // * DOBUTTONS *
    // *************

    for(int i = 0; i < this->buttonCount; i++)
    {
        this->buttonToggleStates[i] = false;

        // If a button has changed between this and the last frame set the toggle to true
        if (this->buttonStates[i] == true && this->buttonStatesLastFrame[i] == false)
            this->buttonToggleStates[i] = true;
        // Store a cache of the state of the buttons for this frame
        this->buttonStatesLastFrame[i] = this->buttonStates[i];
    }
}

float GamePad::getAxis(long axisNumber)
{
    // Validate Axis Number
    if (axisNumber < 0 || axisNumber > this->axisCount)
        return 0.0f;
    // Return our Axis Value
    return this->axisStates[axisNumber];
}

void GamePad::setAxis(long axisNumber, float value)
{
    // Validate Axis Number
    if (axisNumber < 0 || axisNumber > this->axisCount)
        return;
    // Set our Axis Value
    this->axisStates[axisNumber] = value;
}

bool GamePad::isButtonPressed(unsigned int button)
{
    // Keep button paremeter within safe range
    if (button < 0 && button > this->buttonCount - 1)
        return false;
    // Return the button state
    return this->buttonStates[button];
}

void GamePad::setButtonPressed(unsigned int button, bool state)
{
    // Keep button paremeter within safe range
    if (button < 0 && button > this->buttonCount - 1)
        return;
    // Set the button state
    this->buttonStates[button] = state;
}

bool GamePad::isButtonToggled(unsigned int button)
{
    // Keep button paremeter within safe range
    if (button < 0 && button > this->buttonCount - 1)
        return false;
    // Return the button toggle state
    return this->buttonToggleStates[button];
}

void GamePad::setButtonToggled(unsigned int button, bool state)
{
    // Keep button paremeter within safe range
    if (button < 0 && button > this->buttonCount - 1)
        return;
    // Set the button state
    this->buttonToggleStates[button] = state;
}

//void GamePad::doAnalogStick1()
//{
//    // Reset the AnalogStick1 toggles states
//    this->analog1Toggle[0] = this->analog1Toggle[1] = this->analog1Toggle[2] = this->analog1Toggle[3] = false;
//
//    // Set the UP/DOWN/LEFT/RIGHT flags for AnalogStick1
//    if (this->getAnalog1X() == 0.0f)
//    {
//        this->analog1State[2] = false;  // Analog1 Left = false
//        this->analog1State[3] = false;  // Analog1 Right = false
//    }
//    if (this->getAnalog1X() > 0.0f)
//    {
//        this->analog1State[2] = false; // Analog1 Left = false
//        this->analog1State[3] = true;  // Analog1 Right = true
//    }
//    if (this->getAnalog1X() < 0.0f)
//    {
//        this->analog1State[2] = true;  // Analog1 Left = false
//        this->analog1State[3] = false; // Analog1 Right = true
//    }
//    if (this->getAnalog1Y() == 0.0f)
//    {
//        this->analog1State[0] = false;  // Analog1 Up = false
//        this->analog1State[1] = false;  // Analog1 Down = false
//    }
//    if (this->getAnalog1Y() > 0.0f)
//    {
//        this->analog1State[0] = false; // Analog1 Up = false
//        this->analog1State[1] = true;  // Analog1 Down = true
//    }
//    if (this->getAnalog1Y() < 0.0f)
//    {
//        this->analog1State[0] = true;  // Analog1 Up = false
//        this->analog1State[1] = false; // Analog1 Down = true
//    }
//
//    // Set the Toggles for Analog Stick 1
//    if (this->analog1State[0] == true && this->analog1StateLastFrame[0] == false) this->analog1Toggle[0] = true;
//    if (this->analog1State[1] == true && this->analog1StateLastFrame[1] == false) this->analog1Toggle[1] = true;
//    if (this->analog1State[2] == true && this->analog1StateLastFrame[2] == false) this->analog1Toggle[2] = true;
//    if (this->analog1State[3] == true && this->analog1StateLastFrame[3] == false) this->analog1Toggle[3] = true;
//
//    // Set Analog1 Stick States for the last frame
//    this->analog1StateLastFrame[0] = this->analog1State[0];
//    this->analog1StateLastFrame[1] = this->analog1State[1];
//    this->analog1StateLastFrame[2] = this->analog1State[2];
//    this->analog1StateLastFrame[3] = this->analog1State[3];
//}
//
//void GamePad::doAnalogStick2()
//{
//    // Reset the AnalogStick2 toggles states
//    this->analog2Toggle[0] = this->analog2Toggle[1] = this->analog2Toggle[2] = this->analog2Toggle[3] = false;
//
//    // Set the UP/DOWN/LEFT/RIGHT flags for AnalogStick2
//    if (this->getAnalog2X() == 0.0f)
//    {
//        this->analog2State[2] = false;  // Analog2 Left = false
//        this->analog2State[3] = false;  // Analog2 Right = false
//    }
//    if (this->getAnalog2X() > 0.0f)
//    {
//        this->analog2State[2] = false; // Analog2 Left = false
//        this->analog2State[3] = true;  // Analog2 Right = true
//    }
//    if (this->getAnalog2X() < 0.0f)
//    {
//        this->analog2State[2] = true;  // Analog2 Left = false
//        this->analog2State[3] = false; // Analog2 Right = true
//    }
//    if (this->getAnalog2Y() == 0.0f)
//    {
//        this->analog2State[0] = false;  // Analog2 Up = false
//        this->analog2State[1] = false;  // Analog2 Down = false
//    }
//    if (this->getAnalog2Y() > 0.0f)
//    {
//        this->analog2State[0] = false; // Analog2 Up = false
//        this->analog2State[1] = true;  // Analog2 Down = true
//    }
//    if (this->getAnalog2Y() < 0.0f)
//    {
//        this->analog2State[0] = true;  // Analog2 Up = false
//        this->analog2State[1] = false; // Analog2 Down = true
//    }
//
//    // Set the Toggles for Analog Stick 2
//    if (this->analog2State[0] == true && this->analog2StateLastFrame[0] == false) this->analog2Toggle[0] = true;
//    if (this->analog2State[1] == true && this->analog2StateLastFrame[1] == false) this->analog2Toggle[1] = true;
//    if (this->analog2State[2] == true && this->analog2StateLastFrame[2] == false) this->analog2Toggle[2] = true;
//    if (this->analog2State[3] == true && this->analog2StateLastFrame[3] == false) this->analog2Toggle[3] = true;
//
//    // Set Analog2 Stick States for the last frame
//    this->analog2StateLastFrame[0] = this->analog2State[0];
//    this->analog2StateLastFrame[1] = this->analog2State[1];
//    this->analog2StateLastFrame[2] = this->analog2State[2];
//    this->analog2StateLastFrame[3] = this->analog2State[3];
//}
//
//void GamePad::doAnalogStick3()
//{
//    // Reset the AnalogStick2 toggles states
//    this->analog3Toggle[0] = this->analog3Toggle[1] = this->analog3Toggle[2] = this->analog3Toggle[3] = false;
//
//    // Set the UP/DOWN/LEFT/RIGHT flags for AnalogStick3
//    if (this->getAnalog3X() == 0.0f)
//    {
//        this->analog3State[2] = false;  // Analog3 Left = false
//        this->analog3State[3] = false;  // Analog3 Right = false
//    }
//    if (this->getAnalog3X() > 0.0f)
//    {
//        this->analog3State[2] = false; // Analog3 Left = false
//        this->analog3State[3] = true;  // Analog3 Right = true
//    }
//    if (this->getAnalog3X() < 0.0f)
//    {
//        this->analog3State[2] = true;  // Analog3 Left = false
//        this->analog3State[3] = false; // Analog3 Right = true
//    }
//    if (this->getAnalog3Y() == 0.0f)
//    {
//        this->analog3State[0] = false;  // Analog3 Up = false
//        this->analog3State[1] = false;  // Analog3 Down = false
//    }
//    if (this->getAnalog3Y() > 0.0f)
//    {
//        this->analog3State[0] = false; // Analog3 Up = false
//        this->analog3State[1] = true;  // Analog3 Down = true
//    }
//    if (this->getAnalog3Y() < 0.0f)
//    {
//        this->analog3State[0] = true;  // Analog3 Up = false
//        this->analog3State[1] = false; // Analog3 Down = true
//    }
//
//    // Set the Toggles for Analog Stick 2
//    if (this->analog3State[0] == true && this->analog3StateLastFrame[0] == false) this->analog3Toggle[0] = true;
//    if (this->analog3State[1] == true && this->analog3StateLastFrame[1] == false) this->analog3Toggle[1] = true;
//    if (this->analog3State[2] == true && this->analog3StateLastFrame[2] == false) this->analog3Toggle[2] = true;
//    if (this->analog3State[3] == true && this->analog3StateLastFrame[3] == false) this->analog3Toggle[3] = true;
//
//    // Set Analog3 Stick States for the last frame
//    this->analog3StateLastFrame[0] = this->analog3State[0];
//    this->analog3StateLastFrame[1] = this->analog3State[1];
//    this->analog3StateLastFrame[2] = this->analog3State[2];
//    this->analog3StateLastFrame[3] = this->analog3State[3];
//}

// ***************************************
// * SPECIAL FUNCTIONS FOR XBOX GAMEPADS *
// ***************************************

float GamePad::getLeftStickXAxis()
{
    #ifdef _WIN32 || _WIN64
        return this->getAxis(0);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->getAxis(0);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->getAxis(0);
    #endif // TARGET_OS_MAC
}

float GamePad::getLeftStickYAxis()
{
    #ifdef _WIN32 || _WIN64
        return this->getAxis(1);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->getAxis(1);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->getAxis(1);
    #endif // TARGET_OS_MAC
}

float GamePad::getRightStickXAxis()
{
    #ifdef _WIN32 || _WIN64
        return this->getAxis(4);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->getAxis(4);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->getAxis(3);
    #endif // TARGET_OS_MAC
}

float GamePad::getRightStickYAxis()
{
    #ifdef _WIN32 || _WIN64
        return this->getAxis(5);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->getAxis(5);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->getAxis(4);
    #endif // TARGET_OS_MAC
}

float GamePad::getDPadXAxis()
{
    #ifdef _WIN32 || _WIN64
        return this->getAxis(6);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->getAxis(7);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return 0.0f; // NOTE: Not supported on this platform
    #endif // TARGET_OS_MAC
}

float GamePad::getDPadYAxis()
{
    #ifdef _WIN32 || _WIN64
        return this->getAxis(7);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->getAxis(8);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return 0.0f;  // NOTE: Not supported on this platform
    #endif // TARGET_OS_MAC
}

float GamePad::getTriggers()
{
    #ifdef _WIN32 || _WIN64
        return this->getAxis(3);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return 0.0f; // NOTE: Not supported on this platform
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return 0.0f; // NOTE: Not supported on this platform
    #endif // TARGET_OS_MAC
}

float GamePad::getLeftTrigger()
{
    #ifdef _WIN32 || _WIN64
        return this->getAxis(9);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->getAxis(3);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->getAxis(5);
    #endif // TARGET_OS_MAC
}

float GamePad::getRightTrigger()
{
    #ifdef _WIN32 || _WIN64
        return this->getAxis(10);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->getAxis(6);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->getAxis(6);
    #endif // TARGET_OS_MAC
}

bool GamePad::isAButtonPressed()
{
    #ifdef _WIN32 || _WIN64
        return this->isButtonPressed(0);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->isButtonPressed(0);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->isButtonPressed(16);
    #endif // TARGET_OS_MAC
}

bool GamePad::isAButtonToggled()
{
    #ifdef _WIN32 || _WIN64
        return this->isButtonToggled(0);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->isButtonToggled(0);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->isButtonToggled(16);
    #endif // TARGET_OS_MAC
}

bool GamePad::isBButtonPressed()
{
    #ifdef _WIN32 || _WIN64
        return this->isButtonPressed(1);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->isButtonPressed(1);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->isButtonPressed(17);
    #endif // TARGET_OS_MAC
}

bool GamePad::isBButtonToggled()
{
    #ifdef _WIN32 || _WIN64
        return this->isButtonToggled(1);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->isButtonToggled(1);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->isButtonToggled(17);
    #endif // TARGET_OS_MAC
}

bool GamePad::isXButtonPressed()
{
    #ifdef _WIN32 || _WIN64
        return this->isButtonPressed(2);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->isButtonPressed(2);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->isButtonPressed(18);
    #endif // TARGET_OS_MAC
}

bool GamePad::isXButtonToggled()
{
    #ifdef _WIN32 || _WIN64
        return this->isButtonToggled(2);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->isButtonToggled(2);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->isButtonToggled(18);
    #endif // TARGET_OS_MAC
}

bool GamePad::isYButtonPressed()
{
    #ifdef _WIN32 || _WIN64
        return this->isButtonPressed(3);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->isButtonPressed(3);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->isButtonPressed(19);
    #endif // TARGET_OS_MAC
}

bool GamePad::isYButtonToggled()
{
    #ifdef _WIN32 || _WIN64
        return this->isButtonToggled(3);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->isButtonToggled(3);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->isButtonToggled(19);
    #endif // TARGET_OS_MAC
}

bool GamePad::isLeftBumperButtonPressed()
{
    #ifdef _WIN32 || _WIN64
        return this->isButtonPressed(4);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->isButtonPressed(4);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->isButtonPressed(13);
    #endif // TARGET_OS_MAC
}

bool GamePad::isLeftBumperButtonToggled()
{
    #ifdef _WIN32 || _WIN64
        return this->isButtonToggled(4);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->isButtonToggled(4);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->isButtonToggled(13);
    #endif // TARGET_OS_MAC
}

bool GamePad::isRightBumperButtonPressed()
{
    #ifdef _WIN32 || _WIN64
        return this->isButtonPressed(5);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->isButtonPressed(5);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->isButtonPressed(14);
    #endif // TARGET_OS_MAC
}

bool GamePad::isRightBumperButtonToggled()
{
    #ifdef _WIN32 || _WIN64
        return this->isButtonToggled(5);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->isButtonToggled(5);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->isButtonToggled(14);
    #endif // TARGET_OS_MAC
}

bool GamePad::isBackButtonPressed()
{
    #ifdef _WIN32 || _WIN64
        return this->isButtonPressed(6);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->isButtonPressed(6);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->isButtonPressed(10);
    #endif // TARGET_OS_MAC
}

bool GamePad::isBackButtonToggled()
{
    #ifdef _WIN32 || _WIN64
        return this->isButtonToggled(6);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->isButtonToggled(6);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->isButtonToggled(10);
    #endif // TARGET_OS_MAC
}

bool GamePad::isStartButtonPressed()
{
    #ifdef _WIN32 || _WIN64
        return this->isButtonPressed(7);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->isButtonPressed(7);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->isButtonPressed(9);
    #endif // TARGET_OS_MAC
}

bool GamePad::isStartButtonToggled()
{
    #ifdef _WIN32 || _WIN64
        return this->isButtonToggled(7);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->isButtonToggled(7);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->isButtonToggled(9);
    #endif // TARGET_OS_MAC
}

bool GamePad::isLeftStickButtonPressed()
{
    #ifdef _WIN32 || _WIN64
        return this->isButtonPressed(8);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->isButtonPressed(9);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->isButtonPressed(11);
    #endif // TARGET_OS_MAC
}

bool GamePad::isLeftStickButtonToggled()
{
    #ifdef _WIN32 || _WIN64
        return this->isButtonToggled(8);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->isButtonToggled(9);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->isButtonToggled(11);
    #endif // TARGET_OS_MAC
}

bool GamePad::isRightStickButtonPressed()
{
    #ifdef _WIN32 || _WIN64
        return this->isButtonPressed(9);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->isButtonPressed(10);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->isButtonPressed(12);
    #endif // TARGET_OS_MAC
}

bool GamePad::isRightStickButtonToggled()
{
    #ifdef _WIN32 || _WIN64
        return this->isButtonToggled(9);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->isButtonToggled(10);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->isButtonToggled(12);
    #endif // TARGET_OS_MAC
}

bool GamePad::isDPadUpButtonPressed()
{
    #ifdef _WIN32 || _WIN64
        /* TODO: get this behaviour working!
            currently always return false, because on windows, Up on the DPad is an axis
            I want it to grab the actual axis value */
        return false;
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->isButtonPressed(13);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->isButtonPressed(5);
    #endif // TARGET_OS_MAC
}

bool GamePad::isDPadUpButtonToggled()
{
    #ifdef _WIN32 || _WIN64
        /* TODO: get this behaviour working!
            currently always return false, because on windows, Up on the DPad is an axis
            I want it to grab the actual axis value */
        return false;
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->isButtonToggled(13);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->isButtonToggled(5);
    #endif // TARGET_OS_MAC
}

bool GamePad::isDPadDownButtonPressed()
{
    #ifdef _WIN32 || _WIN64
        /* TODO: get this behaviour working!
            currently always return false, because on windows, Down on the DPad is an axis
            I want it to grab the actual axis value */
        return false;
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->isButtonPressed(14);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->isButtonPressed(6);
    #endif // TARGET_OS_MAC
}

bool GamePad::isDPadDownButtonToggled()
{
    #ifdef _WIN32 || _WIN64
        /* TODO: get this behaviour working!
            currently always return false, because on windows, Down on the DPad is an axis
            I want it to grab the actual axis value */
        return false;
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->isButtonToggled(14);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->isButtonToggled(6);
    #endif // TARGET_OS_MAC
}

bool GamePad::isDPadLeftButtonPressed()
{
    #ifdef _WIN32 || _WIN64
        /* TODO: get this behaviour working!
            currently always return false, because on windows, Left on the DPad is an axis
            I want it to grab the actual axis value */
        return false;
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->isButtonPressed(11);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->isButtonPressed(7);
    #endif // TARGET_OS_MAC
}

bool GamePad::isDPadLeftButtonToggled()
{
    #ifdef _WIN32 || _WIN64
        /* TODO: get this behaviour working!
            currently always return false, because on windows, Left on the DPad is an axis
            I want it to grab the actual axis value */
        return false;
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->isButtonToggled(11);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->isButtonToggled(7);
    #endif // TARGET_OS_MAC
}

bool GamePad::isDPadRightButtonPressed()
{
    #ifdef _WIN32 || _WIN64
        /* TODO: get this behaviour working!
            currently always return false, because on windows, Right on the DPad is an axis
            I want it to grab the actual axis value */
        return false;
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->isButtonPressed(12);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->isButtonPressed(8);
    #endif // TARGET_OS_MAC
}

bool GamePad::isDPadRightButtonToggled()
{
    #ifdef _WIN32 || _WIN64
        /* TODO: get this behaviour working!
            currently always return false, because on windows, Right on the DPad is an axis
            I want it to grab the actual axis value */
        return false;
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->isButtonToggled(12);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->isButtonToggled(8);
    #endif // TARGET_OS_MAC
}

bool GamePad::isXboxButtonPressed()
{
    #ifdef _WIN32 || _WIN64
        return this->isButtonPressed(15);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->isButtonPressed(15);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->isButtonPressed(15);
    #endif // TARGET_OS_MAC
}

bool GamePad::isXboxButtonToggled()
{
    #ifdef _WIN32 || _WIN64
        return this->isButtonToggled(15);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__
        return this->isButtonToggled(15);
    #endif // __linux__

    #ifdef TARGET_OS_MAC
        return this->isButtonToggled(15);
    #endif // TARGET_OS_MAC
}
