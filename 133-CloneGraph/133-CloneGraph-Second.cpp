#include <queue>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <D:/Github/RylModule/node.h>
using namespace std;

// bfs - 可以不用两个队列, 用一个node*-node*的队列即可
// time: O(n)
// space: O(n)
class Solution0 {
  public:
	Node *cloneGraph(Node *node) {
		if (!node) return nullptr;
		unordered_map<int, Node*> iumap;
		queue<Node *> iq;
		queue<Node *> iq_ans;
		iq.push(node);
		iumap[1] = new Node(1);
		iq_ans.push(iumap[1]);
		while (!iq.empty()) {
			Node *cur = iq.front(); iq.pop();
			Node *ans_cur = iq_ans.front(); iq_ans.pop();
			for (auto x : cur->neighbors) {
				if (!iumap.count(x->val)) {	// 没有访问过, 新建并加入访问队列
					iumap[x->val] = new Node(x->val);
					iq.push(x);
					iq_ans.push(iumap[x->val]);
				}
				ans_cur->neighbors.push_back(iumap[x->val]);	// 创建邻接关系
			}
		}
		return iumap[1];
	}
};

// dfs
// time: O(n)
// space: O(n)
class Solution {
  public:
	Node *cloneGraph(Node *node) {
		unordered_map<Node*, Node*> iumap;
		return dfs(node, iumap);
	}
  private:
	Node *dfs(Node *node, unordered_map<Node*, Node*> &iumap) {
		if (node == nullptr) return nullptr;	// 不用构造
		if (iumap.find(node) != iumap.end()) return iumap[node];	// 已经构造过了
		Node *cloneNode = new Node(node->val);	// 新建
		iumap[node] = cloneNode;	// 记录
		for (auto &neighbor : node->neighbors)
			cloneNode->neighbors.emplace_back(dfs(neighbor, iumap));	//	dfs构造邻接关系
		return cloneNode;	// 完成构造
	}
};

int main() {
	Solution s;
	Node *i1 = new Node(1);
	Node *i2 = new Node(2);
	Node *i3 = new Node(3);
	Node *i4 = new Node(4);
	i1->neighbors.push_back(i2);
	i1->neighbors.push_back(i4);
	i2->neighbors.push_back(i1);
	i2->neighbors.push_back(i3);
	i3->neighbors.push_back(i2);
	i3->neighbors.push_back(i4);
	i4->neighbors.push_back(i1);
	i4->neighbors.push_back(i3);
	Node *res = s.cloneGraph(i1);
	return 0;
}
