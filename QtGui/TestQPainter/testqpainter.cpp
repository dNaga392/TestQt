///==========================================
///	@brief	QPainter�̃e�X�g
///	@file	testqpainter.cpp
///==========================================

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

private:
	QPoint	rotational_conversion( const QPoint & point, int angle );

};/*}}}*/

QPoint	TestQPainter::rotational_conversion( const QPoint & point, int angle )/*{{{*/
{
	qDebug() << "angle =" << angle;
	angle %= 360;
	if ( angle < 0 )
	{
		angle += 360;
	}
	qDebug() << "angle =" << angle;

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
		x = (int)( (double)point.x() * cos( radian ) - (double)point.y() * sin( radian ) );
		y = (int)( (double)point.x() * sin( radian ) + (double)point.y() * cos( radian ) );
	}

	QPoint rotated( x, y );
	return rotated;
}/*}}}*/

void	TestQPainter::QPainter_drawText_withRotation()/*{{{*/
{
	QSize pix_size( 300, 200 );
	QPixmap pix( pix_size );
//	pix.fill( QColor( RGB_GREEN ) );

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
	QPoint center_point( device->width() / 2, device->height() / 2 );
	// �`��_�⏕���`��
	painter.save();
	painter.setPen( QColor( RGB_RED ) );
	painter.drawLine( 0, draw_point.y(), device->width(), draw_point.y() );
	painter.drawLine( draw_point.x(), 0, draw_point.x(), device->height() );
	painter.restore();
	// ���S�e�L�X�g�`��
	painter.drawText( center_point, "center" );
	// ���S�_�⏕���`��
	painter.save();
	painter.setPen( QColor( RGB_GREEN ) );
	painter.drawLine( 0, center_point.y(), device->width(), center_point.y() );
	painter.drawLine( center_point.x(), 0, center_point.x(), device->height() );
	painter.restore();

	painter.rotate( angle * ( -1 ) );


	// �ϊ���̕`��_���v�Z
	QPoint shift_point( draw_point.x() - center_point.x(), draw_point.y() - center_point.y() );
	QPoint rotated_shift( rotational_conversion( shift_point, angle ) );

	// ���̃f�o�C�X�T�C�Y�̂��߈Ӗ��Ȃ�
	//device = painter.device();
	//Q_CHECK_PTR( device );
	//QPoint rotated_center( device->width() / 2, device->height() / 2 );
	QPoint rotated_center(rotational_conversion( center_point, angle ) );
	QPoint rotated_point( rotated_shift.x() + rotated_center.x(), rotated_shift.y() + rotated_center.y() );

	painter.drawText( rotated_point, text );
	qDebug() << "rotated_shift : " << rotated_shift;
	qDebug() << "rotated_center : " << rotated_center;
	qDebug() << "rotated_point : " << rotated_point;

	painter.rotate( angle * ( -1 ) );

	pix.save( "QPainter_drawText_withRotation.bmp" );
}/*}}}*/

void	TestQPainter::QPainter_drawStaticText_withRotation()/*{{{*/
{
	QSize pix_size( 300, 200 );
	QPixmap pix( pix_size );
//	pix.fill( QColor( RGB_GREEN ) );

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
	QPoint center_point( device->width() / 2, device->height() / 2 );
	// �`��_�⏕���`��
	painter.save();
	painter.setPen( QColor( RGB_RED ) );
	painter.drawLine( 0, draw_point.y(), device->width(), draw_point.y() );
	painter.drawLine( draw_point.x(), 0, draw_point.x(), device->height() );
	painter.restore();
	// ���S�e�L�X�g�`��
	painter.drawText( center_point, "center" );
	// ���S�_�⏕���`��
	painter.save();
	painter.setPen( QColor( RGB_GREEN ) );
	painter.drawLine( 0, center_point.y(), device->width(), center_point.y() );
	painter.drawLine( center_point.x(), 0, center_point.x(), device->height() );
	painter.restore();

	painter.rotate( angle * ( -1 ) );


	// �ϊ���̕`��_���v�Z
	QPoint shift_point( draw_point.x() - center_point.x(), draw_point.y() - center_point.y() );
	QPoint rotated_shift( rotational_conversion( shift_point, angle ) );

	// ���̃f�o�C�X�T�C�Y�̂��߈Ӗ��Ȃ�
	//device = painter.device();
	//Q_CHECK_PTR( device );
	//QPoint rotated_center( device->width() / 2, device->height() / 2 );
	QPoint rotated_center(rotational_conversion( center_point, angle ) );
	QPoint rotated_point( rotated_shift.x() + rotated_center.x(), rotated_shift.y() + rotated_center.y() );

	painter.drawStaticText( rotated_point, QStaticText( text ) );
	qDebug() << "rotated_shift : " << rotated_shift;
	qDebug() << "rotated_center : " << rotated_center;
	qDebug() << "rotated_point : " << rotated_point;

	painter.rotate( angle * ( -1 ) );

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

QTEST_MAIN(TestQPainter)
#include "testqpainter.moc"

