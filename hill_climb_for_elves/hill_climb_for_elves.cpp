#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <queue>

using namespace std;

class Mountain {
public:
	vector<vector<char>> mountain_map; // a - z ch = 97-122
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
						row[j] = '{'; // has a value of ch = 123
					}
					mountain_map[i].push_back(row[j]);
				}
				i++;
			}
		}
	}
	vector<pair<int, int>> neighbour(pair<int, int> coord)
	{
		vector<pair<int, int>> result;
		// we check all possible neighbour to see if they would be out of bounds
		if (coord.first - 1 >= 0) // at y = -1
			if (int(mountain_map[coord.first - 1][coord.second]) <= int(mountain_map[coord.first][coord.second]) + 1)
				result.push_back({ coord.first - 1, coord.second });
		if (coord.second - 1 >= 0) // at x = -1
			if (int(mountain_map[coord.first][coord.second - 1]) <= int(mountain_map[coord.first][coord.second]) + 1)
				result.push_back({ coord.first, coord.second - 1 });
		if (coord.second + 2 <= mountain_map[0].size()) // at vector.size < x (we add +2 because pair.second is an index and vector.size is a value)
			if (int(mountain_map[coord.first][coord.second + 1]) <= int(mountain_map[coord.first][coord.second]) + 1)
				result.push_back({ coord.first, coord.second + 1 });
		if (coord.first + 2 <= mountain_map.size()) // at vector.size < y
			if (int(mountain_map[coord.first + 1][coord.second]) <= int(mountain_map[coord.first][coord.second]) + 1)
				result.push_back({ coord.first + 1, coord.second });
		return result;

	}
	void diagnostics()
	{
		cout << "----------------------------------\n";
		for (int i = 0; i < mountain_map.size(); i++)
		{
			for (int j = 0; j < mountain_map[i].size(); j++)
			{
				if (mountain_map[i][j] == '{')
					cout << 'E';
				else
					cout << mountain_map[i][j];
			}
			cout << "\n";
		}
		cout << "\nNumber of rows: " << mountain_map.size() << "\nNumber of colums: " << mountain_map[0].size();
		cout << "\nStarting pozition: x = " << sx << " y = " << sy;
		cout << "\nEnding pozition: x = " << end_coord.second << " y = " << end_coord.first;
		step_diagnostics(start_coord);
	}
	void step_diagnostics(pair<int, int> new_start_coord)
	{
		cout << "\n----------------------------------\n";
		start_coord = new_start_coord;
		vector<pair<int, int>> neigbours;
		if (mountain_map[sy][sx] == 'S')
			mountain_map[sy][sx] = 'a';
		neigbours = neighbour(start_coord); // gives back coordinates of neigbours as y, x
		cout << "Eligible neigbours of x = " << sx << " y = " << sy << " are:";
		for (int i = 0; i < neigbours.size(); i++)
		{
			cout << "\n\tx= " << neigbours[i].first << " y = " << neigbours[i].second;
			cout << " " << mountain_map[neigbours[i].first][neigbours[i].second] << "(" << int(mountain_map[neigbours[i].first][neigbours[i].second]) << ")";
		}
		cout << "\nWe are on a(n): " << mountain_map[sy][sx] << "(" << int(mountain_map[sy][sx]) << ")\t(a - z ch=97-122)";
	}
	int result_making(vector<vector<pair<int, int>>> route)
	{
		vector<vector<char>> result(mountain_map.size(),vector<char>(mountain_map[0].size(), '.'));
		pair<int, int> current_from = route[end_coord.first][end_coord.second];
		pair<int, int> current = end_coord;
		int min_steps = 0;
		result[end_coord.first][end_coord.second] = 'E';
		while (current_from != make_pair(-1, -1))
		{
			if (current.second - 1 == current_from.second)
				result[current_from.first][current_from.second] = '>';
			else if (current.second + 1 == current_from.second)
				result[current_from.first][current_from.second] = '<';
			else if (current.first - 1 == current_from.first)
				result[current_from.first][current_from.second] = 'V';
			else if (current.first + 1 == current_from.first)
				result[current_from.first][current_from.second] = '^';
			current = current_from;
			current_from = route[current_from.first][current_from.second];
			min_steps++;
		}
		for (int i = 0; i < result.size(); i++)
		{
			cout << "\n";
			for (int j = 0; j < result[i].size(); j++)
				cout << result[i][j] << " ";
		}
		return min_steps;
	}
	int shortest_path(pair<int, int> start_coords)
	{
		vector<vector<int>> color(mountain_map.size(), vector<int>(mountain_map[0].size()));
		vector<vector<pair<int, int>>> from(mountain_map.size(), vector<pair<int, int>>(mountain_map[0].size(), {-1,-1}));
		int white = 0; // yet to be processed
		int grey = 1; // is in queue
		int black = 2; // is processed
		bool end = false;
		queue<pair<int, int>> todo;
		todo.push(start_coords);
		color[start_coords.first][start_coords.second] = grey;
		while (!end && !todo.empty())
		{
			pair<int, int> to_process = todo.front();
			todo.pop();
			color[to_process.first][to_process.second] = black;
			vector<pair<int, int>> neigbours = neighbour(to_process);
			for (int i = 0; i < neigbours.size(); i++)
				if (color[neigbours[i].first][neigbours[i].second] == white)
				{
					todo.push(neigbours[i]);
					from[neigbours[i].first][neigbours[i].second] = to_process;
					color[neigbours[i].first][neigbours[i].second] = grey;
				}
			if (to_process == end_coord)
				end = true;
		}
		/** /
		cout << "\n";
		for (int i = 0; i < from.size(); i++)
		{
			for (int j = 0; j < from[i].size(); j++)
				cout << "{" << from[i][j].first << ", " << from[i][j].second << "} ";
			cout << "\n";
		}
		for (int i = 0; i < color.size(); i++)
		{
			for (int j = 0; j < color[i].size(); j++)
				cout << color[i][j];
			cout << "\n";
		}
		/**/
		return result_making(from);
	}
	void shortest_of_all_path()
	{
		vector<pair<int, int>> starting_coords;
		for (int i = 0; i < mountain_map.size(); i++)
			for (int j = 0; j < mountain_map[i].size(); j++)
				if (mountain_map[i][j] == 'a')
				{
					vector<pair<int, int>> neigbours = neighbour({ i, j });
					for (int k = 0; k < neigbours.size(); k++)
						if (mountain_map[neigbours[k].first][neigbours[k].second] == 'b')
							starting_coords.push_back({i, j});
				}
		for (int i = 0; i < starting_coords.size(); i++)
			cout << shortest_path(starting_coords[i]);
	}
};

