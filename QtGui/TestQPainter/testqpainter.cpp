///============================================================
///	@file	testqpainter.cpp
///	@brief	QPainter�̃e�X�g
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

///	@brief	QPainter�̃e�X�g�N���X
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
	///	PolyBezier() ���e�X�g���܂��B
	void test_PolyBezier();
	///	PolyBezier() �̃e�X�g�f�[�^��ݒ肵�܂��B
	void test_PolyBezier_data();
	///	drawPixmap Test
	void QPainter_drawPixmap();
	///	drawLines Test
	void QPainter_drawLines();

private:
	QPoint	rotational_conversion( const QPoint & point, int angle );
	/// �x�W�F�Ȑ���`�悵�܂��B
	bool PolyBezier( QPainter * pPainter, const QPoint * pPoints, int count );
	/// �w�肳�ꂽ�z����̓_�����сA1 �̘A��������`�悵�܂��B
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
	int  x = rect.left() + margin.x(); // �R�s�[�撷���`�̍������ x ���W
	int  y = rect.top()  + margin.y(); // �R�s�[�撷���`�̍������ y ���W
	//int  w = rect.width();
	//int  h = rect.height();
	int  w = pix.width();  // �R�s�[�撷���`�̕�
	int  h = pix.height(); // �R�s�[�撷���`�̍���
	int sx = 0; // �R�s�[�������`�̍������ x ���W
	int sy = 0; // �R�s�[�������`�̍������ y ���W
	int sw = pix.width();   // �R�s�[�������`�̕�
	int sh = pix.height();  // �R�s�[�������`�̕�

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

	// �w�i
	painter.setBackground( QColor( RGB_WHITE ) );
	QPaintDevice * device = NULL;
	device = painter.device();
	Q_CHECK_PTR( device );
	painter.eraseRect( 0, 0, device->width(), device->height() );

	// �`�揀��
	painter.setPen( QColor( RGB_BLACK ) );
	QString text("test");
	int angle = 90; // �x
	// �`��_
	QPoint draw_point( 50, 100 );
	// �`��_�⏕���`��
	painter.save();
	painter.setPen( QColor( RGB_RED ) );
	painter.drawLine( 0, draw_point.y(), device->width(), draw_point.y() );
	painter.drawLine( draw_point.x(), 0, draw_point.x(), device->height() );
	painter.restore();
	// ���S�_
	QPoint center_point( device->width() / 2, device->height() / 2 );
	// ���S�_�⏕���`��
	painter.save();
	painter.setPen( QColor( RGB_GREEN ) );
	painter.drawLine( 0, center_point.y(), device->width(), center_point.y() );
	painter.drawLine( center_point.x(), 0, center_point.x(), device->height() );
	painter.restore();
	// ���S�e�L�X�g�`��
	painter.drawText( center_point, "center" );

	// �����̌����Ƃ͋t�ɉ�]������
	painter.save();
	painter.rotate( angle * ( -1 ) );

	// �ϊ���̕`��_���v�Z
	QPoint rotated_point( rotational_conversion( draw_point, angle ) );
	//qDebug() << "rotated_point : " << rotated_point;

	// �e�L�X�g��`��
	painter.drawText( rotated_point, text );

	// ��]���X�g�A
	painter.restore();

	pix.save( "QPainter_drawText_withRotation.bmp" );
}/*}}}*/

void	TestQPainter::QPainter_drawStaticText_withRotation()/*{{{*/
{
	QSize pix_size( 300, 200 );
	QPixmap pix( pix_size );

	QPainter painter( &pix );

	// �w�i
	painter.setBackground( QColor( RGB_WHITE ) );
	QPaintDevice * device = NULL;
	device = painter.device();
	Q_CHECK_PTR( device );
	painter.eraseRect( 0, 0, device->width(), device->height() );

	// �`�揀��
	painter.setPen( QColor( RGB_BLACK ) );
	QString text("test");
	int angle = 90; // �x
	// �`��_
	QPoint draw_point( 50, 100 );
	// �`��_�⏕���`��
	painter.save();
	painter.setPen( QColor( RGB_RED ) );
	painter.drawLine( 0, draw_point.y(), device->width(), draw_point.y() );
	painter.drawLine( draw_point.x(), 0, draw_point.x(), device->height() );
	painter.restore();
	// ���S�_
	QPoint center_point( device->width() / 2, device->height() / 2 );
	// ���S�_�⏕���`��
	painter.save();
	painter.setPen( QColor( RGB_GREEN ) );
	painter.drawLine( 0, center_point.y(), device->width(), center_point.y() );
	painter.drawLine( center_point.x(), 0, center_point.x(), device->height() );
	painter.restore();
	// ���S�e�L�X�g�`��
	painter.drawStaticText( center_point, QStaticText( "center" ) );

	// �����̌����Ƃ͋t�ɉ�]������
	painter.save();
	painter.rotate( angle * ( -1 ) );

	// �ϊ���̕`��_���v�Z
	QPoint rotated_point( rotational_conversion( draw_point, angle ) );
	//qDebug() << "rotated_point : " << rotated_point;

	// �e�L�X�g��`��
	painter.drawStaticText( rotated_point, QStaticText( text ) );

	// ��]���X�g�A
	painter.restore();

	pix.save( "QPainter_drawStaticText_withRotation.bmp" );
}/*}}}*/

