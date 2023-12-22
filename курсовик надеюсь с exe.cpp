#include <limits>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian"); // Установка Русского языка.

	int CountVertex, LastVertex; // Кол-во вершин, последняя вершина.
	int FirstVertex, Infinity; // Объявление вершин.
	
	cout << "Введите количество вершин: ";
	cin >> CountVertex;
	cout << "Введите начальную вершину: ";
	cin >> FirstVertex;
	FirstVertex--;
	cout << "Введите конечную вершину: ";
	cin >> LastVertex; 
	LastVertex--;

	Infinity = numeric_limits<int>::max(); // Т.к. расстояние до других вершин неизвестно, приравниваем к бесконечности.

	// Задаём граф с помощью матрицы смежностей:
	vector<vector<int>> ArrVertex(CountVertex, vector<int>(CountVertex));
	
	// Заполним граф:
	cout << "\nЗаполните матрицу смежностей.\n"
		<< "Если в графе есть несвязанные вершины, используйте '-1', для обозначения отсутствия связи:\n";
	for (int i = 0; i < CountVertex; i++) {
		for (int j = 0; j < CountVertex; j++) {
			cin >> ArrVertex[i][j];
			if (ArrVertex[i][j] == -1) {
				ArrVertex[i][j] = Infinity;
			}
		}
	}
	
	// Массив с весом между вершинами:
	vector <int> lenght(CountVertex, Infinity);

	// Очередь с приоритетом для вершин:
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> QueueVertex;

	// Начало алгоритма. Начинаем с первой вершины.
	lenght[FirstVertex] = 0; // Начало (исходящий узел графа) равен 0 (т.к. это расстояние вершины до самой себя).
	QueueVertex.push({ 0, FirstVertex }); // Вставляем в приоритетную очередь начальную вершину.

	// Массив для отслежования посещённых вершин
	vector<bool> visited(CountVertex, false);
	visited[FirstVertex] = true; // Помечаем начальную вершину как посещённую.

	// Массив для хранения предыдущей вершины.
	vector<int> previous(CountVertex, -1); 

	// Шаги повторяем до тех пор, пока на графе есть непосещенные точки.
	while (!QueueVertex.empty()) {
		int distance = -QueueVertex.top().first;
		int vertex = QueueVertex.top().second; // Следующая вершина.
		QueueVertex.pop();

		// Если рассматриваемая длина больше той, что уже хранится, то идём дальше.
		if (distance > lenght[vertex]) {
			continue;
		}

		// Перебираем все вершины.
		for (int v = 0; v < CountVertex; v++) {
			int dist = ArrVertex[vertex][v];
			if (dist != Infinity) {
				if (lenght[v] > lenght[vertex] + dist) {
					lenght[v] = lenght[vertex] + dist;
					QueueVertex.push({ -lenght[v], v });
					visited[v] = true; // Помечаем вершину как посещённую.
					previous[v] = vertex; // Запоминаем предыдущую вершину.
				}

			}
		}
	}

	// В случае несвязанных вершин, вес пути до вершины приравниваем к бесконечности.
	if (lenght[LastVertex] == Infinity) {
		cout << "INF";
	}

	// Вывод кратчайших расстояний:
	for (int i = 0; i < CountVertex; i++) {
		cout << "Кратчайшее расстояние от " << FirstVertex + 1 << " до " << i + 1 << " - " << lenght[i] << endl;
	}

	// Вывод кратчайшего пути:
	if (previous[LastVertex] != -1 || FirstVertex == LastVertex) {
		// Если вершина посещена и мы дошли до конца, то:
		vector<int> path; // Вектор, для хранения вершин кратчайшего пути.
		for (int vertex = LastVertex; vertex != -1; vertex = previous[vertex]) {
			path.push_back(vertex);
		}
		// Переворачиваем, так как рассматривался путь от конечной до исходной вершины.
		reverse(path.begin(), path.end());

		// Выводим кратчайший путь:
		cout << "\nКратчайший путь: ";
		for (int i = 0; i < path.size(); i++) {
			cout << path[i] + 1 << "[" << lenght[i] << "]";
			if (i != path.size() - 1) {
				cout << " -> ";
			}
		}
		cout << endl;
	}
	else { // Иначе по каким-то причинам мы не дошли до конца. Сообщение об отсутсвии пути.
		cout << "\nПути не существует" << endl;
	}
}
