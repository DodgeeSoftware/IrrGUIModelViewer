#include "Mouse.h"

bool Mouse::init()
{
    // If the cursor control hasn't been set return false
    if (this->pCursorControl == 0)
        return false;

    // Success
    return true;
}

void Mouse::update()
{
    // ***********************
    // * TRACK SCROLL WHEEL  *
    // ***********************
    // Set scroll up toggle
    if (this->scrollUpToggle == false && this->scrollWheel == 1)
    {
        this->scrollUpToggle = true;
    }
    else
    {
        this->scrollUpToggle = false;
    }
    // Set scroll down toggle
    if (this->scrollDownToggle == false && this->scrollWheel == -1)
    {
        this->scrollDownToggle = true;
    }
    else
    {
        this->scrollDownToggle = false;
    }
    // Reset the value of the scroll wheel
    this->scrollWheel = 0;

    // *********************
    // * TRACK MOUSE MOVED *
    // *********************
    if (this->x == pCursorControl->getPosition().X && this->y == pCursorControl->getPosition().Y)
    {
        this->movedFlag = false;
    }
    else
    {
        this->movedFlag = true;
    }

    // ***************************
    // * TRACK RELATIVE MOVEMENT *
    // ***************************
    this->xRelative = this->pCursorControl->getPosition().X - this->x;
    this->yRelative = this->pCursorControl->getPosition().Y - this->y;

    // ******************
    // * TRACK POSITION *
    // ******************
    this->x = this->pCursorControl->getPosition().X;
    this->y = this->pCursorControl->getPosition().Y;

    // ************************
    // * TRACK MOUSE DRAGGING *
    // ************************
    this->leftDragRelease = false;
    this->middleDragRelease = false;
    this->rightDragRelease = false;
// TODO: Consider Geting rid of this
//    // Turn off mouse drag on button release
//    if (this->leftButtonDown == false && this->leftDrag == true)
//    {
//        this->leftDragStart[0] = 0;
//        this->leftDragStart[1] = 0;
//        this->leftDrag = false;
//        this->leftDragRelease = true;
//    }
//    if (this->middleButtonDown == false && this->middleDrag == true)
//    {
//        this->middleDragStart[0] = 0;
//        this->middleDragStart[1] = 0;
//        this->middleDrag = false;
//        this->middleDragRelease = true;
//    }
//
//    if (this->rightButtonDown == false && this->rightDrag == true)
//    {
//        this->rightDragStart[0] = 0;
//        this->rightDragStart[1] = 0;
//        this->rightDrag = false;
//        this->rightDragRelease = true;
//    }

    // *************************
    // * TRACK TOGGLED BUTTONS *
    // *************************
    // Turn off all the toggle button states
    this->leftButtonToggled = false;
    this->middleButtonToggled = false;
    this->rightButtonToggled = false;
    // Turn off multiclick for the frame
    this->doubleLeftClick = false;
    this->doubleMiddleClick = false;
    this->doubleRightClick = false;
    this->trippleLeftClick = false;
    this->trippleMiddleClick = false;
    this->trippleRightClick = false;
    // If a button has changed between this and the last frame set the toggle
    if (this->leftButtonDown == true && this->leftButtonDownLastFrame == false)
        this->leftButtonToggled = true;
    if (this->middleButtonDown == true && this->middleButtonDownLastFrame == false)
        this->middleButtonToggled = true;
    if (this->rightButtonDown == true && this->rightButtonDownLastFrame == false)
        this->rightButtonToggled = true;
    // Store Button states for this fame
    this->leftButtonDownLastFrame = this->leftButtonDown;
    this->middleButtonDownLastFrame = this->middleButtonDown;
    this->rightButtonDownLastFrame = this->rightButtonDown;
}

void Mouse::free()
{
    /* Note: At the time of writing this is here for consistency in the interface and
        if we were to allocate resources with new we would have a place to clear things up */
}

void Mouse::flush()
{
    this->leftButtonToggled = false;
    this->middleButtonToggled = false;
    this->rightButtonToggled = false;
    this->leftDrag = false;
    this->middleDrag = false;
    this->rightDrag = false;
    this->movedFlag = false;
}
