#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "data.h"
#include "preview.h"
#include "render.h"
//#include "quadtree.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionLoadData_activated();

    void on_horizontalSlider_actionTriggered(int action);

    void on_actionPreview_triggered();

    void on_actionNewRender_triggered();

    void on_actionStart_Stop_Render_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* preview;
    QGraphicsScene* render;
    QImage *RenderOut;
    QGraphicsPixmapItem *item;
    renderer *RenderTask;
    bool renderRunning;
    unsigned long samples;
    QString AppSpP;
};

#endif // MAINWINDOW_H
