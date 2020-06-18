#include <stack>
#include <string>
#include <cctype>
#include <iostream>
#include <algorithm>
#include <D:/Github/RylModule/tree.h>
using namespace std;

class Solution0 {
  public:
    TreeNode* recoverFromPreorder(string S) {
        if (S.size() == 0) return nullptr;
        size_t pos = 0;
        while (pos < S.size() && isdigit(S[pos])) pos++;
        string val_str = S.substr(0, pos);
        int val = str2Int(val_str);
        TreeNode* root = new TreeNode(val);
        size_t start = pos;
        while (pos < S.size() && !isdigit(S[pos])) pos++;

        string sub = S.substr(start, pos - start);  // 找分割串
        size_t second = findNextStr(S, sub, pos);   // 第二个
        root->left = recoverFromPreorder(S.substr(pos, second - pos));
        root->right = second == S.size() ? nullptr : recoverFromPreorder(S.substr(second + sub.size()));    // 第二个不存在，防止substr溢出
        return root;
    }
  private:
    int findNextStr(string &str, string &sstr, size_t idx) {
        auto pos = find_first_of(str.begin() + idx, str.end(), sstr.begin(), sstr.end());
        if (pos < str.end() && isdigit(*(pos + sstr.size()))) return pos - str.begin();
        while (pos < str.end() && !isdigit(*(pos + sstr.size()))) {
            while (!isdigit(*(++pos)));
            return findNextStr(str, sstr, pos - str.begin());
        }
        return str.size();
    }
    int str2Int(string &str) {
        int x = 0, sgn = 1, pos = 0;
        if (!isdigit(str[pos])) {
            sgn = -1;
            pos++;
        }
        while (pos < str.size() && isdigit(str[pos]))
            x = x * 10 + str[pos++] - '0';
        return x * sgn;
    }
};

class Solution {
public:
    TreeNode* recoverFromPreorder(string S) {
        stack<TreeNode*> path;
        int pos = 0;
        while (pos < S.size()) {
            int level = 0;
            while (S[pos] == '-') {
                ++level;
                ++pos;
            }
            int value = 0;
            while (pos < S.size() && isdigit(S[pos])) { // 转数字
                value = value * 10 + (S[pos] - '0');
                ++pos;
            }
            TreeNode* node = new TreeNode(value);
            if (level == path.size()) { // 深度,左节点赋值
                if (!path.empty()) {
                    path.top()->left = node;
                }
            }
            else {
                while (level != path.size()) {  // 回溯,右节点赋值
                    path.pop();
                }
                path.top()->right = node;
            }
            path.push(node);
        }
        while (path.size() > 1) {
            path.pop();
        }
        return path.top();
    }
};

int main() {
    Solution s;
    string str1 = "1-2--3--4-5--6--7";
    string str2 = "1-2--3---4-5--6---7";
    showTree(s.recoverFromPreorder(str1));
    showTree(s.recoverFromPreorder(str2));
    return 1;
}