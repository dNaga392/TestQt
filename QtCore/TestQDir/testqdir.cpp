///============================================================
///	@file	testqdir.cpp
///	@brief	QDir�̃e�X�g
///============================================================

#include <QtTest/QtTest>
#include <QtCore/QDir>

#include <QtCore/QStringList>

///	QDir�̃e�X�g�N���X
class TestQDir/*{{{*/
	: public QObject
{
	Q_OBJECT

private slots:
	///	�e�X�g�P�[�X�̏����ݒ�����܂��B
	void initTestCase();
	void testmkpath();
	void testmkpath_data();
	void testcleanabsolutefilepath();
	void testcleanabsolutefilepath_data();
	void testpath();
	void testpath_data();
	void alldirstopdown();
	///	�g�b�v�_�E���ŁA�t�H���_�p�X�ꗗ���擾
	void alldirstopdownwithcurrent();
#ifdef QT_DEBUG
	/// [DEBUG]QStringList�̃_���v
	bool dumpQStringList( QStringList & list, QString & fileName );
#endif
};/*}}}*/
//#include "../Plugin/Dialog/FileListDialog.h"
//	QString parent_folder = QDir::currentPath();
//QStringList all_dirs;
//    all_dirs << parent_folder;
//    QDirIterator directories(parent_folder, QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
// 
//    while(directories.hasNext() ){
//        directories.next();
//        all_dirs << directories.filePath();
//    }
//	FileListDialog dlg;
//	dlg.setFileNames( all_dirs );
//	dlg.exec();

///	@brief	�e�X�g�P�[�X�̏����ݒ�����܂��B
void TestQMessageBox::initTestCase()/*{{{*/
{
	// ���{��Ή�
	QTextCodec::setCodecForCStrings( QTextCodec::codecForLocale() );
}/*}}}*/

void TestQDir::alldirstopdown()/*{{{*/
{
	QString parent_folder;
	//parent_folder = "C:/Pictures";
	parent_folder = QDir::currentPath();
	QDir dir = QDir(parent_folder);
	dir.cdUp();
	parent_folder = dir.path();
	QStringList all_dirs;
	//all_dirs << parent_folder;
    QDirIterator directories(parent_folder, QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
 
    while(directories.hasNext()){
        directories.next();
        all_dirs << directories.filePath();
    }
	QVERIFY( !all_dirs.contains( parent_folder ) );
	int nResultCount = all_dirs.count();
	all_dirs.removeDuplicates();
	QCOMPARE( nResultCount, all_dirs.count() );
#ifdef QT_DEBUG
	QString strFileName;
	strFileName = QString("%1/%2").arg(parent_folder).arg("alldirstopdown.txt");
	dumpQStringList( all_dirs, strFileName );
#endif
}/*}}}*/

void TestQDir::alldirstopdownwithcurrent()/*{{{*/
{
	QString parent_folder;
	//parent_folder = "C:/Pictures";
	parent_folder = QDir::currentPath();
	QDir dir = QDir(parent_folder);
	dir.cdUp();
	parent_folder = dir.path();
	QStringList all_dirs;
	all_dirs << parent_folder;
    QDirIterator directories(parent_folder, QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
 
    while(directories.hasNext()){
        directories.next();
        all_dirs << directories.filePath();
    }
	QVERIFY( all_dirs.contains( parent_folder ) );
	int nResultCount = all_dirs.count();
	all_dirs.removeDuplicates();
	QCOMPARE( nResultCount, all_dirs.count() );
#ifdef QT_DEBUG
	QString strFileName;
	strFileName = QString("%1/%2").arg(parent_folder).arg("alldirstopdownwithcurrent.txt");
	dumpQStringList( all_dirs, strFileName );
#endif
}/*}}}*/
/// QDir::mkpath() �̃e�X�g
void TestQDir::testmkpath()/*{{{*/
{
	// �^�C�g������e�X�g�f�[�^�̎擾
	QFETCH(QString, path);
	QFETCH(bool, bRetVal);

	// �w��̃p�X�̃t�H���_�𐶐����邽�߂ɕK�v�Ȑe�t�H���_������
	// ���ɑ��݂���ꍇ��true
	bool bResult = QDir().mkpath( path );

	QCOMPARE(bResult, bRetVal);
}/*}}}*/
/// QDir::mkpath() �̃e�X�g�f�[�^�Z�b�g
void TestQDir::testmkpath_data()/*{{{*/
{
	// �e�X�g�f�[�^�̃^�C�g���ݒ�
	QTest::addColumn<QString>("path");
	QTest::addColumn<bool>("bRetVal");
	
	// �e�X�g�Z�b�g�o�^
	QString strPath;
	// �L���ȃp�X
	strPath = QDir::currentPath();
	strPath.append("/test/testes/testdir");
	QTest::newRow("case default") << strPath << true;
	// ���ΓI�ȃp�X
	strPath = "test/testes/testdir";
	QTest::newRow("case relative dirPath") << strPath << true;
	// �����ȃp�X
	strPath = "?????????????????";
	QTest::newRow("case invalid dirPath") << strPath << false;
}/*}}}*/

// �e�X�g��
void TestQDir::testcleanabsolutefilepath()/*{{{*/
{
	// �^�C�g������e�X�g�f�[�^�̎擾
	QFETCH(QString, directory);
	QFETCH(QString, relative);
	QFETCH(QString, absolute);
	// ����]��
	QDir dir(directory);
	// ��΃p�X���ɕϊ�
	QString path = dir.absoluteFilePath( relative );
//	QCOMPARE(path, absolute); // �V�X�e���p�X(.�܂���..)���c�邽�߁A���s����P�[�X���L��
	path = QDir::cleanPath( path );
	QCOMPARE(path, absolute);

}/*}}}*/
// �f�[�^�Z�b�g��
void TestQDir::testcleanabsolutefilepath_data()/*{{{*/
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
void TestQDir::testpath()/*{{{*/
{
	// �^�C�g������e�X�g�f�[�^�̎擾
	QFETCH(QString, path);
	QFETCH(QString, dirPath);
	// ����]��
	QDir dir(path);
	path = dir.path();
	QCOMPARE(path, dirPath);

}/*}}}*/
// �f�[�^�Z�b�g��
void TestQDir::testpath_data()/*{{{*/
{
	// �e�X�g�f�[�^�̃^�C�g���ݒ�
	QTest::addColumn<QString>("path");
	QTest::addColumn<QString>("dirPath");
	
	// �e�X�g�Z�b�g�o�^
	QTest::newRow("case dir path") << "C:/Data" << "C:/Data";
	QTest::newRow("case dir path with sep") << "C:/Data/" << "C:/Data";
	//QTest::newRow("case file path") << "C:/Data/ie6.png" << "C:/Data"; //FAIL!
}/*}}}*/

#ifdef QT_DEBUG
#include <QtCore/QFile>
#include <QtCore/QTextStream>

/// [DEBUG]QStringList�̃_���v
bool TestQDir::dumpQStringList( QStringList & list, QString & fileName )/*{{{*/
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

#endif

QTEST_MAIN(TestQDir)
#include "testqdir.moc"
