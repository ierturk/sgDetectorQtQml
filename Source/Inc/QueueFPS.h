//
// Created by ierturk on 16/08/2019.
//

#ifndef SG_DETECTOR_QUEUEFPS_H
#define SG_DETECTOR_QUEUEFPS_H

#include <QElapsedTimer>
#include <QMutex>
#include <QQueue>

template <typename T>
class QueueFPS : public QQueue<T> {

public:
    QueueFPS() : counter(0) {}

    void push(const T& entry) {
        QMutexLocker locker(&m_mutex);
        QQueue<T>::enqueue(entry);
        counter += 1;
        if (counter == 1) {
            // Start counting from a second frame (warmup).
            tm.restart();
        }
    }

    T get() {
        QMutexLocker locker(&m_mutex);
        T entry = this->dequeue();
        this->pop();
        return entry;
    }

    float getFPS() {
        double fps = 1000 * counter / tm.elapsed();
        return static_cast<float>(fps);
    }

    void clear() {
        QMutexLocker locker(&m_mutex);
        while (!this->empty())
            this->pop();
    }

    unsigned int getCounter() {
        return counter;
    }

private:
    unsigned int counter;
    QMutex m_mutex;
    QElapsedTimer tm;
};

#endif //SG_DETECTOR_QUEUEFPS_H
