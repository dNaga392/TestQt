///	@file	testqpoint.cpp
///	@brief	QPoint�̃e�X�g

#include <QtTest/QtTest>
#include <QtCore/QPoint>


///	QPoint�̃e�X�g�N���X
class TestQPoint/*{{{*/
	: public QObject
{
	Q_OBJECT
private slots:
	void isNull();
	void isNull_data();

};/*}}}*/

void TestQPoint::isNull()/*{{{*/
{
	// �^�C�g������e�X�g�f�[�^�̎擾
	QFETCH( QPoint, point );
	QFETCH( bool, result );

	QCOMPARE( point.isNull(), result );
}/*}}}*/
void TestQPoint::isNull_data()/*{{{*/
{
	// �e�X�g�f�[�^�̃^�C�g���ݒ�
	QTest::addColumn< QPoint >( "point" );
	QTest::addColumn< bool   >( "result" );
	
	// �e�X�g�Z�b�g�o�^
	QPoint point;
	bool result( true );
	QTest::newRow( "default" ) << point << result;
	point  = QPoint( 0, 0 );
	result = true;
	QTest::newRow( "origin" ) << point << result;
	point  = QPoint( 23, 42 );
	result = false;
	QTest::newRow( "coord" ) << point << result;
}/*}}}*/

QTEST_MAIN(TestQPoint)
#include "testqpoint.moc"
