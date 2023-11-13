#include "qmlinterface.h"
#include <QtGui/qscreen.h>
#include <QGuiApplication>

QmlInterface::QmlInterface(QObject *parent)
    : QObject{parent}, m_isCapturing(false)
{
    m_sourceType = SourceType::Screen;

    m_screenListModel = new ScreenListModel(this);
    m_windowListModel = new WindowListModel(this);
    mediaCaptureSession = new QMediaCaptureSession(this);

    screenCapture = new QScreenCapture(this);
    windowCapture = new QWindowCapture(this);

    mediaCaptureSession->setScreenCapture(screenCapture);
    mediaCaptureSession->setWindowCapture(windowCapture);

    m_serverInterface = new ServerInterface();
    m_serverThread = new QThread(this);
    m_serverInterface->startListening();

    connect(m_serverThread, &QThread::finished, m_serverThread, &QObject::deleteLater);
    // m_serverInterface->moveToThread(m_serverThread);

    connect(m_serverInterface, &ServerInterface::serverOnlineChanged, this, [&](bool isOnline){ emit serverOnlineChanged(isOnline);});
    m_serverThread->start();
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

    if(m_sourceType == SourceType::Screen)
    {
        screenCapture->stop();
    }

    else
    {
        windowCapture->stop();
    }
}

void QmlInterface::setActive(bool active)
{

    screenCapture->setActive(active && m_sourceType == SourceType::Screen);
    windowCapture->setActive(active && m_sourceType == SourceType::Window);

    m_isCapturing = active;
    emit isCapturingChanged();

    m_sourceType = m_sourceType == SourceType::Screen ? SourceType::Screen : SourceType::Window;
    emit sourceTypeChanged();

    qDebug() << "[Screen/Window] [" << SourceType::Screen << "/" <<  SourceType::Window << "] : " << [&](){ return m_sourceType == SourceType::Screen ? SourceType::Screen : SourceType::Window; }();
}

void QmlInterface::startCapture(const int& index)
{
    qDebug() << "Starting " << m_sourceType << " capture on index: " << index;

    // Capturing the screen
    if(m_sourceType == SourceType::Screen)
    {
        // Check if index is within list range
        if(index >= m_screenListModel->rowCount() || index < 0)
        {
            qDebug() << "Invalid Screen Index";
            return;
        }

        // Get the current active screen by index
        auto screen = m_screenListModel->screen(index);

        if(!screen)
        {
            // Screen is invalid / nullptr
            qDebug() << "Invalid screen to capture ...";
            return;
        }

        // Set the selected screen as the current screen for capture
        screenCapture->setScreen(screen);

        // Set the current active capture [window/screen]
        setActive(true);
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

        // Set the selected window as the current window for capture
        windowCapture->setWindow(window);

        // Set the current active capture [window/screen]
        setActive(true);
    }
}

void QmlInterface::setMediaCaptureOutput(VideoCaptureProvider * videoCaptureProvider)
{
    qDebug() << "Setting up media capture output";

    // Save the videcaptureprovider as a member variable for later reference
    m_videoCaptureProvider = videoCaptureProvider;

    // Get the QVideoSink from the VideoCaptureProvider and set as the sink for Screen/Video Capture
    mediaCaptureSession->setVideoOutput(m_videoCaptureProvider->videoSink());

    // connect(m_videoCaptureProvider, &VideoCaptureProvider::sendFrame, m_serverInterface, &ServerInterface::onSendFrame);
}

void QmlInterface::onWindowCaptureErrorOccured(QWindowCapture::Error, const QString &errorString)
{
    qDebug() << "QWindowCapture: Error occurred: " << errorString;
}

void QmlInterface::onScreenCaptureErrorOccured(QScreenCapture::Error, const QString &errorString)
{
    qDebug() << "QScreenCapture: Error occurred: " << errorString;
}
