#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QColorDialog>
#include <QColor>
#include <QMainWindow>
#include <QApplication>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void updateUIComponents(int, int, int, int);
    ~MainWindow();

public slots:
    //pushbuttons
    void on_pushButtonSave_clicked();
    void on_pushButtonLoad_clicked();
    void on_pushButtonColorDialog_clicked();

    //checkbox
    void on_checkBoxErase_stateChanged(int);
    void on_checkBoxFilled_stateChanged(int);

    //combo box
    void on_comboBox_currentIndexChanged(int);

    //sliders
    void on_horizontalSliderRed_valueChanged(int);
    void on_horizontalSliderGreen_valueChanged(int);
    void on_horizontalSliderBlue_valueChanged(int);
    void on_horizontalSliderSize_valueChanged(int);
    void on_horizontalSliderAlpha_valueChanged(int);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
