#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

class Mountain {
public:
	vector<vector<char>> mountain_map; // a - z ch=97-122
	pair<int, int> at;
	int &y = (at.first);
	int &x = (at.second);
	Mountain()
	{
		string row;
		bool end = false;
		int i = 0;
		while (!end && getline(cin,row)) // reading while we don't find an empty line
		{
			if (row.empty()) // if we find an empty line
				end = true;
			else
			{
				mountain_map.push_back(vector<char>()); // filling up the matrixes with vectors
				for (int j = 0; j < row.size(); j++)
				{
					if (row[j] == 'S') // if we find the start we save its coordinates
					{
						y = i; // y coordinate
						x = j; // x coordinate
					}
					mountain_map[i].push_back(row[j]);
				}
				i++;
			}
		}
	}
	vector<pair<int, int>> Neighbour()
	{
		vector<pair<int, int>> result;
		if (x - 1 >= 0) // we check all possible neighbour to see if they would be out of bounds
			if (int(mountain_map[y][x - 1]) <= int(mountain_map[y][x]) + 1)
				result.push_back({ y, x - 1 });
		if (y - 1 >= 0)
			if (int(mountain_map[y - 1][x]) <= int(mountain_map[y][x]) + 1)
				result.push_back({ y - 1, x });
		if (x + 1 <= mountain_map.size())
			if (int(mountain_map[y][x + 1]) <= int(mountain_map[y][x]) + 1)
				result.push_back({ y, x + 1 });
		if (y + 1 <= mountain_map.size())
			if (int(mountain_map[y + 1][x]) <= int(mountain_map[y][x]) + 1)
				result.push_back({ y + 1, x });
		return result;
	}
	void Diagnostics()
	{
		cout << "----------------------------------\n";
		for (int i = 0; i < mountain_map.size(); i++)
		{
			for (int j = 0; j < mountain_map[i].size(); j++)
				cout << mountain_map[i][j] << "";
			cout << "\n";
		}
		cout << "\nNumber of rows: " << mountain_map.size() << "\nNumber of colums: " << mountain_map[0].size();
		cout << "\nStarting pozition: x = " << x << " y = " << y;
		StepDiagnostics(at);
	}
	void StepDiagnostics(pair<int, int> new_at)
	{
		cout << "\n----------------------------------\n";
		at = new_at;
		vector<pair<int, int>> neigbours;
		if (mountain_map[y][x] == 'S')
			mountain_map[y][x] = 'a';
		neigbours = Neighbour();
		cout << "Eligible neigbours of x = " << x << " y = " << y << " are:";
		for (int i = 0; i < neigbours.size(); i++)
		{
			cout << "\n\tx= " << neigbours[i].first << " y = " << neigbours[i].second;
			cout << " " << mountain_map[neigbours[i].first][neigbours[i].second] << "(" << int(mountain_map[neigbours[i].first][neigbours[i].second]) << ")";
		}
		cout << "\nWe are on a(n): " << mountain_map[y][x] << "(" << int(mountain_map[y][x]) << ")\t(a - z ch=97-122)";
	}
	vector<vector<int>> ShortestPath(pair<int, int> from)
	{
		
	}
};

int main()
{
	Mountain mountain;
	mountain.Diagnostics();
}

