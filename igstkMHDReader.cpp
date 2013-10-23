#include "igstkMHDReader.h"

void MHDReader::setFileName(QString fileName)
{
	reader = vtkSmartPointer<vtkMetaImageReader>::New();
     reader->SetFileName(fileName.toAscii().data());
}

vtkSmartPointer<vtkImageData> MHDReader::getOutput()
{
    return reader->GetOutput();
}