int main()
{
	Mountain mountain;
	mountain.diagnostics();
	cout << "\n" << mountain.shortest_path(mountain.start_coord);
	//mountain.ShortestOfAllPath();
}

/*
Sabqponm
abcryxxl
accszExk
acctuvwj
abdefghi
*/
/*
abccccaaaaaaacccaaaaaaaccccccccccccccccccccccccccccccccccaaaa
abcccccaaaaaacccaaaaaaaaaaccccccccccccccccccccccccccccccaaaaa
abccaaaaaaaaccaaaaaaaaaaaaaccccccccccccccccccccccccccccaaaaaa
abccaaaaaaaaaaaaaaaaaaaaaaacccccccccaaaccccacccccccccccaaacaa
abaccaaaaaaaaaaaaaaaaaacacacccccccccaaacccaaaccccccccccccccaa
abaccccaaaaaaaaaaaaaaaacccccccccccccaaaaaaaaaccccccccccccccaa
abaccccaacccccccccaaaaaacccccccccccccaaaaaaaacccccccccccccccc
abcccccaaaacccccccaaaaaaccccccccijjjjjjaaaaaccccccaaccaaccccc
abccccccaaaaacccccaaaacccccccciiijjjjjjjjjkkkkkkccaaaaaaccccc
abcccccaaaaacccccccccccccccccciiiirrrjjjjjkkkkkkkkaaaaaaccccc
abcccccaaaaaccccccccccccccccciiiirrrrrrjjjkkkkkkkkkaaaaaccccc
abaaccacaaaaacccccccccccccccciiiqrrrrrrrrrrssssskkkkaaaaacccc
abaaaaacaaccccccccccccccccccciiiqqrtuurrrrrsssssskklaaaaacccc
abaaaaacccccccccccaaccccccccciiqqqttuuuurrssusssslllaaccccccc
abaaaaaccccccccaaaaccccccccciiiqqqttuuuuuuuuuuusslllaaccccccc
abaaaaaacccccccaaaaaaccccccciiiqqqttxxxuuuuuuuusslllccccccccc
abaaaaaaccccaaccaaaaacccccchhiiqqtttxxxxuyyyyvvsslllccccccccc
abaaacacccccaacaaaaaccccccchhhqqqqttxxxxxyyyyvvsslllccccccccc
abaaacccccccaaaaaaaacccccchhhqqqqtttxxxxxyyyvvssqlllccccccccc
abacccccaaaaaaaaaaccaaacchhhpqqqtttxxxxxyyyyvvqqqlllccccccccc
SbaaacaaaaaaaaaaaacaaaaahhhhppttttxxEzzzzyyvvvqqqqlllcccccccc
abaaaaaaacaaaaaacccaaaaahhhppptttxxxxxyyyyyyyvvqqqlllcccccccc
abaaaaaaccaaaaaaaccaaaaahhhppptttxxxxywyyyyyyvvvqqqmmcccccccc
abaaaaaaacaaaaaaacccaaaahhhpppsssxxwwwyyyyyyvvvvqqqmmmccccccc
abaaaaaaaaaaaaaaacccaacahhhpppssssssswyyywwvvvvvqqqmmmccccccc
abaaaaaaaacacaaaacccccccgggppppsssssswwywwwwvvvqqqqmmmccccccc
abcaaacaaaccccaaaccccccccgggppppppssswwwwwrrrrrqqqmmmmccccccc
abcaaacccccccccccccccccccgggggpppoosswwwwwrrrrrqqmmmmddcccccc
abccaacccccccccccccccccccccgggggoooosswwwrrrnnnmmmmmddddccccc
abccccccccccccccccccccccccccgggggooossrrrrrnnnnnmmmddddaccccc
abaccccaacccccccccccccccccccccgggfoossrrrrnnnnndddddddaaacccc
abaccaaaaaaccccccccccccccccccccgffooorrrrnnnneeddddddaaaacccc
abaccaaaaaacccccccccccccccccccccfffooooonnnneeeddddaaaacccccc
abacccaaaaaccccccccaaccaaaccccccffffoooonnneeeeccaaaaaacccccc
abcccaaaaacccccccccaaccaaaaccccccffffoooneeeeeaccccccaacccccc
abaccaaaaaccccccccaaaacaaaaccccccafffffeeeeeaaacccccccccccccc
abacccccccccccccccaaaacaaacccccccccffffeeeecccccccccccccccaac
abaaaacccccccaaaaaaaaaaaaaacccccccccfffeeeccccccccccccccccaaa
abaaaacccccccaaaaaaaaaaaaaaccccccccccccaacccccccccccccccccaaa
abaacccccccccaaaaaaaaaaaaaaccccccccccccaacccccccccccccccaaaaa
abaaaccccccccccaaaaaaaaccccccccccccccccccccccccccccccccaaaaaa
*/
// https://adventofcode.com/2022/day/12