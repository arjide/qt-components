/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Components project on Qt Labs.
**
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions contained
** in the Technology Preview License Agreement accompanying this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
****************************************************************************/

import QtQuick 1.0
import Qt.labs.components.native 1.0
import "core"
import "core/StyleLoader.js" as StyleLoader

ApplicationWindow {
    id: window

    property Item appStyle: StyleLoader.loadStyle("qrc:/layouts/AppStyle.qml", window, forceFallbackStyle)
    property string appStyleSrc: StyleLoader.sourcePath

    property Item stationListContainer: null
    property bool forceFallbackStyle: false

    //![isTablet]
    property bool isTablet: screen.displayCategory == Screen.ExtraLarge
    //![isTablet]

    onAppStyleChanged: appStyleSrc = StyleLoader.sourcePath

    ToolBarLayout {
        id: commonTools
        ToolButton {
            flat: true
            iconSource: "image://theme/qtg_toolbar_back"
            onClicked: window.pageStack.depth <= 1 ? Qt.quit() : pageStack.pop()
        }
        ToolButton {
            flat: true
            iconSource: "image://theme/qtg_toolbar_options"
            onClicked: if (desktop) displaySelection.open()
        }
    }

    DisplaySelectionDialog {
        id: displaySelection
    }

    //![mainComponents]
    ViewContainer {
        id: mainView
        tools: commonTools
    }
    StationListView {
        id: stationView
        tools: commonTools
    }
    //![mainComponents]
    //![push]
    Component.onCompleted: {
        window.pageStack.push(mainView)
    }
    //![push]
    //![parentChange]
    states: State {
        when: isTablet
        ParentChange {
            target: stationView.stationList
            parent: stationListContainer
        }
    }
    //![parentChange]
    //![pop]
    onStateChanged: {
        pageStack.pop(stationView)
    }
    //![pop]
}
