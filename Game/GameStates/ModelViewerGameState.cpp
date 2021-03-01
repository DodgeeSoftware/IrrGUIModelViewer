#include "ModelViewerGameState.h"
#include "Game.h"

ModelViewerGameState::ModelViewerGameState(Game* pGame) : IGameState(pGame)
{
    // LIGHTING
    this->pLight = 0;
    // CAMERA
    this->pCamera = 0;
    this->cameraDistance = -30;
    cameraDistanceDelta = 1.0f;
    this->theta = 0;
    this->phi = 0;
    // GUISKIN
    this->pSkin = 0;
    // GUI
    // OpenFileDialog
    this->pOpenDialog = 0;
    // Options Window
    this->pOptionsWindow = 0;
        this->pOptionsWindow = 0;
        this->pVerticesCheckBox = 0;
        this->pWireFramesCheckBox = 0;
        this->pNormalsCheckBox = 0;
        this->pTexturesCheckBox = 0;
        this->pShadersCheckBox = 0;
        this->pVertexColoursCheckBox = 0;
        this->pFrontFaceCullCheckBox = 0;
        this->pBackFaceCullCheckBox = 0;
        this->pLightingCheckBox = 0;
        this->checkBoxVerticesFlag = false;
        this->checkBoxNormalsFlag = false;
        this->checkBoxTextureFlag = true;
        this->checkBoxShadersFlag = false;
        this->checkBoxVertexColoursFlag = true;
        this->checkBoxFrontFaceCullFlag = false;
        this->checkBoxBackFaceCullFlag = true;
        this->checkBoxWireframeFlag = false;
        this->checkBoxLightingFlag = true;
    // About Window
    this->pAboutWindow = 0;
        this->aboutWindowText = L"Model Viewer Version 0.1, (c) Dodgee Software. Authors: Shem Taylor";
//    this->pConsoleBox = 0;
//        //this->consoleBoxText.clear();
//        this->pScrollbarHorizontalConsole = 0;
//        this->pScrollbarVerticalConsole = 0;
    this->pOpenButton = 0;
    this->pReloadButton = 0;
    this->pCloseButton = 0;
    this->pOptionsButton = 0;
    this->pExitButton = 0;
    this->pAboutButton = 0;
    // MODEL
    this->pModel = 0;
    this->modelFilename.clear();
//    // MOUSE CONTROL
//    this->MouseXBufferPosition = 0.0f;
//    this->MouseYBufferPosition = 0.0f;
//    this->currentMouseX = 0.0f;
//    this->currentMouseY = 0.0f;
//    this->mouseDeltaX = 0.0f;
//    this->mouseDeltaY = 0.0f;
    // STATE STUFF
    this->allowMovement = true;
}

ModelViewerGameState::ModelViewerGameState(ModelViewerGameState& other) : IGameState(pGame)
{
    // PROTECTED COPY CONSTRUCTOR
}

ModelViewerGameState::~ModelViewerGameState()
{

}

ModelViewerGameState& ModelViewerGameState::operator=(const ModelViewerGameState& other)
{
    return *this;
}

void ModelViewerGameState::enter()
{
    // *********
    // * ENTER *
    // *********

    // Init the Background
    this->initBackground();
    // Init the Window
    this->initWindow();
    // Init the Cursor
    this->initCursor();
    // Init the Skin
    this->initSkin();
    // Init the GUI
    this->initGUI();
    // Init the Camera
    this->initCamera();
    // Init the Lighting
    this->initLighting();
    // Init the Scene
    this->initScene();
}

bool ModelViewerGameState::initBackground()
{
    // *************************
    // * INITIALISE BACKGROUND *
    // *************************

    // Set the background color
    pGame->setBackgroundColor(irr::video::SColor(255, 128, 128, 128),
                              irr::video::SColor(255, 128, 128, 128),
                              irr::video::SColor(255, 15, 15, 15),
                              irr::video::SColor(255, 15, 15, 15));

    // Success
    return true;
}

bool ModelViewerGameState::initWindow()
{
    // *********************
    // * INITIALISE WINDOW *
    // *********************

    // Set Default Caption
    this->defaultCaption();

    // Success
    return true;
}

bool ModelViewerGameState::initCursor()
{
    // *********************
    // * INITIALISE CURSOR *
    // *********************

    // Show the mouse
    pGame->getInputSystem()->getMouse()->setVisible(true);

    // Success
    return true;
}

bool ModelViewerGameState::initSkin()
{
    // *******************
    // * INITIALISE SKIN *
    // *******************

    // Globals
    irr::gui::IGUISkin* pSkin = pGame->getGUIEnvironment()->getSkin();

    // Add a smooth fade to the buttons
    for (int i = 0; i < irr::gui::EGDC_COUNT; i++)
    {
        irr::video::SColor colour = pSkin->getColor((irr::gui::EGUI_DEFAULT_COLOR)i);
            colour.setAlpha(0xFF);
        pSkin->setColor((irr::gui::EGUI_DEFAULT_COLOR)i, colour);
    }

    // Success
    return true;
}


