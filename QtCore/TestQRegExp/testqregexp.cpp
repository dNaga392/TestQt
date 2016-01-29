// QRegExpのテスト
// testqregexp.cpp

#include <QtTest/QtTest>
//#include <QRegExp>

class TestQRegExp
	: public QObject
{
	Q_OBJECT
private slots:

// int QRegExp::indexIn ( const QString & str, int offset = 0, CaretMode caretMode = CaretAtZero ) const

	void indexIn();
	void indexIn_data();
// bool QRegExp::isValid () const
	void isValid();
	void isValid_data();
	void exactMatch();
	void exactMatch_data();
};

void TestQRegExp::exactMatch()
{
	QFETCH( QString, pattern );
	QFETCH( QString, str );
	QFETCH( bool, result );

	QRegExp rx( pattern );
	QCOMPARE( rx.exactMatch( str ), result );
}
void TestQRegExp::exactMatch_data()/*{{{*/
{
	// テストデータのタイトル設定
	QTest::addColumn< QString >("pattern");
	QTest::addColumn< QString >("str");
	QTest::addColumn< bool >("result");

	QString pattern;
	QString str;
	bool result;

	// テストセット登録
	pattern = "201502E4(.+)";
	str = "201502E4-001.jpg";
	result = true;
	QTest::newRow("filename") << pattern << str << result;
	pattern = "[0123456789]*";
	str = "456168416631";
	result = true;
	QTest::newRow("numeric") << pattern << str << result;
	pattern = "[0123456789]*";
	str = "";
	result = true;
	QTest::newRow("numeric empty") << pattern << str << result;
	pattern = "[0123456789]*";
	str = "2.34E+010";
	result = false;
	QTest::newRow("numeric error") << pattern << str << result;
}/*}}}*/

// int QRegExp::indexIn ( const QString & str, int offset = 0, CaretMode caretMode = CaretAtZero ) const
// テスト部
void TestQRegExp::indexIn()/*{{{*/
{
	// タイトルからテストデータの取得
	QFETCH(QRegExp, rx);
	QFETCH(QString, str);
	QFETCH(int, pos);
	//qDebug() << str;
	// 式を評価
	//QVERIFY(testList.isValid() == resultList);
	QCOMPARE(rx.indexIn(str), pos);
}/*}}}*/
// データセット部
void TestQRegExp::indexIn_data()/*{{{*/
{
	// テストデータのタイトル設定
	QTest::addColumn<QRegExp>("rx");
	QTest::addColumn<QString>("str");
	QTest::addColumn<int>("pos");

	// テストセット登録
	QTest::newRow("include file") << QRegExp("^#include \"(\\w+\\.(h|cpp))\"") << "#include \"application.h\"" << 0;
	QTest::newRow("include library") << QRegExp("^#include <(\\w+)>") << "#include <QApplication>" << 0;
	QTest::newRow("include parent file") << QRegExp("^#include \"((\\.+/)*\\w+\\.(h|cpp))\"") << "#include \"../mainwindow.h\"" << 0;
}/*}}}*/

// void QRegExp::isValid()
// テスト部
void TestQRegExp::isValid()/*{{{*/
{
	// タイトルからテストデータの取得
	QFETCH(QString, isValidPattern);
	QFETCH(bool, isValidResult);
	//qDebug() << isValidPattern;
	// テスト
	QRegExp rx(isValidPattern);
	// 式を評価
	//QVERIFY(testList.isValid() == resultList);
	QCOMPARE(rx.isValid(), isValidResult);
}/*}}}*/
// データセット部
void TestQRegExp::isValid_data()/*{{{*/
{
	// テストデータのタイトル設定
	QTest::addColumn<QString>("isValidPattern");
	QTest::addColumn<bool>("isValidResult");

	// テストセット登録
	QTest::newRow("valid pattern") << QString("[a-z]") << true;
	QTest::newRow("invalid pattern") << QString("[a-z") << false;
}/*}}}*/

QTEST_MAIN(TestQRegExp)
#include "testqregexp.moc"
