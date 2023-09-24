#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QPainter>
#include <QPaintEvent>
#include "mazeroom.h"
#include <QDebug>
#include <iostream>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QVector<MazeRoom*> rooms;

    void CreateMaze(MazeRoom *room);

    bool isFirst = 1;
    // QWidget interface
    MazeRoom *GetRoomWithIndex(QPoint _ind);
    bool ControlNeighbourRooms(MazeRoom *room);
    
protected:
    void paintEvent(QPaintEvent *event) override;
};
#endif // MAINWINDOW_H
