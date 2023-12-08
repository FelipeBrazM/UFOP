/*!
 \file Bridge.h
 \brief The classes Handle and Body implements "bridge" design pattern (also known as 
	"handle/body idiom").The class Body was implemented based on the class teCounted
	writed by Ricardo Cartaxo and Gilberto C�mara and founded in the geographic library TerraLib.
 \author Prof. Tiago Garcia de Senna Carneiro - UFOP, MG, Brazil
*/


#if ! defined( HANDLE_BODY )
#define HANDLE_BODY
#include <typeinfo>
#include <iostream>

using namespace std;
//#define DEBUGING
#ifdef DEBUGING
    extern int numHandleCreated;
	extern int numHandleDeleted;
	extern int numBodyCreated;
	extern int numBodyDeleted;
#endif

/** 
 * \brief
 *
 * The classes Handle and Body implements the "bridge" design pattern (also known as
 * "handle/body idiom").
 * 
 */
template <class T> 
class Handle
{

public:	

	/// constructor
	Handle<T>( ){  
		pImpl_ = new T; 
        pImpl_->attach();
		// cout<< typeid(T).name() << endl;
		#ifdef DEBUGING
			numHandleCreated++; 
			cout << numHandleCreated;
			
		#endif
	}
	
	/// Destructor
	virtual ~Handle<T>() {
		pImpl_->detach();
		#ifdef DEBUGING
			numHandleDeleted++;
		#endif
	}

	/// copy constructor 
	Handle<T>( const Handle& hd ):pImpl_( hd.pImpl_ ) { pImpl_->attach();  }

	/// assignment operator
	Handle<T>& operator=( const Handle& hd) {
		if (  this != &hd )
		{
			hd.pImpl_->attach();
			pImpl_->detach();	
			pImpl_  = hd.pImpl_;
		}
		return *this;
	}
protected:

	/// refer�ncia para a implementa��o
	T *pImpl_; 
};

/**
 * \brief
 * 
 * The class Implementation was implemented based on the class teCounted writed by Ricardo Cartaxo 
 * and Gilberto C�mara and founded in the geographic library TerraLib.
 */

class Body
{	
public:
	/// Constructor: zero references when the object is being built
	Body(): refCount_ (0) {
		#ifdef DEBUGING		
			numBodyCreated++;
		#endif
	}
	

	/// Increases the number of references to this object
	void attach ()	{ refCount_++; }

	/// Decreases the number of references to this object.
	/// Destroy it if there are no more references to it
	void detach (){	
		if ( --refCount_ == 0 )	{ 
			delete this; 
		}
	}

	/// Returns the number of references to this object
	int refCount(){ return refCount_; }

	/// Destructor
	virtual ~Body() {
		#ifdef DEBUGING
			numBodyDeleted++; 
		#endif
	}

private:

	/// No copy allowed
	Body(const Body&);

	/// Implementation
	Body& operator=(const Body&){return *this;}

	int refCount_; 	/// the number of references to this class

};

#endif