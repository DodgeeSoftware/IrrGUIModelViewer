#ifndef MOUSE_H
#define MOUSE_H

// C++ Includes
#include <iostream>

// Irrlicht
#include <irrlicht.h>

/** The Mouse Class is a container for the mouse **/
class Mouse
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Default Constructor
        Mouse()
        {
            this->x = 0;
            this->y = 0;
            this->xRelative = 0;
            this->yRelative = 0;
            this->leftButtonDown = false;
            this->middleButtonDown = false;
            this->rightButtonDown = false;
            this->doubleLeftClick = false;
            this->doubleMiddleClick = false;
            this->doubleRightClick = false;
            this->trippleLeftClick = false;
            this->trippleMiddleClick = false;
            this->trippleRightClick = false;
            this->leftButtonToggled = false;
            this->middleButtonToggled = false;
            this->rightButtonToggled = false;
            this->leftButtonDownLastFrame = false;
            this->middleButtonDownLastFrame = false;
            this->rightButtonDownLastFrame = false;
            this->scrollWheel = 0.0f;
            this->scrollDownToggle = false;
            this->scrollUpToggle = false;
            this->leftDrag = false;
            this->leftDragRelease = false;
            this->leftDragStart[0] = 0;
            this->leftDragStart[1] = 0;
            this->middleDrag = false;
            this->middleDragRelease = false;
            this->middleDragStart[0] = 0;
            this->middleDragStart[1] = 0;
            this->rightDrag = false;
            this->rightDragRelease = false;
            this->rightDragStart[0] = 0;
            this->rightDragStart[1] = 0;
            this->pCursorControl = 0;

            this->movedFlag = false;
        }
        //! Destructor
        virtual ~Mouse() {}

    protected:
        //! Copy Constructor
        Mouse(Mouse& other) {}

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
        //! Update
        virtual void update();
        //! Release
        virtual void free();
        //! Flush (clear all toggles and buttons down)
        virtual void flush();

    // ************
    // * POSITION *
    // ************
    public:
        //! Get the horizontal mouse position
        virtual int getX() { return this->x; }
        //! Get the vertical mouse position
        virtual int getY() { return this->y; }
        //! Get the relative horizontal mouse position
        virtual int getXRelative() { return this->xRelative; }
        //! Get the relative vertical mouse position
        virtual int getYRelative() { return this->yRelative; }
        //! Set the relative mouse position
        virtual void setRelativePosition(int x, int y) { this->xRelative = x; this-> yRelative = y; }
