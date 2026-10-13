#include "colourwindow.h"

ColourWindow::ColourWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Colour");
    resize(400, 320);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    colourPanel = new QWidget(this);
    colourPanel->setStyleSheet("background-color: #FFFFFF; border: 1px solid #ccc;");
    colourPanel->setMinimumHeight(150);
    mainLayout->addWidget(colourPanel);

    colourCodeField = new QLineEdit("#FFFFFF (RGB: 255, 255, 255)", this);
    colourCodeField->setAlignment(Qt::AlignCenter);

    QFont font = colourCodeField->font();
    font.setPointSize(11);
    font.bold();
    colourCodeField->setFont(font);
    mainLayout->addWidget(colourCodeField);

    QPushButton *chooseButton = new QPushButton("Open selector", this);
    mainLayout->addWidget(chooseButton);

    QPushButton *okButton = new QPushButton("OK", this);
    mainLayout->addWidget(okButton);

    connect(chooseButton, &QPushButton::clicked, this, &ColourWindow::openColour);
    connect(okButton, &QPushButton::clicked, this, &ColourWindow::applyColour);
    connect(colourCodeField, &QLineEdit::returnPressed, this, &ColourWindow::applyColour);
}

void ColourWindow::openColour(){
    QColor selectedColour = QColorDialog::getColor(
        Qt::white,
        this,
        "Select the colour",
        QColorDialog::DontUseNativeDialog
    );
    if(selectedColour.isValid())
        updateGUI(selectedColour);
}

void ColourWindow::applyColour(){
    QString text = colourCodeField->text().trimmed();
    QColor newColour;

    newColour.setNamedColor(text);

    if(!newColour.isValid()){
        QString cleanText = text;
        cleanText.remove("RGB", Qt::CaseInsensitive);
        cleanText.remove("(");
        cleanText.remove(")");
        QStringList parts = cleanText.split(',');

        if(parts.size() == 3){
            bool okR, okG, okB;
            int r = parts[0].trimmed().toInt(&okR);
            int g = parts[1].trimmed().toInt(&okG);
            int b = parts[2].trimmed().toInt(&okB);

            if (okR && okG && okB && r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255){
                newColour = QColor(r, g, b);
            }
        }
    }

    if(newColour.isValid()){
        updateGUI(newColour);
    } else {
        QMessageBox::warning(this, "Error", "Invalid format! Use Hex (ex: #FF5733) ou RGB (ex: 255, 87, 51).");
    }
}

void ColourWindow::updateGUI(const QColor &colour){
    QString hex = colour.name().toUpper();
    int r = colour.red();
    int g = colour.green();
    int b = colour.blue();

    colourPanel->setStyleSheet(QString("background-color: %1; border: 1px solid #ccc;").arg(hex));

    colourCodeField->setText(QString("%1 (RGB: %2, %3, %4)").arg(hex).arg(r).arg(g).arg(b));
}
