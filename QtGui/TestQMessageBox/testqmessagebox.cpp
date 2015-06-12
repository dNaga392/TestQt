///============================================================
///	@file	testqmessagebox.cpp
///	@brief	QMessageBoxのテスト
///============================================================

#include <QtTest/QtTest>
#include <QtGui/QMessageBox>

///	QMessageBoxのテストクラス
class TestQMessageBox/*{{{*/
	: public QObject
{
	Q_OBJECT

private slots:
	///	テストケースの初期設定をします。
	void initTestCase();
	//	テストケースの終了処理をします。
	//void cleanupTestCase();
	///	QMessageBox::setButtonText()のテストをします。
	void setButtonText();
};/*}}}*/

///	@brief	テストケースの初期設定をします。
void TestQMessageBox::initTestCase()/*{{{*/
{
	// 日本語対応
	QTextCodec::setCodecForCStrings( QTextCodec::codecForLocale() );
}/*}}}*/

///	@brief	QMessageBox::setButtonText()のテストをします。
void TestQMessageBox::setButtonText()/*{{{*/
{
	QMessageBox msgBox;

	msgBox.setWindowTitle( QString("[%1] %2").arg( "42", "hoge" ) );
	msgBox.setText( QString( "foobar" ) );
	msgBox.setStandardButtons( QMessageBox::Ok | QMessageBox::Apply | QMessageBox::Cancel );
	msgBox.setButtonText( QMessageBox::Ok , "おっけー" );
	msgBox.setButtonText( QMessageBox::Cancel , "きゃんせる" );
	msgBox.setButtonText( QMessageBox::Apply , "めいおー" );
	int ret = msgBox.exec();
	if ( ret == QMessageBox::Cancel )
	{
		qDebug("%s, %d: No", __FILE__, __LINE__);
	}
	else if ( ret == QMessageBox::Ok )
	{
		qDebug("%s, %d: Ok", __FILE__, __LINE__);
	}
	else
	{
		qDebug("%s, %d: App", __FILE__, __LINE__);
	}
}/*}}}*/

QTEST_MAIN(TestQMessageBox)
#include "testqmessagebox.moc"
