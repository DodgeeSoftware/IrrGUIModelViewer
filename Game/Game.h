// (c) Copyright Shem Taylor 2021 all rights reserved
// Author: Shem Taylor
// Company: DodgeeSoftware
// Contact Info: dodgeesoftware@gmail.com
// Youtube: youtube.com/dodgeesoftware

#ifndef GAME_H
#define GAME_H

// C/C++ Includes
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>
#include <iomanip>

// Irrlicht Includes
#include <Irrlicht.h>

// Game Includes
#include "GameTimers/GameTimers.h"
#include "GameStates/GameStates.h"
#include "GameUtils/GameUtils.h"
#include "GameInput/GameInput.h"

/** The Game Class is based on the singleton pattern which wraps up
    the games main loop. It follows a microkernel archetecture in that
    engine wide functions and data are stored here and made available
    to game states via a pGame pointer **/
class Game : public irr::IEventReceiver, irr::video::IShaderConstantSetCallBack, irr::scene::ILightManager
{
    // ***********
    // * FRIENDS *
    // ***********

    // Each new state added friends game so that it
    // can access the game objects private members

    friend class ModelViewerGameState;

    // ***********************
    // * SINGLETON FUNCTIONS *
    // ***********************

    public:
        //! Get the singleton Instance
        static Game* getInstance();

    protected:
        // Singleton Poitner
        static Game* pInstance;

    // **************************
    // * COMMAND LINE ARGUMENTS *
    // **************************

    public:
        //! Process Command Line Args
        virtual void processCommandLineArguments(int argc, char* argv[]);

    protected:
        // Command line params go here

    // ***************
    // * CONSTRUCTOR *
    // ***************

    public:
        // Methods and members

    protected:
        //! Constructor
        Game();
        //! Destructor
        virtual ~Game();

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************

    public:
        //! Run the Games Main Loop
        virtual int run(int argc, char* argv[]);

    public:
        //! Initialise the Game
        virtual bool init();
        //! Init the IrrlichtDevice
        virtual bool initIrrlichtDevice();
        //! Init Window
        virtual bool initWindow();
        //! Initialise InputSystem
        virtual bool initInputSystem();
        //! Initialise the LightFactory
        virtual bool initLightManager();
        //! Init Camera
        virtual bool initCamera();

    public:
        //! Handle events
        virtual void handleEvents();
        //! Think
        virtual void think();
        //! Update
        virtual void update();
        //! Draw
        virtual void draw();
        //! Draw the GUI
        virtual void drawGUI();
        //! Swap buffers
        virtual void swapBuffers();

    public:
        //! Start the Game
        virtual void start();
        //! Stop the Game
        virtual void stop();
        //! Pause the game
        virtual void pause();
        //! Resume the game
        virtual void resume();
        //! Is the game engine paused
        virtual bool isPaused() { return this->paused; }
        //! Get Paused flag for the game engine
        virtual bool getPaused() { return this->paused; }
        //! Set Paused flag for the game engine
        virtual void setPaused(bool state) { this->paused = state; }
        //! Is the game engine running
        virtual bool isRunning() { return this->running; }
        //! Get Game Engine Running
        virtual bool getRunning() { return this->running; }
        //! Set the running state
        virtual void setRunning(bool running) { this->running = running; }

    public:
        //! Quit the Game
        virtual void quit();
        //! Shutdown Light Factory
        virtual void shutdownLightManager();
        //! Shutdown Font
        virtual void shutdownFont();
        //! Shutdown Window
        virtual void shutdownWindow();
        //! Shutdown Device
        virtual void shutdownDevice();
        //! Shutdown Input System
        virtual void shutdownInputSystem();
        //! Shutdown Camera
        virtual void shutdownCamera();

    protected:
        // Keep track of whether or not the game engine running
        bool running;
        // Keep track of whether or not the game engine is paused
        bool paused;

    // *************************
    // * GAME STATE MANAGEMENT *
    // *************************
    /* NOTE: This section provides control over the game state */
    public:
        //! Create all game states
        virtual void createGameStates();
        //! Change the current game state
        virtual void changeGameState(const char* state);
        //! Clean up all the game states
        virtual void deleteGameStates();

    protected:
        //! Get GameState
        virtual IGameState* getGameState() { return this->pGameState; }

