#ifndef VIDEOCAPTUREPROVIDER_H
#define VIDEOCAPTUREPROVIDER_H

#include <QObject>
#include <QPointer>
#include <QVideoSink>
#include <QQmlEngine>
#include <QTimer>

class VideoCaptureProvider;

// #include "qmlinterface.h"
/*
class VideoCaptureProvider : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVideoSink* videoSink READ videoSink WRITE setVideoSink NOTIFY videoSinkChanged)

public:
    VideoCaptureProvider(QObject *parent=nullptr);

    QVideoSink *videoSink() const;
    void setVideoSink(QVideoSink *videoSink);

    Q_INVOKABLE void start();
    Q_INVOKABLE void init(QObject *qmlInterface);

signals:
    void videoSinkChanged();

private:
    QPointer<QVideoSink> m_videoSink;
    void handleTimeout();
    QTimer m_timer;
    QmlInterface *m_qmlInterface;
};
*/
#endif // VIDEOCAPTUREPROVIDER_H
