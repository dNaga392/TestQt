///============================================================
///	@file	testqpainter.cpp
///	@brief	QPainterのテスト
///============================================================

#include <QtTest/QtTest>
#include <QtGui/QPainter>

#include <QStaticText>

#define RGB_WHITE	QColor( 0xFF, 0xFF, 0xFF ).rgb()
#define RGB_BLACK	QColor( 0x00, 0x00, 0x00 ).rgb()
#define RGB_RED		QColor( 0xFF, 0x00, 0x00 ).rgb()
#define RGB_GREEN	QColor( 0x00, 0xFF, 0x00 ).rgb()
#define RGB_BLUE	QColor( 0x00, 0x00, 0xFF ).rgb()

#ifdef M_PI
#define PI			M_PI
#else
#define PI			3.14159265358979323846
#endif // M_PI

///	@brief	QPainterのテストクラス
class TestQPainter/*{{{*/
	: public QObject
{
	Q_OBJECT

private slots:
// bool QPainter::drawLine () const
	void drawLine();
	void drawLine_data();
	void drawRect();
	void drawRect_data();
	void drawText();
	void drawText_data();
	void fillRect();
	void fillRect_data();
	void saveAndRestore();
	void saveAndRestore_data();
	void saveAndRestore2();
	void saveAndRestore2_data();
	void saveAndRestoreWinStyle();
	void saveAndRestoreWinStyle_data();
	///	Rotation Test
	void QPainter_drawText_withRotation();
	void QPainter_drawStaticText_withRotation();
	///	PolyBezier() をテストします。
	void test_PolyBezier();
	///	PolyBezier() のテストデータを設定します。
	void test_PolyBezier_data();
	///	drawPixmap Test
	void QPainter_drawPixmap();
	///	drawLines Test
	void QPainter_drawLines();

private:
	QPoint	rotational_conversion( const QPoint & point, int angle );
	/// ベジェ曲線を描画します。
	bool PolyBezier( QPainter * pPainter, const QPoint * pPoints, int count );
	/// 指定された配列内の点を結び、1 つの連続直線を描画します。
	bool Polyline( QPainter * pPainter, const QPoint * pPoints, int count );

};/*}}}*/


//////////////////////////////////////////////////////////////////////
// private slots
//////////////////////////////////////////////////////////////////////

void TestQPainter::QPainter_drawLines()/*{{{*/
{

	QPixmap save_pix( 300, 300 );
	save_pix.fill( QColor( RGB_WHITE ) );

	QPainter save_painter;
	Q_ASSERT( !save_painter.isActive() );
	save_painter.begin( &save_pix );
	Q_ASSERT( save_painter.isActive() );
	QPoint points[ 3 ];
	int pointCount = 3;
	points[ 0 ] = QPoint(   0,   0 );
	points[ 1 ] = QPoint( 100, 200 );
	points[ 2 ] = QPoint( 200, 100 );

	//int lineCount = pointCount;
	//int lineCount = pointCount - 1;

	//save_painter.drawLines( points, lineCount );
	Polyline( &save_painter, points, pointCount );

	save_painter.end();
	Q_ASSERT( !save_painter.isActive() );

	save_pix.save( "QPainter_drawLines.bmp" );
}/*}}}*/