    protected:
        // Pointer to the current game state
        IGameState* pGameState;
        // Keep track of all the game states
        std::map<std::string, IGameState*> gameStateMap;

    // ********************
    // * IRRLICHT HANDLES *
    // ********************
    /* NOTE: Provde external access to our essential irrlicht cores */

    public:
        //! Get the IrrlichtDevice
        virtual irr::IrrlichtDevice* getIrrlichtDevice() { return this->pIrrlichtDevice; }
        //! Get the Irrlicht Driver
        virtual irr::video::IVideoDriver* getVideoDriver() { return this->pVideoDriver; }
        //! Get the SceneManager
        virtual irr::scene::ISceneManager* getSceneManager() { return this->pSceneManager; }
        //! Get the GUIEnvironment
        virtual irr::gui::IGUIEnvironment* getGUIEnvironment() { return this->pGUIEnvironment; }
        //! Get the GUISKin
        irr::gui::IGUISkin* getSkin() { return this->pSkin; }
        //! Get the FileSystem
        virtual irr::io::IFileSystem* getFileSystem() { return this->pFileSystem; }
        //! Get the CursorControl
        virtual irr::gui::ICursorControl* getCursorControl() { return this->pCursorControl; }
        //! Get the EventReceiver
        virtual irr::IEventReceiver* getEventReceiver() { return this->pEventReceiver; }
        //! Get the Logger
        virtual irr::ILogger* getLogger() { return this->pLogger; }
        //! Get the GPU
        virtual irr::video::IGPUProgrammingServices* getGPUProgrammingServices() { return this->pGPUProgrammingServices; }
        //! Get the Scene Collision Manager
        virtual irr::scene::ISceneCollisionManager* getSceneCollisionManager() { return this->pSceneCollisionManager; }
        //! Get the Mesh Manipulator
        virtual irr::scene::IMeshManipulator* getMeshManipulator() { return this->pMeshManipulator; }
        //! Get the Default SceneNodeAnimatorFactory
        virtual irr::scene::ISceneNodeAnimatorFactory* getDefaultSceneNodeAnimatorFactory() { return this->pDefaultSceneNodeAnimatorFactory; }
        //! Get the Default SceneNodeFactory
        virtual irr::scene::ISceneNodeFactory* getDefaultSceneNodeFactory() { return this->pDefaultSceneNodeFactory; }
        //! Get the Default GeometryCreator
        virtual const irr::scene::IGeometryCreator* getDefaultGeometryCreator() { return this->pDefaultGeometryCreator; }
        //! Get SceneLoader
        virtual irr::scene::ISceneLoader* getDefaultSceneLoader() { return this->pDefaultSceneLoader; }

    protected:
        // Pointer to the IrrlichtDevice
        irr::IrrlichtDevice* pIrrlichtDevice;
        // Pointer to the IrrlichtDriver
        irr::video::IVideoDriver* pVideoDriver;
        // Pointer to the SceneManager
        irr::scene::ISceneManager* pSceneManager;
        // Pointer to the GUIEnvironment
        irr::gui::IGUIEnvironment* pGUIEnvironment;
        // Pointer the GUISKin
        irr::gui::IGUISkin* pSkin;
        // Pointer to the FileSystem
        irr::io::IFileSystem* pFileSystem;
        // Pointer to the CursorControl
        irr::gui::ICursorControl* pCursorControl;
        // Pointer to the EventReceiver
        irr::IEventReceiver* pEventReceiver;
        // Pointer to the Scene Collision Manager
        irr::scene::ISceneCollisionManager* pSceneCollisionManager;
        // Pointer to the Logger
        irr::ILogger* pLogger;
        // Pointer to the GPU
        irr::video::IGPUProgrammingServices* pGPUProgrammingServices;
        // Pointer to the Mesh Manipulator
        irr::scene::IMeshManipulator* pMeshManipulator;
        // Pointer to the Default GeometryCreator
        const irr::scene::IGeometryCreator* pDefaultGeometryCreator;
        // Pointer to the Default SceneLoader
        irr::scene::ISceneLoader* pDefaultSceneLoader;
        // Pointer to the Default SceneNodeAnimatorFactory
        irr::scene::ISceneNodeAnimatorFactory* pDefaultSceneNodeAnimatorFactory;
        // Pointer to the Default SceneNodeFacotry
        irr::scene::ISceneNodeFactory* pDefaultSceneNodeFactory;

