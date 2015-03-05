// QDataStreamのテスト
// testqdatastream.cpp

#include <QtTest/QtTest>
#include <QDataStream>

#include <QDir>
#include <QFile>
#include <QString>

class TestQDataStream: public QObject
{
	Q_OBJECT
private slots:
	void readRawData();
	void readRawData_data();
};

void TestQDataStream::readRawData()/*{{{*/
{
	QFETCH(qint32, num);
	QFETCH(qint32, expected);
	QFETCH(int, len);

	QString dirPath = QDir::currentPath();
	QString fileName = "test.dat";
	QString filePath = QString( "%1/%2" ).arg( dirPath ).arg( fileName );

	// write
	QFile outFile( filePath );
	if ( !outFile.open( QIODevice::WriteOnly ) )
	{
		qDebug() << "[Error] Failed open file to write.";
		return;
	}
	QDataStream out ( &outFile );
	out << num;

	outFile.close();

	// read
	QFile inFile( filePath );
	if ( !inFile.open( QIODevice::ReadOnly ) )
	{
		qDebug() << "[Error] Failed open file to read.";
		return;
	}

	QDataStream in ( &inFile );

	char *temp = new char[len];
	Q_CHECK_PTR(temp);
	int size = len;
	in.readRawData( temp, size );
	int actual = 0;
	for ( int i = 0; i < len; ++i )
	{
		int shiftSize = ( 8 * ( len - i - 1 ) );
		//qDebug( "%d, %d", (int)temp[i], shiftSize );
		actual += ( temp[i] << shiftSize );
	}
	//int out2 = (temp[0] << 24) + (temp[1] << 16) + (temp[2] << 8)+(temp[3]);
	//qDebug("%d, %d", outDt, out2);

	delete [] temp;

	inFile.close();
	// 式を評価
	QCOMPARE( actual, expected );
}/*}}}*/

void TestQDataStream::readRawData_data()/*{{{*/
{
	// テストデータのタイトル設定
	QTest::addColumn<qint32>("num");
	QTest::addColumn<qint32>("expected");
	QTest::addColumn<int>("len");
	
	// テストセット
	QTest::newRow("case 0") << 0x00221129 << 0x00 << 1;
	QTest::newRow("case 1") << 0x06221129 << 0x06 << 1;
	QTest::newRow("case 2") << 0x06221129 << 0x0622 << 2;
	QTest::newRow("case 3") << 0x06221129 << 0x062211 << 3;
	QTest::newRow("case 4") << 0x06221129 << 0x06221129 << 4;
}/*}}}*/

QTEST_MAIN(TestQDataStream)
#include "testqdatastream.moc"
