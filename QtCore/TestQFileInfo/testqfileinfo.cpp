// QFileInfo�̃e�X�g
// testqfileinfo.cpp

#include <QtTest/QtTest>
#include <QFileInfo>

class TestQFileInfo: public QObject
{
	Q_OBJECT
private slots:
	void test();
	void test_data();
	void dirtest();
	void dirtest_data();
};

// �e�X�g��
void TestQFileInfo::test()/*{{{*/
{
	// �^�C�g������e�X�g�f�[�^�̎擾
	QFETCH(QString, directory);
	QFETCH(QString, relative);
	QFETCH(QString, absolute);
	// ����]��
	QDir dir(directory);
	QFileInfo info(dir, relative);
	//QCOMPARE(info.absoluteFilePath(), absolute); // FALSE
	QFileInfo infoAbs(absolute);
	//QCOMPARE(info.dir(), infoAbs.dir());//TRUE
	//QCOMPARE(info.dir().path(), infoAbs.dir().path()); // FALSE
	// ���΃p�X������菜���Ă݂�
	QString path = info.absoluteFilePath();
	// ��ʃf�B���N�g���w��̒u��
	QRegExp parSys("\\w+/\\.\\./");
	while(path.contains(parSys))
	{
		qDebug() << "parent replace";
		qDebug() << path;
		path = path.replace(parSys, "");
		qDebug() << path;
	}
	// �N�_�f�B���N�g���w��̒u��
	QRegExp curSys("\\./");
	while(path.contains(curSys))
	{
		qDebug() << "current replace";
		qDebug() << path;
		path = path.replace(curSys, "");
		qDebug() << path;
	}
	QCOMPARE(path, absolute); // TRUE

}/*}}}*/
// �f�[�^�Z�b�g��
void TestQFileInfo::test_data()/*{{{*/
{
	// �e�X�g�f�[�^�̃^�C�g���ݒ�
	QTest::addColumn<QString>("directory");
	QTest::addColumn<QString>("relative");
	QTest::addColumn<QString>("absolute");
	
	// �e�X�g�Z�b�g�o�^
	QTest::newRow("current Path") << "C:/Data" << "ie6.png" << "C:/Data/ie6.png";
	QTest::newRow("current sysPath") << "C:/Data" << "./ie6.png" << "C:/Data/ie6.png";
	QTest::newRow("twice current sysPath") << "C:/Data" << "././ie6.png" << "C:/Data/ie6.png";
	QTest::newRow("parent sysPath") << "C:/Qt" << "../Data/ie6.png" << "C:/Data/ie6.png";
	QTest::newRow("twice parent sysPath") << "C:/Qt/bin" << "../../Data/ie6.png" << "C:/Data/ie6.png";
	QTest::newRow("twice parent sysPath") << "C:/Qt/bin4" << "../../Data/ie6.png" << "C:/Data/ie6.png";
}/*}}}*/

// �e�X�g��
void TestQFileInfo::dirtest()/*{{{*/
{
	// �^�C�g������e�X�g�f�[�^�̎擾
	QFETCH(QString, path);
	QFETCH(QString, dirPath);
	// ����]��
	QDir dir(path);
	QCOMPARE(dir.path(), dirPath);

}/*}}}*/
// �f�[�^�Z�b�g��
void TestQFileInfo::dirtest_data()/*{{{*/
{
	// �e�X�g�f�[�^�̃^�C�g���ݒ�
	QTest::addColumn<QString>("path");
	QTest::addColumn<QString>("dirPath");
	
	// �e�X�g�Z�b�g�o�^
	QTest::newRow("dir path") << "C:/Data" << "C:/Data";
	QTest::newRow("dir path with sep") << "C:/Data/" << "C:/Data";
	//QTest::newRow("file path") << "C:/Data/ie6.png" << "C:/Data"; //FAIL!
}/*}}}*/

QTEST_MAIN(TestQFileInfo)
#include "testqfileinfo.moc"
