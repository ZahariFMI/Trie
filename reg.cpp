#include <iostream>
using namespace std;

class Node
{
    bool isend;
    Node* child[26];
public:

    Node()
    {
        isend=false;
        for(int i=0; i<26; i++)
        {
            child[i] = nullptr;
        }
    }
    Node(const Node&) = delete;
    Node& operator= (const Node& ) = delete;
    ~Node()
    {
        for(int i=0; i<26; i++)
            delete child[i];
    }

    bool getEnd()
    {
        return isend;
    }

    void setEnd()
    {
        isend = true;
    }

    Node* getChild(int code)
    {
        return child[code];
    }

    void makeChild(int code)
    {
        child[code] = new Node();
    }
};

class Trie
{
    Node * root;

public:
    Trie()
    {
        root = new Node();
    }
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;
    ~Trie()
    {
        delete root;
    }

    void Add(string& s)
    {
        Node* curr = root;
        int i,code;
        for(int i=0; i < s.size(); i++)
        {
            code = s[i]-'a';
            if(curr->getChild( code ) == nullptr)
                curr->makeChild( code );
            curr = curr->getChild( code );
        }
        curr->setEnd();
    }

    bool Query(string &s)
    {
        Node* curr = root;
        int i,code;
        for(int i=0; i<s.size(); i++)
        {
            code = s[i] - 'a';
            if(curr->getChild(code) == nullptr)
                return false;
            curr = curr->getChild(code);
        }

        if(curr->getEnd())
            return true;
        else
            return false;
    }
};

bool validate(string &s)
{
    for(int i=0; i<s.size(); i++)
        if( s[i] < 'a' || s[i] > 'z' )
            return false;
    return true;
}

int main()
{
    Trie trie;
    int nwords,queries;
    cin>>nwords;

    string s;
    for(int i=0; i<nwords; i++)
    {
        cin>>s;
        if(validate(s))
            trie.Add(s);
        else
            cout<<"Invalid input"<< endl;
    }

    cin>>queries;
    for(int i=0; i<queries; i++)
    {
        cin>>s;
        if(validate(s))
        {
            if(trie.Query(s))
                cout<<"word found\n";
            else
                cout<<"word not found\n";
        }
        else
            cout <<"Invalid input"<< endl;
    }
    return 0;
}
