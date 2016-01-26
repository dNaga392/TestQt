///	@file	testqrect.cpp
///	@brief	QRect�̃e�X�g

#include <QtTest/QtTest>
#include <QtCore/QRect>


///	QRect�̃e�X�g�N���X
class TestQRect/*{{{*/
	: public QObject
{
	Q_OBJECT
private slots:
	void testmoveTo();
	void testmoveTo_data();

};/*}}}*/

void TestQRect::testmoveTo()/*{{{*/
{
	// �^�C�g������e�X�g�f�[�^�̎擾
	QFETCH( QRect, origin_rect );
	QFETCH( int, x );
	QFETCH( int, y );
	QFETCH( QRect, moved_rect );

	origin_rect.moveTo( x, y );

	QCOMPARE( origin_rect, moved_rect );
	QCOMPARE( origin_rect.size(), moved_rect.size() );

}/*}}}*/
void TestQRect::testmoveTo_data()/*{{{*/
{
	// �e�X�g�f�[�^�̃^�C�g���ݒ�
	QTest::addColumn< QRect  >( "origin_rect" );
	QTest::addColumn< int >( "x" );
	QTest::addColumn< int >( "y" );
	QTest::addColumn< QRect  >( "moved_rect" );
	
	// �e�X�g�Z�b�g�o�^
	QString test_case( "default" );
	QRect origin_rect( 0, 0, 35, 35 );
	int x = 230;
	int y = 230;
	QRect moved_rect( 230, 230, 35, 35 );
	QTest::newRow( qPrintable( test_case ) ) << origin_rect << x << y << moved_rect;
}/*}}}*/

QTEST_MAIN(TestQRect)
#include "testqrect.moc"
