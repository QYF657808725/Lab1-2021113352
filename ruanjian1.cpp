#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include<iostream>
#include<vector>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<cstdlib>
#pragma warning(disable:4996)
#define MAXLEN 50
#define INFINE 50
struct headnode
{
	char id[20];//单词名
	struct nearnode* near;//邻接节点
	struct headnode* next;//下一个头节点
};
struct nearnode
{
	char id[20];//单词名
	struct nearnode* near;//邻接节点
	int count;//邻接次数
};
using namespace std;
unordered_map<string, sf::Vector2f> nodePositions;
sf::Font font; // 将字体变量移到全局范围内
struct headnode* First;//全局变量整体首部
int number;//节点个数
struct headnode* graph[MAXLEN];
struct headnode* create(FILE* fp);
char* queryBridgeWords(char* word1, char* word2);
char* generateNewText(char* inputText);
void show();
void showDirectedGraph();
char* calcShortestPath(char* word1, char* word2);
char* randonWalk();
//struct headnode* first = First;
void addNode(const string& nodeName, float x, float y) {
	nodePositions[nodeName] = sf::Vector2f(x, y);
}

void addEdge(sf::RenderWindow& window, const string& node1, const string& node2, int weight) {
	sf::Vector2f startPos = nodePositions[node1];
	sf::Vector2f endPos = nodePositions[node2];

	// 计算箭头末端位置
	sf::Vector2f arrowEndPos(endPos.x, endPos.y);

	// 绘制带箭头的线条
	sf::Vertex line[] = {
		sf::Vertex(startPos, sf::Color::Black),
		sf::Vertex(arrowEndPos, sf::Color::Black)
	};
	window.draw(line, 2, sf::Lines);

	// 绘制箭头
	sf::ConvexShape arrow;
	arrow.setPointCount(3);
	arrow.setPoint(0, sf::Vector2f(0, 0));
	arrow.setPoint(1, sf::Vector2f(-8, 3));
	arrow.setPoint(2, sf::Vector2f(-8, -3));
	arrow.setFillColor(sf::Color::Black);
	arrow.setPosition(arrowEndPos);
	float angle = atan2(endPos.y - startPos.y, endPos.x - startPos.x);
	arrow.setRotation(angle * 180 / 3.14159265); // 转换为角度
	window.draw(arrow);

	// 绘制权重
	sf::Text text(to_string(weight), font, 15); // 使用全局的字体
	text.setFillColor(sf::Color::Red);
	text.setPosition((startPos.x + endPos.x) / 2, (startPos.y + endPos.y) / 2);
	window.draw(text);
}
void addblueEdge(sf::RenderWindow& window, const string& node1, const string& node2, int weight) {
	sf::Vector2f startPos = nodePositions[node1];
	sf::Vector2f endPos = nodePositions[node2];

	// 计算箭头末端位置
	sf::Vector2f arrowEndPos(endPos.x, endPos.y);

	// 绘制带箭头的线条
	sf::Vertex line[] = {
		sf::Vertex(startPos, sf::Color::Red),
		sf::Vertex(arrowEndPos, sf::Color::Red)
	};
	window.draw(line, 2, sf::Lines);

	// 绘制箭头
	sf::ConvexShape arrow;
	arrow.setPointCount(3);
	arrow.setPoint(0, sf::Vector2f(0, 0));
	arrow.setPoint(1, sf::Vector2f(-8, 3));
	arrow.setPoint(2, sf::Vector2f(-8, -3));
	arrow.setFillColor(sf::Color::Red);
	arrow.setPosition(arrowEndPos);
	float angle = atan2(endPos.y - startPos.y, endPos.x - startPos.x);
	arrow.setRotation(angle * 180 / 3.14159265); // 转换为角度
	window.draw(arrow);

	//绘制权重
	sf::Text text(to_string(weight), font, 15); // 使用全局的字体
	text.setFillColor(sf::Color::Black);
	text.setPosition((startPos.x + endPos.x) / 2, (startPos.y + endPos.y) / 2);
	window.draw(text);
}
int getposition(char* word1) {
	int m;
	for (m = 0; m < number; m++) {
		if (strcmp(graph[m]->id, word1) == 0) {
			return m;
		}
	}
	return -1;
}
int get_weight(int start, int end) {
	struct 	nearnode* node;
	if (start == end)
		return 0;
	node = graph[start]->near;
	while (node != NULL) {
		if (strcmp(graph[end]->id, node->id) == 0) {
			return node->count;
		}
		node = node->near;
	}
	return INFINE;
}
bool abin(string word1, string word2, int* showpath, int max) {
	while (max != 0) {
		string wordaa = graph[showpath[max]]->id;
		string wordbb = graph[showpath[max - 1]]->id;
		if (word1 == wordaa && word2 == wordbb) {
			return true;
		}
		max--;
	}
	return false;
}
int findnumber(struct headnode* a) {
	struct nearnode* b = a->near;
	int i = 0;
	while (b != NULL) {
		i++;
		b = b->near;
	}
	return i;
}
int find(char* word) {
	struct headnode* a = First;
	while (a != NULL) {
		if (strcmp(a->id, word) == 0) {
			return 1;
		}
		a = a->next;
	}
	return 0;
}



