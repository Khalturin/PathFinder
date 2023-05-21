#ifndef BFS_H
#define BFS_H

#include <QObject>
#include <QThread>
#include <cstdint>
#include <vector>
#include <map>

#include "bfsworker.h"

using std::vector;
using std::map;
using std::pair;

class BFS : public QObject{
    Q_OBJECT

public:
    explicit BFS(QObject *parent = 0);

public slots:
    // Установка непроходимой ячейки
    void setUnavailableCell(int, int);
    // Создание воркера и запуск поиска в потоке
    void search(int start_x, int start_y, int finish_x, int finish_y);
    // Очистка поля
    void clearField();
    int getCols(){return _cols;}
    int getRows(){return _rows;}

signals:
    // Проверка текущей ячейки
    void pointChecked(int x, int y);
    // Отображение результирующего маршрута
    void pathViewed(int x, int y);

private:
    int _cols, _rows;
    vector<vector<int>> _field;
    pair<int, int> _start;
    pair<int, int> _finish;
    map<pair<int, int>, vector<pair<int, int>>> _neighbours;

    // private methods
    void GenerateGraph();
    void GenerateNeighbours();
};

#endif // BFS_H
