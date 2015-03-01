// QImageWriter�̃e�X�g
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
// �e�X�g��
void TestQImageWriter::write()/*{{{*/
{
	// �^�C�g������e�X�g�f�[�^�̎擾
	QFETCH(QImage, image);
	QFETCH(QString, fileName);
	QFETCH(QByteArray, format);
	QFETCH(bool, result);
	// ����]��
	QImageWriter writer(fileName,format);
	QVERIFY(!image.isNull());
	QCOMPARE(writer.write(image), result);
	QVERIFY(QFile::exists(fileName));
	//QCOMPARE(writer.write(image), result);
}/*}}}*/
// �f�[�^�Z�b�g��
void TestQImageWriter::write_data()/*{{{*/
{
	// �e�X�g�f�[�^�̃^�C�g���ݒ�
	QTest::addColumn<QImage>("image");
	QTest::addColumn<QString>("fileName");
	QTest::addColumn<QByteArray>("format");
	QTest::addColumn<bool>("result");
	
	// �e�X�g�Z�b�g�o�^
	QImage image("../data/Lenna.png");
	QTest::newRow("save jpeg") << image << "../result/Lenna.jpg" << QByteArray("JPG") << true;
	QTest::newRow("save tiff") << image << "../result/Lenna.tif" << QByteArray("TIFF") << true;
}/*}}}*/

QTEST_MAIN(TestQImageWriter)
#include "testqimagewriter.moc"