void TestQPainter::QPainter_drawPixmap()/*{{{*/
{
	QPixmap pix( 100, 100 );
	pix.fill( QColor( RGB_RED ) );

	QPixmap save_pix( 300, 300 );
	save_pix.fill( QColor( RGB_WHITE ) );

	QPainter save_painter;
	Q_ASSERT( !save_painter.isActive() );
	save_painter.begin( &save_pix );
	Q_ASSERT( save_painter.isActive() );
	QPoint margin( 50, 50 );
	QRect rect( 50, 50, 200, 200 );

	//int sx = rect.left() + margin.x();
	//int sy = rect.top()  + margin.y();
	//int sw = rect.width();
	//int sh = rect.height();
	//int  x = 0;
	//int  y = 0;
	//int  w = pix.width();
	//int  h = pix.height();
	int  x = rect.left() + margin.x(); // コピー先長方形の左上隅の x 座標
	int  y = rect.top()  + margin.y(); // コピー先長方形の左上隅の y 座標
	//int  w = rect.width();
	//int  h = rect.height();
	int  w = pix.width();  // コピー先長方形の幅
	int  h = pix.height(); // コピー先長方形の高さ
	int sx = 0; // コピー元長方形の左上隅の x 座標
	int sy = 0; // コピー元長方形の左上隅の y 座標
	int sw = pix.width();   // コピー元長方形の幅
	int sh = pix.height();  // コピー元長方形の幅

	save_painter.drawPixmap( x, y, w, h, pix, sx, sy, sw, sh );

	save_painter.end();
	Q_ASSERT( !save_painter.isActive() );

	save_pix.save( "QPainter_drawPixmap.bmp" );
}/*}}}*/

void TestQPainter::QPainter_drawText_withRotation()/*{{{*/
{
	QSize pix_size( 300, 200 );
	QPixmap pix( pix_size );

	QPainter painter( &pix );

	// 背景
	painter.setBackground( QColor( RGB_WHITE ) );
	QPaintDevice * device = NULL;
	device = painter.device();
	Q_CHECK_PTR( device );
	painter.eraseRect( 0, 0, device->width(), device->height() );

	// 描画準備
	painter.setPen( QColor( RGB_BLACK ) );
	QString text("test");
	int angle = 90; // 度
	// 描画点
	QPoint draw_point( 50, 100 );
	// 描画点補助線描画
	painter.save();
	painter.setPen( QColor( RGB_RED ) );
	painter.drawLine( 0, draw_point.y(), device->width(), draw_point.y() );
	painter.drawLine( draw_point.x(), 0, draw_point.x(), device->height() );
	painter.restore();
	// 中心点
	QPoint center_point( device->width() / 2, device->height() / 2 );
	// 中心点補助線描画
	painter.save();
	painter.setPen( QColor( RGB_GREEN ) );
	painter.drawLine( 0, center_point.y(), device->width(), center_point.y() );
	painter.drawLine( center_point.x(), 0, center_point.x(), device->height() );
	painter.restore();
	// 中心テキスト描画
	painter.drawText( center_point, "center" );

	// 文字の向きとは逆に回転させる
	painter.save();
	painter.rotate( angle * ( -1 ) );

	// 変換先の描画点を計算
	QPoint rotated_point( rotational_conversion( draw_point, angle ) );
	//qDebug() << "rotated_point : " << rotated_point;

	// テキストを描画
	painter.drawText( rotated_point, text );

	// 回転リストア
	painter.restore();

	pix.save( "QPainter_drawText_withRotation.bmp" );
}/*}}}*/

void	TestQPainter::QPainter_drawStaticText_withRotation()/*{{{*/
{
	QSize pix_size( 300, 200 );
	QPixmap pix( pix_size );

	QPainter painter( &pix );

	// 背景
	painter.setBackground( QColor( RGB_WHITE ) );
	QPaintDevice * device = NULL;
	device = painter.device();
	Q_CHECK_PTR( device );
	painter.eraseRect( 0, 0, device->width(), device->height() );

	// 描画準備
	painter.setPen( QColor( RGB_BLACK ) );
	QString text("test");
	int angle = 90; // 度
	// 描画点
	QPoint draw_point( 50, 100 );
	// 描画点補助線描画
	painter.save();
	painter.setPen( QColor( RGB_RED ) );
	painter.drawLine( 0, draw_point.y(), device->width(), draw_point.y() );
	painter.drawLine( draw_point.x(), 0, draw_point.x(), device->height() );
	painter.restore();
	// 中心点
	QPoint center_point( device->width() / 2, device->height() / 2 );
	// 中心点補助線描画
	painter.save();
	painter.setPen( QColor( RGB_GREEN ) );
	painter.drawLine( 0, center_point.y(), device->width(), center_point.y() );
	painter.drawLine( center_point.x(), 0, center_point.x(), device->height() );
	painter.restore();
	// 中心テキスト描画
	painter.drawStaticText( center_point, QStaticText( "center" ) );

	// 文字の向きとは逆に回転させる
	painter.save();
	painter.rotate( angle * ( -1 ) );

	// 変換先の描画点を計算
	QPoint rotated_point( rotational_conversion( draw_point, angle ) );
	//qDebug() << "rotated_point : " << rotated_point;

	// テキストを描画
	painter.drawStaticText( rotated_point, QStaticText( text ) );

	// 回転リストア
	painter.restore();

	pix.save( "QPainter_drawStaticText_withRotation.bmp" );
}/*}}}*/