bool ModelViewerGameState::initGUI()
{
    // **********************
    // * INITIALISE THE GUI *
    // **********************

    // GLOBALS
    irr::video::IVideoDriver* pVideoDriver = pGame->getVideoDriver();
    irr::gui::IGUISkin* pSkin = pGame->getGUIEnvironment()->getSkin();
    irr::gui::IGUIEnvironment* pGUIEnvironment = pGame->getGUIEnvironment();
    irr::core::dimension2d<irr::u32> screenSize = pGame->getVideoDriver()->getScreenSize();

    // Build NavigationBar
    this->buildNavigationBar();
    this->buildOptions();
//    this->buildConsole();

    // Success
    return true;
}

bool ModelViewerGameState::initCamera()
{
    // ***************
    // * INIT CAMERA *
    // ***************

    this->makeDefaultCamera();

    // Success
    return true;
}

bool ModelViewerGameState::initLighting()
{
    // ***********************
    // * INITIALISE LIGHTING *
    // ***********************

    this->makeDefaultLight();

    // Success
    return true;
}

bool ModelViewerGameState::initScene()
{
    // ********************
    // * INITIALISE SCENE *
    // ********************

    //pCamera->setPosition(this->pModel->getPosition() + irr::core::vector3df(0.0f, 0.0f, 500.0f));
    //pGame->getSceneManager()->addCubeSceneNode()->setPosition(irr::core::vector3df(0.0f, 0.0f, 0.0f));

    //this->pModel = pGame->getSceneManager()->addAnimatedMeshSceneNode(pGame->getSceneManager()->getMesh("media/meshes/biggun.x"));

    // Success
    return true;
}

bool ModelViewerGameState::buildNavigationBar()
{
    // GLOBALS
    irr::video::IVideoDriver* pVideoDriver = pGame->getVideoDriver();
    irr::gui::IGUISkin* pSkin = pGame->getGUIEnvironment()->getSkin();
    irr::gui::IGUIEnvironment* pGUIEnvironment = pGame->getGUIEnvironment();
    irr::core::dimension2d<irr::u32> screenSize = pGame->getVideoDriver()->getScreenSize();

    // BUILD NAVIGATION BAR
    // Navigation Button IDs
    this->guiComponentID["FILE_OPEN_BUTTON"] = 101;
    this->guiComponentID["OPTIONS_BUTTON"] = 102;
    this->guiComponentID["CLOSE_BUTTON"] = 103;
    this->guiComponentID["RELOAD_BUTTON"] = 104;
    this->guiComponentID["ABOUT_BUTTON"] = 105;
    this->guiComponentID["EXIT_BUTTON"] = 106;

    //screenSize
    int buttonCount = 6;
    float idealButtonWidth = 100;
    float idealButtonHeight = 32;
    if (((float)screenSize.Width / 6.0f) < idealButtonWidth)
    {
        idealButtonWidth = ((float)screenSize.Width / 6.0f);
    }

    float startX = (((float)screenSize.Width) / 2.0f) - ((float)buttonCount / 2.0f) * idealButtonWidth;
    float startY = screenSize.Height - idealButtonHeight;

    // Add the OpenButton
    this->pOpenButton = pGUIEnvironment->addButton(irr::core::rect<irr::s32>(startX + 0 * idealButtonWidth, startY, startX + 0 * idealButtonWidth + idealButtonWidth, startY + idealButtonHeight), 0, this->guiComponentID["FILE_OPEN_BUTTON"], L"Open", L"Open File");
    // Add the OptionsButton
    this->pOptionsButton = pGUIEnvironment->addButton(irr::core::rect<irr::s32>(startX + 1 * idealButtonWidth, startY, startX + 1 * idealButtonWidth + idealButtonWidth, startY + idealButtonHeight), 0, this->guiComponentID["OPTIONS_BUTTON"], L"Options", L"Change View Settings");
    // Add the CloseButton
    this->pCloseButton = pGUIEnvironment->addButton(irr::core::rect<irr::s32>(startX + 2 * idealButtonWidth, startY, startX + 2 * idealButtonWidth + idealButtonWidth, startY + idealButtonHeight), 0, this->guiComponentID["CLOSE_BUTTON"], L"Close", L"Close File");
    // Add the ReloadButton
    this->pReloadButton = pGUIEnvironment->addButton(irr::core::rect<irr::s32>(startX + 3 * idealButtonWidth, startY, startX + 3 * idealButtonWidth + idealButtonWidth, startY + idealButtonHeight), 0, this->guiComponentID["RELOAD_BUTTON"], L"Reload", L"Reloads File");
    // Add the AboutButton
    this->pAboutButton = pGUIEnvironment->addButton(irr::core::rect<irr::s32>(startX + 4 * idealButtonWidth, startY, startX + 4 * idealButtonWidth + idealButtonWidth, startY + idealButtonHeight), 0, this->guiComponentID["ABOUT_BUTTON"], L"About", L"About");
    // Add the ExitButton
    this->pExitButton = pGUIEnvironment->addButton(irr::core::rect<irr::s32>(startX + 5 * idealButtonWidth, startY, startX + 5 * idealButtonWidth + idealButtonWidth, startY + idealButtonHeight), 0, this->guiComponentID["EXIT_BUTTON"], L"Exit", L"Exit");

    // success
    return true;
}

