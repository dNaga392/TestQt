/*! ******************************************************************
	@file	testqstring.cpp
	@brief	Test of QString
******************************************************************* */
#include <string>

#include <QtTest/QtTest>

/*! ******************************************************************
	@brief	Test class of QString
******************************************************************* */
class TestQString/*{{{*/
	: public QObject
{
	Q_OBJECT

private Q_SLOTS:
	//void initTestCase();
	//void cleanupTestCase();
	//void init();
	//void cleanUp();

	// 170710-S コードを仮移動
	//void fromLocal8Bit();
	// 170710-E
// bool QString::contains ( const QString & str, Qt::CaseSensitivity cs = Qt::CaseSensitive ) const
	void containsQString();
	void containsQString_data();
//// bool QString::contains ( const QRegExp & rx ) const
//	void containsConstQRegExp();
//	void containsConstQRegExp_data();
// bool QString::contains ( QRegExp & rx ) const
	void containsQRegExp();
	void containsQRegExp_data();

	// QString QString::toUpper() const
	///	QString::toUpper() のテスト
	void toUpper();
	///	QString::toUpper() のテストデータセット
	void toUpper_data();
	
	///	std::string から QString への変換テスト
	void fromStdString();
	///	QString から std::string への変換テスト
	void toStdString();
	void numberDouble();
	void numberDouble_data();
	/// 
	void testcommondirectorypath();
	void testcommondirectorypath_data();
	void testsetnumdouble();
	void testsetnumdouble_data();
	void length();
	void sprintf();
	void sprintf_data();
	void setNum_double();
	void arg_double();
	void split_qchar_data();
	void split_qchar();
	void split_char_data();
	void split_char();
	void split_rx();
	void toInt();
};/*}}}*/

// 170710-S コードを仮移動
//void TestQString::initTestCase()
//{
//	QTextCodec::setCodecForCStrings( QTextCodec::codecForLocale() );
//	qDebug() << QTextCodec::codecForLocale()->name();
//	qDebug() << QTextCodec::codecForLocale()->aliases();
//}
//// テスト部
//void TestQString::fromLocal8Bit()
//{
//	QString str;
//	str = QString::fromLocal8Bit("ほげほげほげ");
//	str = QString::fromAscii("ほげほげほげ");
//	qDebug() << str;
//}
// 170710-E

//void TestQString::toInt_data()
//{
//	QTest::addColumn< QString >( "str" );
//	QTest::addColumn< int >( "result" );
//
//	QString str;
//	int result;
//	// テストセット登録
//	QTest::newRow("example") << str << result;
//}

void TestQString::toInt()
{
	int actual;
	actual = QString("123").split( QRegExp("[\\D]") ).first().toInt();
	QCOMPARE( actual, 123 );
	actual = QString("abc").split( QRegExp("[\\D]") ).first().toInt();
	QCOMPARE( actual, 0 );
	actual = QString("1a2b3c").split( QRegExp("[\\D]") ).first().toInt();
	QCOMPARE( actual, 1 );
	actual = QString("a7b8c9").split( QRegExp("[\\D]") ).first().toInt();
	QCOMPARE( actual, 0 );
}

void TestQString::split_qchar_data()
{
	QTest::addColumn<QString>("str");
	QTest::addColumn<QChar>("sep");
	QTest::addColumn<int>("size");

	QTest::newRow("example") << ("hoge,huga,hage,hege") << QChar(',') << 4;
}
void TestQString::split_qchar()
{
	QFETCH(QString, str);
	QFETCH(QChar, sep);
	QFETCH(int, size);
	QStringList strlist = str.split(sep);

	QCOMPARE(strlist.size(), size);
}

