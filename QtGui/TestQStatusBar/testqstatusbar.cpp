// QStatusBar�̃e�X�g
// testqstatusbar.cpp

#include <QtGui>
#include <QtTest/QtTest>

class TestQStatusBar: public QObject
{
	Q_OBJECT
private slots:
// void QStatusBar::showMessage ( const QStatusBar & message, int timeout = 0 ) [slot]
	void showMessage();
	void showMessage_data();
};

// void QStatusBar::showMessage ( const QStatusBar & message, int timeout = 0 ) [slot]
// �e�X�g��
void TestQStatusBar::showMessage()/*{{{*/
{
	// �^�C�g������e�X�g�f�[�^�̎擾
	QFETCH(QString, message);
	QFETCH(int, timeout);
	// ����]��
	QStatusBar bar;
	bar.showMessage(message, timeout);
	QCOMPARE(bar.currentMessage(), message);
}/*}}}*/
// �f�[�^�Z�b�g��
void TestQStatusBar::showMessage_data()/*{{{*/
{
	// �e�X�g�f�[�^�̃^�C�g���ݒ�
	QTest::addColumn<QString>("message");
	QTest::addColumn<int>("timeout");
	
	// �e�X�g�Z�b�g�o�^
	QTest::newRow("default timeout") << "message" << 0;
	QTest::newRow("timeout 3 secconds") << "message" << 3000;
}/*}}}*/

QTEST_MAIN(TestQStatusBar)
#include "testqstatusbar.moc"