    // ******************
    // * IEVENTRECIEVER *
    // ******************
    // NOTE: This section handles input messages sent by the Operating System

    public:
        //! Callback to handle all Irrlicht events
        virtual bool OnEvent(const irr::SEvent& event);
        //! Function which handles keyboard events
        virtual void keyboardEvent(const irr::SEvent& event);
        //! Function which handles mouse events
        virtual void mouseEvent(const irr::SEvent& event);
        //! Function which handles mouse events
        virtual void mouseGUIEvent(const irr::SEvent& event);

    protected:
        // Members and methods

    // ******************************
    // * ISHADERCONSTANTSETCALLBACK *
    // ******************************
    /* NOTE: Irrlicht Provides two call backs one for when the material changes (OnSetMaterial)
        then the other when it passes variables to the shaders (OnSetConstants).*/

    public:
        //! This function is called by Irrlicht when setting the material for a shader to use
        virtual void OnSetMaterial(const irr::video::SMaterial& material);
        //! OnSetConstants
        virtual void OnSetConstants(irr::video::IMaterialRendererServices* pServices, irr::s32 userData);

    protected:
        // A local reference for the current material in use by the shader
        const irr::video::SMaterial* pShaderMaterial;

    // **********
    // * TIMING *
    // **********
    /* NOTE: This section provides access to the GameTimer, Frames Per Second, Renders per Second and also limits the frame rate */
    public:
        //! Get Timer
        virtual Timer* getGameTimer() { return &(this->gameTimer); }
        //! Get frames per second
        virtual float getFPS() { return this->fpsCounter.getFPS(); }
        //! Get the renders per second
        virtual float getRPS() { return this->rpsCounter.getFPS(); }
        //! Get the desired FPS
        virtual float getDesiredFPS() { return this->desiredFPS; }
        //! Set the desired FPS
        virtual void setDesiredFPS(float value) { this->desiredFPS = value; }
        //! Is the frame rate being limited
        virtual bool isLimitFramesPerSecond() { return this->limitFramesPerSecond; }
        //! Toggle frame rate limiter
        virtual void setLimitFramesPerSecond(bool state) { this->limitFramesPerSecond = state; }

    protected:
        // Game timer
        Timer gameTimer;
        // Frame timer
        Timer frameTimer; /* NOTE: DO NOT PROVIDE EXTERNAL ACCESS, QUERY THE TICKS OR STOP THIS TIMER, IT WILL CRASH THE PROGRAM, THIS IS OUR FRAME RATE CONTROLLING TIMER */
        // Frames Per Second
        FrameCounter fpsCounter;
        // Renders Per Second
        FrameCounter rpsCounter;
        // Keep track of the desired frame rate
        float desiredFPS;
        // The current time of update
        double now;
        // The last time update was called
        double then;
        // Accumulator between update calls
        float accumulator;
        // Toggle for the frame rate limiter
        bool limitFramesPerSecond;

    // ********************
    // * LIGHT MANAGEMENT *
    // ********************
    /* NOTE: This section is the backend for the Irrlicht Light manager */
    /* TODO: Ok, so this is how things need to work, we need to sort and build lists of ONLY
        the lights visible on the screen (based on attenuation and position ect)
        that way we can optimise our deferred lighting model */

    public:
        /* TODO: For everyframe we need to add/remove lights from nodes inside a quadtree because
            some lights might have moved in the last frame */
        //! Called after the scene's light list has been built, but before rendering has begun.
        /** As actual device/hardware lights are not created until the
        ESNRP_LIGHT render pass, this provides an opportunity for the
        light manager to trim or re-order the light list, before any
        device/hardware lights have actually been created.
        \param lightList: the Scene Manager's light list, which
        the light manager may modify. This reference will remain valid
        until OnPostRender().
        */
        virtual void OnPreRender(irr::core::array<irr::scene::ISceneNode*>& lightList);
        //! Called after the last scene node is rendered.
        /** After this call returns, the lightList passed to OnPreRender() becomes invalid. */
        virtual void OnPostRender();
        //! Called before a render pass begins
        /** \param renderPass: the render pass that's about to begin */
        virtual void OnRenderPassPreRender(irr::scene::E_SCENE_NODE_RENDER_PASS renderPass);
        //! Called after the render pass specified in OnRenderPassPreRender() ends
        /** \param[in] renderPass: the render pass that has finished */
        virtual void OnRenderPassPostRender(irr::scene::E_SCENE_NODE_RENDER_PASS renderPass);
        //! Called before the given scene node is rendered
        /** \param[in] node: the scene node that's about to be rendered */
        virtual void OnNodePreRender(irr::scene::ISceneNode* node);
        //! Called after the the node specified in OnNodePreRender() has been rendered
        /** \param[in] node: the scene node that has just been rendered */
        virtual void OnNodePostRender(irr::scene::ISceneNode* node);