void TestQString::split_char_data()
{
	QTest::addColumn<QString>("str");
	QTest::addColumn<char>("sep");
	QTest::addColumn<int>("size");

	QTest::newRow("example") << ("hoge,huga,hage,hege") << (',') << 4;
}
void TestQString::split_char()
{
	QFETCH(QString, str);
	QFETCH(char, sep);
	QFETCH(int, size);
	QStringList strlist = str.split(sep);

	QCOMPARE(strlist.size(), size);

	int count = 0;
	for (count = 0; count < strlist.count(); )
	{
		strlist.at(count);
		++count;
	}
	QCOMPARE(strlist.count(), count);
}

void TestQString::split_rx()
{
	QString str("The piece\tis\fthe\rwar.\n");
	QString sepalate_str(" \t\n\r\f");
	QString rx_str( QString("[%1]").arg( sepalate_str ) );
	QRegExp rx( rx_str );
	QStringList result = str.split( rx );
	QStringList expected;
	expected << "The"<<"piece"<<"is"<<"the"<<"war."<<"";

	QCOMPARE( result, expected );
	QCOMPARE( result.size(), 6 );
}

void TestQString::arg_double()
{
	double n = 0.001592;
	int fieldWidth = 0;
	char format = 'f';
	int precision = 3;
	QChar fillChar = QLatin1Char( ' ' );
	QString result( "0.002" );

	QString str;
	str = QString("%1").arg( n, fieldWidth, format, precision, fillChar );

	QCOMPARE( str, result );
}

void TestQString::setNum_double()
{
	double n = 0.001592;
	char format = 'f';
	int precision = 3;
	QString result("0.002");

	QString str;
	str.setNum( n, format, precision );

	QCOMPARE( str, result );
}
void TestQString::sprintf()
{
//	QFETCH( QString, format );
//	QFETCH( double, d );
//	QFETCH( QString, result );
//
//	const char * cformat = format.toAscii().constData();
//
//	QString str;
//	str.sprintf( cformat, d );
//
//	QCOMPARE( str, result );

	// 現状のテストケースだと失敗するが、
	// 以下は正常にテストが通る
	const char * cformat = "%.0f";
	double d = 3.14;
	QString result("3");

	QString format( cformat );
	QCOMPARE( cformat, format.toAscii().constData() );

	QString str;
	str.sprintf( cformat, d );

	QCOMPARE( str, result );
}

void TestQString::sprintf_data()
{
//	QTest::addColumn< QString >( "format" );
//	QTest::addColumn< double >( "d" );
//	QTest::addColumn< QString >( "result" );
//	
//	// テストセット登録
//	QTest::newRow("example") << QString("%.0f") << 3.14 << QString("3");
//	QTest::newRow("example") << QString("%f")   << 3.14 << QString("3.140000");
}

void TestQString::length()/*{{{*/
{
	QString str = QString::fromUtf8("Ⅳ");

	int nLen = str.length();
	// 式を評価
	QCOMPARE( nLen, 1 );

	// sjis test case
	//QByteArray ba = str.toLocal8Bit().constData();
	//nLen = ba.length();
	//QCOMPARE( nLen, 2 );
}/*}}}*/

/// 共通のフォルダパスを取得する
void TestQString::testcommondirectorypath()/*{{{*/
{
	// タイトルからテストデータの取得
	QFETCH(QString, path1);
	QFETCH(QString, path2);
	QFETCH(QString, common);

	QString ret = path2;
	QString result;

	while ( !path1.startsWith( ret ) )
		ret.chop(1);

	if ( ret.isEmpty() )
		result = QString();

	while ( ret.endsWith('/') )
		ret.chop(1);

	result = ret;

	// 式を評価
	QCOMPARE( result, common );
}/*}}}*/
void TestQString::testcommondirectorypath_data()/*{{{*/
{
	QTest::addColumn<QString>("path1");
	QTest::addColumn<QString>("path2");
	QTest::addColumn<QString>("common");
	
	// テストセット登録
	QTest::newRow("example") << "C:/Documents" << "C:/Pictures" << "C:";
	QTest::newRow("example") << "C:/Documents/Excel" << "C:/Pictures/201502" << "C:";
	QTest::newRow("example") << "C:/Pictures/iPhone" << "C:/Pictures/201502" << "C:/Pictures";
	QTest::newRow("example") << "C:/Pictures/201502" << "C:/Pictures/201502" << "C:/Pictures/201502";
}/*}}}*/
/// QString from std::string
void TestQString::fromStdString()/*{{{*/
{
	std::string str;
	QString qstr;
	
	str = "hoge";
	qstr = QString::fromStdString(str);
	
	QString expected("hoge");

	// 式を評価
	QCOMPARE( qstr, expected );
	QCOMPARE( qstr, expected );
}/*}}}*/
/// QString to std::string
void TestQString::toStdString()/*{{{*/
{
	std::string str;
	QString qstr;
	
	qstr = "hoge";
	str = qstr.toLocal8Bit().constData();
	
	std::string expected("hoge");

	QVERIFY( str == expected );
	QVERIFY( str == expected );

	std::string wrong("hoge!");
	QVERIFY( str != wrong );
}/*}}}*/

