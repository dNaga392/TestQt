///	@file	testqmultimap.cpp
///	@brief	QMultiMap‚ÌƒeƒXƒg

#include <QtCore/QMultiMap>
#include <QtTest/QtTest>


class TestQMultiMap/*{{{*/
	: public QObject
{
	Q_OBJECT

private Q_SLOTS:
	void count();
	void countKey();
	void countKeyValue();
	void insert();
};/*}}}*/


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

void TestQMultiMap::insert()/*{{{*/
{
	QMultiMap< int, QString > map;
	QList< QString > list;
	int key = 1;
	QString value;
	value = ("One!");
	map.insert( key, value );
	list.prepend( value );
	value = ("Two!");
	map.insert( key, value );
	list.prepend( value );
	// Ž®‚ð•]‰¿
	QCOMPARE( map.values( key ), list );
}/*}}}*/

QTEST_MAIN( TestQMultiMap )
#include "testqmultimap.moc"
