/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * LXQt - a lightweight, Qt based, desktop toolset
 * https://lxqt.org/
 *
 * Copyright: 2022 LXQt team
 * Authors:
 *   P.L. Lucas <selairi@gmail.com>
 *
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */

#include <iostream>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QSettings>
#include <QStandardPaths>
#include <QDir>

QString profileDir(QString workspace, QString settings, bool useFallback) {
    // try user-specific config file first
    QString dirName = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation)
                      + QStringLiteral("/") + workspace + QStringLiteral("/") + settings;
    QDir dir(dirName);

    // if user config dir does not exist, try system-wide config dirs instead
    if(!dir.exists() && useFallback) {
        QString fallbackDir;
        const QStringList confList = QStandardPaths::standardLocations(QStandardPaths::ConfigLocation);
        for(const auto &thisConf : confList) {
            fallbackDir = thisConf + QStringLiteral("/") + workspace + QStringLiteral("/") + settings;
            if(fallbackDir != dirName) {
                dir.setPath(fallbackDir);
                if(dir.exists()) {
                    dirName = fallbackDir;
                    break;
                }
            }
        }
    }

    return dirName;
}


QString getSettingsPath(QString workspace, QString settings)
{
    QString fileName = profileDir(workspace, settings, true) + ".conf";
    return fileName;
}

QString getProperty(QString workspace, QString settings, QString propertyName)
{
    QString fileName = getSettingsPath(workspace, settings);
    QSettings qsettings(fileName, QSettings::IniFormat);

    return qsettings.value(propertyName, QString()).toString();
}

QStringList getKeys(QString workspace, QString settings)
{
    QString fileName = getSettingsPath(workspace, settings);
    std::cout << "FileName: " << fileName.toStdString() << std::endl;
    QSettings qsettings(fileName, QSettings::IniFormat);

    return qsettings.allKeys();
}

int main(int argn, char *argv[])
{
    QCoreApplication app(argn, argv);
    QCoreApplication::setApplicationName("lxqt-settings");
    QCoreApplication::setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription(R"(List LXQt settings from command line.

This tool lets read the LXQt settings from command line.

These settings usually are in ~/.config/lxqt or ~/.config/pcmanfm-qt.

Examples:

Get cursor size:
    lxqt-settings session --get Mouse/cursor_size

Get cursor theme:
    lxqt-settings session --get Mouse/cursor_theme

Get wallpaper:
    lxqt-settings pcmanfm-qt lxqt/settings --get Desktop/Wallpaper

Get list of pcmanfm-qt settings:
    lxqt-settings pcmanfm-qt lxqt/settings --list

)");
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addPositionalArgument("workspace", QCoreApplication::translate("main", "Workspace to list, ex. lxqt or pcmanfm-qt. Default lxqt."), "[workspace]");
    parser.addPositionalArgument("settings", QCoreApplication::translate("main", "Settings file to read."));

    QCommandLineOption getPropertyOption(QStringList() << "get",
        QCoreApplication::translate("main", "Get a LXQt <key>."),
        QCoreApplication::translate("main", "key"));
    parser.addOption(getPropertyOption);

    QCommandLineOption listPropertiesOption(QStringList() << "list",
        QCoreApplication::translate("main", "List of keys")
    );
    parser.addOption(listPropertiesOption);


    // Process the actual command line arguments given by the user
    parser.process(app);

    QString workspace, settings;
    const QStringList positionalArgs = parser.positionalArguments();
    if(positionalArgs.size() > 1) {
        workspace = positionalArgs.at(0);
        settings = positionalArgs.at(1);
    } else if(positionalArgs.size() == 1) {
        workspace = "lxqt";
        settings = positionalArgs.at(0);
    } else {
        parser.showHelp();
        return 1;
    }

    QString propertyName = parser.value(getPropertyOption);
    if(! propertyName.isEmpty()) {
        std::cout << getProperty(workspace, settings, propertyName).toStdString() << std::endl;
        return 0;
    }

    if(parser.isSet(listPropertiesOption)) {
        QStringList keys = getKeys(workspace, settings);
        for(QString key : keys)
            std::cout << key.toStdString() << std::endl;
        return 0;
    }

    parser.showHelp();
}