    protected:
        // List of Directional Lights
        std::vector<irr::scene::ILightSceneNode*> directionalLights;
        // List of Point Lights
        std::vector<irr::scene::ILightSceneNode*> pointLights;
        // List of Spot Lights
        std::vector<irr::scene::ILightSceneNode*> spotLights;
        // Temporary List of Directional Lights affecting a scene node (no access is provided to this list its used internally to the shader setup)
        std::vector<irr::scene::ILightSceneNode*> tempDirectionalLights;
        // Temporary List of Point Lights affecting a scene node (no access is provided to this list its used internally to the shader setup)
        std::vector<irr::scene::ILightSceneNode*> tempPointLights;
        // Temporary List of Spot Light saffecting a scene node (no access is provided to this list its used internally to the shader setup)
        std::vector<irr::scene::ILightSceneNode*> tempSpotLights;

    // **********
    // * CAMERA *
    // **********

    public:
        //! Get Camera
        virtual irr::scene::ICameraSceneNode* getCamera() { return this->pSceneManager->getActiveCamera(); }

    protected:
        // Methods and members

    // *********************
    // * WINDOW MANAGEMENT *
    // *********************
    /* NOTE: This section provides support for controlling the window caption and window state */
    public:
        //! Get Window Caption
        virtual std::wstring getWindowCaption() { return this->windowCaption.c_str(); }
        //! Set Window Caption
        virtual void setWindowCaption(irr::core::stringw text) { this->windowCaption = text; this->pIrrlichtDevice->setWindowCaption(text.c_str()); }
        //! Is the Window Fullscreen
        virtual bool isWindowFullScreen() { return this->pIrrlichtDevice->isFullscreen(); }
        //! SetFullScreen
        virtual void setWindowFullscreen(bool value);
        //! Is the Window Active
        virtual bool isWindowActive() { return this->pIrrlichtDevice->isWindowActive(); }
        //! Is the Window Minimised
        virtual bool isWindowMinimised() { return this->pIrrlichtDevice->isWindowMinimized(); }
        //! Minimise the Window
        virtual void minimiseWindow() { this->pIrrlichtDevice->minimizeWindow(); }
        //! Is the Window Maximised
        virtual bool isWindowMaximised() { return !(this->pIrrlichtDevice->isWindowMinimized()); }
        //! Maximise the Window
        virtual void maximiseWindow() { this->pIrrlichtDevice->maximizeWindow(); }
        //! Restore the Window
        virtual void restoreWindow() { this->pIrrlichtDevice->restoreWindow(); }
        //! Screenshot
        virtual bool screenShot();
        //! Get ResolutionX
        virtual int getResolutionX() { return this->xResolution; }
        //! Get ResolutionY
        virtual int getResolutionY() { return this->yResolution; }
        //! Set Resolution
        virtual void setResolution(int xResolution, int yResolution);

    protected:
        // Local reference to the window caption
        irr::core::stringw windowCaption;
        // Horizontal Resolution
        int xResolution;
        // Vertical Resolution
        int yResolution;

    // ****************
    // * INPUT SYSTEM *
    // ****************
    public:
        //! Get InputSystem
        virtual InputSystem* getInputSystem() { return &(this->inputSystem); }

    protected:
        // InputSystem
        InputSystem inputSystem;

    // ***********
    // * SHADERS *
    // ***********

    public:
        /* UserData set to 1 if youve added custom parameters to
            your shader. All SMaterials that use your shader are
            there after required to a custom data instance class
            to it */
        //! Load Shader
        virtual irr::s32 loadShader(std::string vertexShader, std::string fragmentShader, irr::video::E_MATERIAL_TYPE baseType = irr::video::EMT_SOLID, irr::s32 userData = 0);

