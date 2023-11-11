#include "qmlinterface.h"
#include <QtGui/qscreen.h>

QmlInterface::QmlInterface(QObject *parent)
    : QObject{parent}, m_isCapturing(false)
{
    m_sourceType = SourceType::Screen;

    m_screenListModel = new ScreenListModel(this);
    m_windowListModel = new WindowListModel(this);
    mediaCaptureSession = new QMediaCaptureSession(this);

    mediaCaptureSession->setScreenCapture(screenCapture);
    mediaCaptureSession->setWindowCapture(windowCapture);

    m_serverInterface = new ServerInterface();
    m_serverThread = new QThread(this);
    m_serverInterface->startListening();

    connect(m_serverThread, &QThread::finished, m_serverThread, &QObject::deleteLater);
    m_serverInterface->moveToThread(m_serverThread);
}

ScreenListModel *QmlInterface::getScreenListModel()
{
    return m_screenListModel;
}

WindowListModel *QmlInterface::getWindowListModel()
{
    return m_windowListModel;
}

void QmlInterface::stopCapture()
{
    setActive(false);
}

void QmlInterface::setActive(bool active)
{
    // screenCapture->setActive(active && m_sourceType == SourceType::Screen);
    // windowCapture->setActive(active && m_sourceType == SourceType::Window);

    m_isCapturing = active;
    emit isCapturingChanged();

    m_captureSource = m_sourceType == SourceType::Screen ? SourceType::Screen : SourceType::Window;
    emit captureSourceChanged();
}

void QmlInterface::startCapture(const int& index)
{
    qDebug() << "Starting capture ...";

    // Capturing the screen
    if(m_sourceType == SourceType::Screen)
    {
        qDebug() << "Capturing screen ...";

        if(index >= m_screenListModel->rowCount() || index < 0)
        {
            qDebug() << "Invalid Screen Index";
            return;
        }

        qDebug() << "Setting screen to capture ...";
        auto screen = m_screenListModel->screen(index);
        qDebug() << "Refresh Rate: " << screen->refreshRate();

        m_videoCaptureProvider->init(SourceType::Screen, screen);


        // screenCapture->setScreen(screen);

        qDebug() << "Set active source ...";
        setActive(true);

        qDebug() << "Done ...";
    }

    // Capturing the Window
    else
    {
        auto window = m_windowListModel->window(index);
        if (!window.isValid())
        {
            qDebug() << "Selected window is no longer valid!";
            return;
        }

        windowCapture->setWindow(window);
        setActive(true);
        m_captureSource = SourceType::Window;
        emit captureSourceChanged();
    }
}

void QmlInterface::setMediaCaptureOutput(VideoCaptureProvider * videoCaptureProvider)
{
    m_videoCaptureProvider = videoCaptureProvider;
    mediaCaptureSession->setVideoOutput(m_videoCaptureProvider->videoSink());
}

void QmlInterface::onWindowCaptureErrorOccured(QWindowCapture::Error, const QString &errorString)
{
    qDebug() << "QWindowCapture: Error occurred: " << errorString;
}

void QmlInterface::onScreenCaptureErrorOccured(QScreenCapture::Error, const QString &errorString)
{
    qDebug() << "QScreenCapture: Error occurred: " << errorString;
}
