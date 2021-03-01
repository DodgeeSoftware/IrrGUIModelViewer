#include "InputSystem.h"

bool InputSystem::init()
{
    // Set init flag to true
    this->wasInitFlag = false;
    // Set the cursor control for the mouse
    this->mouse.setCursorControl(pIrrlichtDevice->getCursorControl());
    // Initialise the keyboard
    if (this->keyboard.init() == false)
        return false;
    // Initialise the mouse
    if (this->mouse.init() == false)
        return false;
    /* Initalise the game pads create a container to hold
        joystick information and activate GamePad tracking
        for the irrlicht device */
    irr::core::array<irr::SJoystickInfo> joystickInfo;
    // Activate Irrlicht's Joystick Inputs
    this->pIrrlichtDevice->activateJoysticks(joystickInfo);
    //  Create the GamePads
    for(int i = 0; i < joystickInfo.size(); i++)
    {
        // Create a new game pad
        this->gamePads.push_back(new GamePad());
        // Initialise the new game pad
        if (this->gamePads[i]->init(joystickInfo[i]) == false)
            return false;
        // Send information about gamepads found to the console
        std::cout << "Game Pad Found" << std::endl;
        std::cout << "Name: " << this->gamePads[i]->getName() << std::endl;
        std::cout << "ID: " << this->gamePads[i]->getID() << std::endl;
        std::cout << "Number of Axes: " << this->gamePads[i]->getAxisCount() << std::endl;
        std::cout << "Number of Buttons: " << this->gamePads[i]->getButtonCount() << std::endl;
        // NOTE: Not cross platform
        //std::cout << "POV Hat: " << ((this->gamePads[i]->isPOVHat() == true) ? "Yes" : "No") << std::endl;
    }
    // Declare null GamePadInfo
    irr::SJoystickInfo nullGamePadInfo;
    // Initialise the null gamepad
    if (this->nullGamePad.init(nullGamePadInfo) == false)
        return false;
    // Success
    return true;
}