void ModelViewerGameState::makeDefaultLight()
{
    // LightData
    irr::video::SLight lightData;

    // Set Ambient Light
    pGame->getSceneManager()->setAmbientLight(irr::video::SColor(0xFF, 0x19, 0x19, 0x19));
    // Set Shadow Colour
    pGame->getSceneManager()->setShadowColor(irr::video::SColor(0x00, 0x00, 0x00, 0xFF));

    // Create a directional light
    lightData = irr::video::SLight();
    pLight = pGame->getSceneManager()->addLightSceneNode();
        lightData.Type = irr::video::ELT_DIRECTIONAL;
        lightData.DiffuseColor = irr::video::SColorf(.23f, .23f, 0.25f, 1.0f);
        lightData.SpecularColor = irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f);
        pLight->setLightData(lightData);
        pLight->setRotation(irr::core::vector3df(0.0f, 90.0f - 45, -45.0f + -45.0f));
}

void ModelViewerGameState::makeDefaultCamera()
{
    // Make the Camera
    this->pCamera = pGame->getSceneManager()->addCameraSceneNode();
        this->pCamera->bindTargetAndRotation(true);
        this->pCamera->setPosition(irr::core::vector3df(0.0f, 0.0f, this->cameraDistance));
        this->pCamera->setFarValue(100000.0f);
        this->pCamera->setNearValue(0.01f);
        pGame->getSceneManager()->setActiveCamera(this->pCamera);

    this->cameraDistance = -30.0f;
    this->cameraDistanceDelta = 1.0f;
}

bool ModelViewerGameState::openModel(std::string filename)
{
    // Validate filename
    if (filename.size() == 0)
        return false;

    // Try and load the Mesh
    irr::scene::IAnimatedMesh* pAnimatedMesh = pGame->getSceneManager()->getMesh(filename.c_str());
    // If we loaded the model
    if (pAnimatedMesh != 0)
    {
        // Clear the scene
        pGame->getSceneManager()->clear();
        // Remake the default camera
        this->makeDefaultCamera();
        // Remake the default lighting
        this->makeDefaultLight();
        // Add the new mesh to the scene as a scenenode
        this->pModel = pGame->getSceneManager()->addAnimatedMeshSceneNode(pAnimatedMesh);
            this->pModel->setPosition(irr::core::vector3df(0.0f, 0.0f, 0.0f));
            this->pModel->setScale(irr::core::vector3df(1.0f, 1.0f, 1.0f));
            this->pModel->setRotation(irr::core::vector3df(0.0f, 0.0f, 0.0f));
            this->modelFilename = filename;
    }
    else
    {
        // Clear the scene
        pGame->getSceneManager()->clear();

        // Remake the default camera
        this->makeDefaultCamera();
        // Remake the default lighting
        this->makeDefaultLight();

        this->pModel = (irr::scene::IAnimatedMeshSceneNode*) pGame->getSceneManager()->addEmptySceneNode();
            this->pModel->setPosition(irr::core::vector3df(0.0f, 0.0f, 0.0f));
            this->pModel->setScale(irr::core::vector3df(1.0f, 1.0f, 1.0f));
            this->pModel->setRotation(irr::core::vector3df(0.0f, 0.0f, 0.0f));
            this->modelFilename.clear();
    }

    this->pModel->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, this->checkBoxBackFaceCullFlag);
    this->pModel->setMaterialFlag(irr::video::EMF_FRONT_FACE_CULLING, this->checkBoxFrontFaceCullFlag);
    this->pModel->setMaterialFlag(irr::video::EMF_POINTCLOUD, this->checkBoxVerticesFlag);
    this->pModel->setMaterialFlag(irr::video::EMF_LIGHTING, this->checkBoxLightingFlag);
    this->pModel->setMaterialFlag(irr::video::EMF_WIREFRAME, this->checkBoxWireframeFlag);
    this->pModel->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);

    // Set the window caption
    this->setCaption(filename);
    // Position the camera so that it can see thewhole model and reset the rotation
    this->cameraDistance = -this->pModel->getBoundingBox().MaxEdge.getLength() * 2.0f;
    this->cameraDistanceDelta = this->cameraDistance / 10.0f;
    this->theta = 0.0f;
    this->phi = 0.0f;

    // Success
    return true;

}

