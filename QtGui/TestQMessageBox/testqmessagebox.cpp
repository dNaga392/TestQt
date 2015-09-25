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
	void setButtonText_YesNo();
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

void TestQMessageBox::setButtonText_YesNo()/*{{{*/
{
	QMessageBox msgBox;

	msgBox.setWindowTitle( QString("[%1] %2").arg( "42", "hoge" ) );
	//msgBox.setText( QString( "この演算には膨大な時間がかかることが予想されています。\n続行しますか？" ) );
	msgBox.setText( QString( "データ型を変更すると、このデータに対する入力指定は解除されます。\n続行しますか？" ) );
	msgBox.setStandardButtons( QMessageBox::Ok | QMessageBox::Cancel );
	msgBox.setButtonText( QMessageBox::Ok , "続行" );
	msgBox.setButtonText( QMessageBox::Cancel , "キャンセル" );
	int ret = msgBox.exec();
	if ( ret == QMessageBox::Cancel )
	{
		qDebug("%s, %d: No", __FILE__, __LINE__);
	}
	else if ( ret == QMessageBox::Ok )
	{
		qDebug("%s, %d: Ok", __FILE__, __LINE__);
	}
}/*}}}*/

QTEST_MAIN(TestQMessageBox)
#include "testqmessagebox.moc"
