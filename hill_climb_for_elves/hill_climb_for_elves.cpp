#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <queue>

using namespace std;

class Mountain {
public:
	vector<vector<char>> mountain_map; // a - z ch=97-122
	pair<int, int> start_coord;
	pair<int, int> end_coord;
	int &sy = start_coord.first;
	int &sx = start_coord.second;
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
					if (row[j] == 'S') // if we find the Start we save its coordinates
					{
						sy = i; // y coordinate
						sx = j; // x coordinate
					}
					if (row[j] == 'E') // if we find the End we save its coordinates
					{
						end_coord.first = i; // y coordinate
						end_coord.second = j; // x coordinate
					}
					mountain_map[i].push_back(row[j]);
				}
				i++;
			}
		}
	}
	vector<pair<int, int>> Neighbour(pair<int, int> coord)
	{
		vector<pair<int, int>> result;
		// we check all possible neighbour to see if they would be out of bounds
		if (coord.second - 1 >= 0) // at x = -1
			if (int(mountain_map[coord.first][coord.second - 1]) <= int(mountain_map[coord.first][coord.second]) + 1)
				result.push_back({ coord.first, coord.second - 1 });
		if (coord.first - 1 >= 0) // at y = -1
			if (int(mountain_map[coord.first - 1][coord.second]) <= int(mountain_map[coord.first][coord.second]) + 1)
				result.push_back({ coord.first - 1, coord.second });
		if (coord.second + 2 <= mountain_map[0].size()) // at vector.size < x (we add +2 because pair.second is an index and vector.size is a value)
			if (int(mountain_map[coord.first][coord.second + 1]) <= int(mountain_map[coord.first][coord.second]) + 1)
				result.push_back({ coord.first, coord.second + 1 });
		if (coord.first + 2 <= mountain_map.size()) // at vector.size < y
			if (int(mountain_map[coord.first + 1][coord.second]) <= int(mountain_map[coord.first][coord.second]) + 1)
				result.push_back({ coord.first + 1, coord.second });
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
		cout << "\nStarting pozition: x = " << sx << " y = " << sy;
		cout << "\nEnding pozition: x = " << end_coord.second << " y = " << end_coord.first;
		StepDiagnostics(start_coord);
	}
	void StepDiagnostics(pair<int, int> new_start_coord)
	{
		cout << "\n----------------------------------\n";
		start_coord = new_start_coord;
		vector<pair<int, int>> neigbours;
		if (mountain_map[sy][sx] == 'S')
			mountain_map[sy][sx] = 'a';
		neigbours = Neighbour(start_coord); // gives back coordinates of neigbours as y, x
		cout << "Eligible neigbours of x = " << sx << " y = " << sy << " are:";
		for (int i = 0; i < neigbours.size(); i++)
		{
			cout << "\n\tx= " << neigbours[i].first << " y = " << neigbours[i].second;
			cout << " " << mountain_map[neigbours[i].first][neigbours[i].second] << "(" << int(mountain_map[neigbours[i].first][neigbours[i].second]) << ")";
		}
		cout << "\nWe are on a(n): " << mountain_map[sy][sx] << "(" << int(mountain_map[sy][sx]) << ")\t(a - z ch=97-122)";
	}
	vector<vector<char>> ResultMaking(vector<vector<pair<int, int>>> route)
	{
		vector<vector<char>> result;

		return result;
	}
	vector<vector<char>> ShortestPath(pair<int, int> start_coords)
	{
		vector<vector<int>> color;
		vector<vector<pair<int, int>>> from;
		int white = 0; // yet to be processed
		int grey = 1; // is in queue
		int black = 2; // is processed
		bool end = false;
		for (int i = 0; i < mountain_map.size(); i++)
		{
			color.push_back(vector<int>());
			from.push_back(vector<pair<int, int>>());
			for (int j = 0; j < mountain_map[i].size(); j++)
			{
				color[i].push_back(0);
				from[i].push_back({ -1, -1 });
			}
		}
		queue<pair<int, int>> todo;
		todo.push(start_coords);
		color[start_coords.first][start_coords.second] = grey;

		while (!end && !todo.empty())
		{
			pair<int, int> to_process = todo.front();
			todo.pop();
			if (to_process == end_coord)
			{
				end = true;
			}
			color[to_process.first][to_process.second] = black;
			vector<pair<int, int>> neigbours = Neighbour(to_process);
			for (int i = 0; i < neigbours.size(); i++)
			{
				if (color[neigbours[i].first][neigbours[i].second] == white)
				{
					todo.push(neigbours[i]);
					from[neigbours[i].first][neigbours[i].second] = to_process;
					color[neigbours[i].first][neigbours[i].second] = grey;
				}
			}
		}
		/**/
		cout << "\n";
		for (int i = 0; i < from.size(); i++)
		{
			for (int j = 0; j < from[i].size(); j++)
				cout << "{" << from[i][j].first << ", " << from[i][j].second << "} ";
			cout << "\n";
		}
		/**/
		return ResultMaking(from);
	}
};

int main()
{
	Mountain mountain;
	mountain.Diagnostics();
	mountain.ShortestPath(mountain.start_coord);
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