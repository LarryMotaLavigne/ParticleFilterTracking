#include <QLabel>

class Viewer : public QLabel
{
    Q_OBJECT
public slots:
    void mousePressEvent ( QMouseEvent * event )
    {
        emit clicked();
    }
signals:
    void clicked();
};
