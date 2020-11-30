#include "TestCalculator.h"

// -- setup/cleanup --
void TestCalculator::init()
{
	mCalc.SetA(A0);
	mCalc.SetB(B0);
}

// -- tests --
void TestCalculator::testConstructor()
{
	// default values
	Calculator c1;

	//********** verify values
	QVERIFY(c1.GetA() == 0);
	QVERIFY(c1.GetB() == 0);

	// full constructor
	const int A = 10;
	const int B = 2;
	Calculator c2(A, B);

	QVERIFY2(c2.GetA() == A, "first operand doesn't match");
	QVERIFY2(c2.GetB() == B, "second operand doesn't match");
}

void TestCalculator::testSum()
{
	// sum default
	//**********compare values
	QCOMPARE(mCalc.Sum(), A0 + B0);

	// sum after setting a and b
	const int A = 10;
	const int B = 2;
	mCalc.SetA(A);
	mCalc.SetB(B);

	QCOMPARE(mCalc.Sum(), A + B);
}


//each unit test is supposed to be an independent executable = after creating a unit test you need a main to run it

// generate basic main: no GUI, no events :  unit test class directly in the .cpp file (no .h file):
QTEST_APPLESS_MAIN(TestCalculator)
	
   //other options 
   // full Qt application
    //QTEST_MAIN(TestName)
	
    // core Qt application: no GUI, but event loop is available
    //QTEST_GUILESS_MAIN(TestName) 
	
    // no Qt application: no GUI and no events
   // QTEST_APPLESS_MAIN(TestName)
	
	
// uncomment next line if class declaration is in .cpp (no .h)
//#include "TestCalculator.moc"
