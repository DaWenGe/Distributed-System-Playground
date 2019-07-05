#include <memory>
#include <vector>
#include <iostream>
using namespace std;

class TreeNode {
private:
    std::unique_ptr<TreeNode> mLeft = nullptr;
    std::unique_ptr<TreeNode> mRight = nullptr;
    int mLeftSize = 0;
    int mValue = 0;
public:
    TreeNode(int val) : mValue(val) {}
    void insert(int val) {
        if (val < mValue) {
            if (mLeft) {
                mLeft->insert(val);
            } else {
                mLeft = std::make_unique<TreeNode>(val);
            }
            mLeftSize++;
        } else {
            if (mRight) {
                mRight->insert(val);
            } else {
                mRight = std::make_unique<TreeNode>(val);
            }
        }
    }

    int getRank(int val) {
        if (val == mValue) {
            return mLeftSize;
        } else if (val < mValue) {
            if (!mLeft) return -1;
            return mLeft->getRank(val);
        } else {
            if (!mRight) return -1;
            return mLeftSize + 1 + mRight->getRank(val);
        }
    }
};

std::unique_ptr<TreeNode> root;

void track(int val) {
    if (!::root) {
        ::root = std::make_unique<TreeNode>(val);
    } else {
        ::root->insert(val);
    }
}

int getRank(int val) {
    return ::root->getRank(val);
}

int main(int argc, char const *argv[])
{
    vector<int> data { 5, 1, 4, 4, 5, 9, 7, 13, 3 };
    for (auto val : data) {
        track(val);
        std::cout << "Tracking a new number from stream: " << val << std::endl;
        auto randNumber = rand();
        if (randNumber % 2) {
            std::cout << "Check the rank for number: " << val << std::endl;
            std::cout << "Rank: " << getRank(val) << std::endl;
        }
    }

    return 0;
}
