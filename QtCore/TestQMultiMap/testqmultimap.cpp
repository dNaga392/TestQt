// QMultiMap‚ÌƒeƒXƒg
// testqmultimap.cpp

#include <QtTest/QtTest>
#include <QMultiMap>


class TestQMultiMap: public QObject
{
	Q_OBJECT
private slots:
	void count();
	void countKey();
	void countKeyValue();
};

void TestQMultiMap::count()/*{{{*/
{
	QMultiMap<int, int> map;
	map.insert(1, 1);
	map.insert(1, 2);
	map.insert(1, 1);
	map.insert(2, 2);
	map.insert(2, 2);
	int count = 5;
	// Ž®‚ð•]‰¿
	QCOMPARE(map.count(), count);
}/*}}}*/

void TestQMultiMap::countKey()/*{{{*/
{
	QMultiMap<int, int> map;
	map.insert(1, 1);
	map.insert(1, 2);
	map.insert(1, 1);
	map.insert(2, 2);
	map.insert(2, 2);
	// Ž®‚ð•]‰¿
	QCOMPARE(map.count(1), 3);
	QCOMPARE(map.count(2), 2);
}/*}}}*/

void TestQMultiMap::countKeyValue()/*{{{*/
{
	QMultiMap<int, int> map;
	map.insert(1, 1);
	map.insert(1, 2);
	map.insert(1, 1);
	map.insert(2, 2);
	map.insert(2, 2);
	// Ž®‚ð•]‰¿
	QCOMPARE(map.count(1, 1), 2);
	QCOMPARE(map.count(1, 2), 1);
	QCOMPARE(map.count(2, 2), 2);
}/*}}}*/

QTEST_MAIN(TestQMultiMap)
#include "testqmultimap.moc"
