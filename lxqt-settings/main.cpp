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

QString profileDir(QString tool, QString profile, bool useFallback) {
    // try user-specific config file first
    QString dirName = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation)
                      + QStringLiteral("/") + tool + QStringLiteral("/") + profile;
    QDir dir(dirName);

    // if user config dir does not exist, try system-wide config dirs instead
    if(!dir.exists() && useFallback) {
        QString fallbackDir;
        const QStringList confList = QStandardPaths::standardLocations(QStandardPaths::ConfigLocation);
        for(const auto &thisConf : confList) {
            fallbackDir = thisConf + QStringLiteral("/") + tool + QStringLiteral("/") + profile;
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


void getSettingsPathAndKey(QString propertyName, QString *fileName, QString *key)
{
    QStringList path = propertyName.split('/');
    QString tool, profile;
    for(int n = 0; n < path.size(); n++) {
        if(n == 0) {
            tool = path.at(n);
        } else if(n == 1) {
            profile = path.at(n);
        } else if(n == 2) {
            *fileName = profileDir(tool, profile, true) + "/" + path.at(n) + ".conf";
        } else if(n > 2) {
            if(key->isEmpty())
                *key = path.at(n);
            else
                *key += "/" + path.at(n);
        }
    }
}

QString getProperty(QString propertyName)
{
    QString fileName, key;
    getSettingsPathAndKey(propertyName, &fileName, &key);
    QSettings settings(fileName, QSettings::IniFormat);

    return settings.value(key, QString()).toString();
}

QStringList getKeys(QString settingsPath)
{
    QString fileName, key;
    getSettingsPathAndKey(settingsPath, &fileName, &key);
    QSettings settings(fileName, QSettings::IniFormat);

    return settings.allKeys();
}

int main(int argn, char *argv[])
{
    QCoreApplication app(argn, argv);
    QCoreApplication::setApplicationName("lxqt-session-sway");
    QCoreApplication::setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("LXQt session for Sway.");
    parser.addHelpOption();
    parser.addVersionOption();

    	QCommandLineOption getPropertyOption(QStringList() << "get",
        QCoreApplication::translate("main", "Get a LXQt <setting>."),
        QCoreApplication::translate("main", "setting"));
    parser.addOption(getPropertyOption);

    QCommandLineOption listPropertiesOption(QStringList() << "list",
        QCoreApplication::translate("main", "List of keys <setting>."),
        QCoreApplication::translate("main", "setting"));
    parser.addOption(listPropertiesOption);


    // Process the actual command line arguments given by the user
    parser.process(app);

    QString propertyName = parser.value(getPropertyOption);
    if(! propertyName.isEmpty()) {
        std::cout << getProperty(propertyName).toStdString() << std::endl;
    }

    QString fileName = parser.value(listPropertiesOption);
    if(! fileName.isEmpty()) {
        QStringList keys = getKeys(fileName);
        for(QString key : keys)
            std::cout << key.toStdString() << std::endl;
    }
}
