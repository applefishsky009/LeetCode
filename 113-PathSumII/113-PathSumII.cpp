#include <E:\RylModule\tree.h>
using namespace std;

class Solution
{
  public:
    vector<vector<int>> pathSum(TreeNode *root, int sum)
    {
        vector<vector<int>> matrix;
        vector<int> path;
        pathSumDFS(root, matrix, path, sum);
        return matrix;
    }

  private:
    void pathSumDFS(TreeNode *root, vector<vector<int>> &matrix, vector<int> &path, int sum) //path must be Reference(effective!)
    {
        if (!root)
            return;
        if (!root->left && !root->right)
        {
            if (sum == root->val)
            {
                path.push_back(root->val);
                matrix.push_back(path);
                path.pop_back();
                return;
            }
        }
        // if (sum < root->val) //negative interger is possible
        //     return;
        path.push_back(root->val);
        pathSumDFS(root->left, matrix, path, sum - root->val);
        pathSumDFS(root->right, matrix, path, sum - root->val);
        path.pop_back();
        return;
    }
};

int main()
{
    TreeNode *root = constructTree(vector<int>() = {5, 4, 8, 11, -1, 13, 4, 7, 2, -1, -1, -1, -1, 5, 1});
    showTree(root);
    int sum = 22;
    Solution s1;
    vector<vector<int>> matrix = s1.pathSum(root, sum);
    cout << matrix.size() << endl;
    show2DVector(matrix);
    return 0;
}