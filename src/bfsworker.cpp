#include "bfsworker.h"

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using std::vector;
using std::queue;
using std::pair;
using std::cout;
using std::endl;

bfsWorker::bfsWorker(map<pair<int, int>, vector<pair<int, int>>> *graphN, QObject *parent) : QObject(parent){
    _graphN = graphN;
}

void bfsWorker::search(){
    queue<pair<int, int>> q;
    map<pair<int, int>, pair<int, int>> visited;

    q.push(_start);

    while(!q.empty()){
        pair<int, int> point = q.front();
        q.pop();
        if (point == _finish){
            break;
        }

        // Сигнал для qml для отрисовки процесса поиска
        if (point != _start)
            emit pointChecked(point.second, point.first);

        vector<pair<int, int>> neighbors = (*_graphN)[point];
        for(auto neighbor : neighbors){
            if (!visited.count(neighbor)){
                q.push(neighbor);
                visited[neighbor] = point;
            }
        }
        // Задержка для отображения процесса поиска
//        QThread::msleep(1);
    }

    // Отобразить результирующий путь
    pair<int,int> cpoint = visited[_finish];
    while(cpoint != _start){
        // Сигнал для qml для отрисовки результата поиска
        emit pathViewed(cpoint.second, cpoint.first);
        cpoint = visited[cpoint];
    }
}
