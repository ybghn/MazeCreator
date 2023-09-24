#include "mazeroom.h"
#include "qdebug.h"

MazeRoom::MazeRoom(QObject *parent) : QObject{parent} {
  Wall frontWall;
  frontWall.direction = E_Front;
  frontWall.doorStatus = E_Wall;

  Wall rightWall;
  rightWall.direction = E_Right;
  rightWall.doorStatus = E_Wall;

  Wall backWall;
  backWall.direction = E_Back;
  backWall.doorStatus = E_Wall;

  Wall leftWall;
  leftWall.direction = E_Left;
  leftWall.doorStatus = E_Wall;

  listOfWall.push_back(frontWall);
  listOfWall.push_back(rightWall);
  listOfWall.push_back(backWall);
  listOfWall.push_back(leftWall);
}

QPoint MazeRoom::Index() const { return index; }

void MazeRoom::SetIndex(QPoint newIndex) { index = newIndex; }

void MazeRoom::Draw(QPainter &painter) {
  QRect rectofRoom = QRect(MazeConfigs::RoomWidth * index.x(),
                           MazeConfigs::RoomWidth * index.y(),
                           MazeConfigs::RoomWidth, MazeConfigs::RoomWidth);

  QLine front(rectofRoom.topLeft(), rectofRoom.topRight());
  QLine right(rectofRoom.topRight(), rectofRoom.bottomRight());
  QLine back(rectofRoom.bottomLeft(), rectofRoom.bottomRight());
  QLine left(rectofRoom.topLeft(), rectofRoom.bottomLeft());

  painter.setBrush(QBrush(MazeConfigs::WallColor));

  if (listOfWall.at(0).doorStatus != E_Way) {
    painter.drawLine(front);
  }
  if (listOfWall.at(1).doorStatus != E_Way) {
    painter.drawLine(right);
  }
  if (listOfWall.at(2).doorStatus != E_Way) {
    painter.drawLine(back);
  }
  if (listOfWall.at(3).doorStatus != E_Way) {
    painter.drawLine(left);
  }
}

Direction MazeRoom::PickRandomWall() {

  QVector<Direction> tempWallList;

  for( auto w : listOfWall)
  {
    if(w.doorStatus == E_Wall)
    {
        tempWallList.push_back(w.direction);
    }
  }

  if(tempWallList.length() == 0)
  {

    return Direction::E_NotValid;
  }
  else {
   int tempIndex  = QRandomGenerator::global()->bounded(0,tempWallList.count());
    return tempWallList.at(tempIndex);
  }



}

QPoint MazeRoom::NeighbourRoom(Direction direction) {

  Direction dir = direction; // bu atama gereksiz olmuş :)
  QPoint newInd;
  switch (dir) {
  case E_Front: {
    newInd += index + QPoint(0, -1);
    break;
  }
  case E_Right: {
    newInd += index + QPoint(1, 0);
    break;
  }
  case E_Back: {
    newInd += index + QPoint(0, +1);
    break;
  }
  case E_Left:

  {
    newInd += index + QPoint(-1, 0);
    break;
  }
  case E_NotValid:
    break;
  }

  return newInd;
}



void MazeRoom::SetWallStatus(Direction _direction, DoorStatus _status) {
  for (auto &w : listOfWall) {
    if (w.direction == _direction) {
      w.doorStatus = _status;
    }
  }
}

MazeRoom *MazeRoom::PreviousRoom() const { return previousRoom; }

MazeRoom *MazeRoom::NextRoom() const { return nextRoom; }

void MazeRoom::SetNextRoom(MazeRoom *newNextRoom) { nextRoom = newNextRoom; }

void MazeRoom::SetPreviousRoom(MazeRoom *newPreviousRoom) {
  previousRoom = newPreviousRoom;
}

bool MazeRoom::HaveEmptyWall() {
  for (auto w : qAsConst(listOfWall)) {
    if (w.doorStatus == DoorStatus::E_Wall) {
      return 1;
    }
  }
  return 0;
}

bool MazeRoom::IsVisited() const
{
  return isVisited;
}

void MazeRoom::SetVisited(bool visited)
{
  isVisited = visited;
}

