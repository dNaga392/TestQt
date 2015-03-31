// QRegExp�̃e�X�g
// testqregexp.cpp

#include <QtTest/QtTest>
//#include <QRegExp>

class TestQRegExp: public QObject
{
	Q_OBJECT
private slots:

// int QRegExp::indexIn ( const QString & str, int offset = 0, CaretMode caretMode = CaretAtZero ) const

	void indexIn();
	void indexIn_data();
// bool QRegExp::isValid () const
	void isValid();
	void isValid_data();
	void testexactmatch();
};

void TestQRegExp::testexactmatch()
{
	QString str;
	QString pat;

	str = "201502E4-001.jpg";
	pat = "201502E4(.+)";

	QRegExp rx(pat);

	QVERIFY( rx.exactMatch( str ) );
}

// int QRegExp::indexIn ( const QString & str, int offset = 0, CaretMode caretMode = CaretAtZero ) const
// �e�X�g��
void TestQRegExp::indexIn()/*{{{*/
{
	// �^�C�g������e�X�g�f�[�^�̎擾
	QFETCH(QRegExp, rx);
	QFETCH(QString, str);
	QFETCH(int, pos);
	qDebug() << str;
	// ����]��
	//QVERIFY(testList.isValid() == resultList);
	QCOMPARE(rx.indexIn(str), pos);
}/*}}}*/
// �f�[�^�Z�b�g��
void TestQRegExp::indexIn_data()/*{{{*/
{
	// �e�X�g�f�[�^�̃^�C�g���ݒ�
	QTest::addColumn<QRegExp>("rx");
	QTest::addColumn<QString>("str");
	QTest::addColumn<int>("pos");

	// �e�X�g�Z�b�g�o�^
	QTest::newRow("include file") << QRegExp("^#include \"(\\w+\\.(h|cpp))\"") << "#include \"application.h\"" << 0;
	QTest::newRow("include library") << QRegExp("^#include <(\\w+)>") << "#include <QApplication>" << 0;
	QTest::newRow("include parent file") << QRegExp("^#include \"((\\.+/)*\\w+\\.(h|cpp))\"") << "#include \"../mainwindow.h\"" << 0;
}/*}}}*/

// void QRegExp::isValid()
// �e�X�g��
void TestQRegExp::isValid()/*{{{*/
{
	// �^�C�g������e�X�g�f�[�^�̎擾
	QFETCH(QString, isValidPattern);
	QFETCH(bool, isValidResult);
	qDebug() << isValidPattern;
	// �e�X�g
	QRegExp rx(isValidPattern);
	// ����]��
	//QVERIFY(testList.isValid() == resultList);
	QCOMPARE(rx.isValid(), isValidResult);
}/*}}}*/
// �f�[�^�Z�b�g��
void TestQRegExp::isValid_data()/*{{{*/
{
	// �e�X�g�f�[�^�̃^�C�g���ݒ�
	QTest::addColumn<QString>("isValidPattern");
	QTest::addColumn<bool>("isValidResult");

	// �e�X�g�Z�b�g�o�^
	QTest::newRow("valid pattern") << QString("[a-z]") << true;
	QTest::newRow("invalid pattern") << QString("[a-z") << false;
}/*}}}*/

QTEST_MAIN(TestQRegExp)
#include "testqregexp.moc"
