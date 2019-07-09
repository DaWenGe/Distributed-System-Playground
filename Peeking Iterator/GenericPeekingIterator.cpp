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
class IteratorImpl : public IIterator<T> {
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
class PeekingIterator : public IIterator<T> {
private:
    T mPeekedElement;
    bool mHasPeeked = false;
    IIterator<T> * mBaseIter;
public:
    PeekingIterator(IIterator<T> * iter) : mBaseIter(iter) {}
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

int main(int argc, char const *argv[])
{
    vector<int> data {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto * peekingIter = new PeekingIterator<int>(new IteratorImpl<int>(data));
    while (true && peekingIter->hasNext()) {
        auto value = peekingIter->peek();
        std::cout << "Peeked value: " << value;
        std::cout << " Move on to the next value." << std::endl;
        value = peekingIter->next();
        if (rand() % 3 == 0) {
            value = peekingIter->peek();
            std::cout << "LOL! Peeked again: " << value << std::endl;
        }
    }
    return 0;
}