// �e�X�g��
void TestQPainter::drawLine()/*{{{*/
{
	// �^�C�g������e�X�g�f�[�^�̎擾
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
	// ����]��
	//QVERIFY(testList.drawLine() == resultList);
	//QCOMPARE(rx.indexIn(str), pos);
}/*}}}*/
// �f�[�^�Z�b�g��
void TestQPainter::drawLine_data()/*{{{*/
{
	// �e�X�g�f�[�^�̃^�C�g���ݒ�
	QTest::addColumn<int>("x1");
	QTest::addColumn<int>("y1");
	QTest::addColumn<int>("x2");
	QTest::addColumn<int>("y2");
	QTest::addColumn<QString>("filename");

	// �e�X�g�Z�b�g�o�^
	QTest::newRow("case default") << 10 << 10 << 480 << 480 << QString("drawLine.bmp");
	QTest::newRow("case png") << 10 << 10 << 480 << 480 << QString("drawLine.png");
}/*}}}*/

// �e�X�g��
void TestQPainter::drawRect()/*{{{*/
{
	// �^�C�g������e�X�g�f�[�^�̎擾
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
	// ����]��
	//QVERIFY(testList.isValid() == resultList);
	//QCOMPARE(rx.indexIn(str), pos);
}/*}}}*/
// �f�[�^�Z�b�g��
void TestQPainter::drawRect_data()/*{{{*/
{
	// �e�X�g�f�[�^�̃^�C�g���ݒ�
	QTest::addColumn<int>("x1");
	QTest::addColumn<int>("y1");
	QTest::addColumn<int>("x2");
	QTest::addColumn<int>("y2");
	QTest::addColumn<QString>("filename");

	// �e�X�g�Z�b�g�o�^
	QTest::newRow("case default") << 10 << 10 << 480 << 480 << QString("drawRect.bmp");
}/*}}}*/

// �e�X�g��
void TestQPainter::drawText()/*{{{*/
{
	// �^�C�g������e�X�g�f�[�^�̎擾
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

	// ���ʂ̕ۑ�
	pix.save( filename );
	// ����]��
	//QVERIFY(testList.drawText() == resultList);
	//QCOMPARE(rx.indexIn(str), pos);
}/*}}}*/
// �f�[�^�Z�b�g��
void TestQPainter::drawText_data()/*{{{*/
{
	// �e�X�g�f�[�^�̃^�C�g���ݒ�
	QTest::addColumn<int>("pointSize");
	QTest::addColumn<QString>("family");
	QTest::addColumn<int>("x");
	QTest::addColumn<int>("y");
	QTest::addColumn<QString>("text");
	QTest::addColumn<QString>("filename");

	// �e�X�g�Z�b�g�o�^
	QTest::newRow("case default") << 18 << QString("�l�r�@�S�V�b�N") << 100 << 200 << QString("42") << QString("drawText.bmp");
	QTest::newRow("case Local") << 18 << QString("�l�r�@�S�V�b�N") << 100 << 200 << QString("�e�X�g") << QString("drawTextLocal.bmp");
}/*}}}*/

// �e�X�g��
void TestQPainter::fillRect()/*{{{*/
{
	// �^�C�g������e�X�g�f�[�^�̎擾
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
	// ����]��
	//QVERIFY(testList.isValid() == resultList);
	//QCOMPARE(rx.indexIn(str), pos);
}/*}}}*/
// �f�[�^�Z�b�g��
void TestQPainter::fillRect_data()/*{{{*/
{
	// �e�X�g�f�[�^�̃^�C�g���ݒ�
	QTest::addColumn<int>("x1");
	QTest::addColumn<int>("y1");
	QTest::addColumn<int>("x2");
	QTest::addColumn<int>("y2");
	QTest::addColumn<QString>("filename");

	// �e�X�g�Z�b�g�o�^
	QTest::newRow("case default") << 10 << 10 << 480 << 480 << QString("fillRect.bmp");
}/*}}}*/

