// QRegExp�̃e�X�g
// testqregexp.cpp

#include <QtTest/QtTest>
//#include <QRegExp>

class TestQRegExp
	: public QObject
{
	Q_OBJECT
private slots:

// int QRegExp::indexIn ( const QString & str, int offset = 0, CaretMode caretMode = CaretAtZero ) const

	void indexIn();
	void indexIn_data();
// bool QRegExp::isValid () const
	void isValid();
	void isValid_data();
	void exactMatch();
	void exactMatch_data();
};

void TestQRegExp::exactMatch()
{
	QFETCH( QString, pattern );
	QFETCH( QString, str );
	QFETCH( bool, result );

	QRegExp rx( pattern );
	QCOMPARE( rx.exactMatch( str ), result );
}
void TestQRegExp::exactMatch_data()/*{{{*/
{
	// �e�X�g�f�[�^�̃^�C�g���ݒ�
	QTest::addColumn< QString >("pattern");
	QTest::addColumn< QString >("str");
	QTest::addColumn< bool >("result");

	QString pattern;
	QString str;
	bool result;

	// �e�X�g�Z�b�g�o�^
	pattern = "201502E4(.+)";
	str = "201502E4-001.jpg";
	result = true;
	QTest::newRow("filename") << pattern << str << result;
	pattern = "[0123456789]*";
	str = "456168416631";
	result = true;
	QTest::newRow("numeric") << pattern << str << result;
	pattern = "[0123456789]*";
	str = "";
	result = true;
	QTest::newRow("numeric empty") << pattern << str << result;
	pattern = "[0123456789]*";
	str = "2.34E+010";
	result = false;
	QTest::newRow("numeric error") << pattern << str << result;
}/*}}}*/

// int QRegExp::indexIn ( const QString & str, int offset = 0, CaretMode caretMode = CaretAtZero ) const
// �e�X�g��
void TestQRegExp::indexIn()/*{{{*/
{
	// �^�C�g������e�X�g�f�[�^�̎擾
	QFETCH(QRegExp, rx);
	QFETCH(QString, str);
	QFETCH(int, pos);
	//qDebug() << str;
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
	//qDebug() << isValidPattern;
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
