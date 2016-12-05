#include <queue>
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

struct UndirectedGraphNode
{
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x){};
};

//BFS
class Solution
{
  public:
    UndirectedGraphNode *cloneGraph(const UndirectedGraphNode *node)
    {
		if (node == nullptr)
			return nullptr;
		//key是原始节点，val是复制的节点
		unordered_map<const UndirectedGraphNode *, UndirectedGraphNode *> copied; //hash保存已创建过的的节点
		queue<const UndirectedGraphNode *> q;
		q.push(node);
		copied[node] = new UndirectedGraphNode(node->label); //[key]访问key的val；.find(key)返回指向key的指针
		//copied.insert(make_pair(node, new UndirectedGraphNode(node->label)));	//等同于上一句
		//访问已有Key:node,copied.find(node)->first,copied.find(node)->second
		while (!q.empty())
		{
			const UndirectedGraphNode *cur = q.front();
			q.pop();
			const UndirectedGraphNode *nbr = nullptr;
			for (int i = 0; i < cur->neighbors.size(); ++i)
			{
				//for (auto nbr : cur->neighbors) {	//这一行可以代替上边两行
				nbr = cur->neighbors[i];
				if (copied.find(nbr) == copied.end())
				{ //没有创建过
					UndirectedGraphNode *new_node = new UndirectedGraphNode(nbr->label);
					copied[nbr] = new_node;
					copied[cur]->neighbors.push_back(new_node);
					q.push(nbr);
				}
				else
					copied[cur]->neighbors.push_back(copied[nbr]);
			}
		}
		return copied[node];
    }
};

int main()
{
    Solution s1;
    UndirectedGraphNode *node0 = new UndirectedGraphNode(0);
    UndirectedGraphNode *node1 = new UndirectedGraphNode(1);
    UndirectedGraphNode *node2 = new UndirectedGraphNode(2);
    node0->neighbors.push_back(node1);
    node0->neighbors.push_back(node2);
    node1->neighbors.push_back(node2);
    node2->neighbors.push_back(node2);
    UndirectedGraphNode *result = s1.cloneGraph(node0);
    return 0;
}