#ifndef MODELVIEWERGAMESTATE_H
#define MODELVIEWERGAMESTATE_H

// C++ Includes
#include <list>
#include <vector>
#include <set>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <map>

// Irrlicht Includes
#include <irrlicht.h>

// GAME SPECIFIC Includes
#include "GameInput/GameInput.h"
//#include "GameLog.h"
// #include "GameStates.h" // DO NOT INCLUDE THIS DELIBERATELY COMMENTED OUT TO SHOW WE EXCLUDED IT
#include "GameTimers/GameTimers.h"
#include "GameUtils/GameUtils.h"

// State Includes
#include "IGameState.h"

/** The ModelViewerGameState contains a tool to look at custom ModelFormats **/
class ModelViewerGameState : public IGameState
{
    // *****************************
    // * CONSTRUCTORS / DESTRUCTOR *
    // *****************************
    public:
        //! Constructor
        ModelViewerGameState(Game* pGame);
        //! Destructor
        virtual ~ModelViewerGameState();

    protected:
        //! Copy Constructor
        ModelViewerGameState(ModelViewerGameState& other);

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // NO OPERATORS TO OVERLOAD

    protected:
        //! Assignment Operator
        ModelViewerGameState& operator=(const ModelViewerGameState& other);

    // ************************
    // * CORE STATE FUNCTIONS *
    // ************************
    public:
        //! The state entry callback
        virtual void enter();
        //! Handle incoming input events
        virtual void handleEvents();
        //! Process events, from Irrlicht, as they happen (using this is optional. Use only if you are using the irrlicht event system)
        virtual bool onEvent(const irr::SEvent& event);
        //! Keyboard event
        virtual bool keyboardEvent(const irr::SEvent& event);
        //! Mouse event
        virtual bool mouseEvent(const irr::SEvent& event);
        //! GUI event
        virtual bool GUIEvent(const irr::SEvent& event);
        //! joystick event
        virtual bool joystickEvent(const irr::SEvent& event);
        //! Log event
        virtual bool logEvent(const irr::SEvent& event);
        //! Handle all state logic
        virtual void think();
        //! Interpolate to the next frame
        virtual void update();
        //! Draw the state's graphics
        virtual void draw();
        //! Draw the state's GUI objects
        virtual void drawGUI();
        //! A callback for when the state is finished
        virtual void exit();

    public:
        //! Start the State
        virtual void start();
        //! Stop the State()
        virtual void stop();
        //! Pause the State
        virtual void pause();
        //! Resume the State
        virtual void resume();

    protected:
        // State Timer
        Timer stateTimer;

    protected:
        //! Init Background
        bool initBackground();
        //! Init Window
        bool initWindow();
        //! Init Cursor
        bool initCursor();
        //! Init Skin
        bool initSkin();
        //! Init GUI
        bool initGUI();
        //! Init Camera
        bool initCamera();
        //! Init Lighting
        bool initLighting();
        //! Init Scene
        bool initScene();

    // ********************
    // * WINDOW CALLBACKS * // NOTE: In Irrlicht these don't work
    // ********************
    public:
        //! On Change Resolution
        virtual void onWindowChangeResolution(int resolutionX, int resolutionY);
        //! On FullScreen
        virtual void onWindowFullScreen(bool state);
        //! On Reposition
        virtual void onWindowReposition(int newX, int newY);
        //! On Resize Window
        virtual void onWindowResize(int newWidth, int newHeight);
        //! On Close Window
        virtual void onWindowClose();
        //! On Window Refesh
        virtual void onWindowRefresh();
        //! On Window Focus Change
        virtual void onWindowFocusChange(bool state);
        //! On Window Iconify
        virtual void onWindowIconify(bool state);

    // **********************
    // * LANGUAGE CALLBACKS *
    // **********************
    public:
        //! On Change Language
        virtual void onChangeLanguageCallBack(std::string language);

    // ****************
    // * MODEL VIEWER *
    // ****************

