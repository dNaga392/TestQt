// QStringのテスト
// testqstring.cpp

#include <string>

#include <QtTest/QtTest>

class TestQString: public QObject
{
	Q_OBJECT
private slots:
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
	void toUpper();
	void toUpper_data();
	
	void fromStdString();
	void toStdString();
};

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

QTEST_MAIN(TestQString)
#include "testqstring.moc"