// NOTE: I left this code here to show that I could have used out of the box behaviour for relative position
// TODO: Before release I might want to remove this commented out section
//        //! Get Relative Position X
//        virtual float getXRelative() { return this->pCursorControl->getRelativePosition().X; }
//        //! Get Relative Position Y
//        virtual float getYRelative() { return this->pCursorControl->getRelativePosition().Y; }
//        //! Get Relative Position
//        virtual irr::core::position2df getRelativePosition() { return this->pCursorControl->getRelativePosition(); }
        //! Was the mouse moved?
        virtual bool wasMoved() { return this->movedFlag; }
        //! Set moved Flag
        virtual void setMovedFlag(bool state) {this->movedFlag = state; }

    protected:
        // Horizontal Mouse Position in window co-ordinates
        int x;
        // Vertical Mouse Position in window co-ordinates
        int y;
        // Relative Horizontal Mouse Position in window co-ordinates
        int xRelative;
        // Relative Vertical Mouse Position in window co-ordinates
        int yRelative;
        // track if the mouse has moved between this and the last frame
        bool movedFlag;

    // ***********************
    // * BUTTONS AND TOGGLES *
    // ***********************
    public:
        //! Is the left mouse button Pressed?
        virtual const bool isLeftButtonPressed() { return this->leftButtonDown; }
        //! Set the left mouse button Pressed
        virtual void setLeftMouseButtonPressed(bool state) { this->leftButtonDown = state; }
        //! Is the middle mouse button Pressed?
        virtual const bool isMiddleButtonPressed() { return this->middleButtonDown; }
        //! Set the middle mouse button Pressed
        virtual void setMiddleMouseButtonPressed(bool state) { this->middleButtonDown = state; }
        //! Is the right mouse button Pressed?
        virtual const bool isRightButtonPressed() { return this->rightButtonDown; }
        //! Set the right mouse button Pressed
        virtual void setRightMouseButtonPressed(bool state) { this->rightButtonDown = state; }
        //! Was the left mouse button toggled
        virtual bool isLeftButtonToggled() { return this->leftButtonToggled; }
        //! Was the middle mouse button toggled
        virtual bool isMiddleButtonToggled() { return this->middleButtonToggled; }
        //! Was the right mouse button toggled
        virtual bool isRightButtonToggled() { return this->rightButtonToggled; }

    protected:
        // Keep track of the state of the left mouse button
        bool leftButtonDown;
        // Keep track of the state of the middle mouse button
        bool middleButtonDown;
        // Keep track of the state of the right mouse button
        bool rightButtonDown;
        // Was the left Button toggled
        bool leftButtonToggled;
        // Was the middle Button toggled
        bool middleButtonToggled;
        // Was the middle Button toggled
        bool rightButtonToggled;
        // Keep track of the state of the left mouse button
        bool leftButtonDownLastFrame;
        // Keep track of the state of the middle mouse button
        bool middleButtonDownLastFrame;
        // Keep track of the state of the right mouse button
        bool rightButtonDownLastFrame;

    // ****************
    // * DOUBLE CLICK *
    // ****************
    public:
        //! Is double left click
        virtual bool isDoubleLeftClick() { return this->doubleLeftClick; }
        //! Set double left click
        virtual void setDoubleLeftClick(bool state) { this->doubleLeftClick = state; }
        //! Is double middle click
        virtual bool isDoubleMiddleClick() { return this->doubleMiddleClick; }
        //! Set double middle click
        virtual void setDoubleMiddleClick(bool state) { this->doubleMiddleClick = state; }
        //! Is double right click
        virtual bool isDoubleRightClick() { return this->doubleRightClick; }
        //! Set double right click
        virtual void setDoubleRightClick(bool state) { this->doubleRightClick = state; }

    protected:
        // Keep track of double left clicks
        bool doubleLeftClick;
        // Keep track of double middle clicks
        bool doubleMiddleClick;
        // Keep track of double right clicks
        bool doubleRightClick;

    // *****************
    // * TRIPPLE CLICK *
    // *****************
    public:
        //! Is tripple left click
        virtual bool isTrippleLeftClick() { return this->trippleLeftClick; }
        //! Set tripple left click
        virtual void setTrippleLeftClick(bool state) { this->trippleLeftClick = state; }
        //! Is tripple middle click
        virtual bool isTrippleMiddleClick() { return this->trippleMiddleClick; }
        //! Set tripple middle click
        virtual void setTrippleMiddleClick(bool state) { this->trippleMiddleClick = state; }
        //! Is tripple right click
        virtual bool isTrippleRightClick() { return this->trippleRightClick; }
        //! Set tripple right click
        virtual void setTrippleRightClick(bool state) { this->trippleRightClick = state; }

    protected:
        // Keep track of tripple left clicks
        bool trippleLeftClick;
        // Keep track of tripple middle clicks
        bool trippleMiddleClick;
        // Keep track of tripple right clicks
        bool trippleRightClick;

    // ****************
    // * SCROLL WHEEL *
    // ****************
    public:
        //! Get the scroll Wheel
        virtual float getScrollWheel() { return this->scrollWheel; }
        //! Set the scroll Wheel
        virtual void setScrollWheel(float value) { this->scrollWheel = value; }
        //! isScrollup
        virtual bool isScrollUp() { return this->scrollWheel > 0.0f; }
        //! isSrolldown
        virtual bool isScrollDown()  { return this->scrollWheel < 0.0f; }
        //! is ScrollUpToggle
        virtual bool isScrollUpToggled() { return this->scrollUpToggle; }
        //! is ScrollDownToggle
        virtual bool isScrollDownToggled() { return this->scrollDownToggle; }
        //! setScrollupToggle
        virtual void setScrollUpToggled(bool state) { this->scrollUpToggle = state; }
        //! setScrolldownToggle
        virtual void setScrollDownToggled(bool state) { this->scrollDownToggle = state; }

    protected:
        // Keep track of the value of the scroll wheel
        float scrollWheel;
        // Keep track of scroll up toggle
        bool scrollUpToggle;
        // Keep track of scroll up toggle
        bool scrollDownToggle;

    // ************
    // * DRAGGING *
    // ************
    public:
        //! Is left drag
        virtual bool isLeftDrag() { return this->leftDrag; }
        //! Set left drag
        virtual void setLeftDrag(bool state) { this->leftDrag = state; }
        //! Is Left Drag Release
        virtual bool isLeftDragRelease() { return this->leftDragRelease; }
        //! Set Left Drag Release
        virtual void setLeftDragRelease(bool state) { this->leftDragRelease = state; }
        //! Set left drag start co-oridinates
        virtual void setLeftDragStart(int x, int y) { this->leftDragStart[0] = x; this->leftDragStart[1] = y; }
        //! Is middle drag
        virtual bool isMiddleDrag() { return this->middleDrag; }
        //! Set middle drag
        virtual void setMiddleDrag(bool state) { this->middleDrag = state; }
        //! Is Middle Drag Release
        virtual bool isMiddleDragRelease() { return this->middleDragRelease; }
        //! Set Middle Drag Release
        virtual void setMiddleDragRelease(bool state) { this->middleDragRelease = state; }
        //! Set middle drag start co-oridinates
        virtual void setMiddleDragStart(int x, int y) { this->middleDragStart[0] = x; this->middleDragStart[1] = y; }
        //! Is right drag
        virtual bool isRightDrag() { return this->rightDrag; }
        //! Set right drag
        virtual void setRightDrag(bool state) { this->rightDrag = state; }
        //! Is Right Drag Release
        virtual bool isRightDragRelease() { return this->rightDragRelease; }
        //! Set Right Drag Release
        virtual void setRightDragRelease(bool state) { this->rightDragRelease = state; }
        //! Set right drag start co-oridinates
        virtual void setRightDragStart(int x, int y) { this->rightDragStart[0] = x; this->rightDragStart[1] = y; }

    protected:
        // keep track of left mouse drag
        bool leftDrag;
        // Keep track of when the left drag is released
        bool leftDragRelease;
        // keep track of left drag start co-ordinates
        int leftDragStart[2];
        // keep track of middle mouse drag
        bool middleDrag;
        // Keep track of when the middle drag is released
        bool middleDragRelease;
        // keep track of middle drag start co-ordinates
        int middleDragStart[2];
        // keep track of right mouse drag
        bool rightDrag;
        // Keep track of when the right drag is released
        bool rightDragRelease;
        // keep track of right drag start co-ordinates
        int rightDragStart[2];

    // ***********************************************************************
    // * ACCESS TO THE IRRLICHT CURSOR FUNCTIONS THROUGH THE MOUSE INTERFACE *
    // ***********************************************************************
    public:
        //! Set Cursor Control
        virtual void setCursorControl(irr::gui::ICursorControl* pCursorControl) { this->pCursorControl = pCursorControl; }
        //! AddIcon
        virtual void addIcon(irr::gui::SCursorSprite& sprite) { this->pCursorControl->addIcon(sprite); }
        //! ChangeIcon
        virtual void changeIcon(irr::gui::ECURSOR_ICON icon, irr::gui::SCursorSprite& sprite) { this->pCursorControl->changeIcon(icon, sprite); }
        //! Get Active Icon
        virtual irr::gui::ECURSOR_ICON getActiveIcon() { return this->pCursorControl->getActiveIcon(); }
        //! Get Debug Name
        virtual const irr::c8* getDebugName() { return this->pCursorControl->getDebugName(); }
        //! Get Supported Icon Size
        virtual irr::core::dimension2di getSupportedIconSize() const { return this->pCursorControl->getSupportedIconSize(); }
        //! Is Pointer Visible
        virtual bool isVisible() { return this->pCursorControl->isVisible(); }
        //! Set Active Icon
        virtual void setActiveIcon(irr::gui::ECURSOR_ICON icon) { this->pCursorControl->setActiveIcon(icon); }
        //! Set Platform Behaviour
        virtual void setPlatformBehavior(irr::gui::ECURSOR_PLATFORM_BEHAVIOR behavior) { this->pCursorControl->setPlatformBehavior(behavior); }
        //! Set Mouse Position
        virtual void setPosition(int x, int y) {this->x = x; this->y = y; this->pCursorControl->setPosition(x, y); }
        //! Set Visible
        virtual void setVisible(bool state) { this->pCursorControl->setVisible(state); }

    protected:
        // Pointer to the cursor control for the mouse
        irr::gui::ICursorControl* pCursorControl;
};

#endif // MOUSE_H
