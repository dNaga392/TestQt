///============================================================
///	@file	testqlist.cpp
///	@brief	QList�̃e�X�g
///============================================================

#include <QtTest/QtTest>
#include <QtCore/QList>

typedef QList<qint32> QInt32List;

///	QList�̃e�X�g�N���X
class TestQList/*{{{*/
	: public QObject
{
	Q_OBJECT

private slots:
	///	�e�X�g�P�[�X�̏����ݒ�����܂��B
	void initTestCase();
	//	�e�X�g�P�[�X�̏I�����������܂��B
	//void cleanupTestCase();
	void test_operator_eq_eq();
//	void test_operator_eq_eq_data();

};/*}}}*/

///	@brief	�e�X�g�P�[�X�̏����ݒ�����܂��B
void TestQList::initTestCase()/*{{{*/
{
	// ���{��Ή�
	QTextCodec::setCodecForCStrings( QTextCodec::codecForLocale() );
}/*}}}*/

void TestQList::test_operator_eq_eq()/*{{{*/
{
	// �^�C�g������e�X�g�f�[�^�̎擾
//	QFETCH(QInt32List, list1);
//	QFETCH(QInt32List, list2);
//	QFETCH(bool, result);

	QInt32List list1;
	QInt32List list2;
	bool result;
	list1 << 2 << 3 << 5;
	list2 << 2 << 3 << 5;
	result = true;

	bool actual;
	actual = ( list1 == list2 );
	QCOMPARE( actual, result );

	list1.clear();
	list2.clear();
	list1 << 2 << 3 << 5;
	list2 << 3 << 5 << 2;
	result = false;
	actual = ( list1 == list2 );
	QCOMPARE( actual, result );

	qSort( list1.begin(), list1.end() );
	qSort( list2.begin(), list2.end() );
	result = true;
	actual = ( list1 == list2 );
	QCOMPARE( actual, result );

	list1.clear();
	list2.clear();
	list1 << 2 << 3 << 5;
	list2 << 3 << 3 << 4 << 5;
	result = false;
	actual = ( list1 == list2 );
	QCOMPARE( actual, result );

//	QCOMPARE( list1.size(), list2.size() ); // equal size
//	for ( int i = 0; i < list1.size(); ++i  )
//	{
//		QCOMPARE( list1[ i ], list2[ i ] ); // equal string
//	}

}/*}}}*/
//void TestQList::test_operator_eq_eq_data()/*{{{*/
//{
//	// �e�X�g�f�[�^�̃^�C�g���ݒ�
//	QTest::addColumn<QInt32List>("list1");
//	QTest::addColumn<QInt32List>("list2");
//	QTest::addColumn<bool>("result");
//	
//	QInt32List list1;
//	QInt32List list2;
//	list1 << 2 << 3 << 5;
//	list2 << 2 << 3 << 5;
//
//	QTest::newRow("case default") << list1 << list2 << true;
//
//	list1.clear();
//	list2.clear();
//	list1 << 2 << 3 << 5;
//	list2 << 3 << 5 << 2;
//
//	QTest::newRow("case dif order") << list1 << list2 << true;
//}/*}}}*/
//
QTEST_MAIN(TestQList)
#include "testqlist.moc"
