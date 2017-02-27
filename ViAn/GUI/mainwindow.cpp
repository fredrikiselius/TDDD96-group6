#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <chrono>
#include <thread>
#include <iostream>

using namespace std;
using namespace cv;

/**
 * @brief MainWindow::MainWindow
 * Constructor
 * @param parent a QWidget variable
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /**
     * How to get a picture
     */
    /*QImage image;
    image.load("<searchPath>");
    ui->videoFrame->setPixmap(QPixmap::fromImage(image));
    ui->videoFrame->show();*/
    mvideo_player = new video_player();
    QObject::connect(mvideo_player, SIGNAL(processedImage(QImage)),
                                  this, SLOT(update_video(QImage)));
}

/**
 * @brief MainWindow::~MainWindow
 * Destructor
 */
MainWindow::~MainWindow() {
    delete ui;
}

/**
 * @brief MainWindow::on_playButton_clicked
 * The leftmost button supposed to play the video
 */
void MainWindow::on_playButton_clicked() {

    if (mvideo_player->is_paused()) {
        mvideo_player->start();
    } else {
        mvideo_player->pause();
        mvideo_player->wait();
    }


}

/**
 * @brief MainWindow::on_pauseButton_clicked
 * The middle button supposed to pause the video
 */
void MainWindow::on_pauseButton_clicked() {
    mvideo_player->load_video("seq_01.mp4");
    //mvideo_player->load_video("mf.mkv");
}


/**
 * @brief MainWindow::on_stopButton_clicked
 * The rightmost button supposed to stop the video
 */
void MainWindow::on_stopButton_clicked() {

}

void MainWindow::update_video(QImage frame) {
    ui->videoFrame->setPixmap(QPixmap::fromImage(frame));
    ui->videoFrame->show();
}


