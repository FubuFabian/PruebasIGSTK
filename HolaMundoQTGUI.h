#ifndef HOLAMUNDOQTGUI_H
#define HOLAMUNDOQTGUI_H

#include <QGridLayout>
#include <QMainWindow>
#include "igstkView3D.h"
#include "igstkQTWidget.h"
#include "igstkTracker.h"
#include "igstkConfigure.h"

namespace Ui {
class HolaMundoQTGUI;
}

class HolaMundoQTGUI : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit HolaMundoQTGUI(QWidget *parent = 0);
    ~HolaMundoQTGUI();

    typedef igstk::Tracker TrackerType;
    typedef TrackerType::Pointer TrackerPointer;

    igstk::QTWidget * qtDisplay;
	igstk::QTWidget * qtDisplay2;
	igstk::QTWidget * qtDisplay3;
	igstk::QTWidget * qtDisplay4;
    igstk::View3D::Pointer View;
	igstk::View3D::Pointer View2;
	igstk::View3D::Pointer View3;
	igstk::View3D::Pointer View4;
	QGridLayout *layout;
    std::string fileName;

    void Show();
    void SetTracker( TrackerType * tracker);
    bool HasQuitted();
    
private:
    Ui::HolaMundoQTGUI *ui;

    bool quit;
    TrackerPointer m_Tracker;


private slots:

    void Quit();
    void SetTracking( bool tracking);

};

#endif // HOLAMUNDOQTGUI_H
