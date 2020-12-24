project(lab-6212-qlistwidget CXX)

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)

if (WIN32)
    # Чтобы убрать консоль
    #set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE true)

    # Копирование DLL-файлов библиотеки Qt в выходную директорию
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${Qt5_DIR}/../../../bin/windeployqt $<TARGET_FILE:${PROJECT_NAME}>)
endif (WIN32)
