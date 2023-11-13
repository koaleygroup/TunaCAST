#include "qmlinterface.h"

#include <QImage>
#include <QPainter>
#include <QSize>
#include <QVideoFrame>

#include <QGuiApplication>
#include <QBuffer>

VideoCaptureProvider::VideoCaptureProvider(QObject *parent):QObject(parent), m_castState(CastState::Clear)
{
    m_timer.setInterval(100);
    connect(&m_timer, &QTimer::timeout, this, &VideoCaptureProvider::handleTimeout);
}

QVideoSink *VideoCaptureProvider::videoSink() const
{
    return m_videoSink.get();
}

void VideoCaptureProvider::setVideoSink(QVideoSink *videoSink)
{
    if (m_videoSink == videoSink)
        return;

    m_videoSink = videoSink;
    emit videoSinkChanged();
}

void VideoCaptureProvider::start()
{
    // m_timer.start();
    // handleTimeout();
}

void VideoCaptureProvider::init(QObject *qmlInterface)
{
    qDebug() << "Init!";

    m_qmlInterface = qobject_cast<QmlInterface *>(qmlInterface);
    m_qmlInterface->setMediaCaptureOutput(this);

    // connect(this, &VideoCaptureProvider::sendFrame, m_qmlInterface, &QmlInterface::onSendFrame);
    //connect(this, &VideoCaptureProvider::sendFrame, [&](const QImage &img){
    //    qDebug() << "On transit: " << img.size();
    //});

    start();
}

void VideoCaptureProvider::init(int sourceType, QScreen *qscreen)
{
    qDebug() << "Before Screen";
    // auto s = QGuiApplication::screens().value(0); // qscreen;
    qDebug() << "After Screen";
}

void VideoCaptureProvider::handleTimeout()
{
    if(!m_videoSink)
        return;

    switch(m_castState)
    {
    case CastState::StandbyMode:
    {
        auto standbyImg = QImage(":/TunaCastApp/src/assets/img/p1.jpg");
        image2VideoFrame(standbyImg);
        emit sendFrame(standbyImg);
        return;
    }
    case CastState::ScreenMode:
    {
        auto pix = QGuiApplication::screens().value(0)->grabWindow();
        QImage img = pix.toImage();
        image2VideoFrame(img);
        emit sendFrame(img);

        qDebug() << "Snapshot taken: " << img.size() << " bytes";

        return;
    }
    case CastState::WindowMode:
    case CastState::CustomMode:
    case CastState::Clear:
    default:
    {
        QImage image(QSize(1280,720), QImage::Format::Format_RGBA8888);
        image.fill(QColor(0,0,0));
        image2VideoFrame(image);
        emit sendFrame(image);
    }
    }
}

inline void VideoCaptureProvider::image2VideoFrame(const QImage &img)
{
    QVideoFrame frame(QVideoFrameFormat(img.size(), QVideoFrameFormat::pixelFormatFromImageFormat(img.format())));
    frame.map(QVideoFrame::ReadWrite);
    memcpy(frame.bits(0), img.bits(), img.sizeInBytes());
    frame.unmap();
    m_videoSink->setVideoFrame(frame);
}

