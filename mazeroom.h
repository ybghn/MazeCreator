#ifndef MAZEROOM_H
#define MAZEROOM_H

#include <QObject>
#include <QPainter>
#include <QRandomGenerator>
#include <QVector>
#include <mazeconfigs.h>
enum Direction {
  E_Front,
  E_Right,
  E_Back,
  E_Left,
  E_NotValid

};
enum DoorStatus {
  E_Wall,
  E_Way,
    E_Visited,
};
struct Wall {
  Direction direction = E_NotValid;
  DoorStatus doorStatus = E_Wall;
};

class MazeRoom : public QObject {
  Q_OBJECT
public:
  explicit MazeRoom(QObject *parent = nullptr);

  QPoint Index() const;
  void SetIndex(QPoint newIndex);
  void Draw(QPainter &painter);
  Direction PickRandomWall();
  QPoint NeighbourRoom(Direction direction);

  void  SetWallStatus(Direction _direction,DoorStatus _status);
  MazeRoom *PreviousRoom() const;
  MazeRoom *NextRoom() const;
  void SetNextRoom(MazeRoom *newNextRoom);
  void SetPreviousRoom(MazeRoom *newPreviousRoom);
  bool HaveEmptyWall();


  bool IsVisited() const;
  void SetVisited(bool visited);

  private:
  QVector<Wall> listOfWall;
  QPoint index = QPoint(0, 0);

  bool isVisited = false;
  MazeRoom *previousRoom = nullptr;
  MazeRoom *nextRoom = nullptr;
};

#endif // MAZEROOM_H