// テスト部
void TestQPainter::drawLine()/*{{{*/
{
	// タイトルからテストデータの取得
	QFETCH(int, x1);
	QFETCH(int, y1);
	QFETCH(int, x2);
	QFETCH(int, y2);
	QFETCH(QString, filename);

	QSize size(500, 500);//width, height
	QPixmap pix( size );
	QPainter p( &pix );
	p.setPen( QColor( RGB_RED ) );
	p.drawLine( x1, y1, x2, y2 );
	pix.save( filename );
	// 式を評価
	//QVERIFY(testList.drawLine() == resultList);
	//QCOMPARE(rx.indexIn(str), pos);
}/*}}}*/
// データセット部
void TestQPainter::drawLine_data()/*{{{*/
{
	// テストデータのタイトル設定
	QTest::addColumn<int>("x1");
	QTest::addColumn<int>("y1");
	QTest::addColumn<int>("x2");
	QTest::addColumn<int>("y2");
	QTest::addColumn<QString>("filename");

	// テストセット登録
	QTest::newRow("case default") << 10 << 10 << 480 << 480 << QString("drawLine.bmp");
	QTest::newRow("case png") << 10 << 10 << 480 << 480 << QString("drawLine.png");
}/*}}}*/

// テスト部
void TestQPainter::drawRect()/*{{{*/
{
	// タイトルからテストデータの取得
	QFETCH(int, x1);
	QFETCH(int, y1);
	QFETCH(int, x2);
	QFETCH(int, y2);
	QFETCH(QString, filename);

	QSize size(500, 500);//width, height
	QPixmap pix( size );
	QPainter p( &pix );
	p.setPen( QColor( RGB_RED ) );

	QRect rect;
	if ( x1 > x2 ) 
	{
		rect.setLeft( x2 );
		rect.setRight( x1 );
	}
	else
	{
		rect.setLeft( x1 );
		rect.setRight( x2 );
	}
	if ( y1 < y2 )
	{
		rect.setTop( y1 );
		rect.setBottom( y2 );
	}
	else
	{
		rect.setTop( y2 );
		rect.setBottom( y1 );
	}
	p.drawRect(rect);

	pix.save( filename );
	// 式を評価
	//QVERIFY(testList.isValid() == resultList);
	//QCOMPARE(rx.indexIn(str), pos);
}/*}}}*/
// データセット部
void TestQPainter::drawRect_data()/*{{{*/
{
	// テストデータのタイトル設定
	QTest::addColumn<int>("x1");
	QTest::addColumn<int>("y1");
	QTest::addColumn<int>("x2");
	QTest::addColumn<int>("y2");
	QTest::addColumn<QString>("filename");

	// テストセット登録
	QTest::newRow("case default") << 10 << 10 << 480 << 480 << QString("drawRect.bmp");
}/*}}}*/

