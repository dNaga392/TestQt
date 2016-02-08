///	@file	testqpoint.cpp
///	@brief	QPointのテスト

#include <QtTest/QtTest>
#include <QtCore/QPoint>


///	QPointのテストクラス
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
	// タイトルからテストデータの取得
	QFETCH( QPoint, point );
	QFETCH( bool, result );

	QCOMPARE( point.isNull(), result );
}/*}}}*/
void TestQPoint::isNull_data()/*{{{*/
{
	// テストデータのタイトル設定
	QTest::addColumn< QPoint >( "point" );
	QTest::addColumn< bool   >( "result" );
	
	// テストセット登録
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
