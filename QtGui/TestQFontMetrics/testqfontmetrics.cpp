/*! ******************************************************************
	@file	testqfontmetrics.cpp
	@brief	Test of QFontMetrics
******************************************************************* */
#include <QtTest/QtTest>
#include <QtGui/QFontMetrics>

//#include <QtGui/QFont>
#include <QtGui/QPainter>
#include <QtGui/QStaticText>

/*! ******************************************************************
	@brief	Test of QFontMetrics
******************************************************************* */
class TestQFontMetrics
	: public QObject
{
	Q_OBJECT

private Q_SLOTS:
	void size();
	void size_data();
};


//////////////////////////////////////////////////////////////////////
// private Q_SLOTS
//////////////////////////////////////////////////////////////////////

// テスト部
void TestQFontMetrics::size()
{
	// タイトルからテストデータの取得
	QFETCH(QFont, font);
	QFETCH(QString, text);
	QFETCH(QString, fileName);

	QFontMetrics fm(font);
	const int h = fm.height();
	const int w = fm.width(text);
	const QSize size = fm.size(Qt::TextSingleLine, text);
	QCOMPARE(size.height(), h);
	QCOMPARE(size.width(), w);

	if ( !fileName.isEmpty() ) {
		QPixmap pix(size);
		pix.fill();
		QPainter p(&pix);
		p.drawStaticText(0, 0, QStaticText(text));
		pix.save(fileName);
	}
}

// データセット部
void TestQFontMetrics::size_data()
{
	// テストデータのタイトル設定
	QTest::addColumn<QFont>("font");
	QTest::addColumn<QString>("text");
	QTest::addColumn<QString>("fileName");

	QString caseName;
	QFont font;
	QString text;
	QString fileName;

	// テストセット登録
	caseName = "case hoge";
	text = "hogehoge";
	fileName = "size_hoge.png";
	QTest::newRow(qPrintable(caseName)) << font << text << fileName;

	caseName = "case BISO";
	text = QString::fromUtf8("BIOSになりたい人生だった。。");
	fileName = "size_bios.png";
	QTest::newRow(qPrintable(caseName)) << font << text << fileName;
}


//////////////////////////////////////////////////////////////////////
// private
//////////////////////////////////////////////////////////////////////


QTEST_MAIN(TestQFontMetrics)

#include "testqfontmetrics.moc"