// �e�X�g��
void TestQPainter::saveAndRestore()/*{{{*/
{
	// �^�C�g������e�X�g�f�[�^�̎擾
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
	// ����]��
	//QVERIFY(testList.isValid() == resultList);
	//QCOMPARE(rx.indexIn(str), pos);
}/*}}}*/
// �f�[�^�Z�b�g��
void TestQPainter::saveAndRestore_data()/*{{{*/
{
	// �e�X�g�f�[�^�̃^�C�g���ݒ�
	QTest::addColumn<int>("x1");
	QTest::addColumn<int>("y1");
	QTest::addColumn<int>("x2");
	QTest::addColumn<int>("y2");
	QTest::addColumn<QString>("filename");

	// �e�X�g�Z�b�g�o�^
	QTest::newRow("case default") << 10 << 10 << 480 << 480 << QString("saveAndRestore.bmp");
}/*}}}*/

// �e�X�g��
void TestQPainter::saveAndRestore2()/*{{{*/
{
	// �^�C�g������e�X�g�f�[�^�̎擾
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
	// ����]��
	//QVERIFY(testList.isValid() == resultList);
	//QCOMPARE(rx.indexIn(str), pos);
}/*}}}*/
// �f�[�^�Z�b�g��
void TestQPainter::saveAndRestore2_data()/*{{{*/
{
	// �e�X�g�f�[�^�̃^�C�g���ݒ�
	QTest::addColumn<int>("x1");
	QTest::addColumn<int>("y1");
	QTest::addColumn<int>("x2");
	QTest::addColumn<int>("y2");
	QTest::addColumn<QString>("filename");

	// �e�X�g�Z�b�g�o�^
	QTest::newRow("case default") << 10 << 10 << 480 << 480 << QString("saveAndRestore2.bmp");
}/*}}}*/

// �e�X�g��
void TestQPainter::saveAndRestoreWinStyle()/*{{{*/
{
	// �^�C�g������e�X�g�f�[�^�̎擾
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
	// ����]��
	//QVERIFY(testList.isValid() == resultList);
	//QCOMPARE(rx.indexIn(str), pos);
}/*}}}*/
// �f�[�^�Z�b�g��
void TestQPainter::saveAndRestoreWinStyle_data()/*{{{*/
{
	// �e�X�g�f�[�^�̃^�C�g���ݒ�
	QTest::addColumn<int>("x1");
	QTest::addColumn<int>("y1");
	QTest::addColumn<int>("x2");
	QTest::addColumn<int>("y2");
	QTest::addColumn<QString>("filename");

	// �e�X�g�Z�b�g�o�^
	QTest::newRow("case default") << 10 << 10 << 480 << 480 << QString("saveAndRestoreWinStyle.bmp");
}/*}}}*/

///	PolyBezier() ���e�X�g���܂��B
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

	// �`�揀��
	QSize pix_size( 100, 100 );
	QPixmap pix( pix_size );

	QPainter painter( &pix );

	// �w�i�h��Ԃ�
	painter.setBackground( QColor( RGB_WHITE ) );
	QPaintDevice * device = NULL;
	device = painter.device();
	Q_CHECK_PTR( device );
	painter.eraseRect( 0, 0, device->width(), device->height() );

	// �y���ݒ�
	painter.setPen( QColor( RGB_GREEN ) );
	// �`��
	PolyBezier( &painter, pPoints, count );

	// �㏈��
	delete [] pPoints;
	// �摜�o��
	pix.save( "test_PolyBezier.bmp" );
}/*}}}*/