// テスト部
void TestQPainter::drawText()/*{{{*/
{
	// タイトルからテストデータの取得
	QFETCH(int, x);
	QFETCH(int, y);
	QFETCH(QString, text);
	QFETCH(int, pointSize);
	QFETCH(QString, family);
	QFETCH(QString, filename);

	QSize size(500, 500);//width, height
	QPixmap pix( size );

	QPainter p( &pix );
	QPen pen( QColor( RGB_WHITE ) );
	QFont font( family, pointSize );
	p.setPen( pen );
	p.setFont( font );
	p.drawText( x, y, text );

	// 結果の保存
	pix.save( filename );
	// 式を評価
	//QVERIFY(testList.drawText() == resultList);
	//QCOMPARE(rx.indexIn(str), pos);
}/*}}}*/
// データセット部
void TestQPainter::drawText_data()/*{{{*/
{
	// テストデータのタイトル設定
	QTest::addColumn<int>("pointSize");
	QTest::addColumn<QString>("family");
	QTest::addColumn<int>("x");
	QTest::addColumn<int>("y");
	QTest::addColumn<QString>("text");
	QTest::addColumn<QString>("filename");

	// テストセット登録
	QTest::newRow("case default") << 18 << QString("ＭＳ　ゴシック") << 100 << 200 << QString("42") << QString("drawText.bmp");
	QTest::newRow("case Local") << 18 << QString("ＭＳ　ゴシック") << 100 << 200 << QString("テスト") << QString("drawTextLocal.bmp");
}/*}}}*/

// テスト部
void TestQPainter::fillRect()/*{{{*/
{
	// タイトルからテストデータの取得
	QFETCH(int, x1);
	QFETCH(int, y1);
	QFETCH(int, x2);
	QFETCH(int, y2);
	QFETCH(QString, filename);

	QSize size(500, 500);//width, height
	QPixmap pix( size );
	QPainter p( &pix );
	//p.setBrush( QBrush( QColor( RGB_RED ) ) );
	QBrush brush( QColor( RGB_RED ) );
	p.setBrush( brush );

	QRect rect;
	if ( x1 > x2 ) 
	{
		rect.setLeft( x2 );
		rect.setRight( x1 );
	}
	else
	{
		rect.setLeft( x1 );
		rect.setRight( x2 );
	}
	if ( y1 < y2 )
	{
		rect.setTop( y1 );
		rect.setBottom( y2 );
	}
	else
	{
		rect.setTop( y2 );
		rect.setBottom( y1 );
	}
	p.fillRect(rect, p.brush());
	//p.fillRect(rect, QColor( RGB_RED ));

	pix.save( filename );
	// 式を評価
	//QVERIFY(testList.isValid() == resultList);
	//QCOMPARE(rx.indexIn(str), pos);
}/*}}}*/
// データセット部
void TestQPainter::fillRect_data()/*{{{*/
{
	// テストデータのタイトル設定
	QTest::addColumn<int>("x1");
	QTest::addColumn<int>("y1");
	QTest::addColumn<int>("x2");
	QTest::addColumn<int>("y2");
	QTest::addColumn<QString>("filename");

	// テストセット登録
	QTest::newRow("case default") << 10 << 10 << 480 << 480 << QString("fillRect.bmp");
}/*}}}*/

// テスト部
void TestQPainter::saveAndRestore()/*{{{*/
{
	// タイトルからテストデータの取得
	QFETCH(int, x1);
	QFETCH(int, y1);
	QFETCH(int, x2);
	QFETCH(int, y2);
	QFETCH(QString, filename);

	QSize size(500, 500);//width, height
	QPixmap pix( size );
	QPainter p( &pix );

	QPen * newPen = new QPen( QColor( RGB_WHITE ) );
	newPen->setWidth(1);

	p.setPen( QColor( RGB_RED ) );
	p.drawLine( x1, y1, x2, y1 );

	p.save();
	p.setPen( *newPen );

	p.drawLine( x2, y1, x2, y2 );
	p.drawLine( x2, y2, x1, y2 );
	
	p.restore();

	p.drawLine( x1, y2, x1, y1 );

	delete newPen;

	pix.save( filename );
	// 式を評価
	//QVERIFY(testList.isValid() == resultList);
	//QCOMPARE(rx.indexIn(str), pos);
}/*}}}*/
// データセット部
void TestQPainter::saveAndRestore_data()/*{{{*/
{
	// テストデータのタイトル設定
	QTest::addColumn<int>("x1");
	QTest::addColumn<int>("y1");
	QTest::addColumn<int>("x2");
	QTest::addColumn<int>("y2");
	QTest::addColumn<QString>("filename");

	// テストセット登録
	QTest::newRow("case default") << 10 << 10 << 480 << 480 << QString("saveAndRestore.bmp");
}/*}}}*/