int main()
{
	printf("请输入初始文件名\n");
	char* fpp = (char*)malloc(sizeof(char) * 20);
	scanf("%s", fpp);
	getchar();
	FILE* fp;
	while ((fp = fopen(fpp, "r")) == NULL)
	{
		printf("输入的文件名不存在，请重新输入\n");
		scanf("%s", fpp);
		getchar();
	}
	First = create(fp);
	int i = 0;
	//struct headnode* ver[]
	struct headnode* a = First;
	while (a != NULL) {
		i++;
		a = a->next;
	}
	number = i;

	i = 0;
	a = First;
	while (a != NULL) {
		graph[i] = a;
		i++;
		a = a->next;
	}
	while (1)
	{
		show();
		int choose;
		scanf("%d", &choose);
		getchar();
		switch (choose)
		{
		case 1:
		{
			showDirectedGraph();
		}
		break;
		case 2:
		{
			printf("请输入第一个单词:");
			char* word1 = (char*)malloc(sizeof(char) * 20);
			scanf("%s", word1);
			getchar();
			printf("请输入第二个单词:");
			char* word2 = (char*)malloc(sizeof(char) * 20);
			scanf("%s", word2);
			getchar();
			queryBridgeWords(word1, word2);
		}
		break;
		case 3:
		{
			printf("请输入旧文本:\n");
			char* e = (char*)malloc(sizeof(char) * 100);
			scanf("%[^\n]", e);
			getchar();
			strcat(e, " ");
			generateNewText(e);
		}
		break;
		case 4:
		{
			int i = 0;
			//struct headnode* ver[]
			struct headnode* a = First;
			while (a != NULL) {
				i++;
				a = a->next;
			}
			number = i;

			i = 0;
			a = First;
			while (a != NULL) {
				graph[i] = a;
				i++;
				a = a->next;
			}
			std::cout << "输入最短路径的起点和终点" << std::endl;
			char word1[20], word2[20];
			/*cin >> word1;
			cin >> word2;*/
			std::string input;
			std::cout << "输入最短路径的起点" << std::endl;
			scanf("%s", word1);
			while (getchar() != '\n') {}
			std::cout << "输入最短路径的终点" << std::endl;
			std::getline(std::cin, input);
			if (input.empty()) {
				if (find(word1) == 0) {
					std::cout << "没有你要查询的节点" << std::endl;
					getchar();
					break;
				}
				srand(time(0));
				int randomnumber = rand() % number;
				struct headnode* a = graph[randomnumber];
				strcpy(word2, a->id);
				calcShortestPath(word1, word2);
				break;
			}
			strcpy(word2, input.c_str());
			if (find(word1) == 0 || find(word2) == 0) {
				std::cout << "没有你要查询的节点" << std::endl;
				break;
			}
			calcShortestPath(word1, word2);
			break;
		}
		break;
		case 5:
		{
			randonWalk();
		}
		break;
		case 6:
			return 0;
		default:
		{
			printf("输入序号不正确，请重新输入!\n");
		}
			break;
		}
	}

}

