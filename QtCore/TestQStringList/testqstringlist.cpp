// QStringList�̃e�X�g
// qstringlist.cpp

#include <QtTest/QtTest>

class TestQStringList: public QObject
{
	Q_OBJECT
private slots:
	// �����m�F
	void checkOrder();
	// int QStringList::indexOf(const QString & value, int from = 0) const
	void indexOfQString();
	void indexOfQString_data();
	// QString QStringList::join ( const QString & separator ) const
	void join();
	void join_data();
	// void QStringList::sort()
	void sort();
	void sort_data();
};

// �����m�F
// QStringList �� FIFO�ł���
void TestQStringList::checkOrder()/*{{{*/
{
	// �^�C�g������e�X�g�f�[�^�̎擾
	QStringList list;
	list << "Zero!" << "One!" << "Two!";
	int i=0;
	// foreach��FIFO�ł��邱�Ƃ��m�F
	foreach(QString str, list)
	{
		if(i==0)
		{
			QCOMPARE(str, QString("Zero!"));
		}
		else if(i==1)
		{
			QCOMPARE(str, QString("One!"));
		}
		else if(i==2)
		{
			QCOMPARE(str, QString("Two!"));
		}
		++i;
	}
}/*}}}*/

// int QStringList::indexOf(const QString & value, int from = 0) const
// �e�X�g��
void TestQStringList::join()/*{{{*/
{
	// �^�C�g������e�X�g�f�[�^�̎擾
	QFETCH( QStringList, data );
	QFETCH( QString, separator );
	QFETCH( QString, result );
	// ����]��
	QCOMPARE( data.join( separator ), result );
}/*}}}*/
// �f�[�^�Z�b�g��
void TestQStringList::join_data()/*{{{*/
{
	// �e�X�g�f�[�^�̃^�C�g���ݒ�
	QTest::addColumn< QStringList >( "data" );
	QTest::addColumn< QString >( "separator" );
	QTest::addColumn< QString >( "result" );

	// �e�X�g�Z�b�g�o�^
	QStringList listData;
	QString strSeparator;
	QString strResult;

	listData << "Kaga";
	strSeparator = ";";
	strResult = "Kaga";
	QTest::newRow("IJN CV Kaga") << listData << strSeparator << strResult;

	listData.clear();
	strSeparator.clear();

	listData << "Kaga" << "Akagi" << "Hiryu" << "Soryu";
	strSeparator = ";";
	strResult = "Kaga;Akagi;Hiryu;Soryu";
	QTest::newRow("IJN Nagumo fleet") << listData << strSeparator << strResult;

	listData.clear();
	strSeparator.clear();

	listData << "Kaga" << "Akagi" << "Hiryu" << "Soryu";
	strResult = "KagaAkagiHiryuSoryu";
	QTest::newRow("IJN Nagumo fleet (nospace)") << listData << strSeparator << strResult;
}/*}}}*/

// int QStringList::indexOf(const QString & value, int from = 0) const
// �e�X�g��
void TestQStringList::indexOfQString()/*{{{*/
{
	// �^�C�g������e�X�g�f�[�^�̎擾
	QFETCH(QStringList, iOfStrData);
	QFETCH(QString, iOfStrValue);
	QFETCH(int, iOfStrResult);
	// ����]��
	QCOMPARE(iOfStrData.indexOf(iOfStrValue), iOfStrResult);
}/*}}}*/
// �f�[�^�Z�b�g��
void TestQStringList::indexOfQString_data()/*{{{*/
{
	// �e�X�g�f�[�^�̃^�C�g���ݒ�
	QTest::addColumn<QStringList>("iOfStrData");
	QTest::addColumn<QString>("iOfStrValue");
	QTest::addColumn<int>("iOfStrResult");

	// �e�X�g�Z�b�g�o�^
	QStringList testList;
	testList << "Kaga" << "Akagi" << "Hiryu" << "Soryu";
	QString val;
	val = "Hiryu";
	int result = 2;
	QTest::newRow("IJN CV") << testList << val << result;
}/*}}}*/

// void QStringList::sort()
// �e�X�g��
void TestQStringList::sort()/*{{{*/
{
	// �^�C�g������e�X�g�f�[�^�̎擾
	QFETCH(QStringList, sortData);
	QFETCH(QStringList, sortResult);
	// �\�[�g
	sortData.sort();
	// ����]��
	//QVERIFY(testList.sort() == resultList);
	QCOMPARE(sortData, sortResult);
}/*}}}*/
// �f�[�^�Z�b�g��
void TestQStringList::sort_data()/*{{{*/
{
	// �e�X�g�f�[�^�̃^�C�g���ݒ�
	QTest::addColumn<QStringList>("sortData");
	QTest::addColumn<QStringList>("sortResult");

	// �e�X�g�Z�b�g�o�^
	QStringList testList;
	testList << "2_1" << "2_2" << "1" << "3";
	QStringList resultList;
	resultList << "1" << "2_1" << "2_2" << "3";
	QTest::newRow("number list") << testList << resultList;
}/*}}}*/

QTEST_MAIN(TestQStringList)
#include "testqstringlist.moc"