bool ModelViewerGameState::reload()
{
    // Clear the SceneManager
    pGame->getSceneManager()->clear();
    // Clear the Mesh Cache
    pGame->getSceneManager()->getMeshCache()->clear();
    // reload the model return success status
    return this->openModel(this->modelFilename);
}

void ModelViewerGameState::closeModel()
{
    // Clear the SceneManager
    pGame->getSceneManager()->clear();
    // Clear the Mesh Cache
    pGame->getSceneManager()->getMeshCache()->clear();
    // Remake the default camera
    this->makeDefaultCamera();
    // Remake the default lighting
    this->makeDefaultLight();
    this->cameraDistance = -40.0f;
    this->cameraDistanceDelta = 1.0f;
    this->theta = 0.0f;
    this->phi = 0.0f;
    this->pModel = 0;
    // Clear the model Filename
    this->modelFilename.clear();
    // Set default caption
    this->defaultCaption();
}

void ModelViewerGameState::buildOptions()
{
    // GLOBALS
    irr::video::IVideoDriver* pVideoDriver = pGame->getVideoDriver();
    irr::gui::IGUISkin* pSkin = pGame->getGUIEnvironment()->getSkin();
    irr::gui::IGUIEnvironment* pGUIEnvironment = pGame->getGUIEnvironment();
    irr::core::dimension2d<irr::u32> screenSize = pGame->getVideoDriver()->getScreenSize();

    // Component IDs
    this->guiComponentID["OPTIONS_WINDOW"] = 201;
    this->guiComponentID["VERTICES_CHECKBOX"] = 401;
    this->guiComponentID["WIREFRAME_CHECKBOX"] = 402;
    this->guiComponentID["NORMALS_CHECKBOX"] = 403;
    this->guiComponentID["TEXTURES_CHECKBOX"] = 404;
    this->guiComponentID["SHADER_CHECKBOX"] = 405;
    this->guiComponentID["VERTEX_COLOR_CHECKBOX"] = 406;
    this->guiComponentID["FRONTFACE_CULLING_CHECKBOX"] = 407;
    this->guiComponentID["BACKFACE_CULLING_CHECKBOX"] = 408;
    this->guiComponentID["LIGHTING_CHECKBOX"] = 409;
    // TODO: Build a gui in the range 0 - 1 and scale to screenSize
    // Make the OptionsWindow
    this->pOptionsWindow = pGame->getGUIEnvironment()->addWindow(irr::core::rect<irr::s32>(20,20,620,138), false, L"Options", 0, this->guiComponentID["OPTIONS_WINDOW"]);
        // Make the Vertices CheckBox
        this->pVerticesCheckBox = pGame->getGUIEnvironment()->addCheckBox(this->checkBoxVerticesFlag, irr::core::rect<irr::s32>(10, 20, 100, 40), this->pOptionsWindow, this->guiComponentID["VERTICES_CHECKBOX"], L"Vertices");
        // Make the WireFrame CheckBox
        this->pWireFramesCheckBox = pGame->getGUIEnvironment()->addCheckBox(this->checkBoxWireframeFlag, irr::core::rect<irr::s32>(10, 40, 100, 60), this->pOptionsWindow, this->guiComponentID["WIREFRAME_CHECKBOX"], L"WireFrame");
        // Make the Normals CheckBox
        this->pNormalsCheckBox = pGame->getGUIEnvironment()->addCheckBox(this->checkBoxNormalsFlag, irr::core::rect<irr::s32>(10, 60, 100, 80),this->pOptionsWindow, this->guiComponentID["NORMALS_CHECKBOX"], L"Normals");
            this->pNormalsCheckBox->setEnabled(false);
        // Make the Textures CheckBox
        this->pTexturesCheckBox = pGame->getGUIEnvironment()->addCheckBox(this->checkBoxTextureFlag, irr::core::rect<irr::s32>(10 + 100, 20, 100 + 100, 40), this->pOptionsWindow, this->guiComponentID["TEXTURES_CHECKBOX"], L"Textures");
            this->pTexturesCheckBox->setEnabled(false);
        // Make the Shaders CheckBox
        this->pShadersCheckBox = pGame->getGUIEnvironment()->addCheckBox(this->checkBoxShadersFlag, irr::core::rect<irr::s32>(10 + 100, 40, 100 + 100, 60), this->pOptionsWindow, this->guiComponentID["SHADER_CHECKBOX"], L"Shaders");
            this->pShadersCheckBox->setEnabled(false);
        // Make the Vertex CheckBox
        this->pVertexColoursCheckBox = pGame->getGUIEnvironment()->addCheckBox(this->checkBoxVertexColoursFlag, irr::core::rect<irr::s32>(10 + 100, 60, 100 + 100, 80), this->pOptionsWindow, this->guiComponentID["VERTEX_COLOR_CHECKBOX"], L"Vertex Colours");
        // Make the FontFaceCull CheckBox
        this->pFrontFaceCullCheckBox = pGame->getGUIEnvironment()->addCheckBox(this->checkBoxFrontFaceCullFlag, irr::core::rect<irr::s32>(10 + 200, 20, 100 + 200, 40), this->pOptionsWindow, this->guiComponentID["FRONTFACE_CULLING_CHECKBOX"], L"FrontFaceCulling");
        // Make the BackFaceCull CheckBox
        this->pBackFaceCullCheckBox = pGame->getGUIEnvironment()->addCheckBox(this->checkBoxBackFaceCullFlag, irr::core::rect<irr::s32>(10 + 200,40, 100 + 200, 60), this->pOptionsWindow, this->guiComponentID["BACKFACE_CULLING_CHECKBOX"], L"BackFaceCulling");
        // Make the Lighting CheckBox
        this->pLightingCheckBox = pGame->getGUIEnvironment()->addCheckBox(this->checkBoxLightingFlag, irr::core::rect<irr::s32>(10 + 300, 20, 100 + 300, 40), this->pOptionsWindow, this->guiComponentID["LIGHTING_CHECKBOX"], L"Lighting");

    this->pOptionsWindow->setVisible(false);
}

