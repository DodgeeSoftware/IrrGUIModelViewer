#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

// C++ Includes
#include <cmath>
#include <iostream>
#include <vector>

// Irrlicht Includes
#include <irrlicht.h>
#include <ieventreceiver.h> // TODO: Does this need to be here

// Input Includes
#include "Keyboard.h"
#include "Mouse.h"
#include "GamePad.h"

/** The InputSystem class is a centralized location for keeping track of
    all input hardware attached to the system. This class keeps track of
    the keyboard, the mouse and game pads. **/
class InputSystem
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default Constructor
        InputSystem()
        {
            this->wasInitFlag = false;
            this->pIrrlichtDevice = 0;
        }
        //! Destructor
        virtual ~InputSystem() {}

    protected:
        //! Copy Constructor
        InputSystem(InputSystem& other) {}

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
        //! Initialise the input system
        virtual bool init();
        //! Handle system events
        virtual bool handleEvents(const irr::SEvent& event);
        //! Update the input system
        virtual void update();
        //! Free resources allocated by the input system
        virtual void shutdown();

    public:
        //! Flush the InputSystem
        virtual void flush();

    public:
        //! was the input system initialised
        virtual bool wasInit() { return this->wasInitFlag; }
        //! Get the Irrlicht Device
        virtual irr::IrrlichtDevice* getIrrlichtDevice() { return this->pIrrlichtDevice; }
        //! Set the Irrlicht Device
        virtual void setIrrlichtDevice(irr::IrrlichtDevice* pIrrlichtDevice) { this->pIrrlichtDevice = pIrrlichtDevice; }

    public:
        //! Get GamePad Count
        virtual int getGamePadCount() { return gamePads.size(); }

    public:
        //! Get Keyboard
        virtual Keyboard* getKeyboard() { return &keyboard; }
        //! Get Mouse
        virtual Mouse* getMouse() { return &mouse; }
        //! Get GamePad
        virtual GamePad* getGamePad(int id)
        {
            if (id < 0 || id > this->getGamePadCount() - 1)
                return &nullGamePad;
            return gamePads[id];
        }

    protected:
        // Keep track of whether or not this class has been intialised
        bool wasInitFlag;
        // A reference to the Irrlicht device
        irr::IrrlichtDevice* pIrrlichtDevice;
        // Local reference to the Keyboard
        Keyboard keyboard;
        // Local refernce to the mouse
        Mouse mouse;
        // Local reference to the GamePad
        std::vector<GamePad*> gamePads;
        // Null GamePad (used when unable to get a gamepad by id)
        GamePad nullGamePad;
};

#endif // INPUTSYSTEM_H