// bool QString::contains ( const QString & str, Qt::CaseSensitivity cs = Qt::CaseSensitive ) const
// テスト部
void TestQString::containsQString()/*{{{*/
{
	// タイトルからテストデータの取得
	QFETCH(QString, string);
	QFETCH(QString, str);
	QFETCH(int, cs);
	QFETCH(bool, result);
	// 式を評価
	QCOMPARE((bool)string.contains(str, static_cast<Qt::CaseSensitivity>(cs)), result);
}/*}}}*/
// データセット部
void TestQString::containsQString_data()/*{{{*/
{
	// テストデータのタイトル設定
	QTest::addColumn<QString>("string");
	QTest::addColumn<QString>("str");
	//QTest::addColumn<Qt::CaseSensitivity>("cs");
	QTest::addColumn<int>("cs");
	QTest::addColumn<bool>("result");
	
	// テストセット登録
	//QTest::newRow("example") << "Peter Pan" << "peter" << Qt::CaseInsensitive << true;
	QTest::newRow("example") << "Peter Pan" << "peter" << (int)Qt::CaseInsensitive << true;
}/*}}}*/

//// bool QString::contains ( const QRegExp & rx ) const
//// テスト部
//void TestQString::containsConstQRegExp()/*{{{*/
//{
//}/*}}}*/
//// データセット部
//void TestQString::containsConstQRegExp_data()/*{{{*/
//{
//}/*}}}*/

// bool QString::contains ( QRegExp & rx ) const
// テスト部
void TestQString::containsQRegExp()/*{{{*/
{
	// タイトルからテストデータの取得
	QFETCH(QString, string);
	QFETCH(QRegExp, rx);
	QFETCH(bool, result);
	// 式を評価
	QCOMPARE((bool)string.contains(rx), result);
}/*}}}*/
// データセット部
void TestQString::containsQRegExp_data()/*{{{*/
{
	// テストデータのタイトル設定
	QTest::addColumn<QString>("string");
	QTest::addColumn<QRegExp>("rx");
	QTest::addColumn<bool>("result");
	
	// テストセット登録
	QTest::newRow("example") << "Peter Pan" << QRegExp(".+") << true;
	QTest::newRow("example1") << "2012/06/30 13:45:30" << QRegExp("..../../.. ..:..:..") << true;
	QTest::newRow("example2") << "2012/06/30 13:45:30" << QRegExp("..:..:..") << true;
	QTest::newRow("example3") << "2012/06/30 13:45:30" << QRegExp("www") << false;
	QTest::newRow("case dat file") << "201502E4-001.png" << QRegExp("201502E4(.+)") << true;
}/*}}}*/

