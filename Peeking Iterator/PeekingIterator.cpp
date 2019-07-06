#include <vector>
#include <iostream>
using namespace std;

class IIterator {
public:
    IIterator() = default;
    virtual ~IIterator() = default;
    virtual int next() = 0;
    virtual bool hasNext() = 0;
};

class IteratorImpl : public IIterator {
private:
    vector<int> mData;
    int mCurIndex = 0;
public:
    IteratorImpl(const vector<int> & nums) : mData(nums) {};
    ~IteratorImpl() {};
    int next() override {
        if (!hasNext())
            return -1;
        return mData[mCurIndex++];
    };
    bool hasNext() override {
        return mCurIndex < mData.size();
    };
};

class PeekingIterator : public IIterator {
private:
    IIterator* mBaseIter;
    bool mHasPeeked = false;
    int mPeekedValue = -1;
public:
    PeekingIterator(IIterator* iter) : mBaseIter(iter) {}
    ~PeekingIterator() {}
    int next() override {
        if (!mHasPeeked)
            return mBaseIter->next();
        auto retVal = mPeekedValue;
        mHasPeeked = false;
        mPeekedValue = -1;
        return retVal;
    };
    bool hasNext() override {
        return mHasPeeked || mBaseIter->hasNext();
    };
    int peek() {
        if (!mHasPeeked) {
            mPeekedValue = mBaseIter->next();
            mHasPeeked = true;
        }
        return mPeekedValue;
    }
};

int main(int argc, char const *argv[])
{
    vector<int> data {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto * peekingIter = new PeekingIterator(new IteratorImpl(data));
    while (true && peekingIter->hasNext())
    {
        auto value = peekingIter->peek();
        std::cout << "Peeked value: " << value;
        std::cout << " Move on to the next value." << std::endl;
        value = peekingIter->next();
        if (rand() % 3 == 0) {
            value = peekingIter->peek();
            std::cout << "LOL! Peeked again: " << value << std::endl;
        }
    }

    delete peekingIter;
    
    return 0;
}
