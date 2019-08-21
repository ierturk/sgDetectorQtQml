#ifndef SGDETFILTER_H
#define SGDETFILTER_H

#include <QAbstractVideoFilter>

class SGDetFilter : public QAbstractVideoFilter {
    Q_OBJECT
    Q_PROPERTY(int orientation MEMBER m_Orientation)

public:
    SGDetFilter(QObject* parent = nullptr);
    QVideoFilterRunnable* createFilterRunnable() Q_DECL_OVERRIDE;

protected:
    int m_Orientation;
};

#endif // SGDETFILTER_H
