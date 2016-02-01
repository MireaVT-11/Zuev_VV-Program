#ifndef LAGRANGEPOLYNOMIAL_H
#define LAGRANGEPOLYNOMIAL_H

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

template< typename T >
class LagrangePolynomial
{
public:
	//LagrangePolynomial() = default;
	LagrangePolynomial( std::size_t numPoints );

	T operator()( T x );

	void compute();
	LagrangePolynomial &addPoint( T x, T y );

private:
	struct Point
	{
		T x;
		T y;
	};
	std::vector< Point > points;
};

template< typename T >
LagrangePolynomial< T >::LagrangePolynomial( std::size_t numPoints )
{
	points.reserve( numPoints );
}

template< typename T >
T LagrangePolynomial< T >::operator()( T x )
{
	T result = T();
	T prod;
	for( std::size_t k = 0; k < points.size(); ++k )
	{
		prod = T( 1 );
		for( std::size_t i = 0; i < k; ++i )
			prod *= x-points[ i ].x;
		for( std::size_t i = k+1; i < points.size(); ++i )
			prod *= x-points[ i ].x;
		result += points[ k ].y*prod;
	}
	return result;
}

template< typename T >
void LagrangePolynomial< T >::compute()
{
	T prod;
	for( std::size_t k = 0; k < points.size(); ++k )
	{
		prod = T( 1 );
		for( std::size_t i = 0; i < k; ++i )
			prod *= points[ k ].x-points[ i ].x;
		for( std::size_t i = k+1; i < points.size(); ++i )
			prod *= points[ k ].x-points[ i ].x;
		points[ k ].y /= prod;
	}
}

template< typename T >
LagrangePolynomial< T > &LagrangePolynomial< T >::addPoint( T x, T y )
{
	Point p = { x, y };
	points.push_back( p );
	return *this;
}

template< typename T, std::size_t POWER >
class PartialLagrangePolynomial;

template< typename T >
class PartialLagrangePolynomial< T, 2u >
{
public:
	//LagrangePolynomial() = default;
	PartialLagrangePolynomial( std::size_t numPoints );

	T operator()( T x );

	void compute();
	PartialLagrangePolynomial &addPoint( T x, T y );

private:
	struct Point {
		T x; T y;
		bool operator<( const Point &p ) {
			return x < p.x;
		}
	};
	std::vector< Point > points;
	std::vector< LagrangePolynomial< T > > lps;
};

template< typename T >
PartialLagrangePolynomial< T, 2u >::PartialLagrangePolynomial( std::size_t numPoints )
{
	points.reserve( numPoints );
	lps.reserve( numPoints-1 );
}

template< typename T >
T PartialLagrangePolynomial< T, 2u >::operator()( T x )
{
	for( std::size_t i = 1; i < points.size()-1; ++i )
		if( x < points[ i ].x ) return lps[ i-1 ]( x );
	return lps.back()( x );
}

template< typename T >
void PartialLagrangePolynomial< T, 2u >::compute()
{
	if( points.size() < 3 ) throw( "There is too few points" );
	std::sort( points.begin(), points.end() );
	lps.resize( points.size()-2, T() );
	for( std::size_t k = 0; k < points.size()-2; ++k )
	{
		for( std::size_t i = k; i < k+3; ++i )
			lps[ k ].addPoint( points[ i ].x, points[ i ].y );
		lps[ k ].compute();
	}
	//lps[ points.size()-2 ] = lps[ points.size()-3 ];
}

template< typename T >
PartialLagrangePolynomial< T, 2u > &PartialLagrangePolynomial< T, 2u >::addPoint( T x, T y )
{
	Point p = { x, y };
	points.push_back( p );
	return *this;
}

template< typename T >
class PartialLagrangePolynomial< T, 3u >
{
public:
	//LagrangePolynomial() = default;
	PartialLagrangePolynomial( std::size_t numPoints );

	T operator()( T x );

	void compute();
	PartialLagrangePolynomial &addPoint( T x, T y );

private:
	struct Point {
		T x; T y;
		bool operator<( const Point &p ) const {
			return x < p.x;
		}
	};
	std::vector< Point > points;
	std::vector< LagrangePolynomial< T > > lps;
};