// テスト部
void TestQPainter::saveAndRestore2()/*{{{*/
{
	// タイトルからテストデータの取得
	QFETCH(int, x1);
	QFETCH(int, y1);
	QFETCH(int, x2);
	QFETCH(int, y2);
	QFETCH(QString, filename);

	QSize size(500, 500);//width, height
	QPixmap pix( size );
	QPainter p( &pix );

	QPen rPen( QColor( RGB_RED ) ); 
	QPen gPen( QColor( RGB_GREEN ) ); 
	QPen bPen( QColor( RGB_BLUE ) ); 

	rPen.setWidth(1);
	gPen.setWidth(1);
	bPen.setWidth(1);

	p.setPen( rPen );
	p.drawLine( x1, y1, x2, y1 );

	p.save();
	p.setPen( gPen );

	p.drawLine( x1, y1, x2, y2 );

	p.save();
	p.setPen( bPen );
	
	p.drawLine( x1, y1, x1, y2 );
	p.drawLine( x2, y1, x2, y2 );

	p.restore();

	p.drawLine( x2, y1, x1, y2 );

	p.restore();

	p.drawLine( x1, y2, x2, y2 );

	pix.save( filename );
	// 式を評価
	//QVERIFY(testList.isValid() == resultList);
	//QCOMPARE(rx.indexIn(str), pos);
}/*}}}*/
// データセット部
void TestQPainter::saveAndRestore2_data()/*{{{*/
{
	// テストデータのタイトル設定
	QTest::addColumn<int>("x1");
	QTest::addColumn<int>("y1");
	QTest::addColumn<int>("x2");
	QTest::addColumn<int>("y2");
	QTest::addColumn<QString>("filename");

	// テストセット登録
	QTest::newRow("case default") << 10 << 10 << 480 << 480 << QString("saveAndRestore2.bmp");
}/*}}}*/

// テスト部
void TestQPainter::saveAndRestoreWinStyle()/*{{{*/
{
	// タイトルからテストデータの取得
	QFETCH(int, x1);
	QFETCH(int, y1);
	QFETCH(int, x2);
	QFETCH(int, y2);
	QFETCH(QString, filename);

	QSize size(500, 500);//width, height
	QPixmap pix( size );
	QPainter p( &pix );

	QPen * newPen = new QPen( QColor( RGB_WHITE ) );
	newPen->setWidth(1);

	p.setPen( QColor( RGB_RED ) );
	p.drawLine( x1, y1, x2, y1 );

	QPen oldPen = p.pen();
	p.setPen( *newPen );

	p.drawLine( x2, y1, x2, y2 );
	p.drawLine( x2, y2, x1, y2 );
	
	p.setPen(oldPen);

	p.drawLine( x1, y2, x1, y1 );

	delete newPen;

	pix.save( filename );
	// 式を評価
	//QVERIFY(testList.isValid() == resultList);
	//QCOMPARE(rx.indexIn(str), pos);
}/*}}}*/
// データセット部
void TestQPainter::saveAndRestoreWinStyle_data()/*{{{*/
{
	// テストデータのタイトル設定
	QTest::addColumn<int>("x1");
	QTest::addColumn<int>("y1");
	QTest::addColumn<int>("x2");
	QTest::addColumn<int>("y2");
	QTest::addColumn<QString>("filename");

	// テストセット登録
	QTest::newRow("case default") << 10 << 10 << 480 << 480 << QString("saveAndRestoreWinStyle.bmp");
}/*}}}*/

