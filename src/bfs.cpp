#include "bfs.h"
#include "cellstatus.h"

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using std::vector;
using std::queue;
using std::pair;
using std::cout;
using std::reverse;
using std::endl;

BFS::BFS(QObject *parent) : QObject(parent){
    _cols = 60;
    _rows = 80;
    GenerateGraph();
}

void BFS::GenerateGraph(){
    _field.resize(_cols);
    for(int i = 0; i < _cols; i++){
        _field[i].resize(_rows);
    }
    for(int i = 0; i < _cols; i++){
        for(int j = 0; j < _rows; j++){
            _field[i][j] = 0;
        }
    }
}

void BFS::GenerateNeighbours(){
    for(int i = 0; i < _cols; i++)
        for(int j = 0; j < _rows; j++){
            if (_field[i][j] != 1){ // Если не препятствие
                // Прямые
                if (i + 1 != _cols && _field[i + 1][j] != 1)
                    _neighbours[pair<int,int>{i, j}].push_back(pair<int,int>{i + 1, j});
                if (j + 1 != _rows && _field[i][j + 1] != 1)
                    _neighbours[pair<int,int>{i, j}].push_back(pair<int,int>{i, j + 1});
                if (i - 1 >= 0 && _field[i - 1][j] != 1)
                    _neighbours[pair<int,int>{i, j}].push_back(pair<int,int>{i - 1, j});
                if (j - 1 >= 0 && _field[i][j - 1] != 1)
                    _neighbours[pair<int,int>{i, j}].push_back(pair<int,int>{i, j - 1});
                // Диагонали
                if (i - 1 >= 0 && j - 1 >= 0 && _field[i - 1][j - 1] != 1)
                    _neighbours[pair<int,int>{i, j}].push_back(pair<int,int>{i - 1, j - 1});
                if (i - 1 >= 0 && j + 1 != _rows && _field[i - 1][j + 1] != 1)
                    _neighbours[pair<int,int>{i, j}].push_back(pair<int,int>{i - 1, j + 1});
                if (i + 1 != _cols && j - 1 >= 0 && _field[i + 1][j - 1] != 1)
                    _neighbours[pair<int,int>{i, j}].push_back(pair<int,int>{i + 1, j - 1});
                if (i + 1 != _cols && j + 1 != _rows && _field[i + 1][j + 1] != 1)
                    _neighbours[pair<int,int>{i, j}].push_back(pair<int,int>{i + 1, j + 1});
            }
        }
//    cout << "Neighbours: " << endl;
//    for (auto const& [key, val] : _graphN) {
//        std::cout << "Point: " << key.first << " " << key.second << std::endl;
//        for(auto const& a : val) {
//            std::cout << a.first << " " << a.second << std::endl;
//        }
//    }
}

void BFS::clearField(){
    for(int i = 0; i < _cols; i++){
        for(int j = 0; j < _rows; j++){
            _field[i][j] = 0;
        }
    }
    _neighbours.clear();
}

void BFS::search(int start_x, int start_y, int finish_x, int finish_y){
    _start = {start_x, start_y};
    _finish = {finish_x, finish_y};
    GenerateNeighbours();
    auto worker = new bfsWorker(&_neighbours);
    worker->setStartFinishPoint(_start, _finish);

    auto thread = new QThread;
    worker->moveToThread(thread);
    connect(thread, SIGNAL(started()), worker, SLOT(search()));
    connect(worker, SIGNAL(pointChecked(int , int)), this, SIGNAL(pointChecked(int , int)));
    connect(worker, SIGNAL(pathViewed(int , int)), this, SIGNAL(pathViewed(int , int)));
    connect(thread, SIGNAL(finished()), worker, SLOT(deleteLater()));

    thread->start();
};

void BFS::setUnavailableCell(int x, int y){
    _field[x][y] = 1;
}
