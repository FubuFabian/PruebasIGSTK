#ifndef HOLAMUNDO_MESH_H
#define HOLAMUNDO_MESH_H

#endif // HOLAMUNDO_MESH_H

/*
THE HEADER FILE DECALARES TWO CLASSES. CLASS MESH IS USED TO
CREATE A NEW TETRAHEDRON CELL IN IGSTK AND 3D AXES OBJECTS.
THE IMAGE CLASS IS USED TO READ A DICOM IMAGE FROM A FILE.
*/
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
//IGSTK includes
#include "igstkMeshObject.h"
#include "igstkMeshObjectRepresentation.h"
#include "igstkAxesObject.h"
#include "igstkAxesObjectRepresentation.h"
#include "igstkMRImageSpatialObject.h"
#include "igstkMRImageSpatialObjectRepresentation.h"
#include "igstkMRImageReader.h"
#include "igstkNeedleObject.h"
#include "igstkNeedleObjectRepresentation.h"
#include "igstkUSProbeObject.h"
#include "igstkUSProbeObjectRepresentation.h"

//ITK includes
#include "itkCommand.h"

class Mesh{

    //Mesh Typedefs for IGSTK
    typedef igstk::AxesObject AxesObjectType;
    typedef igstk::MeshObject MeshObjectType;
	typedef igstk::USProbeObject USObjectType;
    typedef MeshObjectType::PointType PointType;
    typedef MeshObjectType::PointsContainer PointsContainer;
    typedef igstk::MeshObjectRepresentation MeshRepresentation;
	typedef igstk::USProbeObjectRepresentation USRepresentation;
    typedef igstk::AxesObjectRepresentation AxesRepresentation;

    public:

        //Mesh IGSTK Objects

        PointType p0; //THESE ARE THE COORDINATE POINTS OF THE MESH VERTEX
        PointType p1;
        PointType p2;
        PointType p3;

        AxesObjectType::Pointer axes; //IGSTK OBJECT (USED TO CREATE THE AXES
                                      //OBJECT AND ITS PHYSICAL CHARACTERISTICS SUCH AS SIZE)

        AxesRepresentation::Pointer axesRepresentation; //AXES REPRESENTATION (USED TO GIVE THE
                                                        //OBJECT VISUALIZATION CHARACTERISTICS
                                                        //SUCH AS COLOR AND TEXTURE)

        MeshObjectType::Pointer mesh; //IGSTK OBJECT (USED TO CREATE THE MESH
                                      //OBJECT AND ITS PHYSICAL CHARACTERISTICS SUCH AS SIZE)

        MeshRepresentation::Pointer meshRepresentation; //MESH REPRESENTATION (USED TO GIVE THE
                                                        //OBJECT VISUALIZATION CHARACTERISTICS
                                                        //SUCH AS COLOR AND TEXTURE)

		USObjectType::Pointer us;

		USRepresentation::Pointer usRepresentation;

        //Mesh Class functions

        void CreateAxes(); //INITIALIZE AND CREATE A NEW AXES OBJECT
        void CreateMesh(); //INITIALIZE AND CREATE A NEW AXES OBJECT
		void CreateUS();

};

//Creates new Axes for displaying
void Mesh::CreateAxes(){
	
    axes = AxesObjectType::New();

    int size = 5;
    axes->SetSize(size,size,size); //SET THE SIZE OF THE AXESES

    axesRepresentation = AxesRepresentation::New();

    axesRepresentation->RequestSetAxesObject(axes); //ASIGN THE AXES OBJECT TO ITS VISUAL REPRESENTATION
    axesRepresentation->SetColor(1.0, 0, 0); //ASIGN THE AXES COLOR

}

void Mesh::CreateUS()
{
	us = USObjectType::New();
	usRepresentation = USRepresentation::New();

	usRepresentation->RequestSetUSProbeObject(us);
}

