#include "PanelConcat.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
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

	void TestConstruction();
	void TestSize();

	void TestClear();

	void TestConcat_data();
	void TestConcat();

private:
	PanelConcat panel;
};

void TestPanelConcat::init()
{
	panel.CancelData();
}

void TestPanelConcat::TestConstruction()
{
//In this case the test is fairly straightforward as the code is just checking if the different internal widgets are not NULL. 
//In a real application things can be more complex as some elements are not always created, so it’s important to cover all 
//the cases when unit testing.
	QVERIFY2(panel.mInputA, "Input field A not created");
	QVERIFY2(panel.mInputB, "Input field B not created");

	QVERIFY2(panel.mLabelRes, "Result label not created");
}

void TestPanelConcat::TestSize()
{
	QVERIFY2(panel.minimumWidth() == PanelConcat::MIN_W, "Minimum width not set.");
	QVERIFY2(panel.minimumHeight() == PanelConcat::MIN_H, "Minimum height not set");
}

//The first step is performed using the function QTest::keyClicks which simulates a sequence of key clicks on a widget:
void TestPanelConcat::TestClear()
{
	// write into input fields
	QTest::keyClicks(panel.mInputA, STR1);
	QTest::keyClicks(panel.mInputB, STR2);

	//By default QTest::mouseClick simulates the click in the middle of the widget, 
	//which is fine for a button, but it is also possible to specify a position.
	
	// click button CONCAT = pushing the CONCAT button to get a result
	QTest::mouseClick(panel.mButtonConcat, Qt::LeftButton);

	// click button CANCEL = pushing the CANCEL button to clear all the data
	QTest::mouseClick(panel.mButtonCancel, Qt::LeftButton);

	// check all fields are empty
	QVERIFY2(panel.mInputA->text().isEmpty(), "Input A not empty");
	QVERIFY2(panel.mInputB->text().isEmpty(), "Input B not empty");
	QVERIFY2(panel.mLabelRes->text().isEmpty(), "Label result not empty");
}
//A more advanced way of doing GUI unit testing with Qt Test is data driven testing. 
//The idea is to separate tests and data to avoid to have a long list of similar QVERIFY or QCOMPARE macros 
//and to replicate all the code needed to initialise a test.

void TestPanelConcat::TestConcat_data()
{
	QTest::addColumn<QTestEventList>("inputA");
	QTest::addColumn<QTestEventList>("inputB");
	QTest::addColumn<QString>("result");

	QTestEventList listA;
	QTestEventList listB;

	// -- Normal A + B --
	listA.addKeyClicks(STR1);

	listB.addKeyClicks(STR2);

	QTest::newRow("Normal A + B") << listA << listB << STR_RES;

	// -- empty A --
	listA.clear();

	listB.clear();
	listB.addKeyClicks(STR2);

	QTest::newRow("Empty A") << listA << listB << STR2;

	// -- empty B --
	listA.clear();
	listA.addKeyClicks(STR1);

	listB.clear();

	QTest::newRow("Empty B") << listA << listB << STR1;

	// -- all empty --
	listA.clear();

	listB.clear();

	QTest::newRow("All empty") << listA << listB << QString();
}

void TestPanelConcat::TestConcat()
{
	QFETCH(QTestEventList, inputA);
	QFETCH(QTestEventList, inputB);
	QFETCH(QString, result);

	// write into input fields
	inputA.simulate(panel.mInputA);
	inputB.simulate(panel.mInputB);

	// click button CONCAT
	QTest::mouseClick(panel.mButtonConcat, Qt::LeftButton);

	// compare result
	QCOMPARE(panel.mLabelRes->text(), result);
}

QTEST_MAIN(TestPanelConcat)

#include "TestPanelConcat.moc"