void ModelViewerGameState::showOptions()
{
    if (this->pOptionsWindow != 0)
        this->pOptionsWindow->setVisible(true);
}

void ModelViewerGameState::hideOptions()
{
    if (this->pOptionsWindow != 0)
        this->pOptionsWindow->setVisible(false);
}

void ModelViewerGameState::quit()
{
    // Quit the Framework
    pGame->setRunning(false);
}

void ModelViewerGameState::showAboutWindow()
{
    // GLOBALS
    irr::video::IVideoDriver* pVideoDriver = pGame->getVideoDriver();
    irr::gui::IGUISkin* pSkin = pGame->getGUIEnvironment()->getSkin();
    irr::gui::IGUIEnvironment* pGUIEnvironment = pGame->getGUIEnvironment();
    irr::core::dimension2d<irr::u32> screenSize = pGame->getVideoDriver()->getScreenSize();

    // TODO: Build a gui in the range 0 - 1 and scale to screenSize

    // Show a Message Box
    this->guiComponentID["ABOUT_WINDOW"] = 10000;
    //this->pAboutWindow = pGame->getGUIEnvironment()->addMessageBox(L"About", L"Model Viewer Version 0.1, (c) Dodgee Software. Authors: Shem Taylor", true, irr::gui::EMBF_OK, 0, this->guiComponentID["ABOUT_WINDOW"]);
    this->pAboutWindow = pGame->getGUIEnvironment()->addMessageBox(L"About", this->aboutWindowText.c_str(), true, irr::gui::EMBF_OK, 0, this->guiComponentID["ABOUT_WINDOW"]);
}

void ModelViewerGameState::defaultCaption()
{
    // Set the window caption
    pGame->setWindowCaption(L"MeshFileViewer: No File Loaded");
}

void ModelViewerGameState::setCaption(std::string text)
{
    // Set the window caption
    irr::core::stringw caption = L"MeshFileViewer";
    caption += ": ";
    (text.length() > 0) ? caption += text.c_str() : caption += "No File Loaded";
    pGame->setWindowCaption(caption);
}

void ModelViewerGameState::handleEvents()
{
    // *****************
    // * HANDLE EVENTS *
    // *****************

    // Escape Key
    if (pGame->getInputSystem()->getKeyboard()->isKeyPressed(irr::KEY_ESCAPE) == true)
    {
        // Shut the engine down
        pGame->setRunning(false);
        //return;
        pGame->changeGameState("");
        // Return
        return;
    }

    // Do Orbit Camera controls
    if (this->allowMovement == true)
    {
        if (pGame->getInputSystem()->getMouse()->isScrollDown() == true)
        {
            this->cameraDistance += this->cameraDistanceDelta;
        }
        if (pGame->getInputSystem()->getMouse()->isScrollUp() == true)
        {
            this->cameraDistance -= this->cameraDistanceDelta;
        }

        if (pGame->getInputSystem()->getMouse()->isLeftButtonPressed() == true &&
            pGame->getInputSystem()->getMouse()->isLeftDrag() == false)
        {
            //std::cout << "PRE DRAG" << std::endl;
        }
        if (pGame->getInputSystem()->getMouse()->isLeftButtonPressed() == true &&
            pGame->getInputSystem()->getMouse()->isLeftDrag() == true)
        {
            //std::cout << "DRAGGING" << std::endl;
            this->theta += -pGame->getInputSystem()->getMouse()->getXRelative() * .1f;
            this->phi += -pGame->getInputSystem()->getMouse()->getYRelative() * .1f;
        }
    }

//    // HANDLE LOG EVENTS
//    for (int i = 0; i < pGame->getLogTextEventStack()->size(); i++)
//    {
//        // Grab the first event from the stack
//        irr::SEvent logTextEvent = pGame->getLogTextEventStack()->top();
//        // Remove the first item(i.e. current event being handled here) from the stack
//        pGame->getLogTextEventStack()->pop();
//        // Send a message to the console
//        std::cout << logTextEvent.LogEvent.Text << std::endl;
//        this->consoleBoxText += logTextEvent.LogEvent.Text;
//        this->consoleBoxText += "\n";
//    }
}