template< typename T >
PartialLagrangePolynomial< T, 3u >::PartialLagrangePolynomial( std::size_t numPoints )
{
	points.reserve( numPoints );
	lps.reserve( numPoints-1 );
}

template< typename T >
T PartialLagrangePolynomial< T, 3u >::operator()( T x )
{
	for( std::size_t i = 2; i < points.size()-1; ++i )
		if( x < points[ i ].x ) return lps[ i-2 ]( x );
	return lps.back()( x );
}

template< typename T >
void PartialLagrangePolynomial< T, 3u >::compute()
{
	if( points.size() < 4 ) throw( "There is too few points" );
	std::sort( points.begin(), points.end() );
	lps.resize( points.size()-3, T() );
	for( std::size_t k = 1; k < points.size()-2; ++k )
	{
		for( std::size_t i = k-1; i < k+3; ++i )
			lps[ k-1 ].addPoint( points[ i ].x, points[ i ].y );
		lps[ k-1 ].compute();
	}
	//lps[ 0 ] = lps[ 1 ];
	//lps[ points.size()-2 ] = lps[ points.size()-3 ];
}

template< typename T >
PartialLagrangePolynomial< T, 3u > &PartialLagrangePolynomial< T, 3u >::addPoint( T x, T y )
{
	Point p = { x, y };
	points.push_back( p );
	return *this;
}

//--------------------------------------------------------------------------------------------------
// Метод прогонки
template< typename T1, typename T2, typename T3, typename T4 >
void tridiagonalMatrixAlgorithm( T1 &aIn, T2 &bIn, T3 &cIn, T4 &fIn_xOut, std::size_t N )
{
	using namespace std;
	cIn[ 0 ] = -cIn[ 0 ]/bIn[ 0 ];
	aIn[ 0 ] = fIn_xOut[ 0 ]/bIn[ 0 ];
	for( size_t i = 1; i < N-1; ++i )
	{
		cIn[ i ] = -cIn[ i ]/(aIn[ i ]*cIn[ i-1 ]+bIn[ i ]);
		aIn[ i ] = (fIn_xOut[ i ]-aIn[ i ]*aIn[ i-1 ])/(aIn[ i ]*cIn[ i-1 ]+bIn[ i ]);
	}
	fIn_xOut[ N-1 ] = (fIn_xOut[ N-1 ]-aIn[ N-1 ]*aIn[ N-2 ])/(aIn[ N-1 ]*cIn[ N-2 ]+bIn[ N-1 ]);
	for( size_t i = N-2; i != static_cast< size_t >( -1 ); --i )
		fIn_xOut[ i ] = cIn[ i ]*fIn_xOut[ i+1 ]+aIn[ i ];
}

template< typename T1, typename T2, typename T3, typename T4, std::size_t N1, std::size_t N2,
	std::size_t N3, std::size_t N4 >
inline
void tridiagonalMatrixAlgorithm( T1 (&aIn)[ N1 ], T2 (&bIn)[ N2 ], T3 (&cIn)[ N3 ],
	T4 (&fIn_xOut)[ N4 ] )
{
	tridiagonalMatrixAlgorithm( aIn, bIn, cIn, fIn_xOut, N4 );
}

//--------------------------------------------------------------------------------------------------
// Схема (метод) Горнера
template< typename T>
class HornerScheme
{
public:
	HornerScheme();

	template< typename C >
	HornerScheme& setCoeffs( C &coeffs );

	T operator()( T x );

private:
	std::vector< T > coeffs;
};

template< typename T >
inline
HornerScheme< T >::HornerScheme( )
{
}

template< typename T >
inline
T HornerScheme< T >::operator()( T x )
{
	T result( coeffs.back() );
	for( std::size_t i = coeffs.size()-2; i != -1u; --i )
		result = coeffs[ i ]+x*result;
	return result;
}

template< typename T >
template< typename C >
inline
HornerScheme< T > &HornerScheme< T >::setCoeffs( C &coeffs )
{
	HornerScheme::coeffs.assign( coeffs.begin(), coeffs.end() );
	return *this;
}

