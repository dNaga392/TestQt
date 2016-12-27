///	@file	testqfile.cpp
///	@brief	QFileのテスト

#include <QtTest/QtTest>
#include <QtCore/QFile>
#include <QtCore/QStringList>

#include <cmath>

#ifdef QT_DEBUG
//#define DEBUG_OUTPUT
#endif // QT_DEBUG

///	QFileのテストクラス
class TestQFile
	: public QObject
{
	Q_OBJECT

private Q_SLOTS:
	void readLine_data();
	void readLine();
	void testseek_tobegin_data();
	void testseek_tobegin();

};

void TestQFile::readLine_data()
{
	QTest::addColumn<QString>("strFilePath");

	// テストセット登録
	QString strPath;
	// 有効なパス
	strPath = QCoreApplication::applicationDirPath();
	strPath.append("/../file/sample_file.txt");
	QTest::newRow("case default") << strPath;
}

void TestQFile::readLine()
{
	QFETCH(QString, strFilePath);

	QFile file(strFilePath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qFatal(("Error: file is not opened.[%s]"), qPrintable(strFilePath));
	}
	while (!file.atEnd())
	{
		QString str(file.readLine());
		if (!file.atEnd())
		{
			// a string read by qtextstream contains newline charactor(s).
			bool actual = str.contains(QRegExp("\r$|\n$|\r\n$"));
#ifdef DEBUG_OUTPUT
			if (!actual)
			{
				qDebug() << "not contain newline charactor(s) :" << str;
			}
#endif // DEBUG_OUTPUT
			QCOMPARE(actual, true);
		}
	}
	file.close();
}

/// The test data of QFile::seek() for seak to beginning
void TestQFile::testseek_tobegin_data()
{
	// テストデータのタイトル設定
	QTest::addColumn<QString>("strFilePath");
	
	// テストセット登録
	QString strPath;
	// 有効なパス
	strPath = QCoreApplication::applicationDirPath();
	strPath.append("/../file/sample_file.txt");
	QTest::newRow("case default") << strPath;
}

/// The test of QFile::seek() for seak to beginning
void TestQFile::testseek_tobegin()
{
	// タイトルからテストデータの取得
	QFETCH(QString, strFilePath);

	QFile file(strFilePath);

	bool bResult;
	bResult = file.open(QIODevice::ReadOnly | QIODevice::Text);
	if (!bResult)
	{
		qFatal(("Error: file is not opened.[%s]"), qPrintable(strFilePath));
	}

	QStringList list1;
	while (!file.atEnd())
	{
		QByteArray baLine = file.readLine();
		//qDebug() << "Read: [" << baLine.constData() << "]";
		//qDebug() << "Read: [" << (double)atof(baLine.constData()) << "]";
		list1 << QString(baLine);
	}

	//qDebug(("-------- Seek to beginning --------"));
	file.seek(0); // seak to beginning
	
	QStringList list2;
	while (!file.atEnd())
	{
		QByteArray baLine = file.readLine();
		//qDebug(("Read: [%s]"), baLine.constData());
		//qDebug(("Read: [%f]"), (double)atof(baLine.constData()));
		list2 << QString(baLine);
	}

	QCOMPARE(list1.size(), list2.size()); // equal size
	for (int i = 0; i < list1.size(); ++i)
	{
		QCOMPARE(list1[i], list2[i]); // equal string
	}

	file.close();
}

QTEST_MAIN(TestQFile)
#include "testqfile.moc"