    protected:
        // Methods and memebers

    // *****************
    // * CONFIGURATION *
    // *****************

    public:
        // Config stuff

    protected:
        // FullScreen
        bool fullScreenFlag;

    // ****************
    // * CLEAR COLOUR *
    // ****************
    /* NOTE: This section exposes the clear color to clients */
    public:
        //! Get Clear Color
        virtual irr::video::SColor& getClearColour() { return this->clearColor; }

    protected:
        // Clear Color
        irr::video::SColor clearColor;

    // ********************
    // * BACKGROUND COLOR *
    // ********************
    /* NOTE: This section is in addition to the clear colour section and allows a solid background quad
        after we clear the screen along with background gradients */
    // SINGLE COLOR BACKGROUND
    public:
        //! Get Clear Color Red
        virtual unsigned int getClearColorRed() { return this->clearColor.getRed(); }
        //! Get Clear Color Green
        virtual unsigned int getClearColorGreen() { return this->clearColor.getGreen(); }
        //! Get Clear Color Blue
        virtual unsigned int getClearColorBlue() { return this->clearColor.getBlue(); }
        //! Get Clear Color Alpha
        virtual unsigned int getClearColorAlpha() { return this->clearColor.getAlpha(); }
        //! Set Clear Color
        virtual void setClearColor(irr::video::SColor clearColor) { this->clearColor = clearColor; }
        //! Set Clear Color
        virtual void setClearColor(int red, int green, int blue, int alpha) { this->clearColor = irr::video::SColor(alpha, red, green, blue); }

    // TODO: We need to rename these background Gradients
    // GRADIENT BACKGROUND
    public:
        //! Clear BackgroundColour
        virtual void clearBackgroundColor()
        {
            this->backgroundMode = 0;
            this->topLeftBackgroundColor = irr::video::SColor(255, 0, 0, 0);
            this->topRightBackgroundColor = irr::video::SColor(255, 0, 0, 0);
            this->bottomLeftBackgroundColor = irr::video::SColor(255, 0, 0, 0);
            this->bottomRightBackgroundColor = irr::video::SColor(255, 0, 0, 0);
        }

        //! Get Top Left Background Colour
        virtual irr::video::SColor getTopLeftBackgroundColor() { return this->topLeftBackgroundColor; }
        //! Get Top Right Background Colour
        virtual irr::video::SColor getTopRightBackgroundColor() { return this->topRightBackgroundColor; }
        //! Get Bottom Left Background Colour
        virtual irr::video::SColor getBottomLeftBackgroundColor() { return this->bottomLeftBackgroundColor; }
        //! Get Bottom Right Background Colour
        virtual irr::video::SColor getBottomRightBackgroundColor() { return this->bottomRightBackgroundColor; }
        //! Set BackgroundColour
        virtual void setBackgroundColor(irr::video::SColor topLeftBackgroundColor, irr::video::SColor topRightBackgroundColor, irr::video::SColor bottomLeftBackgroundColor, irr::video::SColor bottomRightBackgroundColor)
        {
            this->backgroundMode = 1;
            this->topLeftBackgroundColor = topLeftBackgroundColor;
            this->topRightBackgroundColor = topRightBackgroundColor;
            this->bottomLeftBackgroundColor = bottomLeftBackgroundColor;
            this->bottomRightBackgroundColor = bottomRightBackgroundColor;
        }
        //! Set BackgroundColor
        virtual void setBackgroundColor(irr::video::SColor backgroundColor)
        {
            this->backgroundMode = 1;
            this->topLeftBackgroundColor = backgroundColor;
            this->topRightBackgroundColor = backgroundColor;
            this->bottomLeftBackgroundColor = backgroundColor;
            this->bottomRightBackgroundColor = backgroundColor;
        }

    protected:
        // Mode for the background
        int backgroundMode;
        // Top left corner colour of the 2d background box
        irr::video::SColor topLeftBackgroundColor;
        // Top Right corner colour of the 2d background box
        irr::video::SColor topRightBackgroundColor;
        // Bottom left corner colour of the 2d background box
        irr::video::SColor bottomLeftBackgroundColor;
        // Bottom Right corner colour of the 2d background box
        irr::video::SColor bottomRightBackgroundColor;
};

#endif // GAME_H
