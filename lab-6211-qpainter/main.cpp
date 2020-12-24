#include <QApplication>
#include <QBoxLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QWidget>
#include <QColor>

#include <vector>

class DrawingWidget : public QWidget {
    const static int R = 2;

    virtual void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);

        // Заливаем фон белым цветом
        painter.fillRect(0, 0, width(), height(), Qt::white);

        // Отрисовка точек
        painter.setPen(Qt::black);   // Цвет границы
        painter.setBrush(Qt::black); // Цвет заливки
        for (const auto& p : _data) {
            painter.drawEllipse(p.x() - R, p.y() - R, 2 * R, 2 * R);
        }

    }

    virtual void mousePressEvent(QMouseEvent* event) override {
        _data.push_back(event->pos());
        update();
    }

    std::vector<QPoint> _data;

};

DrawingWidget* widget;

void undoClick() {
    // TODO
}

void redoClick() {
    // TODO
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Создаём окно
    QWidget window;
    window.setMinimumSize(640, 480);
    window.setWindowTitle(u8"Графический редактор");

    // Создаём элементы управления
    auto undoButton = new QPushButton(u8"Undo");
    auto redoButton = new QPushButton(u8"Redo");
    QObject::connect(undoButton, &QPushButton::clicked, undoClick);
    QObject::connect(redoButton, &QPushButton::clicked, redoClick);
    undoButton->setEnabled(false);
    redoButton->setEnabled(false);

    // Располагаем элементы на форме
    auto panel = new QHBoxLayout;
    panel->addWidget(undoButton);
    panel->addWidget(redoButton);
    panel->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    widget = new DrawingWidget;
    auto layout = new QVBoxLayout;
    layout->addLayout(panel);
    layout->addWidget(widget);
    layout->setStretchFactor(panel, 0);
    layout->setStretchFactor(widget, 1);

    // Показываем окно
    window.setLayout(layout);
    window.show();

    return QApplication::exec();
}
