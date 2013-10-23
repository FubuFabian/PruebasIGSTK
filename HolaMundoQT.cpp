/*=========================================================================

  Program:   Image Guided Surgery Software Toolkit
  Module:    $RCSfile: HelloWorld.cxx,v $
  Language:  C++
  Date:      $Date: 2011-02-04 20:05:03 $
  Version:   $Revision: 1.26 $

  Copyright (c) ISC  Insight Software Consortium.  All rights reserved.
  See IGSTKCopyright.txt or http://www.igstk.org/copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#if defined(_MSC_VER)
//Warning about: identifier was truncated to '255' characters
//in the debug information (MVC6.0 Debug)
#pragma warning( disable : 4284 )
#endif

#include <QtGui/QApplication>
#include <QtTest/QTest>
// BeginLatex
//
// To add a graphical user interface to the application, we use FLTK.
// FLTK is a light weight cross-platform GUI toolkit.
// FLTK stores a description of an interface in files with extension .fl.
// The FLTK tool \emph{fluid} takes this file and uses it for generating C++
// code in two files: one header file with extension .h, and an implementation
// file with extension .cxx. In order to use the GUI from the main program of
// our application, we must include the header file generated by \emph{fluid}.
// This is done as follows:.
//
// EndLatex

// BeginCodeSnippet
#include "HolaMundoQTGUI.h"
// EndCodeSnippet


// BeginLatex
//
// The geometrical description of the Cylinder and the Sphere in the scene are
// managed by SpatialObjects. For this purpose we need two classes,
// \doxygen{EllipsoidObject} and \doxygen{CylinderObject}. Their two header
// files are:
//
// EndLatex

#include "vtkMetaImageReader.h"

#include "vtkSmartPointer.h"

// BeginCodeSnippet
#include "igstkEllipsoidObject.h"
#include "igstkUSProbeObject.h"
#include "igstkAxesObject.h"
#include "igstkNeedleObject.h"
// EndCodeSnippet

// BeginLatex
//
// The visual representation of SpatialObjects in the visualization window is
// created using SpatialObject Representation classes.
// Every SpatialObject has one or several representation objects
// associated with it. Here we include the header files
// of the \doxygen{EllipsoidObjectRepresentation} and
// \doxygen{CylinderObjectRepresentation}:
//
// EndLatex

// BeginCodeSnippet
#include "igstkEllipsoidObjectRepresentation.h"
#include "igstkUSProbeObjectRepresentation.h"
#include "igstkAxesObjectRepresentation.h"
#include "igstkNeedleObjectRepresentation.h"
// EndCodeSnippet


// BeginLatex
//
// As stated above, the tracker in this minimal application is
// represented by a \doxygen{MouseTracker}. This class provides the same
// interface as a real tracking device but with the convenience of running
// based on the movement of the mouse in the screen. The header file for this
// class is as follows:
//
// EndLatex

// BeginCodeSnippet
#include "igstkPolarisTracker.h"
#include "igstkPolarisTrackerTool.h"
#include "PolarisTracker.h"
// EndCodeSnippet


// BeginLatex
//
// Since image-guided surgery applications are used in a safety-critical
// environment, it is important to be able to trace the behavior of the
// application during the intervention. For this purpose, IGSTK uses a
// \doxygen{Logger} class and some helpers. The logger is a class that receives
// messages from IGSTK classes and forwards those messages to LoggerOutput
// classes. Typical logger output classes are the standard output, a file, and
// a popup window. The Logger classes and their helpers are taken from the
// Insight Toolkit (ITK):
//
// EndLatex

// BeginCodeSnippet
#include "igstkLogger.h"
#include "itkStdStreamLogOutput.h"
// EndCodeSnippet
//
#include "igstkTransformObserver.h"

#include <QString.h>

// BeginLatex
//
// We are now ready to write the code of the actual application. Of course, we
// start with the classical \code{main()} function:
//
// EndLatex

// BeginCodeSnippet
int main(int argc, char *argv[])
{

	QApplication app(argc, argv);
  // EndCodeSnippet

  // BeginLatex
  // The first IGSTK command to be invoked in an application is the one that
  // initializes the parameters of the clock. Timing is critical for all
  // operations performed in an IGS application. Timing signals make it possible
  // to synchronize the operation of different components and to ensure that the
  // scene rendered on the screen actually displays a consistent
  // state of the environment on the operating room. The command for the timer
  // initialization is as follows:
  // EndLatex
  //
  // BeginCodeSnippet
  igstk::RealTimeClock::Initialize();
  // EndCodeSnippet

  // BeginLatex
  // First, we instantiate the GUI application:
  // EndLatex
  //
  // BeginCodeSnippet
  HolaMundoQTGUI * m_GUI = new HolaMundoQTGUI();
  m_GUI->fileName = "igstkHelloWorld.dot";
  // EndCodeSnippet
  //

  // BeginLatex
  // Next, we instantiate the ellipsoidal spatial object that we will be
  // attaching to the tracker:
  // EndLatex

  // Create the ellipsoid
  // BeginCodeSnippet
  igstk::EllipsoidObject::Pointer ellipsoid = igstk::EllipsoidObject::New();
  // EndCodeSnippet
  #ifdef IGSTK_USE_SceneGraphVisualization
  ellipsoid->RequestSetCoordinateSystemName("MouseCursor");
  #endif
  //
  // BeginLatex
  // The ellipsoid radius can be set to one in all dimensions ( X, Y, and Z )
  // using the \code{SetRadius} member function, as follows:
  // EndLatex
  // BeginCodeSnippet
  ellipsoid->SetRadius(5,5,5);

  igstk::AxesObject::Pointer axes = igstk::AxesObject::New();
  axes->SetSize(50,50,50);

  // EndCodeSnippet

  // BeginLatex
  // To visualize the ellipsoid spatial object, an object representation
  // class is created and the ellipsoid spatial object is added to it,
  // as follows:
  // EndLatex

  // BeginCodeSnippet
  igstk::EllipsoidObjectRepresentation::Pointer
        ellipsoidRepresentation = igstk::EllipsoidObjectRepresentation::New();
  ellipsoidRepresentation->RequestSetEllipsoidObject( ellipsoid );
  ellipsoidRepresentation->SetColor(0.0,1.0,0.0);
  ellipsoidRepresentation->SetOpacity(1.0);
  // EndCodeSnippet

  igstk::AxesObjectRepresentation::Pointer axesRepresentation = igstk::AxesObjectRepresentation::New();
  axesRepresentation->RequestSetAxesObject(axes);
  // BeginLatex
  // Similarly, a cylinder spatial object and cylinder spatial object
  // representation object are instantiated, as follows:
  // EndLatex


  // BeginCodeSnippet
 igstk::NeedleObject::Pointer cylinder = igstk::NeedleObject::New();


  // Add the position of the cylinder with respect to the View.
  igstk::Transform transform;
  transform.SetToIdentity( igstk::TimeStamp::GetLongestPossibleTime() );
  cylinder->RequestSetTransformAndParent( transform, m_GUI->View );
  cylinder->RequestSetTransformAndParent( transform, m_GUI->View2 );
  cylinder->RequestSetTransformAndParent( transform, m_GUI->View3 );
  cylinder->RequestSetTransformAndParent( transform, m_GUI->View4 );
  axes->RequestSetTransformAndParent( transform, m_GUI->View );
  axes->RequestSetTransformAndParent( transform, m_GUI->View2 );
  axes->RequestSetTransformAndParent( transform, m_GUI->View3 );
  axes->RequestSetTransformAndParent( transform, m_GUI->View4 );


  igstk::NeedleObjectRepresentation::Pointer
          cylinderRepresentation = igstk::NeedleObjectRepresentation::New();
  cylinderRepresentation->RequestSetNeedleObject( cylinder );
  cylinderRepresentation->SetColor(1.0,0.0,0.0);
  cylinderRepresentation->SetOpacity(1.0);
  // EndCodeSnippet

  vtkMetaImageReader * reader = vtkMetaImageReader::New();
  QString filename = "C:/Users/Administrador/Documents/Volume Reconstruction/volumenes/5x1 Hamster A2-subvolume-scale_1.mhd";
	reader->SetFileName(filename.toAscii().data());
    reader->Update();

	/*igstk::USImageObject::Pointer usVolume = igstk::USImageObject::New();
	usVolume->volumeData = reader->GetOutput();

	igstk::ImageSpatialObjectVolumeRepresentation<igstk::USImageObject>::Pointer volumeRepresentation =
		igstk::ImageSpatialObjectVolumeRepresentation<igstk::USImageObject>::New();
	volumeRepresentation->RequestSetImageSpatialObject(usVolume);*/


  // BeginLatex
  // Next, the spatial objects are added to the view as follows:
  //
  //
  // EndLatex
  // BeginCodeSnippet
  m_GUI->View->RequestAddObject( ellipsoidRepresentation );
  m_GUI->View2->RequestAddObject( ellipsoidRepresentation->Copy() );
  m_GUI->View3->RequestAddObject( ellipsoidRepresentation->Copy() );
  m_GUI->View4->RequestAddObject( ellipsoidRepresentation->Copy() );

  m_GUI->View->RequestAddObject( cylinderRepresentation );
  m_GUI->View2->RequestAddObject( cylinderRepresentation->Copy() );
  m_GUI->View3->RequestAddObject( cylinderRepresentation->Copy() );
  m_GUI->View4->RequestAddObject( cylinderRepresentation->Copy() );

  m_GUI->View->RequestAddObject( axesRepresentation );
  m_GUI->View2->RequestAddObject( axesRepresentation->Copy() );
  m_GUI->View3->RequestAddObject( axesRepresentation->Copy() );
  m_GUI->View4->RequestAddObject( axesRepresentation->Copy() );
  // EndCodeSnippet

  // BeginLatex
  // Function \code{RequestEnableInteractions()} allows the user to
  // interactively manipulate (rotate, pan, zoom etc.) the camera.
  // For \doxygen{View2D} class, \code{vtkInteractorStyleImage}
  // is used; for \doxygen{View3D} class,
  // \code{vtkInteractorStyleTrackballCamera} is used. In IGSTK, the keyboard
  // events are disabled, so the original VTK
  // key-mouse-combined interactions are not supported.
  // In summary, the mouse events are as follows: left button click triggers
  // pick event; left button hold rotates the camera, in \doxygen{View3D}
  // (in \doxygen{View2D},
  // camera direction is always perpendicular to image plane, so there is no
  // rotational movement available for it); middle mouse button
  // pans the camera; and right mouse button dollies the camera.
  // EndLatex
  // BeginCodeSnippet
  m_GUI->qtDisplay->RequestEnableInteractions();
  // EndCodeSnippet

  // BeginLatex
  // The following code instantiates a new mouse tracker and initializes it.
  // The scale factor is just a number to scale down the movement of the tracked
  // object in the scene:
  // EndLatex
  // BeginCodeSnippet

  PolarisTracker* polarisTracker = PolarisTracker::New();
  std::cout<<"-Initializing Logger"<<std::endl;
  polarisTracker->initializeLogger();
  std::cout<<"-Initializing SerialCommunication"<<std::endl;
  polarisTracker->initializeSerialCommunication(3);
  std::cout<<"-Initializing Tracker"<<std::endl;
  polarisTracker->initializeTracker();
  std::cout<<"-Initializing Tracker Tool 8700340"<<std::endl;
  polarisTracker->initializeTrackerTool("8700340.rom");
  std::cout<<"-Attaching all tools"<<std::endl;
  polarisTracker->attachAllTools();
  polarisTracker->createToolsObervers();

  igstk::PolarisTracker::Pointer tracker = polarisTracker->getTracker();


  typedef igstk::PolarisTrackerTool         TrackerToolType;
  typedef TrackerToolType::TransformType    TransformType;
  typedef igstk::TransformObserver          ObserverType;

  // instantiate and attach wired tracker tool
  TrackerToolType::Pointer trackerTool = polarisTracker->getTools().at(0);

  ObserverType::Pointer coordSystemAObserver = polarisTracker->getObservers().at(0);
  coordSystemAObserver->ObserveTransformEventsFrom( trackerTool );

  // EndCodeSnippet
  //
  TransformType identityTransform;
  identityTransform.SetToIdentity(
                      igstk::TimeStamp::GetLongestPossibleTime() );
  ellipsoid->RequestSetTransformAndParent( identityTransform, trackerTool );

  #ifdef IGSTK_USE_SceneGraphVisualization
  m_GUI->View->RequestSetCoordinateSystemName("View");
  m_GUI->View2->RequestSetCoordinateSystemName("View2");
  m_GUI->View3->RequestSetCoordinateSystemName("View3");
  m_GUI->View4->RequestSetCoordinateSystemName("View4");
  #endif

  // BeginCodeSnippet
  // Attach a viewer to the tracker
  m_GUI->View->RequestSetTransformAndParent( identityTransform, tracker );
  m_GUI->View2->RequestSetTransformAndParent( identityTransform, tracker );
  m_GUI->View3->RequestSetTransformAndParent( identityTransform, tracker );
  m_GUI->View4->RequestSetTransformAndParent( identityTransform, tracker );

  m_GUI->SetTracker( tracker );
  // EndCodeSnippet

  // BeginLatex
  // Now a logger is set up. The log output is directed to both
  // the standard output (std::cout) and a file (log.txt).
  // For the usage of priority level, please refer to Chapter
  // \ref{Chapter:Logging} on page \pageref{Chapter:Logging}.
  // EndLatex
  // BeginCodeSnippet
  typedef igstk::Object::LoggerType             LoggerType;

  LoggerType::Pointer logger = LoggerType::New();
  itk::StdStreamLogOutput::Pointer logOutput = itk::StdStreamLogOutput::New();
  itk::StdStreamLogOutput::Pointer fileOutput = itk::StdStreamLogOutput::New();

  logOutput->SetStream( std::cout );
  logger->AddLogOutput( logOutput );
  logger->SetPriorityLevel( itk::Logger::DEBUG );

  std::ofstream ofs( "log.txt" );
  fileOutput->SetStream( ofs );
  logger->AddLogOutput( fileOutput );
  // EndCodeSnippet

  // BeginLatex
  // By connecting the logger to the View and the Tracker, messages from
  // these components are redirected to the logger, as follows:
  // EndLatex
  // BeginCodeSnippet
  m_GUI->qtDisplay->SetLogger( logger );
  tracker->SetLogger( logger );
  // EndCodeSnippet


  // BeginLatex
  // Next, the refresh frequency of the display window is set. The
  // \code{Show()} method of the GUI will invoke internally the
  // \code{RequestStart()} method of the View. After the \code{RequestStart()}
  // function is called, the pulse generator inside the display window will
  // start ticking, and will call the display to update itself 60 times per
  // second, as follows: EndLatex
  // BeginCodeSnippet
  m_GUI->View->SetRefreshRate( 60 );
  m_GUI->View2->SetRefreshRate( 60 );
  m_GUI->View3->SetRefreshRate( 60 );
  m_GUI->View4->SetRefreshRate( 60 );
  m_GUI->Show();
  // EndCodeSnippet

  // BeginLatex
  // Here we reset the camera position so that we can observe all objects
  // in the scene. We have deferred this call to shortly before the main
  // event loop so that all the coordinate systems have been set up.
  //
  // We need to have coordinate system connections between the view and
  // each object that we wish to display. For instance, the cylinder's
  // coordinate system is attached directly to the view. The ellipsoid,
  // however, is attached to the tracker tool. The tracker tool is attached
  // to the tracker, which has an attached view.
  // BeginCodeSnippet
  m_GUI->View->RequestResetCamera();
  m_GUI->View2->RequestResetCamera();
  m_GUI->View3->RequestResetCamera();
  m_GUI->View4->RequestResetCamera();
  // EndCodeSnippet

  // BeginLatex
  // All applications should include the following code. This is the main event
  // loop of the application. First, it checks if the application is aborted by
  // user. If not, it calls for the \doxygen{PulseGenerator} to check its time
  // out. The command is as follows:
  // EndLatex
  // BeginCodeSnippet
  //
  //

  typedef ::itk::Vector<double, 3>    VectorType;
  typedef ::itk::Versor<double>       VersorType;

  while( !m_GUI->HasQuitted() )
    {
    QTest::qWait(0.001);
    igstk::PulseGenerator::CheckTimeouts();

	TransformType             transform;
    VectorType                position;
  
    coordSystemAObserver->Clear();
    trackerTool->RequestGetTransformToParent();
    if (coordSystemAObserver->GotTransform())
      {
      transform = coordSystemAObserver->GetTransform();
      position = transform.GetTranslation();
      std::cout << "Trackertool :" 
              << trackerTool->GetTrackerToolIdentifier() 
              << "\t\t  Position = (" << position[0]
              << "," << position[1] << "," << position[2]
              << ")" << std::endl;
      }
    }
  // EndCodeSnippet


  // BeginLatex
  // Finally, before exiting the application, the tracker is properly
  // closed and other clean up procedures are executed, as follows:
  // EndLatex
  // BeginCodeSnippet
  tracker->RequestStopTracking();
  tracker->RequestClose();
  delete m_GUI;
  ofs.close();
  return EXIT_SUCCESS;
  // EndCodeSnippet

}
