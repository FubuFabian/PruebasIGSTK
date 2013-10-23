#ifndef POLARISTRACKER_H
#define POLARISTRACKER_H

#endif // POLARISTRACKER_H

#include <iostream>
#include <fstream>
#include <set>
#include <ctime>
#include <vector>

#include "itkCommand.h"
#include "igstkLogger.h"
#include "itkStdStreamLogOutput.h"
#include "itkVector.h"
#include "itkVersor.h"

#include "igstkSystemInformation.h"
#include "igstkSerialCommunication.h"
#include "igstkPolarisTracker.h"
#include "igstkPolarisTrackerTool.h"
#include "igstkTransform.h"
#include "igstkTransformObserver.h"

using namespace std;

class PolarisTrackerCommand : public itk::Command
{
public:
  typedef  PolarisTrackerCommand   Self;
  typedef  itk::Command                Superclass;
  typedef itk::SmartPointer<Self>      Pointer;
  itkNewMacro( Self );
protected:
  PolarisTrackerCommand() {};

public:
  void Execute(itk::Object *caller, const itk::EventObject & event)
    {
    Execute( (const itk::Object *)caller, event);
    }

  void Execute(const itk::Object * object, const itk::EventObject & event)
    {
    // don't print "CompletedEvent", only print interesting events
    if (!igstk::CompletedEvent().CheckEvent(&event) &&
        !itk::DeleteEvent().CheckEvent(&event) )
      {
      std::cout << event.GetEventName() << std::endl;
      }
    }
};


class PolarisTracker
{
public:

	typedef igstk::TrackerTool                          TrackerToolType;
    typedef igstk::PolarisTrackerTool                   PolarisToolType;
    typedef TrackerToolType::TransformType              TransformType;
    typedef ::itk::Vector<double, 3>                    VectorType;
    typedef ::itk::Versor<double>                       VersorType;
    typedef igstk::TransformObserver                    ObserverType;
    typedef igstk::Object::LoggerType                   LoggerType;
    typedef itk::StdStreamLogOutput                     LogOutputType;
    typedef igstk::SerialCommunication::PortNumberType  PortNumberType;

    static PolarisTracker *New()
    {
		return new PolarisTracker;
    }

	void attachTool(int);
	void attachAllTools();
	void createToolsObervers();
	void detachTool(int);
	void detachAllTools();
    void initializeTracker();
	void initializeTrackerTool(std::string);
    void initializeLogger();
    void initializeSerialCommunication(int);
    int	 getNumberofTools();
	void observeAllToolsTransformations();
	void startTracking();
    void stopTracking(); 
    void track(int);

	igstk::PolarisTracker::Pointer getTracker();
	vector<PolarisToolType::Pointer> getTools();
	vector<ObserverType::Pointer> getObservers();
	

private:


    PolarisTrackerCommand::Pointer			  my_command;
    igstk::PolarisTracker::Pointer            tracker;
    LoggerType::Pointer						  logger;
    LogOutputType::Pointer					  logOutput;
    LogOutputType::Pointer					  fileOutput;
    std::ofstream							  loggerFile;
    igstk::SerialCommunication::Pointer       serialComm;
    PortNumberType                            polarisPortNumber;
	vector<PolarisToolType::Pointer>		  trackerTools;
	vector<ObserverType::Pointer>			  coordSystemAObservers;
	PolarisToolType::Pointer 				  trackerTool;
	ObserverType::Pointer					  coordSystemAObserver;

    void delayNSec(int seconds);

};