///	PolyBezier() �̃e�X�g�f�[�^��ݒ肵�܂��B
void TestQPainter::test_PolyBezier_data()/*{{{*/
{
	//// �e�X�g�f�[�^�̃^�C�g���ݒ�
	//QTest::addColumn<int>("x1");
	//QTest::addColumn<int>("y1");
	//QTest::addColumn<int>("x2");
	//QTest::addColumn<int>("y2");
	//QTest::addColumn<QString>("filename");

	//// �e�X�g�Z�b�g�o�^
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

///	@brief	1�܂��͕����̃x�W�F�Ȑ���`�悵�܂��B
///	@param	pPainter : [in] Painter
///	@param	pPoints  : [in] �[�_�Ɛ���_
///	@param	count    : [in] �[�_�Ɛ���_�̍��v��
///	@return ���s����
///	@retval	true  : ����
///	@retval	false : ���s
///	@date '15.06.xx ADD Function. VC �� CDC::PolyBezier �ɑ���
bool TestQPainter::PolyBezier( QPainter * pPainter, const QPoint * pPoints, int count )/*{{{*/
{
	Q_ASSERT( pPainter != NULL );
	Q_CHECK_PTR( pPainter );
	Q_ASSERT( pPoints != NULL );
	Q_CHECK_PTR( pPoints );

	if ( count < 4 )
	{
		// �x�W�G�Ȑ��̕`��͍Œ�S�_�K�v�ł��B
		return false;
	}
	if ( ( ( count - 1 ) % 3 ) != 0 )
	{
		// ���v���͕`�悷��ׂ��Ȑ��̐��� 3 �{��� 1 �傫���l�łȂ���΂Ȃ�܂���B
		return false;
	}

	///	�`�悷�ׂ��Ȑ��̐�
	int line_count = ( ( count - 1 ) / 3 );

	// Painter �̏�Ԃ�ۑ�
	pPainter->save();
	// �A���`�G�C���A�X��ݒ�
	pPainter->setRenderHint( QPainter::Antialiasing, true );

	// �`��p�X
	QPainterPath path;
	// �n�_��ݒ�
	int startPointX = pPoints[ 0 ].x();
	int startPointY = pPoints[ 0 ].y();
	path.moveTo( startPointX, startPointY );
	for ( int i = 0; i < line_count; ++i )
	{
		// �n�_�C���f�b�N�X
		int startPointIndex = 3 * i;
		// �I�_�C���f�b�N�X���`�F�b�N
		Q_ASSERT( ( startPointIndex + 3 ) < count );

		//	���W�l�̎擾
		int         c1X = pPoints[ startPointIndex + 1 ].x();
		int         c1Y = pPoints[ startPointIndex + 1 ].y();
		int         c2X = pPoints[ startPointIndex + 2 ].x();
		int         c2Y = pPoints[ startPointIndex + 2 ].y();
		int   endPointX = pPoints[ startPointIndex + 3 ].x();
		int   endPointY = pPoints[ startPointIndex + 3 ].y();

		//	�R���x�W�G�Ȑ��̐ݒ�
		path.cubicTo( c1X, c1Y, c2X, c2Y, endPointX, endPointY );
	}

	//-------- �`�� --------
	// �x�W�G�Ȑ���`��
	pPainter->drawPath( path );

	// Painter �̏�Ԃ����X�g�A
	pPainter->restore();

	return true;
}/*}}}*/

///	@brief	�w�肳�ꂽ�z����̓_�����сA1 �̘A��������`�悵�܂��B
///	@param	pPainter : [in] Painter
///	@param	pPoints  : [in] �[�_����Ȃ�z��
///	@param	count    : [in] �z����̓_�̐�
///	@return ���s����
///	@retval	true  : ����
///	@retval	false : ���s
///	@date '15.07.xx ADD Function. VC �� CDC::Polyline �ɑ���
bool TestQPainter::Polyline( QPainter * pPainter, const QPoint * pPoints, int count )/*{{{*/
{
	Q_ASSERT( pPainter != NULL );
	Q_CHECK_PTR( pPainter );
	Q_ASSERT( pPoints != NULL );
	Q_CHECK_PTR( pPoints );

	if ( count < 2 )
	{
		// �����̕`��͍Œ�2�_�K�v�ł��B
		return false;
	}

	///	�`�悷�ׂ����̐�
	int line_count = ( count - 1 );

	// Painter �̏�Ԃ�ۑ�
	pPainter->save();
	// �A���`�G�C���A�X��ݒ�
	pPainter->setRenderHint( QPainter::Antialiasing, true );

	// �`��p�X
	QVector<QLine> lines;
	for ( int i = 0; i < line_count; ++i )
	{
		// �I�_�C���f�b�N�X���`�F�b�N
		Q_ASSERT( ( i + 1 ) < count );

		//	�����̐ݒ�
		lines << QLine( pPoints[ i ], pPoints[ i + 1 ] );
	}

	//-------- �`�� --------
	// �x�W�G�Ȑ���`��
	pPainter->drawLines( lines );

	// Painter �̏�Ԃ����X�g�A
	pPainter->restore();

	return true;
}/*}}}*/

QTEST_MAIN(TestQPainter)
#include "testqpainter.moc"