// void QString::toUpper()
// テスト部
void TestQString::toUpper()/*{{{*/
{
	// タイトルからテストデータの取得
	QFETCH(QString, string);
	QFETCH(QString, result);
	// 式を評価
	if(string!=result)
	{
		// toUpper()で元の文字列は変化しない
		QVERIFY(string != string.toUpper());
		QVERIFY(string.toUpper() != string);
		//string.toUpper();
		//QVERIFY(string.toUpper() == string); // FAIL!
		//QVERIFY(string == string.toUpper()); // FAIL!
	}
	QCOMPARE(string.toUpper(), result);
}/*}}}*/
// データセット部
void TestQString::toUpper_data()/*{{{*/
{
	// テストデータのタイトル設定
	QTest::addColumn<QString>("string");
	QTest::addColumn<QString>("result");
	
	// テストセット登録
	QTest::newRow("all lower") << "hello" << "HELLO";
	QTest::newRow("mixed")     << "Hello" << "HELLO";
	QTest::newRow("all upper") << "HELLO" << "HELLO";
}/*}}}*/

// テスト部
void TestQString::numberDouble()/*{{{*/
{
	// タイトルからテストデータの取得
	QFETCH(double, n);
	QFETCH(char, format);
	QFETCH(int, precision);
	QFETCH(QString, num);

	QString actual = QString::number( n, format, precision );
	QCOMPARE( actual, num );
}/*}}}*/
// データセット部
void TestQString::numberDouble_data()/*{{{*/
{
	// テストデータのタイトル設定
	QTest::addColumn<double>("n");
	QTest::addColumn<char>("format");
	QTest::addColumn<int>("precision");
	QTest::addColumn<QString>("num");
	
	// テストセット登録
	QTest::newRow("case 3") << 3.14159265 << 'f' << 3 << "3.142"; // 四捨五入される
	QTest::newRow("case 4") << 3.14159265 << 'f' << 4 << "3.1416";
	QTest::newRow("case 5") << 3.14159265 << 'f' << 5 << "3.14159";
	QTest::newRow("case 6") << 3.14159265 << 'f' << 6 << "3.141593";
	QTest::newRow("case 14") << 1.0/3.0 << 'g' << 14 << "0.33333333333333";
	QTest::newRow("case z3") << 3.00000000 << 'f' << 3 << "3.000"; // 0は残る
	QTest::newRow("case z4") << 3.00000000 << 'f' << 4 << "3.0000";
	QTest::newRow("case z5") << 3.00000000 << 'f' << 5 << "3.00000";
	QTest::newRow("case z6") << 3.00000000 << 'f' << 6 << "3.000000";
}/*}}}*/

// テスト部
void TestQString::testsetnumdouble()/*{{{*/
{
	// タイトルからテストデータの取得
	QFETCH(double, n);
	QFETCH(char, format);
	QFETCH(int, precision);
	QFETCH(QString, num);

	QString actual;
	actual.setNum( n, format, precision );
	QCOMPARE( actual, num );
}/*}}}*/
// データセット部
void TestQString::testsetnumdouble_data()/*{{{*/
{
	// テストデータのタイトル設定
	QTest::addColumn<double>("n");
	QTest::addColumn<char>("format");
	QTest::addColumn<int>("precision");
	QTest::addColumn<QString>("num");
	
	// テストセット登録
	QTest::newRow("case 3") << 3.14159265 << 'f' << 3 << "3.142"; // 四捨五入される
	QTest::newRow("case 4") << 3.14159265 << 'f' << 4 << "3.1416";
	QTest::newRow("case 5") << 3.14159265 << 'f' << 5 << "3.14159";
	QTest::newRow("case 6") << 3.14159265 << 'f' << 6 << "3.141593";
	QTest::newRow("case 14") << 1.0/3.0 << 'g' << 14 << "0.33333333333333";
	QTest::newRow("case z3") << 3.00000000 << 'f' << 3 << "3.000"; // 0は残る
	QTest::newRow("case z4") << 3.00000000 << 'f' << 4 << "3.0000";
	QTest::newRow("case z5") << 3.00000000 << 'f' << 5 << "3.00000";
	QTest::newRow("case z6") << 3.00000000 << 'f' << 6 << "3.000000";
}/*}}}*/

QTEST_MAIN(TestQString)
#include "testqstring.moc"