//--------------------------------------------------------------------------------------------------
// Кубическая сплайн-интерполяция
template< typename T >
class CubicSpline
{
public:
	struct out_of_range: exception
	{
		const char *what() const;// noexcept( true ) override;
	};
	struct too_few_points: exception
	{
		const char *what() const;// noexcept( true ) override;
	};

	CubicSpline() {}
	CubicSpline( std::size_t size );

	T operator()( T x );

	void compute();
	CubicSpline &addPoint( T x, T y );

private:
	struct Point {
		T x;
		T y;
		bool operator<( const Point &p ) const {
			return x < p.x;
		}
	};

	std::vector< Point > points;
	std::map< T, std::size_t > xs;
	std::vector< HornerScheme< T > > hss;
};

template< typename T >
const char *CubicSpline< T >::out_of_range::what() const// noexcept( true )
{
	return
		"Exception in: \n"
		"template< typename T > \n"
		"T CubicSpline< T >::operator()( T x )\n\n"
		"Exception text: \n"
		"x is out of range \n\n";
}

template< typename T >
const char *CubicSpline< T >::too_few_points::what() const// noexcept( true )
{
	return
		"Exception in: \n"
		"template< typename T > \n"
		"void CubicSpline< T >::compute() \n\n"
		"Exception text: \n"
		"There is too few points";
}

template< typename T >
inline
CubicSpline< T >::CubicSpline( std::size_t size )
{
	points.reserve( size );
	hss.reserve( size );
}

template< typename T >
inline
T CubicSpline< T >::operator()( T x )
{
	using namespace std;
	if( xs.begin()->first > x || (--xs.end())->first < x )
		throw( out_of_range() );
	typename map< T, size_t >::iterator p = xs.lower_bound( x );
	if( x < p->first ) --p;
	return hss[ p->second ]( x-p->first );
}

template< typename T >
void CubicSpline< T >::compute()
{
	using namespace std;
	if( points.size() < 3 ) throw( too_few_points() );
	sort( points.begin(), points.end() );
	hss.resize( points.size() );

	const size_t size1 = points.size()-2;
	vector< T > a( size1 );
	vector< T > b( size1 );
	vector< T > c( size1 );
	vector< T > f( size1+2 );

	T dyc;
	T dxc;
	T dyl = points[ 1 ].y-points[ 0 ].y;
	T dxl = points[ 1 ].x-points[ 0 ].x;
	for( size_t i = 0; i < size1; ++i )
	{
		dyc = points[ i+2 ].y-points[ i+1 ].y;
		dxc = points[ i+2 ].x-points[ i+1 ].x;

		a[ i ] = 2.*dxl*dxl*dxc;
		c[ i ] = dxl*dxc*dxc;
		b[ i ] = a[ i ]+4.*c[ i ];
		f[ i+1 ] = 6.*(dxl*dyc-dxc*dyl);

		dxl = dxc;
		dyl = dyc;
	}

	typename vector< T >::iterator f_from_1 = f.begin()+1;
	tridiagonalMatrixAlgorithm( a, b, c, f_from_1, size1 );
	f[ 0 ] = 0.;
	f[ size1+1 ] = 0.;

	vector< T > coeffs( 4 );
	const size_t size2 = points.size()-1;
	for( size_t i = 0; i < size2; ++i )
	{
		dyc = points[ i+1 ].y-points[ i ].y;
		dxc = points[ i+1 ].x-points[ i ].x;
		coeffs[ 0 ] = points[ i ].y;
		coeffs[ 2 ] = f[ i ];
		coeffs[ 3 ] = ( f[ i+1 ]-2.*f[ i ] )/(6.*dxc);
		coeffs[ 1 ] = dyc/dxc-f[ i ]*dxc-coeffs[ 3 ]*dxc*dxc;
		hss[ i ].setCoeffs( coeffs );
	}
	hss[ size2 ].setCoeffs( coeffs );
	for( size_t i = 0; i < points.size(); ++i )
		xs[ points[ i ].x ] = i;
	points.clear();
}

template< typename T >
inline
CubicSpline< T > &CubicSpline< T >::addPoint( T x, T y )
{
	Point p = { x, y };
	points.push_back( p );
	return *this;
}

#endif // LAGRANGEPOLYNOMIAL_H
