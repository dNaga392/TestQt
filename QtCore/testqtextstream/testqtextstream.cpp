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
			// The returned line has no trailing end-of-line character(s).
			bool actual = str.contains(QRegExp("\r$|\n$|\r\n$"));
#ifdef DEBUG_OUTPUT
			if (actual)
			{
				qDebug() << "contains end-of-line charactor(s) :" << str;
			}
#endif // DEBUG_OUTPUT
			QCOMPARE(actual, false);
		}
	}
	file.close();
}

//int main(int argc, char *argv[])
//{
//	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
//
//	QFile file("C:\\work\\CheckQTextStream\\test.txt");
//	if(!file.open(QIODevice::WriteOnly))
//	{
//		return 0;
//	}
//	QTextStream out(&file);
//	out << "text" << QString("test") << endl;
//	return 0;
//}

QTEST_MAIN(TestQTextStream)
#include "testqtextstream.moc"
