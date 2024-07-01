#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <ctime>

template <typename T>
class TreapNode {
private:
    T key;
    int priority;
    int sum_below;
    int count_below;
    std::shared_ptr<TreapNode<T>> left;
    std::shared_ptr<TreapNode<T>> right;

public:
    TreapNode(T key) : key(key), priority(rand()), sum_below(key), count_below(1), left(nullptr), right(nullptr) {}
    TreapNode(T key, int priority) : key(key), priority(priority), sum_below(key), count_below(1), left(nullptr), right(nullptr) {}
    ~TreapNode() {
        std::cout << "Key " << key << " destroyed." << std::endl;
    }
    
    // Reset the sum below figure for the node to include itself and all left + right nodes.
    void reset_sum() 
    {
        sum_below = key;
        if (left) sum_below += left->sum_below;
        if (right) sum_below += right->sum_below;
    }

    // Reset the count below figure for the node to include itself and all left + right nodes.
    void reset_count()
    {
        count_below = 1;
        if (left) count_below += left->count_below;
        if (right) count_below += right->count_below;
    }

    int no_children() const
    {
        // Base case: if the node is null, return 0.
        if (!this)
        {
            return 0;
        }
        // If the node has no children, return 1.
        else if (!left && !right)
        {
            return 1;
        }

        // Recursively count the leaf nodes in the left and right subtrees.
        int left_count = (left) ? left->no_children() : 0;
        int right_count = (right) ? right->no_children() : 0;

        return left_count + right_count;
    }

    int one_child() const 
    {
        // Base case: if the node is null, return 0.
        if (!this)
        {
            return 0;
        }

        // Initialise count to 0.
        int count = 0;

        // Check if the node has exactly one child. If exactly one child is present, increment count.
        if ((left && !right) || (!left && right))
        {
            count = 1; 
        }

        // Recursively count the nodes with one child in the left and right subtrees.
        int left_count = (left) ? left->one_child() : 0;
        int right_count = (right) ? right->one_child() : 0;

        // Return the total count of nodes with one child from this node's perspective.
        return count + left_count + right_count;
    }

    int two_children() const 
    {
        // Base case: if the node is null, return 0.
        if (!this)
        {
            return 0;
        }

        // Initialise count to 0.
        int count = 0;

        // Check if the node has exactly one child. If exactly one child is present, increment count.
        if (left && right)
        {
            count = 1; 
        }

        // Recursively count the nodes with one child in the left and right subtrees.
        int left_count = (left) ? left->two_children() : 0;
        int right_count = (right) ? right->two_children() : 0;

        // Return the total count of nodes with one child from this node's perspective.
        return count + left_count + right_count;
    }

    void right_rotation(std::shared_ptr<TreapNode<T>>& x) {
        std::shared_ptr<TreapNode<T>> y = x->left;
        std::shared_ptr<TreapNode<T>> g = y->right;
        std::shared_ptr<TreapNode<T>> b = x->right;

        x->left = g;       
        y->right = x;
        x->reset_sum();
        y->reset_sum();
        x->reset_count();
        y->reset_count();
        x = y;
    }

    void left_rotation(std::shared_ptr<TreapNode<T>>& y) {
        std::shared_ptr<TreapNode<T>> x = y->right;
        std::shared_ptr<TreapNode<T>> g = x->left;
        std::shared_ptr<TreapNode<T>> b = x->right;

        x->left = y;
        y->right = g;
        y->reset_sum();
        x->reset_sum();
        y->reset_count();
        x->reset_count();
        y = x;
    }

    void insert(std::shared_ptr<TreapNode<T>>& root, T key) {

        if (!root) {
            root = std::make_shared<TreapNode<T>>(key);
            return;
        }

        insert(key <= root->key ? root->left : root->right, key);

        root->reset_sum();
        root->reset_count();

        if (root->left && root->left->priority > root->priority)
            right_rotation(root);

        if (root->right && root->right->priority > root->priority)
            left_rotation(root);
    }

