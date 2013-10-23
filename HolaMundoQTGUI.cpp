#include <QBoxLayout>

#include "HolaMundoQTGUI.h"
#include "ui_HolaMundoQTGUI.h"

HolaMundoQTGUI::HolaMundoQTGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HolaMundoQTGUI)
{
    ui->setupUi(this);

    this->View = igstk::View3D::New();
	this->View2 = igstk::View3D::New();
	this->View3 = igstk::View3D::New();
	this->View4 = igstk::View3D::New();

    this->qtDisplay = new igstk::QTWidget();
    this->qtDisplay->RequestSetView( this->View );

	this->qtDisplay2 = new igstk::QTWidget();
    this->qtDisplay2->RequestSetView( this->View2 );

	this->qtDisplay3 = new igstk::QTWidget();
    this->qtDisplay3->RequestSetView( this->View3 );

	this->qtDisplay4 = new igstk::QTWidget();
    this->qtDisplay4->RequestSetView( this->View4 );

	layout = new QGridLayout;
	layout->setContentsMargins(0,0,0,0);
	//layout->setSpacing(0);
	layout->addWidget(this->qtDisplay,0,0);
	layout->addWidget(this->qtDisplay2,0,1);
	layout->addWidget(this->qtDisplay3,1,0);
	layout->addWidget(this->qtDisplay4,1,1);
	layout->setColumnStretch(0,100);
	layout->setRowStretch(0,100);
	ui->Display->setLayout(layout);

    /*QVBoxLayout *layout2 = new QVBoxLayout;
    layout2->setContentsMargins(0, 0, 0, 0);
    layout2->setSpacing(0);
    layout2->QLayout::addWidget(this->qtDisplay);
    ui->Display->setLayout(layout2);*/

    this->quit =  false;
}

HolaMundoQTGUI::~HolaMundoQTGUI()
{
    delete ui;
}

void HolaMundoQTGUI::Show()
{
    this->quit = false;
    this->show();
    this->View->RequestStart();
}

void HolaMundoQTGUI::Quit()
{
    this->View->RequestStop();
    this->quit = true;
    this->hide();
}

void HolaMundoQTGUI::SetTracking(bool tracking)
{

	layout->setColumnStretch(0,0);
	layout->setRowStretch(0,0);
    if(true)
        this->m_Tracker->RequestStartTracking();
    else
        this->m_Tracker->RequestStopTracking();

}

void HolaMundoQTGUI::SetTracker(TrackerType *tracker)
{
    this->m_Tracker = tracker;
}

bool HolaMundoQTGUI::HasQuitted()
{
    return this->quit;
}
