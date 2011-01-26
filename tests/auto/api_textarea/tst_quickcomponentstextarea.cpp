/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include <QtTest/QtTest>
#include <QtTest/QSignalSpy>
#include <QtDeclarative/qdeclarativecontext.h>
#include <QDeclarativeView>
#include <QLineEdit>
#include <QTextOption>
#include <QDeclarativeExpression>
#include <QClipboard>

#include "tst_quickcomponentstest.h"

class tst_quickcomponentstextarea : public QObject

{
    Q_OBJECT

private slots:
    void initTestCase();
    void font();
    void cursorPosition();
    void horizontalAlignment();
    void verticalAlignment();
    void readOnly();
    void selectedText();
    void selectionEnd();
    void selectionStart();
    void text();
    void textFormat();
    void wrapMode();

private:
    QObject *componentObject;
    QDeclarativeEngine *engine;
};

void tst_quickcomponentstextarea::initTestCase()
{
    QString errors;
    engine = 0;
    componentObject = tst_quickcomponentstest::createComponentFromFile("tst_quickcomponentstextarea.qml", &errors, &engine);
    QVERIFY2(componentObject, qPrintable(errors));
}


void tst_quickcomponentstextarea::font()
{
    // test setting/getting the property
    QVERIFY(componentObject->setProperty("font", "Helvetica"));
    QVERIFY(componentObject->property("font").toString().startsWith("Helvetica"));
}

void tst_quickcomponentstextarea::cursorPosition()
{
    // test setting/getting the property
    QVERIFY(componentObject->setProperty("cursorPosition", 0));
    QCOMPARE(componentObject->property("cursorPosition").toInt(), 0);
}

void tst_quickcomponentstextarea::horizontalAlignment()
{
    // test setting/getting the property
    QVERIFY( componentObject->setProperty("horizontalAlignment", 0) );
    QCOMPARE( componentObject->property("horizontalAlignment").toInt(), 0 );
}

void tst_quickcomponentstextarea::verticalAlignment()
{
    // test setting/getting the property
    QVERIFY( componentObject->setProperty("verticalAlignment", 0) );
    QCOMPARE( componentObject->property("verticalAlignment").toInt(), 0 );
}

void tst_quickcomponentstextarea::readOnly()
{
    QVERIFY(componentObject->setProperty("readOnly", true));
    QVERIFY(componentObject->setProperty("text", "I just changed the text"));
    QEXPECT_FAIL("", "Not yet guarded by readOnly property, http://bugreports.qt.nokia.com/browse/QTCOMPONENTS-318", Continue);
    QVERIFY(componentObject->property("text").toString() != QString("I just changed the text"));

    // if readOnly == true, we should not be able to cut or paste
    // set the text to something known, select and cut it
    QVERIFY2(QMetaObject::invokeMethod(componentObject, "selectAll"), "Could not select all the text");
    QVERIFY2(QMetaObject::invokeMethod(componentObject, "cut"), "Could not cut the text");

    // check if the text area was cleared
    // ###: Change the string being compared here when the test above is fixed (readOnly guard)
    QCOMPARE(componentObject->property("text").toString(), QString("I just changed the text"));

    // we shouldn't be able to paste stuff on it too
    QVERIFY2(QMetaObject::invokeMethod(componentObject, "selectAll"), "Could not select all the text");
    QVERIFY2(QMetaObject::invokeMethod(componentObject, "copy"), "Could not copy the text");
    QVERIFY2(QMetaObject::invokeMethod(componentObject, "paste"), "Could not paste the text");

    // the text should remain the same as readOnly == true
    // ###: Change the string being compared here when the test above is fixed (readOnly guard)
    QCOMPARE(componentObject->property("text").toString(), QString("I just changed the text"));

    // reset readonly so it doesn't affect the next tests
    componentObject->setProperty("readOnly", false);
}

void tst_quickcomponentstextarea::selectedText()
{
    componentObject->setProperty("text", "Good morning");
    QDeclarativeExpression *expr = new QDeclarativeExpression(engine->rootContext(), componentObject, "select(0,4);");
    expr->evaluate();
    if (expr->hasError())
        qDebug() << expr->error();
    QVERIFY( !expr->hasError() );
    QCOMPARE( componentObject->property("selectedText").toString(), QString("Good") );
}

void tst_quickcomponentstextarea::selectionStart()
{
    componentObject->setProperty("text", "Good morning");
    QDeclarativeExpression *expr = new QDeclarativeExpression(engine->rootContext(), componentObject, "select(5,11);");
    expr->evaluate();
    if (expr->hasError())
        qDebug() << expr->error();
    QVERIFY( !expr->hasError() );
    QCOMPARE( componentObject->property("selectionStart").toInt(), 5 );
}

void tst_quickcomponentstextarea::selectionEnd()
{
    componentObject->setProperty("text", "Good morning");
    QDeclarativeExpression *expr = new QDeclarativeExpression(engine->rootContext(), componentObject, "select(5,11);");
    expr->evaluate();
    if (expr->hasError())
        qDebug() << expr->error();
    QVERIFY( !expr->hasError() );
    QCOMPARE( componentObject->property("selectionEnd").toInt(), 11 );
}

void tst_quickcomponentstextarea::text()
{
    // test setting/getting the property
    QVERIFY(componentObject->setProperty("text", "Hello World"));
    QCOMPARE(componentObject->property("text").toString(), QString("Hello World"));
}

void tst_quickcomponentstextarea::textFormat()
{
    // test setting/getting the property
    QVERIFY(componentObject->setProperty("textFormat", 0));
    QCOMPARE(componentObject->property("textFormat").toInt(), 0);
}

void tst_quickcomponentstextarea::wrapMode()
{
    QVERIFY( componentObject->setProperty("wrapMode", 0) );
    QCOMPARE( componentObject->property("wrapMode").toInt(), 0 );
}

QTEST_MAIN(tst_quickcomponentstextarea)

#include "tst_quickcomponentstextarea.moc"