    // SCENE
    protected:
        //! Make Default Light
        void makeDefaultLight();
        //! Make Default Camera
        void makeDefaultCamera();
        //! Make Default Model
        void makeDefaultModel();

    protected:
        irr::scene::ILightSceneNode* pLight;
        irr::scene::ICameraSceneNode* pCamera;
        float cameraDistance;
        float cameraDistanceDelta;
        float defaultCameraNearValue;
        //float theta;
        //float phi;

        bool allowMovement;
        bool rightMouseButtonDown;
        bool middleMouseButtonDown;
        bool leftMouseButtonDown;
        irr::core::position2df mouseDragStart;
        bool disableDrag;
        float MouseXBufferPosition;
        float MouseYBufferPosition;
        float currentMouseX;
        float currentMouseY;
        float mouseDeltaX;
        float mouseDeltaY;

        //irr::core::stringw consoleBoxText;

    // GUI
    protected:
        //! Build Navigation Bar
        bool buildNavigationBar();
        //! Build Options
        void buildOptions();
        ////! build Console
        //void buildConsole();

    protected:
        //! Refresh Options Window
        void refreshOptionsWindow();

    protected:
        irr::gui::IGUISkin* pSkin;

        // ID's For GUI Components
        std::map<std::string, irr::s32> guiComponentID;

        irr::gui::IGUIButton* pOpenButton;
        irr::gui::IGUIButton* pOptionsButton;
        irr::gui::IGUIButton* pCloseButton;
        irr::gui::IGUIButton* pReloadButton;
        irr::gui::IGUIButton* pAboutButton;
        irr::gui::IGUIButton* pExitButton;

        irr::gui::IGUIWindow* pOptionsWindow;
        irr::gui::IGUICheckBox* pVerticesCheckBox;
        irr::gui::IGUICheckBox* pWireFramesCheckBox;
        irr::gui::IGUICheckBox* pNormalsCheckBox;
        irr::gui::IGUICheckBox* pTexturesCheckBox;
        irr::gui::IGUICheckBox* pShadersCheckBox;
        irr::gui::IGUICheckBox* pVertexColoursCheckBox;
        irr::gui::IGUICheckBox* pFrontFaceCullCheckBox;
        irr::gui::IGUICheckBox* pBackFaceCullCheckBox;
        irr::gui::IGUICheckBox* pLightingCheckBox;
        bool checkBoxVerticesFlag;
        bool checkBoxNormalsFlag;
        bool checkBoxTextureFlag;
        bool checkBoxShadersFlag;
        bool checkBoxVertexColoursFlag;
        bool checkBoxFrontFaceCullFlag;
        bool checkBoxBackFaceCullFlag;
        bool checkBoxWireframeFlag;
        bool checkBoxLightingFlag;

        irr::gui::IGUIWindow* pAboutWindow;
        irr::core::stringw aboutWindowText;

//        irr::gui::IGUIEditBox* pConsoleBox;
//        irr::core::stringw consoleBoxText;
//        irr::gui::IGUIScrollBar* pScrollbarHorizontalConsole;
//        irr::gui::IGUIScrollBar* pScrollbarVerticalConsole;

    // MAIN FUNCTIONS
    protected:
        //! Open a Model File
        bool openModel(std::string filename);
        //! Reload a Model File
        bool reload();
        //! Close an open Model
        void closeModel();
        //! Show Options
        void showOptions();
        //! Hide Options
        void hideOptions();
        //! Show About
        void showAboutWindow();
        //! Quit the ModelViewer
        void quit();

    protected:
        // Local refrence to the model scenenode
        irr::scene::ISceneNode* pModel;
        // Local reference for the model filename
        std::string modelFilename;
        // Pointer to the Open Dialog
        irr::gui::IGUIFileOpenDialog* pOpenDialog;

    // CAPTION
    protected:
        //! Default Window Caption
        void defaultCaption();
        //! Set Window Caption
        void setCaption(std::string text);
};

#endif // MODELVIEWERGAMESTATE_H
