///	@file	testqfile.cpp
///	@brief	QFileのテスト

#include <QtTest/QtTest>
#include <QtCore/QFile>
#include <QtCore/QStringList>

#include <math.h>

///	QFileのテストクラス
class TestQFile/*{{{*/
	: public QObject
{
	Q_OBJECT
private slots:
	void testseek_tobegin();
	void testseek_tobegin_data();

#ifdef QT_DEBUG
	/// [DEBUG]QStringListのダンプ
	bool dumpQStringList( QStringList & list, QString & fileName );
#endif // QT_DEBUG

};/*}}}*/

/// The test of QFile::seek() for seak to beginning
void TestQFile::testseek_tobegin()/*{{{*/
{
	// タイトルからテストデータの取得
	QFETCH(QString, strFilePath);

	QFile file( strFilePath );

	bool bResult;
	bResult = file.open( QIODevice::ReadOnly | QIODevice::Text );
	if ( !bResult )
	{
		qFatal( ("Error: file is not opened.[ %s ]"), qPrintable( strFilePath ) );
	}

	QStringList list1;
	while ( !file.atEnd() )
	{
		QByteArray baLine = file.readLine();
		//qDebug( ("Read: [ %s ]"), baLine.constData() );
		qDebug( ("Read: [ %f ]"), (double)atof( baLine.constData() ) );
		list1 << QString( baLine );
	}

	qDebug( ("-------- Seek to beginning --------") );
	file.seek( 0 ); // seak to beginning
	
	QStringList list2;
	while ( !file.atEnd() )
	{
		QByteArray baLine = file.readLine();
		//qDebug( ("Read: [ %s ]"), baLine.constData() );
		qDebug( ("Read: [ %f ]"), (double)atof( baLine.constData() ) );
		list2 << QString( baLine );
	}

	QCOMPARE( list1.size(), list2.size() ); // equal size
	for ( int i = 0; i < list1.size(); ++i  )
	{
		QCOMPARE( list1[ i ], list2[ i ] ); // equal string
	}

	file.close();
}/*}}}*/
/// The test data of QFile::seek() for seak to beginning
void TestQFile::testseek_tobegin_data()/*{{{*/
{
	// テストデータのタイトル設定
	QTest::addColumn<QString>("strFilePath");
	
	// テストセット登録
	QString strPath;
	// 有効なパス
	strPath = QDir::currentPath();
	strPath.append("/data/sample_file.txt");
	QTest::newRow("case default") << strPath;
}/*}}}*/

#ifdef QT_DEBUG

#include <QtCore/QFile>
#include <QtCore/QTextStream>

/// [DEBUG]QStringListのダンプ
bool TestQFile::dumpQStringList( QStringList & list, QString & fileName )/*{{{*/
{
	QFile file(fileName);
	bool bRet = file.open(QIODevice::WriteOnly);
	if (!bRet) {
		// ERROR
		qDebug("%s, %d: [Error] file is not opened.", __FILE__, __LINE__);
		return false;
	}
	QTextStream out(&file);
	foreach(QString text, list)
	{
		out << text << endl;
	}
	file.close();
	return true;
}/*}}}*/

#endif // QT_DEBUG

QTEST_MAIN(TestQFile)
#include "testqfile.moc"
