#include "CatalogMyGC.h"

CatalogMyGC::CatalogMyGC()
{
    m_header = "Part\tN\tSizeX\tSizeY\tX\tY\tZ\tRA\tDEC\tsizeRA\tsizeDEC\n";
    m_params = 11;
}


void CatalogMyGC::addObjects( vector<PictureObject> spots, S32 numPart,
                              S32 minX, S32 maxX, S32 minY, S32 maxY,
                              D64 minA, D64 maxA, D64 minB, D64 maxB )
{
    S32 k0 = S32(m_objects.size()); S32 k = 0;
    m_objects.resize( k0 + spots.size() );
    for( S32 i = 0; i < S32(spots.size()); i++ )
    {
        spots[i].calculateMinMaxDotsParams();
        if( spots[i].maxZ > 1 )
        {
            S32 sizeX = spots[i].maxX - spots[i].minX + 1;
            S32 sizeY = spots[i].maxY - spots[i].minY + 1;
            S32 X = sizeX / 2 + spots[i].minX;
            S32 Y = sizeY / 2 + spots[i].minY;
            S32 Z = spots[i].maxZ;
            D64 Ra = X * (maxA - minA) / (maxX - minX) + minA;
            D64 Dec = Y * (maxB - minB) / (maxY - minY) + minB;
            D64 dRa = sizeX * (maxA - minA) / (maxX - minX);
            D64 dDec = sizeY * (maxB - minB) / (maxY - minY);

            m_objects[k0+k].setParam( numPart , 0 );
            m_objects[k0+k].setParam( k0+k + 1 , 1 );
            m_objects[k0+k].setParam( sizeX , 2 );
            m_objects[k0+k].setParam( sizeY , 3 );
            m_objects[k0+k].setParam( X , 4 );
            m_objects[k0+k].setParam( Y , 5 );
            m_objects[k0+k].setParam( Z , 6 );
            m_objects[k0+k].setParam( Ra , 7 );
            m_objects[k0+k].setParam( Dec , 8 );
            m_objects[k0+k].setParam( dRa , 9 );
            m_objects[k0+k].setParam( dDec , 10 );

            k++;
        }
    }

    m_objects.resize( k0 + k );
}


bool CatalogMyGC::readFile( string fileName )
{
    std::fstream file;
    file.open( fileName, std::ios_base::in );
    if( !file.is_open() )   return false;

    unsigned int rows = 0;
    std::string fileString;
    while( std::getline( file, fileString ) )
        rows++;

    file.close();   m_objects.resize( rows );
    file.open( fileName, std::ios_base::in );

    std::getline( file, fileString );
    unsigned int colms = Algorithms::calculateWordsInSrting( fileString );

    unsigned int k = 0;
    while( std::getline( file, fileString ) )
    {
        strings W = Algorithms::divideByWordsSrting( fileString, colms );
        for( int i = 0; i < m_params; i++ )
            m_objects[k].setParam( stod( W[i] ), i );
        k++;
    }

    file.close();
    return true;
}


bool CatalogMyGC::writeToFile( string fileName )
{
    if( m_objects.empty() )
        return false;

    std::fstream file;
    file.open( fileName, std::ios_base::out );
    if( !file.is_open() )   return false;

    file.write( m_header.c_str(), m_header.size() );

    unsigned int k = 0;
    while( k < m_objects.size() )
    {
        for( int i = 0; i < 7; i++ )
        {
            double value = m_objects[k].getParam( i );
            file << std::fixed << std::setprecision( 0 )
                 << value << "\t";
        }
        for( int i = 7; i < m_params; i++ )
        {
            double value = m_objects[k].getParam( i );
            file << std::fixed << std::setprecision( 10 )
                 << value << "\t";
        }
        file << endl;
        k++;
    }

    return true;
}
