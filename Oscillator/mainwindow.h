#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QAudioOutput>
#include "audioplayer.h"
#include "oscillatorsource.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_frequencySlider_valueChanged(int value);

    void on_waveformCombobox_activated(int index);

    void on_gainSlider_valueChanged(int value);


    void on_firstC_pressed();

    void on_D_pressed();

    void on_E_pressed();

    void on_F_pressed();

    void on_G_pressed();

    void on_H_pressed();

    void on_A_pressed();

    void on_secondC_pressed();

    void on_firstC_released();

    void on_D_released();

    void on_E_released();

    void on_F_released();

    void on_G_released();

    void on_H_released();

    void on_A_released();

    void on_secondC_released();

private:
    void initializeAudio();
    Ui::MainWindow *ui;
    OscillatorSource oscillatorSource;
    AudioPlayer audioPlayer;
};

#endif // MAINWINDOW_H
