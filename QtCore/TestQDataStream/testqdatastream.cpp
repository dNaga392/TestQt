// QDataStream‚ÌƒeƒXƒg
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
	void rwRaws();
	void rwBytes();
};

void TestQDataStream::rwRaws()/*{{{*/
{
	QString dirPath = QDir::currentPath();
	QString fileName = "testRaws.dat";
	QString filePath = QString( "%1/%2" ).arg( dirPath ).arg( fileName );

	// write
	QFile outFile( filePath );
	if ( !outFile.open( QIODevice::WriteOnly ) )
	{
		qDebug() << "[Error] Failed open file to write.";
		return;
	}
	QDataStream out ( &outFile );

	int length = 4;

	char outDt[length];
	outDt[0] = 0x0A;
	outDt[1] = 0x0B;
	outDt[2] = 0x0C;
	outDt[3] = 0x0D;
	
	out.writeRawData(outDt, length);

	outFile.close();

	// read
	QFile inFile( filePath );
	if ( !inFile.open( QIODevice::ReadOnly ) )
	{
		qDebug() << "[Error] Failed open file to read.";
		return;
	}
	QDataStream in ( &inFile );

	char temp[length];
	in.readRawData (temp, length);
	qDebug("%d, %d", outDt[0], temp[0]);
	qDebug("%d, %d", outDt[1], temp[1]);
	qDebug("%d, %d", outDt[2], temp[2]);
	qDebug("%d, %d", outDt[3], temp[3]);
	qDebug("%d, %d", outDt, temp);
//	QDataStream input (...);
//	QByteArray buffer;
//	int length = ...;
//	 
//	char temp* = 0;
//	input.readBytes (temp, length);
//	buffer.append (temp, length);
//	delete [] temp;
	inFile.close();
	// Ž®‚ð•]‰¿
	//QCOMPARE(map.count(), count);
}/*}}}*/

void TestQDataStream::rwBytes()/*{{{*/
{
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

	int length = 4;

	char outDt[length];
	outDt[0] = 0x0A;
	outDt[1] = 0x0B;
	outDt[2] = 0x0C;
	outDt[3] = 0x0D;
	
	out.writeBytes(outDt, length);

	outFile.close();

	// read
	QFile inFile( filePath );
	if ( !inFile.open( QIODevice::ReadOnly ) )
	{
		qDebug() << "[Error] Failed open file to read.";
		return;
	}
	QDataStream in ( &inFile );

	char *temp = 0;
	uint l = length;
	in.readBytes (temp, l);
	qDebug("%d, %d", outDt[0], temp[0]);
	qDebug("%d, %d", outDt[1], temp[1]);
	qDebug("%d, %d", outDt[2], temp[2]);
	qDebug("%d, %d", outDt[3], temp[3]);
	qDebug("%d, %d", outDt, temp);
	delete [] temp;
//	QDataStream input (...);
//	QByteArray buffer;
//	int length = ...;
//	 
//	char temp* = 0;
//	input.readBytes (temp, length);
//	buffer.append (temp, length);
//	delete [] temp;
	inFile.close();
	// Ž®‚ð•]‰¿
	//QCOMPARE(map.count(), count);
}/*}}}*/

QTEST_MAIN(TestQDataStream)
#include "testqdatastream.moc"
