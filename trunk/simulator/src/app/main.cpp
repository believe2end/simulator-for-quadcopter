/**
 * Copyright (C) 2011 Brian Gou <gouqingsong@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <QApplication>

#include "mainwindow.h"
#include <QDebug>
#include <QMainWindow>
/*
#include "math/quat.h"
#include <math/euler.h>
*/
#include "qextserialport.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    
    QMainWindow mainWindow;

    mainWindow.show();
    
    return app.exec();
}