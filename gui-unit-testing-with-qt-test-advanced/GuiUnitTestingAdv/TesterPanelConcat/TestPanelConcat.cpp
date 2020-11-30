#include "PanelConcat.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSignalSpy>
#include <QString>
#include <QtTest>

const QString STR1("blog.");
const QString STR2("davidecoppola.com");
const QString STR_RES(STR1 + STR2);

class TestPanelConcat : public QObject
{
	Q_OBJECT

private slots:
	void init();

	void TestFocusOrder();
	void TestFocusUsage();

	void TestSignals();

private:
	PanelConcat mPanel;
};

void TestPanelConcat::init()
{
	mPanel.CancelData();
}

//When testing focus with Qt Test we are basically simulating an user interacting with our widget using a keyboard.

//Something important to consider when working with focus is that simply calling QWidget::setFocus on a widget won’t work as 
//the widget is not visible during the execution of a test. What we need to do to get things working is calling the static function
//QApplication::setActiveWindow on the QWidget we are testing, in this case the PanelConcat object:

void TestPanelConcat::TestFocusOrder()
{
	// enables focus and widget events
	QApplication::setActiveWindow(&mPanel);

	// set initial focus
	
	//An extra step to take when testing a widget is to set which element will hold the focus initially with QWidget::setFocus:
	mPanel.mInputA->setFocus();
	QVERIFY2(mPanel.mInputA->hasFocus(), "Input A didn't get focus");

	// move focus to next widget
	QTest::keyClick(&mPanel, Qt::Key_Tab);
	QVERIFY2(mPanel.mInputB->hasFocus(), "Input B didn't get focus");

	// move focus to next widget
	QTest::keyClick(&mPanel, Qt::Key_Tab);
	QVERIFY2(mPanel.mButtonConcat->hasFocus(), "Button CONCAT didn't get focus");

	// move focus to next widget
	QTest::keyClick(&mPanel, Qt::Key_Tab);
	QVERIFY2(mPanel.mButtonCancel->hasFocus(), "Button CANCEL didn't get focus");
}

//In the real world, it would be better to split this test in two functions.
void TestPanelConcat::TestFocusUsage()
{
	// enables focus and widget events
	QApplication::setActiveWindow(&mPanel);

	// set initial focus
	mPanel.mInputA->setFocus();
	QVERIFY2(mPanel.mInputA->hasFocus(), "Input A doesn't have focus");

	// write STR1
	QTest::keyClicks(QApplication::focusWidget(), STR1);

	// move focus to next widget
	QTest::keyClick(&mPanel, Qt::Key_Tab);
	QVERIFY2(mPanel.mInputB->hasFocus(), "Input B doesn't have focus");

	// write STR2
	QTest::keyClicks(QApplication::focusWidget(), STR2);

	// move focus to next widget
	QTest::keyClick(&mPanel, Qt::Key_Tab);
	QVERIFY2(mPanel.mButtonConcat->hasFocus(), "Button CONCAT doesn't have focus");

	// press button CONCAT using space
	QTest::keyClick(QApplication::focusWidget(), Qt::Key_Space);
	QCOMPARE(mPanel.mLabelRes->text(), STR_RES);

	// move focus to next widget
	QTest::keyClick(&mPanel, Qt::Key_Tab);
	QVERIFY2(mPanel.mButtonCancel->hasFocus(), "Button CANCEL doesn't have focus");

	// press button CANCEL using space
	QTest::keyClick(QApplication::focusWidget(), Qt::Key_Space);
	QVERIFY2(mPanel.mInputA->text().isEmpty(), "Cancel didn't work on input A");
	QVERIFY2(mPanel.mInputB->text().isEmpty(), "Cancel didn't work on input B");
	QVERIFY2(mPanel.mLabelRes->text().isEmpty(), "Cancel didn't work on res label");
}

//One of the key features of Qt is the object communication based on signals & slots, which basically is an event-based system.

//To test that, Qt Test offers a class called QSignalSpy, which is a QList on steroids that can intercept and record signals.

 //PanelConcat class emits two signals:
    //DataAvailable(QString) – emitted after CONCAT is pushed and the input text has been merged.
    //DataCleared() – emitted after CANCEL is pushed and all the text is cleared.


void TestPanelConcat::TestSignals()
{
	// set input
	mPanel.mInputA->setText(STR1);
	mPanel.mInputB->setText(STR2);

	// create spy objects
	QSignalSpy spy1(&mPanel, &PanelConcat::DataAvailable);
	QSignalSpy spy2(&mPanel, &PanelConcat::DataCleared);

	// click button CONCAT
	QTest::mouseClick(mPanel.mButtonConcat, Qt::LeftButton);

	QCOMPARE(spy1.count(), 1);
	QCOMPARE(spy2.count(), 0);

	QList<QVariant> args = spy1.takeFirst();
	QCOMPARE(args.at(0).toString(), STR_RES);

	// click button CANCEL
	QTest::mouseClick(mPanel.mButtonCancel, Qt::LeftButton);

	QCOMPARE(spy1.count(), 0);
	QCOMPARE(spy2.count(), 1);

	args = spy2.takeFirst();
	QVERIFY2(args.empty(), "DataCleared signal has parameters now?!?");
}

QTEST_MAIN(TestPanelConcat)

#include "TestPanelConcat.moc"
