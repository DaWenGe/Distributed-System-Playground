#include <vector>
#include <iostream>

using namespace std;

template <typename T>
class IIterator {
public:
    IIterator() = default;
    virtual ~IIterator() = default;
    virtual T next() = 0;
    virtual bool hasNext() = 0;
};

template <typename T>
class IteratorImpl : public IIterator {
private:
    int mCurIndex = 0;
    vector<T> mData;
public:
    IteratorImpl(const vector<T> & data) : mData(data) {};
    ~IteratorImpl() {}
    T next() override {
        if (hasNext())
            return mData[mCurIndex++];
        return T();
    }
    bool hasNext() override {
        return mCurIndex < mData.size();
    }
};

template <typename T>
class PeekingIterator : public IIterator {
private:
    T mPeekedElement;
    bool mHasPeeked = false;
    IIterator* mBaseIter;
public:
    PeekingIterator(const IIterator* iter) : mBaseIter(iter) {}
    ~PeekingIterator() {}
    T next() override {
        if (!mHasPeeked)
            return mBaseIter->next();
        auto retVal = mPeekedElement;
        mPeekedElement = T();
        mHasPeeked = false;
        return retVal;
    }
    T peek() {
        if (!mHasPeeked) {
            mPeekedElement = mBaseIter->next();
            mHasPeeked = true;
        }
        return mPeekedElement;
    }
    bool hasNext() override {
        return mHasPeeked || mBaseIter->hasNext();
    }
};