bool ModelViewerGameState::onEvent(const irr::SEvent& event)
{
    // ************
    // * ON EVENT *
    // ************

    // Globals
    irr::gui::IGUIEnvironment* pGUIEnvironment = pGame->getGUIEnvironment();

    if (event.EventType == irr::EET_GUI_EVENT)
    {
        // Caller ID (Number of the control which pushed this event on the stack
        irr::s32 id = event.GUIEvent.Caller->getID();
        // Handle GUI Events
        switch(event.GUIEvent.EventType)
        {
            case irr::gui::EGET_ELEMENT_FOCUS_LOST:
            {
                break;
            }
            case irr::gui::EGET_ELEMENT_FOCUSED:
            {
                break;
            }
            case irr::gui::EGET_ELEMENT_HOVERED: // When mouse hovers over a GUI component disable movement
            {
                this->allowMovement = false;
                break;
            }
            case irr::gui::EGET_ELEMENT_LEFT: // When mouse no longer hovers over a GUI component disable movement
            {
                this->allowMovement = true;
                break;
            }
            case irr::gui::EGET_ELEMENT_CLOSED: // When a window is closed
            {
                // Detect Options Window Closure
                if (id == this->guiComponentID["OPTIONS_WINDOW"])
                {
                    // Allow movement
                    this->allowMovement = true;
                }
                break;
            }
            case irr::gui::EGET_BUTTON_CLICKED: // Button Clicked
            {
                // OpenButton Clicked
                if (id == this->guiComponentID["FILE_OPEN_BUTTON"])
                {
                    std::cout << "File Open Button" << std::endl;
                    this->pOpenDialog = pGame->getGUIEnvironment()->addFileOpenDialog(L"Open Model", true, 0);
                    this->allowMovement = false;
                }
                // Options Clicked
                if (id == this->guiComponentID["OPTIONS_BUTTON"])
                {
                    if (this->pOptionsWindow->isVisible() == false)
                    {
                        this->showOptions();
                    }
                    else
                    {
                        this->hideOptions();
                    }
                }
                // Close Clicked
                if (id == this->guiComponentID["CLOSE_BUTTON"])
                {
                    std::cout << "Close Button" << std::endl;
                    // Close Model
                    this->closeModel();
                    return false;
                }
                // Reload Clicked
                if (id == this->guiComponentID["RELOAD_BUTTON"])
                {
                    std::cout << "Reload Button" << std::endl;
                    this->reload();
                }
                // About Clicked
                if (id == this->guiComponentID["ABOUT_BUTTON"])
                {
                    std::cout << "About Button" << std::endl;
                    this->showAboutWindow();
                }
                // Exit Clicked
                if (id == this->guiComponentID["EXIT_BUTTON"])
                {
                    std::cout << "Exit Button" << std::endl;
                    this->quit();
                    return false;
                }
                break;
            }
            case irr::gui::EGET_SCROLL_BAR_CHANGED:
            {
//                std::cout << "EGET_SCROLL_BAR_CHANGED" << std::endl;
//                const irr::s32 pos = ((irr::gui::IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
//                if (id == this->guiComponentID["CONSOLE_HORIZONTAL_SCROLLBAR"])
//                {
//                    std::cout << "CONSOLE_HORIZONTAL_SCROLLBAR" << std::endl;
//                    // TODO: There doesn't seem to be away to make a textbox scroll :(
//                    //this->pConsoleBox->
//                }
//                if (id == this->guiComponentID["CONSOLE_VERTICAL_SCROLLBAR"])
//                {
//                    std::cout << "CONSOLE_VERTICAL_SCROLLBAR" << std::endl;
//                    // TODO: There doesn't seem to be away to make a textbox scroll :(
//                    //this->pConsoleBox->
//                }
                break;
            }

            case irr::gui::EGET_CHECKBOX_CHANGED:
            {
                std::cout << "VERTICES_CHECKBOX" << std::endl;
                const bool checked = ((irr::gui::IGUICheckBox*)event.GUIEvent.Caller)->isChecked();
                if (id == this->guiComponentID["VERTICES_CHECKBOX"])
                {
                    std::cout << "GUI_ID_CHECKBOX_VERTICES" << std::endl;
                    if (this->pModel != 0)
                        this->pModel->setMaterialFlag(irr::video::EMF_POINTCLOUD, checked);
                    this->checkBoxVerticesFlag = checked;
                }
                if (id == this->guiComponentID["NORMALS_CHECKBOX"])
                {
                    std::cout << "NORMALS_CHECKBOX" << std::endl;
                    if (checked == true)
                        if (this->pModel != 0)
                            this->pModel->setDebugDataVisible(this->pModel->isDebugDataVisible() | irr::scene::EDS_NORMALS);
                    else
                        if (this->pModel != 0)
                            this->pModel->setDebugDataVisible(this->pModel->isDebugDataVisible() ^ irr::scene::EDS_NORMALS);
                    this->checkBoxNormalsFlag = checked;
                }
                if (id == this->guiComponentID["TEXTURES_CHECKBOX"])
                {
                    std::cout << "TEXTURES_CHECKBOX" << std::endl;
                    this->checkBoxTextureFlag = checked;
                    // TODO: Not sure how to toggle Texture
                }
                if (id == this->guiComponentID["SHADER_CHECKBOX"])
                {
                    std::cout << "SHADER_CHECKBOX" << std::endl;
                    this->checkBoxShadersFlag = checked;
                    // TODO: Not sure how to turn a shader material off ...
                }
                if (id == this->guiComponentID["VERTEX_COLOR_CHECKBOX"])
                {
                    std::cout << "VERTEX_COLOR_CHECKBOX" << std::endl;
                    this->checkBoxVertexColoursFlag = checked;
                    // TODO: Not sure how to toggle vertex colors
                    //pNode->setMaterialFlag(irr::video::EMF_, checked);
                }
                if (id == this->guiComponentID["FRONTFACE_CULLING_CHECKBOX"])
                {
                    std::cout << "FRONTFACE_CULLING_CHECKBOX" << std::endl;
                    if (this->pModel != 0)
                        this->pModel->setMaterialFlag(irr::video::EMF_FRONT_FACE_CULLING, checked);
                    this->checkBoxFrontFaceCullFlag = checked;
                }
                if (id == this->guiComponentID["BACKFACE_CULLING_CHECKBOX"])
                {
                    std::cout << "BACKFACE_CULLING_CHECKBOX" << std::endl;
                    if (this->pModel != 0)
                        this->pModel->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, checked);
                    this->checkBoxBackFaceCullFlag = checked;
                }
                if (id == this->guiComponentID["WIREFRAME_CHECKBOX"])
                {
                    std::cout << "WIREFRAME_CHECKBOX" << std::endl;
                    if (this->pModel != 0)
                        this->pModel->setMaterialFlag(irr::video::EMF_WIREFRAME, checked);
                    this->checkBoxWireframeFlag = checked;
                }
                if (id == this->guiComponentID["LIGHTING_CHECKBOX"])
                {
                    std::cout << "LIGHTING_CHECKBOX" << std::endl;
                    if (this->pModel != 0)
                        this->pModel->setMaterialFlag(irr::video::EMF_LIGHTING, checked);
                    this->checkBoxLightingFlag = checked;
                }
                break;
            }
            case irr::gui::EGET_LISTBOX_CHANGED:
            {
                break;
            }
            case irr::gui::EGET_LISTBOX_SELECTED_AGAIN:
            {
                break;
            }
            case irr::gui::EGET_FILE_SELECTED:
            {
                std::cout << "File Selected" << std::endl;
                const wchar_t* wideFilename = pOpenDialog->getFileName();
                char buffer[wcslen(wideFilename)];
                for(int i = 0; i <= wcslen(wideFilename); i++)
                    buffer[i] = 0;
                wcstombs(buffer, wideFilename, wcslen(wideFilename));
                this->openModel(buffer);
                this->allowMovement = true;
                this->pOpenDialog = 0;
                break;
            }
            case irr::gui::EGET_DIRECTORY_SELECTED:
            {
                break;
            }
            case irr::gui::EGET_FILE_CHOOSE_DIALOG_CANCELLED:
            {
                std::cout << "File Open Dialog Cancelled" << std::endl;
                this->allowMovement = true;
                this->pOpenDialog = 0;
                break;
            }
            case irr::gui::EGET_MESSAGEBOX_YES:
                break;
            case irr::gui::EGET_MESSAGEBOX_NO:
                break;
            case irr::gui::EGET_MESSAGEBOX_OK:
            {
                // If OK was clicked on the About window
                if (id == this->guiComponentID["ABOUT_WINDOW"])
                {
                    // Allow movement
                    this->allowMovement = true;
                }
                break;
            }
            case irr::gui::EGET_MESSAGEBOX_CANCEL:
            {
                // If Cancel or Close was clicked on the About window
                if (id == this->guiComponentID["ABOUT_WINDOW"])
                {
                    // Allow movement
                    this->allowMovement = true;
                }
                break;
            }
            case irr::gui::EGET_EDITBOX_ENTER:
                break;
            case irr::gui::EGET_EDITBOX_CHANGED:
                break;
            case irr::gui::EGET_EDITBOX_MARKING_CHANGED:
                break;
            case irr::gui::EGET_TAB_CHANGED:
                break;
            case irr::gui::EGET_MENU_ITEM_SELECTED:
                break;
            case irr::gui::EGET_COMBO_BOX_CHANGED:
                break;
            case irr::gui::EGET_SPINBOX_CHANGED:
                break;
            case irr::gui::EGET_TABLE_CHANGED:
                break;
            case irr::gui::EGET_TABLE_HEADER_CHANGED:
                break;
            case irr::gui::EGET_TABLE_SELECTED_AGAIN:
                break;
            case irr::gui::EGET_TREEVIEW_NODE_DESELECT:
                break;
            case irr::gui::EGET_TREEVIEW_NODE_SELECT:
                break;
            case irr::gui::EGET_TREEVIEW_NODE_EXPAND:
                break;
            case irr::gui::EGET_TREEVIEW_NODE_COLLAPSE:
                break;
            default:
                break;
        }
    }

    return true;
}

