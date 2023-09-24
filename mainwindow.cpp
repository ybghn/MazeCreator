#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  int size = 10;
  for (int y = 0; y < size; ++y) {
    for (int x = 0; x < size; ++x) {

      MazeRoom *room = new MazeRoom(this);

      room->SetIndex(QPoint(x, y));

      rooms.push_back(room);
    }
  }

  MazeRoom *initialRoom = GetRoomWithIndex(QPoint(0, 0));
  initialRoom->SetVisited(1);
  CreateMaze(initialRoom);
  qDebug() << "Bitti";
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::CreateMaze(MazeRoom *room) {

  update();
  if (!room) {

    qDebug() << "Room Pointer is taken as nullptr.  " << __FILE__ << " : "
             << __LINE__;
    return;
  }

  if(!isFirst)
  {

    if(room->Index() == QPoint(0,0))
    {
      return;
    }
  }
  else {
    isFirst = 0;
  }
  qDebug() << room->Index() << " : Boş Duvar Var Mı  ? "
           << room->HaveEmptyWall();
  Direction selectedWall = room->PickRandomWall();
  if (selectedWall == Direction::E_NotValid) {

    CreateMaze(room->PreviousRoom());
    return;
  }

  auto newRoomInd = room->NeighbourRoom(selectedWall);
  qDebug() << "New Room Ind : " << newRoomInd;
  auto newRoom = GetRoomWithIndex(newRoomInd);

  if (newRoom) {
    // güzel gidiyor, orada oda var, peki müsait mi ? Oda daha önce ziyaret
    // edildi mi
    qDebug() << "Next Room Seçildi Ind : " << newRoom->Index();
    qDebug() << "Ziyaret Edilmiş mi ? " << newRoom->IsVisited();
    Direction newDirection = E_NotValid;

    if (!newRoom->IsVisited()) {

      room->SetWallStatus(selectedWall, E_Way);

      switch (selectedWall) {
      case E_Front:
        newDirection = E_Back;
        break;
      case E_Right:
        newDirection = E_Left;
        break;
      case E_Back:
        newDirection = E_Front;
        break;
      case E_Left:
        newDirection = E_Right;
        break;
      case E_NotValid:
        qCritical("Wtf ? ");
        break;
      }

      newRoom->SetWallStatus(newDirection, E_Way);
      newRoom->SetVisited(1);
      room->SetNextRoom(newRoom);
      newRoom->SetPreviousRoom(room);

      CreateMaze(newRoom);
      return;
    } else { //  room is visited
      room->SetWallStatus(selectedWall, E_Visited);
      qDebug() << "Wall ziyaret edilmiş olarak işaretlendi : " << selectedWall;
      if (room->HaveEmptyWall()) {
        CreateMaze(room);
        return;
      } else {

        CreateMaze(room->PreviousRoom());
        return;
      }
    }

    // eğer oda da müsaitse selectedWall way yapılır,
    // yeni odanın duvarıda way yapılır.
    // yeni odanın uğranıldı bool 'ı 1 ;
  } else {
    room->SetWallStatus(selectedWall,E_Visited);
    CreateMaze(room);
  }
}

MazeRoom *MainWindow::GetRoomWithIndex(QPoint _ind) {
  for (auto r : qAsConst(rooms)) {
    if (r->Index() == _ind) {
      return r;
    }
  }

  return nullptr;
}

void MainWindow::paintEvent(QPaintEvent *event) {

  QPainter painter(this);

  for (MazeRoom *r : qAsConst(rooms)) {
    r->Draw(painter);
  }

}
