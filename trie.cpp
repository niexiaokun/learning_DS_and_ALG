#include <bits/stdc++.h>


using namespace std;


class Trie {

private:
    struct Node{
        bool isWord;
        map<char, Node*> next;
        Node(bool isWord){
            this->isWord = isWord;
        }
        Node(){
            this->isWord = false;
        }
    };

    Node* root;
    int sz;

public:
    Trie(){
        root = new Node();
        sz = 0;
    };

    ~Trie(){
        destroyNode(root);
    };

    void destroyNode(Node* root){
        if(root == NULL)
            return;
        for(pair<char, Node*> ptr : root->next){
            destroyNode(ptr.second);
        }
        delete root;
    };

    void add(string word){
        Node* cur = root;
        for(int i = 0; i < word.size(); i++){
            char c = word[i];
            if(!cur->next.count(c))
                cur->next[c] = new Node();
            cur = cur->next[c];
        }
        if(!cur->isWord){
            cur->isWord = true;
            sz++;
        }
    };

    void erase(string word){
        Node* cur = root;
        for(int i = 0; i < word.size(); i++){
            char c = word[i];
            if(!cur->next.count(c))
                return;
            cur = cur->next[c];
        }
        if(cur->isWord){
            cur->isWord = false;
            sz--;
        }
    };

    bool contains(string word){
        Node* cur = root;
        for(int i = 0; i < word.size(); i++){
            char c = word[i];
            if(!cur->next.count(c))
                return false;
            cur = cur->next[c];
        }
        return cur->isWord;
    };

    int size(){
        return sz;
    };

};


int main(int argc, char* argv[]){

    Trie trie;

    trie.add("cat");
    trie.add("dog");
    trie.add("pandas");

    cout << trie.size() << endl;
    cout << boolalpha << trie.contains("pandas") << endl;
    cout << boolalpha << trie.contains("pan") << endl;

    trie.add("pan");
    cout << trie.size() << endl;
    cout << boolalpha << trie.contains("pan") << endl;

    trie.erase("dog");
    cout << trie.size() << endl;
    cout << trie.contains("dog") << endl;

    trie.erase("cat");
    cout << trie.size() << endl;
    cout << trie.contains("cat") << endl;

    trie.erase("cat");
    cout << trie.size() << endl;
    cout << trie.contains("cat") << endl;

    return 0;
}