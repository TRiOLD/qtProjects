////////////////////////////////////
//class Algorithms
//
//C++98/03, C++11 (+STL, cmath)
//
//
//byTRiOLD -l-      04.18 upd: 05.18
////////////////////////////////////
#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

////////////////////////////////////
typedef std::vector<std::string> strings;

////////////////////////////////////
class Algorithms
{
public:
    static void swapBytes( void * buf, int num_b1, int num_b2 )
    {
        char *p = (char*)buf;
        char temp = p[num_b1];
        p[num_b1] = p[num_b2];
        p[num_b2] = temp;
        buf = p;
    }

    static bool compare( double a, double b, double eps )
    {
        if( abs( a - b ) < eps )	return true;
        if( abs( a - b ) > eps )	return false;
        return false;
    }

    static bool compareSrtings( std::string &str1, std::string &str2, unsigned int length )
    {
        if( str1.length() < length || str2.length() < length )
            return false;

        for( unsigned int i = 0; i < length; i++ )
            if( str1[i] != str2[i] )
                return false;

        return true;
    }

    static unsigned int calculateWordsInSrting( std::string &str )
    {
        unsigned int res = 0;
         for( unsigned int i = 0; i < str.size(); i++ )
              if( str[i] == ' ' || str[i] == '\n' || str[i] == '\t' )
                  res++;
         int l = str.size() - 1;
         if( !(str[l] == ' ' || str[l] == '\n' || str[l] == '\t') )
             res++;

         return res;
    }

    static strings divideByWordsSrting( std::string &str, unsigned int wrdsMax )
    {
        if( !wrdsMax )
            wrdsMax = calculateWordsInSrting( str );

        strings res( wrdsMax );
        std::string word; unsigned int s = 0, w = 0, k = 0;
        for( unsigned int i = 0; i < str.size(); i++ )
            if( str[i] == ' ' || str[i] == '\n' || str[i] == '\t' )
            {
                if( w )
                {
                    word = str.substr( s, w );
                    res[k] = word;
                    k++;
                    if( k == wrdsMax )  break;
                }
                w = 0;
            }
            else
            {
                if( !w )
                    s = i;
                w++;
            }
        return res;
    }

    static double average( std::vector<float> &arr, unsigned int n )
    {
        double res = 0;
        for( unsigned int i = 0; i < n; i++ )
            res += ((double)arr[i] - res) / ((double)i + 1.0);
        return res;
    }

    static double median( std::vector<float> &arr, unsigned int n )
    {
        sort( arr.begin(), arr.begin() + n );
        double res;
        if( n % 2 )
            res = (arr[n / 2] + arr[n / 2 + 1]) / 2.0;
        else res = arr[n / 2];
        return res;
    }

    static double stdDeviation( std::vector<float> &arr, double arrMean, unsigned int n )
    {
        double res = 0;
        for( unsigned int i = 0; i < n; i++ )
            res += (pow( (double)arr[i] - arrMean, 2 )) / n;
        return sqrt( res );
    }
};

