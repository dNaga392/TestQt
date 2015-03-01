// QImageWriterのテスト
// testqimagewriter.cpp

#include <QtTest/QtTest>
#include <QImageWriter>

class TestQImageWriter: public QObject
{
	Q_OBJECT
private slots:
// bool QImageWriter::write ( const QImage & image )
	void write();
	void write_data();
};

// bool QImageWriter::write ( const QImage & image )
// テスト部
void TestQImageWriter::write()/*{{{*/
{
	// タイトルからテストデータの取得
	QFETCH(QImage, image);
	QFETCH(QString, fileName);
	QFETCH(QByteArray, format);
	QFETCH(bool, result);
	// 式を評価
	QImageWriter writer(fileName,format);
	QVERIFY(!image.isNull());
	QCOMPARE(writer.write(image), result);
	QVERIFY(QFile::exists(fileName));
	//QCOMPARE(writer.write(image), result);
}/*}}}*/
// データセット部
void TestQImageWriter::write_data()/*{{{*/
{
	// テストデータのタイトル設定
	QTest::addColumn<QImage>("image");
	QTest::addColumn<QString>("fileName");
	QTest::addColumn<QByteArray>("format");
	QTest::addColumn<bool>("result");
	
	// テストセット登録
	QImage image("../data/Lenna.png");
	QTest::newRow("save jpeg") << image << "../result/Lenna.jpg" << QByteArray("JPG") << true;
	QTest::newRow("save tiff") << image << "../result/Lenna.tif" << QByteArray("TIFF") << true;
}/*}}}*/

QTEST_MAIN(TestQImageWriter)
#include "testqimagewriter.moc"
