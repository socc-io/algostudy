//
// trie.h
//
// trie struct for string search
//
// INPUT: vector<string> (keys)
//
// OUTPUT: if string in keys
//
// Time: 	O(M)
//			M: string length
//
//refix define for None-Alphabet
#include <string>
#include <vector>
using namespace std;

#define ALPHABET_SIZE 26
#define MAX_SIZE ALPHABET_SIZE
#define INDEXING(a) ((size_t)a-(size_t)'a')
struct trie_node
{
	size_t value;
	trie_node * children[MAX_SIZE];
};
struct trie_root
{
	trie_node *root;
	size_t count;
};

class trie {
private:
	trie_root root_;
	trie_node * getNode(void)
	{
		trie_node *pNode = NULL;
		pNode = (trie_node *)malloc(sizeof(trie_node));

		if (pNode)
		{
			int i;
			pNode->value = 0;
			for (i = 0; i < MAX_SIZE; i++)
				pNode->children[i] = NULL;
		}

		return pNode;
	}
	void insert(const string& key)
	{
		this->root_.count++;
		trie_node * pCrawl = this->root_.root;

		for (size_t i = 0; i < key.length(); i++)
		{
			int index = INDEXING(key[i]);
			if (!pCrawl->children[index])
				pCrawl->children[index] = this->getNode();

			pCrawl = pCrawl->children[index];
		}
		pCrawl->value = this->root_.count;
	}
	bool find(const string& key)
	{
		trie_node * pCrawl = this->root_.root;

		for (int i = 0; i < key.length(); i++)
		{
			int index = INDEXING(key[i]);

			if (!pCrawl->children[index])
				return 0;

			pCrawl = pCrawl->children[index];
		}

		return (0 != pCrawl && pCrawl->value);
	}

public:
	trie(const vector<string>& keys) 
	{
		this->root_.root = getNode();
		this->root_.count = 0;

		for (string key : keys)
			this->insert(key);
	}
	bool search(const string& string)
	{
		return this->find(string);
	}
	~trie() {}
};
/*
int main()
{
	vector<string> v = { "the", "a", "there", "answer", "any", "by", "bye", "their" };
	trie p(v);
	if (p.search("the"))
		cout << " OO" << endl;
	return 0;
}
*/