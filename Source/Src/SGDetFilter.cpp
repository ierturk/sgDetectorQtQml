#include "SGDetFilter.h"
#include "SGDetFilterRunnable.h"

SGDetFilter::SGDetFilter(QObject* parent) :
    QAbstractVideoFilter(parent),
    m_Orientation(0) {
}

QVideoFilterRunnable* SGDetFilter::createFilterRunnable() {
    return new SGDetFilterRunnable();
}
