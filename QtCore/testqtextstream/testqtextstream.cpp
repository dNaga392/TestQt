///	@file	testqfile.cpp
///	@brief	QFileのテスト

#include <QtTest/QtTest>
#include <QtCore/QFile>
#include <QtCore/QTextStream>

#ifdef QT_DEBUG
//#define DEBUG_OUTPUT
#endif // QT_DEBUG

///	QFileのテストクラス
class TestQTextStream
	: public QObject
{
	Q_OBJECT

private Q_SLOTS:
	void readLine_data();
	void readLine();

};

void TestQTextStream::readLine_data()
{
	QTest::addColumn<QString>("strFilePath");

	// テストセット登録
	QString strPath;
	// 有効なパス
	strPath = QCoreApplication::applicationDirPath();
	strPath.append("/../file/sample_file.txt");
	QTest::newRow("case default") << strPath;
}

void TestQTextStream::readLine()
{
	QFETCH(QString, strFilePath);

	QFile file(strFilePath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qFatal(("Error: file is not opened.[%s]"), qPrintable(strFilePath));
	}
	QTextStream in(&file);
	while (!in.atEnd())
	{
		QString str(in.readLine());
		if (!file.atEnd())
		{
			// a string read by qtextstream does not contain newline charactor(s).
			bool actual = str.contains(QRegExp("\r$|\n$|\r\n$"));
#ifdef DEBUG_OUTPUT
			if (actual)
			{
				qDebug() << "contains newline charactor(s) :" << str;
			}
#endif // DEBUG_OUTPUT
			QCOMPARE(actual, false);
		}
	}
	file.close();
}

QTEST_MAIN(TestQTextStream)
#include "testqtextstream.moc"
