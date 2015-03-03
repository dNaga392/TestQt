// QString�̃e�X�g
// testqstring.cpp

#include <string>

#include <QtTest/QtTest>

class TestQString: public QObject
{
	Q_OBJECT
private slots:
// bool QString::contains ( const QString & str, Qt::CaseSensitivity cs = Qt::CaseSensitive ) const
	void containsQString();
	void containsQString_data();
//// bool QString::contains ( const QRegExp & rx ) const
//	void containsConstQRegExp();
//	void containsConstQRegExp_data();
// bool QString::contains ( QRegExp & rx ) const
	void containsQRegExp();
	void containsQRegExp_data();
// QString QString::toUpper() const
	void toUpper();
	void toUpper_data();
	
	void fromStdString();
	void toStdString();
};

/// QString from std::string
void TestQString::fromStdString()/*{{{*/
{
	std::string str;
	QString qstr;
	
	str = "hoge";
	qstr = QString::fromStdString(str);
	
	QString expected("hoge");

	// ����]��
	QCOMPARE( qstr, expected );
	QCOMPARE( qstr, expected );
}/*}}}*/
/// QString to std::string
void TestQString::toStdString()/*{{{*/
{
	std::string str;
	QString qstr;
	
	qstr = "hoge";
	str = qstr.toLocal8Bit().constData();
	
	std::string expected("hoge");

	QVERIFY( str == expected );
	QVERIFY( str == expected );

	std::string wrong("hoge!");
	QVERIFY( str != wrong );
}/*}}}*/

// bool QString::contains ( const QString & str, Qt::CaseSensitivity cs = Qt::CaseSensitive ) const
// �e�X�g��
void TestQString::containsQString()/*{{{*/
{
	// �^�C�g������e�X�g�f�[�^�̎擾
	QFETCH(QString, string);
	QFETCH(QString, str);
	QFETCH(int, cs);
	QFETCH(bool, result);
	// ����]��
	QCOMPARE((bool)string.contains(str, static_cast<Qt::CaseSensitivity>(cs)), result);
}/*}}}*/
// �f�[�^�Z�b�g��
void TestQString::containsQString_data()/*{{{*/
{
	// �e�X�g�f�[�^�̃^�C�g���ݒ�
	QTest::addColumn<QString>("string");
	QTest::addColumn<QString>("str");
	//QTest::addColumn<Qt::CaseSensitivity>("cs");
	QTest::addColumn<int>("cs");
	QTest::addColumn<bool>("result");
	
	// �e�X�g�Z�b�g�o�^
	//QTest::newRow("example") << "Peter Pan" << "peter" << Qt::CaseInsensitive << true;
	QTest::newRow("example") << "Peter Pan" << "peter" << (int)Qt::CaseInsensitive << true;
}/*}}}*/

//// bool QString::contains ( const QRegExp & rx ) const
//// �e�X�g��
//void TestQString::containsConstQRegExp()/*{{{*/
//{
//}/*}}}*/
//// �f�[�^�Z�b�g��
//void TestQString::containsConstQRegExp_data()/*{{{*/
//{
//}/*}}}*/

// bool QString::contains ( QRegExp & rx ) const
// �e�X�g��
void TestQString::containsQRegExp()/*{{{*/
{
	// �^�C�g������e�X�g�f�[�^�̎擾
	QFETCH(QString, string);
	QFETCH(QRegExp, rx);
	QFETCH(bool, result);
	// ����]��
	QCOMPARE((bool)string.contains(rx), result);
}/*}}}*/
// �f�[�^�Z�b�g��
void TestQString::containsQRegExp_data()/*{{{*/
{
	// �e�X�g�f�[�^�̃^�C�g���ݒ�
	QTest::addColumn<QString>("string");
	QTest::addColumn<QRegExp>("rx");
	QTest::addColumn<bool>("result");
	
	// �e�X�g�Z�b�g�o�^
	QTest::newRow("example") << "Peter Pan" << QRegExp(".+") << true;
	QTest::newRow("example1") << "2012/06/30 13:45:30" << QRegExp("..../../.. ..:..:..") << true;
	QTest::newRow("example2") << "2012/06/30 13:45:30" << QRegExp("..:..:..") << true;
	QTest::newRow("example3") << "2012/06/30 13:45:30" << QRegExp("www") << false;
}/*}}}*/

// void QString::toUpper()
// �e�X�g��
void TestQString::toUpper()/*{{{*/
{
	// �^�C�g������e�X�g�f�[�^�̎擾
	QFETCH(QString, string);
	QFETCH(QString, result);
	// ����]��
	if(string!=result)
	{
		// toUpper()�Ō��̕�����͕ω����Ȃ�
		QVERIFY(string != string.toUpper());
		QVERIFY(string.toUpper() != string);
		//string.toUpper();
		//QVERIFY(string.toUpper() == string); // FAIL!
		//QVERIFY(string == string.toUpper()); // FAIL!
	}
	QCOMPARE(string.toUpper(), result);
}/*}}}*/
// �f�[�^�Z�b�g��
void TestQString::toUpper_data()/*{{{*/
{
	// �e�X�g�f�[�^�̃^�C�g���ݒ�
	QTest::addColumn<QString>("string");
	QTest::addColumn<QString>("result");
	
	// �e�X�g�Z�b�g�o�^
	QTest::newRow("all lower") << "hello" << "HELLO";
	QTest::newRow("mixed")     << "Hello" << "HELLO";
	QTest::newRow("all upper") << "HELLO" << "HELLO";
}/*}}}*/

QTEST_MAIN(TestQString)
#include "testqstring.moc"
