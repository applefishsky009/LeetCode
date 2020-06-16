#include <queue>
#include <string>
#include <iostream>
#include <D:/Github/RylModule/tree.h>
using namespace std;

class Codec1 {
  public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string str = "[";
        if (!root)
            return str += "]";
        TreeNode *p = root;
        queue<TreeNode *> q;
        q.push(p);
        string tmp;
        while(!q.empty()) {
            p = q.front();
            q.pop();
            if (p) {
                tmp += (to_string(p->val) + ",");
                str += tmp;
                tmp = "";
                q.push(p->left);
                q.push(p->right);
            }
            else {
                tmp += "null,";
            }
        }
        str[str.size() - 1] = ']';
        return str;
    }
    
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.size() <= 2)
            return nullptr;
        TreeNode *root;
        TreeNode *cur;
        vector<int> ans;
        size_t pos = 0;
        data[data.size() - 1] = ',';
        queue<TreeNode *> q;
        queue<TreeNode *> qa;
        do {
            pos = data.find_first_of(',');
            string tmp = data.substr(1, pos - 1);
            data = data.substr(pos);
            data[0] = '[';
            if (tmp[0] == 'n') {
                q.push(nullptr);
            } else {
                TreeNode *tmp_p = new TreeNode(stoi(tmp));
                q.push(tmp_p);
            }
        } while(data.size() > 2);
        root = q.front();q.pop();
        cur = root;
        qa.push(cur);
        while (!q.empty()) {
            do {
            cur = qa.front();qa.pop();
            } while(!cur);
            cur->left = q.front();qa.push(cur->left);q.pop();
            if (q.empty()) break;
            cur->right = q.front();qa.push(cur->right);q.pop();
        }
        return root;
    }
};

// 编解码
class Codec {
public:
    string serialize(TreeNode* root) {
        if (!root) return "X";
        auto l = "(" + serialize(root->left) + ")";
        auto r = "(" + serialize(root->right) + ")";
        return  l + to_string(root->val) + r;
    }

    inline TreeNode* parseSubtree(const string &data, int &ptr) {
        ++ptr; // 跳过左括号
        auto subtree = parse(data, ptr);
        ++ptr; // 跳过右括号
        return subtree;
    }

    inline int parseInt(const string &data, int &ptr) {
        int x = 0, sgn = 1;
        if (!isdigit(data[ptr])) {
            sgn = -1;
            ++ptr;
        }
        while (isdigit(data[ptr])) {
            x = x * 10 + data[ptr++] - '0';
        }
        return x * sgn;
    }

    TreeNode* parse(const string &data, int &ptr) {
        if (data[ptr] == 'X') {
            ++ptr;
            return nullptr;
        }
        auto cur = new TreeNode(0);
        cur->left = parseSubtree(data, ptr);
        cur->val = parseInt(data, ptr);
        cur->right = parseSubtree(data, ptr);
        return cur;
    }

    TreeNode* deserialize(string data) {
        int ptr = 0;
        return parse(data, ptr);
    }
};

int main() {
    Codec s;
    TreeNode* root = constructTree(vector<int> () = {1, 2, 3, -1, -1, 4, 5});
    // string str = "[1,2,3,null,null,4,5]";
    // string str = "[1,2]";
    // string str = "[1,-1,2,-2]";
    string str = "[5,2,3,null,null,2,4,3,1]";
    cout << s.serialize(root) << endl;
    showTree(s.deserialize(s.serialize(root)));
    return 1;
}