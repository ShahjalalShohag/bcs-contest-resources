#include <bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(0); cin.tie(0)
using LL = long long;

const int B = 31;

class Trie
{
private:
    struct Node
    {
        int wordCount, prefixCount;
        Node **next;

        Node(int ALPHABET): wordCount(0), prefixCount(0)
        {
            next = new Node*[ALPHABET];
            for(int i = 0; i < ALPHABET; i++) next[i] = NULL;
        }
    };

    Node *root;
    int ALPHABET;

    Node* search(const vector<int> &word)
    {
        Node *curr = root;

        for(int x: word)
        {
            if(curr->next[x] == NULL) return NULL;
            curr = curr->next[x];
        }

        return curr;
    }

    void freeNode(Node *node)
    {
        if(node == NULL) return;

        for(int i = 0; i < ALPHABET; i++)
        {
            if(node->next[i] != NULL) freeNode(node->next[i]);
        }

        delete[] node->next;
        delete node;
    }

public:

    Trie(int alphabet): ALPHABET(alphabet)
    {
        root = new Node(ALPHABET);
    }

    ~Trie()
    {
        freeNode(root);
    }

    void insert(const vector<int> &word)
    {
        Node *curr = root;
        curr->prefixCount++;

        for(int x: word)
        {
            if(curr->next[x] == NULL) curr->next[x] = new Node(ALPHABET);

            curr = curr->next[x];
            curr->prefixCount++;
        }

        curr->wordCount++;
    }

    int countWord(const vector<int> &word)
    {
        Node *curr = search(word);

        if(curr == NULL) return 0;
        return curr->wordCount;
    }

    int countPrefix(const vector<int> &word)
    {
        Node *curr = search(word);

        if(curr == NULL) return 0;
        return curr->prefixCount;
    }

    void erase(const vector<int> &word, int times = 1)
    {
        Node *curr = search(word);

        assert(curr != NULL);
        assert(curr->wordCount >= times);

        curr = root;
        curr->prefixCount -= times;

        for(int x: word)
        {
            Node *nxt = curr->next[x];
            nxt->prefixCount -= times;
            curr = nxt;
        }

        curr->wordCount -= times;
    }
};

vector<int> getBits(int x)
{
    vector<int> v(B);

    for(int i = 0; i < B; i++) v[i] = ((x >> i) & 1);

    reverse(v.begin(), v.end());

    return v;
}



void pre()
{
    fastio;

    
}

void solve(int tc)
{
    int i, b, n;
    cin >> n;

    vector<int> v(n);
    for(auto &x: v) cin >> x;

    LL temp, ans = 1e12;

    Trie trie(2);
    for(auto x: v)
    {
        auto bits = getBits(x);

        temp = 0;
        vector<int> prefix;

        for(i = 0; i < B; i++)
        {
            prefix.push_back(bits[i]);

            if(trie.countPrefix(prefix) == 0)
            {
                temp += 1LL << (B - 1 - i);
                prefix.back() ^= 1;
            }
        }

        trie.insert(bits);
        ans = min(ans, temp);
    }

    cout << ans;
}

int main()
{
    pre();

    int tc, tt = 1;
    cin >> tt;
    
    for(tc = 1; tc <= tt; tc++)
    {
        // cout << "Case " << tc << ": ";
        solve(tc);
        cout << '\n';
    }

    return 0;
}