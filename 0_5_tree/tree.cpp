#include <iostream>
#include <queue>
using namespace std;
class TreeNode
{
public:
    int val;
    TreeNode* right;
    TreeNode* left;
    TreeNode(int x) : val(x), right(nullptr), left(nullptr){}
};


void levelOrderTraverse(TreeNode* root)
{
    queue<TreeNode* > q;
    int depth = 1;
    q.push(root);
    while (!q.empty())
    {
        int sz = q.size();
        for(int i = 0;i < sz;i ++)
        {
            TreeNode* cur = q.front();
            cout << "depth: " << depth << " " << "val: " << cur->val << endl;
            q.pop();
            if (cur->left != nullptr)
            {
                q.push(cur->left);
            }
            if (cur->right != nullptr)
            {
                q.push(cur->right);
            }
            
        }
        depth ++;
    }
    
}