///===================================================================
///	@file	testqtalgorithms.cpp
///	@brief	QtAlgorithmsのテスト
///	@date	2015/09/19 作成
///===================================================================

#include <QtTest/QtTest>

/*! ******************************************************************
	@brief	QtAlgorithmsのテストクラス
******************************************************************* */
class TestQtAlgorithms/*{{{*/
	: public QObject
{
	Q_OBJECT

private slots:
	void qSortLessThan();
	void qSortLessThan_data();
};/*}}}*/


/*! ******************************************************************
	@brief	文字の大小を無視した自然順ソートLessThan
	@retval	true  : s1 <  s2
	@retval	false : s1 >= s2
	@note	http://www.qtcentre.org/archive/index.php/t-21411.html
******************************************************************* */
bool naturalOrderLessThan( const QString & s1, const QString & s2 )/*{{{*/
{
//	qDebug() << qPrintable( QString( "%1, %2: %3" ).arg( __FILE__ ).arg( __LINE__ ).arg( Q_FUNC_INFO ) );
	// ignore common prefix..
	int i = 0;
	while ( ( i < s1.length() ) && ( i < s2.length() ) && ( s1.at(i).toLower() == s2.at(i).toLower() ) )
	{
		++i;
	}
	++i;
	// something left to compare?
	if ( ( i < s1.length() ) && ( i < s2.length() ) )
	{
		// get number prefix from position i - doesnt matter from which string
		int k = i-1;
		//If not number return native comparator
		if ( !s1.at( k ).isNumber() || !s2.at( k ).isNumber() )
		{
			//Two next lines
			//E.g. 1_... < 12_...
			if ( s1.at( k ).isNumber() )
			{
				return false;
			}
			if ( s2.at( k ).isNumber() )
			{
				return true;
			}
			//return QString::compare(s1, s2, Qt::CaseSensitive) < 0;
			return QString::compare( s1, s2, Qt::CaseInsensitive ) < 0;
		}
		QString n = "";
		k--;
		while ( ( k >= 0 ) && ( s1.at( k ).isNumber() ) )
		{
			n = s1.at( k ) + n;
			--k;
		}
		// get relevant/signficant number string for s1
		k = i - 1;
		QString n1 = "";
		while ( ( k < s1.length() ) && ( s1.at( k ).isNumber() ) )
		{
			n1 += s1.at( k );
			++k;
		}
		
		// get relevant/signficant number string for s2
		//Decrease by
		k = i - 1;
		QString n2 = "";
		while ( ( k < s2.length() ) && ( s2.at( k ).isNumber() ) )
		{
			n2 += s2.at( k );
			++k;
		}
		
		// got two numbers to compare?
		if ( !n1.isEmpty() && !n2.isEmpty() )
		{
			if ( ( n + n1 ).toInt() == ( n + n2 ).toInt() )
			{
				// in case to compare "1" and "01"
				// sort order "01", "1"
				return ( n + n1 ) < ( n + n2 );
			}
			return ( n + n1 ).toInt() < ( n + n2 ).toInt();
		}
		else
		{
			// not a number has to win over a number.. number could have ended earlier... same prefix..
			if ( !n1.isEmpty() )
			{
				return false;
			}
			if ( !n2.isEmpty() )
			{
				return true;
			}
			return s1.at( i ) < s2.at( i );
		}
	}
	else
	{
		// shortest string wins
		return s1.length() < s2.length();
	}
}/*}}}*/

/*! ******************************************************************
	@brief	大文字小文字無視ソートLessThan
	@retval	true  : s1 <  s2
	@retval	false : s1 >= s2
******************************************************************* */
bool caseInsensitiveLessThan(const QString &s1, const QString &s2)
{
	return s1.toLower() < s2.toLower();
}

// テスト部
void TestQtAlgorithms::qSortLessThan()/*{{{*/
{
	// タイトルからテストデータの取得
//	// テスト
//	QStringList list;
//	list << "AlPha" << "beTA" << "gamma" << "DELTA";
//	qSort( list.begin(), list.end(), caseInsensitiveLessThan );
	// テスト
	QStringList list;
	list << "z11.dat" << "z2.dat" << "z1..dat" << "Z1.dat";
	list << "z1_01.dat" << "z1_2.dat" << "z01..dat" << "Z12.dat";
	qSort( list.begin(), list.end(), naturalOrderLessThan );
	qDebug() << list;
}/*}}}*/
// データセット部
void TestQtAlgorithms::qSortLessThan_data()/*{{{*/
{
	// テストデータのタイトル設定
	
	// テストセット登録
}/*}}}*/

QTEST_MAIN(TestQtAlgorithms)
#include "testqtalgorithms.moc"

