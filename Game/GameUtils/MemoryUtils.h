#ifndef MEMORYUTILS_H
#define MEMORYUTILS_H

namespace Utils
{
    class IReferenceCount;
    template <typename T> class Smart_Ptr;
}

/** The IReferenceCount class us our framework neutral reference counting class **/
class Utils::IReferenceCount
{
    // *****************************
    // * CONSTRUCTORS / DESTRUCTOR *
    // *****************************
    public:
        //! Constructor
        IReferenceCount() : count(0) {}
        //! Destructor
        ~IReferenceCount() {}

    protected:
        // Members and Methods

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // Members and Methods

    protected:
        // Members and Methods

    // *****************************
    // * REFERENCE COUNT FUNCTIONS *
    // *****************************
    public:
        //! Add Reference
        void addReference()
        {
            // Increment our reference count
            this->count++;
        }
        //! Release (return the count)
        int release()
        {
            // Decrement the reference count
            return --(this->count);
        }

    protected:
        // The reference count
        long long count;

};

/** The smart_ptr class is our implementation independant
    smart pointer class. **/
template <typename T> class Utils::Smart_Ptr
{
    // *****************************
    // * CONSTRUCTORS / DESTRUCTOR *
    // *****************************
    public:
        //! Default Constructor
        Smart_Ptr() : pData(0), pReferenceCount(0)
        {
            // Create a new reference
            this->pReferenceCount = new Utils::IReferenceCount();
            // Increment the reference count
            this->pReferenceCount->addReference();
        }
        //! Constructor
        Smart_Ptr(T* pValue) : pData(pValue), pReferenceCount(0)
        {
            // Create a new Reference Counter
            this->pReferenceCount = new Utils::IReferenceCount();
            // Increment the reference Count
            this->pReferenceCount->addReference();
        }
        //! Copy Constructor
        Smart_Ptr(const Smart_Ptr<T>& smart_Ptr) : pData(smart_Ptr.pData), pReferenceCount(smart_Ptr.pReferenceCount)
        {
            /* The function signature here makes a copy of the data
                and the reference counter so lets just add a reference */
            this->pReferenceCount->addReference();
        }
        //! Destructor
        ~Smart_Ptr()
        {
            // If after release we have no more references
            if (this->pReferenceCount->release() == 0)
            {
                // Delete the Data
                delete pData;
                // Delete the Reference Counter
                delete pReferenceCount;
            }
        }

    protected:
        // Members and Methods

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        //! Deference Operator
        T& operator*() { return *pData; }
        //! Deference Operator
        T* operator->() { return pData; }
        //! Assignment Operator
        Smart_Ptr<T>& operator= (const Smart_Ptr<T>& smart_Ptr)
        {
            // Do not permid self assignment
            if (this != &smart_Ptr)
            {
                // If after release we have no more references
                if (this->pReferenceCount->release() == 0)
                {
                    // Delete the Data
                    delete pData;
                    // Delete the Reference Counter
                    delete pReferenceCount;
                }
                // Assign the Data
                this->pData = smart_Ptr.pData;
                // Assign the Reference Counter
                this->pReferenceCount = smart_Ptr.pReferenceCount;
                // Add a reference
                this->pReferenceCount->addReference();
            }
            return *this;
        }

    protected:
        // Members and Methods

    // ***************************
    // * SMART POINTER FUNCTIONS *
    // ***************************
    public:
        //! Add a reference manually (you shouldn't need to call this)
        virtual void addReference()
        {
            if (this->pReferenceCount != 0)
            {
                this->pReferenceCount->addReference();
            }
        }
        //! Release a reference manually (you shouldn't need to call this)
        virtual void removeReference()
        {
            // If after release we have no more references
            if (this->pReferenceCount->release() == 0)
            {
                // Delete the Data
                delete pData;
                // Delete the Reference Counter
                delete pReferenceCount;
            }
        }

    protected:
        // Pointer to our data of template Type T
        T* pData;
        // Pointer to our reference counter
        Utils::IReferenceCount* pReferenceCount;
};

#endif // MEMORYUTILS_H
