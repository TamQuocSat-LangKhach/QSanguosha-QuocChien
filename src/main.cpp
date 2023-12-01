/********************************************************************
    Copyright (c) 2013-2015 - Mogara

    This file is part of QSanguosha-Hegemony.

    This game is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 3.0
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    See the LICENSE file for more details.

    Mogara
    *********************************************************************/

#if defined(WIN32) && !defined(GPP) && !defined(QT_NO_DEBUG) && !defined(WINRT)
#include <vld/vld.h>
#endif

#include <QFile>
#include <QCoreApplication>
#include <QApplication>
#include <QTranslator>
#include <QDateTime>
#include <QSplashScreen>
#include <QMessageBox>

#include "server.h"
#include "settings.h"
#include "engine.h"
#include "mainwindow.h"
#include "audio.h"
#include "stylehelper.h"

#ifndef WINDOWS
#include <QDir>
#endif

#ifdef USE_BREAKPAD
#include <client/windows/handler/exception_handler.h>
#include <QProcess>

using namespace google_breakpad;

static bool callback(const wchar_t *, const wchar_t *id, void *, EXCEPTION_POINTERS *, MDRawAssertionInfo *, bool succeeded)
{
    if (succeeded && QFile::exists("QSanSMTPClient.exe")) {
        char ID[16000];
        memset(ID, 0, sizeof(ID));
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4996)
#endif
        wcstombs(ID, id, wcslen(id));
#ifdef _MSC_VER
#pragma warning(pop)
#endif
        QProcess *process = new QProcess(qApp);
        QStringList args;
        args << QString(ID) + ".dmp";
        process->start("QSanSMTPClient", args);
    }
    return succeeded;
}
#endif

