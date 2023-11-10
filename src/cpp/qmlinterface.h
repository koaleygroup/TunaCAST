#ifndef QMLINTERFACE_H
#define QMLINTERFACE_H

#include <QObject>
#include <QScreenCapture>
#include <QWindowCapture>
#include <QMediaCaptureSession>

#include "screenlistmodel.h"
#include "windowlistmodel.h"

class QmlInterface : public QObject
{
    Q_OBJECT
public:
    enum SourceType { Screen=0, Window };
    Q_ENUM(SourceType)

    explicit QmlInterface(QObject *parent = nullptr);

    Q_PROPERTY(SourceType sourceType MEMBER m_sourceType NOTIFY sourceTypeChanged)

    Q_INVOKABLE ScreenListModel* getScreenListModel();
    Q_INVOKABLE WindowListModel *getWindowListModel();

    Q_INVOKABLE void startStopCapture(const int& index);

signals:
    void sourceTypeChanged();

private slots:
    void onWindowCaptureErrorOccured(QWindowCapture::Error error, const QString &errorString);
    void onScreenCaptureErrorOccured(QScreenCapture::Error error, const QString &errorString);

private:
    SourceType m_sourceType;
    ScreenListModel* m_screenListModel;
    WindowListModel* m_windowListModel;

    QScreenCapture *screenCapture = nullptr;
    QWindowCapture *windowCapture = nullptr;
    QMediaCaptureSession *mediaCaptureSession = nullptr;
};

#endif // QMLINTERFACE_H
