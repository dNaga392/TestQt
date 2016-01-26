// Tests of QChar
// testqchar.cpp

#include <QtCore/QChar>

#include <QtTest/QtTest>

class TestQChar
	: public QObject
{
	Q_OBJECT

private Q_SLOTS:
	///	@note	This will be called before the first testfunction was executed.
	void initTestCase();
	///	@note	This will be called after the last testfunction was executed.
	void cleanupTestCase() {};
	///	@note	This will be called before each testfunction is exected.
	void init() {};
	///	@note	This will be called after every testfunction.
	void cleanup() {};

	void isLetter();
	void isLetter_data();
	void isLetterOrNumber();
	void isLetterOrNumber_data();

};

void TestQChar::initTestCase()/*{{{*/
{
	//QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
}/*}}}*/

void TestQChar::isLetter()
{
	QFETCH( QChar, ch );
	QFETCH( bool, result );
	QCOMPARE( ch.isLetter(), result );
}

void TestQChar::isLetter_data()
{
	QTest::addColumn< QChar >( "ch" );
	QTest::addColumn< bool >( "result" );
	QChar ch;
	bool result;
	ch = 'e';
	result = true;
	QTest::newRow("e") << ch << result;
	ch = '0';
	result = false;
	QTest::newRow("0") << ch << result;
	ch = '-';
	result = false;
	QTest::newRow("-") << ch << result;
}

void TestQChar::isLetterOrNumber()
{
	QFETCH( QChar, ch );
	QFETCH( bool, result );
	QCOMPARE( ch.isLetterOrNumber(), result );
}

void TestQChar::isLetterOrNumber_data()
{
	QTest::addColumn< QChar >( "ch" );
	QTest::addColumn< bool >( "result" );
	QChar ch;
	bool result;
	ch = 'e';
	result = true;
	QTest::newRow("e") << ch << result;
	ch = '0';
	result = true;
	QTest::newRow("0") << ch << result;
	ch = '-';
	result = false;
	QTest::newRow("-") << ch << result;
}


QTEST_MAIN(TestQChar)
#include "testqchar.moc"
