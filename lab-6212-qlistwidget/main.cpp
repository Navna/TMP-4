#include <QApplication>
#include <QListWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QGroupBox>
#include <QWidget>

static QListWidget* list;

// TODO Переименовать и дописать согласно варианту
struct Data {
    QString header;
};

// TODO Переименовать и дописать согласно варианту
struct DataItem : QListWidgetItem {
    Data* data;

    DataItem(Data* data) : QListWidgetItem(data->header), data(data) { }

    DataItem(const Data&) = delete;

    DataItem& operator=(const Data&) = delete;

    ~DataItem() {
        delete data;
    }
};

static void addItem() {
    auto data = new Data;
    data->header = u8"Новый объект";
    auto item = new DataItem(data);
    list->addItem(item);
}

static void removeItem() {
    qDeleteAll(list->selectedItems());
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Создаём окно
    QWidget window;
    window.setWindowTitle(u8"Диспетчер объектов");

    // Создаём список и кнопки добавления/удаления
    list = new QListWidget;
    auto addButton = new QPushButton(u8"Добавить");
    auto removeButton = new QPushButton(u8"Удалить");
    QObject::connect(addButton, &QPushButton::clicked, addItem);
    QObject::connect(removeButton, &QPushButton::clicked, removeItem);

    // Создаём поля для отображения информации об объекте
    auto groupBox = new QGroupBox(u8"Информация об объекта");
    //auto editLayout = ...;
    //groupBox->setLayout(editLayout);

    // Расположение элементов на форме
    auto layout = new QGridLayout;
    layout->addWidget(list, 0, 0, 1, 2);
    layout->addWidget(addButton, 1, 0);
    layout->addWidget(removeButton, 1, 1);
    layout->addWidget(groupBox, 0, 2, 2, 1);

    // Показываем окно
    window.setLayout(layout);
    window.show();

    return QApplication::exec();
}
