#include "qmlinterface.h"

QmlInterface::QmlInterface(QObject *parent)
    : QObject{parent}
{
    m_sourceType = SourceType::Screen;

    m_screenListModel = new ScreenListModel(this);
    m_windowListModel = new WindowListModel(this);
    mediaCaptureSession = new QMediaCaptureSession(this);

    mediaCaptureSession->setScreenCapture(screenCapture);
    mediaCaptureSession->setWindowCapture(windowCapture);
    // mediaCaptureSession->setVideoOutput(videoWidget);
}

ScreenListModel *QmlInterface::getScreenListModel()
{
    return m_screenListModel;
}

WindowListModel *QmlInterface::getWindowListModel()
{
    return m_windowListModel;
}

void QmlInterface::startStopCapture(const int& index)
{

    screenCapture->setActive(m_sourceType == SourceType::Screen);
    windowCapture->setActive(m_sourceType == SourceType::Window);

    // Capturing the screen
    if(m_sourceType == SourceType::Screen)
    {
        if(index >= m_screenListModel->rowCount() || index < 0)
            qDebug() << "Invalid Index";

        screenCapture->setScreen(m_screenListModel->screen(index));
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
    }
}

void QmlInterface::onWindowCaptureErrorOccured(QWindowCapture::Error, const QString &errorString)
{
    qDebug() << "QWindowCapture: Error occurred: " << errorString;
}

void QmlInterface::onScreenCaptureErrorOccured(QScreenCapture::Error, const QString &errorString)
{
    qDebug() << "QScreenCapture: Error occurred: " << errorString;
}
