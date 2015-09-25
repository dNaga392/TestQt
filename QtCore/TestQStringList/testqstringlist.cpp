// QStringListのテスト
// qstringlist.cpp

#include <QtTest/QtTest>

class TestQStringList: public QObject
{
	Q_OBJECT
private slots:
	// 順序確認
	void checkOrder();
	// int QStringList::indexOf(const QString & value, int from = 0) const
	void indexOfQString();
	void indexOfQString_data();
	// QString QStringList::join ( const QString & separator ) const
	void join();
	void join_data();
	// void QStringList::sort()
	void sort();
	void sort_data();
};

// 順序確認
// QStringList は FIFOである
void TestQStringList::checkOrder()/*{{{*/
{
	// タイトルからテストデータの取得
	QStringList list;
	list << "Zero!" << "One!" << "Two!";
	int i=0;
	// foreachでFIFOであることを確認
	foreach(QString str, list)
	{
		if(i==0)
		{
			QCOMPARE(str, QString("Zero!"));
		}
		else if(i==1)
		{
			QCOMPARE(str, QString("One!"));
		}
		else if(i==2)
		{
			QCOMPARE(str, QString("Two!"));
		}
		++i;
	}
}/*}}}*/

// int QStringList::indexOf(const QString & value, int from = 0) const
// テスト部
void TestQStringList::join()/*{{{*/
{
	// タイトルからテストデータの取得
	QFETCH( QStringList, data );
	QFETCH( QString, separator );
	QFETCH( QString, result );
	// 式を評価
	QCOMPARE( data.join( separator ), result );
}/*}}}*/
// データセット部
void TestQStringList::join_data()/*{{{*/
{
	// テストデータのタイトル設定
	QTest::addColumn< QStringList >( "data" );
	QTest::addColumn< QString >( "separator" );
	QTest::addColumn< QString >( "result" );

	// テストセット登録
	QStringList listData;
	QString strSeparator;
	QString strResult;

	listData << "Kaga";
	strSeparator = ";";
	strResult = "Kaga";
	QTest::newRow("IJN CV Kaga") << listData << strSeparator << strResult;

	listData.clear();
	strSeparator.clear();

	listData << "Kaga" << "Akagi" << "Hiryu" << "Soryu";
	strSeparator = ";";
	strResult = "Kaga;Akagi;Hiryu;Soryu";
	QTest::newRow("IJN Nagumo fleet") << listData << strSeparator << strResult;

	listData.clear();
	strSeparator.clear();

	listData << "Kaga" << "Akagi" << "Hiryu" << "Soryu";
	strResult = "KagaAkagiHiryuSoryu";
	QTest::newRow("IJN Nagumo fleet (nospace)") << listData << strSeparator << strResult;
}/*}}}*/

// int QStringList::indexOf(const QString & value, int from = 0) const
// テスト部
void TestQStringList::indexOfQString()/*{{{*/
{
	// タイトルからテストデータの取得
	QFETCH(QStringList, iOfStrData);
	QFETCH(QString, iOfStrValue);
	QFETCH(int, iOfStrResult);
	// 式を評価
	QCOMPARE(iOfStrData.indexOf(iOfStrValue), iOfStrResult);
}/*}}}*/
// データセット部
void TestQStringList::indexOfQString_data()/*{{{*/
{
	// テストデータのタイトル設定
	QTest::addColumn<QStringList>("iOfStrData");
	QTest::addColumn<QString>("iOfStrValue");
	QTest::addColumn<int>("iOfStrResult");

	// テストセット登録
	QStringList testList;
	testList << "Kaga" << "Akagi" << "Hiryu" << "Soryu";
	QString val;
	val = "Hiryu";
	int result = 2;
	QTest::newRow("IJN CV") << testList << val << result;
}/*}}}*/

// void QStringList::sort()
// テスト部
void TestQStringList::sort()/*{{{*/
{
	// タイトルからテストデータの取得
	QFETCH(QStringList, sortData);
	QFETCH(QStringList, sortResult);
	// ソート
	sortData.sort();
	// 式を評価
	//QVERIFY(testList.sort() == resultList);
	QCOMPARE(sortData, sortResult);
}/*}}}*/
// データセット部
void TestQStringList::sort_data()/*{{{*/
{
	// テストデータのタイトル設定
	QTest::addColumn<QStringList>("sortData");
	QTest::addColumn<QStringList>("sortResult");

	// テストセット登録
	QStringList testList;
	testList << "2_1" << "2_2" << "1" << "3";
	QStringList resultList;
	resultList << "1" << "2_1" << "2_2" << "3";
	QTest::newRow("number list") << testList << resultList;
}/*}}}*/

QTEST_MAIN(TestQStringList)
#include "testqstringlist.moc"