void ModelViewerGameState::think()
{
    // *********
    // * THINK *
    // *********

}

void ModelViewerGameState::update()
{
    // **********
    // * UPDATE *
    // **********

    // Grab the deltaTime
    float dTime = this->stateTimer.getDelta() / 1000.0f;

    if (this->pModel != 0)
    {
        this->pModel->setRotation(irr::core::vector3df(this->phi, this->theta, 0.0f));
        if (this->pCamera != 0)
            this->pCamera->setPosition(this->pModel->getPosition() + irr::core::vector3df(0.0f, 0.0f, this->cameraDistance));
    }


}

void ModelViewerGameState::draw()
{
    // ********
    // * DRAW *
    // ********

}

void ModelViewerGameState::drawGUI()
{
    // ************
    // * DRAW GUI *
    // ************

    // Globals
    irr::video::IVideoDriver* pVideoDriver = pGame->getVideoDriver();
    irr::core::dimension2d<irr::u32> screenSize = pGame->getVideoDriver()->getScreenSize();
}

void ModelViewerGameState::exit()
{
    // ********
    // * EXIT *
    // ********

    // BACKGROUND
    // Clear Background Color
    pGame->clearBackgroundColor();

    // SCENE
    // Clear SceneManager
    pGame->getSceneManager()->clear();
    // Clear Mesh Cache
    pGame->getSceneManager()->getMeshCache()->clear();

    // GUI
    pGame->getGUIEnvironment()->clear();

    this->cameraDistance = -30.0f;
    this->theta = 0.0f;
    this->phi = 0.0f;
    this->pModel = 0;

//    // CLEAR UP IRRLICHT BUFFERS
//    pGame->getVideoDriver()->removeAllHardwareBuffers();
//    pGame->getVideoDriver()->removeAllOcclusionQueries();
//    pGame->getVideoDriver()->removeAllTextures();
}

