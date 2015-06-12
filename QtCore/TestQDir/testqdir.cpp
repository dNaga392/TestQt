///============================================================
///	@file	testqdir.cpp
///	@brief	QDirのテスト
///============================================================

#include <QtTest/QtTest>
#include <QtCore/QDir>

#include <QtCore/QStringList>

///	QDirのテストクラス
class TestQDir/*{{{*/
	: public QObject
{
	Q_OBJECT

private slots:
	///	テストケースの初期設定をします。
	void initTestCase();
	void testmkpath();
	void testmkpath_data();
	void testcleanabsolutefilepath();
	void testcleanabsolutefilepath_data();
	void testpath();
	void testpath_data();
	void alldirstopdown();
	///	トップダウンで、フォルダパス一覧を取得
	void alldirstopdownwithcurrent();
#ifdef QT_DEBUG
	/// [DEBUG]QStringListのダンプ
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

///	@brief	テストケースの初期設定をします。
void TestQMessageBox::initTestCase()/*{{{*/
{
	// 日本語対応
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
/// QDir::mkpath() のテスト
void TestQDir::testmkpath()/*{{{*/
{
	// タイトルからテストデータの取得
	QFETCH(QString, path);
	QFETCH(bool, bRetVal);

	// 指定のパスのフォルダを生成するために必要な親フォルダも生成
	// 既に存在する場合もtrue
	bool bResult = QDir().mkpath( path );

	QCOMPARE(bResult, bRetVal);
}/*}}}*/
/// QDir::mkpath() のテストデータセット
void TestQDir::testmkpath_data()/*{{{*/
{
	// テストデータのタイトル設定
	QTest::addColumn<QString>("path");
	QTest::addColumn<bool>("bRetVal");
	
	// テストセット登録
	QString strPath;
	// 有効なパス
	strPath = QDir::currentPath();
	strPath.append("/test/testes/testdir");
	QTest::newRow("case default") << strPath << true;
	// 相対的なパス
	strPath = "test/testes/testdir";
	QTest::newRow("case relative dirPath") << strPath << true;
	// 無効なパス
	strPath = "?????????????????";
	QTest::newRow("case invalid dirPath") << strPath << false;
}/*}}}*/

// テスト部
void TestQDir::testcleanabsolutefilepath()/*{{{*/
{
	// タイトルからテストデータの取得
	QFETCH(QString, directory);
	QFETCH(QString, relative);
	QFETCH(QString, absolute);
	// 式を評価
	QDir dir(directory);
	// 絶対パス情報に変換
	QString path = dir.absoluteFilePath( relative );
//	QCOMPARE(path, absolute); // システムパス(.または..)が残るため、失敗するケースが有る
	path = QDir::cleanPath( path );
	QCOMPARE(path, absolute);

}/*}}}*/
// データセット部
void TestQDir::testcleanabsolutefilepath_data()/*{{{*/
{
	// テストデータのタイトル設定
	QTest::addColumn<QString>("directory");
	QTest::addColumn<QString>("relative");
	QTest::addColumn<QString>("absolute");
	
	// テストセット登録
	QTest::newRow("current Path") << "C:/Data" << "ie6.png" << "C:/Data/ie6.png";
	QTest::newRow("current sysPath") << "C:/Data" << "./ie6.png" << "C:/Data/ie6.png";
	QTest::newRow("twice current sysPath") << "C:/Data" << "././ie6.png" << "C:/Data/ie6.png";
	QTest::newRow("parent sysPath") << "C:/Qt" << "../Data/ie6.png" << "C:/Data/ie6.png";
	QTest::newRow("twice parent sysPath") << "C:/Qt/bin" << "../../Data/ie6.png" << "C:/Data/ie6.png";
	QTest::newRow("twice parent sysPath") << "C:/Qt/bin4" << "../../Data/ie6.png" << "C:/Data/ie6.png";
}/*}}}*/

// テスト部
void TestQDir::testpath()/*{{{*/
{
	// タイトルからテストデータの取得
	QFETCH(QString, path);
	QFETCH(QString, dirPath);
	// 式を評価
	QDir dir(path);
	path = dir.path();
	QCOMPARE(path, dirPath);

}/*}}}*/
// データセット部
void TestQDir::testpath_data()/*{{{*/
{
	// テストデータのタイトル設定
	QTest::addColumn<QString>("path");
	QTest::addColumn<QString>("dirPath");
	
	// テストセット登録
	QTest::newRow("case dir path") << "C:/Data" << "C:/Data";
	QTest::newRow("case dir path with sep") << "C:/Data/" << "C:/Data";
	//QTest::newRow("case file path") << "C:/Data/ie6.png" << "C:/Data"; //FAIL!
}/*}}}*/

#ifdef QT_DEBUG
#include <QtCore/QFile>
#include <QtCore/QTextStream>

/// [DEBUG]QStringListのダンプ
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
