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
	void setButtonText_YesNo();
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

void TestQMessageBox::setButtonText_YesNo()/*{{{*/
{
	QMessageBox msgBox;

	msgBox.setWindowTitle( QString("[%1] %2").arg( "42", "hoge" ) );
	//msgBox.setText( QString( "���̉��Z�ɂ͖c��Ȏ��Ԃ������邱�Ƃ��\�z����Ă��܂��B\n���s���܂����H" ) );
	msgBox.setText( QString( "�f�[�^�^��ύX����ƁA���̃f�[�^�ɑ΂�����͎w��͉�������܂��B\n���s���܂����H" ) );
	msgBox.setStandardButtons( QMessageBox::Ok | QMessageBox::Cancel );
	msgBox.setButtonText( QMessageBox::Ok , "���s" );
	msgBox.setButtonText( QMessageBox::Cancel , "�L�����Z��" );
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
