#ifndef QMLINTERFACE_H
#define QMLINTERFACE_H

#include <QObject>
#include <QScreenCapture>
#include <QWindowCapture>
#include <QMediaCaptureSession>
#include <QPointer>
#include <QVideoSink>
#include <QQmlEngine>
#include <QTimer>
#include <QThread>

#include "screenlistmodel.h"
#include "windowlistmodel.h"
#include "serverinterface.h"

// Forward declare classes,  having some issues
// with recursive includes for the two classes
class QmlInterface;
class VideoCaptureProvider;


class QmlInterface : public QObject
{
    Q_OBJECT
public:
    enum SourceType { Screen=0, Window };
    Q_ENUM(SourceType)

    explicit QmlInterface(QObject *parent = nullptr);

    Q_PROPERTY(SourceType sourceType MEMBER m_sourceType NOTIFY sourceTypeChanged FINAL)
    Q_PROPERTY(bool isCapturing MEMBER m_isCapturing NOTIFY isCapturingChanged FINAL)
    Q_PROPERTY(SourceType captureSource MEMBER m_captureSource NOTIFY captureSourceChanged FINAL)

    Q_INVOKABLE ScreenListModel* getScreenListModel();
    Q_INVOKABLE WindowListModel *getWindowListModel();

    Q_INVOKABLE void startCapture(const int& index);
    Q_INVOKABLE void stopCapture();

    void setActive(bool active);
    void setMediaCaptureOutput(VideoCaptureProvider * videoCaptureProvider);

signals:
    void sourceTypeChanged();
    void isCapturingChanged();
    void captureSourceChanged();
    void serverOnlineChanged(bool isOnline);

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

    bool m_isCapturing;
    SourceType m_captureSource;
    VideoCaptureProvider * m_videoCaptureProvider;
    ServerInterface * m_serverInterface;
    QThread * m_serverThread;
};

class VideoCaptureProvider : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVideoSink* videoSink READ videoSink WRITE setVideoSink NOTIFY videoSinkChanged)

public:
    enum SourceType { Screen=0, Window };
    Q_ENUM(SourceType)

    enum CastState {
        Clear=0,
        StandbyMode,
        ScreenMode,
        WindowMode,
        CustomMode
    };
    Q_ENUM(CastState)

    VideoCaptureProvider(QObject *parent=nullptr);
    Q_PROPERTY(CastState castState MEMBER m_castState NOTIFY castStateChanged FINAL)

    QVideoSink *videoSink() const;
    void setVideoSink(QVideoSink *videoSink);

    Q_INVOKABLE void start();
    Q_INVOKABLE void init(QObject *qmlInterface);

    void init(int sourceType, QScreen * qscreen);

signals:
    void videoSinkChanged();

    void castStateChanged();

private:
    void image2VideoFrame(const QImage &img);

    QPointer<QVideoSink> m_videoSink;
    void handleTimeout();
    QTimer m_timer;
    QmlInterface *m_qmlInterface;

    QScreen * m_screen;
    CastState m_castState;
};

#endif // QMLINTERFACE_H
