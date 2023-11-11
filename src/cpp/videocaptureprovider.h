#ifndef VIDEOCAPTUREPROVIDER_H
#define VIDEOCAPTUREPROVIDER_H

#include <QObject>
#include <QPointer>
#include <QVideoSink>
#include <QQmlEngine>
#include <QTimer>

class VideoCaptureProvider : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVideoSink* videoSink READ videoSink WRITE setVideoSink NOTIFY videoSinkChanged)

public:
    VideoCaptureProvider(QObject *parent=nullptr);

    QVideoSink *videoSink() const;
    void setVideoSink(QVideoSink *videoSink);

    Q_INVOKABLE void start();

signals:
    void videoSinkChanged();

private:
    QPointer<QVideoSink> m_videoSink;
    void handleTimeout();
    QTimer m_timer;
};

#endif // VIDEOCAPTUREPROVIDER_H