/*
Sabqponm
abcryxxl
accszExk
acctuvwj
abdefghi
*/
/*
abaaaaaccccccccccccccccccaaaaaaaaaaaaaccccaaaaaaaccccccccccccccccccccccccccccaaaaaa
abaaaaaaccaaaacccccccccccaaaaaaaaacaaaacaaaaaaaaaacccccccccccccccccccccccccccaaaaaa
abaaaaaacaaaaaccccccccccaaaaaaaaaaaaaaacaaaaaaaaaacccccccccccccaacccccccccccccaaaaa
abaaaaaacaaaaaacccccccccaaaaaaaaaaaaaaccaaacaaaccccccccccccccccaacccccccccccccccaaa
abccaaaccaaaaaacccaaaaccaaaaaaaaaaaaaccccaacaaacccccccccaacaccccacccccccccccccccaaa
abcccccccaaaaaccccaaaacccccaaaaacccaaaccaaaaaaccccccccccaaaaccccccccccccccccccccaac
abcccccccccaaaccccaaaacccccaaaaacccccccccaaaaaccccccccccklllllccccccccccccccccccccc
abcccccccccccccccccaaccccccccaaccccccccaaaaaaaccccccccckklllllllcccccddccccaacccccc
abaccccccccccccccccccccccccccaaccccccccaaaaaaaaccccccckkkklslllllcccddddddaaacccccc
abacccccccccccccccccccccccccccccccaaaccaaaaaaaaccccccckkkssssslllllcddddddddacccccc
abaccccccccccccccccccccccccccccccccaaaaccaaacaccccccckkksssssssslllmmmmmdddddaacccc
abcccccccccccccccaaacccccccccccccaaaaaaccaacccccccccckkkssssusssslmmmmmmmdddddacccc
abcccccccaaccccaaaaacccccccccccccaaaaaccccccaaaaaccckkkrssuuuussssqmmmmmmmmdddccccc
abcccccccaaccccaaaaaacccccccaaccccaaaaacccccaaaaacckkkkrruuuuuussqqqqqqmmmmdddccccc
abccccaaaaaaaacaaaaaacccccccaaaaccaaccaccccaaaaaacjkkkrrruuuxuuusqqqqqqqmmmmeeccccc
abcaaaaaaaaaaacaaaaaccccccaaaaaacccccaaccccaaaaajjjjrrrrruuuxxuvvvvvvvqqqmmmeeccccc
abcaacccaaaaccccaaaaaaacccaaaaacccacaaaccccaaaajjjjrrrrruuuxxxxvvvvvvvqqqmmeeeccccc
abaaaaccaaaaacccccccaaaccccaaaaacaaaaaaaacccaajjjjrrrrtuuuuxxxyvyyyvvvqqqnneeeccccc
abaaaaaaaaaaacccaaaaaaaccccaacaacaaaaaaaacccccjjjrrrttttuxxxxxyyyyyvvvqqnnneeeccccc
abaaaaaaaccaacccaaaaaaaaacccccccccaaaaaaccccccjjjrrrtttxxxxxxxyyyyyvvvqqnnneeeccccc
SbaaaaaacccccccccaaaaaaaaaccccccccaaaaacccccccjjjrrrtttxxxEzzzzyyyvvrrrnnneeecccccc
abaaaaacccccccccccaaaaaaacccccccccaaaaaaccccccjjjqqqtttxxxxxyyyyyvvvrrrnnneeecccccc
abaaacccccccccccaaaaaaaccaaccccccccccaaccaaaaajjjqqqttttxxxxyyyyyyvvrrrnnneeecccccc
abaaacccccccccccaaaaaaaccaaacaaacccccccccaaaaajjjjqqqtttttxxyywyyyywvrrnnnfeecccccc
abcaaacccccccaaaaaaaaaaacaaaaaaaccccccccaaaaaaciiiiqqqqtttxwyywwyywwwrrrnnfffcccccc
abcccccccccccaaaaaaaaaaccaaaaaacccccccccaaaaaacciiiiqqqqttwwywwwwwwwwrrrnnfffcccccc
abccccccccccccaaaaaacccaaaaaaaacccccccccaaaaaaccciiiiqqqttwwwwwswwwwrrrrnnfffcccccc
abccccccccccccaaaaaacccaaaaaaaaacccccccccaaacccccciiiqqqtswwwwssssrrrrrroofffcccccc
abccccccaaaaacaaaaaacccaaaaaaaaaaccccccccccccccccciiiqqqssswsssssssrrrrooofffaccccc
abccccccaaaaacaaccaaccccccaaacaaacccccccccccccccccciiiqqssssssspoorrrooooofffaacccc
abcccccaaaaaacccccccccccccaaacccccccccccccccccccccciiiqppssssspppooooooooffffaacccc
abcccccaaaaaacccccccccccccaacccccccccccccccccccccccciipppppppppppoooooooffffaaccccc
abcccccaaaaaaccccccccccccccccccccccccccccccccccccccciihppppppppgggggggggfffaaaccccc
abccccccaaacccccccccccccccccccccccaccccccccccccccccchhhhpppppphggggggggggfaaaaccccc
abaaaccccccccccccccccccccccaccccaaacccccccccccccccccchhhhhhhhhhgggggggggcaacccccccc
abaaccaaaccaccccccccccccccaaacccaaacaacccaaaaacccccccchhhhhhhhhgaaccccccccccccccccc
abaaacaaacaacccccccccaaaccaaaacaaaaaaaaccaaaaaccccccccchhhhhhaaaaacccccccccccccccca
abaaaccaaaaaccccccccccaaacaaaaaaaacaaaaccaaaaaaccccccccccaaacccaaaacccccccccccaccca
abcccaaaaaaccccccccccaaaaaaaaaaaaacaaaaccaaaaaaccccccccccaaaccccaaaccccccccccaaaaaa
abcccaaaaaaaacccccccaaaaaaaaaaaaaaaaaccccaaaaaacccccccccccccccccccccccccccccccaaaaa
abcccaacaaaaaccccccaaaaaaaaaaaaaaaaaaacccccaacccccccccccccccccccccccccccccccccaaaaa
*/
// https://adventofcode.com/2022/day/12