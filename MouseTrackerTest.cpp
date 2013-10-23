#include "igstkMouseTracker.h"
#include "igstkMouseTrackerTool.h"
#include "igstkTransformObserver.h"

int main(int argc, char *argv[])
{

    typedef igstk::MouseTracker TrackerType;
    typedef igstk::MouseTrackerTool ToolType;
    typedef ToolType::TransformType TransformType;
    typedef igstk::TransformObserver ObserverType;

    TrackerType::Pointer tracker = TrackerType::New();

    tracker->RequestOpen();
    tracker->SetScaleFactor(100.0);

    ToolType::Pointer trackerTool = ToolType::New();
    std::string mouseName = "Mouse compatible con HID";
    trackerTool->RequestSetMouseName(mouseName);
    trackerTool->RequestConfigure();
	trackerTool->RequestAttachToTracker(tracker);

    ObserverType::Pointer observer = ObserverType::New();
    observer->ObserveTransformEventsFrom(trackerTool);

    tracker->RequestStartTracking();

	typedef ::itk::Vector<double, 3>    VectorType;

    while(true)
    {
        igstk::PulseGenerator::CheckTimeouts();

        TransformType             transform;
        VectorType                position;

        observer->Clear();
        trackerTool->RequestGetTransformToParent();
        if (observer->GotTransform())
          {
          transform = observer->GetTransform();
          position = transform.GetTranslation();
          std::cout << "Trackertool :"
                  << trackerTool->GetTrackerToolIdentifier()
                  << "\t\t  Position = (" << position[0]
                  << "," << position[1] << "," << position[2]
                  << ")" << std::endl;
          }
		else
			std::cout<<"not";

    }


}
