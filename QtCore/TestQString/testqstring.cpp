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
	///	QString::toUpper() �̃e�X�g
	void toUpper();
	///	QString::toUpper() �̃e�X�g�f�[�^�Z�b�g
	void toUpper_data();
	
	///	std::string ���� QString �ւ̕ϊ��e�X�g
	void fromStdString();
	///	QString ���� std::string �ւ̕ϊ��e�X�g
	void toStdString();
	void numberDouble();
	void numberDouble_data();
	/// 
	void testcommondirectorypath();
	void testcommondirectorypath_data();
};

/// ���ʂ̃t�H���_�p�X���擾����
void TestQString::testcommondirectorypath()/*{{{*/
{
	// �^�C�g������e�X�g�f�[�^�̎擾
	QFETCH(QString, path1);
	QFETCH(QString, path2);
	QFETCH(QString, common);

	QString ret = path2;
	QString result;

	while ( !path1.startsWith( ret ) )
		ret.chop(1);

	if ( ret.isEmpty() )
		result = QString();

	while ( ret.endsWith('/') )
		ret.chop(1);

	result = ret;

	// ����]��
	QCOMPARE( result, common );
}/*}}}*/
void TestQString::testcommondirectorypath_data()/*{{{*/
{
	QTest::addColumn<QString>("path1");
	QTest::addColumn<QString>("path2");
	QTest::addColumn<QString>("common");
	
	// �e�X�g�Z�b�g�o�^
	QTest::newRow("example") << "C:/Documents" << "C:/Pictures" << "C:";
	QTest::newRow("example") << "C:/Documents/Excel" << "C:/Pictures/201502" << "C:";
	QTest::newRow("example") << "C:/Pictures/iPhone" << "C:/Pictures/201502" << "C:/Pictures";
	QTest::newRow("example") << "C:/Pictures/201502" << "C:/Pictures/201502" << "C:/Pictures/201502";
}/*}}}*/
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

// �e�X�g��
void TestQString::numberDouble()/*{{{*/
{
	// �^�C�g������e�X�g�f�[�^�̎擾
	QFETCH(double, n);
	QFETCH(char, format);
	QFETCH(int, precision);
	QFETCH(QString, num);

	QString actual = QString::number( n, format, precision );
	QCOMPARE( actual, num );
}/*}}}*/
// �f�[�^�Z�b�g��
void TestQString::numberDouble_data()/*{{{*/
{
	// �e�X�g�f�[�^�̃^�C�g���ݒ�
	QTest::addColumn<double>("n");
	QTest::addColumn<char>("format");
	QTest::addColumn<int>("precision");
	QTest::addColumn<QString>("num");
	
	// �e�X�g�Z�b�g�o�^
	QTest::newRow("case 3") << 3.14159265 << 'f' << 3 << "3.142"; // �l�̌ܓ������
	QTest::newRow("case 4") << 3.14159265 << 'f' << 4 << "3.1416";
	QTest::newRow("case 5") << 3.14159265 << 'f' << 5 << "3.14159";
	QTest::newRow("case 6") << 3.14159265 << 'f' << 6 << "3.141593";
}/*}}}*/

QTEST_MAIN(TestQString)
#include "testqstring.moc"
