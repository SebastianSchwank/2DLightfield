#ifndef PREVIEW_H
#define PREVIEW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include "data.h"
#include "quadtree.h"
#include "bresenhamgrid.h"

void viewpreview(data Daten,BresenhamGrid grid, QGraphicsScene *preview,long scale);

#endif // PREVIEW_H
