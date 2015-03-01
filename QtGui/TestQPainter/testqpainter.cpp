// QPainter�̃e�X�g
// testqpainter.cpp

#include <QtTest/QtTest>
#include <QPainter>



#define COLOR_WHITE	QColor(0xFF, 0xFF, 0xFF).rgb()
#define COLOR_RED	QColor(0xFF, 0x00, 0x00).rgb()
#define COLOR_GREEN	QColor(0x00, 0xFF, 0x00).rgb()
#define COLOR_BLUE	QColor(0x00, 0x00, 0xFF).rgb()

class TestQPainter: public QObject/*{{{*/
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
};/*}}}*/

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
	p.setPen( QColor( COLOR_RED ) );
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
	p.setPen( QColor( COLOR_RED ) );

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
	QPen pen( QColor( COLOR_WHITE ) );
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
	//p.setBrush( QBrush( QColor( COLOR_RED ) ) );
	QBrush brush( QColor( COLOR_RED ) );
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
	//p.fillRect(rect, QColor( COLOR_RED ));

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

	QPen * newPen = new QPen( QColor( COLOR_WHITE ) );
	newPen->setWidth(1);

	p.setPen( QColor( COLOR_RED ) );
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

	QPen rPen( QColor( COLOR_RED ) ); 
	QPen gPen( QColor( COLOR_GREEN ) ); 
	QPen bPen( QColor( COLOR_BLUE ) ); 

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

	QPen * newPen = new QPen( QColor( COLOR_WHITE ) );
	newPen->setWidth(1);

	p.setPen( QColor( COLOR_RED ) );
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