//Creates a new Mesh
void Mesh::CreateMesh(){
	
    mesh = MeshObjectType::New();

   //SET THE POINTS OF THE MESH VERTEXES
    p0[0] = 0; p0[1] = 0; p0[2] = 5;
    p1[0] = 0; p1[1] = 0; p1[2] = 0;
    p2[0] = 5; p2[1] = 0; p2[2] = 0;
    p3[0] = 0; p3[1] = 5; p3[2] = 0;
	
    int pId = 0;

    //ADD THE POINTS TO THE MESH AND ASSIGN THE POINT ID FOR THEIR USAGE
    mesh->AddPoint(pId++, p0[0], p0[1], p0[2]);
    mesh->AddPoint(pId++, p1[0], p1[1], p1[2]);
    mesh->AddPoint(pId++, p2[0], p2[1], p2[2]);
    mesh->AddPoint(pId, p3[0], p3[1], p3[2]);

    mesh->AddTetrahedronCell(0, 0, 1, 2, 3); //ADD A THETRAEDRON CELL TO THE MESH
                                             //BY ESTABLISHING WHICH POINTS TO USE
    int tcId = 1;

    //ADD TRIANGLE CELLS TO THE MESH THAT ARE THE 4 FACES OF THE TETRAHEDRON
    mesh->AddTriangleCell(tcId++, 0, 1, 2);
    mesh->AddTriangleCell(tcId++, 0, 2, 3);
    mesh->AddTriangleCell(tcId++, 0, 1, 3);
    mesh->AddTriangleCell(tcId, 1, 2, 3);
	

    meshRepresentation = MeshRepresentation::New();

	
    meshRepresentation->RequestSetMeshObject(mesh); //ASIGN THE MESH OBJECT TO ITS VISUAL REPRESENTATION
    meshRepresentation->SetColor(0, 1.0, 1.0); //ASIGN THE MESH COLOR

}

class Image{

    //Image Typedefs for IGSTK
    typedef igstk::MRImageReader ImageReaderType;
    typedef igstk::MRImageSpatialObject ImageType;
    typedef igstk::MRImageSpatialObjectRepresentation ImageRepresentationType;

	
    //Definition of IGSTK observer
    igstkObserverObjectMacro(MRImage,ImageReaderType::ImageModifiedEvent,igstk::MRImageSpatialObject);
    typedef MRImageObserver ImageObserver;
	
    public:

        //Image IGSTK Objects
        ImageType::Pointer image; //IGSTK OBJECT (USED TO OBTAIN IMAGE DATA AND IMAGE PROCESSING)
        ImageRepresentationType::Pointer imageRepresentation; //VISUAL REPRESENTATION OF THE IMAGE
        ImageReaderType::Pointer reader; //IMAGE READER (SPECIFIED READER FOR MR IMAGES SIGNED SHORT)
        ImageObserver::Pointer imageobserver; //IMAGE READER OBSERVER (USED TO KNOW WHEN AND IMAGE_MODIFIED_EVENT HAPPENS)

        std::string filename; //DIRECTORY OF THE DICOM IMAGES

        //Image Class functions
        void CreateImage(); //READ AND CREATE A NEW IGSTK IMAGE

};

void Image::CreateImage(){

    reader = ImageReaderType::New();

	/*char *path=NULL;
	size_t size;
	path=_getcwd(path,0);
	cout<<"\n current Path"<<path;*/

    filename = "../../DICOM/PNEUMATIX/Cardiovascular Heart-Cardiac Function/cine_retro_lvot";
    reader->RequestSetDirectory(filename); //SET THE DIRECTORY OF THE DICOM IMAGES TO READ
    reader->RequestReadImage(); //READ THE DICOM IMAGES IN THE DIRECTORY

    if(reader->FileSuccessfullyRead()){ //IF THE READING WAS SUCCESFUL
        
        imageobserver = ImageObserver::New();
		
        reader->AddObserver(ImageReaderType::ImageModifiedEvent(), imageobserver); //ADD AN MRIMAGE_READER_OBSERVER
                                                                                   //TO THE READER TO OBSERVE IMAGEMODIFIED EVENTS
        reader->RequestGetImage(); //GET THE IMAGE DATA
	
        image = imageobserver->GetMRImage(); //IF THE MODIFIED IMAGE EVENT HAPPEN, ASK FOR THE MR IMAGE DATA
                                             //AND ASIGN IT TO THE IGSTK IMAGE

        imageRepresentation = ImageRepresentationType::New();
        imageRepresentation->RequestSetImageSpatialObject(image); //ASIGN THE IMAGE VISUAL REPRESENTATION
        imageRepresentation->RequestSetOrientation(ImageRepresentationType::Sagittal); //INDICATES WHICH ORIENTATION THE IMAGE IS GOING TO BE SHOWN
        imageRepresentation->RequestSetSliceNumber(18); //INDICATE WHICH SLICE OF THE DICOM SERIES TO SHOW

    }else{
        std::cout<<"Image Reading Error"<<std::endl;
    }
}