void show()
{
	printf("程序功能如下:\n");
	printf("1.展示生成的有向图\n");
	printf("2.查询两个单词的桥接词\n");
	printf("3.根据桥接词将旧文本扩充为新文本\n");
	printf("4.计算两个单词之间的最短路径\n");
	printf("5.随机游走(固定向random_walk.txt输出)\n");
	printf("6.退出\n");
	printf("请输入你的选择:");
}
struct headnode* create(FILE* fp)
{
	char c;//单个字符
	char word[20];//整个单词
	int hasword = 0;
	struct headnode* first = (struct headnode*)malloc(sizeof(struct headnode));//头一个单词同时作为返回值
	struct headnode* previous = NULL;
	int i = 0;
	while ((c = fgetc(fp)) != EOF)//文件末尾
	{
		//printf("%c\n", c);
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))//符号为a-z
		{
			if (c >= 'A' && c <= 'Z')
				c += 32;
			word[i] = c;
			i++;
			//printf("%c", word[i - 1]);
		}
		else if (c == ' ' || c == '\n' || c == ',' || c == '.' || c == '?' || c == '!')//标点符号 换行符 空格
		{
			if (i == 0)
			{
				continue;//i=0表示刚开始或者前一个单词已经处理完
			}
			else
			{

				word[i] = '\0';
				//printf("%s\n", word);
				i = 0;
				if (hasword)//有上个单词
				{
					int flag = 0;//flag=0表示不存在该邻接单词
					struct nearnode* selected = previous->near;
					if (selected == NULL)
					{
					}
					else
					{
						while (selected != NULL)
						{
							if (!strcmp(selected->id, word))
							{
								flag = 1;
								break;
							}
							selected = selected->near;
						}
					}
					if (flag == 0)//新增邻接结点同时检查是否存在该表头结点
					{
						struct nearnode* newnearnode = (struct nearnode*)malloc(sizeof(struct nearnode));
						newnearnode->count = 1;
						strcpy(newnearnode->id, word);
						newnearnode->near = NULL;
						struct nearnode* fznode = previous->near;
						//printf("%s\n", previous->id);
						if (fznode == NULL)
						{
							//printf("%s", previous->id);
							previous->near = newnearnode;
							//printf("%s\n", previous->near->id);
						}
						else
						{
							while (fznode->near != NULL)
							{
								fznode = fznode->near;
							}
							fznode->near = newnearnode;
						}

						int flag2 = 0;//查头结点是否存在
						struct headnode* select = first;
						if (!strcmp(word, select->id))
						{
							flag2 = 1;
							previous = select;
							//printf("%saaaaaa\n", word);
						}
						else
						{
							while (select->next != NULL)
							{
								if (!strcmp(word, select->next->id))
								{
									//printf("aaa");
									//printf("%s", word);
									flag2 = 1;
									previous = select->next;
									break;
								}
								//printf("%s\n", select->id);
								select = select->next;
							}
						}
						if (!flag2)//如果不存在则新增头结点
						{
							struct headnode* newheadnode = (struct headnode*)malloc(sizeof(struct headnode));
							strcpy(newheadnode->id, word);
							newheadnode->near = NULL;
							newheadnode->next = NULL;
							select->next = newheadnode;
							//printf("%s\n", select->next->id);
							previous = newheadnode;
						}
						else
						{
						}//若存在不进行处理

					}
					else
					{
						selected->count++;
					}
				}
				else//第一个单词
				{
					strcpy(first->id, word);
					first->near = NULL;
					first->next = NULL;
					previous = first;
					hasword = 1;
				}
			}
		}
		else
		{
			continue;//其他字符跳过不处理
		}
		//printf("%s\n", previous->id);
	}
	if (i != 0)
	{
		word[i] = '\0';
		//printf("%s\n", word);
		i = 0;
		if (hasword)//有上个单词
		{
			int flag = 0;//flag=0表示不存在该邻接单词
			struct nearnode* selected = previous->near;
			if (selected == NULL)
			{
			}
			else
			{
				while (selected != NULL)
				{
					if (!strcmp(selected->id, word))
					{
						flag = 1;
						break;
					}
					selected = selected->near;
				}
			}
			if (flag == 0)//新增邻接结点同时检查是否存在该表头结点
			{
				struct nearnode* newnearnode = (struct nearnode*)malloc(sizeof(struct nearnode));
				newnearnode->count = 1;
				strcpy(newnearnode->id, word);
				newnearnode->near = NULL;
				struct nearnode* fznode = previous->near;
				//printf("%s\n", previous->id);
				if (fznode == NULL)
				{
					//printf("%s", previous->id);
					previous->near = newnearnode;
					//printf("%s\n", previous->near->id);
				}
				else
				{
					while (fznode->near != NULL)
					{
						fznode = fznode->near;
					}
					fznode->near = newnearnode;
				}

				int flag2 = 0;//查头结点是否存在
				struct headnode* select = first;
				if (!strcmp(word, select->id))
				{
					flag2 = 1;
					previous = select;
					//printf("%saaaaaa\n", word);
				}
				else
				{
					while (select->next != NULL)
					{
						if (!strcmp(word, select->next->id))
						{
							//printf("aaa");
							//printf("%s", word);
							flag2 = 1;
							previous = select->next;
							break;
						}
						//printf("%s\n", select->id);
						select = select->next;
					}
				}
				if (!flag2)//如果不存在则新增头结点
				{
					struct headnode* newheadnode = (struct headnode*)malloc(sizeof(struct headnode));
					strcpy(newheadnode->id, word);
					newheadnode->near = NULL;
					newheadnode->next = NULL;
					select->next = newheadnode;
					//printf("%s\n", select->next->id);
					previous = newheadnode;
				}
				else
				{
				}//若存在则不进行任何处理

			}
			else
			{
				selected->count++;
			}
		}
		else//第一个单词
		{
			strcpy(first->id, word);
			first->near = NULL;
			first->next = NULL;
			previous = first;
			hasword = 1;
		}
	}
	return first;
}
void showDirectedGraph()
{
	std::cout << std::endl;
	struct headnode* a = First;
	struct nearnode* b = a->near;

	float x = 100, y = 100;
	while (a != NULL) {
		addNode(a->id, x, y);
		x += 200;
		y += pow((-1), ((int)x / 200) % 2) * 20;
		if (x > 700) {
			x = 200;
			y += 100;
		}
		a = a->next;
	}
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");
	if (!font.loadFromFile("arial.ttf")) {
		cerr << "无法加载字体文件" << endl;
		return;
	}

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::White);


		a = First;
		sf::Color textColor = sf::Color::Green;
		for (const auto& pair : nodePositions) {
			const string& nodeName = pair.first;
			const sf::Vector2f& pos = pair.second;

			sf::CircleShape circle(5);
			circle.setFillColor(sf::Color::Green);
			circle.setPosition(pos.x - 5, pos.y - 5);
			window.draw(circle);

			sf::Text text(nodeName, font, 15); // 使用全局的字体
			text.setFillColor(textColor);
			text.setPosition(pos.x - 5, pos.y - 25);
			window.draw(text);
		}

		while (a != NULL) {
			b = a->near;
			while (b != NULL) {
				string word1 = a->id;
				string word2 = b->id;
				addEdge(window, word1, word2, b->count);
				b = b->near;
			}
			a = a->next;
		}


		window.display();
	}
}
char* queryBridgeWords(char* word1, char* word2)
{
	for (int z = 0; z < strlen(word1); z++)
	{
		if (word1[z] >= 'A' && word1[z] <= 'Z')
			word1[z] += 32;
	}
	for (int z = 0; z < strlen(word2); z++)
	{
		if (word2[z] >= 'A' && word2[z] <= 'Z')
			word2[z] += 32;
	}
	char* bridgewords;
	bridgewords = (char*)malloc(sizeof(char) * 100);
	int count1 = 0;
	int count2 = 0;
	int flag2 = 0;//是否存在连接词
	struct headnode* first = First;
	struct headnode* select1 = First;
	int j = 0;//用于赋值
	while (select1 != NULL)
	{
		if (!strcmp(select1->id, word1))
			count1 = 1;

		if (!strcmp(select1->id, word2))
			count2 = 1;
		select1 = select1->next;
	}
	if (count1 != 1 && count2 != 1)
	{
		strcpy(bridgewords, "No word!");
		printf("No \"%s\" and \"%s\" in the graph!\n", word1, word2);
		return bridgewords;
	}
	else if (count1 != 1 && count2 == 1)
	{
		strcpy(bridgewords, "No word!");
		printf("No \"%s\" in the graph!\n", word1);
		return bridgewords;
	}
	if (count1 == 1 && count2 != 1)
	{
		strcpy(bridgewords, "No word!");
		printf("No \"%s\" in the graph!\n", word2);
		return bridgewords;
	}
	while (first != NULL)
	{
		if (!strcmp(first->id, word1))
		{
			break;
		}
		first = first->next;
	}
	struct nearnode* nearr = first->near;
	while (nearr != NULL)
	{
		struct headnode* middleheadnode = First;
		while (middleheadnode != NULL)
		{
			if (!strcmp(middleheadnode->id, nearr->id))
			{
				struct nearnode* select = middleheadnode->near;
				while (select != NULL)
				{
					if (!strcmp(select->id, word2))
					{
						for (int i = 0; i < strlen(nearr->id); i++)
						{
							bridgewords[j] = nearr->id[i];
							j++;
						}
						bridgewords[j] = ',';
						j++;
						flag2 = 1;
					}//找到word2
					select = select->near;
				}
			}//找到中间node的头结点
			middleheadnode = middleheadnode->next;
		}
		nearr = nearr->near;
	}
	if (flag2 == 0)
	{
		strcpy(bridgewords, "No word!");
		printf("No bridge words from \"%s\" to \"%s\"!\n", word1, word2);
		return bridgewords;
	}
	else
	{
		bridgewords[j - 1] = '\0';//消除最后一个逗号
		printf("The bridge words from \"%s\" to \"%s\" is: %s\n", word1, word2, bridgewords);
		return bridgewords;//处理bridgewords并输出
	}
}
char* generateNewText(char* inputText)
{
	char* word1;
	word1 = (char*)malloc(sizeof(char) * 20);
	char* word2;
	word2 = (char*)malloc(sizeof(char) * 20);
	char* jilu;
	jilu = (char*)malloc(sizeof(char) * 20);
	char* newText;
	newText = (char*)malloc(sizeof(char) * 1000);
	char* bridgewords;//所有桥接词
	bridgewords = (char*)malloc(sizeof(char) * 100);
	char* bridgeword;//选中的桥接词
	bridgeword = (char*)malloc(sizeof(char) * 20);
	newText = (char*)malloc(sizeof(char) * 1000);
	int j = 0;//记录单词下标
	int m = 0;
	int n = 0;
	int z = 0;//新文本下标
	int flag = 0;//记录是否已经将两个初始word准备好
	int first = 0;
	for (int i = 0; i < strlen(inputText); i++)
	{
		newText[z] = inputText[i];
		z++;
		if ((inputText[i] >= 'a' && inputText[i] <= 'z') || (inputText[i] >= 'A' && inputText[i] <= 'Z'))
		{
			jilu[j] = inputText[i];
			j++;
		}
		else if (j == 0)//空格而且没有单词
		{
		}
		else//单词已结束
		{
			if (flag == 0)
			{
				jilu[j] = '\0';
				strcpy(word1, jilu);
				j = 0;
				flag = 1;
			}
			else if (flag == 1)
			{
				if (first == 1)
				{
					strcpy(word1, word2);
				}
				first = 1;
				jilu[j] = '\0';
				strcpy(word2, jilu);
				j = 0;
				strcpy(bridgewords, queryBridgeWords(word1, word2));
				//printf("test%s\n",bridgewords);
				if (!strcmp(bridgewords, "No word!"))
				{
				}
				else//有桥接词
				{
					int sum = 1;//一共有sum个桥接词
					for (int h = 0; h < strlen(bridgewords); h++)
					{
						if (bridgewords[h] == ',')
							sum++;
					}
					srand((unsigned int)time(NULL));
					int randword = rand() % sum + 1;//生成第随机个桥接词
					printf("随机选择到第%d个桥接词\n", randword);//第randword-1到randword个逗号之间的词
					if (randword == 1)
					{
						int h = 0;
						while (bridgewords[h] != '\0' && bridgewords[h] != ',')
						{
							bridgeword[h] = bridgewords[h];
							h++;
						}
						bridgeword[h] = '\0';
					}
					else//不是第一个
					{
						int h = 0;
						int sum = 1;
						while (sum != randword)
						{
							if (bridgewords[h] == ',')
								sum++;
							h++;
						}//此时h指向单词第一个字母
						int f = 0;
						while (bridgewords[h] != '\0' && bridgewords[h] != ',')
						{
							bridgeword[f] = bridgewords[h];
							f++;
							h++;
						}
						bridgeword[f] = '\0';
					}
					printf("randbridgeword: %s\n", bridgeword);
					z -= strlen(word2) + 1;
					newText[z] = '\0';
					strcat(newText, bridgeword);
					z += strlen(bridgeword);
					newText[z] = ' ';
					newText[z + 1] = '\0';
					strcat(newText, word2);
					z += strlen(word2) + 1;
					//printf("\n%c\n", newText[z]);
					newText[z] = ' ';
					z += 1;
				}
			}

		}
	}
	newText[z] = '\0';
	printf("oldText:%s\n", inputText);
	printf("newText:%s\n", newText);
	return newText;
}
char* calcShortestPath(char* word1, char* word2)
{
	int ps;
	int dist[MAXLEN], pre[MAXLEN];
	ps = getposition(word1);
	int i, j, k, t, m;
	int min;
	int tmp;
	int flag[INFINE];

	for (i = 0; i < number; i++) {
		flag[i] = 0;
		pre[i] = ps;
		dist[i] = get_weight(ps, i);
		//path[i][0] = 0;
	}
	flag[ps] = 1;
	dist[ps] = 0;
	//path[ps][0] = 1;
	for (i = 1; i < number; i++) {
		//t = 0;
		min = INFINE;
		for (int zip = 0; zip < number; zip++) {
			if (flag[zip] == 0)
				k = zip;
		}
		for (j = 0; j < number; j++) {
			if (flag[j] == 0 && dist[j] < min) {
				min = dist[j];
				k = j;
			}
		}
		flag[k] = 1;
		for (j = 0; j < number; j++) {
			tmp = get_weight(k, j);
			tmp = (tmp == INFINE ? INFINE : (min + tmp));
			if (flag[j] == 0 && (tmp < dist[j])) {
				dist[j] = tmp;
				pre[j] = k;
				//path[j][t] = k;
				//t++;
			}
		}
	}
	int ends = getposition(word2);
	if (dist[ends] == INFINE) {
		std::cout << "这两点不可达" << std::endl;
		return NULL;
	}
	std::cout << word1 << "到" << word2 << "的最短路径如下" << std::endl;

	int showpath[MAXLEN];
	int top = -1;
	memset(showpath, -1, sizeof(showpath));
	showpath[++top] = ends;
	int qian = pre[ends];
	while (qian != ps) {
		showpath[++top] = qian;
		qian = pre[qian];
	}
	showpath[++top] = qian;
	int max = top;
	std::cout << "最短路径的长度是" << dist[ends] << std::endl;
	while (top != 0) {
		std::cout << graph[showpath[top--]]->id << "->";

	}
	std::cout << graph[showpath[top]]->id;
	top--;




	std::cout << std::endl;
	struct headnode* a = First;
	struct nearnode* b = a->near;

	float x = 100, y = 100;
	while (a != NULL) {
		addNode(a->id, x, y);
		x += 200;
		y += pow((-1), ((int)x / 200) % 2) * 20;
		if (x > 700) {
			x = 200;
			y += 100;
		}
		a = a->next;
	}
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");
	if (!font.loadFromFile("arial.ttf")) {
		cerr << "无法加载字体文件" << endl;
		return NULL;
	}

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::White);
		int variable = dist[ends]; // 举例
		std::string textToPrint = "The shortest path length is: " + std::to_string(variable);

		// 创建文字对象
		sf::Text topLeftText(textToPrint, font, 15);
		topLeftText.setFillColor(sf::Color::Black);
		topLeftText.setPosition(10, 10); // 调整文字位置

		// 在窗口上绘制文字对象
		window.draw(topLeftText);

		a = First;
		sf::Color textColor = sf::Color::Green;
		for (const auto& pair : nodePositions) {
			const string& nodeName = pair.first;
			const sf::Vector2f& pos = pair.second;

			sf::CircleShape circle(5);
			circle.setFillColor(sf::Color::Green);
			circle.setPosition(pos.x - 5, pos.y - 5);
			window.draw(circle);

			sf::Text text(nodeName, font, 15); // 使用全局的字体
			text.setFillColor(textColor);
			text.setPosition(pos.x - 5, pos.y - 25);
			window.draw(text);
		}
		while (a != NULL) {
			b = a->near;
			while (b != NULL) {
				string word11 = a->id;
				string word22 = b->id;
				if (!abin(word11, word22, showpath, max))
					addEdge(window, word11, word22, b->count);
				else
					addblueEdge(window, word11, word22, b->count);
				b = b->near;
			}
			a = a->next;
		}



		window.display();
	}
	return NULL;
}
char* randonWalk()
{
	int find[MAXLEN][MAXLEN] = { 0 };
	std::ofstream outputFile("random_walk.txt");
	if (!outputFile.is_open()) {
		std::cerr << "无法打开文件" << std::endl;
		return NULL;
	}
	srand(time(0));
	int randomnumber = rand() % number;
	struct headnode* a = graph[randomnumber];
	outputFile << a->id << " ";
	int nearnumber = findnumber(a);
	while (nearnumber != 0) {
		struct nearnode* b = a->near;
		randomnumber = rand() % nearnumber;
		for (int i = 1; i < randomnumber; i++) {
			b = b->near;
		}
		int m = getposition(a->id);
		int n = getposition(b->id);
		if (find[m][n] == 0) {
			find[m][n] = 1;
			outputFile << b->id << " ";
			a = graph[n];
			nearnumber = findnumber(a);
		}
		else {
			outputFile << b->id << " ";
			outputFile.close();
			return NULL;
		}
	}
	outputFile.close();
	return NULL;
}