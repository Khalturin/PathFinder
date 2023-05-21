#ifndef BFSWORKER_H
#define BFSWORKER_H

#include <QObject>
#include <QThread>
#include <cstdint>
#include <vector>
#include <map>

using std::vector;
using std::map;
using std::pair;


class bfsWorker: public QObject{
    Q_OBJECT

public:
    bfsWorker(map<pair<int, int>, vector<pair<int, int>>> *graphN, QObject *parent = 0);
    void setStartFinishPoint(pair<int, int> start, pair<int, int> finish){_start = start; _finish = finish;}

public slots:
    void search();

signals:
    void pointChecked(int x, int y);
    void pathViewed(int x, int y);

private:
    map<pair<int, int>, vector<pair<int, int>>> * _graphN;
    pair<int, int> _start;
    pair<int, int> _finish;
};

#endif // BFSWORKER_H
