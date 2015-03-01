// QStatusBarのテスト
// testqstatusbar.cpp

#include <QtGui>
#include <QtTest/QtTest>

class TestQStatusBar: public QObject
{
	Q_OBJECT
private slots:
// void QStatusBar::showMessage ( const QStatusBar & message, int timeout = 0 ) [slot]
	void showMessage();
	void showMessage_data();
};

// void QStatusBar::showMessage ( const QStatusBar & message, int timeout = 0 ) [slot]
// テスト部
void TestQStatusBar::showMessage()/*{{{*/
{
	// タイトルからテストデータの取得
	QFETCH(QString, message);
	QFETCH(int, timeout);
	// 式を評価
	QStatusBar bar;
	bar.showMessage(message, timeout);
	QCOMPARE(bar.currentMessage(), message);
}/*}}}*/
// データセット部
void TestQStatusBar::showMessage_data()/*{{{*/
{
	// テストデータのタイトル設定
	QTest::addColumn<QString>("message");
	QTest::addColumn<int>("timeout");
	
	// テストセット登録
	QTest::newRow("default timeout") << "message" << 0;
	QTest::newRow("timeout 3 secconds") << "message" << 3000;
}/*}}}*/

QTEST_MAIN(TestQStatusBar)
#include "testqstatusbar.moc"