void ModelViewerGameState::start()
{
    // *********
    // * START *
    // *********

    // stateTimer
    this->stateTimer.start();
}

void ModelViewerGameState::stop()
{
    // ********
    // * STOP *
    // ********

    // stateTimer
    this->stateTimer.stop();

}

void ModelViewerGameState::pause()
{
    // *********
    // * PAUSE *
    // *********

    // stateTimer
    this->stateTimer.pause();
}

void ModelViewerGameState::resume()
{
    // **********
    // * RESUME *
    // **********

    // stateTimer
    this->stateTimer.resume();
}

void ModelViewerGameState::onWindowChangeResolution(int resolutionX, int resolutionY)
{

}

void ModelViewerGameState::onWindowFullScreen(bool state)
{

}

void ModelViewerGameState::onWindowReposition(int newX, int newY)
{

}

void ModelViewerGameState::onWindowResize(int newWidth, int newHeight)
{

}

void ModelViewerGameState::onWindowClose()
{

}

void ModelViewerGameState::onWindowRefresh()
{

}

void ModelViewerGameState::onWindowFocusChange(bool state)
{

}

void ModelViewerGameState::onWindowIconify(bool state)
{

}

void ModelViewerGameState::onChangeLanguageCallBack(std::string language)
{
    // ****************************
    // * ONCHANGELANGUAGECALLBACK *
    // ****************************

}
