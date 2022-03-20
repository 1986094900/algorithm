

#include <iostream>

// 本算法list从1开始, list[0]无用
int list[7] = {0, 2, 3, 5, 7, 4, 6};

class Tree {
public:
    int val;
    int l;
    int r;
};

Tree trees[20];

void build(int root, int left, int right) {
    if (left == right) {
        trees[root].l = left;
        trees[root].r = right;
        trees[root].val = list[left];
        return;
    }
    int mid = (left + right) >> 1;
    build(root * 2, left, mid);
    build(root * 2 + 1, mid + 1, right);
    trees[root].l = left;
    trees[root].r = right;
    trees[root].val = trees[root * 2].val + trees[root * 2 + 1].val;
}

void update(int root, int left, int right, int start, int end, int k) {
    if (left == right) {
        trees[root].val += k;
        return;
    }
    int mid = (left + right) >> 1;
    if (start <= mid) {
        update(root * 2, left, mid, start, end, k);
    }
    if (end >= mid + 1) {
        update(root * 2 + 1, mid + 1, right, start, end, k);
    }
    trees[root].val = trees[root * 2].val + trees[root * 2 + 1].val;
}

int query(int root, int left, int right, int start, int end) {
    if (start <= left && end >= right) {
        return trees[root].val;
    }
    int mid = (left + right) >> 1;
    int sum = 0;
    if (start <= mid) {
        sum += query(root * 2, left, mid, start, end);
    }
    if (end >= mid + 1) {
        sum += query(root * 2 + 1, mid + 1, right, start, end);
    }
    return sum;
}

void print(int root, int left, int right) {
    std::cout << "node : " << root << " left : " << trees[root].l << " right : " << trees[root].r
        << " val : " << trees[root].val << std::endl;
    if (left == right) {
        return;
    }
    int mid = (left + right) >> 1;
    print(root * 2, left, mid);
    print(root * 2 + 1, mid + 1, right);
}

int main() {
    int root = 1;
    int left = 1, right = 6;
    build(root, left, right);

    for (int i = left; i <= right; ++i) {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;
    print(root, left, right);
    std::cout << "query 1 - 6 :" << query(root, left, right, 1, 6) << std::endl;
    std::cout << "update 10 : " << std::endl;
    update(1, 1, 6, 1, 6, 10);
    std::cout << "query 1 - 6 :" << query(root, left, right, 1, 6) << std::endl;
    print(root, left, right);
    
}
