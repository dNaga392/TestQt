// QFileInfoのテスト
// testqfileinfo.cpp

#include <QtTest/QtTest>
#include <QFileInfo>

class TestQFileInfo: public QObject
{
	Q_OBJECT
private slots:
	void test();
	void test_data();
	void dirtest();
	void dirtest_data();
};

// テスト部
void TestQFileInfo::test()/*{{{*/
{
	// タイトルからテストデータの取得
	QFETCH(QString, directory);
	QFETCH(QString, relative);
	QFETCH(QString, absolute);
	// 式を評価
	QDir dir(directory);
	QFileInfo info(dir, relative);
	//QCOMPARE(info.absoluteFilePath(), absolute); // FALSE
	QFileInfo infoAbs(absolute);
	//QCOMPARE(info.dir(), infoAbs.dir());//TRUE
	//QCOMPARE(info.dir().path(), infoAbs.dir().path()); // FALSE
	// 相対パス情報を取り除いてみる
	QString path = info.absoluteFilePath();
	// 上位ディレクトリ指定の置換
	QRegExp parSys("\\w+/\\.\\./");
	while(path.contains(parSys))
	{
		qDebug() << "parent replace";
		qDebug() << path;
		path = path.replace(parSys, "");
		qDebug() << path;
	}
	// 起点ディレクトリ指定の置換
	QRegExp curSys("\\./");
	while(path.contains(curSys))
	{
		qDebug() << "current replace";
		qDebug() << path;
		path = path.replace(curSys, "");
		qDebug() << path;
	}
	QCOMPARE(path, absolute); // TRUE

}/*}}}*/
// データセット部
void TestQFileInfo::test_data()/*{{{*/
{
	// テストデータのタイトル設定
	QTest::addColumn<QString>("directory");
	QTest::addColumn<QString>("relative");
	QTest::addColumn<QString>("absolute");
	
	// テストセット登録
	QTest::newRow("current Path") << "C:/Data" << "ie6.png" << "C:/Data/ie6.png";
	QTest::newRow("current sysPath") << "C:/Data" << "./ie6.png" << "C:/Data/ie6.png";
	QTest::newRow("twice current sysPath") << "C:/Data" << "././ie6.png" << "C:/Data/ie6.png";
	QTest::newRow("parent sysPath") << "C:/Qt" << "../Data/ie6.png" << "C:/Data/ie6.png";
	QTest::newRow("twice parent sysPath") << "C:/Qt/bin" << "../../Data/ie6.png" << "C:/Data/ie6.png";
	QTest::newRow("twice parent sysPath") << "C:/Qt/bin4" << "../../Data/ie6.png" << "C:/Data/ie6.png";
}/*}}}*/

// テスト部
void TestQFileInfo::dirtest()/*{{{*/
{
	// タイトルからテストデータの取得
	QFETCH(QString, path);
	QFETCH(QString, dirPath);
	// 式を評価
	QDir dir(path);
	QCOMPARE(dir.path(), dirPath);

}/*}}}*/
// データセット部
void TestQFileInfo::dirtest_data()/*{{{*/
{
	// テストデータのタイトル設定
	QTest::addColumn<QString>("path");
	QTest::addColumn<QString>("dirPath");
	
	// テストセット登録
	QTest::newRow("dir path") << "C:/Data" << "C:/Data";
	QTest::newRow("dir path with sep") << "C:/Data/" << "C:/Data";
	//QTest::newRow("file path") << "C:/Data/ie6.png" << "C:/Data"; //FAIL!
}/*}}}*/

QTEST_MAIN(TestQFileInfo)
#include "testqfileinfo.moc"
