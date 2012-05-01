#include "data.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <QLocale>


using namespace std;

data::data()
{
}

edge data::getEdge(unsigned long ElNumbr)
{
    if(ElNumbr < this->getSize())
    {
        return Edges[ElNumbr];
    }
    else
    {
        qDebug() << "Element not accessable";
    }
}

long data::getSize()
{
    return Edges.size();
}

int data::loadFile(QString FileName)
{
    QString LoadedData;         //Ausgabevariable für den TextEdit

    QFile myFile(FileName); // Create a file handle for the file
    QString line;

    if (!myFile.open(QIODevice::ReadOnly | QIODevice::Text)) // Open the file
    {
        return 1;
    }

    QTextStream stream( &myFile ); // Set the stream to read from myFile
    while (!stream.atEnd()){
        edge BufferEdge;

        line = stream.readLine(); // this reads a line (QString) from the file First Line (Koordinates)
        QStringList Koordinates = line.split(",");

        BufferEdge.x1 = Koordinates[0].toDouble();
        BufferEdge.y1 = Koordinates[1].toDouble();
        BufferEdge.x2 = Koordinates[2].toDouble();
        BufferEdge.y2 = Koordinates[3].toDouble();

        line = stream.readLine(); // this reads a line (QString) from the file Second Line (Color)
        QStringList Color = line.split(",");

        BufferEdge.r = Color[0].toDouble();
        BufferEdge.g = Color[1].toDouble();
        BufferEdge.b = Color[2].toDouble();

        line = stream.readLine(); // this reads a line (QString) from the file Third Line (Emission)
        QStringList Emission = line.split(" ");
        BufferEdge.e = Emission[0].toDouble();

        line = stream.readLine(); // this reads a line (QString) from the file 4th Line (Glossyness)
        QStringList Glossy = line.split(" ");
        BufferEdge.gl = Glossy[0].toDouble();

        line = stream.readLine();

        LoadedData += LoadedData.number(BufferEdge.x1) + ",";
        LoadedData += LoadedData.number(BufferEdge.y1) + ",";
        LoadedData += LoadedData.number(BufferEdge.x2) + ",";
        LoadedData += LoadedData.number(BufferEdge.y2) + " // x1,y1,x2,y2 Pos of the Edge\n";

        LoadedData += LoadedData.number(BufferEdge.r) + ",";
        LoadedData += LoadedData.number(BufferEdge.g) + ",";
        LoadedData += LoadedData.number(BufferEdge.b) + " // Color r,g,b of the Edge\n";

        LoadedData += LoadedData.number(BufferEdge.e) + " // Emission of the Edge\n";

        LoadedData += LoadedData.number(BufferEdge.gl) + " // Glossyness of the Edge\n";

        LoadedData += "----------------------\n";

        Edges.push_back(BufferEdge);
    }



    myFile.close();   // Datei schließen


    return 0;
}
