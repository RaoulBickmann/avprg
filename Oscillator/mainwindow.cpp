#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QAudioInput>
#include <QAudioDecoder>
#include <QAudioFormat>
#include <math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , audioPlayer(this)

{
    ui->setupUi(this);
    initializeAudio();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initializeAudio(){
    on_frequencySlider_valueChanged(ui->frequencySlider->value());
    on_gainSlider_valueChanged(ui->gainSlider->value());

    audioPlayer.setAudioSource(&oscillatorSource);
    //audioPlayer.start();
}



void MainWindow::on_frequencySlider_valueChanged(int value)
{
    // 0 ... 100% --> 100Hz ... 10000Hz
    float scaledValue = 2 * value / 100.f + 2;
    float frequency = pow(10, scaledValue);

    ui->frequencyLabel->setText(QString::number((int)frequency));
    oscillatorSource.setFrequency(frequency);
}

void MainWindow::on_waveformCombobox_activated(int index)
{
    oscillatorSource.setSelectedOscillator(index);
}

void MainWindow::on_gainSlider_valueChanged(int value)
{
    oscillatorSource.setGain(value);
}


//Buttons pressed

void MainWindow::on_firstC_pressed()
{
    oscillatorSource.setNote(40);
    audioPlayer.start();
}


void MainWindow::on_D_pressed()
{
    oscillatorSource.setNote(42);
    audioPlayer.start();
}

void MainWindow::on_E_pressed()
{
    oscillatorSource.setNote(44);
    audioPlayer.start();
}

void MainWindow::on_F_pressed()
{
    oscillatorSource.setNote(45);
    audioPlayer.start();
}

void MainWindow::on_G_pressed()
{
    oscillatorSource.setNote(47);
    audioPlayer.start();
}

void MainWindow::on_H_pressed()
{
    oscillatorSource.setNote(49);
    audioPlayer.start();
}

void MainWindow::on_A_pressed()
{
    oscillatorSource.setNote(51);
    audioPlayer.start();
}

void MainWindow::on_secondC_pressed()
{
    oscillatorSource.setNote(52);
    audioPlayer.start();
}

//Buttons released

void MainWindow::on_firstC_released()
{
    audioPlayer.stop();
}

void MainWindow::on_D_released()
{
    audioPlayer.stop();
}

void MainWindow::on_E_released()
{
    audioPlayer.stop();
}

void MainWindow::on_F_released()
{
    audioPlayer.stop();
}

void MainWindow::on_G_released()
{
    audioPlayer.stop();
}

void MainWindow::on_H_released()
{
    audioPlayer.stop();
}

void MainWindow::on_A_released()
{
    audioPlayer.stop();
}

void MainWindow::on_secondC_released()
{
    audioPlayer.stop();
}