///	PolyBezier() をテストします。
void TestQPainter::test_PolyBezier()/*{{{*/
{
	int count = 0;
	count = 7;
	QPoint * pPoints = new QPoint[ count ];
	pPoints[ 0 ] = QPoint(  0,  0 );
	pPoints[ 1 ] = QPoint( 99,  0 );
	pPoints[ 2 ] = QPoint( 50, 50 );
	pPoints[ 3 ] = QPoint( 99, 99 );
	pPoints[ 4 ] = QPoint(  0, 99 );
	pPoints[ 5 ] = QPoint( 50, 50 );
	pPoints[ 6 ] = QPoint(  0,  0 );

	// 描画準備
	QSize pix_size( 100, 100 );
	QPixmap pix( pix_size );

	QPainter painter( &pix );

	// 背景塗りつぶし
	painter.setBackground( QColor( RGB_WHITE ) );
	QPaintDevice * device = NULL;
	device = painter.device();
	Q_CHECK_PTR( device );
	painter.eraseRect( 0, 0, device->width(), device->height() );

	// ペン設定
	painter.setPen( QColor( RGB_GREEN ) );
	// 描画
	PolyBezier( &painter, pPoints, count );

	// 後処理
	delete [] pPoints;
	// 画像出力
	pix.save( "test_PolyBezier.bmp" );
}/*}}}*/

///	PolyBezier() のテストデータを設定します。
void TestQPainter::test_PolyBezier_data()/*{{{*/
{
	//// テストデータのタイトル設定
	//QTest::addColumn<int>("x1");
	//QTest::addColumn<int>("y1");
	//QTest::addColumn<int>("x2");
	//QTest::addColumn<int>("y2");
	//QTest::addColumn<QString>("filename");

	//// テストセット登録
	//QTest::newRow("case default") << 10 << 10 << 480 << 480 << QString("saveAndRestoreWinStyle.bmp");
}/*}}}*/

//////////////////////////////////////////////////////////////////////
// private
//////////////////////////////////////////////////////////////////////

QPoint	TestQPainter::rotational_conversion( const QPoint & point, int angle )/*{{{*/
{
	//qDebug() << "angle =" << angle;
	angle %= 360;
	if ( angle < 0 )
	{
		angle += 360;
	}
	//qDebug() << "angle =" << angle;

	int x;
	int y;
	if ( angle == 0 )
	{
		x = point.x() * ( 1 ) - point.y() * ( 0 );
		y = point.x() * ( 0 ) + point.y() * ( 1 );
	}
	else if ( angle == 90 )
	{
		x = point.x() * ( 0 ) - point.y() * ( 1 );
		y = point.x() * ( 1 ) + point.y() * ( 0 );
	}
	else if ( angle == 180 )
	{
		x = point.x() * ( -1 ) - point.y() * (  0 );
		y = point.x() * (  0 ) + point.y() * ( -1 );
	}
	else if ( angle == 270 )
	{
		x = point.x() * (  0 ) - point.y() * ( -1 );
		y = point.x() * ( -1 ) + point.y() * (  0 );
	}
	else
	{
		double radian = angle * PI / 180;
		x = (int)( point.x() * cos( radian ) - point.y() * sin( radian ) );
		y = (int)( point.x() * sin( radian ) + point.y() * cos( radian ) );
	}

	return QPoint( x, y );
}/*}}}*/

