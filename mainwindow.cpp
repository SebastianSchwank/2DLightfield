#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <QImage>
#include <QGraphicsPixmapItem>
#include <QPixmap>

data Daten;


using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLoadData_activated()
{
    QString FileName;
    FileName = ui->textEdit->toPlainText();
    ui->textEdit->insertPlainText("\nLoading File:");
    ui->textEdit->insertPlainText(FileName);
    ui->textEdit->insertPlainText("\n");
    if(!Daten.loadFile(FileName))
    {
        QString numberOfElements = QString::number(Daten.getSize());
        ui->textEdit->insertPlainText("\n File sucessfully Loaded");
        ui->textEdit->insertPlainText("\n");
        ui->textEdit->insertPlainText(numberOfElements);
        ui->textEdit->insertPlainText(" Elements loaded");
        grid.setGrid(&Daten);
        ui->textEdit->insertPlainText("\n BresenhamGrid sucessfully built");
    }
    else
    {
        ui->textEdit->insertPlainText("\n File failed to load");
    }
}

void MainWindow::on_horizontalSlider_actionTriggered(int action)
{
    QString Size;
    ui->label_2->setText(Size.number(ui->horizontalSlider->value()));
}

void MainWindow::on_actionPreview_triggered()
{
    preview = new QGraphicsScene();

    viewpreview(Daten,grid,preview,ui->horizontalSlider->value());

    ui->graphicsView->setScene(preview);
    ui->graphicsView->show();
}


void MainWindow::on_actionNewRender_triggered()
{
    render = new QGraphicsScene();
    unsigned long scale;
    scale = ui->horizontalSlider->value();

    RenderTask = new renderer(&Daten,scale,grid);

    item = new QGraphicsPixmapItem ( QPixmap::fromImage(RenderTask->getImage()));
    render->addItem(item);

    ui->graphicsView->setScene(render);
    ui->graphicsView->show();
    renderRunning = false;
    samples = 0;
}

void MainWindow::on_actionStart_Stop_Render_triggered()
{
    renderRunning = !renderRunning;
    while(renderRunning == true)
    {
        render->~QGraphicsScene();
        render = new QGraphicsScene();

        RenderTask->renderSp(ui->spinBox->value());

        item = new QGraphicsPixmapItem ( QPixmap::fromImage(RenderTask->getImage()));
        render->addItem(item);

        ui->graphicsView->setScene(render);
        ui->graphicsView->show();

        samples += ui->spinBox->value();

        QCoreApplication::processEvents();
   }
}
