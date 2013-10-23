#include "HolaMundo_Mesh.h"
#include "HolaMundo_Mesh_GUI.h"

#include "igstkMouseTracker.h"
#include "igstkMouseTrackerTool.h"
#include "igstkTransformObserver.h"

//IGSKT typedefs
typedef igstk::MouseTracker MouseTrackerType;
typedef igstk::MouseTrackerTool MouseTrackerToolType;
typedef igstk::TransformObserver ObserverType;

Mesh mesh_object;
Image image_object;
void Display();

int main(int argc, char *  argv[]){

        igstk::RealTimeClock::Initialize(); //USED FOR SYNCRONIZATION

        mesh_object.CreateAxes();
        mesh_object.CreateMesh();

        image_object.CreateImage();

        Display();

    return 0;

}

//Display the IGSTK objects
void Display(){

    igstk::Transform transform; //INDICATES THE COORDINATION SYSTEM TO USE
    transform.SetToIdentity( igstk::TimeStamp::GetLongestPossibleTime()); //SET THE COORDINATE SYSTEM TO THE ORIGIN

    HolaMundo_Mesh_GUI * m_gui = new HolaMundo_Mesh_GUI(); //GRAFICAL INTERFACE

    m_gui->MainWindow->show(); //SHOWS THE APLICATION MAIN WINDOW

    m_gui->View->RequestAddObject(mesh_object.axesRepresentation); //ADD THE AXES VISUAL REPRESENTATION TO A SCENE
    m_gui->View->RequestAddObject(mesh_object.meshRepresentation); //ADD THE MESH VISUAL REPRESENTATION TO A SCENE
    m_gui->View->SetRendererBackgroundColor(0,0,0); //SET THE SCENE BACKGRPOUND COLOR

    m_gui->View_Image->RequestAddObject(image_object.imageRepresentation); //ADD THE IMAGE VISUAL REPRESENTATION TO ANOTHE SCENE
    m_gui->View_Image->SetRendererBackgroundColor(0,0,0);

    m_gui->Display->RequestEnableInteractions(); //ENABLE THE MOUSE AND KEYBOARD USER INTERAACTION OF THE SCENE
    m_gui->Display_Image->RequestEnableInteractions();

    mesh_object.axes->RequestSetTransformAndParent(transform, m_gui->View); //ASIGN THE POSITION FOR DISPLAYING THE OBJECT IN THE SCENE

    MouseTrackerType::Pointer tracker = MouseTrackerType::New(); //NEW MOUSE TRACKER

    tracker->RequestOpen(); //OPEN COMMUNICATION WITH THE TRACKING DEVICE
	tracker->SetScaleFactor( 100.0 );

    MouseTrackerToolType::Pointer   trackertool = MouseTrackerToolType::New(); //NEW TRACKER TOOL

    std::string mouse = "Mouse compatible con HID";
    trackertool->RequestSetMouseName(mouse); //SET THE NAME OF THE TRACKING DEVICE
    trackertool->RequestConfigure(); //ATTEMPS TO CONFIGURE THE TRACKER TOOL

    trackertool->RequestAttachToTracker(tracker); //ASIGN THE TRACKER COM TO THE TRACKER TOOL

    ObserverType::Pointer coordobserver = ObserverType::New(); //OBSERVER FOR COORDINATE SYSTEMS

    coordobserver->ObserveTransformEventsFrom(trackertool); //ASIGN THE OBSERVER TO THE TRACKER TOOL

    igstk::Transform identitytransform;
    identitytransform.SetToIdentity( igstk::TimeStamp::GetLongestPossibleTime());

    mesh_object.mesh->RequestSetTransformAndParent(identitytransform, trackertool);

    m_gui->View->RequestSetTransformAndParent(identitytransform, tracker); //ASIGN THE TRACKER TO A SCENE
	
    tracker->RequestStartTracking();

    image_object.image->RequestSetTransformAndParent(transform, m_gui->View_Image);

    m_gui->View->SetRefreshRate(100); //REFRESH FREQUENCY OF THE DISPLAY SCENE
    m_gui->View_Image->SetRefreshRate( 0.1 );
    m_gui->View_Image->RequestSetOrientation( igstk::View2D::Sagittal ); //SET THE ORIANTATION FOR DISPLAYING THE DICOM
    m_gui->Show();
    m_gui->View->RequestResetCamera(); //RESET THE CAMERA POSITION
    m_gui->View_Image->RequestResetCamera();

    while(!m_gui->HasQuitted())
    {
         Fl::wait(0.05);
         igstk::PulseGenerator::CheckTimeouts(); //FOR TRACKERS TO UPDATE

    }

    tracker->RequestStopTracking();
    tracker->RequestClose(); //CLOSE COMUNICATION WITH THE TRACKING DEVICE

    delete m_gui;

}