int main(int argc, char *argv[])
{
    bool noGui = argc > 1 && strcmp(argv[1], "-server") == 0;

    if (noGui)
        new QCoreApplication(argc, argv);
    else
        new QApplication(argc, argv);

#if defined(Q_OS_MAC) || defined(Q_OS_ANDROID)
#define showSplashMessage(message)
#define SPLASH_DISABLED
#else
    QSplashScreen *splash = NULL;
    if (!noGui) {
        QPixmap raraLogo;
        raraLogo.load("image/system/developers/logo.png");

        splash = new QSplashScreen(raraLogo);
        splash->show();
        qApp->processEvents();
    }
#define showSplashMessage(message) \
    if (splash == NULL) {\
        puts(message.toUtf8().constData());\
        } else {\
        splash->showMessage(message, Qt::AlignBottom | Qt::AlignHCenter, Qt::cyan);\
        qApp->processEvents();\
        }
#endif

#ifdef USE_BREAKPAD
    showSplashMessage(QSplashScreen::tr("Loading BreakPad..."));
    ExceptionHandler eh(L"./dmp", NULL, callback, NULL, ExceptionHandler::HANDLER_ALL);
#endif

#if defined(Q_OS_MAC) && defined(QT_NO_DEBUG)
    showSplashMessage(QSplashScreen::tr("Setting game path..."));
    QDir::setCurrent(qApp->applicationDirPath());
#endif

#ifdef Q_OS_LINUX
    showSplashMessage(QSplashScreen::tr("Checking game path..."));
    QDir dir(QString("lua"));
    if (dir.exists() && (dir.exists(QString("config.lua")))) {
        // things look good and use current dir
    } else {
        showSplashMessage(QSplashScreen::tr("Setting game path..."));
#ifndef Q_OS_ANDROID
        QDir::setCurrent(qApp->applicationFilePath().replace("games", "share"));
#else
        bool found = false;
        QDir storageDir("/storage");
        QStringList sdcards = storageDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
        foreach (const QString &sdcard, sdcards) {
            QDir root(QString("/storage/%1/Android/data/org.qsgsrara.qsanguosha").arg(sdcard));
            if (root.exists("lua/config.lua")) {
                QDir::setCurrent(root.absolutePath());
                found = true;
                break;
            }
        }
        if (!found) {
            QDir root("/sdcard/Android/data/org.qsgsrara.qsanguosha");
            if (root.exists("lua/config.lua")) {
                QDir::setCurrent(root.absolutePath());
                found = true;
            }
        }


        if (!found) {
            QString m = QObject::tr("Game data not found, please download QSanguosha-For-Hegemony PC version, and put the files and folders into /sdcard/Android/data/org.qsgsrara.qsanguosha");
            if (!noGui)
                QMessageBox::critical(NULL, QObject::tr("Error"), m);
            else
                puts(m.toLatin1().constData());

            return -2;
        }
#endif
    }
#endif

    // initialize random seed for later use
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    // load the main translation file first for we need to translate messages of splash.
    QTranslator translator;
    translator.load("sanguosha.qm");
    qApp->installTranslator(&translator);
    QStringList funMess;
    funMess << "Đang đi chiếm Kinh Châu..." << "Đang đi mời Gia Cát Lượng..."
            << "Đang trị độc cho Quan Vũ..." << "Đang cạo râu cho Tào Tháo..."
            << "Đang ra chợ mua Đào..." << "Đang cho Nghiêm Bạch Hổ ăn..."
            << "Đang hát karaoke cùng Trương Phi..." << "Đang cởi giáp cho Hứa Chử..."
            << "Đang tiến về Hứa Xương..." << "Đang đi đoạt Hán Trung..."
            << "Đang đi đánh Đông Ngô..." << "Đang tiếp giá Tôn Quyền..."
            << "Đang đi tìm Hán Hiến Đế..." << "Đang yết kiến Lưu hoàng thúc..."
            << "Đang huấn luyện cho AI Tài Tống..." << "Đang vận lương tới Kỳ Sơn..."
            << "Đang tỉ thí với Tôn Thượng Hương..." << "Đang đi mua ngựa Xích Thố..."
            << "Đang thu xếp quân lương..." << "Đang triệu tập binh mã..."
            << "Đang tiêu diệt giặc Khăn Vàng..." << "Đang triệu tập 18 lộ chư hầu..."
            << "Đang truy đuổi Đổng Trác..." << "Đang Hỏa Công Xích Bích..."
            << "Đang vây bắt Mạnh Hoạch..." << "Đang thu nhận Trương Liêu..."
            << "Đang quyết đấu với Lữ Bố..." << "Đang không biết làm gì..."
            << "Đang bận chạy deadline..." << "Đang vá lỗ hổng không gian..."
            << "Đang chuẩn bị máy ảnh..." << "Đang trở về quá khứ..."
            << "Đang hồi sinh cho Quách Gia..." << "Đang ngủ trưa..."
            << "Đang bận chọc Chu Du..." << "Đang đi in bài..."
            << "Đang bận chửi Dev code ngu..."
               ;
    std::random_shuffle(funMess.begin(), funMess.end());

    showSplashMessage(funMess.at(0));
    QTranslator qt_translator;
    qt_translator.load("qt_zh_CN.qm");
    qApp->installTranslator(&qt_translator);

    showSplashMessage(funMess.at(1));
    new Settings;
    Sanguosha = new Engine;

    showSplashMessage(funMess.at(2));
    Config.init();
    if (!noGui) {
        QFont f = Config.AppFont;
#ifdef Q_OS_ANDROID
        f.setPointSize(12);
#endif
        qApp->setFont(f);
    }

    if (qApp->arguments().contains("-server")) {
        Server *server = new Server(qApp);
        printf("Server is starting on port %u\n", Config.ServerPort);

        if (server->listen())
            printf("Starting successfully\n");
        else
            printf("Starting failed!\n");

        return qApp->exec();
    }

    showSplashMessage(funMess.at(3));
    QFile file("style-sheet/sanguosha.qss");
    QString styleSheet;
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        styleSheet = stream.readAll();
    }

#ifdef Q_OS_WIN
    QFile winFile("style-sheet/windows-extra.qss");
    if (winFile.open(QIODevice::ReadOnly)) {
        QTextStream winStream(&winFile);
        styleSheet += winStream.readAll();
    }
#endif

    qApp->setStyleSheet(styleSheet + StyleHelper::styleSheetOfTooltip());

#ifdef AUDIO_SUPPORT
    showSplashMessage(funMess.at(4));
    Audio::init();
#else
    if (!noGui)
        QMessageBox::warning(NULL, QMessageBox::tr("Warning"), QMessageBox::tr("Audio support is disabled when compiled"));
#endif

    showSplashMessage(funMess.at(5));
    MainWindow main_window;

    Sanguosha->setParent(&main_window);
    main_window.show();
#ifndef SPLASH_DISABLED
    if (splash != NULL) {
        splash->finish(&main_window);
        delete splash;
    }
#endif

    foreach (const QString &_arg, qApp->arguments()) {
        QString arg = _arg;
        if (arg.startsWith("-connect:")) {
            arg.remove("-connect:");
            Config.HostAddress = arg;
            Config.setValue("HostAddress", arg);

            main_window.startConnection();
            break;
        }
    }

    return qApp->exec();
}
