/**
 * @algorithm 广度优先搜索 (BFS)
 * @time_complexity O(N) - 每个节点入队出队一次
 * @space_complexity O(W) - W 为最大层数节点数（宽度）
 */

#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};


class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (root == nullptr) return result;

        // 核心工具：队列（存放在内存堆区）
        queue<TreeNode*> que;
        que.push(root);

        while (!que.empty()) {
            // 【关键步骤】：记录当前层的节点个数
            // 这一步决定了你处理的是“当前层”还是把所有东西混在一起
            int size = que.size();
            vector<int> currentLevel;
            currentLevel.reserve(size); // 再次强调：性能习惯

            for (int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                
                currentLevel.push_back(node->val);

                // 将下一层的孩子放入队列
                if (node->left) que.push(node->left);
                if (node->right) que.push(node->right);
            }
            // 当前层处理完毕，装入结果集
            result.push_back(move(currentLevel)); // 侯捷：使用 move 避免深拷贝
        }
        return result;
    }
};