///	@brief	1つまたは複数のベジェ曲線を描画します。
///	@param	pPainter : [in] Painter
///	@param	pPoints  : [in] 端点と制御点
///	@param	count    : [in] 端点と制御点の合計数
///	@return 実行結果
///	@retval	true  : 成功
///	@retval	false : 失敗
///	@date '15.06.xx ADD Function. VC の CDC::PolyBezier に相当
bool TestQPainter::PolyBezier( QPainter * pPainter, const QPoint * pPoints, int count )/*{{{*/
{
	Q_ASSERT( pPainter != NULL );
	Q_CHECK_PTR( pPainter );
	Q_ASSERT( pPoints != NULL );
	Q_CHECK_PTR( pPoints );

	if ( count < 4 )
	{
		// ベジエ曲線の描画は最低４点必要です。
		return false;
	}
	if ( ( ( count - 1 ) % 3 ) != 0 )
	{
		// 合計数は描画するべき曲線の数の 3 倍より 1 大きい値でなければなりません。
		return false;
	}

	///	描画すべき曲線の数
	int line_count = ( ( count - 1 ) / 3 );

	// Painter の状態を保存
	pPainter->save();
	// アンチエイリアスを設定
	pPainter->setRenderHint( QPainter::Antialiasing, true );

	// 描画パス
	QPainterPath path;
	// 始点を設定
	int startPointX = pPoints[ 0 ].x();
	int startPointY = pPoints[ 0 ].y();
	path.moveTo( startPointX, startPointY );
	for ( int i = 0; i < line_count; ++i )
	{
		// 始点インデックス
		int startPointIndex = 3 * i;
		// 終点インデックスをチェック
		Q_ASSERT( ( startPointIndex + 3 ) < count );

		//	座標値の取得
		int         c1X = pPoints[ startPointIndex + 1 ].x();
		int         c1Y = pPoints[ startPointIndex + 1 ].y();
		int         c2X = pPoints[ startPointIndex + 2 ].x();
		int         c2Y = pPoints[ startPointIndex + 2 ].y();
		int   endPointX = pPoints[ startPointIndex + 3 ].x();
		int   endPointY = pPoints[ startPointIndex + 3 ].y();

		//	３次ベジエ曲線の設定
		path.cubicTo( c1X, c1Y, c2X, c2Y, endPointX, endPointY );
	}

	//-------- 描画 --------
	// ベジエ曲線を描画
	pPainter->drawPath( path );

	// Painter の状態をリストア
	pPainter->restore();

	return true;
}/*}}}*/

///	@brief	指定された配列内の点を結び、1 つの連続直線を描画します。
///	@param	pPainter : [in] Painter
///	@param	pPoints  : [in] 端点からなる配列
///	@param	count    : [in] 配列内の点の数
///	@return 実行結果
///	@retval	true  : 成功
///	@retval	false : 失敗
///	@date '15.07.xx ADD Function. VC の CDC::Polyline に相当
bool TestQPainter::Polyline( QPainter * pPainter, const QPoint * pPoints, int count )/*{{{*/
{
	Q_ASSERT( pPainter != NULL );
	Q_CHECK_PTR( pPainter );
	Q_ASSERT( pPoints != NULL );
	Q_CHECK_PTR( pPoints );

	if ( count < 2 )
	{
		// 直線の描画は最低2点必要です。
		return false;
	}

	///	描画すべき線の数
	int line_count = ( count - 1 );

	// Painter の状態を保存
	pPainter->save();
	// アンチエイリアスを設定
	pPainter->setRenderHint( QPainter::Antialiasing, true );

	// 描画パス
	QVector<QLine> lines;
	for ( int i = 0; i < line_count; ++i )
	{
		// 終点インデックスをチェック
		Q_ASSERT( ( i + 1 ) < count );

		//	線分の設定
		lines << QLine( pPoints[ i ], pPoints[ i + 1 ] );
	}

	//-------- 描画 --------
	// ベジエ曲線を描画
	pPainter->drawLines( lines );

	// Painter の状態をリストア
	pPainter->restore();

	return true;
}/*}}}*/

QTEST_MAIN(TestQPainter)
#include "testqpainter.moc"

