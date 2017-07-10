// QtGlobal�̃e�X�g
// testqtglobal.cpp

#include <QtTest/QtTest>

class TestQtGlobal: public QObject
{
	Q_OBJECT
private slots:
// const T & qMax ( const T & value1, const T & value2 )
	void qMaxInt();
	void qMaxInt_data();
	//void test_foreach();
};

// const T & qMax ( const T & value1, const T & value2 )
// �e�X�g��
void TestQtGlobal::qMaxInt()/*{{{*/
{
	// �^�C�g������e�X�g�f�[�^�̎擾
	QFETCH(int, val1);
	QFETCH(int, val2);
	QFETCH(int, max);
	// �e�X�g
	QCOMPARE(qMax(val1, val2), max);
}/*}}}*/
// �f�[�^�Z�b�g��
void TestQtGlobal::qMaxInt_data()/*{{{*/
{
	// �e�X�g�f�[�^�̃^�C�g���ݒ�
	QTest::addColumn<int>("val1");
	QTest::addColumn<int>("val2");
	QTest::addColumn<int>("max");
	
	// �e�X�g�Z�b�g�o�^
	QTest::newRow("qMax(6,8)") << 6 << 8 << 8;
	QTest::newRow("qMax(8,6)") << 8 << 6 << 8;
	QTest::newRow("qMax(-8,6)") << -8 << 6 << 6;
	QTest::newRow("qMax(8,-6)") << 8 << -6 << 8;
	QTest::newRow("qMax(-8,-6)") << -8 << -6 << -6;
}/*}}}*/

//void TestQtGlobal::test_foreach()
//{
//	QList<QString> intList;
//	intList.append(QString("Bob"));
//	intList.append(QString("Bob2"));
//	intList.append(QString("Bob3"));
//	intList.append(QString("Bob4"));
//	int index=0;
//	foreach(QString item, intList)
//	{
//		if(index%3==0)
//		{
//			qDebug() << "Bob is" << index << "\n";
//			++index;
//			continue;
//		}
//		qDebug() << "Bob is" << item << "\n";
//			++index;
//	}
//}

QTEST_MAIN(TestQtGlobal)
#include "testqtglobal.moc"