bool InputSystem::handleEvents(const irr::SEvent& event)
{
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    {
        // Set the Alt Key Value
        if (event.KeyInput.Key == irr::KEY_MENU ||
            event.KeyInput.Key == irr::KEY_LMENU ||
            event.KeyInput.Key == irr::KEY_RMENU)
        {
            this->keyboard.setAltKeyPressed(event.KeyInput.PressedDown);
        }
        // Set the control key value
        this->keyboard.setControlKeyPressed(event.KeyInput.Control);
        // Set the shift key value
        this->keyboard.setShiftKeyPressed(event.KeyInput.Shift);
        // Implement this function in they keyboard class
        this->keyboard.setKeyPressed(event.KeyInput.Key, event.KeyInput.PressedDown);
        // Handled
        return false;
    }
    if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
    {
        switch(event.MouseInput.Event)
        {
            case irr::EMIE_MOUSE_MOVED:
                // Handle mouse drag flags
                if (this->mouse.isLeftDrag() == false && this->mouse.isLeftButtonPressed() == true)
                {
                    this->mouse.setLeftDrag(true);
                    this->mouse.setLeftDragStart(pIrrlichtDevice->getCursorControl()->getPosition().X, pIrrlichtDevice->getCursorControl()->getPosition().Y);
                }
                if (this->mouse.isMiddleDrag() == false && this->mouse.isMiddleButtonPressed() == true)
                {
                    this->mouse.setMiddleDrag(true);
                    this->mouse.setMiddleDragStart(pIrrlichtDevice->getCursorControl()->getPosition().X, pIrrlichtDevice->getCursorControl()->getPosition().Y);
                }
                if (this->mouse.isRightDrag() == false && this->mouse.isRightButtonPressed() == true)
                {
                    this->mouse.setRightDrag(true);
                    this->mouse.setRightDragStart(pIrrlichtDevice->getCursorControl()->getPosition().X, pIrrlichtDevice->getCursorControl()->getPosition().Y);
                }
                // NOTE: This is not used we handle mouse movement flag internal to the mouse class
                //this->mouse.setMovedFlag(true);
                break;
            case irr::EMIE_LMOUSE_PRESSED_DOWN:
            {
                // Set the mouse left button state
                this->mouse.setLeftMouseButtonPressed(true);
                break;
            }
            case irr::EMIE_LMOUSE_LEFT_UP:
            {
                // Set the mouse left button state
                this->mouse.setLeftMouseButtonPressed(false);
                // Set the Left Drag Start
                this->mouse.setLeftDragStart(0, 0);
                // Turn off Left Drag
                this->mouse.setLeftDrag(false);
                // Set the Left Drag Release Flag
                this->mouse.setLeftDragRelease(true);
                break;
            }
            case irr::EMIE_MMOUSE_PRESSED_DOWN:
            {
                // Set the mouse middle button state
                this->mouse.setMiddleMouseButtonPressed(true);
                break;
            }
            case irr::EMIE_MMOUSE_LEFT_UP:
            {
                // Set the mouse middle button state
                this->mouse.setMiddleMouseButtonPressed(false);
                // Set the Middle Drag Start
                this->mouse.setMiddleDragStart(0, 0);
                // Turn off Middle Drag
                this->mouse.setMiddleDrag(false);
                // Set the Middle Drag Release Flag
                this->mouse.setMiddleDragRelease(true);
                break;
            }
            case irr::EMIE_RMOUSE_PRESSED_DOWN:
            {
                // Set the mouse right button state
                this->mouse.setRightMouseButtonPressed(true);
                break;
            }
            case irr::EMIE_RMOUSE_LEFT_UP:
            {
                // Set the mouse right button state
                this->mouse.setRightMouseButtonPressed(false);
                // Set the Right Drag Start
                this->mouse.setRightDragStart(0, 0);
                // Turn off Right Drag
                this->mouse.setRightDrag(false);
                // Set the Right Drag Release Flag
                this->mouse.setRightDragRelease(true);
                break;
            }
            case irr::EMIE_MOUSE_WHEEL:
            {
                // Set the value of the scroll wheel
                int value = 0;
                if (event.MouseInput.Wheel < 0)
                    value = -1;
                if (event.MouseInput.Wheel > 0)
                    value = 1;
                this->mouse.setScrollWheel(value);
                //std::cout << "Irrlicht scrollwheel: " << value << std::endl;
                break;
            }
            case irr::EMIE_LMOUSE_DOUBLE_CLICK:
            {
                // Set the Double Left Click Flag
                this->mouse.setDoubleLeftClick(true);
                break;
            }
            case irr::EMIE_MMOUSE_DOUBLE_CLICK:
            {
                // Set the Double Middle Click Flag
                this->mouse.setDoubleMiddleClick(true);
                break;
            }
            case irr::EMIE_RMOUSE_DOUBLE_CLICK:
            {
                // Set the Right Double Click Flag
                this->mouse.setDoubleRightClick(true);
                break;
            }
            case irr::EMIE_LMOUSE_TRIPLE_CLICK:
            {
                // Set the Left Tripple Click Flag
                this->mouse.setTrippleLeftClick(true);
                break;
            }
            case irr::EMIE_MMOUSE_TRIPLE_CLICK:
            {
                // Set the Middle Tripple Click Flag
                this->mouse.setTrippleMiddleClick(true);
                break;
            }
            case irr::EMIE_RMOUSE_TRIPLE_CLICK:
            {
                // Set the Right Tripple Click Flag
                this->mouse.setTrippleRightClick(true);
                break;
            }
            default:
                break;
        }
        // Allow Irrlicht to process other events by returning false
        return false;
    }
    if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT)
    {
        // Get the gamepad index
        unsigned int index = event.JoystickEvent.Joystick;
        // If our GamePad is Valid Process it's events
        if (index >= 0 && index < this->gamePads.size())
        {
            // Go through each of the Axes
            for (long axis = 0; axis < irr::SEvent::SJoystickEvent::NUMBER_OF_AXES; axis++) // NOTE: deliberatyly not using GamePad.getAxisCount (my gamepad supports 255 irrlicht supports 6)
            {
                // Get the normalised value of the GamePad's axis [number] and scale to 0.0f - 255.0f
                float value = ((float)(event.JoystickEvent.Axis[axis]) / 32767.0f) * 255.0f;
                // Make sure to cancel the movement in the dead zone of the game pad
                if (fabsf(value) < 64.0f)
                    value = 0.0f;
                // Set the Axis Value
                this->gamePads[index]->setAxis(axis, value);
            }
            // Go through each of the Buttons
            for(int i = 0; i < this->gamePads[index]->getButtonCount(); i++)
            {
                // Set the State for our button
                this->gamePads[index]->setButtonPressed(i, event.JoystickEvent.IsButtonPressed(i));
            }
        }
        // Allow Irrlicht to process other events by returning false
        return false;
    }
    // Allow Irrlicht to process other events by returning false
    return false;
}

void InputSystem::update()
{
    // Update the keyboard
    this->keyboard.update();
    // Update the mouse
    this->mouse.update();
    // Update the GamePad
    for (int i = 0; i < this->gamePads.size(); i++)
        this->gamePads[i]->update();
}

void InputSystem::shutdown()
{
    // Set the init flag to false
    this->wasInitFlag = false;
    // Release the Keyboard
    this->keyboard.free();
    // Release the Mouse
    this->mouse.free();
    // Release the GamePads
    for (int i = 0; i < this->gamePads.size(); i++)
    {
        this->gamePads[i]->free();
        delete this->gamePads[i];
    }
    // Release the null gamepad
    this->nullGamePad.free();
    // Clear the GamePads
    this->gamePads.clear();
}

void InputSystem::flush()
{
    // Flush the Keyboard
    this->keyboard.flush();
    // Flush the Mouse
    this->mouse.flush();
    // Go through each GamePad
    for(int i = 0; i < this->getGamePadCount(); i++)
    {
        // Free the GamePad
        this->getGamePad(i)->flush();
    }
}