    bool remove(std::shared_ptr<TreapNode<T>>& root, T key) {
        if (!root)
            return false;

        if (key < root->key)
        {
            if (remove(root->left, key))
            {
                root->reset_sum();
                root->reset_count();
                return true;
            }
            return false;
        } 
        else if (key > root->key)
        {
            if (remove(root->right, key))
            {
                root->reset_sum();
                root->reset_count();
                return true;
            }
            return false;
        }

        if (!root->left && !root->right) {
            root.reset();
        } else if (!root->left || !root->right) {
            std::shared_ptr<TreapNode<T>> child = (root->left) ? root->left : root->right;
            root = child;
        } else {
            if (root->left->priority < root->right->priority) {
                left_rotation(root);
                remove(root->left, key);
            } else {
                right_rotation(root);
                remove(root->right, key);
            }
        }

        if (root)
        {
            root->reset_sum();
            root->reset_count();
        }
        return true;
    }

    void split(std::shared_ptr<TreapNode<T>>& t, T key, std::shared_ptr<TreapNode<T>>& l, std::shared_ptr<TreapNode<T>>& r) {
        int inf = INT_MAX;

        insert(t, key, inf);

        l = t->left;
        r = t->right;
    }

    std::shared_ptr<TreapNode<T>> search(std::shared_ptr<TreapNode<T>>& root, T key) {
        if (!root || root->key == key)
            return root;
        if (root->key < key)
            return search(root->right, key);
        if (root->key > key)
            return search(root->left, key);
    }

    void heapify(std::shared_ptr<TreapNode<T>> t) {
        if (!t)
            return;

        std::shared_ptr<TreapNode<T>> max = t;

        if (t->left && t->left->priority > max->priority)
            max = t->left;
        if (t->right && t->right->priority > max->priority)
            max = t->right;

        if (max != t)
            std::swap(t->priority, max->priority),
            heapify(max);
    }

    std::shared_ptr<TreapNode<T>> build(std::vector<T>& v, int l, int r) {
        if (l > r)
            return nullptr;

        int m = (l + r) / 2;

        std::shared_ptr<TreapNode<T>> t = std::make_shared<TreapNode<T>>(v[m]);
        t->left = build(v, l, m - 1);
        t->right = build(v, m + 1, r);

        heapify(t);
        return t;
    }

    void printBT(const std::string &prefix, std::shared_ptr<TreapNode<T>> node, bool isLeft)
    {
        if (node != nullptr)
        {
            std::cout << prefix;
            std::cout << (isLeft ? "|--" : "L--");
            // print the value of the node
            std::cout << node->key << " (" << node->priority << ")" << std::endl;
            // enter the next tree level - left and right branch
            printBT(prefix + (isLeft ? "|   " : "    "), node->right, true);
            printBT(prefix + (isLeft ? "|   " : "    "), node->left, false);
        }
    }

    void print_sum_below(std::shared_ptr<TreapNode<T>> node)
    {
        if (node != nullptr) 
        {
            std::cout << "Key: " << node->key << ", Node Sum (Including + Below): " << node->sum_below << std::endl;
            print_sum_below(node->left);
            print_sum_below(node->right);
        }
    }

    void print_count_below(std::shared_ptr<TreapNode<T>> node)
    {
        if (node != nullptr) 
        {
            std::cout << "Key: " << node->key << ", Node Count (Including + Below): " << node->count_below << std::endl;
            print_count_below(node->left);
            print_count_below(node->right);
        }
    }

};

int main() {
    srand(time(NULL));

    std::shared_ptr<TreapNode<int>> t = nullptr;

    std::vector<int> keys{3, 1, 4, 2, 9, 5, 7, 8, 6};

    for (auto key : keys)
        t->insert(t, key);

    t->printBT("", t, false);
    std::cout << std::endl;

    t->print_sum_below(t);
    std::cout << std::endl;

    t->print_count_below(t);
    std::cout << std::endl;

    // Display the count of nodes with no children.
    std::cout << "NODES WITH NO CHILDREN: " << t->no_children() << std::endl;

    // Display the count of nodes with exactly one child.
    std::cout << "NODES WITH ONE CHILD: " << t->one_child() << std::endl;

    // Display the count of nodes with no children.
    std::cout << "NODES WITH TWO CHILDREN: " << t->two_children() << std::endl << std::endl;

    return 0;
}
