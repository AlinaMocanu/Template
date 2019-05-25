#include <iostream>
#include <exception>
//#define NDEBUG
#include <assert.h>

using namespace std;
template < class T, unsigned n >
class Vector
{
    T *memblock;
public:
    Vector();
    Vector( T value );
    Vector( Vector& );
    Vector& operator = ( const Vector& );
    const unsigned getdim() const;
    Vector operator + ( const Vector& );
    Vector operator - ( const Vector& );
    T operator * ( const Vector& );
    T& operator [] ( unsigned );
    Vector operator * ( T );
    template < class W, unsigned m >
    friend ostream& operator << ( ostream& os, const Vector< W, m>& );
    ~Vector();
};

template < class T, unsigned n >
Vector< T, n >::Vector()
{
    try
    {
        memblock = new T[n];
    }
    catch ( exception& e )
    {
        cout<< "standard exception : " << e.what() <<endl;
    }
}

template < class T, unsigned n >
Vector< T, n >::Vector( T value )
{
    try
    {
        memblock = new T[n];
        for( unsigned i = 0; i < n; i++ )
            memblock[i] = value;
    }
    catch ( exception& e )
    {
        cout<< "standard exception : " << e.what() <<endl;
    }
}

template < class T, unsigned n >
Vector< T, n >::Vector( Vector& ob )
{
    try
    {
        memblock = new T[ob.getdim()];
        for( unsigned i = 0; i < ob.getdim(); i++ )
            memblock[i] = ob.memblock[i];
    }
    catch ( exception& e )
    {
        cout<< "standard exception : " << e.what() <<endl;
    }
}

template < class T, unsigned n >
Vector< T, n >& Vector< T, n >::operator = ( const Vector& ob )
{
    try
    {
        if(this != &ob)
        {
            for( unsigned i = 0; i < ob.getdim(); i++ )
                memblock[i] = ob.memblock[i];
        }
        else
            throw 1;
    }
    catch(const int x)
    {
        cout<<"Self assignment!"<<endl;
    }

    return *this;
}

template < class T, unsigned n >
const unsigned Vector< T, n >::getdim() const
{
    return n;
}

template < class T, unsigned n >
Vector< T, n > Vector< T, n >::operator + ( const Vector& ob )
{
    Vector< T, n > result;
    for( unsigned i = 0; i < n; i++ )
        result.memblock[i] = memblock[i] + ob.memblock[i];
    return result;
}

template < class T, unsigned n >
Vector< T, n > Vector< T, n >::operator - ( const Vector& ob )
{
    Vector< T, n > result;
    for( unsigned i = 0; i < n; i++ )
        result.memblock[i] = memblock[i] - ob.memblock[i];
    return result;
}

template < class T, unsigned n >
T Vector< T, n >::operator * ( const Vector& ob )
{
    T result = 0;
    for( unsigned i = 0; i < n; i++ )
        result += memblock[i] * ob.memblock[i];
    return result;
}

template < class T, unsigned n >
T& Vector< T, n >::operator [] ( unsigned j )
{
    if( j >= n )
        throw out_of_range( "Index invalid" );
    return memblock[j];

}

template < class T, unsigned n >
Vector< T, n > Vector< T, n >::operator * ( T k )
{
    Vector< T, n> result(0) ;
    for( unsigned i = 0; i < n; i++ )
        result.memblock[i] = k * memblock[i];
    return result;
}

template < class T, unsigned n >
ostream& operator << ( ostream& os, const Vector< T, n >& ob )
{
    for( unsigned i = 0; i < n; i++ )
        os<< ob.memblock[i] <<" ";
    return os;
}

template < class T, unsigned n >
Vector< T, n >::~Vector()
{
    delete[] memblock;
    memblock = NULL;
}

int main()
{
    Vector< int, 10 > arr(3);
    Vector< int, 10 > arr2(7);
    Vector< int, 10 > arr3(arr2);
    Vector< int, 10 > arr4;
    Vector< int, 10 > res;
    arr4 = arr3;

    assert(arr.getdim() == 10);
    for( unsigned i = 0; i < arr.getdim(); i++ )
        assert(arr[i] == 3);

    assert(arr3.getdim() == arr2.getdim());
    for( unsigned i = 0; i < arr2.getdim(); i++ )
        assert(arr3[i] == arr2[i] );

    assert(arr4.getdim() == arr3.getdim()) ;
    for( unsigned i = 0; i < arr4.getdim(); i++ )
        assert(arr2[i] == arr3[i] );


    for( unsigned i = 0; i < arr.getdim(); i++ )
        cout<< arr[i] << " ";
    cout<<endl;

    for( unsigned i = 0; i < arr2.getdim(); i++ )
        cout<< arr2[i] << " ";
    cout<<endl;

    for( unsigned i = 0; i < arr.getdim(); i++ )
        cout<< arr3[i] << " ";
    cout<<endl;


    for( unsigned i = 0; i < arr.getdim(); i++ )
        cout<< arr4[i] << " ";
    cout<<endl;

    cout<< "dimensiunea vectorilor : " << arr.getdim() <<endl;
    cout<< arr << " + "<<arr2 << " = ";
    res = arr + arr2;
    for( unsigned i = 0; i < res.getdim(); i++ )
        assert(res[i] == 10 );
    cout<<res;
    cout<<endl;

    cout<< arr3 << " - "<<arr << " = ";
    res = arr3 - arr;
    for( unsigned i = 0; i < res.getdim(); i++ )
        assert(res[i] == 4 );
    cout<<res;
    cout<<endl;

    cout<< arr3 << " * "<<arr4 << " = ";
    float res2;
    res2 = arr3 * arr4;
    assert(res2 == 490 );
    cout<<res2;
    cout<<endl;

    int k = 5;
    cout<< k << " * "<<arr4 << " = ";
    res = arr4 * k;
    for( unsigned i = 0; i < res.getdim(); i++ )
        assert(res[i] == 35);
    cout<<res;
    cout<<endl;

    return 0;
}
