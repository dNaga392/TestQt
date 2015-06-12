///============================================================
///	@file	testqmessagebox.cpp
///	@brief	QMessageBox�̃e�X�g
///============================================================

#include <QtTest/QtTest>
#include <QtGui/QMessageBox>

///	QMessageBox�̃e�X�g�N���X
class TestQMessageBox/*{{{*/
	: public QObject
{
	Q_OBJECT

private slots:
	///	�e�X�g�P�[�X�̏����ݒ�����܂��B
	void initTestCase();
	//	�e�X�g�P�[�X�̏I�����������܂��B
	//void cleanupTestCase();
	///	QMessageBox::setButtonText()�̃e�X�g�����܂��B
	void setButtonText();
};/*}}}*/

///	@brief	�e�X�g�P�[�X�̏����ݒ�����܂��B
void TestQMessageBox::initTestCase()/*{{{*/
{
	// ���{��Ή�
	QTextCodec::setCodecForCStrings( QTextCodec::codecForLocale() );
}/*}}}*/

///	@brief	QMessageBox::setButtonText()�̃e�X�g�����܂��B
void TestQMessageBox::setButtonText()/*{{{*/
{
	QMessageBox msgBox;

	msgBox.setWindowTitle( QString("[%1] %2").arg( "42", "hoge" ) );
	msgBox.setText( QString( "foobar" ) );
	msgBox.setStandardButtons( QMessageBox::Ok | QMessageBox::Apply | QMessageBox::Cancel );
	msgBox.setButtonText( QMessageBox::Ok , "�������[" );
	msgBox.setButtonText( QMessageBox::Cancel , "����񂹂�" );
	msgBox.setButtonText( QMessageBox::Apply , "�߂����[" );
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
