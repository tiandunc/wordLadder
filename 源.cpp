#include<iostream>
#include<vector>
#include<string>
#include<unordered_set>
#include<queue>
#include<map>
using namespace std;
struct Node
{
	string word;
	int level;
	Node(string&x, int y) :word(x), level(y){}
};
class Solution
{
public:
	map<string, unordered_set<string>> graph;
	vector<vector<string>> path;
	int ladderLength(string beginWord, string endWord, unordered_set<string>& wordDict) 
	{
		Node start(beginWord, 0);
		queue<Node> qu;
		qu.push(start);
		wordDict.insert(endWord);
		while (!qu.empty())
		{
			Node tnode = qu.front();
			qu.pop();
			if (tnode.word == endWord)
				return tnode.level + 1;
			string& word = tnode.word;
			int wordlen = word.length();
			for (int i = 0; i < wordlen; i++)
			{
				char ch = word[i];
				for (int j = 0; j < 26; j++)
				{

					if (word[i] == 'a' + j)
						continue;
					word[i] = 'a' + j;
					if (wordDict.find(word) != wordDict.end())
					{
						qu.push(Node(word, tnode.level + 1));
						wordDict.erase(word);
					}
				}
				word[i] = ch;
			}
		}
		return 0;
	}
	void createGraph(string beginword, string endword, unordered_set<string>& wordDict)
	{
		unordered_set<string> cur_layer, next_layer;
		cur_layer.insert(beginword);
		unordered_set<string> unvisited = wordDict;
		unvisited.insert(endword);
		while (unvisited.size() > 0)
		{
			for (auto& e : cur_layer)
			{
				int len = e.length();
				string tmp_word = e;
				for (int i = 0; i < len; i++)
				{
					char ch = tmp_word[i];
					for (int j = 0; j < 26; j++)
					{
						if (ch == 'a' + j)
							continue;
						tmp_word[i] = 'a' + j;
						if (unvisited.find(tmp_word) != unvisited.end())
						{
							next_layer.insert(tmp_word);
							graph[e].insert(tmp_word);
						}
					}
					tmp_word[i] = ch;
				}
			}
			if (next_layer.empty())
				break;
			for (auto &e : cur_layer)
				unvisited.erase(e);
			cur_layer = next_layer;
			next_layer.clear();
		}
	}
	void dfs(vector<string>& cur_path, string& start, const string& end)
	{
		if (start == end)
		{
			path.push_back(cur_path);
			return;
		}
		for (auto e : graph[start])
		{
			cur_path.push_back(e);
			dfs(cur_path, e, end);
			cur_path.pop_back();
		}
	}
	vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict) {
		createGraph(start, end, dict);
		vector<string> tpath;
		dfs(tpath, start, end);
		return path;
	}
};
int main()
{
	unordered_set<string> dict = { "hot", "dot", "dog", "lot", "log" };
	string begin = "hit", end = "cog";
	Solution sln;
	//int step = sln.ladderLength(begin, end, dict);
	//cout << "Step = " << step << endl;
	vector<vector<string>> path = sln.findLadders(begin, end, dict);
	for (auto& vec : path)
	{
		for (auto&e : vec)
		{
			cout << e << "==>";
		}
		cout << endl;
	}
	return 0;
}