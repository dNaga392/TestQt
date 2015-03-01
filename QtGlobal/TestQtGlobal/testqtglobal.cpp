// QtGlobalのテスト
// testqtglobal.cpp

#include <QtTest/QtTest>

class TestQtGlobal: public QObject
{
	Q_OBJECT
private slots:
// const T & qMax ( const T & value1, const T & value2 )
	void qMaxInt();
	void qMaxInt_data();
};

// const T & qMax ( const T & value1, const T & value2 )
// テスト部
void TestQtGlobal::qMaxInt()/*{{{*/
{
	// タイトルからテストデータの取得
	QFETCH(int, val1);
	QFETCH(int, val2);
	QFETCH(int, max);
	// テスト
	QCOMPARE(qMax(val1, val2), max);
}/*}}}*/
// データセット部
void TestQtGlobal::qMaxInt_data()/*{{{*/
{
	// テストデータのタイトル設定
	QTest::addColumn<int>("val1");
	QTest::addColumn<int>("val2");
	QTest::addColumn<int>("max");
	
	// テストセット登録
	QTest::newRow("qMax(6,8)") << 6 << 8 << 8;
	QTest::newRow("qMax(8,6)") << 8 << 6 << 8;
	QTest::newRow("qMax(-8,6)") << -8 << 6 << 6;
	QTest::newRow("qMax(8,-6)") << 8 << -6 << 8;
	QTest::newRow("qMax(-8,-6)") << -8 << -6 << -6;
}/*}}}*/

QTEST_MAIN(TestQtGlobal)
#include "testqtglobal.moc"
