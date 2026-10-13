#ifndef COLOURWINDOW_H
#define COLOURWINDOW_H
#include <QMainWindow>
#include <QApplication>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QColorDialog>
#include <QColor>
#include <QMessageBox>
#include <QStringList>

class ColourWindow : public QMainWindow
{
    Q_OBJECT
public:
    ColourWindow(QWidget *parent = nullptr);
private slots:
    void openColour();
    void applyColour();
    void updateGUI(const QColor &colour);
private:
    QWidget *colourPanel;
    QLineEdit *colourCodeField;
};

#endif // COLOURWINDOW_H
